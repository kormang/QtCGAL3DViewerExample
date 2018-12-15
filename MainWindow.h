#pragma once

#include <array>

#include <QMainWindow>

namespace Ui {
	class MainWindow;
}

class BSpline;
class PNtriangle;

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
	bool convexHullShown;
	std::array<BSpline*, 2> bsplines;
	PNtriangle* singlePNTriangle;
	std::array<PNtriangle*, 8> pnoctahedron;

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