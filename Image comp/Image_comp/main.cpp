// my header files
#include <iostream>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio.hpp"

//My Headers
#include "matching.hpp"
#include "checkloaded.hpp"
#include "testing.hpp"

#define TEMPLATE_PATH "../images/download.png"
#define TEST_CATS "../images/test_images/cat.png"
#define CAMERA 0    // 0 = open default camera

#define TEST true

using namespace std;
using namespace cv;

int main()
{
    // Load template image in grayscale
    Mat templ = imread(TEMPLATE_PATH, IMREAD_GRAYSCALE);
    if (!ImageLoad(templ))  // check it loaded else give error
        return -1;

    //int w = templ.cols;
    //int h = templ.rows;

    if (TEST==true){
        // run test version of code with static inputs
        Testing test(templ);
        //RunTestCode(templ);
    }
    else{
        // Open Camera
        VideoCapture camera;
        camera.open(CAMERA);
        if (!CameraOpen(camera))
            return -1;

    while(1)
    {
            vector<Vec4f> positionGuil;
        Mat image;
        camera.read(image);

        //  create grayscale image
        Mat grayImage;
        cvtColor(image, grayImage, COLOR_RGB2GRAY);

        Ptr<GeneralizedHoughGuil> guil = createGeneralizedHoughGuil();
        //  create guil and set options // green
        SetupHoughGuilParams(templ,guil);

        //  execute guil detection
        guil->detect(grayImage, positionGuil);


        //  draw guil
        for (vector<Vec4f>::iterator iter = positionGuil.begin(); iter != positionGuil.end(); ++iter) {
            circle(image,Point2f((*iter)[0], (*iter)[1]),4,Scalar(0, 255, 0),6);
        }


        // show windows
        imshow("result_img", image);
        imshow("template",templ);
        waitKey(1);
    }

    return 0;
}
}
