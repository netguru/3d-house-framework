//
//  SheetDetection.cpp
//  VRHouseFramework
//

#include "SheetDetection.hpp"

const int DESIRED_WIDTH = 640;

void SheetDetection::resizeWithRatio(InputArray input, OutputArray result, int desiredWidth) {
    float ratio = (float)input.rows() / input.cols();
    Size resultSize = Size(desiredWidth, (int)(desiredWidth * ratio));

    resize(input, result, resultSize);
}

int SheetDetection::findLargestContourIndex(vector<vector<Point>> contours) {
    double largestArea = 0;
    int largestContourIndex = 0;

    for (int i = 0; i < int(contours.size()); i++) {
        double a = contourArea(contours[i], false);
        if (a > largestArea) {
            largestArea = a;
            largestContourIndex = i;
        }
    }

    return largestContourIndex;
}

vector<Point> SheetDetection::findCorners(InputArray input) {
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
    #if CV_MAJOR_VERSION == 3
    cvtColor(resized, gray, CV_BGR2GRAY);
    #elif CV_MAJOR_VERSION == 4
    cvtColor(resized, gray, COLOR_BGR2GRAY);
    #endif

    // blurred image
    Mat blurred(gray.size(), gray.type());

    // blur the image
    blur(gray, blurred, Size(20, 20));

    // binary input
    Mat binary(blurred.size(), blurred.type());

    // apply thresholding
    threshold(blurred, binary, 128, 255, THRESH_BINARY);

    // contour detection starts here
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Scalar green(0, 255, 0);
    Scalar red(0, 0, 255);

    // find contours
    #if CV_MAJOR_VERSION == 3
    findContours(binary, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
    #elif CV_MAJOR_VERSION == 4
    findContours(binary, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    #endif

    // find largest contour index
    int largestContourIndex = findLargestContourIndex(contours);

    return contours[largestContourIndex];
}
