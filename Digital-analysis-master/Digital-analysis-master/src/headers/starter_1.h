/*
header file associated to 'starter_1.cpp'
contains the functions related to the starter 1
*/

/**
  This is a Doxygen documentation.
  @file starter_1.h
  @brief Header for the functions of the Starter 1
  @author Romain C. & Théo M. & Théo L. & William D.
*/
#ifndef STARTER_1
#define STARTER_1

#include <opencv2/opencv.hpp>
#include <cstdio>

using namespace cv;
using std::cout;
using std::endl;

/**
  @fn Mat convert_to_float(Mat &src, Mat &dest)
  @brief Casts the data of a source Mat from ints to floats in a dest Mat.
  @param &src Image that you want to switch to floating point values. Has to be between 0 and 255
  @param &dest Image where the data is casted to floating point values between 0.0 and 1.0
  @author Théo L.
*/
void convert_to_float(Mat &src, Mat &dest);


/**
  @fn Mat convert_to_int(Mat &src, Mat &dest)
  @brief Casts the data of a source Mat from floats to ints in a dest Mat.
  @param &src Image that you want to cast to integer values. Has to be between 0.0 and 1.0
  @param &dest Image where the data is casted to integer values between 0 and 255
  @author Théo L.
*/
void convert_to_int(Mat &src, Mat &dest);


/**
  @fn int draw_uniform_rectangle (Mat image, Rect r, float color)
  @brief Draws a rectangle of the given size and color on the image.
  @param Image Image on which you want to insert a rectangle. Data has to be floating point values.
  @param r Region of the image that will be colored. Has to be included in the image
  @param color Floating point number in [0.0;1.0] corresponding to the intensity of the rectangle
  @author William D.
*/
void draw_uniform_rectangle (Mat image, Rect r, float color);

/**
@fn symetry_x(Mat &image)
@brief Computes the x-axis symetry of the image
@param &image Image to be modified
@return Mat Image transformed according to the x-axis symetry
@author Romain C. & Théo M.
*/

Mat symetry_x(Mat &image);
/**
  @fn symetry_y(Mat &image)
  @brief Computes the y-axis symetry of the image
  @param &image Image to be modified
  @return Mat Image transformed according to the y-axis symetry
  @author Romain C. & Théo M.
*/
Mat symetry_y(Mat &image);

/**
  @fn symetry_diag(Mat &image)
  @brief Performs a diagonal symmetry on the image
  @param &image Image to be modified
  @return Mat Image transformed according to the diagonal symmetry
  @author Romain C. & Théo M.
*/
Mat symetry_diag(Mat &image);

#endif
