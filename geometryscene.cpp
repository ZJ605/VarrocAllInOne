#include "geometryscene.h"
#include "plyreader.h"
#include <QtMath>

GeometryScene::GeometryScene(QOpenGLWidget *parent):QOpenGLWidget (parent)
{
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setVersion(4,0);
    format.setProfile(QSurfaceFormat::CoreProfile);
    this->setFormat(format);
    //this->setStyleSheet("border: 2px solid green");

}

GeometryScene::~GeometryScene()
{
    makeCurrent();
    delete m_shaderProgram;

}

void GeometryScene::initializeGL()
{
    setMatrixDefault();
    m_centerMatrix.setToIdentity();
    initializeOpenGLFunctions();
    printContextInfo();
    setProjectionMatrix();
    glClearColor(0.5, 0, 0.5, 0);

    //m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/phong.vert");
    //m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/phong.frag");
    m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/coord.vert");
    m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/coord.frag");
    //m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/sim.vert");
    //m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/sim.frag");

    m_shaderProgram->link();

    m_shaderProgram->bind();
/*
    m_shaderProgram->setUniformValue("mat.ka", QVector3D(0.1,0,0.0));
    m_shaderProgram->setUniformValue("mat.kd", QVector3D(0.0,0.5,0.0));
    m_shaderProgram->setUniformValue("mat.ks", QVector3D(1.0, 1.0, 1.0));
    m_shaderProgram->setUniformValue("mat.shininess", 128.0f);
    m_shaderProgram->setUniformValue("light.position", QVector3D(-1000, 10, 500));
    m_shaderProgram->setUniformValue("light.intensity", QVector3D(1, 1, 1));    
*/
    m_shaderProgram->setUniformValue("mat.ka", QVector3D(0.2,0.1,0.1));
    m_shaderProgram->setUniformValue("mat.kd", QVector3D(0.7,0,0));
    m_shaderProgram->setUniformValue("mat.ks", QVector3D(1,1,1));
    m_shaderProgram->setUniformValue("mat.shininess", 100.0f);
    m_shaderProgram->setUniformValue("light.position", QVector3D(0, 0, 500));
    m_shaderProgram->setUniformValue("light.intensity", QVector3D(1,1,1));
}

void GeometryScene::paintGL()
{
        m_shaderProgram->bind();

        m_viewMatrix.setToIdentity();
        m_viewMatrix.lookAt(m_eye, m_center, m_up);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glEnable(GL_DEPTH_TEST);
        //glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glEnable(GL_PROGRAM_POINT_SIZE);
        glEnable(GL_DEPTH_CLAMP);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        m_modelMatrix.setToIdentity();
        m_modelMatrix = m_transformationMatrix*m_prevModelMatrix;
        m_prevModelMatrix = m_modelMatrix;
        //m_modelMatrix.rotate(-90,QVector3D(1,0,0));
        QMatrix4x4 modelViewMatrix = m_viewMatrix * m_modelMatrix;        
        m_shaderProgram->setUniformValue("modelViewMatrix", modelViewMatrix);
        m_shaderProgram->setUniformValue("projectionMatrix", m_projectionMatrix);
        m_shaderProgram->setUniformValue("mvpMatrix", m_projectionMatrix*modelViewMatrix*m_centerMatrix);
        m_shaderProgram->setUniformValue("normalMatrix", modelViewMatrix.normalMatrix());

        foreach (VAO_VBO_Object *var, vao_vbo_objects) {
            if (var->getObject().getType() == 1) {
                /*
                m_shaderProgram->setUniformValue("Color",QVector4D(1.0,1.0,1.0,1.0));
                var->getVao1()->bind();
                glDrawArrays(GL_LINE_STRIP,0,var->getObject().getPointsFloatVector().count()/3);
                var->getVao1()->release();
                m_shaderProgram->setUniformValue("Color",QVector4D(1.0,1.0,1.0,0.0));
                var->getVao2()->bind();
                //glDrawArrays(GL_POINTS,0,var->getObject().getCtrlPointsFloatVector().count()/3);
                var->getVao2()->release();

                var->getDvao1()->bind();
                glDrawArrays(GL_LINE_STRIP,0,var->getObject().getDerivativePointsFloatVector().count()/3);
                var->getDvao1()->release();
                var->getDvao2()->bind();
                //glDrawArrays(GL_POINTS,0,var->getObject().getDerivativeCtrlPointsFloatVector().count()/3);
                var->getDvao2()->release();

                //QVector4D(-0.2f,-0.5,0,1);
                //qDebug()<<m_projectionMatrix*modelViewMatrix*QVector4D(-0.2,-0.5,0,0);
                //qDebug()<<m_projectionMatrix*modelViewMatrix*QVector4D(0.5,0.5,0,0);
                //qDebug()<<m_projectionMatrix*modelViewMatrix*QVector4D(-0.1,0.3,0,0);
                //qDebug()<<var->getObject().getPointsFloatVector();
                */
            }
            if (var->getObject().getType()== 2){
                m_shaderProgram->setUniformValue("Color",QVector4D(0.5,0.5,1.0,1.0));
                var->getVao1()->bind();
                glDrawArrays(GL_TRIANGLES,0,var->getObject().getPointsAndNormalsFloatVector2D().count()/2);
                //glDrawArrays(GL_TRIANGLES,0,3);
                var->getVao1()->release();
                //m_shaderProgram->setUniformValue("Color",QVector4D(1.0,1.0,1.0,0.0));
                //var->getVao2()->bind();
                //glDrawArrays(GL_POINTS,0,var->getObject().getCtrlPointsFloatVector().count()/3);
                //var->getVao2()->release();
            }
        }

        if (m_sourceIsInitialized){
            m_shaderProgram->setUniformValue("Color",QVector4D(0.0,1.0,1.0,0.0));
            sourceVAO.bind();
            glDrawArrays(GL_LINE_STRIP,0,sourceFloatArray.count()/3);
            sourceVAO.release();
        }
        if (m_incRaysExist){
            m_shaderProgram->setUniformValue("Color",QVector4D(1.0,1.0,0.0,0.0));
            incRayVAO.bind();
            glDrawArrays(GL_LINES,0,incRayArray.count()/2);
            incRayVAO.release();
        }
        if (m_reflRaysExist){
            m_shaderProgram->setUniformValue("Color",QVector4D(1.0,1.0,0.0,1.0));
            reflRayVAO.bind();
            glDrawArrays(GL_LINES,0,reflRayArray.count()/2);
            reflRayVAO.release();
        }
}

void GeometryScene::mousePressEvent(QMouseEvent *ev)
{    
    if (ev->buttons()==Qt::MidButton){
        float x = float(ev->x()-this->width()/2)/float(this->width());
        float y = -1*float(ev->y()-this->height()/2)/float(this->height());
        m_previousVector.t.setX(x);
        m_previousVector.t.setY(y);
        m_previousVector.tIsSet = 1;
        m_transformation_type = translate;
    }
    else if ((ev->buttons() & Qt::MidButton)&& (ev->button()==Qt::RightButton)){
        float x = (ev->x()-this->width()/2)/float(this->width());
        float y = -1*(ev->y()-this->height()/2)/float(this->height());
        float z = float(qSqrt(1.0f-x*x-y*y));
        m_previousVector.r.setX(x);
        m_previousVector.r.setY(y);
        m_previousVector.r.setZ(z);

        m_previousVector.rIsSet = 1;

        m_transformation_type = rotate;
    }
}

void GeometryScene::mouseMoveEvent(QMouseEvent *ev)
{
        switch(m_transformation_type){
            case rotate:
            {
                m_previousVector.rIterator++;
                if (m_previousVector.rIsSet && m_previousVector.rIterator>3){
                    float x = (ev->x()-this->width()/2)/float(this->width());
                    float y = -1*(ev->y()-this->height()/2)/float(this->height());
                    float z = float(qSqrt(1-x*x-y*y));
                    QVector3D r(x,y,z);
                    float number = r.x()*r.x()+r.y()*r.y();
                    if (number <= float(0.1225)){
                        QVector3D osa = QVector3D::crossProduct(r,m_previousVector.r);
                        m_angle = -0.07*QVector3D::dotProduct(m_previousVector.r,r);
                        osa.normalize();
                        osa = osa*sin(m_angle);
                        m_rotation = QQuaternion(cos(m_angle),osa);
                    }
                    else {
                        QVector2D prev = QVector2D(m_previousVector.r.x(),m_previousVector.r.y());
                        QVector2D newVector = QVector2D(r.x(),r.y());
                        QVector3D osa = QVector3D::crossProduct(QVector3D(prev,0),QVector3D(newVector,0));
                        osa.normalize();
                        m_angle = 0.2*QVector2D::dotProduct(prev,newVector);
                        osa = osa*sin(m_angle);
                        m_rotation = QQuaternion(cos(m_angle),osa);
                    }
                    m_transformationMatrix.setToIdentity();
                    m_transformationMatrix.rotate(m_rotation);
                    m_previousVector.r = r;
                    m_previousVector.rIterator = 0;
                    update();
                }
                break;
            }
            case translate: {
                m_previousVector.tIterator++;
                if (m_previousVector.tIsSet == 1 && m_previousVector.tIterator>5){
                    float x = float(ev->x()-this->width()/2)/float(this->width());
                    float y = -1*float(ev->y()-this->height()/2)/float(this->height());
                    QVector2D t(x,y);
                    m_transformationMatrix.setToIdentity();
                    QVector2D trans = t - m_previousVector.t;
                    m_transformationMatrix.translate(trans.x()*2*m_biggestObject,trans.y()*2*m_biggestObject);
                    m_previousVector.t = t;
                    m_previousVector.tIterator = 0;
                    update();
                }
                break;
            }
            case scale: {
                m_previousVector.sIterator++;
                if (m_previousVector.sIsSet == 1 && m_previousVector.sIterator>3){
                    m_transformationMatrix.setToIdentity();
                    float s = ev->y();
                    float scale;
                    if (s < m_previousVector.s)
                        scale = float(1.2);
                    else {
                        scale = float(0.8);
                    }
                    m_transformationMatrix.scale(scale);
                    m_previousVector.sIterator = 0;
                    m_previousVector.s = s;
                    update();
                }
                break;
            }
            case nothing:
                break;
            }
}

void GeometryScene::mouseReleaseEvent(QMouseEvent *ev)
{
    if ((ev->button()==Qt::RightButton)&&(ev->buttons() & Qt::MidButton)){
        m_transformation_type = scale;
        m_previousVector.sIsSet = 1;
        m_previousVector.s = ev->y();
    }
    else {
        m_previousVector.rIsSet = 0;
        m_previousVector.tIsSet = 0;
        m_previousVector.rIterator = 0;
        m_previousVector.tIterator = 0;
        m_transformation_type = nothing;
    }
}

void GeometryScene::initializeData()
{

}

void GeometryScene::printContextInfo()
{
    QString glType;
      QString glVersion;
      QString glProfile;

      // Get Version Information
      glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
      glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

      // Get Profile Information

#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
      switch (format().profile())
      {
        CASE(NoProfile);
        CASE(CoreProfile);
        CASE(CompatibilityProfile);
      }
    #undef CASE

      //qPrintable() will print our QString w/o quotes around it.
      //qDebug() << qPrintable(glType) << qPrintable(glVersion)<<"("<<qPrintable(glProfile)<<")";
}

void GeometryScene::setProjectionMatrix()
{
    m_projectionMatrix.setToIdentity();

    float aspectRatio = 1;
    switch (m_projectionType) {
    case 0:{
        m_projectionMatrix.ortho(-1,1,-1,1,float(0.0),10);
        //m_projectionMatrix.frustum(-width()/2.0f,width()/2.0f,-height()/2.0f,height()/2.0f,0.1f,10.0f);
        break;
    }
    case 1:{
        m_projectionMatrix.perspective(90, aspectRatio, 0.5, 40);
        break;
    }
    }
}

void GeometryScene::fitAllObjectsIn()
{    
    float objectWidth = 0;
    float objectHeight = 0;
    foreach(VAO_VBO_Object* v,vao_vbo_objects){
       m_left = v->getObject().getBoundingRect().at(0)<m_left ? v->getObject().getBoundingRect().at(0):m_left;
       m_top = v->getObject().getBoundingRect().at(1)>m_top ? v->getObject().getBoundingRect().at(1):m_top;
       m_right = v->getObject().getBoundingRect().at(2)>m_right ? v->getObject().getBoundingRect().at(2):m_right;
       m_bottom = v->getObject().getBoundingRect().at(3)<m_bottom ? v->getObject().getBoundingRect().at(3):m_bottom;

       objectWidth = m_right - m_left;
       objectHeight = m_top - m_bottom;
       float pom = objectWidth > objectHeight ? objectWidth : objectHeight;
       m_biggestObject = m_biggestObject>pom ? m_biggestObject : pom;

    }
     m_centerMatrix.setToIdentity();
    m_projectionMatrix.setToIdentity();
    m_centerMatrix.translate(-m_left - objectWidth/2, -m_bottom - objectHeight/2);
    m_projectionMatrix.ortho(-0.6f*m_biggestObject,0.6f*m_biggestObject,-0.6f*m_biggestObject,0.6f*m_biggestObject,float(0.0),10);
    this->update();
}

void GeometryScene::axisSystemInicialization()
{
    makeCurrent();
    axisFloatArray.append(0.0f);
    axisFloatArray.append(0.0f);
    axisFloatArray.append(0.0f);
    axisFloatArray.append(1.0f);
    axisFloatArray.append(0.0f);
    axisFloatArray.append(0.0f);
    axisFloatArray.append(0.0f);
    axisFloatArray.append(0.0f);
    axisFloatArray.append(0.0f);
    axisFloatArray.append(0.0f);
    axisFloatArray.append(1.0f);
    axisFloatArray.append(0.0f);
    axisFloatArray.append(0.0f);
    axisFloatArray.append(0.0f);
    axisFloatArray.append(0.0f);
    axisFloatArray.append(0.0f);
    axisFloatArray.append(0.0f);
    axisFloatArray.append(1.0f);
    m_shaderProgram->bind();
    axisVAO.create();
    axisVAO.bind();
    axisVBO.create();
    axisVBO.bind();
    axisVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    axisVBO.allocate(&axisFloatArray.first(),axisFloatArray.count()*sizeof (float));
    m_shaderProgram->enableAttributeArray(0);
    m_shaderProgram->setAttributeBuffer(0,GL_FLOAT,0,3,0);
    axisVBO.release();
    axisVAO.release();
    m_shaderProgram->release();
    m_axisIsInitialized = true;
}

void GeometryScene::setMatrixDefault()
{
    m_prevModelMatrix.setToIdentity();
    m_modelMatrix.setToIdentity();
    m_transformationMatrix.setToIdentity();
    m_viewMatrix.setToIdentity();    
}

QVector3D GeometryScene::countRotationAxis(QVector3D vektor, QVector3D normal)
{
    QVector3D rotVector = QVector3D::crossProduct(vektor,normal);
    rotVector.normalize();
    return rotVector;
}

void GeometryScene::geometryTransformXYView()
{
    setMatrixDefault();
    update();
}

void GeometryScene::geometryChanged(BasicObject &o)
{
    //qDebug()<<"ctrlpoints"<<o.getCtrlPointsFloatVector();
    //qDebug()<<"points"<<o.getPointsFloatVector();

    makeCurrent();

    QOpenGLVertexArrayObject *a1 = new QOpenGLVertexArrayObject();
    QOpenGLBuffer *b1 = new QOpenGLBuffer();
    QOpenGLVertexArrayObject *a2 = new QOpenGLVertexArrayObject();
    QOpenGLBuffer *b2 = new QOpenGLBuffer();
    QOpenGLVertexArrayObject *da1 = new QOpenGLVertexArrayObject();
    QOpenGLBuffer *db1 = new QOpenGLBuffer();
    QOpenGLVertexArrayObject *da2 = new QOpenGLVertexArrayObject();
    QOpenGLBuffer *db2 = new QOpenGLBuffer();
    m_shaderProgram->bind();

    a1->create();
    a1->bind();
    b1->create();
    b1->bind();
    b1->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    b1->allocate(&o.getPointsFloatVector().first(),sizeof (float)*o.getPointsFloatVector().count());
    m_shaderProgram->enableAttributeArray(0);
    m_shaderProgram->setAttributeBuffer(0,GL_FLOAT,0,3,0);
    a1->release();
    b1->release();
    a2->create();
    a2->bind();
    b2->create();
    b2->bind();
    b2->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    //b2->allocate(&o.getCtrlPointsFloatVector().first(),sizeof (float)*o.getCtrlPointsFloatVector().count());
    m_shaderProgram->enableAttributeArray(0);
    m_shaderProgram->setAttributeBuffer(0,GL_FLOAT,0,3,0);
    a2->release();
    b2->release();

    da1->create();
    da1->bind();
    db1->create();
    db1->bind();
    db1->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    db1->allocate(&o.getDerivativePointsFloatVector().first(),sizeof (float)*o.getDerivativePointsFloatVector().count());
    m_shaderProgram->enableAttributeArray(0);
    m_shaderProgram->setAttributeBuffer(0,GL_FLOAT,0,3,0);
    da1->release();
    db1->release();

    da2->create();
    da2->bind();
    db2->create();
    db2->bind();
    db2->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    //db2->allocate(&o.getDerivativeCtrlPointsFloatVector().first(),sizeof (float)*o.getDerivativeCtrlPointsFloatVector().count());

    m_shaderProgram->enableAttributeArray(0);
    m_shaderProgram->setAttributeBuffer(0,GL_FLOAT,0,3,0);
    da2->release();
    db2->release();

    m_shaderProgram->release();

    VAO_VBO_Object *abo = new VAO_VBO_Object(a1,b1,a2,b2,da1,db1,da2,db2,o);
    vao_vbo_objects.append(abo);

    fitAllObjectsIn();

}

void GeometryScene::geometryChanged2D(BasicObject &o)
{
    makeCurrent();
    for (int i = 3; i<o.getPointsAndNormalsFloatVector2D().count();i=i+6){
        //qDebug()<<o.getPointsAndNormalsFloatVector2D()[i]<<o.getPointsAndNormalsFloatVector2D()[i+1]<<o.getPointsAndNormalsFloatVector2D()[i+2];
    }

    QOpenGLVertexArrayObject *a1 = new QOpenGLVertexArrayObject();
    QOpenGLBuffer *b1 = new QOpenGLBuffer();
    //QOpenGLVertexArrayObject *da1 = new QOpenGLVertexArrayObject();
    //QOpenGLBuffer *db1 = new QOpenGLBuffer();

    m_shaderProgram->bind();

    a1->create();
    a1->bind();
    b1->create();
    b1->bind();
    b1->setUsagePattern(QOpenGLBuffer::DynamicDraw);

    b1->allocate(&o.getPointsAndNormalsFloatVector2D().first(),sizeof (float)*o.getPointsAndNormalsFloatVector2D().count());
    m_shaderProgram->enableAttributeArray(0);
    m_shaderProgram->setAttributeBuffer(0,GL_FLOAT,0,3,24);
    m_shaderProgram->enableAttributeArray(1);
    m_shaderProgram->setAttributeBuffer(1,GL_FLOAT,12,3,24);
    a1->release();
    b1->release();
/*
    da1->create();
    da1->bind();
    db1->create();
    db1->bind();
    db1->setUsagePattern(QOpenGLBuffer::DynamicDraw);

    db1->allocate(&o.getPointsNormalsFloatVector2D().first(),sizeof (float)*o.getPointsNormalsFloatVector2D().count());

    m_shaderProgram->enableAttributeArray(0);
    m_shaderProgram->setAttributeBuffer(0,GL_FLOAT,0,3,0);
    da1->release();
    db1->release();
*/
    m_shaderProgram->release();
    VAO_VBO_Object *abo = new VAO_VBO_Object(a1, b1, o);
    vao_vbo_objects.append(abo);
    fitAllObjectsIn();
}

void GeometryScene::sourceUpdated(QVector<float> s)
{
    makeCurrent();
    sourceFloatArray = s;

    m_shaderProgram->bind();
    sourceFloatArray = s;
    sourceVAO.create();
    sourceVAO.bind();
    sourceVBO.create();
    sourceVBO.bind();

    sourceVBO.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    sourceVBO.allocate(&sourceFloatArray.first(),sizeof (float)*sourceFloatArray.count());

    m_shaderProgram->enableAttributeArray(0);
    m_shaderProgram->setAttributeBuffer(0,GL_FLOAT,0,3,0);

    sourceVBO.release();
    sourceVAO.release();
    m_shaderProgram->release();
    m_sourceIsInitialized = true;
    //fitAllObjectsIn();
}

void GeometryScene::geometryTraced(QVector<float> v,QVector<float> r)
{
    makeCurrent();

    incRayArray = v;
    m_shaderProgram->bind();
    incRayVAO.create();
    incRayVAO.bind();
    incRayVBO.create();
    incRayVBO.bind();
    incRayVBO.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    incRayVBO.allocate(&incRayArray.first(),sizeof(float)*incRayArray.count());
    m_shaderProgram->enableAttributeArray(0);
    m_shaderProgram->setAttributeBuffer(0,GL_FLOAT,0,3,0);
    incRayVBO.release();
    incRayVAO.release();
    m_incRaysExist = true;

    reflRayArray = r;
    reflRayVAO.create();
    reflRayVAO.bind();
    reflRayVBO.create();
    reflRayVBO.bind();
    reflRayVBO.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    reflRayVBO.allocate(&reflRayArray.first(),sizeof(float)*reflRayArray.count());
    m_shaderProgram->enableAttributeArray(0);
    m_shaderProgram->setAttributeBuffer(0,GL_FLOAT,0,3,0);
    reflRayVBO.release();
    reflRayVAO.release();
    m_shaderProgram->release();
    m_reflRaysExist = true;
    update();
}

