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

layout(location = 0) uniform vec3  g_cam_pos;
layout(location = 1) uniform vec4  g_cam_rot;
layout(location = 2) uniform float g_fov_x;
layout(location = 3) uniform float g_fov_y;

layout(binding = 0) uniform samplerBuffer  s_pos;
layout(binding = 1) uniform samplerBuffer  s_instance_pos;
layout(binding = 4) uniform isamplerBuffer s_id;
layout(binding = 5) uniform samplerBuffer  s_uv;
layout(binding = 6) uniform samplerBuffer  s_normal;

layout(location = 0) out vec3 g_pos;
layout(location = 1) out vec3 g_normal;
layout(location = 2) out vec2 g_uv;
layout(location = 3) out flat int g_index;

vec4 qinv(vec4 v) {
  return vec4(-v.xyz, v.w);
}

vec3 qrot(vec3 p, vec4 v) {
  return fma(cross(v.xyz, fma(p, vec3(v.w), cross(v.xyz, p))), vec3(2), p);
}

void main() {
  g_index  = texelFetch(s_id,     gl_VertexID).x;
  g_pos    = texelFetch(s_pos,    gl_VertexID).xyz;
  g_uv     = texelFetch(s_uv,     gl_VertexID).xy;
  g_normal = texelFetch(s_normal, gl_VertexID).xyz;

  g_pos += texelFetch(s_instance_pos, (g_index * 30) + gl_InstanceID).xyz;

  vec3 mv = g_pos;
  mv -= g_cam_pos;
  mv  = qrot(mv, qinv(g_cam_rot));

  mv.x *= g_fov_x;
  mv.y *= g_fov_y;

  gl_Position = vec4(mv, mv.z + 0.1);
}
