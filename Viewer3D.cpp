#define GL_SILENCE_DEPRECATION
#include "Viewer3D.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <QMessageBox>
#include <random>
#include <cmath>

constexpr auto PI = 3.14159265358979323846;

using namespace std;

#define NUMBER_OF_RUNDOM_POINTS 500

void Viewer3D::addPoint(float x, float y, float z)
{
	addPointImpl(x, y, z);
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
		addPointImpl(center.x() + dis(gen), center.y() + dis(gen), center.z() + dis(gen));
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
		addPointImpl(x, y, z);
	}
	update();
}

void Viewer3D::draw()
{
	glPointSize(5.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POINTS);
	for (uint i = 0; i < points.size(); ++i) {
		glVertex3f(points[i].x(), points[i].y(), points[i].z());
	}
	glEnd();

	for (auto element : drawingElements) {
		element->draw();
	}
}

void Viewer3D::postSelection(const QPoint & point)
{
	// Вычисление вершин, находящихся на пути луча
	qglviewer::Vec orig, dir;
	camera()->convertClickToLine(point, orig, dir);
	std::vector<int> selected;
	for (uint i = 0; i < points.size(); i++) {
		qglviewer::Vec point(
			points[i].x() - orig.x,
			points[i].y() - orig.y,
			points[i].z() - orig.z
		);
		qglviewer::Vec projection = point;
		projection.projectOnAxis(dir);
		if ((point - projection).squaredNorm() < 0.001f) {
			selected.push_back(i);
		}
	}
	if (selected.size() > 0) {
		// Отображение результата в отдельном окне
		QString result;
		for (uint i = 0; i < selected.size(); i++) {
			QString tmp = "Vertex number " + QString::number(selected[i]) + ": " +
				QString::number(points[selected[i]].x()) + " " +
				QString::number(points[selected[i]].y()) + " " +
				QString::number(points[selected[i]].z()) + "\n";
			result.append(tmp);
		}
		QMessageBox::information(this, "Selection", result);
	}
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

void Viewer3D::addElement(DrawingElement* element)
{
	drawingElements.push_back(element);
	update();
}

void Viewer3D::removeElement(DrawingElement* element)
{
	drawingElements.erase(std::remove(drawingElements.begin(), drawingElements.end(), element));
	update();
}

void Viewer3D::mousePressEvent(QMouseEvent *e) {
	if ((e->button() == Qt::LeftButton) && (e->modifiers() == Qt::ControlModifier)) {
		qglviewer::Vec orig, dir;
		camera()->convertClickToLine(e->pos(), orig, dir);
		int selected = -1;
		float maxCos = 0.0f;
		for (uint i = 0; i < points.size(); i++)
		{
			qglviewer::Vec point(
				points[i].x() - orig.x,
				points[i].y() - orig.y,
				points[i].z() - orig.z
			);
			const float cos = (dir * point) / (dir.norm() * point.norm());
			// чем косинус больше, т.е. ближе единице, тем угол меньше.
			if (cos > 0.9999f) {
				// находим самую близкую точку
				if (cos > maxCos) {
					maxCos = cos;
					selected = i;
				}
			}
		}
		if (selected > -1) {
			selectedPointIndex = selected;
		}
	} else {
		QGLViewer::mousePressEvent(e);
	}
}

void Viewer3D::mouseReleaseEvent(QMouseEvent *e) {
	if ((e->button() == Qt::LeftButton) && (selectedPointIndex > -1)) {
		selectedPointIndex = -1;
	} else {
		QGLViewer::mouseReleaseEvent(e);
	}
}

void Viewer3D::mouseMoveEvent(QMouseEvent *e) {
	if (selectedPointIndex > -1) {
		qglviewer::Vec cdir = camera()->viewDirection();
		qglviewer::Vec orig, pdir;
		camera()->convertClickToLine(e->pos(), orig, pdir);
		int i = selectedPointIndex;
		qglviewer::Vec point(
			points[i].x() - orig.x,
			points[i].y() - orig.y,
			points[i].z() - orig.z
		);
		float s = (point * cdir) / (pdir * cdir);
		points[i] = Point_3(
			orig.x + s * pdir.x,
			orig.y + s * pdir.y,
			orig.z + s * pdir.z
		);
		update();
	} else {
		QGLViewer::mouseMoveEvent(e);
	}
}