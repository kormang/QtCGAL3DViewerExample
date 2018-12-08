#define GL_SILENCE_DEPRECATION
#include "Viewer3D.h"
#include <OpenGL/gl.h>
#include <QMessageBox>
#include <random>
#include <cmath>

constexpr auto PI = 3.14159265358979323846;

using namespace std;

#define NUMBER_OF_RUNDOM_POINTS 500

void Viewer3D::addPoint(float x, float y, float z)
{
	points.push_back(Point_3(x, y, z));
	update();
}

void Viewer3D::clearPoints()
{
	points.clear();
	update();
}

void Viewer3D::generateCube(const Point_3& center, float sideSize)
{
	std::random_device rd;
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(-sideSize/2, sideSize/2);

	for (int i = 0; i < NUMBER_OF_RUNDOM_POINTS; ++i) {
		addPoint(center.x() + dis(gen), center.y() + dis(gen), center.z() + dis(gen));
	}
	update();
}
void Viewer3D::generateSphere(const Point_3& center, float radius)
{
	std::random_device rd;
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis_azimuth(0.0, 2*PI);
    std::uniform_real_distribution<> dis_polar(0.0, PI);
	const float r = radius;

	for (int i = 0; i < NUMBER_OF_RUNDOM_POINTS; ++i) {
		const auto azimuth = dis_azimuth(gen);
		const auto polar = dis_polar(gen);
		const auto sinpolar = sin(polar);
		const float x = center.x() + r * sinpolar * cos(azimuth);
		const float y = center.y() + r * sinpolar * sin(azimuth);
		const float z = center.z() + r * cos(polar);
		addPoint(x, y, z);
	}
	update();
}

void Viewer3D::draw()
{
	glPointSize(10.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < points.size(); ++i)
	{
		glVertex3f(points[i].x(), points[i].y(), points[i].z());
	}
	glEnd();
}

void Viewer3D::postSelection(const QPoint & point)
{
	// Вычисление вершин, находящихся на пути луча
	qglviewer::Vec orig, dir;
	camera()->convertClickToLine(point, orig, dir);
	std::vector<int> selected;
	for (int i = 0; i < points.size(); i++)
	{
		float t = (points[i].z() - orig.z) / dir.z;
		float x = orig.x + dir.x * t;
		float y = orig.y + dir.y * t;
		float xdiff = points[i].x() - x;
		float ydiff = points[i].y() - y;
		if ((xdiff*xdiff + ydiff*ydiff) < 0.01f)
			selected.push_back(i);
	}
	// Отображение результата в отдельном окне
	QString result;
	for (int i = 0; i < selected.size(); i++)
	{
		QString tmp = "Vertex number " + QString::number(selected[i]) + ": " +
			QString::number(points[selected[i]].x()) + " " +
			QString::number(points[selected[i]].y()) + " " +
			QString::number(points[selected[i]].z()) + "\n";
		result.append(tmp);
	}
	QMessageBox::information(this, "Selection", result);
}

void Viewer3D::init()
{
}

void Viewer3D::initializeGL()
{
	QGLViewer::initializeGL();

	this->camera()->setZNearCoefficient(0.0001);
	this->camera()->setZClippingCoefficient(100.0);

	this->camera()->setPosition(qglviewer::Vec(0, 0, 1.0));
	this->camera()->lookAt(qglviewer::Vec(0, 0, 0));
}
