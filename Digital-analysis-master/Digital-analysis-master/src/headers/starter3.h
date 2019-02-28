/**
  This is a Doxygenb documentation.
  @file starter3.h
  @brief Header for the functions of the Starter 3
  @author Romain C. & Théo M. & Théo L. & William D.
*/
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <time.h>
#include <vector>

using namespace cv;

#ifndef STARTER3
#define STARTER3

/**
  @fn Mat produit_coefbycoef(Mat A, Mat B)
  @brief Give the by-coefficient product of the two matrices
  @param A The first matrix
  @param B The second matrix, that has the same dimension as A
  @author Théo M. & Romain
*/

float produit_coefbycoef(Mat A, Mat B);
/**
  @fn Mat Convol(Mat X, Mat H)
  @brief Give X**H, centered on the downright coefficient of the matrix H
  @param X The matrix we want to convol
  @param H The kernel that can be of any dimension
  @author Théo M. & Romain
*/
Mat Convol(Mat X, Mat H);

/**
  @fn Mat Convol_Shifted(Mat X, Mat H)
  @brief Gives X**H, centered on the centered coefficient of the matrix H
  @param X The matrix we want to convol
  @param H The kernel, that has to be of square dimension
  @return The matrix of convolution
  @author Théo M. & Romain
*/
void Convol_Shifted(Mat &X, Mat &dst, Mat &H);

/**
  @fn Mat transfo_fourier( Mat image)
  @brief Gives a complex matrix which is the result of the fourier transform of initial matrix
  @param &X The matrix X we want to convol
  @param &dst The matrix that store the result
  @param &H The kernel of square dimension
  @author Théo M. & Romain
*/
Mat transfo_fourier( Mat image);

/**
@fn Mat img_magnitude(Mat img_complexe)
@brief Gives the module of a complex matrix
@param img_complexe A complex matrix
@return A real matrix as a representation of magnitude
@author Théo M. & Romain
*/
Mat img_magnitude(Mat img_complexe);

/**
@fn Mat inv_transfo_fourier(Mat image, int nbCols, int nbRows)
@brief Gives the inverse fourier transform of a matrix, redemensionned on size nbCols*nbRows
@param image A complex matrix
@param nbCols The number of colomns
@param &nbRows The number of rows
@return A real matrix
@author Théo M. & Romain
*/
Mat inv_transfo_fourier(Mat image, int nbCols, int nbRows);

/**
@fn void periodic_shift(Mat &src, Mat &dst, int p)
@brief For a matrix M of size m*n, give the matrix M' where M'[i,j] = M[(i+p)%m, (j+p)%n]
@param &src The source we shift
@param &dst The destination of the result
@param p An integer that correspond of how many we shift
@return A real matrix
@author William
*/

void periodic_shift(Mat &src, Mat &dst, int p);

/**
@fn Mat convolution_fft(Mat x, Mat h)
@brief Gives the convolution of the two matrices thanks to FFT
@param &src The source we convol
@param &dst The destination of the result
@param &h The kernel of square dimension
@author Théo M. & Romain
*/

void convolution_fft(Mat &x, Mat &dst, Mat &h);

/**
@fn Mat Normalized_kernel(int NbCols, int NbRows)
@brief Gives a normalized kernel of size NbCols*NbRows. Each coefficient is equal to 1/(NbCols*NbRows)
@param NbCols The number of columns
@param NbRows The number of rows
@return A real matrix
@author Théo M. & Romain
*/

Mat Normalized_kernel(int NbCols, int NbRows);

/**
@fn float gauss2D(float x, float y, float esp_x, float esp_y, float sigma_x, float sigma_y)
@brief Gives the value of the 2D-Gaussian at the point (x,y)
@param The two coordinates where we compute the value of the gaussian, and four float for the parameters of the gaussian
@return The float that correspond to the output of the function
@author Théo M. & Romain
*/

float gauss2D(float x, float y, float esp_x, float esp_y, float sigma_x, float sigma_y);

/**
@fn Gaussian_kernel(int size, float sigma_x, float sigma_y, float energy)
@brief Gives a Matrix filled with coefficient computed with a 2D Gaussian function
@param An odd integer for the size of the square matrix, two float for the parameters of the gaussian, and a float for the norm of the matrix
@return The resulting matrix
@author Théo M. & Romain
*/

Mat Gaussian_kernel(int size, float sigma_x, float sigma_y, float energy);

/**
@fn Mat Convol_Shifted_xy(Mat X, uint size_h)
@brief Gives the convolution of the image with a gaussian kernel where sigma_x and sigma_y depends on coordinates
@param X The input matrix
@param size_h The size of the varying kernel
@return The resulting matrix
@author Théo M.
*/

Mat Convol_Shifted_xy(Mat X, uint size_h);

/**
@fn Mat Convol_Shifted_xy(Mat X, uint size_h)
@brief Gives the convolution of the image with a gaussian kernel where sigma_x, sigma_y, and the norm depends on coordinates
@param X The input matrix
@param size_h The size of the varying kernel
@return The resulting matrix
@author Théo M.
*/
Mat Convol_Shifted_xy_energy(Mat X, uint size_h);

#endif
