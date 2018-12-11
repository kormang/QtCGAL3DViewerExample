#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "BSpline.h"

#include <CGAL/Surface_mesh.h>
#include <CGAL/convex_hull_3.h>

MainWindow::MainWindow(QWidget* parent):
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	convexHullShown(false),
	bsplines({nullptr, nullptr})
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
		ui->widget->addPoint(x, y, z);
	}
	ui->widget->generateCube(Point_3(x, y, z), 0.15);
}
void MainWindow::slotGenerateSphere()
{
	bool success = false;
	float x, y, z;
	readPointFromTextBoxes(&success, &x, &y, &z);
	if (success) {
		ui->widget->generateSphere(Point_3(x, y, z), 0.15);
	}
}

void MainWindow::slotShowConvexHull()
{
	Surface_mesh result;
	if (convexHullShown) {
		ui->actionShow_convex_hull->setText(tr("Show convex hull"));
		convexHullShown = false;
	} else {
		const auto points = ui->widget->getPoints();
		CGAL::convex_hull_3(points.begin(), points.end(), result);
		ui->actionShow_convex_hull->setText(tr("Hide convex hull"));
		convexHullShown = true;
	}
	ui->widget->setSurfaceMesh(result);

}

void MainWindow::slotShowBSpline3()
{
	if (bsplines[1] == nullptr) {
		bsplines[1] = new BSpline(ui->widget->getPoints(), 3);
		ui->widget->addBSpline(bsplines[1]);
		ui->actionShow_3rd_degree_BSpline->setText(tr("Hide 3rd degree BSpline"));
	} else {
		ui->actionShow_3rd_degree_BSpline->setText(tr("Show 3rd degree BSpline"));
		ui->widget->removeBSpline(bsplines[1]);
		delete bsplines[1];
		bsplines[1] = nullptr;
	}
}

void MainWindow::slotShowBSpline2()
{
	if (bsplines[0] == nullptr) {
		bsplines[0] = new BSpline(ui->widget->getPoints(), 2);
		ui->widget->addBSpline(bsplines[0]);
		ui->actionShow_2nd_degree_BSpline->setText(tr("Hide 2nd degree BSpline"));
	} else {
		ui->actionShow_2nd_degree_BSpline->setText(tr("Show 2nd degree BSpline"));
		ui->widget->removeBSpline(bsplines[0]);
		delete bsplines[0];
		bsplines[0] = nullptr;
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}