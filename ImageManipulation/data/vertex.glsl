#version 410

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 textureCoord;

out vec2 TextureCoord;

uniform mat4 transform;

void main() {
  gl_Position = transform * vec4(position, 0.0, 1.0);
  gl_PointSize = 5.0;
  TextureCoord = vec2(textureCoord.x, 1.0f - textureCoord.y);
}
