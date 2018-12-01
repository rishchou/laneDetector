/**============================================================================
 * @file       : imageProcessor.hpp
 * @author     : Rishabh Choudhary, Akash Atharv
 * @version    : 1.0
 * @copyright  : MIT License
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
 * @brief      : Contains function and variable declarations of the class imageProcessor
 *============================================================================
 */

#ifndef INCLUDE_IMAGEPROCESSOR_HPP_
#define INCLUDE_IMAGEPROCESSOR_HPP_


#include <iostream>
#include <string>
#include <vector>
#include "opencv2/opencv.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

/**
 * @brief Class imageProcessor
 * The class imageProcessor deals with the initial processing
 * algorithms to be performed on the frame before the lines detected  
 * are processed further
 */

class imageProcessor {
 public:
        /**
         * @brief constructor for imageProcessor
         * @param none
         * @return none
         */
        imageProcessor();
        /**
         * @brief destructor for imageProcessor
         * @param none
         * @return none
         */
        virtual ~imageProcessor();
        /**
         * @brief function for retrieving original frame
         * @param none
         * @return original input image
         */
        cv::Mat getOriginalImage();
        /**
         * @brief function for retrieving grayscale frame
         * @param none
         * @return Grayscale image
         */
        cv::Mat getGrayImage();
        /**
         * @brief function for retrieving Noise filtered frame
         * @param none
         * @return Noise filtered image
         */
        cv::Mat getNoiseImage();
        /**
         * @brief function for retrieving edge detected frame
         * @param none
         * @return Image after edge detection
         */
        cv::Mat getEgdeImage();
        /**
         * @brief function for retrieving Hough transformed frame
         * @param none
         * @return Image with Hough transform generated lines
         */
        cv::Mat getHoughImage();
        /**
         * @brief function for retrieving and setting
         * the captured frame from video as input image
         * @param original input frame
         * @return none
         */
        void setOriginalImage(cv::Mat);
	/**
   	 * @brief converts rgb image to grayscale image
   	 * @param input rgb image
   	 * @return output grayscale image
   	 */
        cv::Mat rgbToGray(cv::Mat);
	/**
   	 * @brief converts grayscale image to rgb image
   	 * @param input grayscale image
   	 * @return output rgb image
   	 */
        cv::Mat grayToRGB(cv::Mat);
	/**
         * @brief filters noise from given input image
         * @param input grayscale image
         * @return noise filtered image
         */
        cv::Mat noiseFilter(cv::Mat);
        /**
         * @brief detect edges from input image
         * @param input noise filtered image
         * @return output edge detected image
         */
        cv::Mat edgeDetector(cv::Mat);
	/**
         * @brief generate lines from roi image
         * @param roi image
         * @return output lines
         */
        std::vector<cv::Vec4i> houghTransform(cv::Mat, cv::Mat);

 private:
        cv::Mat originalImage;       /* Input frame */
        cv::Mat grayImage;           /* Grayscale image */
        cv::Mat noiseImage;          /* Noise filtered image */
        cv::Mat edgeImage;           /* Edge detected Image */
        cv::Mat houghImage;          /* Hough transformed image */
};

#endif /* INCLUDE_IMAGEPROCESSOR_HPP_ */
