#ifndef VAO_VBO_OBJECT_H
#define VAO_VBO_OBJECT_H

#include "basicobject.h"
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class VAO_VBO_Object
{
public:
    VAO_VBO_Object( QOpenGLVertexArrayObject* v1, QOpenGLBuffer* b1, QOpenGLVertexArrayObject* v2, QOpenGLBuffer* b2,
                    QOpenGLVertexArrayObject* dv1, QOpenGLBuffer* db1, QOpenGLVertexArrayObject* dv2, QOpenGLBuffer* db2,const BasicObject& obj);
    VAO_VBO_Object( QOpenGLVertexArrayObject* v1, QOpenGLBuffer* b1, const BasicObject& obj);
    VAO_VBO_Object( QOpenGLVertexArrayObject* v1, QOpenGLBuffer* b1, QOpenGLVertexArrayObject* dv1, QOpenGLBuffer* db1, const BasicObject& obj);
    QOpenGLVertexArrayObject *getVao1() const;
    QOpenGLVertexArrayObject *getVao2() const;

    const BasicObject &getObject() const;

    QOpenGLVertexArrayObject *getDvao1() const;

    QOpenGLVertexArrayObject *getDvao2() const;

private:
    QOpenGLVertexArrayObject* vao1; //vao for points
    QOpenGLVertexArrayObject* vao2; //vao for ctrl points
    QOpenGLVertexArrayObject* dvao1; //vao for derivative
    QOpenGLVertexArrayObject* dvao2; //vao for derivative ctrl points
    QOpenGLBuffer* vbo1;
    QOpenGLBuffer* vbo2;
    QOpenGLBuffer* dvbo1;
    QOpenGLBuffer* dvbo2;
    const BasicObject& object;
};

#endif // VAO_VBO_OBJECT_H
