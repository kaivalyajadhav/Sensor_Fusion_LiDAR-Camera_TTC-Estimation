#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "objectDetection2D.hpp"
#include "dataStructures.h"

using namespace std;
using namespace cv;
using namespace dnn;

void detectObjects(cv::Mat &img, std::vector<BoundingBox> &boundingBoxes, float confThreshold, float nmsThreshold,
                   const std::string &yoloBasePath, const std::string &yoloClassesFile,
                   const std::string &yoloModelConfiguration, const std::string &yoloModelWeights, bool bVis)
{
    // Load class names
    vector<string> classes;
    ifstream ifs(yoloClassesFile.c_str());
    string line;
    while (getline(ifs, line)) classes.push_back(line);
    
    // Load YOLO network
    Net net = readNetFromDarknet(yoloModelConfiguration, yoloModelWeights);
    net.setPreferableBackend(DNN_BACKEND_OPENCV);
    net.setPreferableTarget(DNN_TARGET_CPU);
    
    // Prepare input blob
    Mat blob;
    blobFromImage(img, blob, 1/255.0, cv::Size(416, 416), Scalar(0,0,0), true, false);
    net.setInput(blob);
    
    // Run forward pass
    vector<Mat> outs;
    vector<String> outNames = net.getUnconnectedOutLayersNames();
    net.forward(outs, outNames);
    
    // Process outputs
    vector<int> classIds;
    vector<float> confidences;
    vector<Rect> boxes;
    
    for (size_t i = 0; i < outs.size(); ++i)
    {
        float* data = (float*)outs[i].data;
        for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
        {
            Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
            Point classIdPoint;
            double confidence;
            minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
            if (confidence > confThreshold)
            {
                int centerX = (int)(data[0] * img.cols);
                int centerY = (int)(data[1] * img.rows);
                int width = (int)(data[2] * img.cols);
                int height = (int)(data[3] * img.rows);
                int left = centerX - width / 2;
                int top = centerY - height / 2;
                
                classIds.push_back(classIdPoint.x);
                confidences.push_back((float)confidence);
                boxes.push_back(Rect(left, top, width, height));
            }
        }
    }
    
    // Apply non-maximum suppression
    vector<int> indices;
    dnn::NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
    
    // Fill bounding boxes
    for (size_t i = 0; i < indices.size(); ++i)
    {
        int idx = indices[i];
        BoundingBox box;
        box.boxID = idx; 
        box.trackID = -1; // Not tracked yet
        box.roi = boxes[idx];
        box.classID = classIds[idx];
        box.confidence = confidences[idx];
        boundingBoxes.push_back(box);
    }
    
    if (bVis && !boundingBoxes.empty())
    {
        Mat visImg = img.clone();
        for (size_t i = 0; i < boundingBoxes.size(); ++i)
        {
            rectangle(visImg, boundingBoxes[i].roi, Scalar(0, 255, 0), 2);
            string label = format("%.2f", boundingBoxes[i].confidence);
            label = classes[boundingBoxes[i].classID] + ": " + label;
            int baseLine;
            Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
            topLeft = boundingBoxes[i].roi.tl();
            rectangle(visImg, Rect(Point(topLeft.x, topLeft.y - labelSize.y - baseLine),
                                   Size(labelSize.width, labelSize.y + baseLine)),
                      Scalar(255, 255, 255), FILLED);
            putText(visImg, label, Point(topLeft.x, topLeft.y - baseLine),
                    FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));
        }
        imshow("Object Detection", visImg);
        waitKey(0);
    }
}