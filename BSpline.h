#pragma once
#include <math.h>

#include "typedefs.h"

class BSpline
{
protected:
typedef std::vector<double> coefs_t;

	std::vector<coefs_t> coefs;
    int degree;
	int stepCount;
	const Points3& points;
	coefs_t calcSplineCoef3(double t);
	coefs_t calcSplineCoef2(double t);
	void drawSegment3(int segNum);
	void drawSegment2(int segNum);
public:
	bool closed;
	void drawSplineCurve();
	BSpline(const Points3& points, int degree, int stepCount = 10, bool closed = false);
	~BSpline(){};
};
