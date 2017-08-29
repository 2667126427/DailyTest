//#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <iostream>

using namespace cv;
using namespace std;

string path = "/home/yaning/JetBrains/clion/OpenCV/";

void colorReduce(Mat &input, Mat &output, int div) {
    output = input.clone();
    int rows = output.rows;
    int cols = output.cols;
//
//    for (int i = 0; i < rows; ++i) {
//        uchar *data = output.ptr(i);
//        for (int j = 0; j < cols; ++j) {
//            data[j] = static_cast<uchar>(data[j] / div * div + div / 2);
//        }
//    }

//    Mat_<Vec3b>::iterator it = output.begin<Vec3b>();
//    Mat_<Vec3b>::iterator end = output.end<Vec3b>();
//
//    for (; it != end; ++it) {
//        (*it)[0] = static_cast<uchar>((*it)[0] / div * div + div / 2);
//        (*it)[1] = static_cast<uchar>((*it)[1] / div * div + div / 2);
//        (*it)[2] = static_cast<uchar>((*it)[2] / div * div + div / 2);
//    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            output.at<Vec3b>(i, j)[0] = static_cast<uchar>(output.at<Vec3b>(i, j)[0] / div * div + div / 2);
            output.at<Vec3b>(i, j)[1] = static_cast<uchar>(output.at<Vec3b>(i, j)[1] / div * div + div / 2);
            output.at<Vec3b>(i, j)[2] = static_cast<uchar>(output.at<Vec3b>(i, j)[2] / div * div + div / 2);
        }
    }

}

bool LinearBlending() {
    double alphaValue = 0.5;
    double betaValue;
    Mat src1, src2, dst;
    src1 = imread(path + "1.jpg");
    src2 = imread(path + "2.jpg");

//    assert(src1 * src2 != 0);

    betaValue = 1 - alphaValue;

    // 混合图片函数
    addWeighted(src1, alphaValue, src2, betaValue, 0.0, dst);

    imshow("1.jpg", src1);
    imshow("2.jpg", src2);
    imshow("now", dst);

    waitKey(0);
    return true;
}

int main() {
    LinearBlending();

//    waitKey(0);

    return 0;
}

