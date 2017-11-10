#version 330
 
layout(lines) in;
layout(triangle_strip, max_vertices = 4) out;
 
void main(void)
{
    vec4 a;
    vec4 b;
    vec4 c;
    vec4 d;

    int i = 0;
    for(i = 0; i < gl_in.length(); i++)
    {
        a = gl_in[i].gl_Position;
        //a.x -= 0.01;
        //a.y -= 0.01;
        //a.z = 0.0;
        gl_Position = a;
        EmitVertex();

        b = gl_in[i].gl_Position;
        b.x += 0.01;
        //b.y -= 0.01;
        //b.z = 0.0;
        gl_Position = b;
        EmitVertex();

        d = gl_in[i].gl_Position;
        //d.x -= 0.01;
        d.y += 0.01;
        //d.z = 0.0;
        gl_Position = d;        
        EmitVertex();

        c = gl_in[i].gl_Position;
        c.x += 0.01;
        c.y += 0.01;
        //c.z = 0.0;
        gl_Position = c;
        EmitVertex();

    }
    EndPrimitive();

}