#include <opencv2/opencv.hpp>

using namespace cv;

#define winName "window"

// 全局函数声明
void on_MouseHandle(int event, int x, int y, int flags, void *param);

void DrawRectangle(Mat &img, Rect box);

//void ShowHelpText();

//全局变量声名
Rect g_rectangle;
bool g_bDrawingBox = false;
RNG g_rng(12345);
// main函数

int main() {
    g_rectangle = Rect(-1, -1, 0, 0);
    Mat srcImage(600, 800, CV_8UC3), tempImage;
    srcImage.copyTo(tempImage);
    g_rectangle = Rect(-1, -1, 0, 0);
    srcImage = Scalar::all(0);
    // 设置回调函数
    namedWindow(winName);
    setMouseCallback(winName, on_MouseHandle, (void *) &srcImage);
    // 主循环
    while (true) {
        srcImage.copyTo(tempImage);
        if (g_bDrawingBox) DrawRectangle(tempImage, g_rectangle);
        imshow(winName, tempImage);
        if (waitKey(10) == 27) break;
    }

    return 0;
}

void on_MouseHandle(int event, int x, int y, int flags, void *param) {
    Mat &image = *(Mat *) param;
    switch (event) {
        case EVENT_MOUSEMOVE: {
            if (g_bDrawingBox) {
                g_rectangle.width = x - g_rectangle.x;
                g_rectangle.height = y - g_rectangle.y;
            }
        }
            break;
        case EVENT_LBUTTONDOWN: {
            g_bDrawingBox = true;
            g_rectangle = Rect(x, y, 0, 0);
        }
            break;
        case EVENT_LBUTTONUP: {
            g_bDrawingBox = false;
            if (g_rectangle.width < 0) {
                g_rectangle.x += g_rectangle.width;
                g_rectangle.width *= -1;
            }
            if (g_rectangle.height < 0) {
                g_rectangle.y += g_rectangle.height;
                g_rectangle.height *= -1;
            }
            DrawRectangle(image, g_rectangle);
        }
            break;
    }
}

void DrawRectangle(Mat &img, Rect box) {
    rectangle(img, box.tl(), box.br(), Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));
}

