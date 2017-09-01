#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/*Global function define*/
static void on_ContrastAndBright(int, void *);

static void ShowHelpText();

/*Global variable define*/
int g_nContrastValue;
int g_nBrightAndValue;
Mat g_srcImage, g_dstImage;

/*main function*/
int main() {
    const string path = "/home/yaning/JetBrains/clion/OpenCV/";
    g_srcImage = imread(path + "head.jpg");
    if (!g_srcImage.data) {
        cout << "Please check if you have the file of the path " + path + "head.jpg" << endl;
    }

    g_dstImage = Mat::zeros(g_srcImage.size(), g_dstImage.type());

    g_nContrastValue = 80;
    g_nBrightAndValue = 80;

    string winName = "dst window";
    namedWindow(winName, 1);
    createTrackbar("Contrast", winName, &g_nContrastValue, 300, on_ContrastAndBright);
    createTrackbar("Bright", winName, &g_nBrightAndValue, 200, on_ContrastAndBright);

    on_ContrastAndBright(g_nContrastValue, 0);
    on_ContrastAndBright(g_nBrightAndValue, 0);

    while ((char(waitKey(1)) != 'q')) {};

    return 0;
}

static void on_ContrastAndBright(int, void *) {
    string srcWinName = "src window";
    string dstWinName = "dst window";
    namedWindow(srcWinName, 1);

    for (int rows = 0; rows < g_srcImage.rows; ++rows) {
        for (int cols = 0; cols < g_srcImage.cols; ++cols) {
            g_dstImage.at<Vec3b>(rows, cols)[0] = static_cast<uchar>(
                    g_nContrastValue * 0.01 * (g_srcImage.at<Vec3b>(rows, cols)[0] + g_nBrightAndValue));
            g_dstImage.at<Vec3b>(rows, cols)[1] = static_cast<uchar>(
                    g_nContrastValue * 0.01 * (g_srcImage.at<Vec3b>(rows, cols)[1] + g_nBrightAndValue));
            g_dstImage.at<Vec3b>(rows, cols)[2] = static_cast<uchar>(
                    g_nContrastValue * 0.01 * (g_srcImage.at<Vec3b>(rows, cols)[2] + g_nBrightAndValue));
        }
    }

    imshow(srcWinName, g_srcImage);
    imshow(dstWinName, g_dstImage);
}

