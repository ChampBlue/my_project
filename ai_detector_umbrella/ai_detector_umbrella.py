import torch
import cv2
from numpy import random

model = torch.hub.load('ultralytics/yolov5', 'custom', path = 'yolov5s.pt')

cap = cv2.VideoCapture(0)

while cap.isOpened():
    ret, frame = cap.read()
    
    if ret:
        frame = cv2.resize(frame, (640, 640))
        results = model(frame)
        detections = results.pandas().xyxy[0]
        
        if not detections.empty:
            for _, detection in detections.iterrows():
                x1, y1, x2, y2 = detection[['xmin', 'ymin', 'xmax', 'ymax']].astype(int).values
                detection['class'] = 25
                label_index = int(detection['class'])
                label = results.names[label_index]
                conf = detection['confidence']
                
                color = [int(c) for c in random.choice(range(256), size = 3)]
                cv2.rectangle(frame, (x1,y1), (x2, y2), color, 2)
                cv2.putText(frame, f'{label} {conf:.2f}', (x1, y1 -10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, color, 2)
                
                
        cv2.imshow('frame', frame)
                
        if cv2.waitKey(1) == 27:
            break
    
    else:
        break
    
cap.release()
cv2.destroyAllWindows()
