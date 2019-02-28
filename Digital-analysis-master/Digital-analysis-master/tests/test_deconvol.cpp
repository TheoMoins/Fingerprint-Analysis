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
    //TESTING THE CONVOLUTION WITH FFT
    cout << "deconvolution...";
    // convert_to_float(image,image);
    // Mat kernel = Gaussian_kernel(11, 2, 2, 1);
    // cout << kernel << endl << endl;
    // Mat naive;
    // convolution_fft(image, naive, kernel);
    // Mat k;
    // deconvolution_kernel(naive,k,image);
    // cout << k << endl << endl;
    Mat kernel = Normalized_kernel(5, 5);
    cout << kernel << endl << endl;
    //copyMakeBorder(kernel, kernel, 0, 5, 0, 5, BORDER_CONSTANT, Scalar::all(0));
    Mat tmp = transfo_fourier(kernel);
    tmp = inv_transfo_fourier(kernel, 5, 5);
    cout << tmp << endl;

    // Mat kernel2 = 1/Gaussian_kernel(11, 2, 2, 1);
    // Mat naive2;
    // kernel = Gaussian_kernel(11, 2, 2, 1);
    // deconvolution_fft(naive, naive2, kernel);
    // convert_to_int(naive2, naive2);
    // imwrite("../img/Banques/deconvol.png", naive2);
    cout << " Done." << endl;
}
