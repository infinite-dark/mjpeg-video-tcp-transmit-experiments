import pygame
import numpy as np
import cv2

import socket
from threading import Thread


class Receiver:

    def __init__(self):
        pygame.init()
        
        self.screen = pygame.display.set_mode((1280, 720), pygame.NOFRAME, vsync=1)
        self.clock = pygame.time.Clock()
        self.running = False
        
        self.receiver_thread = Thread(target=self.receiveFrame, daemon=False)
        self.frame = np.zeros((720, 1080, 3), dtype=np.uint8)

    def start(self) -> None:
        self.running = True
        self.receiver_thread.start()
        self.run()

    def run(self):
        while self.running:
            self.render()
            self.handleEvents()
            self.clock.tick(30)
        pygame.quit()
    
    def stop(self) -> None:
        self.running = False
        self.receiver_thread.join()
    
    def render(self) -> None:
        self.drawVideoFrame()
        pygame.display.flip()

    def handleEvents(self) -> None:
        for event in pygame.event.get():
            if event.type == pygame.KEYUP:
                if event.key in (pygame.K_ESCAPE, pygame.K_q):
                    self.stop()
                    break

    def receiveFrame(self) -> None:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect(("", 5000))
            data = b""
    
            while self.running:
                try:
                    while b"\xff\xd8" not in data:
                        data += s.recv(8192)
                    start = data.find(b"\xff\xd8")
            
                    while b"\xff\xd9" not in data:
                        data += s.recv(8192)
                    end = data.find(b"\xff\xd9")
            
                    image = data[start:end+2]
                    data = data[end+2:]
            
                    image = np.frombuffer(image, np.uint8)
                    image = cv2.imdecode(image, cv2.IMREAD_COLOR)
                    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
                    self.frame = cv2.flip(image, 1)

                except socket.error:
                    self.frame = np.zeros((720, 1080, 3), dtype=np.uint8)
                    break


    def drawVideoFrame(self) -> None:
        frame = pygame.surfarray.make_surface(np.rot90(self.frame))
        self.screen.blit(frame, (0, 0))


if __name__ == "__main__":
    receiver = Receiver()
    receiver.start()

