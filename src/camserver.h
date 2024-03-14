#include "server.h"
#include <vector>
#include <opencv4/opencv2/videoio.hpp>

#define WIDTH 1280
#define HEIGHT 720
#define FPS 30

class CameraServer : public SocketServer {
public:
    explicit CameraServer(int index, int width=WIDTH, int height=HEIGHT, int fps=FPS);
    void serve(int client) override;
    ~CameraServer();
private:
    cv::VideoCapture* cam;
};