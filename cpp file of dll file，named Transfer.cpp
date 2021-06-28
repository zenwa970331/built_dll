#include "pch.h" //这个放最开头，在Visual Studio中,预编译的头文件通常命名为“pch.h”(用于基于控制台的应用程序),但可以使用不同的名称,或者根本不使用它.预编译头文件(如果有)由项目设置决定.
#define BUILD_DLLTRANSFER //define一下，让头文件Transfer.h中默认的_declspec(dllimport)变成_declspec(dllexport)
#include "Transfer.h" //把头文件加进来

void f_PointTranslate(const Point2f& ePointMoveDirection, Point2f& eP)
{
	Mat qMat_TransformationMatrix = (Mat_<float>(3, 3) << 1, 0, ePointMoveDirection.x, 0, 1, ePointMoveDirection.y, 0, 0, 1);
	Mat qMat_Point2f = (Mat_<float>(3, 1) << eP.x, eP.y, 1);
	qMat_Point2f = qMat_TransformationMatrix * qMat_Point2f;
	eP.x = qMat_Point2f.at<float>(0, 0);
	eP.y = qMat_Point2f.at<float>(1, 0);
}

void f_PointTranslate(const sTransfer& eT, Point2f& eP)
{
	Point2f qPointMoveDirection;
	qPointMoveDirection.x = eT.m_SizeDisplacement.width;
	qPointMoveDirection.y = eT.m_SizeDisplacement.height;
	f_PointTranslate(qPointMoveDirection, eP);
}

void f_Translate(const Point2f& ePointMoveDirection, MyVector& eV)
{
	f_PointTranslate(ePointMoveDirection, eV.m_PointOrigin);
	f_PointTranslate(ePointMoveDirection, eV.m_PointTerminal);
}

void f_Translate(sTransfer& eT, MyVector& eV)
{
	f_PointTranslate(eT, eV.m_PointOrigin);
	f_PointTranslate(eT, eV.m_PointTerminal);
	f_PointTranslate(eT, eT.m_PointCenter);
}

void f_PointRotate(const sTransfer& eT, Point2f& ePoint)
{
	f_PointTranslate(eT.m_PointCenter * -1, ePoint);
	Mat qMat_RotateMatrix = (Mat_<float>(3, 3) << cos(eT.m_dAngle), -sin(eT.m_dAngle), 0, sin(eT.m_dAngle), cos(eT.m_dAngle), 0, 0, 0, 1);
	Mat qMat_Point2f = (Mat_<float>(3, 1) << ePoint.x, ePoint.y, 1);
	qMat_Point2f = qMat_RotateMatrix * qMat_Point2f;
	ePoint.x = qMat_Point2f.at<float>(0, 0);
	ePoint.y = qMat_Point2f.at<float>(1, 0);
	f_PointTranslate(eT.m_PointCenter, ePoint);
}

void f_Rotate(sTransfer& eT, MyVector& eV)
{
	f_PointRotate(eT, eV.m_PointOrigin);
	f_PointRotate(eT, eV.m_PointTerminal);
}

void f_Transfer(sTransfer& eT, MyVector& eV)
{
	if (eT.m_bFlagOrderTranslateRotate == 1)
	{
		f_Rotate(eT, eV);
		f_Translate(eT, eV);
	}
	else
	{
		f_Translate(eT, eV);
		f_Rotate(eT, eV);
	}
}

int f_add(int a, int b)
{
	return a+b;
}
