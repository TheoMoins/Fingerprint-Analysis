#include <opencv2/opencv.hpp>
#include <stdio.h>
using namespace cv;
using std::cout;
using std::endl;

/**
  This is a Doxygen documentation.
  @file starter_1.cpp
  @brief Body for the functions of the Starter 1
  @author Romain C. & Théo M. & Théo L. & William D.
*/

void convert_to_float(Mat &src, Mat & dst){
  src.convertTo(dst, CV_32F, 1.0/255.0);
}


void convert_to_int(Mat &src, Mat &dst) {
  src.convertTo(dst, CV_8UC1, 255);
}



void draw_uniform_rectangle (Mat image, Rect r, float color){
  image = image(r);
  image = Scalar(color);
}



Mat symetry_y(Mat &image) {
    /* returns the symetry along the y axis */
    int nRows = image.rows;
    int nCols = image.cols;
    Mat image_sym;
    //creation of a Mat with the same size as 'image'
    image_sym.create(nRows, nCols, CV_32F);
    for (uint i = 0; i < nCols; i++) {
      for (uint j = 0; j < nRows; j++) {
        //gets the intensity value of image
        Scalar intensity = image.at<float>(j, i);

        //fills 'image_sym' according to the symetry
        image_sym.at<float>(j, nCols - i) = intensity[0];
      }
    }
    return image_sym;
  }

Mat symetry_x(Mat &image) {
  /* returns the symmetry along the y axis */
  int nRows = image.rows;
  int nCols = image.cols;
  Mat image_sym;
  //creation of a Mat with the same size as 'image'
  image_sym.create(nRows, nCols, CV_32F);
  for (uint i = 0; i < nCols; i++) {
    for (uint j = 0; j < nRows; j++) {
      image_sym.at<float>(nRows-j-1, i) = image.at<float>(j, i);
    }
  }
  return(image_sym);
}

Mat symetry_diag(Mat &image) {
    int nRows = image.rows;
    int nCols = image.cols;
    Mat image_sym;
    //creation of a Mat with the same size as 'image'
    image_sym.create(nCols, nRows, CV_32F);
    for (uint i = 0; i < nCols; i++) {
      for (uint j = 0; j < nRows; j++) {
        image_sym.at<float>(i, j) = image.at<float>(j, i);
      }
    }
    return(image_sym);
}
