#include <opencv2/opencv.hpp>

#include "starter_4.h"
#include "starter_1.h"
#include <vector>

using namespace cv;
using std::cout;
using std::endl;

/**
  This is a Doxygen documentation.
  @file starter_4.cpp
  @brief Body for the functions of the Starter 4
  @author Théo L.
*/

void print_vector(vector<float> vect) {
    for (uint i = 0; i < vect.size(); i++) {
        cout << vect[i] << endl;
    }
}

std::vector<int> levels_computation(Mat &image) {

    std::vector<int> levels(256, 0);
    int intensity;
    for (uint i = 0; i < image.cols; i++) {
      for (uint j = 0; j < image.rows; j++) {
        intensity = image.at<uchar>(j, i);
        levels[intensity] += 1;
      }
    }

    return(levels);
}

std::vector<float> normalized_levels(Mat &image) {
    int nb_pixels = image.rows * image.cols;
    std::vector<int> levels = levels_computation(image);
    //creation of a new vector to avoid type conflicts between int and floats
    std::vector<float> levels_normalized(256, 0);
    for (uint i = 0; i < levels.size(); i++) {
        levels_normalized[i] = (float) levels[i]/nb_pixels;
    }
    return levels_normalized;
}

float mean_level(vector<float> levels, int k) {
    float mean = 0;
    for (uint i = 0; i <= k; i++) {
        mean += i * levels[i];
    }
    return mean;
}

float cumulative_moment_0(vector<float> levels, int k) {
   float omega = 0;
   for (uint i = 0; i <= k; i++) {
       omega += levels[i];
   }
   return omega;
}

int index_max(vector<float> vect) {
    int idx = 0;
    for (uint k = 1; k < vect.size(); k++) {
        if (vect[idx] < vect[k]) {
          idx = k;
        }
    }
    return idx;
}

int optimal_threshold(Mat &image) {
    vector<float> levels = normalized_levels(image);
    vector<float> sigmas(256, 0);
    float mu_T = mean_level(levels, sigmas.size());
    for (uint k = 0; k < sigmas.size(); k++) {
        float mu = mean_level(levels, k);
        float omega = cumulative_moment_0(levels, k);
        sigmas[k] = (mu_T*omega - mu)*(mu_T*omega - mu)/(omega*(1-omega));
    }
    return index_max(sigmas);
}

void binarization(Mat &image, Mat &bin_image) {

  int nRows = image.rows;
  int nCols = image.cols;

  float threshold = (float) optimal_threshold(image)/256.;
  cout << threshold << endl;

  for (uint i = 0; i < nCols; i++) {
    for (uint j = 0; j < nRows; j++) {
      bin_image.at<float>(j, i) = (image.at<float>(j, i) > threshold);
    }
  }
}
