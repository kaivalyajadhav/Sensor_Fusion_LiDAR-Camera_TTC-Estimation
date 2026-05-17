#ifndef objectDetection2D_hpp
#define objectDetection2D_hpp

#include <stdio.h>
#include <vector>
#include <opencv2/core.hpp>

#include "dataStructures.h"

void detectObjects(cv::Mat &img, std::vector<BoundingBox> &boundingBoxes, float confThreshold, float nmsThreshold,
                   const std::string &yoloBasePath, const std::string &yoloClassesFile,
                   const std::string &yoloModelConfiguration, const std::string &yoloModelWeights, bool bVis);

#endif /* objectDetection2D_hpp */