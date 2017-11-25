#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/mman.h> // mmap, munmap
#include <fcntl.h>    // open
#include <unistd.h>   // close
#endif
#include <assert.h>

enum {
  e_draw_Cylinder,
  e_draw_Suzanne,
  e_draw_Torus,
  e_draw_count
};

static inline void MeshUploadIBVB(
    char      *  in_path_to_ib_binary,
    char      *  in_path_to_vb_binary,
    unsigned     in_di_buf_flags,
    unsigned     in_ib_buf_flags,
    unsigned     in_vb_buf_flags,
    ptrdiff_t *  out_ib_count,
    ptrdiff_t *  out_vb_count,
    ptrdiff_t *  out_ib_bytes,
    ptrdiff_t *  out_vb_bytes,
    void      ** out_ib_fh,
    void      ** out_vb_fh,
    void      ** out_ib_fm,
    void      ** out_vb_fm,
    void      ** out_ib_map_ptr,
    void      ** out_vb_map_ptr,
    unsigned  *  out_di_buf,
    unsigned  *  out_ib_buf,
    unsigned  *  out_vb_buf,
    unsigned  *  out_vb_tex,
    unsigned  *  out_draw_commands_array_of_size_e_draw_count_times_5)
{
  *out_ib_count = 6732;
  *out_vb_count = 1342;
  *out_ib_bytes = 6732 * sizeof(unsigned);
  *out_vb_bytes = 1342 * 3 * sizeof(float);
  {
    // 0: Count
    // 1: Instance count
    // 2: First
    // 3: Base vertex
    // 4: Instance first
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_Cylinder] = 372;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_Cylinder] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_Cylinder] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_Cylinder] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_Cylinder] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_Suzanne] = 2904;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_Suzanne] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_Suzanne] = 372;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_Suzanne] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_Suzanne] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_Torus] = 3456;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_Torus] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_Torus] = 3276;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_Torus] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_Torus] = 0;
  }
  {
    glGenBuffers(1, out_di_buf);
    glBindBuffer(0x8F3F, *out_di_buf); // GL_DRAW_INDIRECT_BUFFER
    glBufferStorage(0x8F3F, e_draw_count * 5 * sizeof(unsigned), out_draw_commands_array_of_size_e_draw_count_times_5, in_di_buf_flags);
    glBindBuffer(0x8F3F, 0);
  }
  {
#ifdef _WIN32
    *out_ib_fh = CreateFileA(in_path_to_ib_binary, FILE_READ_DATA, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    assert(*out_ib_fh != INVALID_HANDLE_VALUE);
    *out_ib_fm = CreateFileMappingFromApp(*out_ib_fh, NULL, PAGE_READONLY, *out_ib_bytes, NULL);
    assert(*out_ib_fm != INVALID_HANDLE_VALUE);
    *out_ib_map_ptr = MapViewOfFileFromApp(*out_ib_fm, FILE_MAP_READ, 0, 0);
    assert(*out_ib_map_ptr != NULL);
#else
    int fh = open(in_path_to_ib_binary, O_RDONLY);
    assert(fh != -1);
    *out_ib_fh = (void *)(ptrdiff_t)fh;
    *out_ib_fm = NULL;
    *out_ib_map_ptr = mmap(NULL, *out_ib_bytes, PROT_READ, MAP_PRIVATE, fh, 0);
    assert(*out_ib_map_ptr != MAP_FAILED);
#endif
    glGenBuffers(1, out_ib_buf);
    glBindBuffer(0x8893, *out_ib_buf); // GL_ELEMENT_ARRAY_BUFFER
    glBufferStorage(0x8893, *out_ib_bytes, *out_ib_map_ptr, in_ib_buf_flags);
    glBindBuffer(0x8893, 0);
  }
  {
#ifdef _WIN32
    *out_vb_fh = CreateFileA(in_path_to_vb_binary, FILE_READ_DATA, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    assert(*out_vb_fh != INVALID_HANDLE_VALUE);
    *out_vb_fm = CreateFileMappingFromApp(*out_vb_fh, NULL, PAGE_READONLY, *out_vb_bytes, NULL);
    assert(*out_vb_fm != INVALID_HANDLE_VALUE);
    *out_vb_map_ptr = MapViewOfFileFromApp(*out_vb_fm, FILE_MAP_READ, 0, 0);
    assert(*out_vb_map_ptr != NULL);
#else
    int fh = open(in_path_to_vb_binary, O_RDONLY);
    assert(fh != -1);
    *out_vb_fh = (void *)(ptrdiff_t)fh;
    *out_vb_fm = NULL;
    *out_vb_map_ptr = mmap(NULL, *out_vb_bytes, PROT_READ, MAP_PRIVATE, fh, 0);
    assert(*out_vb_map_ptr != MAP_FAILED);
#endif
    glCreateBuffers(1, out_vb_buf);
    glNamedBufferStorage(*out_vb_buf, *out_vb_bytes, *out_vb_map_ptr, in_vb_buf_flags);
    glCreateTextures(0x8C2A, 1, out_vb_tex); // GL_TEXTURE_BUFFER
    glTextureBufferRange(*out_vb_tex, 0x8815, *out_vb_buf, 0, *out_vb_bytes); // GL_RGB32F
  }
}

static inline unsigned SimpleMeshUploadIBVB(
    char     * in_path_to_ib_binary,
    char     * in_path_to_vb_binary,
    unsigned   in_di_buf_flags,
    unsigned   in_ib_buf_flags,
    unsigned   in_vb_buf_flags,
    unsigned * out_di_buf,
    unsigned * out_ib_buf,
    unsigned * out_vb_buf,
    unsigned * out_draw_commands_array_of_size_e_draw_count_times_5)
{
  ptrdiff_t ib_count = 0;
  ptrdiff_t vb_count = 0;
  ptrdiff_t ib_bytes = 0;
  ptrdiff_t vb_bytes = 0;
  void * ib_fh = NULL;
  void * vb_fh = NULL;
  void * ib_fm = NULL;
  void * vb_fm = NULL;
  void * ib_map_ptr = NULL;
  void * vb_map_ptr = NULL;
  unsigned di_buf = 0;
  unsigned ib_buf = 0;
  unsigned vb_buf = 0;
  unsigned vb_tex = 0;
  MeshUploadIBVB(
    in_path_to_ib_binary,
    in_path_to_vb_binary,
    in_di_buf_flags,
    in_ib_buf_flags,
    in_vb_buf_flags,
    &ib_count,
    &vb_count,
    &ib_bytes,
    &vb_bytes,
    &ib_fh,
    &vb_fh,
    &ib_fm,
    &vb_fm,
    &ib_map_ptr,
    &vb_map_ptr,
    &di_buf,
    &ib_buf,
    &vb_buf,
    &vb_tex,
    out_draw_commands_array_of_size_e_draw_count_times_5);
#ifdef _WIN32
  UnmapViewOfFile(ib_map_ptr);
  UnmapViewOfFile(vb_map_ptr);
  CloseHandle(ib_fm);
  CloseHandle(vb_fm);
  CloseHandle(ib_fh);
  CloseHandle(vb_fh);
#else
  munmap(ib_map_ptr, ib_bytes);
  munmap(vb_map_ptr, vb_bytes);
  close((int)(ptrdiff_t)ib_fh);
  close((int)(ptrdiff_t)vb_fh);
#endif
  if (out_di_buf != NULL)
     *out_di_buf = di_buf;
  *out_ib_buf = ib_buf;
  if (out_vb_buf != NULL)
     *out_vb_buf = vb_buf;
  return vb_tex;
}

static inline void MeshDraw(
    unsigned in_program_pipeline_object_id,
    int in_textures_first,
    int in_textures_count,
    unsigned * in_textures,
    unsigned in_index_buffer_id,
    unsigned in_draw_command_indirect_buffer_id,
    unsigned in_draw_command_first,
    unsigned in_draw_command_count)
{
  glBindProgramPipeline(in_program_pipeline_object_id);
  glBindTextures(in_textures_first, in_textures_count, in_textures);
  glBindBuffer(0x8893, in_index_buffer_id); // GL_ELEMENT_ARRAY_BUFFER
  glBindBuffer(0x8F3F, in_draw_command_indirect_buffer_id); // GL_DRAW_INDIRECT_BUFFER
  glMultiDrawElementsIndirect(0x0004, 0x1405, (void *)(in_draw_command_first * 5 * sizeof(unsigned)), in_draw_command_count, 0); // GL_TRIANGLES, GL_UNSIGNED_INT
}

