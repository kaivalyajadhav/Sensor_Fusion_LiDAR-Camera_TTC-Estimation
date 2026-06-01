/* INCLUDES FOR THIS PROJECT */
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/features2d.hpp>

#include "dataStructures.h"
#include "matching2D.hpp"

using namespace std;
using namespace cv::xfeatures2d;

#define LOG_CSV(imgIdx, det, desc, nKpts, minS, meanS, maxS, t_det, t_desc, nMatches) \
    do { \
        std::cout << imgIdx << "," \
                  << det << "," \
                  << desc << "," \
                  << nKpts << "," \
                  << minS << "," \
                  << meanS << "," \
                  << maxS << "," \
                  << t_det << "," \
                  << t_desc << "," \
                  << nMatches \
                  << std::endl; \
        csvFile << imgIdx << "," \
                << det << "," \
                << desc << "," \
                << nKpts << "," \
                << minS << "," \
                << meanS << "," \
                << maxS << "," \
                << t_det << "," \
                << t_desc << "," \
                << nMatches \
                << "\n"; \
    } while(0)

bool isValidCombo(const std::string &det, const std::string &desc)
{
    // AKAZE descriptor only works with AKAZE detector
    if (det != "AKAZE" && desc == "AKAZE") return false;
    if (det == "AKAZE" && desc != "AKAZE") return false;
    

    // ORB detector cannot use SIFT descriptor
    if (det == "ORB" && desc == "SIFT") return false;
    if (det == "SIFT" && desc == "ORB") return false;

    return true;
}

/* MAIN PROGRAM */
int main(int argc, const char *argv[])
{

    /* INIT VARIABLES AND DATA STRUCTURES */

    // All detectors to test
    std::vector<std::string> detectorTypes = 
    {
        "SHITOMASI", "HARRIS", "FAST", "BRISK", "ORB", "AKAZE", "SIFT"
    };

    // All descriptors to test
    std::vector<std::string> descriptorTypes = 
    {
        "BRISK", "BRIEF", "ORB", "FREAK", "AKAZE", "SIFT"
    };

    double t_det = 0.0;
    double t_desc = 0.0;   

    std::ofstream csvFile("results.csv");
    csvFile << "imgIndex,detectorType,descriptorType,nKeypointsROI,minSize,meanSize,maxSize,t_det_ms,t_desc_ms,nMatches\n";       

    // data location
    string dataPath = "../";

    // camera
    string imgBasePath = dataPath + "images/";
    string imgPrefix = "KITTI/2011_09_26/image_00/data/000000"; // left camera, color
    string imgFileType = ".png";
    int imgStartIndex = 0; // first file index to load (assumes Lidar and camera names have identical naming convention)
    int imgEndIndex = 9;   // last file index to load
    int imgFillWidth = 4;  // no. of digits which make up the file index (e.g. img-0001.png)

    // misc
    int dataBufferSize = 2;       // no. of images which are held in memory (ring buffer) at the same time
    vector<DataFrame> dataBuffer; // list of data frames which are held in memory at the same time
    bool bVis = false;            // visualize results

    /* MAIN LOOP OVER ALL IMAGES */
    for (const auto &detectorType : detectorTypes)
    {
        for (const auto &descriptorType : descriptorTypes)
        {
            if (!isValidCombo(detectorType, descriptorType))
            {
                std::cout << "Skipping invalid combo: " 
                        << detectorType << " + " << descriptorType << std::endl;
                continue;
            }

            std::cout << "\n=== Running " << detectorType 
                    << " + " << descriptorType << " ===\n";

            dataBuffer.clear();
    
            // ---- ORIGINAL IMAGE LOOP STARTS HERE ----

            for (size_t imgIndex = 0; imgIndex <= imgEndIndex - imgStartIndex; imgIndex++)
            {
                /* LOAD IMAGE INTO BUFFER */

                // assemble filenames for current index
                ostringstream imgNumber;
                imgNumber << setfill('0') << setw(imgFillWidth) << imgStartIndex + imgIndex;
                string imgFullFilename = imgBasePath + imgPrefix + imgNumber.str() + imgFileType;

                // load image from file and convert to grayscale
                cv::Mat img, imgGray;
                img = cv::imread(imgFullFilename);
                cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

                
                //// TASK MP.1 -> replace the following code with ring buffer of size dataBufferSize

                // push image into data frame buffer
                DataFrame frame;
                frame.cameraImg = imgGray;
                if (dataBuffer.size() >= dataBufferSize){
                    dataBuffer.erase(dataBuffer.begin());
                }

                dataBuffer.push_back(frame);

                
                cout << "#1 : LOAD IMAGE INTO BUFFER done" << endl;

                /* DETECT IMAGE KEYPOINTS */

                // extract 2D keypoints from current image
                vector<cv::KeyPoint> keypoints; // create empty feature list for current image
                

                //string detectorType = "HARRIS";

                
                //// TASK MP.2 -> add the following keypoint detectors in file matching2D.cpp and enable string-based selection based on detectorType
                //// -> HARRIS, FAST, BRISK, ORB, AKAZE, SIFT

                t_det = (double)cv::getTickCount();

                detKeypointsModern(keypoints, imgGray, detectorType, false);
                
                t_det = ((double)cv::getTickCount() - t_det) / cv::getTickFrequency();
                t_det *= 1000.0;                 
                

                
                //// TASK MP.3 -> only keep keypoints on the preceding vehicle

                // only keep keypoints on the preceding vehicle
                bool bFocusOnVehicle = true;
                cv::Rect vehicleRect(535, 180, 180, 150);
                if (bFocusOnVehicle)
                {
                    std::vector<cv::KeyPoint> filteredKpts;
                    filteredKpts.reserve(keypoints.size());

                    for (auto &kp : keypoints)
                    {
                        if (vehicleRect.contains(kp.pt))
                        {
                            filteredKpts.push_back(kp);
                        }
                    }

                    keypoints = filteredKpts;

                    std::cout << "Keypoints inside vehicle ROI: "
                            << keypoints.size() << std::endl;
                }
                // Neighborhood size stats ADDED
                double minS = 1e9, maxS = 0, sumS = 0;
                for (auto &kp : keypoints)
                {
                    minS = std::min(minS, (double)kp.size);
                    maxS = std::max(maxS, (double)kp.size);
                    sumS += kp.size;
                }
                double meanS = keypoints.empty() ? 0 : sumS / keypoints.size();

                dataBuffer.back().keypoints = keypoints;

                

                // optional : limit number of keypoints (helpful for debugging and learning)
                bool bLimitKpts = false;
                if (bLimitKpts)
                {
                    int maxKeypoints = 50;

                    if (detectorType.compare("SHITOMASI") == 0)
                    { // there is no response info, so keep the first 50 as they are sorted in descending quality order
                        keypoints.erase(keypoints.begin() + maxKeypoints, keypoints.end());
                    }
                    cv::KeyPointsFilter::retainBest(keypoints, maxKeypoints);
                    cout << " NOTE: Keypoints have been limited!" << endl;
                }

                // push keypoints and descriptor for current frame to end of data buffer
                (dataBuffer.end() - 1)->keypoints = keypoints;
                cout << "#2 : DETECT KEYPOINTS done" << endl;

                /* EXTRACT KEYPOINT DESCRIPTORS */

                
                //// TASK MP.4 -> add the following descriptors in file matching2D.cpp and enable string-based selection based on descriptorType
                //// -> BRIEF, ORB, FREAK, AKAZE, SIFT

                cv::Mat descriptors;

                //string descriptorType = "BRIEF"; // BRIEF, ORB, FREAK, AKAZE, SIFT

                t_desc = (double)cv::getTickCount();

                descKeypoints((dataBuffer.end() - 1)->keypoints, (dataBuffer.end() - 1)->cameraImg, descriptors, descriptorType);

                t_desc = ((double)cv::getTickCount() - t_desc) / cv::getTickFrequency();
                t_desc *= 1000.0;
                
                

                // push descriptors for current frame to end of data buffer
                (dataBuffer.end() - 1)->descriptors = descriptors;

                cout << "#3 : EXTRACT DESCRIPTORS done" << endl;

                if (dataBuffer.size() > 1) // wait until at least two images have been processed
                {

                    /* MATCH KEYPOINT DESCRIPTORS */

                    vector<cv::DMatch> matches;
                    string matcherType = "MAT_BF";        // MAT_BF, MAT_FLANN

                    string selectorType = "SEL_NN";       // SEL_NN, SEL_KNN

                    
                    //// TASK MP.5 -> add FLANN matching in file matching2D.cpp
                    //// TASK MP.6 -> add KNN match selection and perform descriptor distance ratio filtering with t=0.8 in file matching2D.cpp
                    string descriptorCategory = 
                        (descriptorType == "SIFT") ? "DES_HOG" : "DES_BINARY";
                    
                    std::cout << "Descriptor category = " << descriptorCategory << std::endl;

                    matchDescriptors((dataBuffer.end() - 2)->keypoints, (dataBuffer.end() - 1)->keypoints,
                                    (dataBuffer.end() - 2)->descriptors, (dataBuffer.end() - 1)->descriptors,
                                    matches, descriptorCategory, matcherType, selectorType);

                    

                    // store matches in current data frame
                    (dataBuffer.end() - 1)->kptMatches = matches;

                    cout << "#4 : MATCH KEYPOINT DESCRIPTORS done" << endl;

                    // CSV LOGGING 
                    LOG_CSV(imgIndex, detectorType, descriptorType,
                            keypoints.size(), minS, meanS, maxS,
                            t_det, t_desc, matches.size());
                    // END CSV LOGGING
                    // visualize matches between current and previous image
                    bVis = false;
                    if (bVis)
                    {
                        cv::Mat matchImg = ((dataBuffer.end() - 1)->cameraImg).clone();
                        cv::drawMatches((dataBuffer.end() - 2)->cameraImg, (dataBuffer.end() - 2)->keypoints,
                                        (dataBuffer.end() - 1)->cameraImg, (dataBuffer.end() - 1)->keypoints,
                                        matches, matchImg,
                                        cv::Scalar::all(-1), cv::Scalar::all(-1),
                                        vector<char>(), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

                        string windowName = "Matching keypoints between two camera images";
                        cv::namedWindow(windowName, 7);
                        cv::imshow(windowName, matchImg);
                        cout << "Press key to continue to next image" << endl;
                        cv::waitKey(0); // wait for key to be pressed
                    }
                    bVis = false;
                }

            } // eof loop over all images
        }
    }
    csvFile.close();
    return 0;
}
