/**============================================================================
 * @file        : test.cpp
 * @author      : Rishabh Choudhary, Akash Atharv
 * @version     : 1.0
 * @copyright   : MIT License
 * Copyright 2018 Rishabh Choudhary, Akash Atharv
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction,including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE 
USE OR OTHER DEALINGS IN THE SOFTWARE. 
 * @brief        Contains Test and mock cases for testing prediction heading generated
 *============================================================================
 */
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <string>
#include <vector>
#include "opencv2/opencv.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "../include/imageProcessor.hpp"
#include "../include/lanes.hpp"
using::testing::_;
/**
 * @brief Class Mocklanes
 * The class Mocklanes is used for defining GMock methods
 */
class Mocklanes : public lanes {
 public:
  /* Mock method for the function is defined */
       MOCK_METHOD3(lanePrediction, std::string(cv::Vec4f leftLine,
       cv::Vec4f rightLine, std::vector<cv::Point> outputLines));
};

/**
 *@brief Function implentation to generate heading for a single frame
 *@param frameNumber is used to specify the frame to be tested 
 *@return testHeading which is a string that outputs the heading generated
 */

std::string testHeading(int frameNumber) {
      lanes img;
      cv::Mat originalImage;
      cv::Mat maskImage;
      cv::Mat frame;
      cv::Mat separateImage;
      std::vector<cv::Vec4i> lines;
      std::vector<cv::Point> rightPts;
      std::vector<cv::Point> leftPts;
      std::vector<cv::Point> outputLines;

      cv::VideoCapture cap("../data/Lane Detection Test Video 01.mp4");
      cap.set(cv::CAP_PROP_POS_FRAMES, frameNumber);
      cap.read(frame);
      img.setOriginalImage(frame);
      img.rgbToGray(frame);
      img.noiseFilter(img.getGrayImage());
      img.edgeDetector(img.getNoiseImage());
      cv::Mat mask = cv::Mat::zeros(img.getEgdeImage().size(),
      img.getEgdeImage().type());
      cv::Point pts[4] = {
        cv::Point(150, 718),
        cv::Point(600, 530),
        cv::Point(650, 530),
        cv::Point(1000, 718)
    };
      cv::fillConvexPoly(mask, pts, 4, cv::Scalar(255, 0, 0));
      cv::bitwise_and(img.getEgdeImage(), mask, maskImage);
      img.grayToRGB(img.getEgdeImage());
      lines = img.houghTransform(maskImage, img.getHoughImage());
      separateImage = img.lineSeparation(lines, img.getEgdeImage());
      outputLines = img.fitLine(rightPts, leftPts);
      img.showOutput(img.prediction, frame, outputLines);
      return(img.prediction);
}

/**
 *@brief Case to test for straight direction prediction
 *@param none
 *@return none
 */

TEST(LaneHeadingTest, Vehicle_go_straight) {
      EXPECT_EQ(testHeading(600), "Heading Straight");
}

/**
 *@brief Case to test for right turn direction prediction
 *@param none
 *@return none
 */

TEST(LaneHeadingTest, Vehicle_right_turn) {
      EXPECT_EQ(testHeading(100), "Heading Right");
}

/**
 *@brief Case to test for left turn direction prediction
 *@param none
 *@return none
 */

TEST(LaneHeadingTest, Vehicle_left_turn) {
      EXPECT_EQ(testHeading(455), "Heading Left");
}
/**
 *@brief Mock test for class lanes
 *@param none
 *@return none
 */
TEST(GMock, Function_should_be_called) {
/* Object for mocking is created */
      Mocklanes mock;
/* Condition for checking the mock is implemented */
      EXPECT_CALL(mock, lanePrediction(_, _, _)).Times(1);
      std::vector<cv::Point> rightPts;
      std::vector<cv::Point> leftPts;
/* fitLine Function is called for verifying */
      mock.fitLine(leftPts, rightPts);
}
