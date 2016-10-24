#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QtOpenGL>

#include <QtWebView>

namespace Ui {
class GLWidget;
}

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QGLWidget *parent = 0);
    ~GLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:

private:
    Ui::GLWidget *ui;
};

#endif // GLWIDGET_H
