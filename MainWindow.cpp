#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "BSpline.h"
#include "PNtriangle.h"
#include "DrawingElements.h"
#include <CGAL/Surface_mesh.h>
#include <CGAL/convex_hull_3.h>

MainWindow::MainWindow(QWidget* parent):
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	convexHull(nullptr),
	bsplines({nullptr, nullptr}),
	singlePNTriangle(nullptr),
	pnoctahedron({nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr})
{
	ui->setupUi(this);
	connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
	connect(this->ui->btnAddPoint, SIGNAL(clicked()), this, SLOT(slotAddPoint()));
	connect(this->ui->actionClear_all_points, SIGNAL(triggered()), this, SLOT(slotClearPoints()));
	connect(this->ui->actionGenerate_sphere, SIGNAL(triggered()), this, SLOT(slotGenerateSphere()));
	connect(this->ui->actionGenerate_cube, SIGNAL(triggered()), this, SLOT(slotGenerateCube()));
	connect(this->ui->actionShow_convex_hull, SIGNAL(triggered()), this, SLOT(slotShowConvexHull()));
	connect(this->ui->actionShow_2nd_degree_BSpline, SIGNAL(triggered()), this, SLOT(slotShowBSpline2()));
	connect(this->ui->actionShow_3rd_degree_BSpline, SIGNAL(triggered()), this, SLOT(slotShowBSpline3()));
	connect(this->ui->actionShow_PNTriangle, SIGNAL(triggered()), this, SLOT(slotShowPNTriangle()));
	connect(this->ui->actionShow_octahedron_sphere, SIGNAL(triggered()), this, SLOT(slotShowOctahedronSphere()));

};

void MainWindow::show(){
	QMainWindow::show();
	ui->menubar->show();
}

void MainWindow::slotExit() {
	this->close();
}

void MainWindow::readPointFromTextBoxes(bool* success, float* x, float* y, float* z)
{
	bool flags[] = {false, false, false};
	*x = QString(ui->leXCoord->text()).toFloat(flags);
	*y = QString(ui->leYCoord->text()).toFloat(flags+1);
	*z = QString(ui->leZCoord->text()).toFloat(flags+2);

	*success = flags[0] && flags[1] && flags[2];

	if (!(*success)) {
		QMessageBox::critical(this, "Wrong input", "Values in input boxes must be valid real numbers.");
	}
}

void MainWindow::slotAddPoint() {
	bool success = false;
	float x, y, z;
	readPointFromTextBoxes(&success, &x, &y, &z);
	if (success) {
		ui->widget->addPoint(x, y, z);
	}
}

void MainWindow::slotClearPoints()
{
	ui->widget->clearPoints();
}
void MainWindow::slotGenerateCube()
{
	bool success = false;
	float x, y, z;
	readPointFromTextBoxes(&success, &x, &y, &z);
	if (success) {
		float sideSize = QString(ui->leParam->text()).toFloat(&success);
		if (!success) {
			sideSize = 0.2;
		}
		ui->widget->generateCube(Point_3(x, y, z), sideSize);
	}
}
void MainWindow::slotGenerateSphere()
{
	bool success = false;
	float x, y, z;
	readPointFromTextBoxes(&success, &x, &y, &z);
	if (success) {
		float radius = QString(ui->leParam->text()).toFloat(&success);
		if (!success) {
			radius = 0.141;
		}
		ui->widget->generateSphere(Point_3(x, y, z), radius);
	}
}

void MainWindow::slotShowConvexHull()
{
	Surface_mesh* result = new Surface_mesh;
	if (convexHull != nullptr) {
		ui->widget->removeElement(convexHull);
		delete convexHull;
		convexHull = nullptr;
		ui->actionShow_convex_hull->setText(tr("Show convex hull"));
	} else {
		const auto points = ui->widget->getPoints();
		CGAL::convex_hull_3(points.begin(), points.end(), *result);
		ui->actionShow_convex_hull->setText(tr("Hide convex hull"));
		convexHull = new SurfaceMeshDrawingElement(result);
		ui->widget->addElement(convexHull);
	}
}

void MainWindow::slotShowBSpline3()
{
	if (bsplines[1] == nullptr) {
		bsplines[1] = new BSpline(ui->widget->getPoints(), 3, ui->cbClosed->isChecked());
		ui->widget->addBSpline(bsplines[1]);
		ui->actionShow_3rd_degree_BSpline->setText(tr("Hide 3rd degree BSpline"));
	} else {
		ui->actionShow_3rd_degree_BSpline->setText(tr("Show 3rd degree BSpline"));
		ui->widget->removeElement(bsplines[1]);
		delete bsplines[1];
		bsplines[1] = nullptr;
	}
}

void MainWindow::slotShowBSpline2()
{
	if (bsplines[0] == nullptr) {
		bsplines[0] = new BSpline(ui->widget->getPoints(), 2, ui->cbClosed->isChecked());
		ui->widget->addBSpline(bsplines[0]);
		ui->actionShow_2nd_degree_BSpline->setText(tr("Hide 2nd degree BSpline"));
	} else {
		ui->actionShow_2nd_degree_BSpline->setText(tr("Show 2nd degree BSpline"));
		ui->widget->removeElement(bsplines[0]);
		delete bsplines[0];
		bsplines[0] = nullptr;
	}
}

void MainWindow::slotShowPNTriangle()
{
	if (singlePNTriangle != nullptr) {
		ui->widget->removeElement(singlePNTriangle);
		delete singlePNTriangle;
		singlePNTriangle = nullptr;
		ui->actionShow_PNTriangle->setText(tr("Show PNTriangle"));
	} else {
		bool success = false;
		int tessLevel = QString(ui->leTessLevel->text()).toInt(&success);
		if (!success) {
			tessLevel = 0;
		}
		singlePNTriangle = new PNtriangleDrawingElement(new PNtriangle(
			// точки
			Point_3(0.0, 0.26, 0.0),
			Point_3(-0.15, 0.0, 0.0),
			Point_3(0.15, 0.0, 0.0),
			// нормали
			Point_3(0.0, 0.3, 1.0),
			Point_3(-0.2, -0.1, 1.0),
			Point_3(0.2, -0.1, -1.0),
			// уровень тесселяции
			tessLevel
		));
		ui->widget->addElement(singlePNTriangle);
		ui->actionShow_PNTriangle->setText(tr("Hide PNTriangle"));
	}
}

void MainWindow::slotShowOctahedronSphere()
{
	if (pnoctahedron[0] != nullptr) {
		for (int i = 0; i < 8; ++i) {
			ui->widget->removeElement(pnoctahedron[i]);
			delete pnoctahedron[i];
			pnoctahedron[i] = nullptr;
		}
		ui->actionShow_octahedron_sphere->setText(tr("Show octahedron sphere"));
	} else {
		bool success = false;
		int tessLevel = QString(ui->leTessLevel->text()).toInt(&success);
		if (!success) {
			tessLevel = 0;
		}
		float size = QString(ui->leParam->text()).toFloat(&success);
		if (!success) {
			size = 0.0f;
		}
		for (int j = 0; j <= 4; j += 4) {
			float sizez = j == 0 ? size : -size;
			pnoctahedron[0 + j] = new PNtriangleDrawingElement(new PNtriangle(
				// точки
				Point_3(size, 0.0, 0.0),
				Point_3(0.0, size, 0.0),
				Point_3(0.0, 0.0, sizez),
				// уровень тесселяции
				tessLevel
			));
			pnoctahedron[1 + j] = new PNtriangleDrawingElement(new PNtriangle(
				// точки
				Point_3(0.0, size, 0.0),
				Point_3(-size, 0.0, 0.0),
				Point_3(0.0, 0.0, sizez),
				// уровень тесселяции
				tessLevel
			));
			pnoctahedron[2 + j] = new PNtriangleDrawingElement(new PNtriangle(
				// точки
				Point_3(-size, 0.0, 0.0),
				Point_3(0.0, -size, 0.0),
				Point_3(0.0, 0.0, sizez),
				// уровень тесселяции
				tessLevel
			));
			pnoctahedron[3 + j] = new PNtriangleDrawingElement(new PNtriangle(
				// точки
				Point_3(size, 0.0, 0.0),
				Point_3(0.0, -size, 0.0),
				Point_3(0.0, 0.0, sizez),
				// уровень тесселяции
				tessLevel
			));
		}
		for (int i = 0; i < 8; ++i) {
			ui->widget->addElement(pnoctahedron[i]);
		}
		ui->actionShow_octahedron_sphere->setText(tr("Hide octahedron sphere"));
	}
}

MainWindow::~MainWindow()
{
	if (convexHull != nullptr) {
		delete convexHull;
	}

	for (int i = 0; i < bsplines.size(); ++i) {
		if (bsplines[i] != nullptr) {
			delete bsplines[i];
		}
	}

	if (singlePNTriangle != nullptr) {
		delete singlePNTriangle;
	}

	for (int i = 0; i < pnoctahedron.size(); ++i) {
		if (pnoctahedron[i] != nullptr) {
			delete pnoctahedron[i];
		}
	}
	delete ui;
}