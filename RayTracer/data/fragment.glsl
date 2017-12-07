#version 410

in vec2 textureCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 FragmentColour;

struct Material {
	float specularExp;
	vec3 specular;
	sampler2D diffuse;
	sampler2D ao;
	vec3 ambient;
};

uniform Material material;
uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform vec3 lightColour = vec3(1, 1, 1);


uniform bool aoMode = true;
uniform bool textureMode = true;


void main() {
  float ambientStrength = 0.2;
  vec3 ambient;
  if (aoMode) {
	  if (textureMode) {
	  	ambient = vec3(texture(material.ao, textureCoord)) * vec3(texture(material.diffuse, textureCoord));
	  } else {
	  	ambient = ambientStrength * (lightColour * material.ambient);
    	  }
  } else {
	  if (textureMode) {
      	  	ambient = ambientStrength * vec3(texture(material.diffuse, textureCoord));
    	  } else {
	  	ambient = ambientStrength * (lightColour * material.ambient);
    	  }
  }

  float diffuseStrength = 0.5;
  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(lightPos - fragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse;
  if (textureMode) {
    diffuse = diffuseStrength * diff * vec3(texture(material.diffuse, textureCoord));
  } else {
    diffuse = diffuseStrength * ((diff * material.ambient) * lightColour);
  }

  float specularStrength = 1.0;
  vec3 viewDir = normalize(cameraPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.specularExp);
  vec3 specular = specularStrength * (spec * material.specular) * lightColour;

  vec3 result = ambient + diffuse + specular;
  FragmentColour = vec4(result, 1);
}
