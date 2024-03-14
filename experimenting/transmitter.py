import numpy as np
import cv2
import socket


cap = cv2.VideoCapture(0, cv2.CAP_V4L2)
cap.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter.fourcc(*"MJPG"))
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)
cap.set(cv2.CAP_PROP_FPS, 30)


if cap.isOpened():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind(("", 5000))
        s.listen(1)
        conn, addr = s.accept()
    
        while True:
            try:
                ret, frame = cap.read()
                if ret:
                    ret, frame = cv2.imencode(".jpg", frame)
                    encoded = frame.tobytes()
                    conn.sendall(encoded)
            except (socket.error, KeyboardInterrupt):
                conn.close()
                break

cap.release()

