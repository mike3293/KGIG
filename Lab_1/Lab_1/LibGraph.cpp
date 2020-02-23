#include "pch.h"
#include "LibGraph.h"
#include "CMatrix.h"

#define SPACING 50 
#define PI 3.14159

void fillMatrix(CMatrix& matrix, double start)
{
	for (int i = 0; i < matrix.countRows(); i++)
	{
		for (int j = 0; j < matrix.countCols(); j++, start+=0.5)
		{
			matrix(i, j) = start;
		}
	}
}

void printMatrix(CDC* dc, int x, int y, CString title, CMatrix& matrix)
{
	CString str = L"";

	dc->TextOut(x, y, title);
	y += SPACING;
	for (int i = 0; i < matrix.countRows(); i++)
	{
		for (int j = 0; j < matrix.countCols(); j++)
		{
			str.Format(L"%.2f", matrix(i, j));
			dc->TextOut(x + j * SPACING, y + i * SPACING, str);
		}
	}
}

void printNumber(CDC* dc, int x, int y, CString title, double number)
{
	CString str = L"";
	dc->TextOut(x, y, title);
	str.Format(L"%.3f", number);
	dc->TextOut(x, y + SPACING, str);
}

double cos(CMatrix& left, CMatrix& right)
{
	return ScalarMult(left, right) / (module(left) * module(right));
}

CMatrix VectorMult(CMatrix& left, CMatrix& right)
{
	CMatrix result(3);
	result(0) = left(1) * right(2) - left(2) * right(1);
	result(1) = left(2) * right(0) - left(0) * right(2);
	result(2) = left(0) * right(1) - left(1) * right(0);
	return result;
}

double ScalarMult(CMatrix& left, CMatrix& right)
{
	double result = 0;
	for (int i = 0; i < left.countRows(); i++)
	{
		result += left(i) * right(i);
	}
	return result;
}

double module(CMatrix& vector)
{
	double sum = 0;
	for (int i = 0; i < vector.countRows(); i++)
	{
		sum += vector(i) * vector(i);
	}
	return sqrt(sum);
}

CMatrix sphericalToCartesian(CMatrix& point)
{
	double r = point(0),//радиус
		theta = point(1), // азимут, от оси Х
		phi = point(2); // угл, от оси Z

	CMatrix result(3);
	result(0) = r * sin(theta) * cos(phi);
	result(1) = r * sin(theta) * sin(phi);
	result(2) = r * cos(theta);
	return result;
}