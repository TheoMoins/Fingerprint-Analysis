#include "elliptical_modelling.h"
#include "main_1.h"
#include "starter_4.h"

using namespace cv;
/**
  @file elliptical_modelling.cpp
  @brief Body for the functions dealing with anisotropy (Main course 1)
  @author Théo L.
*/

float INTENSITY_FLOOR = 0.065;
float INTENSITY_STEP = 0.00028;


int dilation_elem = 1;
int dilation_size = 1;
int const max_elem = 2;
int const max_kernel_size = 21;


void dilation( int, void*, Mat &src, Mat &dst){
  int dilation_type;
  if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
  else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
  else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

  Mat element = getStructuringElement( dilation_type,
                                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                       Point( dilation_size, dilation_size ) );

  /// Apply the dilation operation
  dilate( src, dst, element );
}


Point2i parameters_computation(Mat &image, Point2i pressure_center) {
    Point2i boundaries = fingerprint_boundaries(image);
    Point2i parameters;
    parameters.x = (pressure_center.x - boundaries.x)*1/5;
    parameters.y = (pressure_center.y - boundaries.y)*2/7;
    return(parameters);
}


bool test_ellipse(Point2f parameters, Point2i const pressure_center, Point2i coordinates) {
    float res = pow((coordinates.x - pressure_center.x)/parameters.x, 2); // à refaire avec la fonction distance
    res += pow((coordinates.y - pressure_center.y)/parameters.y, 2);
    res = sqrt(res);
    return(res>=1);
}


Mat ellipse(Point2i parameters, Point2i const pressure_center, Point2i dimensions) {
    int nRows = dimensions.x;
    int nCols = dimensions.y;
    Mat res;
    res.create(nRows, nCols, CV_32F);
    for (uint j = 0; j < nCols; j++) {
      for (uint i = 0; i < nRows; i++) {
        res.at<float>(i, j) = test_ellipse(parameters, pressure_center, Point2i(i,j));
      }
    }
    return(res);
}


void per_layer_filtering(Mat &image, Mat &protected_zone, float coef) {
    int nRows = image.rows;
    int nCols = image.cols;
    for (uint j = 0; j < nCols; j++) {
      for (uint i = 0; i < nRows; i++) {
        if (protected_zone.at<float>(i,j) == 1.) {
            Point2i point(j,i);
            if (image.at<float>(point) == 0.) {
              image.at<float>(point) += INTENSITY_FLOOR;
            } else {
              change_intensity(image, point, coef);
            }
        }
      }
    }
}


int number_of_iterations(Mat &image, Point2i pressure_center) {
    Point2i boundaries = fingerprint_boundaries(image);
    Point2i parameters = parameters_computation(image, pressure_center);
    int X = (pressure_center.x - boundaries.x) - parameters.x;
    int Y = (pressure_center.y - boundaries.y) - parameters.y;
    return (max(X, Y));
}


void anisotropic_filtering(Mat &image, Point2i const pressure_center) {
    int nRows = image.rows;
    int nCols = image.cols;

    Point2f parameters = parameters_computation(image, pressure_center);
    Mat protected_zone = ellipse(parameters, pressure_center, Point2i(nRows, nCols));

    int max_iteration = number_of_iterations(image, pressure_center);

    Mat dst;
    dilation(0, 0, image, dst);
    selected_dilation_Protection(dst, image, pressure_center);
    image = dst;

    float coef = 1.00;

    for (uint k = 0; k < max_iteration; k++) {
        per_layer_filtering(image, protected_zone, coef + k*INTENSITY_STEP);
        parameters.x++; parameters.y++;
        protected_zone = ellipse(parameters, pressure_center, Point2i(nRows, nCols));
    }

}


Point2i ellipse_erosion_parameters(Mat &image, Point2i pressure_center) {
    Point2i boundaries = fingerprint_boundaries(image);
    Point2i parameters;
    parameters.x = (pressure_center.x - boundaries.x)*17/25;
    parameters.y = (pressure_center.y - boundaries.y)*25/35;
    return(parameters);
}


void selected_dilation_Protection(Mat &src, Mat &original, Point2i pressure_center) {
    int nRows = src.rows;
    int nCols = src.cols;
    Point2i parameters = ellipse_erosion_parameters(original, pressure_center);
    Mat zone = ellipse(parameters, pressure_center, Point2i(nRows, nCols));
    for (uint j = 0; j < nCols; j++) {
      for (uint i = 0; i < nRows; i++) {
        if (zone.at<float>(i,j) == 0.) {
            Point2i point(j,i);
            src.at<float>(point) = original.at<float>(point);
        }
      }
    }
}
