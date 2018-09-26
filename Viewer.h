#pragma once
#include <QGLViewer/qglviewer.h>
#include <Qstring>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/triangulate_faces.h>
#include <CGAL/Polyhedron_3.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 Point_3;
typedef std::vector<Point_3> Points;
typedef CGAL::Surface_mesh<Point_3> Surface_mesh;

class Viewer : public QGLViewer
{
protected:
	Points points;
	Surface_mesh mesh;

	virtual void draw();
	virtual void init();
	virtual void initializeGL();

public:
	void setPoints(const Points& points) {
		this->points = points;
	}

	void setMesh(const Surface_mesh& mesh) {
		this->mesh = mesh;
	}
};
