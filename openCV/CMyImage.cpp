#include "stdafx.h"
#include "CMyImage.h"

int _tmain(int argc, _TCHAR* argv[])
{

	IplImage* img;

	img = cvLoadImage("im1_2.bmp", -1);
	CMyImage <double> im1(img->width, img->height, img->nChannels, img->imageData);

	img = cvLoadImage("im2_2.bmp", -1);
	CMyImage <double> im2(img->width, img->height, img->nChannels, img->imageData);

	CMyImage <double> im3;
	im3 = im2 + im1;

	IplImage* result;
	result = cvCreateImage(cvSize(im3.GetWidth(), im3.GetHeight()), IPL_DEPTH_8U, im3.GetChannel());
	int pixel_number = im3.GetWidth()*im3.GetHeight()*im3.GetChannel();
	for (int i = 0; i < pixel_number; i++)
	{
		if (im3.m_img_data[i] >= 255)
			result->imageData[i] = 255;
		else if (im3.m_img_data[i] <= 0)
			result->imageData[i] = 0;
		else
			result->imageData[i] = static_cast<unsigned char>(im3.m_img_data[i]);
	}

	cvSaveImage("result_plus.bmp", result);
	//cvSaveImage("D:/Image/im1_result.bmp", result);

	
	cout << "plus end" << endl;

	//minus**************************
	cout << "minus start" << endl;

	img = cvLoadImage("im1_1.bmp", -1);
	CMyImage <double> im4(img->width, img->height, img->nChannels, img->imageData);

	img = cvLoadImage("im1_2.bmp", -1);
	CMyImage <double> im5(img->width, img->height, img->nChannels, img->imageData);

	CMyImage <double> im6;
	im6 = im4 - im5;

	result = cvCreateImage(cvSize(im6.GetWidth(), im6.GetHeight()), IPL_DEPTH_8U, im6.GetChannel());
	int pixel_number1 = im6.GetWidth()*im6.GetHeight()*im6.GetChannel();
	for (int i = 0; i < pixel_number1; i++)
	{
		if (im6.m_img_data[i] >= 255)
			result->imageData[i] = 255;
		else if (im6.m_img_data[i] <= 0)
			result->imageData[i] = 0;
		else
			result->imageData[i] = static_cast<unsigned char>(im6.m_img_data[i]);
	}

	cvSaveImage("result_minus.bmp", result);
	//cvSaveImage("D:/Image/im1_result.bmp", result);


	cout << "minus end" << endl;

	//******************곱하기

	cout << "multi start" << endl;
	
	img = cvLoadImage("im2_2_gray.bmp", -1);
	CMyImage <double> im7(img->width, img->height, img->nChannels, img->imageData);

	
	CMyImage <double> im8;
	im8 = im7*2;

	result = cvCreateImage(cvSize(im8.GetWidth(), im8.GetHeight()), IPL_DEPTH_8U, im8.GetChannel());
	int pixel_number2 = im8.GetWidth()*im8.GetHeight()*im8.GetChannel();
	for (int i = 0; i < pixel_number2; i++)
	{
		if (im8.m_img_data[i] >= 255)
			result->imageData[i] = 255;
		else if (im8.m_img_data[i] <= 0)
			result->imageData[i] = 0;
		else
			result->imageData[i] = static_cast<unsigned char>(im8.m_img_data[i]);
	}

	cvSaveImage("result_multi.bmp", result);
	//cvSaveImage("D:/Image/im1_result.bmp", result);

	
	cout << "multi end" << endl;

	//*******************************나누기
	cout << "sub start" << endl;

	img = cvLoadImage("im2_1.bmp", -1);
	CMyImage <double> im9(img->width, img->height, img->nChannels, img->imageData);


	CMyImage <double> im10;
	im10 = im9 / 2;

	result = cvCreateImage(cvSize(im10.GetWidth(), im10.GetHeight()), IPL_DEPTH_8U, im10.GetChannel());
	int pixel_number3 = im10.GetWidth()*im10.GetHeight()*im10.GetChannel();
	for (int i = 0; i < pixel_number3; i++)
	{
		if (im10.m_img_data[i] >= 255)
			result->imageData[i] = 255;
		else if (im10.m_img_data[i] <= 0)
			result->imageData[i] = 0;
		else
			result->imageData[i] = static_cast<unsigned char>(im10.m_img_data[i]);
	}

	cvSaveImage("result_sub.bmp", result);
	//cvSaveImage("D:/Image/im1_result.bmp", result);

	//할당된 메모리 공간 해제(IplImage)
	cvReleaseImage(&img);
	cvReleaseImage(&result);

	cout << "sub end" << endl;


	return 0;
}