#version 410

in vec2 TextureCoord;

out vec4 FragmentColour;

uniform sampler2D imageTexture;
uniform int quantizationLevel = 8;
uniform bool grayscale = false;
uniform bool curve = false;

float quantizeValue(float value, float originalLevel, float targetLevel) {
  value *= (pow(2, originalLevel) - 1);
  value /= (pow(2, originalLevel) / pow(2, targetLevel));
  value = floor(value);
  value /= (pow(2, targetLevel) - 1);
  return value;
}

vec4 quantizeColor(vec4 color, float originalLevel, float targetLevel) {
  return vec4(quantizeValue(color.r, originalLevel, targetLevel), quantizeValue(color.g, originalLevel, targetLevel), quantizeValue(color.b, originalLevel, targetLevel), color.a);
}

void main() {
  if (curve) {
    FragmentColour = vec4(1,0,0,1);
    return;
  }
  FragmentColour = texture(imageTexture, TextureCoord);
  FragmentColour = quantizeColor(FragmentColour, 8, quantizationLevel);
  // FragmentColour.r *= 255;
  // FragmentColour.r /= 64;
  // FragmentColour.r = floor(FragmentColour.r);
  // FragmentColour.r /= 3;

  // FragmentColour.g *= 255;
  // FragmentColour.g /= 64;
  // FragmentColour.g = floor(FragmentColour.g);
  // FragmentColour.g /= 3;

  // FragmentColour.b *= 255;
  // FragmentColour.b /= 64;
  // FragmentColour.b = floor(FragmentColour.b);
  // FragmentColour.b /= 3;

  //float gray = dot(FragmentColour.rgb, vec3(0.299, 0.587, 0.114));
  if (grayscale) {
    float gray = (0.299 * FragmentColour.r) + (0.587 * FragmentColour.g)  + (0.114 * FragmentColour.b);
    FragmentColour = vec4(gray, gray, gray, 1);
  }
}
