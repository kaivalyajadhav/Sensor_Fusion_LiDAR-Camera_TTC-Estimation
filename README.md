# Sensor_Fusion-LiDAR-Camera-_TTC-Estimation

Welcome to the final project of the camera course. This is the ninth stage of development with bounding box tracking and robustness improvements.

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
- Keypoint matching to ROIs (clusterKptMatchesWithROI)
- TTC computation foundation (computeTTCCamera and computeTTCLidar)
- Bounding box tracking (matchBoundingBoxes)
- Robustness improvements in TTC computation

## What is NOT implemented yet
- Complete integration of all components in the main processing loop
- Support for multiple detector/descriptor combinations
- Data logging to CSV
- Full test framework validation

## How to run the current version
1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./3D_object_tracking` (should process the full pipeline with bounding box tracking and improved TTC computation)