#ifndef STARTER_4_H
#define STARTER_4_H

#include <opencv2/opencv.hpp>

/**
  This is a Doxygen documentation.
  @file starter_4.h
  @brief Header for the functions of the Starter 4
  @author Théo L.
*/

using namespace cv;
using std::cout;
using std::endl;



/**
  @fn print_vector(vector<float> vect)
  @brief Prints all the values of a vector of floating point numbers.
  @param vect the vector to be printed
  @author Théo L.
*/
void print_vector(vector<float> vect);

/**
  @fn std::vector<int> levels_computation(Mat &image)
  @brief Computes the histogram of grey levels in an image
  @param &image The image from which the histogram will be computed
  @return A vector of int. Each value of the vector represents the number of pixels of the image having this intensity.
  @author Théo L.
*/
std::vector<int> levels_computation(Mat &image);

/**
  @fn std::vector<float> normalized_levels(Mat &image)
  @brief Computes a normalized histogram of grey levels w.r.t the number of
      pixels in an image
  @param image The image from which the histrogram has been computed
  @return A vector of floats of [0;1]
  @author Théo L.
*/
std::vector<float> normalized_levels(Mat &image);

/**
  @fn float mean_level(vector<float> levels, int k)
  @brief Computes the mean of normalized levels at floor k
  @param levels The normalized histogram of grey levels
  @param k The floor
  @return A float containing the mean level of intensity of the image
  @author Théo L.
*/
float mean_level(vector<float> levels, int k);

/**
  @fn float cumulative_moment_0(vector<float> levels, int k)
  @brief Computes the cumulative moment at order 0 of normalized levels at
      floor k
  @param levels The normalized histogram of grey levels
  @param k The floor
  @return A float containing the cumulative moment at order 0
  @author: Théo L.
*/
float cumulative_moment_0(vector<float> levels, int k);

/**
  @fn int index_max(vector<float> vect)
  @brief Returns the index of the max value in a float vector
  @param vector The input vector
  @return An int containing the index of the max value
  @author Théo L.
*/
int index_max(vector<float> vect);

/**
  @fn int optimal_threshold(Mat &image)
  @brief Computes an optimal threshold for image
      binarization using the previous methods
  @param &image The image for which the threshold has to be computed
  @return An int containing the threshold
  @author Théo L.
*/
int optimal_threshold(Mat &image);

/**
  @fn void binarization(Mat &image, Mat &bin_image)
  @brief Binarizes an image according to a threshold
  @param &image The image that will be processed
  @param &bin_image The location where the result will be stored
  @author Théo L.
*/
void binarization(Mat &image, Mat &bin_image);

#endif //STARTER_4_H
