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

vector<Point> SheetDetection::findCorners(InputArray input) {
    // gray image
    Mat src(input.size(), CV_8U);

    Mat gray = src.clone();

    // convert to gray
    #if CV_MAJOR_VERSION == 3
    cvtColor(input, gray, CV_BGR2GRAY);
    #elif CV_MAJOR_VERSION == 4
    cvtColor(input, gray, COLOR_BGR2GRAY);
    #endif

    // blurred image
    Mat blurred(gray.size(), gray.type());

    // blur the image
    bilateralFilter(gray, blurred, 9, 100, 100);

    // binary input
    Mat binary(blurred.size(), blurred.type());

    // apply thresholding
    threshold(blurred, binary, 155, 255, THRESH_BINARY);
    Mat edges;
    Canny(binary, edges, 175, 255);

    // contour detection starts here
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    // find contours
    #if CV_MAJOR_VERSION == 3
    findContours(edges, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
    #elif CV_MAJOR_VERSION == 4
    findContours(edges, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    #endif

    // find the largest contour, if any
    if (contours.size() < 1) {
        vector<Point> emptyVector;
        return emptyVector;
    }

    int largestContourIndex = findLargestContourIndex(contours);
    vector<Point> largestContour = contours[largestContourIndex];

    // find corners
    vector<Point> hull;
    convexHull(largestContour, hull);

    // get only extreme conrners
    auto topLeftBottomRight = std::minmax_element(hull.begin(), hull.end(), [](const Point &a, const Point &b) {
        return (a.x + a.y) < (b.x + b.y);
    });

    auto topRightBottomLeft = minmax_element(hull.begin(), hull.end(), [](const Point &a, const Point &b) {
        return (a.x - a.y) > (b.x - b.y);
    });

    return {*topLeftBottomRight.first, *topRightBottomLeft.first, *topLeftBottomRight.second, *topRightBottomLeft.second};
}
