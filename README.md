# AI Surveillance System using C++ and OpenCV

This project implements a **real-time object detection system** using **C++, OpenCV, and YOLOv3**.
It captures video from a camera (including mobile cameras via Camo or virtual webcam) and detects objects such as **person, bottle, chair, phone, car**, and more.

---

## Features

* Real-time object detection using YOLOv3
* Works with laptop camera or mobile camera
* Bounding box detection with object labels
* Non-Maximum Suppression for clean detection
* Built using **C++ and OpenCV DNN module**

---

## Technologies Used

* C++
* OpenCV
* YOLOv3
* Git / GitHub

---

## Project Structure

AIcamera
│
├── detect.cpp
├── camera.cpp
├── coco.names
├── yolov3.cfg
├── haarcascade_frontalface_default.xml
└── README.md

---

## Download YOLO Weights

The **YOLOv3 weights file is large (~240MB)**, so it is not included in this repository.

Download it from the official source:

https://pjreddie.com/media/files/yolov3.weights

After downloading, place the file inside the project folder:

C:\Users\HP\AIcamera

Your folder should look like this:

AIcamera
│
├── detect.cpp
├── camera.cpp
├── coco.names
├── yolov3.cfg
├── yolov3.weights
├── haarcascade_frontalface_default.xml

---

## How to Compile

Open **x64 Native Tools Command Prompt for Visual Studio** and run:

cl detect.cpp /EHsc /I C:\opencv\opencv\build\include /link /LIBPATH:C:\opencv\opencv\build\x64\vc16\lib opencv_world4120.lib

---

## How to Run

detect.exe

Press **ESC** to exit the program.

---

## Example Output

The system detects objects in real time and draws bounding boxes around them.

Example detected classes:

* person
* bottle
* chair
* phone
* car

---

## Future Improvements

* Person-only detection for surveillance systems
* Intruder alert system
* Face recognition
* Object tracking

---

## Author

Sandeep Neelam
B.Tech Information Technology

---
