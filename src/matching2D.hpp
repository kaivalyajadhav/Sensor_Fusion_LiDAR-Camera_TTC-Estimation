#ifndef MATCHING2D_HPP_
#define MATCHING2D_HPP_

#include <vector>
#include <opencv2/core.hpp>
#include "dataStructures.h"

void detKeypointsShiTomasi(std::vector<cv::KeyPoint> &keypoints, cv::Mat &img, bool bVis);
void detKeypointsHarris(std::vector<cv::KeyPoint> &keypoints, cv::Mat &img, bool bVis);
void detKeypointsModern(std::vector<cv::KeyPoint> &keypoints, cv::Mat &img, std::string detectorType, bool bVis);
void descKeypoints(std::vector<cv::KeyPoint> &keypoints, cv::Mat &img, cv::Mat &descriptors, std::string descriptorType);
void matchDescriptors(std::vector<cv::KeyPoint> &kPtsPrev, std::vector<cv::KeyPoint> &kPtsCurr, 
                     cv::Mat &descPrev, cv::Mat &descCurr, 
                     std::vector<cv::DMatch> &matches, std::string matcherType, std::string selectorType);

#endif /* MATCHING2D_HPP_ */
