#include <iostream>
#include<mylib.h>
#include<imageprocessingl.h>
#include<opencv.h>
#include<tensorflow/c/c_api.h>

using namespace std;
int main()
{
    MYLIB mylib;
    mylib.print();

    ImageProcessingL imagepro;
    imagepro.processImage();

    OpenCV opencv;
    opencv.testOpenCv();

    printf("Hello from TensorFlow C library version %s\n", TF_Version());


    return 0;
}
