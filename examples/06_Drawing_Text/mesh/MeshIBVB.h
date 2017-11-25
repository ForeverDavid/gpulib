#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/mman.h> // mmap, munmap
#include <fcntl.h>    // open
#include <unistd.h>   // close
#endif
#include <assert.h>

enum {
  e_draw_exclamation_mark,
  e_draw_double_quote,
  e_draw_hash,
  e_draw_dollar,
  e_draw_percent,
  e_draw_ampersand,
  e_draw_single_quote,
  e_draw_round_bracket_open,
  e_draw_round_bracket_close,
  e_draw_multiply,
  e_draw_plus,
  e_draw_comma,
  e_draw_minus,
  e_draw_dot,
  e_draw_slash,
  e_draw_0,
  e_draw_1,
  e_draw_2,
  e_draw_3,
  e_draw_4,
  e_draw_5,
  e_draw_6,
  e_draw_7,
  e_draw_8,
  e_draw_9,
  e_draw_colon,
  e_draw_semicolon,
  e_draw_less_than,
  e_draw_equal,
  e_draw_more_than,
  e_draw_question_mark,
  e_draw_at,
  e_draw_A,
  e_draw_B,
  e_draw_C,
  e_draw_D,
  e_draw_E,
  e_draw_F,
  e_draw_G,
  e_draw_H,
  e_draw_I,
  e_draw_J,
  e_draw_K,
  e_draw_L,
  e_draw_M,
  e_draw_N,
  e_draw_O,
  e_draw_P,
  e_draw_Q,
  e_draw_R,
  e_draw_S,
  e_draw_T,
  e_draw_U,
  e_draw_V,
  e_draw_W,
  e_draw_X,
  e_draw_Y,
  e_draw_Z,
  e_draw_square_bracket_open,
  e_draw_backslash,
  e_draw_square_bracket_close,
  e_draw_caret,
  e_draw_underscore,
  e_draw_backtick,
  e_draw_a,
  e_draw_b,
  e_draw_c,
  e_draw_d,
  e_draw_e,
  e_draw_f,
  e_draw_g,
  e_draw_h,
  e_draw_i,
  e_draw_j,
  e_draw_k,
  e_draw_l,
  e_draw_m,
  e_draw_n,
  e_draw_o,
  e_draw_p,
  e_draw_q,
  e_draw_r,
  e_draw_s,
  e_draw_t,
  e_draw_u,
  e_draw_v,
  e_draw_w,
  e_draw_x,
  e_draw_y,
  e_draw_z,
  e_draw_curly_bracket_open,
  e_draw_vertical_bar,
  e_draw_curly_bracket_close,
  e_draw_tilde,
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
  *out_ib_count = 12708;
  *out_vb_count = 4382;
  *out_ib_bytes = 12708 * sizeof(unsigned);
  *out_vb_bytes = 4382 * 3 * sizeof(float);
  {
    // 0: Count
    // 1: Instance count
    // 2: First
    // 3: Base vertex
    // 4: Instance first
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_exclamation_mark] = 72;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_exclamation_mark] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_exclamation_mark] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_exclamation_mark] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_exclamation_mark] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_double_quote] = 12;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_double_quote] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_double_quote] = 72;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_double_quote] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_double_quote] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_hash] = 96;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_hash] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_hash] = 84;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_hash] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_hash] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_dollar] = 309;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_dollar] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_dollar] = 180;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_dollar] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_dollar] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_percent] = 435;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_percent] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_percent] = 489;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_percent] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_percent] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_ampersand] = 444;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_ampersand] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_ampersand] = 924;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_ampersand] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_ampersand] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_single_quote] = 6;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_single_quote] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_single_quote] = 1368;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_single_quote] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_single_quote] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_round_bracket_open] = 144;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_round_bracket_open] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_round_bracket_open] = 1374;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_round_bracket_open] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_round_bracket_open] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_round_bracket_close] = 144;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_round_bracket_close] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_round_bracket_close] = 1518;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_round_bracket_close] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_round_bracket_close] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_multiply] = 39;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_multiply] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_multiply] = 1662;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_multiply] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_multiply] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_plus] = 30;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_plus] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_plus] = 1701;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_plus] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_plus] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_comma] = 36;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_comma] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_comma] = 1731;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_comma] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_comma] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_minus] = 6;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_minus] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_minus] = 1767;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_minus] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_minus] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_dot] = 69;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_dot] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_dot] = 1773;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_dot] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_dot] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_slash] = 6;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_slash] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_slash] = 1842;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_slash] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_slash] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_0] = 252;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_0] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_0] = 1848;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_0] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_0] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_1] = 42;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_1] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_1] = 2100;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_1] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_1] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_2] = 189;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_2] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_2] = 2142;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_2] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_2] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_3] = 312;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_3] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_3] = 2331;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_3] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_3] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_4] = 57;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_4] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_4] = 2643;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_4] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_4] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_5] = 186;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_5] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_5] = 2700;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_5] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_5] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_6] = 363;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_6] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_6] = 2886;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_6] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_6] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_7] = 15;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_7] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_7] = 3249;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_7] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_7] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_8] = 453;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_8] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_8] = 3264;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_8] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_8] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_9] = 363;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_9] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_9] = 3717;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_9] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_9] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_colon] = 138;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_colon] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_colon] = 4080;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_colon] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_colon] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_semicolon] = 105;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_semicolon] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_semicolon] = 4218;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_semicolon] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_semicolon] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_less_than] = 15;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_less_than] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_less_than] = 4323;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_less_than] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_less_than] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_equal] = 12;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_equal] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_equal] = 4338;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_equal] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_equal] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_more_than] = 15;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_more_than] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_more_than] = 4350;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_more_than] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_more_than] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_question_mark] = 324;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_question_mark] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_question_mark] = 4365;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_question_mark] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_question_mark] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_at] = 564;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_at] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_at] = 4689;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_at] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_at] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_A] = 51;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_A] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_A] = 5253;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_A] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_A] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_B] = 252;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_B] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_B] = 5304;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_B] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_B] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_C] = 216;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_C] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_C] = 5556;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_C] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_C] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_D] = 117;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_D] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_D] = 5772;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_D] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_D] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_E] = 30;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_E] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_E] = 5889;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_E] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_E] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_F] = 24;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_F] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_F] = 5919;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_F] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_F] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_G] = 204;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_G] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_G] = 5943;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_G] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_G] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_H] = 30;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_H] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_H] = 6147;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_H] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_H] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_I] = 30;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_I] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_I] = 6177;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_I] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_I] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_J] = 111;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_J] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_J] = 6207;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_J] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_J] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_K] = 33;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_K] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_K] = 6318;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_K] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_K] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_L] = 12;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_L] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_L] = 6351;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_L] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_L] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_M] = 57;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_M] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_M] = 6363;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_M] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_M] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_N] = 51;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_N] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_N] = 6420;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_N] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_N] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_O] = 216;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_O] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_O] = 6471;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_O] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_O] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_P] = 120;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_P] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_P] = 6687;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_P] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_P] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_Q] = 252;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_Q] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_Q] = 6807;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_Q] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_Q] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_R] = 123;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_R] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_R] = 7059;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_R] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_R] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_S] = 324;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_S] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_S] = 7182;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_S] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_S] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_T] = 18;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_T] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_T] = 7506;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_T] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_T] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_U] = 144;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_U] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_U] = 7524;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_U] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_U] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_V] = 42;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_V] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_V] = 7668;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_V] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_V] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_W] = 141;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_W] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_W] = 7710;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_W] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_W] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_X] = 30;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_X] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_X] = 7851;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_X] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_X] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_Y] = 21;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_Y] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_Y] = 7881;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_Y] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_Y] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_Z] = 24;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_Z] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_Z] = 7902;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_Z] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_Z] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_square_bracket_open] = 18;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_square_bracket_open] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_square_bracket_open] = 7926;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_square_bracket_open] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_square_bracket_open] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_backslash] = 6;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_backslash] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_backslash] = 7944;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_backslash] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_backslash] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_square_bracket_close] = 18;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_square_bracket_close] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_square_bracket_close] = 7950;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_square_bracket_close] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_square_bracket_close] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_caret] = 15;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_caret] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_caret] = 7968;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_caret] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_caret] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_underscore] = 6;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_underscore] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_underscore] = 7983;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_underscore] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_underscore] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_backtick] = 39;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_backtick] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_backtick] = 7989;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_backtick] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_backtick] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_a] = 282;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_a] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_a] = 8028;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_a] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_a] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_b] = 243;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_b] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_b] = 8310;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_b] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_b] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_c] = 180;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_c] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_c] = 8553;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_c] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_c] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_d] = 246;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_d] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_d] = 8733;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_d] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_d] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_e] = 204;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_e] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_e] = 8979;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_e] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_e] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_f] = 123;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_f] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_f] = 9183;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_f] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_f] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_g] = 513;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_g] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_g] = 9306;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_g] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_g] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_h] = 84;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_h] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_h] = 9819;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_h] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_h] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_i] = 99;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_i] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_i] = 9903;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_i] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_i] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_j] = 183;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_j] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_j] = 10002;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_j] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_j] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_k] = 39;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_k] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_k] = 10185;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_k] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_k] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_l] = 24;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_l] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_l] = 10224;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_l] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_l] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_m] = 231;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_m] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_m] = 10248;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_m] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_m] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_n] = 81;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_n] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_n] = 10479;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_n] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_n] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_o] = 216;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_o] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_o] = 10560;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_o] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_o] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_p] = 246;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_p] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_p] = 10776;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_p] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_p] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_q] = 246;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_q] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_q] = 11022;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_q] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_q] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_r] = 114;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_r] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_r] = 11268;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_r] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_r] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_s] = 324;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_s] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_s] = 11382;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_s] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_s] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_t] = 87;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_t] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_t] = 11706;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_t] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_t] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_u] = 99;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_u] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_u] = 11793;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_u] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_u] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_v] = 45;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_v] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_v] = 11892;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_v] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_v] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_w] = 96;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_w] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_w] = 11937;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_w] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_w] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_x] = 30;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_x] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_x] = 12033;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_x] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_x] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_y] = 153;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_y] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_y] = 12063;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_y] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_y] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_z] = 24;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_z] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_z] = 12216;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_z] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_z] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_curly_bracket_open] = 189;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_curly_bracket_open] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_curly_bracket_open] = 12240;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_curly_bracket_open] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_curly_bracket_open] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_vertical_bar] = 6;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_vertical_bar] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_vertical_bar] = 12429;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_vertical_bar] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_vertical_bar] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_curly_bracket_close] = 189;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_curly_bracket_close] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_curly_bracket_close] = 12435;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_curly_bracket_close] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_curly_bracket_close] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[0 + 5 * e_draw_tilde] = 84;
    out_draw_commands_array_of_size_e_draw_count_times_5[1 + 5 * e_draw_tilde] = 1;
    out_draw_commands_array_of_size_e_draw_count_times_5[2 + 5 * e_draw_tilde] = 12624;
    out_draw_commands_array_of_size_e_draw_count_times_5[3 + 5 * e_draw_tilde] = 0;
    out_draw_commands_array_of_size_e_draw_count_times_5[4 + 5 * e_draw_tilde] = 0;
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

