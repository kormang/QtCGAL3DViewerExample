#pragma once
#include <QGLViewer/qglviewer.h>
#include <Qstring>

#include "typedefs.h"

class BSpline;
class PNtriangle;

class Viewer3D : public QGLViewer
{
private:
	Points3 points;
	Surface_mesh mesh;
	std::vector<BSpline*> bsplines;
	std::vector<PNtriangle*> pntriangles;
	int selectedPointIndex;

protected:
	virtual void draw();
	virtual void init();
	virtual void initializeGL();
	virtual void postSelection(const QPoint& point);
	inline void addPointImpl(float x, float y, float z) { points.push_back(Point_3(x, y, z)); };
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);

public:
	Viewer3D(QWidget* parent): selectedPointIndex(-1), QGLViewer(parent) {}

	void addPoint(float x, float y, float z);
	void clearPoints();
	void generateCube(const Point_3& center, float sideSize);
	void generateSphere(const Point_3& center, float radius);
	const Points3& getPoints() const { return points; };
	void setSurfaceMesh(const Surface_mesh& mesh) { this->mesh = mesh; };
	void addBSpline(BSpline* bspline);
	void removeBSpline(BSpline* bspline);
	void addPNtriangle(PNtriangle* pntriangle);
	void removePNtriangle(PNtriangle* pntriangle);
};
