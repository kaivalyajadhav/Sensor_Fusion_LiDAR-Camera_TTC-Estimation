#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "objectDetection2D.hpp"
#include "dataStructures.h"

using namespace std;
using namespace cv;
using namespace dnn;

void detectObjects(cv::Mat &img, std::vector<BoundingBox> &boundingBoxes, float confThreshold, float nmsThreshold,
                   const std::string &yoloBasePath, const std::string &yoloClassesFile,
                   const std::string &yoloModelConfiguration, const std::string &yoloModelWeights, bool bVis)
{
    // Stub implementation
    std::cout << "Stub: detectObjects called" << std::endl;
}