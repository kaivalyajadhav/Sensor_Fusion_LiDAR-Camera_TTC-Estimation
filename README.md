# Sensor_Fusion-LiDAR-Camera-_TTC-Estimation

## Project Overview
This project implements a 3D object tracking system with Time-to-Collision (TTC) estimation 
using sensor fusion of camera and LiDAR data.

## Snapshot 3: Initial Function Implementations
This snapshot adds:
- Basic Shi-Tomasi feature detector implementation
- Enhanced main function with data structure testing
- OpenCV version output
- Preparation for further functionality

## Directory Structure
- `src/`: Contains all source code files
- `dat/`: Data directory (will contain YOLO weights and other data)
- `images/`: Input images and LiDAR scans
- `build/`: Build directory (created during compilation)

## Next Steps
In subsequent snapshots, we will:
1. Add more feature detectors and descriptors
2. Implement descriptor extraction
3. Add keypoint matching functionality
4. Integrate object detection using YOLO
5. Implement LiDAR-camera fusion
6. Calculate Time-to-Collision estimates
