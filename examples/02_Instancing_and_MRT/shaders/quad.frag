#version 330
#extension GL_ARB_gpu_shader5                : enable
#extension GL_ARB_shader_precision           : enable
#extension GL_ARB_enhanced_layouts           : enable
#extension GL_ARB_texture_cube_map_array     : enable
#extension GL_ARB_separate_shader_objects    : enable
#extension GL_ARB_shading_language_420pack   : enable
#extension GL_ARB_shading_language_packing   : enable
#extension GL_ARB_explicit_uniform_location  : enable
#extension GL_ARB_fragment_coord_conventions : enable
layout(origin_upper_left) in vec4 gl_FragCoord;

layout(location = 0) uniform vec4 g_time;

layout(binding = 1) uniform sampler2DArray s_color;

layout(location = 0) in vec2 g_uv;

layout(location = 0) out vec4 g_color;

vec3 ScreenSpaceDither(vec2 screen_pos) {
  vec3 dither = dot(vec2(171.0, 231.0), screen_pos.xy + g_time.x).xxx;
  dither.rgb = fract(dither.rgb / vec3(103.0, 71.0, 97.0)) - vec3(0.5, 0.5, 0.5);
  return (dither.rgb / 255.0) * 0.375;
}

void main() {
  g_color = texture(s_color, vec3(g_uv, 0));
  g_color.xyz += ScreenSpaceDither(gl_FragCoord.xy) * 10;
}
