import os, time
from PIL import ImageChops, Image
import cv2
import numpy as np
import serial

#sp = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)

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
        _, diff = cv2.threshold(diff, 30, 255, cv2.THRESH_BINARY)
        contours, _ = cv2.findContours(diff, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
        
        COLOR = (0, 200, 0)
    
        for cnt in contours:
            if cv2.contourArea(cnt) > 10000:
                x, y, width, height = cv2.boundingRect(cnt)
                cv2.rectangle(frame, (x, y), (x + width, y + height), COLOR, 2)
            cv2.imshow('chage', frame)
            cv2.imshow('root', src)
            

    key = cv2.waitKey(1)
    if key == ord('q'):
        break
        
webcam.release()
cv2.destroyAllWindows()

    