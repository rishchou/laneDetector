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
 *  @file    demo.cpp
 *  @author  Rishabh Choudhary
 *  @copyright MIT License
 *
 *  @brief  ENPM808X :MIdterm project on Traffic lane detection
 *
 *  @section DESCRIPTION
 *
 *  THis file runs the demo of the code
 *
 */


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
 *@brief Function main that runs the main algorithm of the lane detection.
 *@brief It will read a video of a car in the highway and it will output the
 *@brief same video but with the plotted detected lane
 *@param argv[] is a string to the full path of the demo video
 *@return 0 for successful execution, -1 for failed execution
 */

int main(int argc, char* argv[]) {
    std::string inputVideo;
    cv::Mat originalImage;
    double i = 0;
    cv::Mat maskImage;
    cv::Mat frame;
    cv::Mat separateImage;
    /* If number of arguments specified is incorrect, return */
    if ( argc != 2 ) {
        std::cout << "Wrong usage : PLease"
        "specify Input video clip with the"
        " program as argument" << std::endl;
        return -1;
    }

    inputVideo = argv[1];

    /* Capture the video clip into inputVideo */
    cv::VideoCapture cap(inputVideo);

    /* If not able to open video file, return */
    if (!cap.isOpened()) return -1;

    while (i < cap.get(CV_CAP_PROP_FRAME_COUNT)) {
        // Read video frame by frame
        if (!cap.read(frame)) { break; }
        originalImage = frame;

        /* Initialize object for class lanes */
        lanes img;

        /* Set the class member originalImage to input frame */
        img.setOriginalImage(originalImage);

        /* Create a window for display */
        cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);

        /* Convert the original RGB format image to GrayScale */
        img.rgbToGray(originalImage);

        /* Display the grayscale image */
        cv::imshow("Display GrayScale Image", img.getGrayImage());

        /* Filter the grayscale image to reduce noise */
        img.noiseFilter(img.getGrayImage());

        /* Display the noise filtered image */
        cv::imshow("Display Noise filtered Image", img.getNoiseImage());

        /* Apply canny edge detection to noise filtered image to detect edges */
        img.edgeDetector(img.getNoiseImage());

        /* Display the edge detected image */
        cv::imshow("Display Canny edge", img.getEgdeImage());

        cv::Mat mask = cv::Mat::zeros
        (img.getEgdeImage().size(), img.getEgdeImage().type());

        /* Define the points for region of interest */
        cv::Point pts[4] = {
        cv::Point(150, 718),
        cv::Point(600, 530),
        cv::Point(650, 530),
        cv::Point(1000, 718)
        };

        /* Create a mask given by the points above */
        cv::fillConvexPoly(mask, pts, 4, cv::Scalar(255, 0, 0));

        /**
         * Superimpose mask with the edge detected
         * image to generate region of interest image
         */
        cv::bitwise_and(img.getEgdeImage(), mask, maskImage);

        /** Convert back the grayscale image to RGB for inputting into
         *  Hough transform
         */
        img.grayToRGB(img.getEgdeImage());
        cv::imshow("Display Region of interest", maskImage);

        /* Apply hough transform on masked Image to generate lines */
        std::vector<cv::Vec4i> lines;
        lines = img.houghTransform(maskImage, img.getHoughImage());

        /* Display generated lines given by Hough Transform */
        cv::imshow("Display hough lines", img.getHoughImage());

        /* Separate right and left lines on the road */
        separateImage = img.lineSeparation(lines, img.getEgdeImage());

        /* Display the right and left line */
        cv::imshow("Display separated lines", separateImage);

        std::vector<cv::Point> rightPts;
        std::vector<cv::Point> leftPts;
        std::vector<cv::Point> outputLines;

       /** Apply linear regression on the set of points obtained from
        *  separated lines to generate one line on left and right side which form the lane
        */
       outputLines = img.fitLine(rightPts, leftPts);

       /*
        * Display output lines along with predicted text
        */
       img.showOutput(img.prediction, originalImage, outputLines);
       cv::waitKey(5);
       i++;
       }

    cv::waitKey(0);

    return 0;
}
