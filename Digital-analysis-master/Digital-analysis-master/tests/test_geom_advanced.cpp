#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "starter_1.h"
#include "main_1.h"
#include "elliptical_modelling.h"
using namespace cv;
using std::cout;
using std::endl;

int main(int argc, char** argv ){
  if ( argc < 2 )
  {
      printf("usage: Test_1 <Fingerprint_Path>\n");
      return -1;
  }
  Mat fingerprint;
  fingerprint = imread(argv[1], 1);
  if (!fingerprint.data)
  {
      printf("No image data \n");
      return -1;
  }
  cout << "This test program will save all its work to the img/Geom_tests directory" << endl;
  cout << "Image succesfully imported" << endl;

  /* TESTING THE ELLIPTICAL FUNCTION */
  cout << "Testing the ellipse creation...";
  Mat ellipse_test;
  ellipse_test.create(256, 288, CV_32F);
  Point2i param(90, 60);
  Point2i press(144, 128);
  ellipse_test = ellipse(param, press, Point2i(288, 256));
  convert_to_int(ellipse_test, ellipse_test);
  imwrite("img/Geom_tests/test_limpt.png", ellipse_test);
  cout << " Done. (image saved at img/test_limpt.png)" << endl;

  /*TESTING THE XLIM YLIM COMPUTATION */
  cout << "Testing the extreme points computation...";
  Mat image = imread("img/test_limpt.png",0);
  convert_to_float(image, image);
  //assert(fingerprint_boundaries(image) == Point2i(233,69));
  cout << " Done" << endl;

  /* TESTING POINTS AIGAIN */
  cout << "Creating image for highest intensity test...";
  image = imread("img/black.png", 0);
  Point2i test_pt(image.cols/2, image.rows/2);
  image.at<uchar>(test_pt) = 255;
  imwrite("img/Geom_tests/black_test.png",image);
  cout << " Done" << endl;

  /*TESTING THE ROI FINDING*/
  cout << "Testing highest intensity zone research...";
  image = imread("img/black_test.png", 0);
  Mat gblur;
  image.copyTo(gblur);
  GaussianBlur(image, gblur, Size(17, 17), 0, 0);
  double minVal = 0;
  double maxVal = 0;
  Point minLoc, maxLoc;
  minMaxLoc(gblur, &minVal, &maxVal, &minLoc, &maxLoc);
  assert(pressure_center_computation(image) == minLoc);
  Rect roi;
  roi = Rect(maxLoc.x-25, maxLoc.y-25, 50, 50);
  image=image(roi);
  imwrite("../output/roi.png",image);
  cout << " Done." << endl;

  /*TESTING ON FINGERPRINT*/
  cout << "Testing with given fingerprint...";
  fingerprint.copyTo(image);
  cvtColor(fingerprint, image, COLOR_BGR2GRAY);
  GaussianBlur(image, image, Size(11,11), 0, 0);
  imwrite("../output/blur.png", image);
  minMaxLoc(image, &minVal, &maxVal, &minLoc, &maxLoc);
  circle(image, minLoc, 15, Scalar(0,0,255), 5);
  imwrite("../output/blur_circle.png", image);
  circle(fingerprint, minLoc, 15, Scalar(0,0,255), 5);
  imwrite("../output/img_roi.png", fingerprint);
  cout << " Done." << endl;

}
