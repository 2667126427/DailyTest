//#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define WINDOW_WIDTH 600
#define WinName1 "Win1"
#define WinName2 "Win2"
//#include <string>
using namespace cv;
using namespace std;

void DrawEllipse(Mat img, double angle) {
    int thickness = 2;
    int lineType = 8;

    // 目标图像
    ellipse(img,
            // 椭圆中心
            Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2),
            // 大小位置
            Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16),
            // 旋转角度
            angle,
            // 拓展的弧度
            0,
            360,
            // 颜色蓝色
            Scalar(255, 129, 0),
            // 线段宽度
            thickness,
            // 线型
            lineType);
}

void DrawFilledCircle(Mat img, Point center) {
    int thickness = -1;
    int lineType = 8;

    circle(img,
           center,
           WINDOW_WIDTH / 32,
           Scalar(0, 0, 255),
           thickness,
           lineType);
}

void DrawPolygon(Mat img) {
    int lineType = 8;
    // 创建一些点
    Point rootPoints[1][20];
    rootPoints[0][0] = Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
    rootPoints[0][1] = Point(3 * WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
    rootPoints[0][2] = Point(3 * WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);
    rootPoints[0][3] = Point(11 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
    rootPoints[0][4] = Point(19 * WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
    rootPoints[0][5] = Point(3 * WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 8);
    rootPoints[0][6] = Point(3 * WINDOW_WIDTH / 4, WINDOW_WIDTH / 8);
    rootPoints[0][7] = Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
    rootPoints[0][8] = Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
    rootPoints[0][9] = Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
    //
    rootPoints[0][10] = Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
    rootPoints[0][11] = Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
    rootPoints[0][12] = Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
    rootPoints[0][13] = Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
    rootPoints[0][14] = Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
    rootPoints[0][15] = Point(WINDOW_WIDTH / 4, WINDOW_WIDTH / 8);
    rootPoints[0][16] = Point(WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 8);
    rootPoints[0][17] = Point(13 * WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
    rootPoints[0][18] = Point(5 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
    rootPoints[0][19] = Point(WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);
    //
    const Point *ppt[1] = {rootPoints[0]};
    int npt[] = {20};
    fillPoly(img,
             ppt,
             npt,
             1,
             Scalar(255, 255, 255),
             lineType);
}

void DrawLine(Mat img, Point start, Point end) {
    int thickness = 2;
    int lineType = 8;
    line(img,
         start,
         end,
         Scalar(0, 0, 0),
         thickness,
         lineType);
}

int main() {
    // 创建空图像
    Mat atomImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
    Mat rookImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
    // 先绘制椭圆
    DrawEllipse(atomImage, 90);
    DrawEllipse(atomImage, 0);
    DrawEllipse(atomImage, 45);
    DrawEllipse(atomImage, -45);
    // 绘制圆心
    DrawFilledCircle(atomImage, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));
//    imshow(WinName1, atomImage);
    // 绘制组合图
    DrawPolygon(rookImage);
    // 绘制矩形
    rectangle(rookImage,
              Point(0, 7 * WINDOW_WIDTH / 8),
              Point(WINDOW_WIDTH, WINDOW_WIDTH),
              Scalar(0, 255, 255),
              -1,
              8);
    // 绘制一些线段
    DrawLine(rookImage, Point(0, 15 * WINDOW_WIDTH / 16), Point(WINDOW_WIDTH, 15 * WINDOW_WIDTH / 16));
    DrawLine(rookImage, Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH / 4, WINDOW_WIDTH));
    DrawLine(rookImage, Point(WINDOW_WIDTH / 2, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH / 2, WINDOW_WIDTH));
    DrawLine(rookImage, Point(3 * WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), Point(3 * WINDOW_WIDTH / 4, WINDOW_WIDTH));
    // 显示图像
    imshow(WinName1, atomImage);
    moveWindow(WinName1, 0, 200);
    imshow(WinName2, rookImage);
    moveWindow(WinName2, WINDOW_WIDTH, 200);


    waitKey(0);
    return 0;
}

