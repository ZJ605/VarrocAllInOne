#include "vao_vbo_object.h"

VAO_VBO_Object::VAO_VBO_Object(QOpenGLVertexArrayObject* v1, QOpenGLBuffer* b1, QOpenGLVertexArrayObject* v2, QOpenGLBuffer* b2,
                               QOpenGLVertexArrayObject* dv1, QOpenGLBuffer* db1, QOpenGLVertexArrayObject* dv2, QOpenGLBuffer* db2,const BasicObject& obj):vao1(v1),vbo1(b1),vao2(v2),vbo2(b2), dvao1(dv1), dvbo1(db1),dvao2(dv2), dvbo2(db2), object(obj)
{

}

VAO_VBO_Object::VAO_VBO_Object(QOpenGLVertexArrayObject *v1, QOpenGLBuffer *b1, const BasicObject &obj):vao1(v1), vbo1(b1), object(obj)
{

}

VAO_VBO_Object::VAO_VBO_Object(QOpenGLVertexArrayObject *v1, QOpenGLBuffer *b1, QOpenGLVertexArrayObject *dv1, QOpenGLBuffer *db1, const BasicObject &obj):vao1(v1),vbo1(b1), dvao1(dv1), dvbo1(db1), object(obj)
{

}

QOpenGLVertexArrayObject *VAO_VBO_Object::getVao2() const
{
    return vao2;
}

QOpenGLVertexArrayObject *VAO_VBO_Object::getVao1() const
{
    return vao1;
}

const BasicObject &VAO_VBO_Object::getObject() const
{
    return object;
}

QOpenGLVertexArrayObject *VAO_VBO_Object::getDvao1() const
{
    return dvao1;
}

QOpenGLVertexArrayObject *VAO_VBO_Object::getDvao2() const
{
    return dvao2;
}
