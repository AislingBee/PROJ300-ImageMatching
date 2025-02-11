#ifndef TESTPARAMS_H
#define TESTPARAMS_H

#include "opencv2/core/core.hpp"
// Test image paths
#define TEST_PATH_IMG1 "../images/cat.png"
#define TEST_PATH_IMG2 "../images/cat_90.png"
#define TEST_PATH_IMG3 "../images/cat_90_0.5.png"
#define TEST_PATH_IMG4 "../images/blackX_more.png"
#define TEST_PATH_IMG5 "../images/cat_0.5.png"

const char *testpaths[]={TEST_PATH_IMG1,TEST_PATH_IMG2,TEST_PATH_IMG3,TEST_PATH_IMG4,TEST_PATH_IMG5};

cv::Mat test_input;
cv::Mat test_input2;
cv::Mat test_input3;
cv::Mat test_input4;
cv::Mat test_input5;
cv::Mat testImgArr[]={test_input,test_input2,test_input3,test_input4,test_input5};

#endif // TESTPARAMS_H
