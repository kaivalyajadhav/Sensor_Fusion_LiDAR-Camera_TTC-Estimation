# Sensor_Fusion-LiDAR-Camera-_TTC-Estimation

Welcome to the final project of the camera course. This is the seventh stage of development with LiDAR-camera point association capability.

## Current Capabilities
- Project structure established
- Basic data structures implemented
- Entry point with hello world functionality
- Basic CMake configuration with OpenCV integration
- LiDAR data loading implemented
- 2D feature detection foundation (all detectors: Shi-Tomasi, Harris, FAST, BRISK, ORB, AKAZE, SIFT)
- Descriptor extraction and matching foundation (all descriptors: BRISK, BRIEF, ORB, FREAK, AKAZE, SIFT)
- Object detection integration (YOLO)
- LiDAR-camera point association (clusterLidarWithROI)

## What is NOT implemented yet
- TTC computation
- Keypoint matching to ROIs
- Bounding box tracking
- Camera TTC computation
- Lidar TTC computation

## How to run the current version
1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./3D_object_tracking` (should load data, detect objects, detect keypoints, extract descriptors, match them, and associate LiDAR points with camera ROIs)