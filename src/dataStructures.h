#ifndef DATASTRUCTURES_H_
#define DATASTRUCTURES_H_

#include <vector>
#include <opencv2/core.hpp>

struct LidarPoint { double x,y,z,r; int reflectance; };

struct BoundingBox { int boxID; int trackID; float confidence; 
                     cv::Rect roi; int classID; bool isVisible; 
                     std::vector<LidarPoint> lidarPoints; 
                     std::vector<cv::KeyPoint> keypoints; 
                     std::vector<cv::DMatch> kptMatches; 
                     double TTC; };

struct DataFrame { cv::Mat cameraImg; 
                   std::vector<cv::KeyPoint> keypoints; 
                   std::vector<cv::DMatch> kptMatches; 
                   std::vector<cv::KeyPoint> keypointsPrev; 
                   std::vector<cv::DMatch> kptMatchesPrev; 
                   std::vector<BoundingBox> boundingBoxes; 
                   std::vector<LidarPoint> lidarPoints; 
                   std::vector<BoundingBox> boundingBoxesPrev; 
                   std::vector<LidarPoint> lidarPointsPrev; };

#endif /* DATASTRUCTURES_H_ */
