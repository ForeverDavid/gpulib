static inline void MeshUploadUV(
    char      *  in_path_to_binary,
    unsigned     in_buf_flags,
    ptrdiff_t *  out_count,
    ptrdiff_t *  out_bytes,
    void      ** out_fh,
    void      ** out_fm,
    void      ** out_map_ptr,
    unsigned  *  out_buf,
    unsigned  *  out_tex)
{
  *out_count = 29004;
  *out_bytes = 29004 * 2 * sizeof(float);
  unsigned format = 0x8230; // GL_RG32F
#ifdef _WIN32
  *out_fh = CreateFileA(in_path_to_binary, FILE_READ_DATA, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
  assert(*out_fh != INVALID_HANDLE_VALUE);
  *out_fm = CreateFileMappingFromApp(*out_fh, NULL, PAGE_READONLY, *out_bytes, NULL);
  assert(*out_fm != INVALID_HANDLE_VALUE);
  *out_map_ptr = MapViewOfFileFromApp(*out_fm, FILE_MAP_READ, 0, 0);
  assert(*out_map_ptr != NULL);
#else
  int fh = open(in_path_to_binary, O_RDONLY);
  assert(fh != -1);
  *out_fh = (void *)(ptrdiff_t)fh;
  *out_fm = NULL;
  *out_map_ptr = mmap(NULL, *out_bytes, PROT_READ, MAP_PRIVATE, fh, 0);
  assert(*out_map_ptr != MAP_FAILED);
#endif
  glCreateBuffers(1, out_buf);
  glNamedBufferStorage(*out_buf, *out_bytes, *out_map_ptr, in_buf_flags);
  glCreateTextures(0x8C2A, 1, out_tex); // GL_TEXTURE_BUFFER
  glTextureBufferRange(*out_tex, format, *out_buf, 0, *out_bytes);
}

static inline unsigned SimpleMeshUploadUV(
    char     * in_path_to_binary,
    unsigned   in_buf_flags,
    unsigned * out_buf)
{
  ptrdiff_t count = 0;
  ptrdiff_t bytes = 0;
  void * fh = NULL;
  void * fm = NULL;
  void * map_ptr = NULL;
  unsigned buf = 0;
  unsigned tex = 0;
  MeshUploadUV(in_path_to_binary, in_buf_flags, &count, &bytes, &fh, &fm, &map_ptr, &buf, &tex);
#ifdef _WIN32
  UnmapViewOfFile(map_ptr);
  CloseHandle(fm);
  CloseHandle(fh);
#else
  munmap(map_ptr, bytes);
  close((int)(ptrdiff_t)fh);
#endif
  if (out_buf != NULL)
     *out_buf = buf;
  return tex;
}

