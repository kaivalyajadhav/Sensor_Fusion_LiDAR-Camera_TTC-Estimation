#ifndef OBJECTDETECTION2D_HPP_
#define OBJECTDETECTION2D_HPP_

#include <vector>
#include <opencv2/core.hpp>
#include "dataStructures.h"

void detectObjects(std::vector<BoundingBox> &boundingBoxes, float confThreshold, float nmsThreshold);

#endif /* OBJECTDETECTION2D_HPP_ */
