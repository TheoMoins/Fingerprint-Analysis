#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "starter_1.h"
#include "main_1.h"
#include "starter3.h"
#include <stdlib.h>
#include <cmath>

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
    //TESTING THE CONVOLUTION SINCE CENTERED POINT
    cout << "convol_xy from the centered point ...";
    convert_to_float(image,image);
    Point2i pc(image.cols/2, image.rows/2);
    Mat naive = Convol_Shifted_xy(image, 11);
    convert_to_int(naive, naive);
    imwrite("../img/Banques/test_convol_shifted_xy0.png", naive);
    //waitKey(0);
    cout << " Done." << endl;
}
