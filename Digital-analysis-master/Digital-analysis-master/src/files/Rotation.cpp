#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include "Rotation.h"
#include "main_1.h"
#define PI 3.14159265
using namespace cv;
using std::cout;
using std::endl;

/**
  @file Rotation.cpp
  @brief Body for the Rotation class and associated functions
  @author Romain C. & William D.
*/

void Rotation::point_rotation(Point2f &pt, Mat &img){

  Point2f rot_center(img.rows/2, img.cols/2);
  float tmp = pt.x;
  switch(method){
    case TODEST:
    case TODESTMOY:
    case TODESTNEIGHBOUR:
      pt.x = cos(-PI*angle/180)*(pt.x-rot_center.y) - sin(-PI*angle/180)*(pt.y-rot_center.x)+rot_center.y;
      pt.y = sin(-PI*angle/180)*(tmp-rot_center.y) + cos(-PI*angle/180)*(pt.y-rot_center.x)+rot_center.x;
      pt.x = floor(pt.x+0.5);
      pt.y = floor(pt.y+0.5);
      break;
    default:
    pt.x = cos(PI*angle/180)*(pt.x-rot_center.y) - sin(PI*angle/180)*(pt.y-rot_center.x)+rot_center.y;
    pt.y = sin(PI*angle/180)*(tmp-rot_center.y) + cos(PI*angle/180)*(pt.y-rot_center.x)+rot_center.x;
  }
  if (method == CLASSIC){
    pt.x = floor(pt.x+0.5);
    pt.y = floor(pt.y+0.5);
  }
}

int Rotation::horizontal_rotated_size(const Mat &img){
  int h_size = sin(PI*angle/180.)*img.cols + img.rows*fabs(cos(PI*angle/180.));
  return (int) fabs(h_size);
}


int Rotation::vertical_rotated_size(const Mat &img){
  int v_size = sin(PI*angle/180.)*img.rows + img.cols*fabs(cos(PI*angle/180.));
  return (int) fabs(v_size);
}

Rotation::Rotation(rotation_type p1, float p2){
  method = p1;
  angle = p2;
}

Mat Rotation::apply(Mat &img){
  Mat Res;
  switch(method){
    case TODEST:
    case TODESTMOY:
    case TODESTNEIGHBOUR:
      Res = this -> apply_dest(img);
      break;
    case ELASTICITY:
      Res = this -> apply_elasticity(img);
      break;
    default:
      Res = this -> apply_source(img);
  }
  return Res;
}

Mat Rotation::apply_source(Mat &img){
  int dim_output_x = this -> horizontal_rotated_size(img);
  int dim_output_y = this -> vertical_rotated_size(img);
  Mat Res = Mat::ones(dim_output_x,dim_output_y, CV_32FC1);
  for(int i = 0; i < dim_output_x; i++ ){
    for(int j = 0 ; j < dim_output_y ; j++){
      Point2f pt(j,i);
      this -> point_rotation(pt, img);
      if( pt.x >= 0 && pt.y >= 0 && int(pt.x) < img.cols-1 && int(pt.y) < img.rows-1){
        float intensity;
        switch(method){
          case CLASSIC:
            intensity = intensity_computation_classic(pt, img);
            break;
          case BILINEAR:
            intensity = intensity_computation_bilinear(pt, img);
            break;
          case BICUBIC:
            intensity = intensity_computation_bicubic(pt, img);
            break;
          case WEIGHTED:
            intensity = intensity_computation_weighted(pt, img);
            break;
          default:
            std::cerr << "ERROR : The type of the rotation wasn't understood or try apply_dest function. Aborting" << endl;
            break;
        }
        Res.at<float>(i,j) = intensity;
      }
    }
  }
  Rect roi = Rect(0, 0, img.cols, img.rows);
  return Res(roi);
}

Mat Rotation::apply_dest(Mat &img){
  int dim_output_x = this -> horizontal_rotated_size(img);
  int dim_output_y = this -> vertical_rotated_size(img);
  Mat Res = Mat::ones(dim_output_x,dim_output_y, CV_32FC1);
  for(int i = 0; i < img.cols; i++ ){
    for(int j = 0 ; j < img.rows ; j++){
      Point2f pt(i,j);
      float intensity = img.at<float>(pt);
      this -> point_rotation(pt, img);
      if( pt.x >= 0 && pt.y >= 0 && pt.y < dim_output_x&& pt.x < dim_output_y){
        Res.at<float>(pt) = intensity;
      }
    }
  }
  for(int i = 0; i < img.cols; i++ ){
    for(int j = 0 ; j < img.rows ; j++){
      Point2f pt(i,j);
      Mat big_image;
      float intensity = Res.at<float>(pt);
      switch(method){
        case TODEST:
          break;
        case TODESTNEIGHBOUR:
          copyMakeBorder(Res, big_image, 1, 1, 1, 1, BORDER_CONSTANT, Scalar::all(1));
          if (intensity == 1){
            intensity = big_image.at<float>(j+2,i+1);
           }
           break;
        case TODESTMOY:
          copyMakeBorder(Res, big_image, 1, 1, 1, 1, BORDER_CONSTANT, Scalar::all(1));
          if (intensity == 1){
          float moy = (big_image.at<float>(j+1, i+2)+big_image.at<float>(j+1,i)+
            big_image.at<float>(j+2, i+1)+big_image.at<float>(j,i+1)
            +big_image.at<float>(j+2, i+2)+big_image.at<float>(j, i)
            +big_image.at<float>(j,i+2)+ big_image.at<float>(j+2,i))/8.;
            intensity = moy;
           }
           break;
           default:
           std::cerr << "ERROR : The type of the rotation wasn't understood or try apply_source function. Aborting" << endl;
           break;
          }
          Res.at<float>(pt) = intensity;

        }
      }
  Rect roi = Rect(0, 0, img.cols, img.rows);
  return Res(roi);
}

Mat Rotation::apply_elasticity(Mat &image){
    int rows = image.rows;
    int cols = image.cols;
    Mat Res = Mat::ones(rows,cols, CV_32FC1);
    Point2f rot_center = pressure_center_computation(image);
    float tmp = rot_center.x;
    rot_center.x = rot_center.y;
    rot_center.y = tmp;
    for(int i = 0; i < rows; i++ ){
      for(int j = 0; j < cols ; j++){
        Point2f pt(j,i);
        this -> decrease_rotation(pt, rot_center, image);
        if( pt.x >= 0 && pt.y >= 0 && int(pt.x) < image.cols-1 && int(pt.y) < image.rows-1){
          float intensity = intensity_computation_bicubic(pt, image);
          Res.at<float>(i,j) = intensity;
       }
    }
    // Rect roi = Rect(dim_output_y/2-cols/2+1, dim_output_x/2-rows/2, cols, rows);
  }
  return Res;
}

void Rotation::decrease_rotation(Point2f &pt, Point2f &rot_center, Mat &img){
  float tmp = pt.x;
  float dist = dist_to_O(rot_center-pt);
  float angle_tmp = angle * exp(-dist*dist/1000);

  pt.x = cos(-PI*angle_tmp/180)*(pt.x-rot_center.y) - sin(-PI*angle_tmp/180)*(pt.y-rot_center.x)+rot_center.y;
  pt.y = sin(-PI*angle_tmp/180)*(tmp-rot_center.y) + cos(-PI*angle_tmp/180)*(pt.y-rot_center.x)+rot_center.x;
}


void Rotation::set_angle(float new_angle){
  angle = new_angle;
}

void Rotation::set_method(rotation_type new_method){
  method = new_method;
}


float intensity_computation_classic(const Point2f &pt, const Mat &img){
  return img.at<float>(pt);
}

float intensity_computation_bilinear(const Point2f &pt, const Mat &img){
  Point2f inf, sup;
  float dx, dy;
  floor_ceil_dx_dy(pt, inf, sup, dx, dy);

  if (inf.x == pt.x && inf.y == pt.y){
    return img.at<float>(inf);
  }
  floor_ceil_dx_dy(pt, inf, sup, dx, dy);

  float intensity1, intensity2, intensity3, intensity4;
  get_intensities(img, inf, sup, intensity1, intensity2, intensity3, intensity4);

  float res = (1-dx)*(1-dy)*intensity1+dx*(1-dy)*intensity2+dx*dy*intensity3+(1-dx)*dy*intensity4;
  if (res > 1){
    res = 1;
  }

  return res;
}

float intensity_computation_bicubic(Point2f &pt, Mat &img){
  Point2f inf, sup;
  float dx, dy;
  floor_ceil_dx_dy(pt, inf, sup, dx, dy);

  if (inf.x == pt.x && inf.y == pt.y){
    return img.at<float>(inf);
  }

  Mat coeff = coeff_bicubic(pt, img);
  vector<float> res_tmp(4);

  for(int i=0; i < 4; i++){
    float puis = 1;
    for(int j = 0; j < 4; j++){
      res_tmp[i] += coeff.at<float>(j,i)*puis;
      puis *= dx;
    }
  }

  float res = res_tmp[0]+res_tmp[1]*dy+res_tmp[2]*dy*dy+res_tmp[3]*dy*dy*dy;
  return res;
}

float intensity_computation_weighted(const Point2f &pt, const Mat &img){
  Point2f inf, sup;
  float dx, dy;
  floor_ceil_dx_dy(pt, inf, sup, dx, dy);

  if (inf.x == pt.x && inf.y == pt.y){
    return img.at<float>(inf);
  }

  float intensity1, intensity2, intensity3, intensity4;
  get_intensities(img, inf, sup, intensity1, intensity2, intensity3, intensity4);

  float dist_left_top = dist_to_O(pt-inf);
  float dist_right_top = dist_to_O(Point2f(pt.x-sup.x, pt.y-inf.y));
  float dist_left_bottom = dist_to_O(Point2f(pt.x-inf.x, pt.y-sup.y));
  float dist_right_bottom = dist_to_O(pt-sup);

  float res = (1./dist_left_top)*intensity1+(1./dist_right_top)*intensity2+(1./dist_left_bottom)*intensity4+(1./dist_right_bottom)*intensity3;
  res /= ((1./dist_left_top)+(1./dist_right_top)+(1./dist_left_bottom)+(1./dist_right_bottom));
  return res;
}

Mat coeff_bicubic(const Point2f &pt, const Mat &img){
  Point2f inf, sup;
  float dx, dy;
  floor_ceil_dx_dy(pt, inf, sup, dx, dy);
  float intensity1, intensity2, intensity3, intensity4;
  get_intensities(img, inf, sup, intensity1, intensity2, intensity3, intensity4);

  Mat M = (Mat_<float>(4,4) << intensity1, intensity4, derive_y(pt, img), derive_y(pt + Point2f(0,1),img),
                               intensity2, intensity3, derive_y(pt + Point2f(1,0),img), derive_y(pt+Point2f(1,1),img),
                               derive_x(pt, img), derive_x(pt + Point2f(0,1),img), derive_xy(pt, img), derive_xy(pt + Point2f(0,1),img),
                               derive_x(pt + Point2f(1,0), img), derive_x(pt+Point2f(1,1),img), derive_xy(pt+Point2f(1,0),img), derive_xy(pt+Point2f(1,1),img));

  Mat A = (Mat_<float>(4,4) << 1,0,0,0,
                                0,0,1,0,
                                -3,3,-2,-1,
                                2,-2,1,1);


  Mat A_inv = (Mat_<float>(4,4) << 1,0,-3,2,
                                    0,0,3,-2,
                                    0,1,-2,1,
                                    0,0,-1,1);

  Mat res(Size(4,4),CV_32F);
  res = A*M*A_inv;
  return res;
}

void get_intensities(const Mat &img, const Point2i &inf, const Point2i &sup, float &i1, float &i2, float &i3, float &i4){
  i1 = img.at<float>(inf);
  i2 = img.at<float>(sup.y, inf.x);
  //i2 =  img.at<float>(Point2f(inf.x, sup.y))
  i3 = img.at<float>(sup);
  i4 = img.at<float>(inf.y, sup.x);
}




void floor_ceil_dx_dy(const Point2f &pt, Point2f &inf, Point2f &sup, float &dx, float &dy){
  inf.x = float(floor(pt.x));
  inf.y = float(floor(pt.y));
  sup = inf + Point2f(1,1);
  dx = (pt.y-inf.y)/(sup.x-inf.x);
  dy = (pt.x-inf.x)/(sup.y-inf.y);
}

float dist_to_O(const Point2f pt){
  float dist = sqrt(pt.x*pt.x + pt.y*pt.y);
  return dist;
}

float derive_x(const Point2f pt, Mat image){
    float res;
    float floorx = float(floor(pt.x));
    float floory = float(floor(pt.y));
    float floorx_1 = float(floor(pt.x))-1;
    float ceilx = float(ceil(pt.x));

    float intensity1 = image.at<float>(Point2f(floorx-1,  floory));
    float intensity2 = image.at<float>(Point2f(ceilx,  floory));

    res = (intensity2 -intensity1)/(ceilx-floorx_1);

    return res;
  }

float derive_y(const Point2f pt, Mat image){
    float res;
    float floorx = float(floor(pt.x));
    float floory = float(floor(pt.y));
    float floory_1 = float(floor(pt.y))-1;
    float ceily = float(ceil(pt.y));

    float intensity1 = image.at<float>(Point2f(floorx,  floory_1));
    float intensity2 = image.at<float>(Point2f(floorx,  ceily));

    res = (intensity2 -intensity1)/(ceily-floory_1);

    return res;
  }

float derive_xy(const Point2f pt, Mat image){
    float res;
    float floorx = float(floor(pt.x));
    float floory = float(floor(pt.y));
    float floory_1 = float(floor(pt.y))-1;
    float ceily = float(ceil(pt.y));
    float floorx_1 = float(floor(pt.x))-1;
    float ceilx = float(ceil(pt.x));

    float intensity1 = image.at<float>(Point2f(floorx_1,  floory_1));
    float intensity2 = image.at<float>(Point2f(floorx_1,  ceily));
    float intensity3 = image.at<float>(Point2f(ceilx,  floory_1));
    float intensity4 = image.at<float>(Point2f(ceilx,  ceily));

    res = (intensity4-intensity3-intensity2+intensity1)/((ceilx-floorx_1)*(ceily-floory_1));
    return res;
  }
