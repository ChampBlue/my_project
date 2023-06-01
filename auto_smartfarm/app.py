from flask import Flask, render_template, Response
import cv2
import torch
from numpy import random
import mysql.connector
import serial
from flask_socketio import SocketIO, emit
import threading

app = Flask(__name__)
socketio = SocketIO(app)

try:
	cap = cv2.VideoCapture(0)
except:
	print('camera disconnected')

try:
	sp = serial.Serial('/dev/ttyACM0', 9600, timeout = 0.1)
	print("serial connect")
except:
	print("serial disconnect")

read_data = ''
def serial_read_thread():
	global read_data
	while True:
		read_data = sp.readline().decode()

t1 = threading.Thread(target=serial_read_thread)
#t1.daemon = True
t1.start()

connection = mysql.connector.connect(
	host = 'localhost',
	user = 'root',
	password = 'pi',
	database = 'smartfarm'
)

model = torch.hub.load('ultralytics/yolov5', 'custom', path = 'best.pt')

@app.route('/')
def video_show():
	return render_template('index.html')

def gen_frames():
	global read_data
	while True:
		ret, frame = cap.read()
		if ret:
			frame = cv2.resize(frame, (480, 480))
			results = model(frame)
			detections = results.pandas().xyxy[0]

			if not detections.empty:
				for _, detection in detections.iterrows():
					x1, y1, x2, y2 = detection[['xmin', 'ymin', 'xmax', 'ymax']].astype(int).values
					label = detection['name']
					conf = detection['confidence']
                    
					color = [int(c) for c in random.choice(range(256), size = 3)]
                    
					cv2.rectangle(frame, (x1, y1), (x2, y2), color, 2)
					cv2.putText(frame, f'{label} {conf:.2f}', (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, color, 2)
			
			_, buffer = cv2.imencode('.jpg',frame)
			frame = buffer.tobytes()
			
			yield (b'--frame\r\n'
					b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')
		
		if read_data != "":
			print("read_data:",read_data)
			#line = sp.readline().decode().rstrip()
			if read_data.startswith("humidity="):
				humidity = float(read_data[9:])
				cursor = connection.cursor()
				sql = "INSERT INTO farm_info (humidity) VALUES (%s)"
				cursor.execute(sql, (humidity,))
				connection.commit()
				socketio.emit('humidity', humidity)

			elif read_data.startswith("temperature="):
				temperature = float(read_data[12:])
				cursor = connection.cursor()
				sql = "INSERT INTO farm_info (temperature) VALUES (%s)"
				cursor.execute(sql, (temperature,))
				connection.commit()
				socketio.emit('temperature', temperature)

			elif read_data.startswith("lux="):
				lux = float(read_data[4:])
				cursor = connection.cursor()
				sql = "INSERT INTO farm_info (lux) VALUES (%s)"
				cursor.execute(sql, (lux,))
				connection.commit()
				socketio.emit('lux', lux)

			elif read_data.startswith("humidity_dirt="):
				humidity_dirt = float(read_data[14:])
				cursor = connection.cursor()
				sql = "INSERT INTO farm_info (humidity_dirt) VALUES (%s)"
				cursor.execute(sql, (humidity_dirt,))
				connection.commit()
				socketio.emit('humidity_dirt', humidity_dirt)
			read_data = ''

@app.route('/video')
def video():
	return Response(gen_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/data')
def data():
	cursor = connection.cursor()
	sql = "SELECT * FROM farm_info ORDER BY id DESC LIMIT 1"
	cursor.execute(sql)
	result = cursor.fetchone()

	if result:
		humidity = result[1]
		temperature = result[2]
		lux = result[3]
		humidity_dirt = result[4]
	else:
		humidity = 0
		temperature = 0
		lux = 0
		humidity_dirt = 0

	return render_template('index.html', humidity = humidity, temperature = temperature, lux = lux, humidity_dirt = humidity_dirt)

def send_to_arduino(data):
	if sp.is_open:
		encoded_data = data + '\n'
		print(encoded_data)
		sp.write(encoded_data.encode())

@socketio.on('command')
def handle_command(command):
	if command == 'right':
		send_to_arduino('right')
	elif command == 'left':
		send_to_arduino('left')
	elif command == 'default':
		send_to_arduino('default')
	elif command == 'up':
		send_to_arduino('up')
	elif command == 'down':
		send_to_arduino('down')

if __name__ == '__main__':
	socketio.run(app, host = '0.0.0.0', port = 8080)
	sp.close()
	connection.close()
	cap.release()
	cv2.destroyAllWindows()	
