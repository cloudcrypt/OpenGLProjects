#version 410

//in vec2 TextureCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 FragmentColour;

struct Material {
	float specularExp;
	vec3 specular;
	vec3 diffuse;
	vec3 ambient;
};

uniform Material material = Material(32, vec3(0.5,0.5,0.5), vec3(1.0,0.5,0.31), vec3(1.0,0.5,0.31));
uniform vec3 lightPos;
uniform vec3 cameraPos;
//uniform vec3 objectColour = vec3(1, 0.5, 0.31);
uniform vec3 lightColour = vec3(1, 1, 1);

//uniform sampler2D imageTexture;
//uniform int quantizationLevel = 8;
//uniform bool grayscale = false;
//uniform bool curve = false;

//float quantizeValue(float value, float originalLevel, float targetLevel) {
//  value *= (pow(2, originalLevel) - 1);
//  value /= (pow(2, originalLevel) / pow(2, targetLevel));
//  value = floor(value);
//  value /= (pow(2, targetLevel) - 1);
//  return value;
//}

//vec4 quantizeColor(vec4 color, float originalLevel, float targetLevel) {
//  return vec4(quantizeValue(color.r, originalLevel, targetLevel), quantizeValue(color.g, originalLevel, targetLevel), quantizeValue(color.b, originalLevel, targetLevel), color.a);
//}

void main() {
  //FragmentColour = vec4(1,0,0,1);
  float ambientStrength = 0.2; //0.1;
  vec3 ambient = ambientStrength * (lightColour * material.ambient);

  float diffuseStrength = 0.5;
  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(lightPos - fragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diffuseStrength * ((diff * material.diffuse) * lightColour);

  float specularStrength = 1.0; //0.5;
  vec3 viewDir = normalize(cameraPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.specularExp);
  vec3 specular = specularStrength * (spec * material.specular) * lightColour;

  vec3 result = ambient + diffuse + specular;
  FragmentColour = vec4(result, 1);
  //if (curve) {
  //  FragmentColour = vec4(1,0,0,1);
  //  return;
  //}
  //FragmentColour = texture(imageTexture, TextureCoord);
  //FragmentColour = quantizeColor(FragmentColour, 8, quantizationLevel);
  //if (grayscale) {
  //  float gray = (0.299 * FragmentColour.r) + (0.587 * FragmentColour.g)  + (0.114 * FragmentColour.b);
  //  FragmentColour = vec4(gray, gray, gray, 1);
  //}
}
