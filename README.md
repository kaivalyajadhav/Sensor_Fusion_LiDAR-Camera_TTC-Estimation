# Sensor_Fusion-LiDAR-Camera-_TTC-Estimation

## Project Overview
This project implements a 3D object tracking system with Time-to-Collision (TTC) estimation 
using sensor fusion of camera and LiDAR data.

## Snapshot 2: Basic Project Structure
This snapshot adds:
- Enhanced CMake configuration ready for OpenCV integration
- Complete data structure definitions
- Basic header files for all modules
- Stub implementations for all student tasks

## Directory Structure
- `src/`: Contains all source code files
- `dat/`: Data directory (will contain YOLO weights and other data)
- `images/`: Input images and LiDAR scans
- `build/`: Build directory (created during compilation)

## Next Steps
In subsequent snapshots, we will:
1. Integrate OpenCV for feature detection
2. Implement 2D feature detectors and descriptors
3. Add object detection using YOLO
4. Implement LiDAR-camera fusion
5. Calculate Time-to-Collision estimates
