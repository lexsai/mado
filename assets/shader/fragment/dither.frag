out vec4 frag_color;

in vec3 vs_p;
in vec2 vs_uv;

uniform sampler2D screen;

float bayer_matrix[16] = float[] (
  -0.5,      0.0,    -0.375,   0.125,
   0.25,    -0.25,    0.375,  -0.125,
  -0.3125,   0.1875, -0.4375,  0.0625,
   0.4375,  -0.0625,  0.3125, -0.1875
);

#define color_range 32.0

float bayer_r = 1.0 / 16.0;

void main()
{
  ivec2 uv = ivec2(vs_uv * 0.5 * vec2(textureSize(screen, 0)));

  vec3 tex_color = texture(screen, vs_uv).rgb;
  vec3 dither_color = tex_color + bayer_r * bayer_matrix[(uv.y % 4) * 4 + (uv.x % 4)];
  vec3 nearest_color = round(dither_color * color_range) / color_range;
  
  frag_color = vec4(nearest_color, 1.0);
}
