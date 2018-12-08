#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
    connect(this->ui->btnAddPoint, SIGNAL(clicked()), this, SLOT(slotAddPoint()));
    connect(this->ui->actionClear_all_points, SIGNAL(triggered()), this, SLOT(slotClearPoints()));
    connect(this->ui->actionGenerate_sphere, SIGNAL(triggered()), this, SLOT(slotGenerateSphere()));
    connect(this->ui->actionGenerate_cube, SIGNAL(triggered()), this, SLOT(slotGenerateCube()));
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

MainWindow::~MainWindow()
{
    delete ui;
}