#pragma once
#include <opencv.hpp>
#include <iostream>
#ifdef BUILD_DLLTRANSFER //看是用_declspec(dllexport)还是_declspec(dllimport)
#define API_SYMBOL _declspec(dllexport) 
#else
#define API_SYMBOL _declspec(dllimport)
#endif // BUILD_DLLTRANSFER

using namespace cv;
using namespace std;

struct sTransfer
{
	Size2f m_SizeDisplacement;
	Point2f m_PointCenter;
	double m_dAngle;
	bool m_bFlagOrderTranslateRotate;
};

class MyVector
{
public:
	MyVector(const Point2f& Point1, const Point2f& Point2);
	~MyVector();
	void f_print();
	Point2f m_PointOrigin;
	Point2f m_PointTerminal;
private:

};

MyVector::MyVector(const Point2f& Point1 = Point2f(), const Point2f& Point2 = Point2f()) :m_PointOrigin(Point1), m_PointTerminal(Point2)
{
}

MyVector::~MyVector()
{
}

void MyVector::f_print()
{
	cout.precision(19);
	cout << m_PointOrigin << " " << m_PointTerminal << endl;
}

API_SYMBOL void f_PointTranslate(const Point2f& ePointMoveDirection, Point2f& eP);
API_SYMBOL void f_PointTranslate(const sTransfer& eT, Point2f& eP);
API_SYMBOL void f_Translate(const Point2f& ePointMoveDirection, MyVector& eV);
API_SYMBOL void f_Translate(sTransfer& eT, MyVector& eV);
API_SYMBOL void f_PointRotate(const sTransfer& eT, Point2f& ePoint);
API_SYMBOL void f_Rotate(sTransfer& eT, MyVector& eV);
API_SYMBOL void f_Transfer(sTransfer& eT, MyVector& eV);
