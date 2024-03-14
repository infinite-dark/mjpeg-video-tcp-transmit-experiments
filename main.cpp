#include "src/camserver.h"

int main() {
    CameraServer server(0);
    server.initialize("127.0.0.1", 5000);
    server.start();
    server.join();

    return 0;
}
