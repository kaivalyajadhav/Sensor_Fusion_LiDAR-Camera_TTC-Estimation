# Sensor_Fusion-LiDAR-Camera-_TTC-Estimation

Welcome to the final project of the camera course. This is the tenth stage of development with complete pipeline integration and testing.

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
- TTC computation (computeTTCCamera and computeTTCLidar)
- Bounding box tracking (matchBoundingBoxes)
- Complete integration of all components in the main processing loop
- Support for multiple detector/descriptor combinations
- Data logging to CSV
- Basic test framework validation

## What is NOT implemented yet
- Code polish and optimization
- Comprehensive documentation
- Performance optimizations
- Advanced error handling

## How to run the current version
1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./3D_object_tracking` (should process the full pipeline with all detector/descriptor combinations and log results to ttc_log.csv)