#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/photo/photo.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/contrib/contrib.hpp"

#include "opencv2/core/core_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"

#include <iostream>
#include <windows.h>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	String command = "";
	String exit = "e";
	String msee = "m";
	String local = "l";

	bool isRunning = true;
	while (isRunning){

		//prints out the menu options the user can choose from
		cout << "Type\n\t\t'm' for MSEE_Cam; \n\t\t'l' for local video about EE238_Cam, \n\t\t'e' for exit.\n\n\t\t\t";

		//prompts the user for an option 
		cin >> command;

		if (command.compare(exit) == 0){
			isRunning = false;
		}

		//Play the video stream from MSEE_Cam
		if (command.compare(msee) == 0){
			VideoCapture cap;
			cout << "Loading......" << endl;
			cap.open("http://ipv2.ecn.purdue.edu/mjpg/video.mjpg");
			if (!cap.isOpened())  // if not success, exit program
			{
				cout << "Video Stream cannot be connected, please check Network." << endl;
				return -1;
			}
			
			double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video

			cout << "Traffic Light Display from MSEE_Cam\n\nFrame per seconds : " << fps << endl;

			namedWindow(command, CV_WINDOW_AUTOSIZE); //create a window 

			Mat frame;

			while (1){
				bool bSuccess = cap.read(frame); // read a new frame from video
				if (!bSuccess) //if not success, break loop
				{
					cout << "Cannot read the frame from video file" << endl;
					break;
				}
				
				moveWindow("MSEE_Cam",0,0);
				imshow("MSEE_Cam", frame);
				waitKey(10);

				//Test for MSEE_Cam
				int x1 = 263; int x2 = 384; int x3 = 513;
				int y1 = 262; int y2 = 266; int y3 = 265;

				Rect rect1(x1, y1, 8, 6); //ROI of left crossroad light
				Rect rect2(x1, y1, 8, 6); //ROI of middle crossroad light
				Rect rect3(x2, y2, 8, 6); //ROI of right crossroad light
				Size enlarge(80, 60);

				Mat roi1;
				Mat roi1_large;
				frame(rect1).copyTo(roi1);
				
				resize(roi1, roi1_large, enlarge);//resize image
				//pyrUp(roi1,roi1_large,Size(roi1.cols*2,roi1.rows*2));


				moveWindow("Left",400,0);
				moveWindow("Middle",480,0);
				moveWindow("Right",560,0);
				imshow("Left", roi1_large);
				namedWindow("Left", CV_WINDOW_AUTOSIZE);
				waitKey(10);

				Mat roi2;
				Mat roi2_large;
				frame(rect2).copyTo(roi2);
				resize(roi2, roi2_large, enlarge);//resize image
				imshow("Middle", roi2_large);
				namedWindow("Middle", CV_WINDOW_AUTOSIZE); //create a window called "Northwestern Avenue"
				waitKey(10);

				Mat roi3;
				Mat roi3_large;
				frame(rect3).copyTo(roi3);
				resize(roi3, roi3_large, enlarge);//resize image
				imshow("Right", roi3_large);
				namedWindow("Right", CV_WINDOW_AUTOSIZE); 
				waitKey(10);
				
				

			}
		}

		//Play the local video about EE238_Cam
		bool notReadable = true;
		if (command.compare(local) == 0){
			bool contplay = true;
			VideoCapture cap;
			while (notReadable){ //If not readable, loop back
				cout << "\n\nPlease type in the video serial number.\n\n\t\t\t";
				cin >> command;

				SetCurrentDirectoryA("E:\\EE238_Cam\\");
				
				cap.open(command + ".avi");
				if (!cap.isOpened())  // if not success, exit program
				{
					cout << "Cannot open the video cam" << endl;
				}
				else{
					notReadable = false;
				}
			}
			double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video

			cout << "Traffic Light Display from EE238\n\nFrame per seconds : " << fps << endl;

			namedWindow(command, CV_WINDOW_AUTOSIZE); 

			Mat frame;
			while (contplay){

				bool bSuccess = cap.read(frame); // read a new frame from video

				if (!bSuccess) //if not success, break loop
				{
					cout << "Cannot read the frame from video file" << endl;
					break;

				}
				moveWindow("EE238_Cam",0,0);
				imshow("EE238_Cam", frame);
				waitKey(10);
				int x1 = 779;
				int y1 = 272;
				int x2 = 834;
				int y2 = 272;

				Rect rect1(x1, y1, 10, 30); //ROI of left traffic light
				Rect rect2(x2, y2, 10, 30); //ROI of right traffic light
				Size enlarge(100, 300);
				if (command.compare("4") == 0){
					x1 = 720;
					y1 = 270;
					x2 = 789;
					y2 = 372;
				}

				Mat roi1;
				Mat roi1_large;
				frame(rect1).copyTo(roi1);
				resize(roi1, roi1_large, enlarge);//resize image
				
				moveWindow("Left",1075,0);
				imshow("Left", roi1_large);
				namedWindow("Left", CV_WINDOW_AUTOSIZE);
				waitKey(10);
				Mat roi2;
				Mat roi2_large;
				frame(rect2).copyTo(roi2);
				resize(roi2, roi2_large, enlarge);//resize image
				moveWindow("Right",1180,0);
				
				imshow("Right", roi2_large);
				namedWindow("Right", CV_WINDOW_AUTOSIZE); 
				waitKey(10);
			}
		}

		


		if (waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
		{
			isRunning = false;
		}

	}

	return 0;

}
