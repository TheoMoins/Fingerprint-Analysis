#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "starter_1.h"
#include "main_1.h"
#include "starter_4.h"
#include "elliptical_modelling.h"

using namespace cv;
/**
  @file main_1.cpp
  @brief Body for the functions of the Main course 1
  @author Théo L. & William D.
*/

float distance_computation(const Point2i pressure_center, Point2i point) {
    return(sqrt(pow(pressure_center.x - point.x, 2) + pow(pressure_center.y - point.y, 2)));
}


float coefficient_computation(bool clean_to_weak, const Point2i pressure_center, Point2i point){
  float distance = distance_computation(pressure_center, point);
  if (clean_to_weak){
    return exp(distance/100);
  } else {
    return exp(-distance/500);
  }
}


void change_intensity (Mat &image, Point2i point, float coef){
  image.at<float>(point) = coef*image.at<float>(point);
}


bool white_thresholding(Mat &image, Point2i point, const float threshold){
  if (image.at<float>(point) > threshold){
    image.at<float>(point) = 1.0;
    return true;
  }
  return false;
}


void clean_to_weak_iso(Mat &image, const Point2i pressure_center){
  for (unsigned int x = 0; x < image.rows; x++){
    for (unsigned int y = 0; y < image.cols; y++){
      Point2i pt = Point(y,x);
      float coef = coefficient_computation(true, pressure_center, pt);
      change_intensity(image, pt, coef);
    }
  }
}


void weak_to_clean_iso(Mat &image, const Point2i pressure_center){
  for (unsigned int x = 0; x < image.rows; x++){
    for (unsigned int y = 0; y < image.cols; y++){
      Point2i pt = Point(y,x);
      float threshold = optimal_threshold(image);
      if  (!white_thresholding(image, pt, threshold)){
        float coef = coefficient_computation(false, pressure_center, pt);
        change_intensity(image, pt, coef);
      }
    }
  }
}


int fingerprint_boundaries_x(Mat &image){
  for (int i = 0; i < image.cols; i++){
    for (int j = 0; j < image.rows; j++){
      if (image.at<float>(j,i) < 0.2){
         return i;
      }
    }
  }
  cout << "No x found..." << endl;
  return(-1);
}

int fingerprint_boundaries_y(Mat &image){
  for (int j = 0; j < image.rows; j++){
    for (int i = 0; i < image.cols; i++){
      if (image.at<float>(j,i) < 0.2){
         return j;
      }
    }
  }
  cout << "No y found..." << endl;
  return(-1);
}

Point2i fingerprint_boundaries(Mat &image) {
  int x = fingerprint_boundaries_x(image);
  int y = fingerprint_boundaries_y(image);
  Point2i res(y, x);
  return res;
}


Point2i pressure_center_computation(Mat &image){
    Mat gblur;
    image.copyTo(gblur);
    GaussianBlur(image, gblur, Size(17, 17), 0, 0);
    double minVal = 0;
    double maxVal = 0;
    Point minLoc, maxLoc;
    minMaxLoc(gblur, &minVal, &maxVal, &minLoc, &maxLoc);
    Point2i pressure_center(minLoc.y, minLoc.x);
    return pressure_center;
}
