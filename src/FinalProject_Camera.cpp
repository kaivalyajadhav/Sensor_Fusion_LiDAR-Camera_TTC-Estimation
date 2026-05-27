/* INCLUDES FOR THIS PROJECT */
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

#include "dataStructures.h"
#include "matching2D.hpp"
#include "objectDetection2D.hpp"
#include "lidarData.hpp"
#include "camFusion.hpp"

using namespace std;

/* MAIN PROGRAM */
int main(int argc, const char *argv[])
{
    cout << "Hello - Initial Project Skeleton" << endl;
    cout << "OpenCV version: " << CV_VERSION << endl;
    
    // Test LiDAR data loading
    string testFilename = "../dat/raw_data/0000000000.bin"; // Example path
    vector<LidarPoint> testPoints;
    loadLidarFromFile(testPoints, testFilename);
    cout << "Test LiDAR loading: " << testPoints.size() << " points loaded" << endl;
    
    // Test 2D feature detection with Shi-Tomasi
    string imgPath = "../images/KITTI/2011_09_26/image_02/data/0000000000.png";
    cv::Mat img = cv::imread(imgPath);
    if (!img.empty()) {
        cout << "Testing Shi-Tomasi detector on first image..." << endl;
        vector<cv::KeyPoint> keypoints;
        detKeypointsShiTomasi(keypoints, img, false); // false for no visualization
        cout << "Detected " << keypoints.size() << " keypoints using Shi-Tomasi" << endl;
        
        // Optional: visualize if needed
        // detKeypointsShiTomasi(keypoints, img, true);
    } else {
        cout << "Warning: Could not load test image at " << imgPath << endl;
    }
    
    // Test object detection
    cout << "\nTesting object detection..." << endl;
    string yoloBasePath = "../dat/yolo/";
    string yoloClassesFile = yoloBasePath + "coco.names";
    string yoloModelConfiguration = yoloBasePath + "yolov3.cfg";
    string yoloModelWeights = yoloBasePath + "yolov3.weights";
    
    vector<BoundingBox> boundingBoxes;
    detectObjects(img, boundingBoxes, 0.2, 0.4, yoloBasePath, yoloClassesFile, 
                  yoloModelConfiguration, yoloModelWeights, false);
    
    cout << "Detected " << boundingBoxes.size() << " objects" << endl;
    
    // Test LiDAR-camera point association
    cout << "\nTesting LiDAR-camera point association..." << endl;
    if (!boundingBoxes.empty() && !testPoints.empty()) {
        // Use dummy calibration matrices for testing
        cv::Mat P_rect_00(3,4,cv::DataType<double>::type);
        cv::Mat R_rect_00(4,4,cv::DataType<double>::type);
        cv::Mat RT(4,4,cv::DataType<double>::type);
        
        // Set some dummy values
        P_rect_00.at<double>(0,0) = 7.215377e+02;
        R_rect_00.at<double>(0,0) = 9.999239e-01;
        RT.at<double>(0,0) = 7.533745e-03;
        
        clusterLidarWithROI(boundingBoxes, testPoints, 0.1f, P_rect_00, R_rect_00, RT);
        cout << "LiDAR-camera association test completed" << endl;
        
        // Check if any Lidar points were associated
        int total_associated = 0;
        for (const auto& box : boundingBoxes) {
            total_associated += box.lidarPoints.size();
        }
        cout << "Total Lidar points associated with ROIs: " << total_associated << endl;
    } else {
        cout << "Skipping LiDAR-camera association test (no detections or LiDAR points)" << endl;
    }
    
    // Test keypoint detection and description
    cout << "\nTesting 2D feature detection and description..." << endl;
    if (!img.empty()) {
        cv::Mat imgGray;
        cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
        
        vector<cv::KeyPoint> keypoints;
        detKeypointsModern(keypoints, imgGray, "SHITOMASI", false);
        
        cv::Mat descriptors;
        descKeypoints(keypoints, img, descriptors, "BRISK");
        
        cout << "Extracted " << keypoints.size() << " keypoints and descriptors" << endl;
        
        // Test matching with a second frame (same image for simplicity)
        vector<cv::KeyPoint> keypoints2;
        detKeypointsModern(keypoints2, imgGray, "SHITOMASI", false);
        cv::Mat descriptors2;
        descKeypoints(keypoints2, img, descriptors2, "BRISK");
        
        vector<cv::DMatch> matches;
        matchDescriptors(keypoints, keypoints2, descriptors, descriptors2, matches, "DES_BINARY", "MAT_BF", "SEL_NN");
        
        cout << "Matched " << matches.size() << " keypoint descriptors" << endl;
        
        // Test keypoint matching to ROIs
        if (!boundingBoxes.empty() && !matches.empty()) {
            clusterKptMatchesWithROI(boundingBoxes[0], keypoints, keypoints2, matches);
            cout << "Keypoint matching to ROIs test completed" << endl;
            cout << "Matches in ROI: " << boundingBoxes[0].kptMatches.size() << endl;
        }
    }
    
    return 0;
}