//
//  SheetDetection.cpp
//  VRHouseFramework
//

#include "SheetDetection.hpp"

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

vector<Point2f> SheetDetection::findCorners(InputArray input) {
    // gray image
    Mat gray(input.size(), CV_8U);

    // convert to gray
    #if CV_MAJOR_VERSION == 3
    cvtColor(input, gray, CV_BGR2GRAY);
    #elif CV_MAJOR_VERSION == 4
    cvtColor(input, gray, COLOR_BGR2GRAY);
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

    // find the largest contour, if any
    if (contours.size() < 1) {
        vector<Point2f> emptyVector;
        return emptyVector;
    }

    int largestContourIndex = findLargestContourIndex(contours);
    vector<Point> largestContour = contours[largestContourIndex];

    // find four corners
    RotatedRect rect = minAreaRect(largestContour);
    Point2f corners[4];
    rect.points(corners);

    // convert the array to a vector
    vector<Point2f> vector(begin(corners), end(corners));

    return vector;
}
