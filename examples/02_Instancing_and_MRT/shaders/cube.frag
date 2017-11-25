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

layout(location = 0) uniform int g_cubemap_id;

layout(binding = 0) uniform samplerCubeArray s_cubemaps;

layout(location = 0) in vec3 g_pos;

layout(location = 0) out vec4 g_color;

void main() {
  g_color = texture(s_cubemaps, vec4(g_pos, g_cubemap_id));
}
