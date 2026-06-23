# Sensor_Fusion-TTC-Estimation

3D Object Tracking & Time‑to‑Collision (TTC) Estimation
Multi‑Sensor Fusion with Camera + LiDAR | C++ | OpenCV
This project implements a full 2D feature‑tracking pipeline and a LiDAR–camera fusion system to estimate Time‑to‑Collision (TTC) for forward vehicles in an autonomous‑driving scenario.
It is based on the Udacity Sensor Fusion Nanodegree final project, with extensive improvements, debugging, and evaluation.

# Project Overview
The system processes synchronized camera images and LiDAR point clouds to:
- Detect vehicles using YOLOv3
- Track 2D keypoints across frames using classical & modern detectors/descriptors
- Associate LiDAR points and keypoints with object bounding boxes
- Compute TTC from LiDAR (geometric distance change)
- Compute TTC from camera (keypoint distance‑ratio change)
- Compare TTC stability across sensor modalities
- Evaluate detector/descriptor performance for vision‑based TTC

# Skills Demonstrated
- Multi‑sensor fusion (LiDAR + camera)
- 2D feature detection, description, and matching
- Object tracking across frames
- Robust TTC estimation (vision & LiDAR)
- Outlier rejection (median filtering, ROI clustering)
- Performance benchmarking across detector/descriptor pairs
- C++ engineering, debugging, and pipeline design
Tech Stack: C++, OpenCV, PCL‑style LiDAR processing, YOLOv3, Eigen

# Pipeline Architecture
1. Object Detection (YOLOv3)
Detects vehicles and produces 2D bounding boxes.
2. LiDAR Cropping & ROI Association
Filters LiDAR points by height, distance, reflectivity, and associates them with bounding boxes.
3. 2D Keypoint Detection & Description
Supports all classical and modern OpenCV methods:
Detectors:
SHITOMASI, HARRIS, FAST, BRISK, ORB, AKAZE, SIFT
Descriptors:
BRISK, BRIEF, ORB, FREAK, AKAZE, SIFT
4. Keypoint Matching
BF or FLANN matching with NN/KNN selection.
5. Bounding Box Matching Across Frames
Implemented in matchBoundingBoxes() using a 2D histogram of keypoint correspondences.
6. TTC Estimation
- LiDAR TTC :
Median x‑distance change across frames
- Camera TTC :
Median keypoint distance‑ratio change
7. Performance Evaluation 
- Identify LiDAR TTC failure cases
- Identify camera TTC failure cases
- Compare detector/descriptor combos
- Log results to CSV for analysis

# Implementation Summary
— Match 3D Objects Across Frames
File: camFusion_Student.cppDetector/Descriptor Performance Evaluation
All combinations tested:
Detectors: SHITOMASI, HARRIS, FAST, BRISK, ORB, AKAZE, SIFT
Descriptors: BRISK, BRIEF, ORB, FREAK, AKAZE, SIFT
Logged to CSV:
frame, detector, descriptor, ttc_lidar, ttc_camera

Best-Performing (Stable) Combinations

These detector–descriptor pairs produced consistent TTC values, closely matching LiDAR TTC (~11.7 s), with minimal variance:

SIFT + SIFT
BRISK + SIFT
SIFT + FREAK

Why these work well:
    SIFT descriptors deliver stable, scale-invariant matches
    Median ratio filtering remains effective due to consistent feature geometry
    BRISK + SIFT combines fast keypoint detection with robust SIFT descriptors

These combinations are recommended for reliable camera-based TTC estimation.

Unstable / Poor-Performing Combinations

These combinations frequently produce extreme TTC spikes, inflated values, or invalid ratios:

HARRIS + ORB
ORB + ORB
HARRIS + BRIEF

Common root causes:
    Low keypoint count (HARRIS)
    ORB descriptor mismatch sensitivity
    Distance ratios become unstable due to small denominator distances
    Outliers slip through, even after median filtering

Camera TTC Failure Examples
- HARRIS + ORB: TTC Camera ~0.4 s (too small)
- ORB + ORB: TTC Camera ~20+ s (inflated)

📊 Results Summary
- LiDAR TTC is generally more stable but fails when bounding boxes include road/truck points.
- Camera TTC is highly sensitive to keypoint quality and descriptor robustness.
- SIFT‑based combinations consistently produce the most reliable camera TTC.
- ORB‑based combinations frequently produce mismatches and unstable TTC.
- HARRIS keypoints are too sparse, making TTC extremely sensitive to outliers.




🚀 How to Run
- Build the project:
  
        mkdir build && cd build
        cmake ..
        make

- Run:
  
        ./3D_object_tracking
