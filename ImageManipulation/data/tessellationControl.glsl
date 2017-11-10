#version 410

in vec2 TCposition[];

layout(vertices = 4) out;
out vec2 TEposition[];

void main() {
  gl_TessLevelOuter[0] = 1;
  gl_TessLevelOuter[1] = 16;
  TEposition[gl_InvocationID] = TCposition[gl_InvocationID];
  //gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}
