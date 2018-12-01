/**============================================================================
 * @file       : lanes.hpp
 * @author     : Rishabh Choudhary, Akash Atharv
 * @version    : 1.0
 * @copyright  : MIT License
 * Copyright 2018 Rishabh Choudhary, Akash Atharv
 * @brief      : Contains function and variable definitions of the class lanes
 *============================================================================
 */

#ifndef INCLUDE_LANES_HPP_
#define INCLUDE_LANES_HPP_

#include <string>
#include <vector>
#include <imageProcessor.hpp>

/**
 * @brief Class lanes
 * The class lanes deals with all the operations remaining 
 * for lane detection after the hough lines in the image 
 * have been detected
 * derived from the base class ImageProcessor
 */

class lanes: public imageProcessor {
 public:
        /**
         * @brief constructor for lanes
         * @param none
         * @return none
         */
        lanes();
        /**
         * @brief destructor for lanes
         * @param none
         * @return none
         */
        virtual ~lanes();
        /**
         * @brief function for retrieving set of lines detected on left side
         * @param none
         * @return vector containing points describing set of left lines
         */
        std::vector<cv::Vec4i> getLeftLines() { return leftLines; }
        /**
         * @brief function for retrieving set of lines detected on right side
         * @param none
         * @return vector containing points describing set of right lines
         */
        std::vector<cv::Vec4i> getRightLines() { return rightLines; }
        /**
         * @brief function to separate left and right lines on the road
         * @param[in] set of all lines
         * @param[in] input image
         */
        cv::Mat lineSeparation(std::vector<cv::Vec4i>, cv::Mat);
        /**
         * @brief function to calculate linear regression of given points
         * on left and right lines.
         * @param[in] set of left and right points
         */
        std::vector<cv::Point> fitLine(std::vector<cv::Point>,
                                    std::vector<cv::Point>);
        /**
         * @brief function to predict lane heading 
         * given left anf right line
         * @param[in] left line
         * @param[in] right line
         * @param[in] output line to calculate x intercept
         */
        std::string lanePrediction(cv::Vec4f, cv::Vec4f,
                                     std::vector<cv::Point>);
        std::string prediction;
        /**
         * @brief function for displaying the output
         * @param string which contains the direction of heading
         * @param original Image of the frame
         * @param set of points which describe the lanes
         * @return none
         */
        void showOutput(std::string, cv::Mat, std::vector<cv::Point>);
        /**
         * @brief virtual function for using google Mock
         * @param none
         * @return int
         */
        virtual int output() { return 0;}

 private:
        cv::Point rightB;/* y = mX + B */     /* B of right line */
        cv::Point leftB;                      /* B of left line */
        double rightSlope;                    /* slope of right line */
        double leftSlope;                     /* slope of left line */
        std::vector<cv::Vec4i> rightLines;    /* Set of right lines */
        std::vector<cv::Vec4i> leftLines;     /* Set of left lines */
};

#endif /* INCLUDE_LANES_HPP_ */
