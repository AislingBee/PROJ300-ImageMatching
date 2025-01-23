// my header files
#include <iostream>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

Mat cap_frame;
Mat img_template;
Mat test_input;
Mat img;
Mat result;

void MatchFrames();
bool ImageLoad(Mat);

int main()
{
    // lecture 5 slide 79
    //QCoreApplication a(argc, argv);
    const char *vid_window = "Video Feed with Match Square";
    namedWindow(vid_window, WINDOW_AUTOSIZE);
    const char *match_results = "Image Matching";
    namedWindow(match_results, WINDOW_AUTOSIZE);

    // Open the Default Camera
    VideoCapture input_cap(0);
    if (!input_cap.isOpened()) {
        cerr << "Error: Unable to open camera\n";
        return -1;
    }

    // Open the template and test image
    img_template = imread("../images/blackX_centre.png");
    test_input = imread("../images/blackX_more.png");
    ImageLoad(img_template);
    ImageLoad(test_input);



    while(1){
        // Read the camera input
        input_cap.read(cap_frame);
        ImageLoad(cap_frame);

        // match input image to template
        MatchFrames();

        /*

        // FAST feature detector
        // now ORB cause why not
        vector<KeyPoint> keypoints1, keypoints2;
        Mat descriptors1, descriptors2;
        //Ptr<FastFeatureDetector> FeatureDetector = FastFeatureDetector::create();
        Ptr<ORB> FeatureDetector = ORB::create();

        // detect keypoints and descriptors
        FeatureDetector->detectAndCompute(img_template,noArray(),keypoints1,descriptors1);
        FeatureDetector->detectAndCompute(input_img,noArray(),keypoints2,descriptors2);

        //////////////////////
        /// DRAW KEYPOINTS ///
        //////////////////////
        // Mat tar_keypoints1, tar_keypoints2;
        // drawKeypoints(target1,keypoints1,tar_keypoints1, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
        // drawKeypoints(target1,keypoints2,tar_keypoints2, Scalar::all(-1), DrawMatchesFlags::DEFAULT );

        Ptr<DescriptorMatcher> FDescriptorMatcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
        std::vector< std::vector<DMatch> > knn_matches;
        FDescriptorMatcher->knnMatch( descriptors1, descriptors2, knn_matches, 2 );

        const float ratio_thresh = 100.0f;
        std::vector<DMatch> good_matches;
        for (size_t i = 0; i < knn_matches.size(); i++)
        {
            if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
            {
                good_matches.push_back(knn_matches[i][0]);
            }
        }

        // DRAW MATCHES

        //drawMatches(target1,keypoints1,target2,keypoints2,good_matches , result, Scalar::all(-1), Scalar::all(-1), std::vector<char>(),DrawMatchesFlags::DEFAULT);

        // go through and and comment
    */


        // Display the windows :)
        imshow(vid_window,img);
        imshow(match_results,result);
        waitKey(1);
    }

    return 0;
}

// Functions
bool ImageLoad(Mat image)
{
    if(image.empty())
    {
        cout<<"Error: Image cant be loaded"<<endl;
        return false;
    }
    return true;
}

void MatchFrames()
{
    cap_frame.copyTo(img);
    int result_cols = img.cols - img_template.cols + 1;
    int result_rows = img.rows - img_template.rows + 1;

    result.create( result_rows, result_cols, CV_32FC1 );

    // match template to the camera frame
    matchTemplate(cap_frame, img_template, result,TM_SQDIFF_NORMED);
    normalize(result,result,0,1, NORM_MINMAX, -1,Mat());

    double minVal, maxVal;
    Point minLoc, maxLoc, matchLoc;

    minMaxLoc(result,&minVal,&maxVal,&minLoc,&maxLoc,Mat());
    matchLoc=minLoc;

    // drawing the results
    rectangle(img,matchLoc,Point(matchLoc.x+img_template.cols,matchLoc.y+img_template.rows),Scalar(0,0,0),2,8,0);
    rectangle(result,matchLoc,Point(matchLoc.x+img_template.cols,matchLoc.y+img_template.rows),Scalar(0,0,0),2,8,0);
    return;

}

