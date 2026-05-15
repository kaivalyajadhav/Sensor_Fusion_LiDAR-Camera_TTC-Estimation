/* INCLUDES FOR THIS PROJECT */
#include <iostream>
#include <opencv2/core.hpp>

#include "dataStructures.h"
#include "matching2D.hpp"
#include "objectDetection2D.hpp"
#include "lidarData.hpp"
#include "camFusion.hpp"

using namespace std;

/* MAIN PROGRAM */
int main(int argc, const char *argv[])
{
    cout << "Hello - Sensor Fusion TTC Estimation" << endl;
    cout << "OpenCV version: " << CV_VERSION << endl;
    
    // Test basic functionality
    cout << "Testing basic data structure creation..." << endl;
    
    // Create a sample bounding box
    BoundingBox box;
    box.boxID = 0;
    box.trackID = -1;
    box.confidence = 0.0f;
    box.lidarConfidence = 0.0f;
    box.roi = cv::Rect(0, 0, 100, 100);
    box.classID = 0;
    box.isVisible = true;
    
    cout << "Created bounding box with ID: " << box.boxID << endl;
    
    // Test data frame
    DataFrame frame;
    frame.cameraImg = cv::Mat();
    cout << "Created empty data frame" << endl;
    
    return 0;
}
