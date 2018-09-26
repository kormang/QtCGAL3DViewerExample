#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_3.h>
#include <vector>
#include <QApplication>
#include "Viewer.h"

int main(int argc, char** argv)
{
	QApplication application(argc, argv);
	Points points;
	points.push_back(Point_3(0, 0, 0));
	points.push_back(Point_3(10, 0, 0));
	points.push_back(Point_3(10, 10, 0));
	points.push_back(Point_3(0, 10, 0));
	points.push_back(Point_3(0, 0, 8));
	points.push_back(Point_3(10, 0, 8));
	points.push_back(Point_3(10, 10, 8));
	points.push_back(Point_3(0, 10, 8));
	points.push_back(Point_3(6, 5, 3));
	points.push_back(Point_3(4, 1, 4));

	Surface_mesh result;
	CGAL::convex_hull_3(points.begin(), points.end(), result);

	std::cout << "The convex hull contains " << num_vertices(result) << " vertices" << std::endl;

	for (auto p : points) {
		std::cout << p << std::endl;
	}

	Viewer viewer;
	viewer.setPoints(points);
	viewer.setMesh(result);
	viewer.setWindowTitle("simpleViewer");
	viewer.show();
	return application.exec();
}
