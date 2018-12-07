//
//  SheetDetection.cpp
//  VRHouseFramework
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace cv;
using namespace std;

class SheetDetection {

public:
    /**
     Returns found corners of the given Mat in the clockwise order:
     top-left, top-right, bottom-right, and bottom-left.

     @param input The given Mat.
     @return A vector of Points.
     */
    vector<cv::Point> findCorners(cv::InputArray input);

private:
    int findLargestContourIndex(vector<vector<cv::Point>> contours);

};
