//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
//#include <string>
//#include <vector>
using namespace cv;
using namespace std;
const string winName = "window";
const int g_nMaxAlphaValue = 100; //Alpha最大值
int g_nAlphaValueSlider;
double g_dAlphaValue;
double g_dBetaValue;

// 存储的变量
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

void on_Trackbar(int, void*) {
    // 当前alpha值相对最大的比例
    g_dAlphaValue = (double) g_nAlphaValueSlider / g_nMaxAlphaValue;
    // beta 值为1-alpha
    g_dBetaValue = 1 - g_dAlphaValue;
    // 根据alpha和beta线性混合
    addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0, g_dstImage);
    // 显示图片
    imshow(winName, g_dstImage);
}


int main() {
    g_srcImage1 = imread("1.jpg");
    g_srcImage2 = imread("2.jpg");

    g_nAlphaValueSlider = 70;
    // 创建窗体
    namedWindow(winName, 1);
    // 添加滑动条
    char TrackbarName[50];
    sprintf(TrackbarName, "透明值 %d", g_nMaxAlphaValue);
    createTrackbar(TrackbarName, winName, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);
    // 显示结果
    on_Trackbar(g_nAlphaValueSlider, 0);

    // 退出
    waitKey(0);


    return 0;
}

