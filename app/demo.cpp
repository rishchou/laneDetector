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
   // cv::Mat noiseImage;
  //  cv::Mat edgeImage;
   // int lowThreshold = 100;
   // int ratio = 3;
   // int kernelSize = 3;
    cv::Mat maskImage;
    cv::Mat frame;
   // cv::Mat houghImage;
	cv::Mat separateImage;
    if( argc != 2 ) {
        std::cout << "Usage wrong" <<std::endl;
	return -1;
    }
    

    inputVideo = argv[1];
    cv::VideoCapture cap(inputVideo);
    if (!cap.isOpened()) return -1;

    while(1) {
    	if (!cap.read(frame)) break;
    originalImage = frame;
    lanes img;
    //double ic = double(originalImage.cols/2);
    //img.setImageCentre(ic);
    img.setOriginalImage(originalImage);
    img.rgbToGray(originalImage);

    //  cv::Mat grayImage;
   // cv::cvtColor(originalImage, grayImage, CV_BGR2GRAY);



    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display GrayScale Image", img.getGrayImage());

    img.noiseFilter(img.getGrayImage());
   // cv::GaussianBlur(grayImage, noiseImage, cv::Size(3,3), 0, 0);
   // cv::medianBlur(grayImage,noiseImage, kernelSize);
    cv::imshow("Display Noise filtered Image", img.getNoiseImage());
    img.edgeDetector(img.getNoiseImage());
    //cv::Canny( noiseImage, edgeImage, lowThreshold, lowThreshold*ratio, kernelSize );
    cv::imshow("Display Canny edge", img.getEgdeImage());


    std::cout << "size of image " << img.getEgdeImage().size() << std::endl;
    cv::Mat mask = cv::Mat::zeros(img.getEgdeImage().size(), img.getEgdeImage().type());
    cv::Point pts[4] = {
        cv::Point(0, 831),
        cv::Point(629, 465),
        cv::Point(756, 472),
        cv::Point(1195, 711)
    };
    std::cout << "size of image " << img.getEgdeImage().size() << std::endl;
    // Create a binary polygon mask
    cv::fillConvexPoly(mask, pts, 4, cv::Scalar(255, 0, 0));
    // Multiply the edges image and the mask to get the output
    cv::bitwise_and(img.getEgdeImage(), mask, maskImage);

    std::cout << "size of image " << img.getEgdeImage().size() << std::endl;

    img.grayToRGB(img.getEgdeImage());
    std::cout << "size of image " << img.getEgdeImage().size() << std::endl;
    cv::imshow("Display Region of interest", maskImage);
    std::cout << "size of image " << img.getEgdeImage().size() << std::endl;

    std::vector<cv::Vec4i> lines;
    lines = img.houghTransform(maskImage, img.getHoughImage());
   // std::vector<cv::Vec4i> lines;
    //cv::HoughLinesP(maskImage, lines, 1, CV_PI/180, 20 , 35, 30);
    
    cv::imshow("Display hough lines", img.getHoughImage());


    separateImage = img.lineSeparation(lines, img.getEgdeImage());
    cv::imshow("Display separated lines", separateImage);

    std::vector<cv::Point> rightPts;
   	std::vector<cv::Point> leftPts;
    std::vector<cv::Point> outputLines;
   	outputLines = img.fitLine(rightPts, leftPts);

    img.showOutput(img.prediction, originalImage, outputLines);
    //cv::imshow("Display output", originalImage);
    cv::waitKey(50);
    }

	cv::waitKey(0);

    return 0;
}
