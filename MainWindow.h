#pragma once

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

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


public slots:
    void slotExit();
    void slotAddPoint();
    void slotClearPoints();
    void slotGenerateCube();
    void slotGenerateSphere();
};