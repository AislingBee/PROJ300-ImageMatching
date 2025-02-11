// my header files
#include <iostream>
#include <vector>
// #include <thread>
//#include <ctype.h>
#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc.hpp"

//My Headers
#include "matching.hpp"
#include "checkloaded.hpp"
#include "testparams.hpp"

#define TEMPLATE_PATH "../images/cat_template_0.5.png"
#define CAMERA 0    // 0 = open default camera

using namespace std;
using namespace cv;


int main() {
    // Open Camera
    VideoCapture camera;
    camera.open(CAMERA);
    if (!CameraOpen(camera))
        return -1;

    // Load template image in grayscale
    Mat templ = imread(TEMPLATE_PATH, IMREAD_GRAYSCALE);
    if (!ImageLoad(templ))
        return -1;
    int w = templ.cols;
    int h = templ.rows;

    //  create variable for location, scale and rotation of detected templates
    vector<Vec4f> positionGuil;
    Ptr<GeneralizedHoughGuil> guil = createGeneralizedHoughGuil();
    SetupHoughGuilParams(templ,guil);

    // Read cam frame, draw match
    while(1)
    {
        // read camera frame and convert to greyscale
        Mat image, grayImage;
        camera.read(image);
        cvtColor(image, grayImage, COLOR_RGB2GRAY);
       // ScaleandRotateTemplate(grayImage,0,0.5);
        guil->detect(grayImage, positionGuil);

        //  draw guil
        for (vector<Vec4f>::iterator iter = positionGuil.begin(); iter != positionGuil.end(); ++iter) {
            RotatedRect rRect = RotatedRect(Point2f((*iter)[0], (*iter)[1]),
                                            Size2f(w * (*iter)[2], h * (*iter)[2]),
                                            (*iter)[3]);
            Point2f vertices[4];
            rRect.points(vertices);
            for (int i = 0; i < 4; i++)
                line(image, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
        }

        // show windows
        imshow("result_img", image);
        imshow("template",templ);
        waitKey(1);
    }

    return 0;
}
