#version 410

in vec2 TextureCoord;

out vec4 FragmentColour;

uniform sampler2D imageTexture;

void main() {
  //FragmentColour = vec4(1,0,0,1);
  FragmentColour = texture(imageTexture, TextureCoord);
}
