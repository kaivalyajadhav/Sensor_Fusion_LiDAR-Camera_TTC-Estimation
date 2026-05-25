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
    
    return 0;
}