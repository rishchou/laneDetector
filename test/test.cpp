/**============================================================================
 * @file        : test.cpp
 * @author      : Rishabh Choudhary, Akash Atharv
 * @version     : 1.0
 * @copyright   : MIT License
 * Copyright 2018 Rishabh Choudhary, Akash Atharv
 * @brief        Contains Test cases for testing prediction heading generated
 *============================================================================
 */
#include <gtest/gtest.h>
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

      cv::VideoCapture cap("../data/Vehicle Detection Raw Video.mp4");
      cap.set(cv::CAP_PROP_POS_FRAMES, frameNumber);
      cap.read(frame);
      img.setOriginalImage(frame);
      img.rgbToGray(frame);
      img.noiseFilter(img.getGrayImage());
      img.edgeDetector(img.getNoiseImage());
      cv::Mat mask = cv::Mat::zeros(img.getEgdeImage().size(),
      img.getEgdeImage().type());
      cv::Point pts[4] = {
        cv::Point(0, 831),
        cv::Point(629, 465),
        cv::Point(756, 472),
        cv::Point(1195, 711)
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
      EXPECT_EQ(testHeading(100), "Straight");
}

/**
 *@brief Case to test for right turn direction prediction
 *@param none
 *@return none
 */

TEST(LaneHeadingTest, Vehicle_right_turn) {
      EXPECT_EQ(testHeading(600), "Right Turn");
}

/**
 *@brief Case to test for left turn direction prediction
 *@param none
 *@return none
 */

TEST(LaneHeadingTest, Vehicle_left_turn) {
      EXPECT_EQ(testHeading(1), "Left Turn");
}



