#version 410

layout(isolines) in;

uniform mat4 model;
uniform mat4 transform;

//in vec2 TEposition[];

//out gl_PerVertex {
//	vec4 gl_Position;
//	float gl_PointSize;
//	float gl_ClipDistance[];
//};

vec2 bezier(float u, vec2 p0, vec2 p1, vec2 p2, vec2 p3)
{
	float B0 = (1.-u)*(1.-u)*(1.-u);
	float B1 = 3.*u*(1.-u)*(1.-u);
	float B2 = 3.*u*u*(1.-u);
	float B3 = u*u*u;

	vec2 p = B0*p0 + B1*p1 + B2*p2 + B3*p3;
	return p;
} 

void main() {
  //gl_Position = transform * model * vec4(position, 0.0, 1.0);
  float u = gl_TessCoord.x;
  //float v = gl_TessCoord.y;
  vec2 p0 = vec2(gl_in[0].gl_Position);
  vec2 p1 = vec2(gl_in[1].gl_Position);
  vec2 p2 = vec2(gl_in[2].gl_Position);
  vec2 p3 = vec2(gl_in[3].gl_Position);
  //vec2 p0 = TEposition[0];
  //vec2 p1 = TEposition[1];
  //vec2 p2 = TEposition[2];
  //vec2 p3 = TEposition[3];
  vec4 pos = vec4(bezier(u, p0, p1, p2, p3), 0.0, 1.0);
  gl_Position = transform * model * pos;
}
