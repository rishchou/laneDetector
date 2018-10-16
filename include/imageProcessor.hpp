/*
 * imageProcessor.hpp
 *
 *  Created on: Oct 15, 2018
 *      Author: viki
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

class imageProcessor {
 public:

	imageProcessor();
	virtual ~imageProcessor();
	cv::Mat getOriginalImage();
	cv::Mat getGrayImage();
	cv::Mat getNoiseImage();
	cv::Mat getEgdeImage();
	cv::Mat getHoughImage();
//	cv::Mat getImageCentre();
	//void setImageCentre(double ic);
	void setOriginalImage(cv::Mat);
	cv::Mat rgbToGray(cv::Mat);
	cv::Mat grayToRGB(cv::Mat);
	cv::Mat noiseFilter(cv::Mat);
	cv::Mat edgeDetector(cv::Mat);
	std::vector<cv::Vec4i> houghTransform(cv::Mat, cv::Mat);

 private:
	cv::Mat originalImage;
	cv::Mat grayImage;
	cv::Mat noiseImage;
	cv::Mat edgeImage;
	cv::Mat houghImage;
	//double imageCentre;
};

#endif /* INCLUDE_IMAGEPROCESSOR_HPP_ */
