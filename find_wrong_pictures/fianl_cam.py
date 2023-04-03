import os
import cv2
import serial

sp = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)

webcam = cv2.VideoCapture(0)

if not webcam.isOpened():
    print("Could not open webcam")
    exit()
else:
    status, frame = webcam.read()
    cv2.imwrite("./ref.png",frame)
    
    while not os.path.exists('ref.png'):
        pass

src = cv2.imread('./ref.png')
src = cv2.cvtColor(src, cv2.COLOR_BGR2GRAY)

while webcam.isOpened():
    status, frame = webcam.read()
    curr_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    if status:
        diff = cv2.absdiff(src, curr_frame)    
        _, diff = cv2.threshold(diff, 100, 255, cv2.THRESH_BINARY)
        contours, _ = cv2.findContours(diff, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
        
        COLOR = (0, 200, 0)
        #count = 0
        
        for cnt in contours:
            if cv2.contourArea(cnt) > 5000:
                x, y, width, height = cv2.boundingRect(cnt)
                cv2.rectangle(frame, (x, y), (x + width, y + height), COLOR, 2)
                
                if 0<=(x+width//2)<213:
                    sp.write(('pan' + '45' + '\n').encode())
                elif 213<=(x+width//2)<416:
                    sp.write(('pan' + '90' + '\n').encode())
                elif 416<=(x+width//2)<=640: 
                    sp.write(('pan' + '135' + '\n').encode())
            
            cv2.imshow('change', frame)
            cv2.imshow('root', src)
            
        #if cv2.waitKey(1) == 13:  # Enter 키를 눌렀을 때 이미지 저장
            #cv2.imwrite("./detecting_diff_image/result_{}.jpg".format(count), frame)
            
    key = cv2.waitKey(1)
    if key == ord('q'):
        break
        
webcam.release()
cv2.destroyAllWindows()

    
