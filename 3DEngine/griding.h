#ifndef GRIDING_H
#define GRIDING_H

#include <QObject>
#include <QDebug>
#include <QtOpenGL>

#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/GLUT.h"

#ifndef CALLBACK
#define CALLBACK _stdcall
#endif

GLint nProperty=0;                  //环绕规则索引
GLdouble TessProperty[5] = {        //环绕规则
    GLU_TESS_WINDING_ODD,           //环绕数为奇数
    GLU_TESS_WINDING_NONZERO,       //环绕数为非0
    GLU_TESS_WINDING_POSITIVE,      //环绕数为正数
    GLU_TESS_WINDING_NEGATIVE,      //环绕数为负数
    GLU_TESS_WINDING_ABS_GEQ_TWO    //环绕数绝对值大于等于2
};

GLdouble graphics0[3][4][3] = {     //左上角图形
    {{10.0, 10.0, 0.0}, {-10.0, 10.0, 0.0}, {-10.0, -10.0, 0.0}, {10.0, -10.0, 0.0}},
    {{7.0, 7.0, 0.0}, {-7.0, 7.0, 0.0}, {-7.0, -7.0, 0.0}, {7.0, -7.0, 0.0}},
    {{4.0, 4.0, 0.0}, {-4.0, 4.0, 0.0}, {-4.0, -4.0, 0.0}, {4.0, -4.0, 0.0}}
};

GLdouble graphics1[3][4][3] = {     //右上角图形
    {{10.0, 10.0, 0.0}, {-10.0, 10.0, 0.0}, {-10.0, -10.0, 0.0}, {10.0, -10.0, 0.0}},
    {{7.0, 7.0, 0.0}, {7.0, -7.0, 0.0}, {-7.0, -7.0, 0.0}, {-7.0, 7.0, 0.0}},
    {{4.0, 4.0, 0.0}, {4.0, -4.0, 0.0}, {-4.0, -4.0, 0.0}, {-4.0, 4.0, 0.0}}
};

GLdouble graphics2[11][3] = {       //左下角图形
    {10.0, 10.0, 0.0}, {-10.0, 10.0, 0.0},  {-10.0, -10.0, 0.0}, {10.0, -10.0, 0.0},
    {13.0, 2.0, 0.0}, {-13.0, 2.0, 0.0}, {-13.0, -2.0, 0.0}, {13.0, -2.0, 0.0},
    {3.0, 6.0, 0.0}, {-3.0, 6.0, 0.0}, {0.0, -15.0, 0.0}
};

GLdouble graphics3[16][3] = {       //右下角图形
    {7.0, 10.0, 0.0}, {-10.0, 10.0, 0.0}, {-10.0, -10.0, 0.0}, {10, -10.0, 0.0},
    {10.0, 1.0, 0.0}, {-1.0, 1.0, 0.0}, {-1.0, -1.0, 0.0}, {1.0, -1.0, 0.0},
    {1.0, 4.0, 0.0}, {-4.0, 4.0, 0.0}, {-4.0, -4.0, 0.0}, {4.0, -4.0, 0.0},
    {4.0, 7.0, 0.0}, {-7.0, 7.0, 0.0}, {-7.0, -7.0, 0.0}, {7.0, -7.0, 0.0}
};

static void CALLBACK combineCallback(GLdouble coords[3],
                                     GLdouble* data[4],
                                     GLfloat weight[4],
                                     GLdouble **dataout)
{
    GLdouble *vertex;
    int i;
    vertex = (GLdouble*)malloc(6*sizeof(GLdouble));
    vertex[0] = coords[0];
    vertex[1] = coords[1];
    vertex[2] = coords[2];

    for(i=3; i<6; i++)      //新顶点的颜色为4个顶点的线型组合
    {
        vertex[i] = weight[0]*data[0][i]+weight[1]*data[1][i]
                    +weight[2]*data[2][i]+weight[3]*data[3][i];
    }
    *dataout = vertex;
}

//顶点的回调函数
static void CALLBACK vertexCallback(GLdouble* vertex)
{
    GLdouble* pt;
    GLubyte red, green, blue;
    int numb;
    pt = (GLdouble*)vertex;
    numb = rand();
    red = (GLubyte)rand()&0xff;         //(numb>>16) & 0xff;
    green = (GLubyte)rand()&0xff;       //(numb>>8) & 0xff;
    blue = (GLubyte)rand()&0xff;        //numb & 0xff;
    glColor3ub(red, green, blue);
    glVertex3dv(pt);
}

static void CALLBACK beginCallback(GLenum type)
{
    glBegin(type);
}

static void CALLBACK endCallback()
{
    glEnd();
}

static void CALLBACK errorCallback(GLenum errorCode)
{
    const GLubyte * estring;
    //打印错误类型
    estring = gluErrorString(errorCode);
    fprintf(stderr, "Tessellation Error: %s/n", estring);
    exit(0);
}

static void drawGraphics(GLint ngraphic, GLint nproperty)
{
    int i;
    GLUtesselator * tessobj;
    tessobj = gluNewTess();

    //注册回调函数
    gluTessCallback(tessobj, GLU_TESS_VERTEX, (GLvoid(_stdcall*)())vertexCallback);
    gluTessCallback(tessobj, GLU_TESS_BEGIN, (GLvoid(_stdcall*)())beginCallback);
    gluTessCallback(tessobj, GLU_TESS_END, endCallback);
    gluTessCallback(tessobj, GLU_TESS_ERROR, (GLvoid(_stdcall*)())errorCallback);

    //设置环绕规则
    gluTessProperty(tessobj, GLU_TESS_WINDING_RULE, TessProperty[nproperty]);

    if(2==ngraphic || 3==ngraphic)
    {
        gluTessCallback(tessobj, GLU_TESS_COMBINE, (GLvoid(_stdcall*)())combineCallback);//多边型边自相交的情况下回调用回调函数
    }

    gluTessBeginPolygon(tessobj, NULL);
    switch(ngraphic){
    case 0:
        gluTessBeginContour(tessobj);       //定义轮廓线1 逆时针矩形
            gluTessVertex(tessobj, graphics0[0][0], graphics0[0][0]);
            gluTessVertex(tessobj, graphics0[0][1], graphics0[0][1]);
            gluTessVertex(tessobj, graphics0[0][2], graphics0[0][2]);
            gluTessVertex(tessobj, graphics0[0][3], graphics0[0][3]);
        gluTessEndContour(tessobj);

        gluTessBeginContour(tessobj);       //定义轮廓线2 逆时针矩形
            gluTessVertex(tessobj, graphics0[1][0], graphics0[1][0]);
            gluTessVertex(tessobj, graphics0[1][1], graphics0[1][1]);
            gluTessVertex(tessobj, graphics0[1][2], graphics0[1][2]);
            gluTessVertex(tessobj, graphics0[1][3], graphics0[1][3]);
        gluTessEndContour(tessobj);

        gluTessBeginContour(tessobj);       //定义轮廓线3 逆时针矩形
            gluTessVertex(tessobj, graphics0[2][0], graphics0[2][0]);
            gluTessVertex(tessobj, graphics0[2][1], graphics0[2][1]);
            gluTessVertex(tessobj, graphics0[2][2], graphics0[2][2]);
            gluTessVertex(tessobj, graphics0[2][3], graphics0[2][3]);
        gluTessEndContour(tessobj);
        break;

    case 1:
        gluTessBeginContour(tessobj);       //定义轮廓线1 逆时针矩形
            gluTessVertex(tessobj, graphics1[0][0], graphics1[0][0]);
            gluTessVertex(tessobj, graphics1[0][1], graphics1[0][1]);
            gluTessVertex(tessobj, graphics1[0][2], graphics1[0][2]);
            gluTessVertex(tessobj, graphics1[0][3], graphics1[0][3]);
        gluTessEndContour(tessobj);

        gluTessBeginContour(tessobj);       //定义轮廓线2 顺时针矩形
            gluTessVertex(tessobj, graphics1[1][0], graphics1[1][0]);
            gluTessVertex(tessobj, graphics1[1][1], graphics1[1][1]);
            gluTessVertex(tessobj, graphics1[1][2], graphics1[1][2]);
            gluTessVertex(tessobj, graphics1[1][3], graphics1[1][3]);
        gluTessEndContour(tessobj);

        gluTessBeginContour(tessobj);       //定义轮廓线3 顺时针矩形
            gluTessVertex(tessobj, graphics1[2][0], graphics1[2][0]);
            gluTessVertex(tessobj, graphics1[2][1], graphics1[2][1]);
            gluTessVertex(tessobj, graphics1[2][2], graphics1[2][2]);
            gluTessVertex(tessobj, graphics1[2][3], graphics1[2][3]);
        gluTessEndContour(tessobj);
        break;

    case 2:
        gluTessBeginContour(tessobj);       //定义轮廓线1 逆时针矩形
            gluTessVertex(tessobj, graphics2[0], graphics2[0]);
            gluTessVertex(tessobj, graphics2[1], graphics2[1]);
            gluTessVertex(tessobj, graphics2[2], graphics2[2]);
            gluTessVertex(tessobj, graphics2[3], graphics2[3]);
        gluTessEndContour(tessobj);

        gluTessBeginContour(tessobj);       //定义轮廓线2 逆时针矩形
            gluTessVertex(tessobj, graphics2[4], graphics2[4]);
            gluTessVertex(tessobj, graphics2[5], graphics2[5]);
            gluTessVertex(tessobj, graphics2[6], graphics2[6]);
            gluTessVertex(tessobj, graphics2[7], graphics2[7]);
        gluTessEndContour(tessobj);

        gluTessBeginContour(tessobj);       //定义轮廓线3 逆时针三角形
            gluTessVertex(tessobj, graphics2[8], graphics2[8]);
            gluTessVertex(tessobj, graphics2[9], graphics2[9]);
            gluTessVertex(tessobj, graphics2[10], graphics2[10]);
        gluTessEndContour(tessobj);
        break;

    case 3:
        gluTessBeginContour(tessobj);
            for(i=0; i<16; i++)
            {
                gluTessVertex(tessobj, graphics3[i], graphics3[i]);
            }
        gluTessEndContour(tessobj);
        break;

    default:
        break;
    }
    gluTessEndPolygon(tessobj);
}

void display()
{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glTranslated(-8.0, 8.0, -45.0);
        glScaled(0.5, 0.5, 1.0);
        drawGraphics(0, nProperty);
    glPopMatrix();

    glPushMatrix();
        glTranslated(8.0, 8.0, -45.0);
        glScaled(0.5, 0.5, 1.0);
        drawGraphics(1, nProperty);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-8.0, -8.0, -45.0);
        glScaled(0.5, 0.5, 1.0);
        drawGraphics(2, nProperty);
    glPopMatrix();

    glPushMatrix();
        glTranslated(8.0, -8.0, -45.0);
        glScaled(0.5, 0.5, 1.0);
        drawGraphics(3, nProperty);
    glPopMatrix();
    glFlush();
}

#endif // GRIDING_H
