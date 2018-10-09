/**============================================================================
 * @file         laneDetector.hpp
 * Author      : Rishabh Choudhary, Akash Atharv
 * Version     : 1.0
 * @Copyright  : MIT License
 * Copyright 2018 Rishabh Choudhary, Akash Atharv
 * @brief        Class declaration for laneDetector
 *============================================================================
 */


#ifndef LANE_H
#define LANE_H

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "opencv2/opencv.hpp"


class laneDetector {
    private:
        cv::Mat originalImage;           /* Input image */
        cv::Mat grayImage;		 /* Grayscale image */
        cv::Mat noiseImage;              /* Noise filtered image */  
        cv::Mat edgeImage; 		 /* Image after edge detection */
        cv::Mat maskImage;		 /* ROI image */
        std::vector<cv::Vec4i> lines;	 /* Hough transform generated lines */
	std::vector<std::vector<cv::Vec4i> > leftRightLines;   /* Separated left and right lines */ 
	std::vector<cv::Point> lane;     /* generated line after regression */
        double imageCentre;		 /* Center of the original image */
	cv::Point leftB;		 /* y = m1*x + b1, constant of left line */
	cv::Point rightB;		 /* y = m2*x + b2, constant of right line */
	double leftSlope;		 /* Slope of left line */
	double rightSlope;		 /* Slope of right line */

    public:
	/**
   	 * @brief converts rgb image to grayscale image
   	 * @param input rgb image
   	 * @return output grayscale image
   	 */
        cv::Mat rgbToGray(cv::Mat originalImage);
	
	/**
         * @brief filters noise from given input image
         * @param input grayscale image
         * @return noise filtered image
         */
        cv::Mat noiseFilter(cv::Mat grayImage);
        /**
         * @brief detect edges from input image
         * @param input noise filtered image
         * @return output edge detected image
         */

	cv::Mat edgeDetector(cv::Mat noiseImage);
	/**
         * @brief generate region of interest from input image
         * @param input edge detected image
         * @return output masked image
         */

	cv::Mat mask(cv::Mat edgeImage); 
	/**
         * @brief generate lines from roi image
         * @param roi image
         * @return output lines
         */

	std::vector<cv::Vec4i> houghTransform(cv::Mat maskImage);
	/**
         * @brief separate the lines from edge detected image
         * @param edge detected image
         * @return separated lines
         */

	std::vector<std::vector<cv::Vec4i> > lineSegregation(std::vector<cv::Vec4i> lines, cv::Mat edgeImage);
	/**
         * @brief Regress the left and right lines wrt original image  
         * @param input rgb image
	 * @param left right lines
         * @return output regressed line
         */

	std::vector<cv::Point> regression(std::vector<std::vector<cv::Vec4i> > leftRightLines, cv::Mat originalImage);
	/**
         * @brief shows output lanes superimposed on original image
         * @param input rgb image
         * @param lane line		
         * @return none
         */

	void showLanes(cv::Mat originalImage, std::vector<cv::Point> lane);		
};

#endif	 	
