/*
 * lanes.cpp
 *
 *  Created on: Oct 15, 2018
 *      Author: Rishabh Choudhary
 */

#include <lanes.hpp>

lanes::lanes() {
	/* Constructor */
    leftSlope = 0;
    rightSlope = 0;
}

lanes::~lanes() {
	/* Destructor */
}

cv::Mat lanes::lineSeparation(std::vector<cv::Vec4i> lines, cv::Mat image) {

	cv::Mat separateImage;
	std::vector<double> slopes;
	/* Set the slope threshold to 0.2 to discard horizontal lines */
	double slopeThreshold = 0.2;

	/* specify the image centre along x axis to separate lines */
	double xCentre = double(image.cols/2);

	cvtColor(image, separateImage, CV_GRAY2BGR);

	/*
	 * Iterate over the set of lines to detect slope and
	 * segregate left and right lines
	 */
	for (auto i : lines) {
		cv::Point pt1 = cv::Point(i[0], i[1]);
		cv::Point pt2 = cv::Point(i[2], i[3]);
	    double slope = (double(pt2.y - pt1.y)/double(pt2.x - pt1.x));

		/*
		 * If absolute value of slope is less than given threshold, discard it
		 */
		if (std::abs(slope) < slopeThreshold) {
	    	continue;
		}
		/*
		 * If slope is less zero and points lie on left of image center,
		 * it is a left line, else right line
		 */
		if((slope < 0) && (pt1.x < xCentre) && (pt2.x < xCentre)) {
			leftLines.emplace_back(i);
			/* Draw left lines on the image */
	        cv::line(separateImage, pt1, pt2, cv::Scalar(255,0,0), 3, CV_AA);
	    } else if(slope > 0 && (pt1.x > xCentre) && (pt2.x > xCentre)) {
	        rightLines.emplace_back(i);
	        /* Draw right lines on the image */
	        cv::line(separateImage, pt1, pt2, cv::Scalar(0,255,0), 3, CV_AA);
		}
	}
	return separateImage;
}

std::vector<cv::Point> lanes::fitLine(std::vector<cv::Point> rightPts, std::vector<cv::Point> leftPts) {

	cv::Vec4f leftLine;
	cv::Vec4f rightLine;

	/*
	 * Iterate over left lines to store left points
	 */
	for(auto i : leftLines) {
		leftPts.emplace_back(cv::Point(i[0], i[1]));
		leftPts.emplace_back(cv::Point(i[2], i[3]));
	}
	/*
	 * Regress the points using least square method to obtain
	 * slope and point of final left line
	 */
	if (leftPts.size() > 0) {
		cv::fitLine(leftPts, leftLine, CV_DIST_L2, 0, 0.01, 0.01);
		leftB = cv::Point(leftLine[2], leftLine[3]);
		leftSlope = double(leftLine[1])/double(leftLine[0]);
	}

	/*
	 * Iterate over right lines to store right points
	 */
	for (auto i : rightLines) {
		rightPts.emplace_back(cv::Point(i[0], i[1]));
		rightPts.emplace_back(cv::Point(i[2], i[3]));
	}

	/*
	 * Regress the points using least square method to obtain
	 * slope and point of final right line
	 */
	if (rightPts.size() > 0) {
		cv::fitLine(rightPts, rightLine, CV_DIST_L2, 0, 0.01, 0.01);
	    rightB = cv::Point(rightLine[2], rightLine[3]);
	    rightSlope = double(rightLine[1])/double(rightLine[0]);
	}

	/*
	 * Find left and right x intercept on the image to draw lines
	 */
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

	/*
	 * Predict the left, right or straight lane heading
	 */
	prediction = lanePrediction(leftLine, rightLine, outputLines);
	return outputLines;
}

std::string lanes::lanePrediction(cv::Vec4f leftLine, cv::Vec4f rightLine, std::vector<cv::Point> outputLines) {
	std::string turn;
	double vanishPt;
	double laneCenterX = (outputLines[0].x+outputLines[2].x)/2.0;
	double vanishThreshold = 80;
	/*
	 * Compute the vanishing point of left and right lines
	 */
	vanishPt = ((rightLine[3]-rightSlope*rightLine[2])-(leftLine[3]-leftSlope*leftLine[2]))/(leftSlope-rightSlope);

	/* Based on vanishing point, decide the lane heading direction */
	if (vanishPt < (laneCenterX - vanishThreshold)) {
		turn = "Left Turn";
	} else if (vanishPt > (laneCenterX + vanishThreshold)) {
		turn = "Right Turn";
	} else {
		turn = "Straight";
	}
	return turn;

}

void lanes::showOutput(std::string prediction, cv::Mat frame, std::vector<cv::Point> outputLines) {
	/*
	 * Draw output lines over the current frame
	 */
	cv::line(frame, outputLines[0], outputLines[1], cv::Scalar(0, 255, 255), CV_AA);
	cv::line(frame, outputLines[2], outputLines[3], cv::Scalar(0, 255, 255), CV_AA);

	/*
	 * Draw lane heading text over the current frame
	 */
	cv::putText(frame, prediction, cv::Point(600,600), cv::FONT_HERSHEY_SIMPLEX, 1, cvScalar(255,255,255), 1, CV_AA);

	/*
	 * Display the final output frame
	 */
	cv::imshow("Display output with prediction", frame);
}

