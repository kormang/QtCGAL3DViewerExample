#pragma once

#include <array>

#include <QMainWindow>

namespace Ui {
	class MainWindow;
}

class DrawingElement;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = 0);
	~MainWindow();

	void show();
private:
	Ui::MainWindow* ui;
	void readPointFromTextBoxes(bool* success, float* x, float* y, float* z);
	DrawingElement* convexHull;
	std::array<DrawingElement*, 2> bsplines;
	DrawingElement* singlePNTriangle;
	std::array<DrawingElement*, 8> pnoctahedron;

public slots:
	void slotExit();
	void slotAddPoint();
	void slotClearPoints();
	void slotGenerateCube();
	void slotGenerateSphere();
	void slotShowConvexHull();
	void slotShowBSpline3();
	void slotShowBSpline2();
	void slotShowPNTriangle();
	void slotShowOctahedronSphere();
};