#version 400
uniform highp vec4 Color;
struct Material {
    lowp vec3 ka;
    lowp vec3 kd;
    lowp vec3 ks;
    lowp float shininess;
};

struct Light {
    lowp vec3 position;
    lowp vec3 intensity;
};

uniform Material mat;

uniform Light light;

in vec3 vVertex;
in vec3 vNormal;
out vec4 fColor;

void main(void) {
    vec3 n = normalize(vNormal);
    vec3 L = normalize(light.position.xyz - vVertex);
    //vec3 E = normalize(-vVertex);
    vec3 E = vec3(-vVertex);
    vec3 R = normalize(reflect(-L, n));
    float LdotN = dot(L, n);
    float diffuse = abs(LdotN);
    //float diffuse = max(LdotN, 0.0);
    vec3 spec = vec3(0, 0, 0);

    if(LdotN > 0.0) {
        float RdotE = max(dot(R, E), 0.0);
        spec = light.intensity * pow(RdotE, mat.shininess);
    }
    vec3 color = light.intensity * (mat.ka + mat.kd * diffuse + mat.ks * spec*0);

    fColor = vec4(color,1);
}
