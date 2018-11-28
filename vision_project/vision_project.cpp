// vision_project.cpp : This file contains the 'main' function. Program execution begins and ends there.


/* ..(1).. DIGITAL IMAGES ARE MATRICES
Humans use various methods to create different digital images from the real-world: digital cameras, scanners,
CT & MRI to name a few. In every case what we (humans) see are images. However, when transforming this to our digital-devices what we record are
numerical values for each of the points of the image (a matrix if you will)*/


/* ..(2).. MAT OpenCV Class 
"Mat" is OpenCV's C++ class for (storing) image-matrices.
It's analagous to the C-language's ("lplImage"), but w/ auto memory alloc.
It has 2 data-parts:
	(1) Header: constant-size var that stores matrix-size, etc.
	(2) Pointer to Matrix: image information */

// ... METHOD GLOSSARY ...

// equalizeHist(inputFrame, outputFrame) ==> equalize histogram of grayscale image 
// https://docs.opencv.org/4.0.0/d6/dc7/group__imgproc__hist.html#ga7e54091f0c937d49bf84152a16f76d6e


#include "pch.h"
#include <iostream>
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;
using namespace std;


// function protptyes
void detectAndDisplay(Mat frame);

// global variables
CascadeClassifier face_cascade;
String face_cascade_name = "Cascades/haarcascade_frontalface.xml";


int main()
{
	// ..(1).. boot cascades
	if (!face_cascade.load(face_cascade_name)) { printf("--(!) Error in loading face cascade"); return -1; }

	// ..(2).. read video stream
	int camera_device = 0; // 0 = webcame
	VideoCapture capture;
	capture.open(camera_device);
	if (!capture.isOpened()) { printf("--(!) Error in opening camera"); return -1;}

	Mat frame; // see note (2) on Mat 
	while (capture.read(frame)) {
		
		// run Object Detection on frame
		if (frame.empty()) break;
		detectAndDisplay(frame);

		// ESC to exit
		if (waitKey(10) == 27) break;
	}
	capture.release();
	destroyAllWindows();
	return 0;
}

void detectAndDisplay(Mat frame)
{
	Mat frame_gray;
	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	//-- Detect faces
	std::vector<Rect> faces;
	face_cascade.detectMultiScale(frame_gray, faces);
	for (size_t i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
		ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4);
		Mat faceROI = frame_gray(faces[i]);
	}
	imshow("detection", frame);
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
