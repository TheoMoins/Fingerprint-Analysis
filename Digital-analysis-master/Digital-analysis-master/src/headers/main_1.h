/*
GLOBAL DESCRIPTION: header file associated to main_1.cpp
    - contains the functions related to the 'Main course 1'
    - the goal is to simulate the blur you get due to finger pressure variations
      variations
*/

#ifndef MAIN_1_H
#define MAIN_1_H


#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include"starter_1.h"

using namespace cv;

/**
  @file main_1.h
  @brief Header for the functions of the Main course 1
  @author Théo L. & William D.
*/

/**
################################################################################
                              basic operations
################################################################################
  */

/**
  @fn float distance_computation(const Point2i pressure_center, Point2i point,
      bool anisotropic)
  @brief Computes the distance between a point and the pressure center.
  @param pressure_center coordinates of the pressure pressure_center
  @param point coordinates of a point
  @param anisotropic true means anisotropic distance computation
  @return A float containing the distance
  @author Théo L.
*/
float distance_computation(const Point2i pressure_center, Point2i point);

/**
  @fn float coefficient_computation(bool clean_to_weak, const Point2i
      pressure_center, Point2i point)
  @brief Computes the coefficient c(x,y) such that g(x,y) = c(x,y)f(x,y)
  @param clean_to_weak boolean that indicates which coefficient whould be
   computed, depending on the transformation we are doing
   @param pressure_center the point of maximum pressure during the acquisition
  @param point the point (x,y) at which we compute the coefficient c(x,y)
  @return the floating point number c(x,y)
  @author William D.
*/
float coefficient_computation(bool clean_to_weak, const Point2i pressure_center,
    Point2i point);

/**
  @fn void change_intensity (Mat &image, Point2i point, float coef)
  @brief Changes the intensity of the image at the point (x,y)
  @param &image image that will be modified
  @param point the point (x,y) at which we change the intensity
  @param coef floating point number that multiplies the intensity at the point
  @author William D.
*/
void change_intensity (Mat &image, Point2i point, float coef);


/**
################################################################################
                            isotropic filtering
################################################################################
  */

/**
  @fn bool white_thresholding(Mat &image, Point2i pt, const float threshold)
  @brief Applies a thresholding to the intensity of the image at a given point.
  @param &image image that will be modified
  @param pt the point (x,y) at which we apply the thresholding
  @param threshold floating point number <1.0 such that if the intensity at
      the point (x,y) is greater than the threshold, it is set to 1.0.
  @return A boolean that indicates wether or not the threshold has been applied
  @author William D.
*/
bool white_thresholding(Mat &image, Point2i point, const float threshold);

/**
  @fn void clean_to_weak_iso(Mat &image, const Point2i pressure_center)
  @brief simulates the weakening of the pressure given a fingerprint.
  @param &image image that will be treated
  @param pressure_center the point of maximum pressure during the acquisition
  @author William D.
*/
void clean_to_weak_iso(Mat &image, const Point2i pressure_center);

/**  @param pressure_center the point of maximum pressure during the acquisition

  @fn void weak_to_clean_iso(Mat &image, const Point2i pressure_center)
  @brief Simulates a bigger pressure on a given fingerprint.
  @param &image image that will be treated
  @param pressure_center the point of maximum pressure during the acquisition
  @author William D.
*/
void weak_to_clean_iso(Mat &image, const Point2i pressure_center);


/**
################################################################################
                            anisotropic filtering
################################################################################
  */

/**
  @fn int fingerprint_boundaries_x(Mat &image)
  @brief Finds the first point along the x axis that belongs to the fingerprint
  @param &image Image on which we are looking for the boundary. Has to be a fingerprint
  @return An int containing the wanted coordinate
  @author Théo L.
*/
int fingerprint_boundaries_x(Mat &image);

/**
    @fn int fingerprint_boundaries_y(Mat &image)
    @brief Finds the first point along the y axis that belongs to the fingerprint
    @param &image Image on which we are looking for the boundary. Has to be a fingerprint
    @return An int containing the wanted coordinate
    @author Théo L.
*/
int fingerprint_boundaries_y(Mat &image);

/**
    @fn Point2i fingerprint_boundaries(Mat &image)
    @brief Finds the extreme points of a fingerprint.
    @param &image Image on which we are looking for the boundary. Has to be a fingerprint
    @return A point (y, x) representing the boundaries of the fingerprint.
    @author Théo L.
*/
Point2i fingerprint_boundaries(Mat &image);

/**
    @fn Point2i pressure_center_computation(Mat &image)
    @brief Estimates the point at which the pressure was maximum during the acquisition of a given fingerprint
    @param &image a fingerprint
    @return A point with the coordinates (y, x) fo the pressure center
    @author William D.
*/
Point2i pressure_center_computation(Mat &image);



#endif //MAIN_1_H
