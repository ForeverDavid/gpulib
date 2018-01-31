#version 330 core
#extension GL_ARB_gpu_shader5                : enable
#extension GL_ARB_compute_shader             : enable
#extension GL_ARB_shader_precision           : enable
#extension GL_ARB_enhanced_layouts           : enable
#extension GL_ARB_texture_cube_map_array     : enable
#extension GL_ARB_shader_image_load_store    : enable
#extension GL_ARB_separate_shader_objects    : enable
#extension GL_ARB_shading_language_420pack   : enable
#extension GL_ARB_shading_language_packing   : enable
#extension GL_ARB_explicit_uniform_location  : enable
#extension GL_ARB_fragment_coord_conventions : enable
out gl_PerVertex { vec4 gl_Position; };

layout(location = 0) uniform vec4 g_cam_rot;
layout(location = 1) uniform vec4 g_fov;

layout(location = 0) out vec3 g_pos;

const vec3 g_cube[] = vec3[](
  vec3(-1, 1,-1), vec3(-1,-1,-1), vec3( 1,-1,-1),
  vec3( 1,-1,-1), vec3( 1, 1,-1), vec3(-1, 1,-1),
  vec3(-1,-1, 1), vec3(-1,-1,-1), vec3(-1, 1,-1),
  vec3(-1, 1,-1), vec3(-1, 1, 1), vec3(-1,-1, 1),
  vec3( 1,-1,-1), vec3( 1,-1, 1), vec3( 1, 1, 1),
  vec3( 1, 1, 1), vec3( 1, 1,-1), vec3( 1,-1,-1),
  vec3(-1,-1, 1), vec3(-1, 1, 1), vec3( 1, 1, 1),
  vec3( 1, 1, 1), vec3( 1,-1, 1), vec3(-1,-1, 1),
  vec3(-1, 1,-1), vec3( 1, 1,-1), vec3( 1, 1, 1),
  vec3( 1, 1, 1), vec3(-1, 1, 1), vec3(-1, 1,-1),
  vec3(-1,-1,-1), vec3(-1,-1, 1), vec3( 1,-1,-1),
  vec3( 1,-1,-1), vec3(-1,-1, 1), vec3( 1,-1, 1)
);

vec4 qinv(vec4 v) {
  return vec4(-v.xyz, v.w);
}

vec3 qrot(vec3 p, vec4 v) {
  return fma(cross(v.xyz, fma(p, vec3(v.w), cross(v.xyz, p))), vec3(2), p);
}

void main() {
  g_pos = g_cube[gl_VertexID];

  vec3 mv = g_pos;
  mv = qrot(mv, qinv(g_cam_rot));

  mv.x *= g_fov.x;
  mv.y *= g_fov.y;

  gl_Position = vec4(mv, mv.z + 0.1);
}
