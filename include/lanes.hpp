/*
 * lanes.hpp
 *
 *  Created on: Oct 15, 2018
 *      Author: viki
 */

#ifndef INCLUDE_LANES_HPP_
#define INCLUDE_LANES_HPP_

#include <imageProcessor.hpp>

class lanes: public imageProcessor {
public:
	lanes();
	virtual ~lanes();
	std::vector<cv::Vec4i> getLeftLines() { return leftLines; }
	std::vector<cv::Vec4i> getRightLines() { return rightLines; }
	cv::Mat lineSeparation(std::vector<cv::Vec4i>, cv::Mat);
	std::vector<cv::Point> fitLine(std::vector<cv::Point>, std::vector<cv::Point>);
	std::string lanePrediction(cv::Vec4f, cv::Vec4f, std::vector<cv::Point>);
	std::string prediction;
	void showOutput(std::string, cv::Mat, std::vector<cv::Point>);
private:
	cv::Point rightB;
	cv::Point leftB;
	double rightSlope;
	double leftSlope;
	std::vector<cv::Vec4i> rightLines;
	std::vector<cv::Vec4i> leftLines;
};

#endif /* INCLUDE_LANES_HPP_ */
