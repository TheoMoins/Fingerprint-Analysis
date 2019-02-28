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
    //TESTING THE INVERSE FOURIER TRANSFORM
    cout << "give the spectre of the fourier transform of an image ...";
    Mat dst = image;
    convert_to_float(dst, image);
    Mat kernel = Gaussian_kernel(5,2,2,1);
    Mat complex = transfo_fourier(image);
    int nbCols = complex.cols;
    int nbRows = complex.rows;
    Mat naive = inv_transfo_fourier(complex, nbCols, nbRows);
    convert_to_int(naive, naive);
    imwrite("tests/test_ifft.png", naive);
    waitKey(0);
    cout << " Done." << endl;
}
