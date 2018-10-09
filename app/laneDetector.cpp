/**============================================================================
 * @file         laneDetector.cpp
 * Author      : Rishabh Choudhary, Akash Atharv
 * Version     : 1.0
 * @Copyright  : MIT License
 * Copyright 2018 Rishabh Choudhary, Akash Atharv
 * @brief        Stub functions implementation for laneDetector class
 *============================================================================
 */

#include <string>
#include <vector>
#include "opencv2/opencv.hpp"
#include "../include/laneDetector.hpp"
#define UNUSED(expr) do { (void)(expr); } while (0)

float sampleData[10] = { 1, 2, 3, 4, 5, 6, 7, 8 };
cv::Mat sample = cv::Mat(2, 4, CV_32F, sampleData);
std::vector<cv::Vec4i> vec;
std::vector<std::vector<cv::Vec4i> > vec1;
std::vector<cv::Point> point;

cv::Mat rgbToGray(cv::Mat /*originalImage*/) {
	return sample;
}

cv::Mat noiseFilter(cv::Mat /*grayImage*/) {
	return sample;
}

cv::Mat edgeDetector(cv::Mat /*noiseImage*/) {
	return sample;
}

cv::Mat mask(cv::Mat /*maskImage*/) {
	return sample;
}
 
std::vector<cv::Vec4i> houghTransform(cv::Mat /*maskImage*/) {
	return vec;	
}

std::vector<std::vector<cv::Vec4i> > lineSegregation(std::vector<cv::Vec4i> /*lines*/, cv::Mat /*edgeImage*/) {
	return vec1;
}

std::vector<cv::Point> regression(std::vector<std::vector<cv::Vec4i> > /*leftRightLines*/, cv::Mat /*originalImage*/) {
	return point;
}

void showLanes(cv::Mat /*originalImage*/, std::vector<cv::Point> /*lane*/) {
	return;
}
 
