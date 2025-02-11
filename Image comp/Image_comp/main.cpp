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
            // [0]: x coordinate of center point
            // [1]: y coordinate of center point
            // [2]: scale of detected object compared to template
            // [3]: rotation of detected object in degree in relation to template

            // to make prettier still
            float scale=(*iter)[2];
            Point location_top,location_bottom;
            location_top.x=(*iter)[0]-((w*scale)/2);
            location_top.y=(*iter)[1]-((h*scale)/2);
            location_bottom.x=(*iter)[0]+((w*scale)/2);
            location_bottom.y=(*iter)[1]+((h*scale)/2);
            rectangle(image,location_top,location_bottom,Scalar(0, 255, 0),2);

        }

        // show windows
        imshow("result_img", image);
        imshow("template",templ);
        waitKey(1);
    }

    return 0;
}
