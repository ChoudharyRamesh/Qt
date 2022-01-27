#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "paintercanvas.h"
#include <QPushButton>
#include <QCheckBox>
#include<QKeyEvent>
#include <QLabel>
#include <QSpinBox>
#include <QColorDialog>
#include<QKeySequence>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void penWidthChanged(int width);
    void changePenColor();
    void changeFillColor();
    void changeFillProperty();

private:
    Ui::MainWindow *ui;
    PainterCanvas * canvas;
    QPushButton * penColorButton;
    QPushButton * fillColorButton;
    QCheckBox * fillCheckBox;
};

#endif // MAINWINDOW_H
