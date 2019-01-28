//
//  WallsDetection.cpp
//  VRHouseFramework
//

#include "WallsDetection.hpp"

vector<vector<cv::Point>> WallsDetection::findWalls(cv::Mat input) {
    Mat img = input.clone();

    threshold(img, img, 210, 255, THRESH_BINARY);

    int an = 2;
    Mat closeElement = getStructuringElement(MORPH_RECT, Size(an*2+1, an*2+1), Point(an, an));
    Mat openElement = getStructuringElement(MORPH_RECT, Size(an*2, an*2), Point(an, an));
    morphologyEx(img, img, MORPH_CLOSE, closeElement);
    morphologyEx(img, img, MORPH_OPEN, openElement);

    Mat dst, cdst;
    Canny(img, dst, 50, 200, 3);
    cvtColor(dst, cdst, COLOR_GRAY2BGR);

    vector<Vec4i> lines;
    HoughLinesP(dst, lines, 1, CV_PI/180, 10, 5, 20);

    vector<vector<cv::Point>> linesToReturn;

    for (size_t i = 0; i < lines.size(); i++) {
        Vec4i l = lines[i];
        vector<cv::Point> wall = { Point(l[0], l[1]), Point(l[2], l[3]) };
        linesToReturn.push_back(wall);
    }

    return linesToReturn;
}
