#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace dnn;
using namespace std;

int main()
{
    // Load class names
    vector<string> classes;
    ifstream ifs("coco.names");
    string line;
    while (getline(ifs, line))
        classes.push_back(line);

    // Load YOLO
    Net net = readNetFromDarknet("yolov3.cfg", "yolov3.weights");

    if (net.empty())
    {
        cout << "YOLO failed to load" << endl;
        return -1;
    }

    // Open camera
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cout << "Camera not opened" << endl;
        return -1;
    }

    Mat frame;

    while (true)
    {
        cap >> frame;
        if (frame.empty()) continue;

        // Convert frame to blob
        Mat blob = blobFromImage(frame, 1 / 255.0, Size(608, 608), Scalar(), true, false);

        net.setInput(blob);

        vector<Mat> outputs;
        net.forward(outputs, net.getUnconnectedOutLayersNames());

        vector<int> classIds;
        vector<float> confidences;
        vector<Rect> boxes;

        for (size_t i = 0; i < outputs.size(); i++)
        {
            float* data = (float*)outputs[i].data;

            for (int j = 0; j < outputs[i].rows; j++, data += outputs[i].cols)
            {
                Mat scores = outputs[i].row(j).colRange(5, outputs[i].cols);
                Point classIdPoint;
                double confidence;

                minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);

                if (confidence > 0.6)
                {
                    int centerX = (int)(data[0] * frame.cols);
                    int centerY = (int)(data[1] * frame.rows);
                    int width = (int)(data[2] * frame.cols);
                    int height = (int)(data[3] * frame.rows);

                    int left = centerX - width / 2;
                    int top = centerY - height / 2;

                    boxes.push_back(Rect(left, top, width, height));
                    confidences.push_back((float)confidence);
                    classIds.push_back(classIdPoint.x);
                }
            }
        }

        // Remove duplicate boxes
        vector<int> indices;
        NMSBoxes(boxes, confidences, 0.6, 0.4, indices);

        for (int i : indices)
        {
            Rect box = boxes[i];

            rectangle(frame, box, Scalar(0, 255, 0), 2);

            string label = classes[classIds[i]];

            putText(frame, label,
                Point(box.x, box.y - 10),
                FONT_HERSHEY_SIMPLEX,
                0.7,
                Scalar(0, 255, 0),
                2);
        }

        imshow("YOLO Detection", frame);

        if (waitKey(1) == 27)
            break;
    }

    cap.release();
    destroyAllWindows();

    return 0;
}