#pragma once
#include "typedefs.h"
#include <math.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>

class PNtriangle
{
	// Координаты и нормали обыкновенного треугольника
	Point_3 p300, p030, p003;
	Point_3 n200, n020, n002;
	// Дополнительные координаты и нормали
	Point_3 p210, p120, p201, p102, p021, p012, p111;
	Point_3 n110, n011, n101;

    int tessellationLevel;

    void calcPNcoefs();
    Point_3 pointFromBarycentric(double u, double v, double w);
    Point_3 normalFromBarycentric(double u, double v, double w);
    void drawPoint(double u, double v, double w);

public:
	PNtriangle(Point_3 p1, Point_3 p2, Point_3 p3,
		Point_3 n1, Point_3 n2, Point_3 n3, int tessellationLevel = 0);
    PNtriangle(Point_3 p1, Point_3 p2, Point_3 p3, int tessellationLevel = 0);
	void drawTriangle();
};
