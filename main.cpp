//#include <opencv\cv.h>


#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <algorithm>


void colorReduce(cv::Mat& image)
{
	int nl = image.rows;                   
	int nc = image.cols * image.channels(); 

	for (int j = 0; j < nl; j++)
	{
		uchar* data = image.ptr<uchar>(j);
		//cout << sizeof(data) << endl;

		for (int i = 0; i < nc; i += 3)
		{

			if (data[i] <= 128 && data[i + 1] <= 128 && data[i + 2] <= 128) { //000
				data[i] = 255; data[i + 1] = 0; data[i + 2] = 0;
			}
			else if (data[i] > 128 && data[i + 1] <= 128 && data[i + 2] <= 128) {//100 
				data[i] = 255; data[i + 1] = 191; data[i + 2] = 0;
			}
			else if (data[i] > 128 && data[i + 1] > 128 && data[i + 2] <= 128) {//110 
				data[i] = 129; data[i + 1] = 255; data[i + 2] = 0;
			}
			else if (data[i] <= 128 && data[i + 1] > 128 && data[i + 2] > 128) {//011 
				data[i] = 0; data[i + 1] = 255; data[i + 2] = 61;
			}
			else if (data[i] > 128 && data[i + 1] <= 128 && data[i + 2] > 128) {//101 
				data[i] = 0; data[i + 1] = 255; data[i + 2] = 252;
			}
			else if (data[i] <= 128 && data[i + 1] > 128 && data[i + 2] <= 128) {//010 
				data[i] = 0; data[i + 1] = 68; data[i + 2] = 255;
			}
			else if (data[i] <= 128 && data[i + 1] <= 128 && data[i + 2] > 128) {//001 
				data[i] = 122; data[i + 1] = 0; data[i + 2] = 255;
			}
			else if (data[i] > 128 && data[i + 1] > 128 && data[i + 2] > 128) {//001 
				data[i] = 255; data[i + 1] = 0; data[i + 2] = 192;
			}
		}
	}
}

template <size_t rows, size_t cols>
void createMatArr(int(&frameArr)[rows][cols], cv::Mat& image)
{
	int nl = image.rows;                    
	int nc = image.cols * image.channels();

	for (int j = 0; j < nl; j++)
	{
		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; i += 3)
		{

			if (data[i] <= 128 && data[i + 1] <= 128 && data[i + 2] <= 128) { //000
				frameArr[j][i / 3] = 0;
			}
			else if (data[i] > 128 && data[i + 1] <= 128 && data[i + 2] <= 128) {//100 
				frameArr[j][i / 3] = 1;
			}
			else if (data[i] > 128 && data[i + 1] > 128 && data[i + 2] <= 128) {//110 
				frameArr[j][i / 3] = 2;
			}
			else if (data[i] <= 128 && data[i + 1] > 128 && data[i + 2] > 128) {//011 
				frameArr[j][i / 3] = 3;
			}
			else if (data[i] > 128 && data[i + 1] <= 128 && data[i + 2] > 128) {//101 
				frameArr[j][i / 3] = 4;
			}
			else if (data[i] <= 128 && data[i + 1] > 128 && data[i + 2] <= 128) {//010 
				frameArr[j][i / 3] = 5;
			}
			else if (data[i] <= 128 && data[i + 1] <= 128 && data[i + 2] > 128) {//001 
				frameArr[j][i / 3] = 6;
			}
			else if (data[i] > 128 && data[i + 1] > 128 && data[i + 2] > 128) {//001 
				frameArr[j][i / 3] = 7;
			}
		}
	}
}







template <size_t rows, size_t cols>
void setColorByCyclic(int (&frameArr)[rows][cols], cv::Mat &image) {
	int nl = image.rows;
	int nc = image.cols * image.channels();

	for (int j = 0; j < nl; j++)
	{

		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; i += 3)
		{
			switch (frameArr[j][i/3]) {
				case 0:
					data[i] = 255; data[i + 1] = 0; data[i + 2] = 0;
					break;
				case 1:
					data[i] = 255; data[i + 1] = 191; data[i + 2] = 0;
					break;
				case 2:
					data[i] = 129; data[i + 1] = 255; data[i + 2] = 0;
					break;
				case 3:
					data[i] = 0; data[i + 1] = 255; data[i + 2] = 61;
					break;
				case 4:
					data[i] = 0; data[i + 1] = 255; data[i + 2] = 252;
					break;
				case 5:
					data[i] = 0; data[i + 1] = 68; data[i + 2] = 255;
					break;
				case 6:
					data[i] = 122; data[i + 1] = 0; data[i + 2] = 255;
					break;
				case 7:
					data[i] = 255; data[i + 1] = 0; data[i + 2] = 192;
					break;

				default:
					break;
				
			}

		}
	}

}


template <size_t rows, size_t cols>
void randomFrame(int(&array)[rows][cols])
{
	for (size_t i = 0; i < rows; ++i)
	{
		
		for (size_t j = 0; j < cols; ++j)
			array[i][j] = rand() % 8;
	}
}

template <size_t rows, size_t cols>
void deepCopy(int(&array)[rows][cols], int(&array2)[rows][cols])
{

	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < cols; ++j)
			array2[i][j] = array[i][j];
	}
}

struct position{
	int x;
	int y;
};

int main() {
	const int gridX = 64*5;
	const int gridY = 36*5;
	const int threshold = 1;

	std::vector<position> expections;

	int cellularData[gridX][gridY];
	int copyCellularData[gridX][gridY];
	int frameArray[gridX][gridY];
	randomFrame(cellularData);
	deepCopy(cellularData, copyCellularData);
	cv::VideoCapture cap(1);
	cv::Mat frame;
	cv::Mat resizedframe;
	cv::Mat filteredImage;
	cv::Mat cellular(gridY, gridX, CV_8UC3);
	cv::Mat croppedFrame;
	setColorByCyclic(cellularData, cellular);
	while (1)
	{
		cap.read(frame);
		resize(frame, resizedframe, cv::Size(gridX, gridY));
		blur(resizedframe, filteredImage, cv::Size(5, 5));
		resize(filteredImage, filteredImage, cv::Size(gridX, gridY));
		colorReduce(filteredImage);
		createMatArr(frameArray, filteredImage);

		resize(cellular, cellular, cv::Size(gridX, gridY), 0, 0, cv::INTER_NEAREST);
		deepCopy(copyCellularData, cellularData);
		expections.clear();
		for (int i = 0; i < gridX; i++) {
			for (int j = 0; j < gridY; j++) {
				int count = 0;
				bool flag = false;
				for (int k = -1; k < 2; k++) {
					for (int l = -1; l < 2; l++) {
						int currentX = (i + k + gridX) % gridX;
						int currentY = (j + l + gridY) % gridY;
						int tempMain = cellularData[i][j];
						int tempCheck = cellularData[currentX][currentY];
						if ( !((cellularData[i][j]+1) %8 == cellularData[currentX][currentY] %8)) continue;
						if (!(frameArray[i][j] == frameArray[currentX][currentY])){
							flag = true;
							continue;
						}
						count++;
					}
				}
				if (count >= threshold) {
					copyCellularData[i][j] = (cellularData[i][j] + 1) % 8;
				}
				else  copyCellularData[i][j] = cellularData[i][j];
				if (flag == true) {
					position tempPosition{ i, j };
					expections.push_back(tempPosition);
				}
			}
		}
		for (position i : expections) {
			copyCellularData[i.x][i.y] = frameArray[i.x][i.y];
		}
		for (int i = gridX / 2; i < gridX; i++) {
			for (int j = gridX / 2; j < gridX; j++) {

			}
		}
		setColorByCyclic(copyCellularData, cellular);
		resize(frame, frame, cv::Size(2048, 1152));
		resize(cellular, cellular, cv::Size(2048, 1152),0 ,0 , cv::INTER_NEAREST);
		frame(cv::Rect(0, 0, 2048/2, 1152)).copyTo(croppedFrame);
		croppedFrame.copyTo(cellular(cv::Rect(2048/2, 0, 2048/2, 1152)));
		imshow("camera", cellular);
		cv::waitKey(16.66666);

	}
	return 0;
}