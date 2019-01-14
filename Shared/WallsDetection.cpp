//
//  WallsDetection.cpp
//  VRHouseFramework
//

#include "WallsDetection.hpp"

int MAX_LENGTH = 800;

vector<vector<cv::Point>> WallsDetection::findWalls(cv::Mat input) {
    Mat img = input.clone();

    // Scale as threshold and dilate parameters works best for images up to 800x800.
    int height = img.rows;
    int width = img.cols;
    bool isTall = height > width;
    int newHeight = isTall ? MAX_LENGTH : (int)(((float)MAX_LENGTH / (float)width) * (float)height);
    int newWidth = isTall ? (int)(((float)MAX_LENGTH / (float)height) * (float)width) : MAX_LENGTH;
    float scale = (float)newHeight / (float)height;

    resize(img, img, Size(newWidth, newHeight));

    threshold(img, img, 245, 255, THRESH_BINARY);
    dilate(img, img, cv::Mat());
    dilate(img, img, cv::Mat());

    Mat dst, cdst;
    Canny(img, dst, 50, 200, 3);
    cvtColor(dst, cdst, COLOR_GRAY2BGR);

    vector<Vec4i> lines;
    HoughLinesP(dst, lines, 1, CV_PI/180, 10, 5, 20);

    vector<vector<cv::Point>> linesToReturn;

    for (size_t i = 0; i < lines.size(); i++) {
        Vec4i l = lines[i];
        int x1 = int(l[0] / scale);
        int y1 = int(l[1] / scale);
        int x2 = int(l[2] / scale);
        int y2 = int(l[3] / scale);

        vector<cv::Point> wall = { Point(x1, y1), Point(x2, y2) };
        linesToReturn.push_back(wall);
    }

    return linesToReturn;
}
