/**============================================================================
 * @file       : imageProcessor.cpp
 * @author     : Rishabh Choudhary, Akash Atharv
 * @version    : 1.0
 * @copyright  : MIT License
 * Copyright 2018 Rishabh Choudhary, Akash Atharv
 * @brief      : Contains function definitions of the class imageProcessor
 *============================================================================
 */

#include "../include/imageProcessor.hpp"

imageProcessor::imageProcessor() {
}

imageProcessor::~imageProcessor() {
}
cv::Mat imageProcessor::getOriginalImage() {
        return originalImage;
}
cv::Mat imageProcessor::getGrayImage() {
        return grayImage;
}
cv::Mat imageProcessor::getNoiseImage() {
        return noiseImage;
}
cv::Mat imageProcessor::getEgdeImage() {
        return edgeImage;
}
cv::Mat imageProcessor::getHoughImage() {
        return houghImage;
}
void imageProcessor::setOriginalImage(cv::Mat image) {
        originalImage = image;
}

cv::Mat imageProcessor::rgbToGray(cv::Mat originalImage) {
        cv::cvtColor(originalImage, grayImage, CV_BGR2GRAY);
        return grayImage;
}
cv::Mat imageProcessor::grayToRGB(cv::Mat edgeImage) {
        cv::cvtColor(edgeImage, houghImage, CV_GRAY2BGR);
        return houghImage;
}

cv::Mat imageProcessor::noiseFilter(cv::Mat grayImage) {
        /*
         * Apply Gaussian blur with kernel size 3
         */
        cv::GaussianBlur(grayImage, noiseImage, cv::Size(3, 3), 0, 0);
        return noiseImage;
}
cv::Mat imageProcessor::edgeDetector(cv::Mat noiseImage) {
        int lowThreshold = 100;
        int ratio = 3;
        int kernelSize = 3;
        cv::Canny(noiseImage, edgeImage, lowThreshold,
        lowThreshold*ratio, kernelSize);
        return edgeImage;
}

std::vector<cv::Vec4i> imageProcessor::houghTransform(cv::Mat
maskImage, cv::Mat houghImage) {
        std::vector<cv::Vec4i> lines;
  /* Apply hough transform with given parameters
   * maxGapLenghth: 300
   * minSegmentLength = 20
   * min Number of votes = 20
   * The paramteres are calculated by hit and trial
   */
        cv::HoughLinesP(maskImage, lines, 1, CV_PI/180, 20 , 20, 300);
        for (auto i : lines) {
                cv::line(houghImage, cv::Point(i[0], i[1]),
                cv::Point(i[2], i[3]), cv::Scalar(0, 0, 255), 3, CV_AA);
        }
        return lines;
}
