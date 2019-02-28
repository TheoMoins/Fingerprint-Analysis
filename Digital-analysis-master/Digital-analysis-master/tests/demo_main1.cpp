#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "starter_1.h"
#include "main_1.h"
using namespace cv;
using std::cout;
using std::endl;

int main(int argc, char** argv )
{
    if ( argc > 1 )
    {
        printf("usage: Demo_Main1 \n");
        return -1;
    }
    cout << "This test program will save all its work to the output directory" << endl;


    Mat image;
    /*TESTING THE WEAKENING */
    image = imread("img/clean_finger.png", 0);
    cout << "Weakening clean_finger...";
    Point2i pressure_center;
    pressure_center = pressure_center_computation(image);
    convert_to_float(image, image);
    clean_to_weak_iso(image, pressure_center);
    convert_to_int(image, image);
    imwrite("img/Weakened_finger.png", image);
    cout << " Done." << endl;

    /*TESTING THE REINFORCEMENT*/
    image = imread("img/weak_finger.png", 0);
    cout << "Reinforcing weak_finger...";
    pressure_center = pressure_center_computation(image);
    convert_to_float(image, image);
    weak_to_clean_iso(image, pressure_center);
    convert_to_int(image, image);
    imwrite("img/Reinforced_finger.png", image);
    cout << " Done." << endl;
}
    //AJOUTER LA VERSION ELLIPSE PUIS LA VERSION ANISOTROPIQUE QUAND ON L'AURA
