/*
 * lanes.cpp
 *
 *  Created on: Oct 15, 2018
 *      Author: viki
 */

#include <lanes.hpp>

lanes::lanes() {
	// TODO Auto-generated constructor stub
 leftSlope = 0;
 rightSlope = 0;
}

lanes::~lanes() {
	// TODO Auto-generated destructor stub
}

cv::Mat lanes::lineSeparation(std::vector<cv::Vec4i> lines, cv::Mat image) {
	cv::Mat separateImage;
	std::vector<double> slopes;
//	std::vector<cv::Vec4i> leftRightLines;
//	std::vector<cv::Vec4i> rightLines, leftLines;

	double slopeThreshold = 0.1;
	double xCentre = double(image.cols/2);
	std::cout << "image center " << xCentre << std::endl;


	cvtColor(image, separateImage, CV_GRAY2BGR);
	for (auto i : lines) {
		cv::Point pt1 = cv::Point(i[0], i[1]);
		cv::Point pt2 = cv::Point(i[2], i[3]);
		std::cout << pt1.x <<" "<< pt1.y<<" " << pt2.x<< " " << pt2.y<<" " << std::endl;
	    double slope = (double(pt2.y - pt1.y)/double(pt2.x - pt1.x));
		std::cout << "Slope of line " << abs(slope) << std::endl;
	    if (std::abs(slope) < slopeThreshold) {
	    	continue;
		}
		if((slope < 0) && (pt1.x < xCentre) && (pt2.x < xCentre)) {
			leftLines.emplace_back(i);
	        cv::line(separateImage, pt1, pt2, cv::Scalar(255,0,0), 3, CV_AA);
	    } else if(slope > 0 && (pt1.x > xCentre) && (pt2.x > xCentre)) {
	        rightLines.emplace_back(i);
	        cv::line(separateImage, pt1, pt2, cv::Scalar(0,255,0), 3, CV_AA);
		}
	}
	return separateImage;
}
std::vector<cv::Point> lanes::fitLine(std::vector<cv::Point> rightPts, std::vector<cv::Point> leftPts) {

	cv::Vec4f leftLine;
	cv::Vec4f rightLine;

	for(auto i : leftLines) {
			leftPts.emplace_back(cv::Point(i[0], i[1]));
			leftPts.emplace_back(cv::Point(i[2], i[3]));
		}

		if (leftPts.size() > 0) {
			cv::fitLine(leftPts, leftLine, CV_DIST_L2, 0, 0.01, 0.01);
			leftB = cv::Point(leftLine[2], leftLine[3]);
			leftSlope = double(leftLine[1])/double(leftLine[0]);
		}

		for (auto i : rightLines) {
			rightPts.emplace_back(cv::Point(i[0], i[1]));
			rightPts.emplace_back(cv::Point(i[2], i[3]));
		}

		if (rightPts.size() > 0) {
	        cv::fitLine(rightPts, rightLine, CV_DIST_L2, 0, 0.01, 0.01);
	        rightB = cv::Point(rightLine[2], rightLine[3]);
	        rightSlope = double(rightLine[1])/double(rightLine[0]);
	    }

		double bottomY = getOriginalImage().rows-1;
		double topY = 475;

		double rightInterceptX0 = ((bottomY - rightB.y) / rightSlope) + rightB.x;
		double rightInterceptX1 = ((topY - rightB.y) / rightSlope) + rightB.x;

		double leftInterceptX0 = ((bottomY - leftB.y) / leftSlope) + leftB.x;
		double leftInterceptX1 = ((topY - leftB.y) / leftSlope) + leftB.x;

	    std::vector<cv::Point> outputLines(4);

		outputLines[0] = cv::Point(rightInterceptX0, bottomY);
		outputLines[1] = cv::Point(rightInterceptX1, topY);
		outputLines[2] = cv::Point(leftInterceptX0, bottomY);
		outputLines[3] = cv::Point(leftInterceptX1, topY);

		prediction = lanePrediction(leftLine, rightLine, outputLines);
		return outputLines;
}

std::string lanes::lanePrediction(cv::Vec4f leftLine, cv::Vec4f rightLine, std::vector<cv::Point> outputLines) {
	std::string turn;
	double vanishPt;
	double laneCenterX = (outputLines[0].x+outputLines[2].x)/2.0;
	double vanishThreshold = 80;
	vanishPt = ((rightLine[3]-rightSlope*rightLine[2])-(leftLine[3]-leftSlope*leftLine[2]))/(leftSlope-rightSlope);
	if (vanishPt < (laneCenterX - vanishThreshold))
		turn = "Left Turn";
	else if (vanishPt > (laneCenterX + vanishThreshold))
		turn = "Right Turn";
	else
		turn = "Straight";
		std::cout<<"Vanish:"<<vanishPt<<"Centre"<<laneCenterX;
		std::cout<<turn<<std::endl;
		return turn;
}

void lanes::showOutput(std::string prediction, cv::Mat frame, std::vector<cv::Point> outputLines) {
	cv::line(frame, outputLines[0], outputLines[1], cv::Scalar(0, 255, 255), CV_AA);
	cv::line(frame, outputLines[2], outputLines[3], cv::Scalar(0, 255, 255), CV_AA);

	cv::putText(frame, prediction, cv::Point(600,600), cv::FONT_HERSHEY_SIMPLEX, 1, cvScalar(255,255,255), 1, CV_AA);
	cv::imshow("Display output with prediction", frame);
}

