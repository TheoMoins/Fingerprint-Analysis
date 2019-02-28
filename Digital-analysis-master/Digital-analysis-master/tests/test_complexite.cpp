#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "starter_1.h"
#include "main_1.h"
#include "starter3.h"
#include <time.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace cv;
using std::cout;
using std::endl;

void create_file(std::ofstream &monFlux, clock_t temps1, clock_t temps2, clock_t temps3, clock_t temps4, int m, int n){
  monFlux << n << " " << m << " " <<  -(double) temps1/CLOCKS_PER_SEC + (double) temps2/CLOCKS_PER_SEC;
  monFlux << " " << -(double) temps3/CLOCKS_PER_SEC + (double) temps4/CLOCKS_PER_SEC << endl;
}

int main(int argc, char** argv)
{
  clock_t temps1;
  clock_t temps2;
  clock_t temps3;
  clock_t temps4;
  string const nomFichier1("kernel3.txt");
  string const nomFichier2("kernel9.txt");
  string const nomFichier3("kernel15.txt");

  std::ofstream monFlux1(nomFichier1.c_str());
  std::ofstream monFlux2(nomFichier2.c_str());
  std::ofstream monFlux3(nomFichier3.c_str());

  for (int n = 16; n<10000; n+=100){
    // for (int m = 16; m<1000; m+=50){
      int elt = 3;
      while(elt <16){
        temps1 = clock();
        Mat image = Mat::ones(n,n, CV_32F);
        Mat kernel(elt,elt,CV_32FC1, Scalar(1./(elt*elt)));
        Mat naive;
        Convol_Shifted(image, naive, kernel);
        temps2=clock();
        temps3= clock();
        Mat naive2;
        convolution_fft(image, naive2, kernel);
        temps4=clock();
        if( elt == 3){
          create_file(monFlux1, temps1, temps2, temps3, temps4, n, n);
        }
        if( elt == 9){
          create_file(monFlux2, temps1, temps2, temps3, temps4, n, n);
        }
        if( elt == 15){
          create_file(monFlux3, temps1, temps2, temps3, temps4, n, n);
        }
        elt += 6;
      // }
    }
  cout << n << endl;
  }
}
