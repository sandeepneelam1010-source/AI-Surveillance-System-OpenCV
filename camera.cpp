#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    VideoCapture cap(0);

    CascadeClassifier faceDetector;
    faceDetector.load("haarcascade_frontalface_default.xml");

    Mat frame, gray;

    while(true)
    {
        cap >> frame;

        if(frame.empty())
            continue;

        cvtColor(frame, gray, COLOR_BGR2GRAY);

        std::vector<Rect> faces;
        faceDetector.detectMultiScale(gray, faces);

        for(int i=0;i<faces.size();i++)
        {
            rectangle(frame, faces[i], Scalar(0,255,0), 2);
        }

        imshow("Face Detection", frame);

        if(waitKey(1)==27)
            break;
    }

    cap.release();
    destroyAllWindows();
}