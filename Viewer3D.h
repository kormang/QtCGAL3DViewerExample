#pragma once
#include <QGLViewer/qglviewer.h>
#include <Qstring>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef K::Point_3 Point_3;
typedef std::vector<Point_2> Points;
typedef std::vector<Point_3> Points3;

class Viewer3D : public QGLViewer
{
private:
	Points3 points;

protected:
	virtual void draw();
	virtual void init();
	virtual void initializeGL();

public:
	Viewer3D(QWidget* parent): QGLViewer(parent) {}

	void addPoint(float x, float y, float z);
	void clearPoints();
};
