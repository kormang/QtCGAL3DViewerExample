#include "BSpline.h"
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>

inline int clamp(int val, int minVal, int maxVal)
{
    return std::min(std::max(val, minVal), maxVal);
}

BSpline::coefs_t BSpline::calcSplineCoef3(double t)
{
	coefs_t coefs;
    coefs.reserve(4);

	coefs.push_back((1.0 - t) * (1.0 - t) * (1.0 - t) / 6.0);
	coefs.push_back((3.0 * t * t * t - 6.0 * t * t + 4) / 6.0);
	coefs.push_back((-3.0 * t * t * t + 3 * t * t + 3 * t + 1) / 6.0);
	coefs.push_back(t * t * t / 6.0);

	return coefs;
}

BSpline::coefs_t BSpline::calcSplineCoef2(double t)
{
	coefs_t coefs;
    coefs.reserve(3);

	coefs.push_back((1.0 - t) * (1.0 - t) / 2.0);
	coefs.push_back((-2.0 * t * t + 2.0 * t + 1) / 2.0);
	coefs.push_back(t * t / 2.0);

	return coefs;
}

BSpline::BSpline(const Points3& points, int degree, bool closed, int stepCount)
: degree(degree), stepCount(stepCount), points(points), closed(closed)
{
    // Генерация коэффициентов B-сплайна
	coefs = std::vector<coefs_t>();
	for (int i = 0; i < stepCount; i++) {
		coefs_t coef = degree == 3
            ? calcSplineCoef3(i / (double)stepCount)
            : calcSplineCoef2(i / (double)stepCount);
		coefs.push_back(coef);
	}
}

void BSpline::drawSegment3(int segNum)
{
	int pNum = points.size();
	int p0, p1, p2, p3;
	//Вычисление номеров вершин для построения сплайна
	if (closed == false) {
		p0 = clamp(segNum - 2, 0, pNum - 1);
		p1 = clamp(segNum - 1, 0, pNum - 1);
		p2 = clamp(segNum, 0, pNum - 1);
		p3 = clamp(segNum + 1, 0, pNum - 1);
	} else {
		p0 = (segNum - 1 + pNum) % pNum;
		p1 = (segNum + pNum) % pNum;
		p2 = (segNum + 1 + pNum) % pNum;
		p3 = (segNum + 2 + pNum) % pNum;
	}
	// По заранее вычисленным коэффициентам
	// Вычисляем промежуточные точки сплайна
	for (int i = 0; i < stepCount; i++) {
		double x = coefs.at(i)[0] * points[p0].x()
			+ coefs.at(i)[1] * points[p1].x()
			+ coefs.at(i)[2] * points[p2].x()
			+ coefs.at(i)[3] * points[p3].x();
		double y = coefs[i][0] * points[p0].y()
			+ coefs.at(i)[1] * points[p1].y()
			+ coefs.at(i)[2] * points[p2].y()
			+ coefs.at(i)[3] * points[p3].y();
		double z = coefs.at(i)[0] * points[p0].z()
			+ coefs.at(i)[1] * points[p1].z()
			+ coefs.at(i)[2] * points[p2].z()
			+ coefs.at(i)[3] * points[p3].z();

			glVertex3f(x, y, z);
	}
}

void BSpline::drawSegment2(int segNum)
{
	int pNum = points.size();
	int p0, p1, p2;
	//Вычисление номеров вершин для построения сплайна
	if (closed == false) {
		p0 = clamp(segNum - 1, 0, pNum - 1);
		p1 = clamp(segNum, 0, pNum - 1);
		p2 = clamp(segNum + 1, 0, pNum - 1);
	} else {
		p0 = (segNum - 1 + pNum) % pNum;
		p1 = (segNum + pNum) % pNum;
		p2 = (segNum + 1 + pNum) % pNum;
	}
	// По заранее вычисленным коэффициентам
	// Вычисляем промежуточные точки сплайна
	for (int i = 0; i < stepCount; i++) {
		double x = coefs.at(i)[0] * points[p0].x()
			+ coefs[i][1] * points[p1].x()
			+ coefs[i][2] * points[p2].x();
		double y = coefs[i][0] * points[p0].y()
			+ coefs[i][1] * points[p1].y()
			+ coefs[i][2] * points[p2].y();
		double z = coefs[i][0] * points[p0].z()
			+ coefs[i][1] * points[p1].z()
			+ coefs[i][2] * points[p2].z();

			glVertex3f(x, y, z);
	}
}

void BSpline::drawSplineCurve()
{
	int segmentsCount;
	glLineWidth(2.0f);
	glColor4f(1.0f, 1.0f, 0.33f * degree, 1.0f);
	if (closed == false) {
		glBegin(GL_LINE_STRIP);
		segmentsCount = std::max(static_cast<int>(points.size()) + degree - 2, 0);
	} else {
		segmentsCount = points.size(); //Сегмент между первой и последней вершиной
		glBegin(GL_LINE_LOOP);
	}

    if (degree == 3) {
        for (int i = 0; i < segmentsCount; i++) {
            drawSegment3(i);
        }
    } else {
		for (int i = 0; i < segmentsCount; i++) {
			drawSegment2(i);
		}
    }

	glEnd();
}
