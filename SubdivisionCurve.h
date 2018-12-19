#pragma once
#include <math.h>

#include "typedefs.h"

class SubdivisionCurve
{
protected:
	Points3 points;
    uint level;
    void subdivide();
public:
	bool closed;
	void drawSubdivisionCurve();
	SubdivisionCurve(const Points3& points, uint level);
	~SubdivisionCurve(){};
};
