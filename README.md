# Sensor_Fusion-LiDAR-Camera-_TTC-Estimation

Welcome to the final project of the camera course. This is the fifth stage of development with descriptor extraction and matching capability.

## Current Capabilities
- Project structure established
- Basic data structures implemented
- Entry point with hello world functionality
- Basic CMake configuration with OpenCV integration
- LiDAR data loading implemented
- 2D feature detection foundation (Shi-Tomasi, Harris, FAST, BRISK, ORB, AKAZE, SIFT detectors)
- Descriptor extraction and matching foundation

## What is NOT implemented yet
- Object detection
- TTC computation
- Lidar point cloud processing (beyond loading and basic filtering)
- Camera-LiDAR fusion
- Keypoint matching to ROIs
- Bounding box tracking

## How to run the current version
1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./3D_object_tracking` (should detect keypoints, extract descriptors, and match them between consecutive frames using Shi-Tomasi and BRISK)