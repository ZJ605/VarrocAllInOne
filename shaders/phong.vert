#version 400
uniform highp mat4 modelViewMatrix;
uniform highp mat3 normalMatrix;
uniform highp mat4 projectionMatrix;
uniform highp mat4 mvpMatrix;

layout(location = 0) in vec4 Vertex;
layout(location = 1) in vec3 Normal;

out vec3 N;
out vec3 v;

void main(void)
{
    N = normalize(normalMatrix * Normal);
    v = vec3(modelViewMatrix * Vertex);

    gl_Position = mvpMatrix * Vertex;
}

