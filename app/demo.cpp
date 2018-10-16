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


int main(int argc, char* argv[]) {

    std::string inputVideo;
    cv::Mat originalImage;

    cv::Mat maskImage;
    cv::Mat frame;
	cv::Mat separateImage;
    /* If number of arguments specified is incorrect, return */
	if( argc != 2 ) {
        std::cout << "Wrong usage : PLease specify Input video "
        		"clip with the program as argument" <<std::endl;
        return -1;
    }
    
    inputVideo = argv[1];

    /* Capture the video clip into inputVideo */
    cv::VideoCapture cap(inputVideo);

    /* If not able to open video file, return */
    if (!cap.isOpened()) return -1;

    while(1) {
    	// Read video frame by frame
    	if (!cap.read(frame)) break;
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

        cv::Mat mask = cv::Mat::zeros(img.getEgdeImage().size(), img.getEgdeImage().type());

        /* Define the points for region of interest */
        cv::Point pts[4] = {
        cv::Point(0, 831),
        cv::Point(629, 465),
        cv::Point(756, 472),
        cv::Point(1195, 711)
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
        cv::waitKey(50);
       }

	cv::waitKey(0);

    return 0;
}
