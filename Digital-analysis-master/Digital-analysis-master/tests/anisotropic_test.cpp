#include <opencv2/opencv.hpp>

#include "starter_1.h"
#include "main_1.h"
#include "elliptical_modelling.h"

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
    cout << "This test program will save all its work to the img/Anisotropic_filtering directory" << endl;
    cout << "Image succesfully imported" << endl;
    convert_to_float(image, image);


    /* TESTING THE ELLIPTICAL DILATION */
    Point2i pressure_center = pressure_center_computation(image);
    anisotropic_filtering(image, pressure_center);
    /*Point2i parameters = parameters_computation(image, pressure_center);
    Point2i dimensions(image_bis.rows, image_bis.cols);
    Mat Ellipse = ellipse(parameters, pressure_center, dimensions);
    namedWindow("ellipse", CV_WINDOW_AUTOSIZE);
    imshow("ellipse", Ellipse);
    waitKey(0);
    //for (uint i = 0; i < 2; i++) {
      erosion(0, 0, Ellipse, Ellipse);
    //}
    convert_to_int(Ellipse, Ellipse);
    */
    namedWindow("Anisotropic filtering", CV_WINDOW_AUTOSIZE);
    imshow("Anisotropic filtering", image);
    waitKey(0);
    convert_to_int(image, image);
    imwrite("img/Anisotropic_filtering/weakened_finger_v2.png", image);

    cout << endl << "Anisotropic filtering done." << endl;
}
