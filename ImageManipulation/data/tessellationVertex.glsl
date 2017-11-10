#version 410

layout(location = 0) in vec2 position;
//layout(location = 1) in vec2 textureCoord;

//uniform mat4 model;
//uniform mat4 transform;

void main() {
  //gl_Position = transform * model * vec4(position, 0.0, 1.0);
  gl_Position = vec4(position, 0.0, 1.0);
  //gl_PointSize = 5.0;
}
