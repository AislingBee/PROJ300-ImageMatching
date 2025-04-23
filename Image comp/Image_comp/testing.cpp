
#include "testing.hpp"

#include <vector>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"

#include "checkloaded.hpp"
#include "matching.hpp"

Testing::Testing(Mat templ)
{
    vector<Vec4f> positionGuil;

    int i =0;
    for (const char *test_img:testpaths)
    {
        test_input = imread(test_img);
        if (!ImageLoad(test_input))
        {
            break;//return -1;
        }
        testImgArr[i]=test_input;
        i++;
    }

    while(1)
    {
        Mat image;
        for (Mat c:testImgArr)
        {
            c.copyTo(image);

            Mat grayImage;
            cvtColor(image, grayImage, COLOR_RGB2GRAY);

            Ptr<GeneralizedHoughGuil> guil = createGeneralizedHoughGuil();
            //  create guil and set options // green
            SetupHoughGuilParams(templ,guil);

            //  execute guil detection
            guil->detect(grayImage, positionGuil);

            //  draw guil
            int i=0;
            for (vector<Vec4f>::iterator iter = positionGuil.begin(); iter != positionGuil.end(); ++iter) {
               // circle(image,Point2f((*iter)[0], (*iter)[1]),4,Scalar(0, 255, 0),6);
                putText(image,""+to_string(i),Point2f((*iter)[0], (*iter)[1]),1,5,Scalar(0, 255, 0),6);
               i++;
            }

            // show windows
            imshow("result_img", image);
            imshow("template",templ);
            waitKey(1);
        }
    }
    //break;//return 0;
}
