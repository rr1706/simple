#include <chrono>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace std::chrono;
using namespace cv;

int main(int argc, char **argv)
{
    VideoCapture cam;
    Mat image;
    int keycode, frames, fps;
    high_resolution_clock::time_point last_compute, current_time;

    printf("Starting %s camera app...\n", argv[0]);
    cam.open(0);
    last_compute = high_resolution_clock::now();
    frames = 0;
    fps = 0;

    while (cam.isOpened()) {
        cam >> image;

        putText(image, "FPS: " + to_string(fps), Point(20, 20), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0));
        imshow("Image (" + to_string(image.cols) + "x" + to_string(image.rows) + ")", image);
        keycode = waitKey(33);
        frames += 1;
        current_time = high_resolution_clock::now();

        if ((keycode & 0xFF) == 27) {
            break;
        }
        duration<double> time_span = duration_cast<duration<double>>(current_time - last_compute);
        if (time_span.count() > 1.0) {
            fps = frames;
            frames = 0;
            last_compute = current_time;
        }
    }

    printf("Quitting application.\n");
    cam.release();
    return 0;
}
