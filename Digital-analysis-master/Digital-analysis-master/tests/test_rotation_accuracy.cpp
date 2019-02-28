#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "starter_1.h"
#include "main_1.h"
#include "starter3.h"
#include "Rotation.h"
#include <cmath>
using namespace cv;
using std::cout;
using std::endl;

Mat rotate(Mat src, double angle)
{
    Mat dst;
    Point2f pt(src.cols/2, src.rows/2);
    Mat r = getRotationMatrix2D(pt, angle, 1.0);
    warpAffine(src, dst, r, Size(src.cols, src.rows), INTER_CUBIC, BORDER_CONSTANT,Scalar(255));
    return dst;
}


float mean_accuracy(Mat image1, Mat image2){
  Mat diff;
  absdiff(image1, image2, diff);

  Scalar res = mean(diff);
  return 100-100*res[0]/255;
}




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

    //TESTING THE ACCURACY OF THE ROTATION OF THE IMAGE

    cout << "Rotation accuracy of image..." <<endl;
    convert_to_float(image, image);
    float angle = 75;
    Rotation rot(WEIGHTED, angle);
    Mat rotation_weighted = rot.apply(image);
    rot.set_method(TODEST);
    Mat rotation_to_dest = rot.apply(image);
    rot.set_method(TODESTMOY);
    Mat rotation_to_dest_moy = rot.apply(image);
    rot.set_method(TODESTNEIGHBOUR);
    Mat rotation_to_dest_neighbour = rot.apply(image);
    rot.set_method(BICUBIC);
    Mat rotation_from_source_bicubic = rot.apply(image);
    rot.set_method(CLASSIC);
    Mat rotation_from_source = rot.apply(image);
    rot.set_method(BILINEAR);
    Mat rotation_from_source_bilinear = rot.apply(image);
    Mat true_rotation = rotate(image, angle);
    convert_to_int(rotation_to_dest_moy, rotation_to_dest_moy);
    convert_to_int(rotation_to_dest_neighbour, rotation_to_dest_neighbour);
    convert_to_int(rotation_to_dest, rotation_to_dest);
    convert_to_int(rotation_from_source, rotation_from_source);
    convert_to_int(rotation_from_source_bicubic, rotation_from_source_bicubic);
    convert_to_int(rotation_from_source_bilinear, rotation_from_source_bilinear);
    convert_to_int(true_rotation, true_rotation);
    convert_to_int(rotation_weighted, rotation_weighted);
    float accuracy_dest_moy = mean_accuracy(rotation_to_dest_moy, true_rotation);
    float accuracy_dest_neighbour = mean_accuracy(rotation_to_dest_neighbour, true_rotation);
    float accuracy_source = mean_accuracy(rotation_from_source, true_rotation);
    float accuracy_bilinear = mean_accuracy(rotation_from_source_bilinear, true_rotation);
    float accuracy_bicubic = mean_accuracy(rotation_from_source_bicubic, true_rotation);
    float accuracy_to_dest = mean_accuracy(rotation_to_dest, true_rotation);
    float accuracy_weighted = mean_accuracy(rotation_weighted, true_rotation);

    cout << "accuracy_to_dest :" << accuracy_to_dest << endl;
    cout << "accuracy_to_dest_moy :" << accuracy_dest_moy << endl;
    cout << "accuracy_dest_neighbour:" << accuracy_dest_neighbour << endl;
    cout << "accuracy_source :" << accuracy_source << endl;
    cout << "accuracy_weighted :" << accuracy_weighted << endl;
    cout << "accuracy_bilinear :" << accuracy_bilinear << endl;
    cout << "accuracy_bicubic :" << accuracy_bicubic << endl;

    cout << " Done." << endl;
}
