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

    /**
     Crops the given Mat using the given corners.

     @param input The given Mat.
     @param topLeft The top left corner.
     @param topRight The top right corner.
     @param bottomLeft The bottom left corner.
     @param bottomRight The bottom right corner.
     @return A cropped Mat with applied a perspective transformation.
     */
    Mat cropSelectedArea(Mat input, Point2f topLeft, Point2f topRight, Point2f bottomLeft, Point2f bottomRight);

private:
    int findLargestContourIndex(vector<vector<cv::Point>> contours);

};
