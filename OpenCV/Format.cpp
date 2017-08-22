#include <opencv2/opencv.hpp>
//#include <string>
using namespace cv;
using namespace std;


int main() {
    Mat r = Mat(10, 3, CV_8UC3);
    randu(r, Scalar::all(0), Scalar::all(255));
    cout << "default: " << endl << r << endl;
    cout << "python: " << endl << format(r, Formatter::FMT_PYTHON) << endl;
    cout << "comma: " << endl << format(r, Formatter::FMT_CSV) << endl;
    cout << "numpy: " << endl << format(r, Formatter::FMT_NUMPY) << endl;
    cout << "c: " << endl << format(r, Formatter::FMT_C) << endl;

    return 0;
}

