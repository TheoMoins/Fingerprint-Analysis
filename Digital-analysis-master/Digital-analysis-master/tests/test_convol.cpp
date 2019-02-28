#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "starter_1.h"
#include "main_1.h"
#include "starter3.h"
using namespace cv;
using std::cout;
using std::endl;

int main(int argc, char** argv )
{
    if ( argc < 2 )
    {
        printf("usage: Test_1 <Image_Path> [Test]\n");
        return -1;
    }
    Mat image;
    image = imread(argv[1], 0);
    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }
    //TESTING THE CONVOLUTION SINCE THE RIGHT DOWN POINT
    /*cout << "convol from the right down point ...";
    convert_to_float(image, image);
    Mat kernel = Gaussian_kernel(5,2,2);
    Mat naive = Convol(image, kernel);
    convert_to_int(naive, naive);
    imwrite("tests/test_convol.png", naive);
    waitKey(0);
    cout << " Done." << endl;*/
    /*cout << "Testing the image shifting" << endl;
    convert_to_float(image,image);
    image = periodic_shift(image, 350);
    convert_to_int(image,image);
    imwrite("../output/shift.png", image);*/
    Mat kernel(3,3,CV_8UC1, 1);
    erode(image,image,kernel);
    imwrite("../dilatation.png", image);
    dilate(image,image,kernel);
    imwrite("../erodation.png", image);

}
