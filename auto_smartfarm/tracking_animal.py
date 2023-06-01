import torch
import cv2
from numpy import random
import serial
import time

try:
    sp = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
    print("serial connected~!!")
except:
    print("serial disconnected")

model = torch.hub.load('ultralytics/yolov5', 'custom', path='best_2.pt')

cap = cv2.VideoCapture(0)

recording = False
video_writer = None
        
if cap.isOpened():
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
            
                    if conf > 0.6:
                        color = [int(c) for c in random.choice(range(256), size=3)]
                        cv2.rectangle(frame, (x1, y1), (x2, y2), color, 2)
                        cv2.putText(frame, f'{label} {conf:.2f}', (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, color, 2)

                        if not recording:
                            recording = True
                            current_time = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
                            video_name = f"./save/{current_time}.avi"
                            video_writer = cv2.VideoWriter(video_name, cv2.VideoWriter_fourcc(*"XVID"), 1, (frame.shape[1], frame.shape[0]))
                        
                        sp.write(('on' + '\n').encode())

                        object_center_x = (x1 + x2) // 2
                        object_center_y = (y1 + y2) // 2

                        if object_center_x < 160:
                            sp.write(('pan' + '135' + '\n').encode())
                        elif object_center_x >= 160 and object_center_x < 320:
                            sp.write(('pan' + '90' + '\n').encode())
                        elif object_center_x >= 320:
                            sp.write(('pan' + '45' + '\n').encode())

                        if object_center_y <160:
                            sp.write(('tilt' + '135' +'\n').encode())
                        elif object_center_y >= 160 and object_center_y < 320:
                            sp.write(('tilt' + '90' +'\n').encode())
                        elif object_center_y >= 320:
                            sp.write(('tilt' + '45' +'\n').encode())
                    else:
                        sp.write(('off' + '\n').encode())

            if recording:
                video_writer.write(frame)
                
            if recording and detections.empty:
                recording = False
                video_writer.release()

            cv2.imshow('frame', frame)

            if cv2.waitKey(1) == 27:
                break
        else:
            break

sp.close()
cap.release()
cv2.destroyAllWindows()
