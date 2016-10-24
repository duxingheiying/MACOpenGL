#include "GLWidget.h"
#include "ui_GLWidget.h"

#include "griding.h"


GLWidget::GLWidget(QGLWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::GLWidget)
{
    ui->setupUi(this);
//    this->resize(600,800);
}

void GLWidget::initializeGL()
{
    glShadeModel(GL_SMOOTH);  //设置阴影平滑模式
    glClearColor(0.0, 0.0, 0.0, 0.5);  //设置背景颜色
    glClearDepth(1.0);  //设置深度缓存
    glEnable(GL_DEPTH_TEST);  //允许深度测试
    glDepthFunc(GL_LEQUAL);  //设置深度测试类型
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);  //进行透视矫正
}

//初始化GL编辑环境
void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //和glclearColor()配套使用
    glLoadIdentity();  //重置当前观察矩阵
//    drawGraphics(0,2);
//    display();  //griding函数的使用技巧

//    glBegin(GL_TRIANGLES);//GL_TRIANGLES代表为画三角形
//    glVertex3f(0.0f, 0.2f, 0.0f);//上顶点坐标
//    glVertex3f(-0.2f, -0.2f, 0.0f);//左下角坐标
//    glVertex3f(0.2f, -0.2f, 0.0f);//右下角坐标
//    glEnd();//结束画完
//    glLoadIdentity();  //重置当前观察矩阵

//    glColor3f(1,0,1);
//    glRectf(-0.5,-0.5,0.5,0.5);

//    //绘制多边形
//    glBegin(GL_POLYGON);
//    glVertex2f(0.0, 0.0);
//    glVertex2f(0.0, 3.0);
//    glVertex2f(4.0, 3.0);
//    glVertex2f(6.0, 1.5);
//    glVertex2f(4.0, 0.0);
//    glEnd();


    // The vertex array is enabled for writing and used during rendering.
    glEnableClientState(GL_VERTEX_ARRAY);

    // 顶点坐标数组
    const GLdouble vers[] = {GLdouble(1.0), GLdouble(1.0), GLdouble(0.0), // 第1个顶点坐标
                             GLdouble(1.0), GLdouble(-1.0), GLdouble(0.0), // 第2个顶点坐标
                             GLdouble(-1.0), GLdouble(-1.0), GLdouble(0.0), // 第3个顶点坐标
                             GLdouble(-1.0), GLdouble(1.0), GLdouble(0.0),  // 第4个顶点坐标
                             GLdouble(0.0), GLdouble(0.0), GLdouble(0.0)  // 第4个顶点坐标
                            };

    glVertexPointer(3,        // 表示每一个顶点由3维坐标构成
                    GL_DOUBLE,// 顶点坐标数组中的元素是 GL_FIXED 类型
                    0,        // 从顶点坐标数组的第0个元素开始读取数据
                    vers      // 指向顶点坐标数组的指针
                    );

    // 等效替换 glDrawArrays(GL_TRIANGLE_STRIP, 0, 4) ++

    /* 索引数组. 此索引数组表示依次是
    第0个顶点{F2X(0.25), F2X(0.25), F2X(0.0)}，
    第1个顶点{F2X(0.75), F2X(0.25), F2X(0.0)}，
    第2个顶点{F2X(0.25), F2X(0.75), F2X(0.0)}，
    第3个顶点{F2X(0.75), F2X(0.75), F2X(0.0)} */
    const GLubyte indices[] = {0, 1, 2, 3};

    glDrawElements(GL_TRIANGLE_STRIP, // 绘图模式
                   5,                 // 依次从索引数组中读取4个顶点来进行绘制
                   GL_UNSIGNED_BYTE,  // 索引数组中存放的元素的类型
                   indices            // 指向索引数组的指针
                   );

    glDisableClientState(GL_VERTEX_ARRAY);
}

//重置窗口
void GLWidget::resizeGL(int width, int height)
{
    if(0 == height)
    {
        height = 1;
    }

    glViewport(0,0,(GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION);  //选择投影矩阵
//    gluPerspective(0.0, (GLfloat)width/(GLfloat)height, -20, 100.0);//建立透视投影矩
    glLoadIdentity();
    glOrtho(-20, 20, -20, 20, -500, 500);
    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
}

GLWidget::~GLWidget()
{
    delete ui;
}
