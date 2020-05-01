#version 400
struct Material {
    lowp vec3 ka;
    lowp vec3 kd;
    lowp vec3 ks;
    lowp float shininess;
};

struct Light {
    lowp vec4 position;
    lowp vec3 intensity;
};

uniform Material mat;

uniform Light light;

in vec3 N;
in vec3 v;

//out vec4 fColor;

void main(void) {
    vec3 n = normalize(N);
    vec3 L = normalize(light.position.xyz - v);
    vec3 E = normalize(-v);
    vec3 R = normalize(reflect(-L, n));

    float LdotN = dot(L, n);
    float diffuse = max(LdotN, 0.0);
    vec3 spec = vec3(0, 0, 0);

    if(LdotN > 0.0) {
        float RdotE = max(dot(R, E), 0.0);
        spec = light.intensity * pow(RdotE, mat.shininess);
    }
    vec3 color = light.intensity * (mat.ka + mat.kd * diffuse + mat.ks * spec);
    //fColor = vec4(color, 1.0);
}
