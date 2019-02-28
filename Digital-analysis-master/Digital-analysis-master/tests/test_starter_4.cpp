#include <opencv2/opencv.hpp>

#include "starter_4.h"
#include "starter_1.h"
#include "main_1.h"


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
    cout << "This test program will save all its work to the main directory" << endl;
    cout << "Image succesfully imported" << endl;
    convert_to_float(image, image);

    /* TESTING THE BINARIZATION OF THE IMAGE */
    binarization(image, image);
    /*
    namedWindow( "Display window", WINDOW_AUTOSIZE );
    imshow( "Display window", image );
    waitKey(0);
    */
    convert_to_int(image, image);
    imwrite("../output/test_bin.png", image);
    cout << "Binarization done." << endl;

    cout << endl << "All tests have passed successfully, well done !" << endl;
}
