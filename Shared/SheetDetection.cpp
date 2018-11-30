//
//  SheetDetection.cpp
//  VRHouseFramework
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

const bool SHOW_STEPS = false;
const bool DRAW_CONTOURS = false;
const int DESIRED_WIDTH = 640;

void resizeWithRatio(InputArray input, OutputArray result, int desiredWidth) {
    float ratio = (float) input.rows() / input.cols();
    Size resultSize = Size(desiredWidth, (int) (desiredWidth * ratio));
    
    if (SHOW_STEPS) {
        cout << "resizeWithRatio: desiredSize = " << resultSize << endl;
    }
    
    resize(input, result, resultSize);
}

int findLargestContourIndex(vector<vector<Point>> contours) {
    double largest_area = 0;
    int largest_contour_index = 0;
    
    for (int i = 0; i < contours.size(); i++)
    {
        double a = contourArea(contours[i], false);
        if (a > largest_area)
        {
            largest_area = a;
            largest_contour_index = i;
        }
    }
    
    return largest_contour_index;
}

void findCorners(InputArray input) {
    // resized input
    Mat resized;
    
    // resize input image
    resizeWithRatio(input, resized, DESIRED_WIDTH);
    
    // display resized image
    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display window", resized);
    
    // gray image
    Mat gray(resized.size(), CV_8U);
    
    // convert to gray
    cvtColor(resized, gray, CV_BGR2GRAY);
    
    // display gray image
    if (SHOW_STEPS)
    {
        imshow("Gray image", gray);
    }
    
    // blurred image
    Mat blurred(gray.size(), gray.type());
    
    // blur the image
    blur(gray, blurred, Size(20, 20));
    
    // display blurred image
    if (SHOW_STEPS)
    {
        imshow("Blurred image", blurred);
    }
    
    // binary input
    Mat binary(blurred.size(), blurred.type());
    
    // apply thresholding
    threshold(blurred, binary, 128, 255, THRESH_BINARY);
    
    // display binary image
    if (SHOW_STEPS)
    {
        imshow("Binary image", binary);
    }
    
    // contour detection starts here
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Scalar green(0, 255, 0);
    Scalar red(0, 0, 255);
    
    // find contours
    findContours(binary, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
    
    // result image
    Mat result;
    
    // convert binary to color
    cvtColor(binary, result, CV_GRAY2BGR);
    
    // find largest contour index
    int largest_contour_index = findLargestContourIndex(contours);
    
    // largest contour convex hull
    vector<vector<Point>> hull(1);
    
    // find convex hull for largest contour
    convexHull(Mat(contours[largest_contour_index]), hull[0], false);
    
    // draw largest contour and convex hull
    if (DRAW_CONTOURS)
    {
        drawContours(result, contours, largest_contour_index, green, 4);
    }
    drawContours(result, hull, 0, red, 4);
    
    // display result image
    imshow("Result image", result);
}

int main(int argc, char** argv)
{
    // original image
    Mat input;
    
    // load input image
    input = imread("/Users/danielrudczuk/Desktop/a4_sheet.jpg");
    
    // find paper sheet and draw corners
    findCorners(input);
    
    // wait for key and exit
    waitKey(0);
    return 0;
}

