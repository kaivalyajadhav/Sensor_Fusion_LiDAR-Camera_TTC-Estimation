# Sensor_Fusion-LiDAR-Camera-_TTC-Estimation

Welcome to the final project of the camera course. This is the eighth stage of development with keypoint matching to ROIs and TTC foundation.

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
- TTC computation foundation (computeTTCCamera and computeTTCLidar stubs)

## What is NOT implemented yet
- Bounding box tracking
- Full TTC computation implementations
- Data logging to CSV
- Complete integration of all components in the main loop

## How to run the current version
1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./3D_object_tracking` (should process the full pipeline up to TTC computation stubs)