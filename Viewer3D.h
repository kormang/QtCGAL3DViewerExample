#pragma once
#include <QGLViewer/qglviewer.h>
#include <Qstring>

#include "typedefs.h"

class DrawingElement
{
public:
	virtual void draw() = 0;
	virtual ~DrawingElement() {};
};

class Viewer3D : public QGLViewer
{
private:
	Points3 points;
	std::vector<DrawingElement*> drawingElements;
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
	void addElement(DrawingElement* element);
	void removeElement(DrawingElement* element);
};
