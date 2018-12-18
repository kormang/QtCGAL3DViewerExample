#include "SubdivisionCurve.h"
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>

SubdivisionCurve::SubdivisionCurve(const Points3& points, int level): points(points), level(level)
{
    subdivide();
}

void SubdivisionCurve::subdivide()
{
    for (int i = 0; i < level; ++i) {
        Points3 temp;
        for (int j = 0; j < points.size(); ++j) {
            Point_3 a = points[j];
            Point_3 b = points[(j + 1) % points.size()];
            temp.emplace_back(
                a.x() + (b.x() - a.x()) * 0.25,
                a.y() + (b.y() - a.y()) * 0.25,
                a.z() + (b.z() - a.z()) * 0.25
            );
            temp.emplace_back(
                a.x() + (b.x() - a.x()) * 0.75,
                a.y() + (b.y() - a.y()) * 0.75,
                a.z() + (b.z() - a.z()) * 0.75
            );
        }
        points = std::move(temp);
    }
}

void SubdivisionCurve::drawSubdivisionCurve()
{
	glLineWidth(2.0f);
	glColor4f(0.5f, 1.0f, 0.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < points.size(); ++i) {
		glVertex3f(points[i].x(), points[i].y(), points[i].z());
	}
	glEnd();
}