/**
 *  MIT License
 *
 *  Copyright (c) 2018 Rishabh Choudhary
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without
 *  limitation the rights to use, copy, modify, merge, publish, distribute,
 *  sublicense, and/or sell copies of the Software, and to permit persons to
 *  whom the Software is furnished to do so, subject to the following
 *  conditions:
 *
 *  The above copyright notice and this permission notice shall be included
 *  in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 *
 *  @file    imageProcessor.cpp
 *  @author  Rishabh Choudhary
 *  @copyright MIT License
 *
 *  @brief  ENPM808X :Assignment to mock classes using googlemock framework
 *
 *  @section DESCRIPTION
 *
 *  THis file contains the mock class definition and test cases
 *
 */

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

using ::testing::_;

class mockImageProcessor : public imageProcessor {
 public:
    MOCK_METHOD0(getEgdeImage, cv::Mat());
    MOCK_METHOD1(rgbToGray, cv::Mat(cv::Mat));
    MOCK_METHOD1(noiseFilter, cv::Mat(cv::Mat));
};

TEST(imageProcessorTest, edgeDetectorTest) {
    mockImageProcessor mock;
    ::testing::Expectation init = EXPECT_CALL(mock, rgbToGray(_)).Times(1);
    EXPECT_CALL(mock, noiseFilter(_)).After(init);

    cv::Mat img = cv::imread("../data/originalImage.png");
    mock.edgeDetector(img);
}

TEST(imageProcessorTest, fetchImageTest) {
    mockImageProcessor mock;
    ::testing::Expectation init = EXPECT_CALL(mock, getEgdeImage()).Times(1);
    cv::Mat img = cv::imread("../data/originalImage.png");

    mock.grayToRGB(img);
}
