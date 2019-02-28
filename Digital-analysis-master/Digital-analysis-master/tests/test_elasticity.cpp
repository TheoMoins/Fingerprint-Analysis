#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "starter_1.h"
#include "main_1.h"
#include "starter3.h"
#include "Rotation.h"
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
    //TESTING THE ELASTICITY IN THE IMAGE
    float angle = 30;
    cout << "Elasticity of image...";
    convert_to_float(image, image);
    Rotation rot(ELASTICITY, angle);
    Mat elasticity = rot.apply(image);
    convert_to_int(image, image);
    convert_to_int(elasticity, elasticity);
    imwrite("img/image_rotation/elasticity.png", elasticity);
    imwrite("img/image_rotation/image.png", image);

    cout << "done." << std::endl;
}
