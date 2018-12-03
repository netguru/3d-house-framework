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
    vector<cv::Point2f> findCorners(cv::InputArray input);

private:
    int findLargestContourIndex(vector<vector<cv::Point>> contours);

};
