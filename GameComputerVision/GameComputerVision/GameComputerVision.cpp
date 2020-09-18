///// game code written by student Mahdi Bentaleb Msc AI - Computer Vision 3d Lab 1
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define WIDTH 800
#define HEIGHT 600


Mat image;
int iksz, ipszilon;
Point centreMove;
Point TOPLEFT(2, 2), DOWNLEFT(2,HEIGHT),TOPRIGHT(WIDTH-2, 2),DOWNRIGHT(WIDTH-2,HEIGHT);
int WidthPl, HeightPl;
int directionX=1, directionY=1;
void drawWalls()
{
	//walls draw / i set  2 in place of 0 only so we can view the walls on the scene 
	line(image, TOPLEFT, TOPRIGHT, Scalar(255, 0, 0), 2);
	line(image, TOPLEFT, DOWNLEFT, Scalar(255, 0, 0), 2);
	line(image, TOPRIGHT, DOWNRIGHT, Scalar(255, 0, 0), 2);
}
void redraw() {
	rectangle(image, Point(0, 0), Point(WIDTH, HEIGHT), Scalar(0, 0, 0), CV_FILLED);
	// top wall
	if (ipszilon < 10)
	{
		directionY *= -1;
	}
	else if (ipszilon > HEIGHT - 10)
	{
		exit(0);
	}
	// left right wall
	if (iksz<10 || iksz > WIDTH - 10)
	{
		directionX *= -1;
	}// player collision
	else if ((iksz > centreMove.x - WidthPl / 2) && (iksz < centreMove.x + WidthPl / 2))
	{
		if (ipszilon >= centreMove.y - HeightPl / 2)
		{
			directionY *= -1;
		}	
	}
	iksz += directionX * 10;
	ipszilon += directionY * 10;

	circle(image, Point(iksz, ipszilon ), 10, Scalar(0, 255, 0), CV_FILLED);
	imshow("Display window", image);                   // Show our image inside it.
}
void drawplayer(Point center)
{
	drawWalls();
	Point P1, P2;
	P1.x = center.x - WidthPl / 2;
	P2.x = center.x + WidthPl / 2;
	P1.y = center.y - HeightPl / 2;
	P2.y = center.y + HeightPl / 2;
	rectangle(image, Point(P1), Point(P2), Scalar(0, 0, 255),CV_FILLED);
	imshow("Display window", image);                   // Show our image inside it.
}

void MouseCallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_MOUSEMOVE)
	{		
		if ((x < WidthPl/2) || (x > WIDTH - WidthPl/2))
		{
			return;
		}
		centreMove=Point(x, 585);
	}
}


int main(int argc, char** argv)
{
	image = Mat::zeros(600, 800, CV_8UC3);
	iksz = WIDTH/2;
	ipszilon = HEIGHT/2;
	WidthPl = 100;
	HeightPl = 10;

	namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.

	setMouseCallback("Display window", MouseCallBackFunc, NULL);

	imshow("Display window", image);                   // Show our image inside it.
	int key;
	while (true) {
		key = cvWaitKey(100);
		if (key == 27) break;
		redraw();
		drawplayer(centreMove);
	}
	return 0;
}
