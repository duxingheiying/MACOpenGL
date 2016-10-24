#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(600,600);
    GL = new GLWidget();
    this->setCentralWidget(GL);
    GL->show();
}

MainWindow::~MainWindow()
{
    delete GL;
    delete ui;
}
