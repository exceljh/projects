#pragma once
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <iostream>
using namespace std;

template<typename T>
class CMyImage
{
public:
	CMyImage() { cout << "CMyImage" << endl; }

	// ������: �Է� ���� data�� ���� ���
	CMyImage(int p_Width, int p_Height, int p_Channel)
		:m_Width(p_Width), m_Height(p_Height), m_Channel(p_Channel)
	{
		cout << "CMyImage(int,int,int)" << endl;
		m_img_data = new T[m_WidthStep * m_Height];
	}

	// ������: �Է� ���� data�� �ִ°�� 
	CMyImage(int p_Width, int p_Height, int p_Channel, char* input)
		:m_Width(p_Width), m_Height(p_Height), m_Channel(p_Channel)
	{
		cout << "CMyImage(int,int,int,char*)" << endl;
		m_img_data = new T[m_WidthStep * m_Height];
		for (int i = 0; i < m_WidthStep * m_Height; i++)
		{
			m_img_data[i] = static_cast<unsigned char>(input[i]);
			//CMy_img_data[i] = (unsigned char)input[i];
		}
	}

	// ���� ������ 
	CMyImage(const CMyImage &rhs)
	{
		cout << "CMyImage: &rhs" << endl;
		m_Channel = rhs.m_Channel;
		m_Width = rhs.m_Width;
		m_Height = rhs.m_Height;
		m_WidthStep = rhs.m_WidthStep;
		m_img_data = new T[m_WidthStep * m_Height];
		memcpy(m_img_data, rhs.m_img_data, m_WidthStep * m_Height * sizeof(T));
	}

	// �̵� ������
	CMyImage(const CMyImage &&rhs)
	{
		cout << "CMyImage: &&rhs" << endl;
		m_Channel = rhs.m_Channel;
		m_Width = rhs.m_Width;
		m_Height = rhs.m_Height;
		m_WidthStep = rhs.m_WidthStep;
		m_img_data = new T[m_WidthStep * m_Height];
		memcpy(m_img_data, rhs.m_img_data, m_WidthStep * m_Height * sizeof(T));
	}

	~CMyImage()
	{
		cout << "~CMyImage" << endl;
		delete[] m_img_data;
	}


	// operator ������ ���� 
	//���Կ�����
	CMyImage& operator=(const CMyImage &rhs)
	{
		cout << "operator= " << endl;
		if (this == &rhs)
			return *this;

		m_Channel = rhs.m_Channel;
		m_Width = rhs.m_Width;
		m_Height = rhs.m_Height;
		m_WidthStep = rhs.m_WidthStep;
		if (m_img_data)
			delete[] m_img_data;

		if (rhs.m_img_data != NULL)
		{
			m_img_data = new T[m_WidthStep * m_Height];
			memcpy(m_img_data, rhs.m_img_data, m_WidthStep * m_Height * sizeof(T));
		}
		return *this;
	}

	// ���� ������
	CMyImage operator+(const CMyImage<T> &rhs)
	{
		CMyImage<T> result(m_Width, m_Height, m_Channel);

		for (int i = 0; i < m_WidthStep*m_Height; i++)
		{
			result.m_img_data[i] = m_img_data[i] + rhs.m_img_data[i];
		}

		return result;
	}

	// ���� ������
	CMyImage operator-(const CMyImage<T> &rhs)
	{
		CMyImage<T> result(m_Width, m_Height, m_Channel);

		for (int i = 0; i < m_WidthStep*m_Height; i++)
		{
			result.m_img_data[i] = m_img_data[i] - rhs.m_img_data[i];
		}

		return result;
	}

	// ���� ������
	template<typename P>
	CMyImage operator*(P param)
	{
		CMyImage<T> result(m_Width, m_Height, m_Channel);

		for (int i = 0; i < m_WidthStep*m_Height; i++)
		{
			result.m_img_data[i] = m_img_data[i]*param;
		}

		return result;
	}


	// ������ ������
	template<typename Q>
	CMyImage operator/(Q param)
	{
		CMyImage<T> result(m_Width, m_Height, m_Channel);

		for (int i = 0; i < m_WidthStep*m_Height; i++)
		{
			result.m_img_data[i] = m_img_data[i] / param;
		}

		return result;
	}


	int GetWidth() { return m_Width; }
	int GetHeight() { return m_Height; }
	int GetChannel() { return m_Channel; }

	// ��� ���� ����
public:
	T *m_img_data = NULL;
private:
	int m_Width = 0;
	int m_Height = 0;
	int m_Channel = 0;
	int m_WidthStep = m_Width * m_Channel;
};
