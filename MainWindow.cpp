#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
    connect(this->ui->btnAddPoint, SIGNAL(clicked()), this, SLOT(slotAddPoint()));
};

void MainWindow::show(){
    QMainWindow::show();
    ui->menubar->show();
}

void MainWindow::slotExit() {
    this->close();
}

void MainWindow::slotAddPoint() {
    bool success[] = {false, false, false};
    float x = QString(ui->leXCoord->text()).toFloat(success);
	float y = QString(ui->leYCoord->text()).toFloat(success+1);
	float z = QString(ui->leZCoord->text()).toFloat(success+2);

    if (success[0] && success[1] && success[2]) {
        ui->widget->addPoint(x, y, z);
    } else {
        std::cerr << "NOT FLOATS!!!\n";
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}