#ifndef ELLIPTICAL_MODELLING_H
#define ELLIPTICAL_MODELLING_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
/**
  @file elliptical_modelling.h
  @brief Header for the functions dealing with anisotropy (Main course 1)
  @author Théo L.
*/

/**
    @fn Point2i parameters_computation(Mat &image, Point2i pressure_center)
    @brief Computes the semi-major and semi-minor axes of the future ellipse
    @param &image The image on which will be applied the ellipse after
    @param pressure_center The coordinates of the pressure pressure_center
    @return A point that contains semi-major and semi-minor axes length
    @author Théo L.
 */
Point2i parameters_computation(Mat &image, Point2i pressure_center);

/**
   @fn bool test_ellipse(Point2f const parameters, Point2i const
       pressure_center, Point2i coordinates)
   @brief Tests if a given point is in the parametrized ellipse or not
   @param parameters semi-major and semi-minor axes length
   @param pressure_center coordinates of the pressure center
   @param pt the point that is tested
   @return A boolean representing the belonging of the point to the ellipse
   @author Théo L.
 */
bool test_ellipse(Point2f const parameters, Point2i const pressure_center,
    Point2i coordinates);

/**
    @fn Mat ellipse(Point2i const parameters, Point2i const pressure_center,
        Point2i dimensions)
    @brief Creats a binary matrix representing the parametrized ellipse
    @param parameters Semi-major and semi-minor axes
    @param pressure_center Coordinates of the pressure center
    @param dimensions Dimensions of the image
    @return A binary Mat object representing an ellipse
    @author Théo L.
*/
Mat ellipse(Point2i const parameters, Point2i const pressure_center,
    Point2i dimensions);

/**
    @fn void per_layer_filtering(Mat &image, Mat &protected_zone, float coef)
    @brief Applies the coefficient transform outside the ellipse
    @param &image The image on which the filter will be applied
    @param pressure_center The coordinates of the pressure pressure_center
    @param coef The coefficient that has to be applied on the image intensity
    @return Nothing the image is directly modified
    @author Théo L.
 */
void per_layer_filtering(Mat &image, Mat &protected_zone, float coef);

/**
    @fn int number_of_iterations(Mat &image, Point2i pressure_center)
    @brief Computes the approximate number of iterations that will be recquired
        to apply correctly the anisotropic filtering process
    @param &image The image on which the filter will be applied
    @param pressure_center The coordinates of the pressure pressure_center
    @return An int containing the number of iterations
    @author Théo L.
 */
int number_of_iterations(Mat &image, Point2i pressure_center);

/**
    @fn void anisotropic_filtering(Mat &image, Point2i const pressure_center)
    @brief Computes at each step the new ellipse and applies the filter outside
    @param &image The image on which the filter will be applied
    @param pressure_center The coordinates of the pressure pressure_center
    @return Nothing : the image is directly modified
    @author Théo L.
 */
void anisotropic_filtering(Mat &image, Point2i const pressure_center);

/**
    @fn Point2i ellipse_erosion_parameters(Mat &image, Point2i pressure_center)
    @brief Computes the parameters of the ellipse that will select the eroded
        zone
    @param &image The image on which the filter will be applied
    @param pressure_center The coordinates of the pressure pressure_center
    @return A point containing the axes of the ellipse
    @author Théo L.
 */
Point2i ellipse_erosion_parameters(Mat &image, Point2i pressure_center);

/**
    @fn void dilation(int, void*, Mat &src, Mat &dst)
    @brief Applies a morphological dilation to an image
    @param &src The image on which the filter will be applied
    @param &dst The location where the image will be stored
    @author Théo L.
*/
void dilation(int, void*, Mat &src, Mat &dst);

/**
    @fn void selected_dilation_Protection(Mat &src, Mat &original, Point2i
        pressure_center)
    @brief Selects a zone that will be protected from dilation operation, and
        paste it on the dilated image
    @param &src The image on which the protection will be applied
    @param &original The original image
    @return Nothing the image is directly modified
    @author Théo L.
 */
void selected_dilation_Protection(Mat &src, Mat &original, Point2i pressure_center);


#endif //ELLIPTICAL_MODELLING_H
