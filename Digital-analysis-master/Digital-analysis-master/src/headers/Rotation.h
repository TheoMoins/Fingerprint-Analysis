#ifndef ROTATION_T
#define ROTATION_T

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#define PI 3.14159265
using namespace cv;
/**
  @file Rotation.h
  @brief Header for the Rotation class and associated functions
  @author Romain C. & William D.
*/


/**
  @enum rotation_type
  @brief Enum type that represents the different methods
  we can use to apply a rotation to an image
*/
enum rotation_type{ CLASSIC, /*!< Rotation from source image.$ */
                    BILINEAR, /*!< Rotation from source with bilinear interpolation.$ */
                    BICUBIC, /*!< Rotation from source with bicubic interpolation.$ */
                    WEIGHTED,/*!< Rotation from source with weighted interpolation.$ */
                    TODEST, /*!< Rotation giving the rotated image.$ */
                    TODESTMOY,/*!< Rotation giving the roatated image where white holes have the mean intensity of its neighbour.$ */
                    TODESTNEIGHBOUR,/*!< Rotation giving the roatated image where white holes have the  intensity of its right neighbour.$ */
                    ELASTICITY /*!< Rotation only applied to the center of the image : simulating skin elasticity.$ */
                  };

/**
* @class Rotation
* @brief Class representing parametrized rotations of an image.
* @param method The method that will be applied to perform the rotation (rotation_type)
* @param angle The angle of the rotation (float)
*
* The Rotation class has two private attributes that define a rotation : angle and type.
*
*/

class Rotation{
private:
  rotation_type method; /*!< Method to apply the rotation */
  float angle;          /*!< Angle of the rotation */

  /**
    @fn void point_rotation(Point2f pt, Mat &img)
    @brief Sets the passed by reference point to its coordinates in the rotated image.
    @param pt Point of the original image that will have its coordinates changed
    @param &img Reference to the original image
  */
  void point_rotation(Point2f &pt, Mat &img);

  /**
    @fn int horizontal_rotated_size(const Mat &img)
    @brief Computes the horizontal size of the rotated image.
    @param &img Original image
    @return An integer representing the horizontal size of the rotated image
  */
  int horizontal_rotated_size(const Mat &img);

  /**
    @fn int vertical_rotated_size(const Mat &img)
    @brief Computes the vertical size of the rotated image.
    @param &img Original image
    @return An integer representing the vertical size of the rotated image
  */
  int vertical_rotated_size(const Mat &img);

  Mat apply_source(Mat &img);


  Mat apply_dest(Mat &img);

  Mat apply_elasticity(Mat &image);

  void decrease_rotation(Point2f &pt, Point2f &rot_center, Mat &img);


public:
  /**
    @fn Rotation(rotation_type p1, float p2)
    @brief Constructor of the Rotation class
    @param p1 Enum rotation_type
    @param p2 Floating point number representing the angle of the rotation
  */
  Rotation(rotation_type p1, float p2);

  /**
    @fn void set_angle(float new_angle)
    @brief Sets the angle of the Rotation object to a new value
    @param new_angle angle the Rotation will be set to.
  */
  void set_angle(float new_angle);

  /**
    @fn   void set_method(rotation_type new_method)
    @brief Sets the method of the Rotation object to a new value
    @param new_method Method the Rotation will be set to
  */
  void set_method(rotation_type new_method);

  /**
  @fn   Mat apply_source(Mat &img)
  @brief Applied the parametrized Rotation to an image.
  @param p1 &img Image the rotation will be applied to.
  @return Rotated image.
  */
  Mat apply(Mat &img);
};

/**
  @fn   float intensity_computation_classic(const Point2f &pt, const Mat &img)
  @brief Compute the rotation from source without interpolation.
  @param &pt Point on which we apply rotation.
  @param &img Image on which we apply the rotation.
  @return intensity at the point (x,y).
*/
float intensity_computation_classic(const Point2f &pt, const Mat &img);


/**
  @fn   float intensity_computation_bilinear(const Point2f &pt, const Mat &img)
  @brief Compute the rotation from source with bilinear interpolation.
  @param &pt Point on which we apply rotation.
  @param &img Image on which we apply the rotation.
  @return intensity at the point (x,y).
*/
float intensity_computation_bilinear(const Point2f &pt, const Mat &img);

/**
  @fn   float intensity_computation_bilinear(const Point2f &pt, const Mat &img)
  @brief Compute the rotation from source with bicubic interpolation.
  @param &pt Point on which we apply rotation.
  @param &img Image on which we apply the rotation.
  @return intensity at the point (x,y).
*/
float intensity_computation_bicubic(Point2f &pt, Mat &img);

/**
  @fn   float intensity_computation_bilinear(const Point2f &pt, const Mat &img)
  @brief Compute the rotation from source with weighted interpolation.
  @param &pt Point on which we apply rotation
  @param &img Image on which we apply the rotation.
  @return intensity at the point (x,y).
*/
float intensity_computation_weighted(const Point2f &pt, const Mat &img);

/**
  @fn   Mat coeff_bicubic(const Point2f &pt, const Mat &img)
  @brief Find the coefficient for the bicubic interpolation
  @param &pt Point on which we apply rotation
  @param &img Image on which we apply the rotation.
  @return The matrix with the bicubic coefficient.
*/
Mat coeff_bicubic(const Point2f &pt, const Mat &img);

/**
  @fn void get_intensities(const Mat &img, const Point2i &inf, const Point2i &sup, float &i1, float &i2, float &i3, float &i4)
  @image html image_distance.svg
  @brief Puts the intensities of the 4 points surrounding pt in the passed by reference floats
  @param &img Image from whih we'll get the intensities
  @param &inf Q11
  @param &sup Q22
  @param &i1 Horizontal distance between pt and inf
  @param &i2 Vertical distance between pt and inf
  @param &i3 Vertical distance between pt and inf
  @param &i4 Vertical distance between pt and inf
  @return Rotated image.
*/
void get_intensities(const Mat &img, const Point2i &inf, const Point2i &sup, float &i1, float &i2, float &i3, float &i4);

/**
  @fn void floor_ceil_dx_dy(const Point2f &pt, Point2f &inf, Point2f &sup, float &dx, float &dy)
  @brief Computes various important values to apply a Rotation. Pt is the only
  actual parameter, the other parameters are passsed by reference parameters that
  are to be modified by this function
  @param &pt Point that is concerned by the computations
  @param &inf Point that has the same coordinates as pt, but floored
  @param &sup Point that has the same coordinates as pt, but ceiled
  @param &dx Horizontal distance between pt and inf
  @param &dy Vertical distance between pt and inf
  @return Rotated image.
*/
void floor_ceil_dx_dy(const Point2f &pt, Point2f &inf, Point2f &sup, float &dx, float &dy);

/**
  @fn float dist_to_O(Point2f pt)
  @brief Computes the distance of a point to the origin
*/

float dist_to_O(const Point2f pt);


/**
  @fn   float derive_x(const Point2f pt, Mat image)
  @brief Compute the numerical derivation wrt x.
  @param &pt Point where we apply the derivation.
  @param &img Image on which we apply the rotation.
  @return Derived intensity at the point (x,y).
*/

float derive_x(const Point2f pt, Mat image);

/**
  @fn   float derive_y(const Point2f pt, Mat image)
  @brief Compute the numerical derivation wrt y.
  @param &pt Point where we apply the derivation.
  @param &img Image on which we apply the rotation.
  @return Derived intensity at the point (x,y).
*/
float derive_y(const Point2f pt, Mat image);

/**
  @fn   float derive_xy(const Point2f pt, Mat image)
  @brief Compute the numerical derivation wrt x and y.
  @param &pt Point where we apply the derivation.
  @param &img Image on which we apply the rotation.
  @return Derived intensity at the point (x,y).
*/
float derive_xy(const Point2f pt, Mat image);



#endif // ROTATION_T
