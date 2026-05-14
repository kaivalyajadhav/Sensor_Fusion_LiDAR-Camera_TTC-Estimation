#ifndef DATASTRUCTURES_H_
#define DATASTRUCTURES_H_

#include <vector>
#include <opencv2/core.hpp>

struct LidarPoint { 
    double x,y,z;   // x,y,z in [m]
    double intensity; // reflected intensity
};

struct BoundingBox { 
    int boxID;         // unique bounding box ID
    int trackID;       // unique track ID
    float confidence;  // classification confidence
    float lidarConfidence; // LiDAR-based confidence
    cv::Rect roi;      // 2D region-of-interest in image coordinates
    int classID;       // classification ID (0: car, 1: truck, etc.)
    bool isVisible;    // visibility flag
    std::vector<LidarPoint> lidarPoints;  // LiDAR points in 3D space
    std::vector<cv::KeyPoint> keypoints;  // keypoints enclosed by 2D roi
    std::vector<cv::DMatch> kptMatches;   // keypoint matches to previous frame
    double TTC;        // time to collision
};

struct DataFrame { 
    cv::Mat cameraImg;           // camera image
    std::vector<cv::KeyPoint> keypoints;     // 2D keypoints within camera image
    std::vector<cv::DMatch> kptMatches;      // keypoint matches to previous frame
    std::vector<cv::KeyPoint> keypointsPrev; // 2D keypoints from previous frame
    std::vector<cv::DMatch> kptMatchesPrev;  // keypoint matches from previous frame
    std::vector<BoundingBox> boundingBoxes;  // bounding boxes around objects
    std::vector<LidarPoint> lidarPoints;     // LiDAR points in vehicle coordinates
    std::vector<BoundingBox> boundingBoxesPrev; // bounding boxes from previous frame
    std::vector<LidarPoint> lidarPointsPrev; // LiDAR points from previous frame
};

#endif /* DATASTRUCTURES_H_ */
