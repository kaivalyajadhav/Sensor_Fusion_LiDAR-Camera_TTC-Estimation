#ifndef LIDARDATA_HPP_
#define LIDARDATA_HPP_

#include <vector>
#include "dataStructures.h"

void loadLidarFromFile(std::vector<LidarPoint> &lidarPoints, std::string filename);
void cropLidarPoints(std::vector<LidarPoint> &lidarPoints, float minX, float maxX, float maxY, float minZ, float maxZ, float minR);

#endif /* LIDARDATA_HPP_ */
