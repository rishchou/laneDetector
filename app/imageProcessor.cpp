/*
 * imageProcessor.cpp
 *
 *  Created on: Oct 15, 2018
 *      Author: viki
 */

#include "../include/imageProcessor.hpp"

imageProcessor::imageProcessor() {
	// TODO Auto-generated constructor stub
}

imageProcessor::~imageProcessor() {
	// TODO Auto-generated destructor stub
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
/*
cv::Mat imageProcessor::getImageCentre() {
	return imageCentre;
}

void imageProcessor::setImageCentre(double ic) {
	ic = imageCentre;
}
*/
cv::Mat imageProcessor::rgbToGray(cv::Mat originalImage) {
	cv::cvtColor(originalImage, grayImage, CV_BGR2GRAY);
	return grayImage;
}
cv::Mat imageProcessor::grayToRGB(cv::Mat edgeImage) {

	cv::cvtColor(edgeImage, houghImage, CV_GRAY2BGR);
	return houghImage;
}

cv::Mat imageProcessor::noiseFilter(cv::Mat grayImage) {
	cv::GaussianBlur(grayImage, noiseImage, cv::Size(3,3), 0, 0);
	return noiseImage;
}
cv::Mat imageProcessor::edgeDetector(cv::Mat noiseImage) {
	int lowThreshold = 100;
	int ratio = 3;
	int kernelSize = 3;
	cv::Canny( noiseImage, edgeImage, lowThreshold, lowThreshold*ratio, kernelSize );

	return edgeImage;

}

std::vector<cv::Vec4i> imageProcessor::houghTransform(cv::Mat maskImage, cv::Mat houghImage) {

	std::vector<cv::Vec4i> lines;
	cv::HoughLinesP(maskImage, lines, 1, CV_PI/180, 30 , 30, 10);
	for(auto i : lines) {
		cv::line( houghImage, cv::Point(i[0], i[1]), cv::Point(i[2], i[3]), cv::Scalar(0,0,255), 3, CV_AA);
	}
	return lines;

}
