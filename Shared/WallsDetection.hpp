//
//  WallsDetection.cpp
//  VRHouseFramework
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace cv;
using namespace std;

class WallsDetection {

public:
    vector<vector<cv::Point>> findWalls(cv::Mat input);
};
