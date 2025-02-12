#ifndef TESTING_HPP
#define TESTING_HPP

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

class Testing
{
public:
    Testing(Mat templ);
    int RunTestCode(Mat templ);

private:
    #define TEST_PATH_IMG1 "../images/test_images/cat.png"
    #define TEST_PATH_IMG2 "../images/test_images/cat_90.png"
    #define TEST_PATH_IMG3 "../images/test_images/cat_90_0.5.png"
    #define TEST_PATH_IMG4 "../images/test_images/cat_0.5.png"
    #define TEST_PATH_IMG5 "../images/test_images/blackX.png"

    const char *testpaths[5]={TEST_PATH_IMG1,TEST_PATH_IMG2,TEST_PATH_IMG3,TEST_PATH_IMG4,TEST_PATH_IMG5};
    Mat test_input, test_input2, test_input3, test_input4, test_input5;
    Mat testImgArr[5]={test_input,test_input2,test_input3,test_input4,test_input5};

};



#endif // TESTING_HPP
