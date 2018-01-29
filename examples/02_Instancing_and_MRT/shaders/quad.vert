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
out gl_PerVertex { vec4 gl_Position; };

layout(location = 0) out vec2 g_uv;

const vec2 g_tri[] = vec2[](
  vec2(-1,-1),
  vec2(-1, 3),
  vec2( 3,-1)
);

void main() {
  g_uv = g_tri[gl_VertexID] * 0.5 + 0.5;
  gl_Position = vec4(g_tri[gl_VertexID], 0, 1);
}
