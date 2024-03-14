#include <opencv2/opencv.hpp>
#include "camserver.h"

CameraServer::CameraServer(int index, int width, int height, int fps) {
    std::cout << "camera: ";
    cam = new cv::VideoCapture(index, cv::CAP_V4L2);
    cam->set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
    cam->set(cv::CAP_PROP_FRAME_WIDTH, width);
    cam->set(cv::CAP_PROP_FRAME_HEIGHT, height);
    cam->set(cv::CAP_PROP_FPS, fps);
    if (!cam || !cam->isOpened())
        std::cout << "failed\n";
}

void CameraServer::serve(int client) {
    if (!cam || !cam->isOpened())
        return;

    cv::Mat frame;
    std::vector<uchar> buf;
    unsigned long sent, size;

    while (running) {
        bool ret = cam->read(frame);
        if (ret) {
            cv::imencode(".jpg", frame, buf);
            uchar* sbuf = buf.data();

            size = buf.size();
            sent = 0;

            while (running && sent < size)
                sent += ::send(client, sbuf, (size - sent) * sizeof(uchar), 0);
        }
    }
}

CameraServer::~CameraServer() {
    SocketServer::stop();
    cam->release();
    delete cam;
}
