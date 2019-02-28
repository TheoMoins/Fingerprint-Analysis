#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "starter_1.h"
#include "main_1.h"
#include "starter3.h"
#include "Rotation.h"
using namespace cv;
using std::cout;
using std::endl;



Mat rotate(Mat src, double angle)
{
    Mat dst;
    Point2f pt(src.cols/2, src.rows/2);
    Mat r = getRotationMatrix2D(pt, angle, 1.0);
    warpAffine(src, dst, r, Size(src.cols, src.rows), INTER_LINEAR, BORDER_CONSTANT,Scalar(255));
    return dst;
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
    //TESTING THE ROTATION OF THE IMAGE
    cout << "Rotation of image...";
    convert_to_float(image, image);
    float angle = 30;
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
    convert_to_int(image, image);
    imwrite("img/image_rotation/rotation_to_dest.png", rotation_to_dest);
    imwrite("img/image_rotation/rotation_from_source_bilinear.png", rotation_from_source_bilinear );
    imwrite("img/image_rotation/rotation_from_source.png", rotation_from_source);
    imwrite("img/image_rotation/rotation_from_source_bicubic.png", rotation_from_source_bicubic);
    imwrite("img/image_rotation/true_rotation.png", true_rotation);
    imwrite("img/image_rotation/rotation_weighted.png", rotation_weighted);
    imwrite("img/image_rotation/rotation_to_dest_moy.png", rotation_to_dest_moy);
    imwrite("img/image_rotation/rotation_to_dest_neighbour.png", rotation_to_dest_neighbour);
    cout << " Done." << endl;
}
