#include <numeric>
#include "matching2D.hpp"
#include <opencv2/xfeatures2d.hpp>
using namespace cv::xfeatures2d;

using namespace std;

// Find best matches for keypoints in two camera images based on several matching methods
void matchDescriptors(std::vector<cv::KeyPoint> &kPtsSource, std::vector<cv::KeyPoint> &kPtsRef, cv::Mat &descSource, cv::Mat &descRef,
                      std::vector<cv::DMatch> &matches, std::string descriptorType, std::string matcherType, std::string selectorType)
{
    // Stub implementation
    std::cout << "Stub: matchDescriptors called" << std::endl;
}

// Use one of several types of state-of-art descriptors to uniquely identify keypoints
void descKeypoints(vector<cv::KeyPoint> &keypoints, cv::Mat &img, cv::Mat &descriptors, string descriptorType)
{
    // Stub implementation
    std::cout << "Stub: descKeypoints called for " << descriptorType << std::endl;
}

// Detect keypoints in image using the traditional Shi-Thomasi detector
void detKeypointsShiTomasi(vector<cv::KeyPoint> &keypoints, cv::Mat &img, bool bVis)
{
    // compute detector parameters based on image size
    int blockSize = 4;       //  size of an average block for computing a derivative covariation matrix over each pixel neighborhood
    double maxOverlap = 0.0; // max. permissible overlap between two features in %
    double minDistance = (1.0 - maxOverlap) * blockSize;
    int maxCorners = img.rows * img.cols / max(1.0, minDistance); // max. num. of keypoints

    double qualityLevel = 0.01; // minimal accepted quality of image corners
    double k = 0.04;

    // Apply corner detection
    double t = (double)cv::getTickCount();
    vector<cv::Point2f> corners;
    cv::goodFeaturesToTrack(img, corners, maxCorners, qualityLevel, minDistance, cv::Mat(), blockSize, false, k);

    // add corners to result vector
    for (auto it = corners.begin(); it != corners.end(); ++it)
    {
        cv::KeyPoint newKeyPoint;
        newKeyPoint.pt = cv::Point2f((*it).x, (*it).y);
        newKeyPoint.size = blockSize;
        keypoints.push_back(newKeyPoint);
    }
    t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
    //cout << "Shi-Tomasi detection with n=" << keypoints.size() << " keypoints in " << 1000 * t / 1.0 << " ms" << endl;

    // visualize results
    if (bVis)
    {
        cv::Mat visImage = img.clone();
        cv::drawKeypoints(img, keypoints, visImage, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
        string windowName = "Shi-Tomasi Corner Detector Results";
        cv::namedWindow(windowName, 6);
        imshow(windowName, visImage);
        cv::waitKey(0);
    }
}

// Harris detector - stub for now
void detKeypointsHarris(std::vector<cv::KeyPoint> &keypoints, cv::Mat &img, bool bVis)
{
    // Stub implementation
    std::cout << "Stub: detKeypointsHarris called" << std::endl;
}

// FAST detector - stub for now
void detKeypointsFAST(std::vector<cv::KeyPoint> &keypoints, cv::Mat &img, bool bVis)
{
    // Stub implementation
    std::cout << "Stub: detKeypointsFAST called" << std::endl;
}

// BRISK detector - stub for now
void detKeypointsBRISK(std::vector<cv::KeyPoint> &keypoints, cv::Mat &img, bool bVis)
{
    // Stub implementation
    std::cout << "Stub: detKeypointsBRISK called" << std::endl;
}

// ORB detector - stub for now
void detKeypointsORB(std::vector<cv::KeyPoint> &keypoints, cv::Mat &img, bool bVis)
{
    // Stub implementation
    std::cout << "Stub: detKeypointsORB called" << std::endl;
}

// AKAZE detector - stub for now
void detKeypointsAKAZE(std::vector<cv::KeyPoint> &keypoints, cv::Mat &img, bool bVis)
{
    // Stub implementation
    std::cout << "Stub: detKeypointsAKAZE called" << std::endl;
}

// SIFT detector - stub for now
void detKeypointsSIFT(std::vector<cv::KeyPoint> &keypoints, cv::Mat &img, bool bVis)
{
    // Stub implementation
    std::cout << "Stub: detKeypointsSIFT called" << std::endl;
}

void detKeypointsModern(std::vector<cv::KeyPoint> &keypoints,
                        cv::Mat &img, std::string detectorType, bool bVis)
{
    // Convert to uppercase for safety
    std::string det = detectorType;
    std::transform(det.begin(), det.end(), det.begin(), ::toupper);

    if (det == "HARRIS")
    {
        detKeypointsHarris(keypoints, img, bVis);
    }
    else if (det == "SHITOMASI")
    {
        detKeypointsShiTomasi(keypoints, img, bVis);
    }
    else if (det == "FAST")
    {
        detKeypointsFAST(keypoints, img, bVis);
    }
    else if (det == "BRISK")
    {
        detKeypointsBRISK(keypoints, img, bVis);
    }
    else if (det == "ORB")
    {
        detKeypointsORB(keypoints, img, bVis);
    }
    else if (det == "AKAZE")
    {
        detKeypointsAKAZE(keypoints, img, bVis);
    }
    else if (det == "SIFT")
    {
        detKeypointsSIFT(keypoints, img, bVis);
    }
    else
    {
        std::cout << "WARNING: Unknown detectorType = '" << detectorType
                  << "'. Valid options are: "
                  << "HARRIS, SHITOMASI, FAST, BRISK, ORB, AKAZE, SIFT."
                  << std::endl;
    }
}