#version 410

layout(isolines, equal_spacing, ccw) in;

uniform mat4 model;
uniform mat4 transform;

vec2 catmullRom(float u, vec2 p0, vec2 p1, vec2 p2, vec2 p3)
{
	vec2 p = 0.5 * ((-p0 + 3*p1 - 3*p2 + p3)*u*u*u + (2*p0 - 5*p1 + 4*p2 -p3)*u*u + (-p0 + p2)*u + (2*p1));
	return p;
}

void main() {
  float u = gl_TessCoord.x;
  vec2 p0 = vec2(gl_in[0].gl_Position);
  vec2 p1 = vec2(gl_in[1].gl_Position);
  vec2 p2 = vec2(gl_in[2].gl_Position);
  vec2 p3 = vec2(gl_in[3].gl_Position);
  vec4 pos = vec4(catmullRom(u, p0, p1, p2, p3), 0.0, 1.0);
  gl_Position = transform * model * pos;
}
