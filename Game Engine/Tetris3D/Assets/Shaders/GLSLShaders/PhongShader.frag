#version 330 core 

in vec3 tnorm;
in vec4 eyeCoords;
in vec2 TexCoords;

layout(location = 0) out vec4 FragColor;

uniform vec3 objectColor;
uniform sampler2D texture1;

struct LightInfo {
  vec4 Position; // Light position in eye coords.
  vec3 La;       // Ambient light intensity
  vec3 Ld;       // Diffuse light intensity
  vec3 Ls;       // Specular light intensity
};
uniform LightInfo Light[2];

struct MaterialInfo {
  vec3 Ka;            // Ambient reflectivity
  vec3 Kd;            // Diffuse reflectivity
  vec3 Ks;            // Specular reflectivity
  float Shininess;    // Specular shininess factor
};
uniform MaterialInfo Material;

void main() 
{
    // Light 1
    vec3 s1 = normalize(vec3(Light[0].Position - eyeCoords));
    vec3 v1 = normalize(-eyeCoords.xyz);
    vec3 r1 = reflect(-s1, tnorm);
    float sDotN1 = max(dot(s1,tnorm), 0.0);
    vec3 ambient1 = Light[0].La * Material.Ka;
    vec3 diffuse1 = Light[0].Ld * Material.Kd * sDotN1;
    vec3 spec1= vec3(0.0);
    if(sDotN1 > 0.0)
       spec1 = Light[0].Ls * Material.Ks * pow(max(dot(r1, v1), 0.0), Material.Shininess);

    // Light 2
    vec3 s2 = normalize(vec3(Light[1].Position - eyeCoords));
    vec3 v2 = normalize(-eyeCoords.xyz);
    vec3 r2 = reflect(-s2, tnorm );
    float sDotN2 = max(dot(s2,tnorm), 0.0 );
    vec3 ambient2 = Light[1].La * Material.Ka;
    vec3 diffuse2 = Light[1].Ld * Material.Kd * sDotN2;
    vec3 spec2 = vec3(0.0);
    if(sDotN2 > 0.0)
       spec2 = Light[1].Ls * Material.Ks * pow(max(dot(r2, v2), 0.0), Material.Shininess);

    vec3 LightIntensity = ambient1 + diffuse1 + spec1 + ambient2 + diffuse2 + spec2;

    FragColor = texture(texture1, TexCoords) * vec4(LightIntensity * objectColor, 1.0);
}
