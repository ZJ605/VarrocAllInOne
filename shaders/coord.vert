#version 400
uniform highp mat4 modelViewMatrix;
uniform highp mat3 normalMatrix;
uniform highp mat4 projectionMatrix;
uniform highp mat4 mvpMatrix;

layout(location = 0) in vec3 Vertex;
layout(location = 1) in vec3 Normal;
out vec3 vNormal;
out vec3 vVertex;

void main(void)
{
    gl_PointSize = 5;

    vVertex = vec3(modelViewMatrix*vec4(Vertex,1.0));
    vNormal = normalize(normalMatrix*Normal);
    gl_Position = mvpMatrix*vec4(Vertex,1.0);
}
