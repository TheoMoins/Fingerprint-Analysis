#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "starter_1.h"
#include "main_1.h"
#include "elliptical_modelling.h"
using namespace cv;
using std::cout;
using std::endl;

int main(int argc, char** argv )
{
    if ( argc < 2 )
    {
        printf("usage: Test_1 <Image_Path> [Test]\n");
        return -1;
    }
    Mat image;
    image = imread(argv[1], 1);
    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }
    cout << "This test program will save all its work to the main directory" << endl;
    cout << "Image succesfully imported" << endl;

    /*TESTING THE XLIM YLIM COMPUTATION */
    cout << "Testing the extreme points computation...";;
    image = imread("../fingerprints/test_limpt.png",0);
    convert_to_float(image, image);
    assert(fingerprint_boundaries(image) == Point2i(233,69));
    cout << " Done" << endl;

    /* TESTING POINT COORDINATES */
    cout << "Creating image for highest intensity test...";
    image = imread("../fingerprints/black.png", 0);
    Point2i test_pt(image.cols/2, image.rows/2);
    image.at<uchar>(test_pt) = 255;
    imwrite("../black_test.png",image);
    cout << " Done" << endl;

    /*TESTING THE ROI FINDING*/
    cout << "Testing highest intensity zone research...";
    image = imread("../black_test.png", 0);
    Mat gblur;
    image.copyTo(gblur);
    GaussianBlur(image, gblur, Size(17, 17), 0, 0);
    double minVal = 0;
    double maxVal = 0;
    Point minLoc, maxLoc;
    minMaxLoc(gblur, &minVal, &maxVal, &minLoc, &maxLoc);
    Rect roi;
    roi = Rect(maxLoc.x-25, maxLoc.y-25, 50, 50);
    image=image(roi);
    imwrite("../roi.png",image);
    cout << " Done." << endl;

    /*TESTING ON FINGERPRINT*/
    cout << "Testing with fingerprint...";
    Mat image_color = imread("../fingerprints/clean_finger.png", 1);
    image_color.copyTo(image);
    cvtColor(image_color, image, COLOR_BGR2GRAY);
    GaussianBlur(image, image, Size(11,11), 0, 0);
    minMaxLoc(image, &minVal, &maxVal, &minLoc, &maxLoc);
    circle(image_color, minLoc, 5, Scalar(0,0,255));
    imwrite(".../img_roi.png", image_color);
    cout << " Done." << endl;


    /*TESTING ISOTROPIC FILTERING*/
    /*cout << "Testing isotropic transformation..." << endl;
    image = imread("../fingerprints/test_limpt.png",0);
    apply_iso(image, pressure_center);
    imwrite("../test_iso.png", convert_to_int(image));
    cout << " Done." << endl;*/

    cout << endl << "All tests have passed successfully, well done !" << endl;
}
