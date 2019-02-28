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
    cout << "convol thanks to fft...";
    convert_to_float(image,image);
    // for (int i = 1; i < 7; i++){
    //   Mat kernel = Gaussian_kernel(11, i, i, 1);
    //   Mat naive;
    //   // cout << kernel << endl << endl;
    //   convolution_fft(image, naive, kernel);
    //   convert_to_int(naive, naive);
    //   imwrite("../img/Banques/convol_blur_" + std::to_string(i)+".png", naive);
    //   cout << " Done." << endl;
    // }
    Mat kernel = Gaussian_kernel(11, 7, 0.0001, 1);
    Mat naive;
    // cout << kernel << endl << endl;
    convolution_fft(image, naive, kernel);
    convert_to_int(naive, naive);
    imwrite("../img/Banques/convol_fft.png", naive);
    cout << " Done." << endl;
}
