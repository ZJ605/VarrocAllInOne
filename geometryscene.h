#ifndef GEOMETRYSCENE_H
#define GEOMETRYSCENE_H

#include <QFrame>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QVector3D>
#include <QWidget>
#include <QtMath>
#include <QtGlobal>
#include "plyreader.h"
#include "vao_vbo_object.h"
#include "smaz.h"
#include <QWheelEvent>

class GeometryScene: public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GeometryScene(QOpenGLWidget* parent = nullptr);
    virtual ~GeometryScene() override;
    virtual void initializeGL() override;
    void paintGL() override;
    void setMatrixDefault();

protected:
    void mousePressEvent(QMouseEvent* ev) override;
    void mouseMoveEvent(QMouseEvent* ev) override;
    void mouseReleaseEvent(QMouseEvent* ev) override;

public slots:
    void geometryTransformXYView();
    void geometryChanged(BasicObject& o);
    void geometryChanged2D(BasicObject& o);
    void sourceUpdated(QVector<float> s);
    void geometryTraced(QVector<float> v,QVector<float> r);

private:
    void initializeData();
    void printContextInfo();
    void setProjectionMatrix();
    void fitAllObjectsIn();
    void axisSystemInicialization();
    float m_height;
    float m_width;
    enum Transformation_type{
        translate,
        rotate,
        scale,
        nothing
    };
    Transformation_type m_transformation_type = nothing;
    QVector3D m_eye = QVector3D(0,0,1);
    QVector3D m_center = QVector3D(0,0,0);
    QVector3D m_up = QVector3D(0,1,0);

    QMatrix4x4 m_modelMatrix;
    QMatrix4x4 m_prevModelMatrix;
    QMatrix4x4 m_transformationMatrix;
    QMatrix4x4 m_viewMatrix;
    QMatrix4x4 m_projectionMatrix;
    QMatrix4x4 m_centerMatrix;
    QQuaternion m_rotation;
    double m_angle = 0;

    QOpenGLShaderProgram *m_shaderProgram = new QOpenGLShaderProgram();
    QList<VAO_VBO_Object*> vao_vbo_objects;

    QOpenGLVertexArrayObject sourceVAO;
    QOpenGLBuffer sourceVBO;
    QVector<float> sourceFloatArray;
    bool m_sourceIsInitialized = false;

    QOpenGLVertexArrayObject axisVAO;
    QOpenGLBuffer axisVBO;
    QVector<float> axisFloatArray;
    bool m_axisIsInitialized = false;

    QOpenGLVertexArrayObject incRayVAO;
    QOpenGLBuffer incRayVBO;
    bool m_incRaysExist = false;
    QVector<float> incRayArray;

    QOpenGLVertexArrayObject reflRayVAO;
    QOpenGLBuffer reflRayVBO;
    bool m_reflRaysExist = false;
    QVector<float> reflRayArray;

    float m_biggestObject = 0;
    float m_left = 0;
    float m_top = 0;
    float m_right = 0;
    float m_bottom = 0;

    bool m_initalized = false; //geometry is initialized
    int m_projectionType = 0; //0 ortonormal, 1 perspective

    //attributes for geometry   transformation
    struct previousVector {
            boolean rIsSet = 0;
            boolean tIsSet = 0;
            boolean sIsSet = 0;
            QVector3D r = QVector3D(0.0,0.0,0.0);
            QVector2D t = QVector2D(0.0,0.0);
            float s = float(0.0);
            int rIterator = 0;
            int tIterator = 0;
            int sIterator = 0;
            previousVector(){}
    };
    previousVector m_previousVector; //

    QVector3D countRotationAxis(QVector3D vektor, QVector3D normal);

};

#endif //GEOMETRYSCENE_H
