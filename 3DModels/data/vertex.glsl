#version 410

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normalVec;
layout(location = 2) in vec2 TextureCoord;

//out vec2 TextureCoord;

//uniform mat4 model;
//uniform mat4 transform;
out vec3 normal;
out vec3 fragPos;
out vec2 textureCoord;

uniform mat4 reverseScaling;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * reverseScaling * model * vec4(position, 1.0);
  normal = mat3(transpose(inverse(model))) * normalVec;
  fragPos = vec3(model * vec4(position, 1.0));
  textureCoord = vec2(TextureCoord.x, 1.0f - TextureCoord.y);
  //textureCoord = TextureCoord;
  //gl_PointSize = 5.0;
}
