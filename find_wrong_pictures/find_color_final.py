import cv2
import serial
import numpy as np

cap = cv2.VideoCapture(0)      

while(1):
    ret, frame = cap.read()    

    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)    

    lower_blue = np.array([100,100,120])          
    upper_blue = np.array([150,255,255])
    
    lower_green = np.array([50, 150, 50])        
    upper_green = np.array([80, 255, 255])

    lower_red = np.array([150, 50, 50])        
    upper_red = np.array([180, 255, 255])

    mask = cv2.inRange(hsv, lower_blue, upper_blue)
    mask1 = cv2.inRange(hsv, lower_green, upper_green)  
    mask2 = cv2.inRange(hsv, lower_red, upper_red)
     

    res = cv2.bitwise_and(frame, frame, mask=mask)   
    res1 = cv2.bitwise_and(frame, frame, mask=mask1)    
    res2 = cv2.bitwise_and(frame, frame, mask=mask2)       
    
    _, res = cv2.threshold(res, 130, 255, cv2.THRESH_BINARY)
    res = cv2.cvtColor(res, cv2.COLOR_BGR2GRAY)
    contours, _ = cv2.findContours(res, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    
    _, res1 = cv2.threshold(res1, 130, 255, cv2.THRESH_BINARY)
    res1 = cv2.cvtColor(res1, cv2.COLOR_BGR2GRAY)
    contours1, _ = cv2.findContours(res1, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    
    _, res2 = cv2.threshold(res2, 100, 255, cv2.THRESH_BINARY)
    res2 = cv2.cvtColor(res2, cv2.COLOR_BGR2GRAY)
    contours2, _ = cv2.findContours(res2, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    
    COLOR1 = (255, 0, 0)
    COLOR2 = (0, 255, 0)
    COLOR3 = (0, 0, 255)
    
    for cnt in contours:
        if cv2.contourArea(cnt) > 500:
            x, y, width, height = cv2.boundingRect(cnt)
            cv2.rectangle(frame, (x, y), (x + width, y + height), COLOR1, 2)
    for cnt in contours1:
        if cv2.contourArea(cnt) > 500:
            x, y, width, height = cv2.boundingRect(cnt)
            cv2.rectangle(frame, (x, y), (x + width, y + height), COLOR2, 2)
    for cnt in contours2:
        if cv2.contourArea(cnt) > 500:
            x, y, width, height = cv2.boundingRect(cnt)
            cv2.rectangle(frame, (x, y), (x + width, y + height), COLOR3, 2)
            
    cv2.imshow('frame',frame)       

    k = cv2.waitKey(5) & 0xFF
    if k == 27:
        break

cv2.destroyAllWindows()
