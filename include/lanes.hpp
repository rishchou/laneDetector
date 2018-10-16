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
	~lanes();
	std::vector<cv::Vec4i> getLeftLines() { return leftLines; }
	std::vector<cv::Vec4i> getRightLines() { return rightLines; }
	cv::Mat lineSeparation(std::vector<cv::Vec4i>, cv::Mat);
	std::vector<cv::Point> fitLine(std::vector<cv::Point>, std::vector<cv::Point>);
	std::string lanePrediction(cv::Vec4f, cv::Vec4f, std::vector<cv::Point>);
	std::string prediction;
	void showOutput(std::string, cv::Mat, std::vector<cv::Point>);
private:
	cv::Point rightB;       /* y = mX + B */     /* B of right line */
	cv::Point leftB;		/* B of left line */
	double rightSlope;	    /* slope of right line */
	double leftSlope;		/* slope of left line */
	std::vector<cv::Vec4i> rightLines;	/* Set of right lines */
	std::vector<cv::Vec4i> leftLines;   /* Set of left lines */
};

#endif /* INCLUDE_LANES_HPP_ */
