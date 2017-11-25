#version 330
#extension GL_ARB_gpu_shader5                : enable
#extension GL_ARB_shader_precision           : enable
#extension GL_ARB_texture_cube_map_array     : enable
#extension GL_ARB_separate_shader_objects    : enable
#extension GL_ARB_shading_language_420pack   : enable
#extension GL_ARB_shading_language_packing   : enable
#extension GL_ARB_explicit_uniform_location  : enable
#extension GL_ARB_fragment_coord_conventions : enable
layout(origin_upper_left) in vec4 gl_FragCoord;

layout(location = 0) uniform vec3 g_cam_pos;
layout(location = 1) uniform int  g_show_pass;
layout(location = 2) uniform int  g_cubemap_id;

layout(binding = 2) uniform sampler2DArray   s_texture;
layout(binding = 3) uniform samplerCubeArray s_cubemaps;

layout(location = 0) in vec3 g_pos;
layout(location = 1) in vec3 g_normal;
layout(location = 2) in vec2 g_uv;
layout(location = 3) in flat int g_index;

layout(location = 0) out vec4 g_color;

int ColorToInt(vec3 c) {
  int r = int(c.r * 255.0);
  int g = int(c.g * 255.0);
  int b = int(c.b * 255.0);
  return b + (g << 8) + (r << 16);
}

vec3 IntToColor(int i) {
  vec3 color;
  color.r = float(i >> 16 & 255) / 255.0;
  color.g = float(i >> 8  & 255) / 255.0;
  color.b = float(i       & 255) / 255.0;
  return color;
}

void main() {
  vec4 diff = texture(s_texture, vec3(g_uv, g_index));
  vec4 refl = texture(s_cubemaps, vec4(reflect((g_pos - g_cam_pos), g_normal), g_cubemap_id));
  vec4 tint = vec4(0);

  if (g_index == 0) tint += vec4(1, 0, 0, 1);
  if (g_index == 1) tint += vec4(0, 1, 0, 1);
  if (g_index == 2) tint += vec4(0, 0, 1, 1);

  g_color = mix(diff * 0.4 + tint * 0.6, refl, dot(g_normal, normalize(g_pos - g_cam_pos)) * 0.5 + 0.5);

  if (g_show_pass == 1) g_color = diff;
  if (g_show_pass == 2) g_color = refl;
  if (g_show_pass == 3) g_color = tint;
  if (g_show_pass == 4) g_color = vec4(IntToColor(g_index + 1), 1);
  if (g_show_pass == 5) g_color = vec4(g_uv, 0, 1);
  if (g_show_pass == 6) g_color = vec4(g_normal, 1);
  if (g_show_pass == 7) g_color = vec4(g_pos, 1);
  if (g_show_pass == 8) g_color = vec4(vec3(gl_FragCoord.z), 1);
}
