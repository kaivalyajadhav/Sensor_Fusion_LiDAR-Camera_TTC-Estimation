# Sensor_Fusion-LiDAR-Camera-_TTC-Estimation

Welcome to the final project of the camera course. This is the fourth stage of development with 2D feature detection foundation.

## Current Capabilities
- Project structure established
- Basic data structures implemented
- Entry point with hello world functionality
- Basic CMake configuration with OpenCV integration
- LiDAR data loading implemented
- 2D feature detection foundation (Shi-Tomasi detector)

## What is NOT implemented yet
- Descriptor extraction and matching
- Object detection
- TTC computation
- Lidar point cloud processing (beyond loading and basic filtering)
- Camera-LiDAR fusion
- Keypoint matching to ROIs

## How to run the current version
1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./3D_object_tracking` (should detect and display keypoints using Shi-Tomasi on first image)