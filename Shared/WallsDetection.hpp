//
//  WallsDetection.cpp
//  VRHouseFramework
//

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class WallsDetection {

public:
    vector<vector<cv::Point>> findWalls(cv::Mat input);
};
