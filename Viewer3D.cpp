#define GL_SILENCE_DEPRECATION
#include "Viewer3D.h"
#include <OpenGL/gl.h>

using namespace std;

void Viewer3D::addPoint(float x, float y, float z)
{
	points.push_back(Point_3(x, y, z));
}

void Viewer3D::clearPoints()
{
	points.clear();
}

void Viewer3D::draw()
{
	glPointSize(3.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < points.size(); ++i)
	{
		glVertex3f(points[i].x(), points[i].y(), points[i].z());
	}
	glEnd();
}

void Viewer3D::init()
{
}

void Viewer3D::initializeGL()
{
	QGLViewer::initializeGL();

	this->camera()->setZNearCoefficient(0.0001);
	this->camera()->setZClippingCoefficient(100.0);

	this->camera()->setPosition(qglviewer::Vec(1, 1.2, 1.2));
	this->camera()->lookAt(qglviewer::Vec(0, 0, 0));
}
