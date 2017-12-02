#pragma once

#ifndef TINYPROFILER_NO_HEADER_IMPORT
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#endif // TINYPROFILER_NO_HEADER_IMPORT

#ifndef USE_TINYPROFILER

static inline void profAlloc(size_t sample_count_per_thread) {}
static inline void profPrintAndFree() {}
static inline void profB(char * name) {}
static inline void profE(char * name) {}
static inline void profBmt(int tid, char * name) {}
static inline void profEmt(int tid, char * name) {}

#else // USE_TINYPROFILER

#ifndef TINYPROFILER_MAX_NUM_OF_THREADS
#define TINYPROFILER_MAX_NUM_OF_THREADS 1
#endif

#ifndef TINYPROFILER_MAX_NAME_STRING_LENGTH
#define TINYPROFILER_MAX_NAME_STRING_LENGTH 100
#endif

#ifndef TINYPROFILER_MAX_JSON_LINE_LENGTH
#define TINYPROFILER_MAX_JSON_LINE_LENGTH 10000
#endif

#ifndef TINYPROFILER_OUTPUT_STRING
#ifdef _WIN32
#define TINYPROFILER_OUTPUT_STRING(x) OutputDebugStringA(x)
#else
#define TINYPROFILER_OUTPUT_STRING(x) fprintf(stderr, "%s", x)
#endif
#endif

#ifndef TINYPROFILER_CALLOC
#define TINYPROFILER_CALLOC calloc
#endif

#ifndef TINYPROFILER_FREE
#define TINYPROFILER_FREE free
#endif

#ifndef TINYPROFILER_SNPRINTF
#define TINYPROFILER_SNPRINTF snprintf
#endif

#ifndef TINYPROFILER_GETTIMEOFDAY
#define TINYPROFILER_GETTIMEOFDAY gettimeofday
#endif

#ifndef TINYPROFILER_TIME_TO_TS
#ifdef _WIN32
#define TINYPROFILER_TIME_TO_TS(x) (unsigned long)(((double)(x) / (double)_tinyprofiler_perf_freq) * 1000000.0)
#else
#define TINYPROFILER_TIME_TO_TS(x) ((x) - _tinyprofiler_prof_time_from * 1000000UL)
#endif
#endif

struct _tinyprofiler_sample_t {
  unsigned long ts;
  char tid;
  char name[TINYPROFILER_MAX_NAME_STRING_LENGTH];
};

struct _tinyprofiler_samples_mt_t {
  struct _tinyprofiler_sample_t * sample;
  int i;
  size_t sample_count;
};

struct _tinyprofiler_samples_mt_t _g_prof_data[TINYPROFILER_MAX_NUM_OF_THREADS] = {0};

#ifdef _WIN32
unsigned long long _tinyprofiler_perf_freq = 0;
#else
unsigned long _tinyprofiler_prof_time_from = 0;
#endif

#ifdef _WIN32
static inline unsigned long long _prof_time() {
  unsigned long long counter;
  QueryPerformanceCounter((LARGE_INTEGER *)&counter);
  return counter;
}
#else
static inline unsigned long _prof_time() {
  struct timeval tv;
  TINYPROFILER_GETTIMEOFDAY(&tv, NULL);
  return tv.tv_sec * 1000000UL + tv.tv_usec;
}
#endif

static inline void _profB(char tid, unsigned long ts, size_t name_size, char * name_ascii) {
  int i = _g_prof_data[tid].i;
  _g_prof_data[tid].i += 1;
  struct _tinyprofiler_sample_t * s = &_g_prof_data[tid].sample[i];
  s->ts = ts;
  s->tid = tid + 1;
  memcpy(s->name, name_ascii, name_size);
}

static inline void _profE(char tid, unsigned long ts, size_t name_size, char * name_ascii) {
  int i = _g_prof_data[tid].i;
  _g_prof_data[tid].i += 1;
  struct _tinyprofiler_sample_t * s = &_g_prof_data[tid].sample[i];
  s->ts = ts;
  s->tid = -(tid + 1);
  memcpy(s->name, name_ascii, name_size);
}

static inline void profAlloc(size_t sample_count_per_thread) {
#ifdef _WIN32
  BOOL query_perf_freq_fail = QueryPerformanceFrequency((LARGE_INTEGER *)&_tinyprofiler_perf_freq);
  assert(query_perf_freq_fail != 0);
#else
  struct timeval tv;
  TINYPROFILER_GETTIMEOFDAY(&tv, NULL);
  _tinyprofiler_prof_time_from = tv.tv_sec;
#endif
  for (int t = 0; t < TINYPROFILER_MAX_NUM_OF_THREADS; t += 1) {
    _g_prof_data[t].sample_count = sample_count_per_thread;
    _g_prof_data[t].sample = (struct _tinyprofiler_sample_t *)TINYPROFILER_CALLOC(sample_count_per_thread, sizeof(struct _tinyprofiler_sample_t));
  }
}

static inline void profPrintAndFree() {
  unsigned long self_t_begin = (unsigned long)_prof_time();
  size_t line_bytes = TINYPROFILER_MAX_JSON_LINE_LENGTH * sizeof(char);
  char * line = (char *)TINYPROFILER_CALLOC(TINYPROFILER_MAX_JSON_LINE_LENGTH, sizeof(char));
  TINYPROFILER_SNPRINTF(line, line_bytes, "{\"traceEvents\":[{}\n"); TINYPROFILER_OUTPUT_STRING(line);
  for (int t = 0; t < TINYPROFILER_MAX_NUM_OF_THREADS; t += 1) {
    for (size_t i = 0; i < _g_prof_data[t].sample_count; i += 1) {
      char tid = _g_prof_data[t].sample[i].tid;
      if (tid == 0) break;
      char ph  = tid > 0 ? 'B' : 'E';
      tid = tid > 0 ? tid : tid * -1;
      TINYPROFILER_SNPRINTF(line, line_bytes, ",{\"ph\":\"%c\",\"ts\":%lu,\"pid\":0,\"tid\":%d,\"name\":\"%s\"}\n", ph, TINYPROFILER_TIME_TO_TS(_g_prof_data[t].sample[i].ts), tid - 1, _g_prof_data[t].sample[i].name);
      TINYPROFILER_OUTPUT_STRING(line);
    }
  }
  TINYPROFILER_SNPRINTF(line, line_bytes, ",{\"ph\":\"B\",\"ts\":%lu,\"pid\":0,\"tid\":0,\"name\":\"%s\"}\n", TINYPROFILER_TIME_TO_TS((unsigned long)self_t_begin), __func__); TINYPROFILER_OUTPUT_STRING(line);
  TINYPROFILER_SNPRINTF(line, line_bytes, ",{\"ph\":\"E\",\"ts\":%lu,\"pid\":0,\"tid\":0,\"name\":\"%s\"}\n", TINYPROFILER_TIME_TO_TS((unsigned long)_prof_time()), __func__); TINYPROFILER_OUTPUT_STRING(line);
  TINYPROFILER_SNPRINTF(line, line_bytes, "]}\n"); TINYPROFILER_OUTPUT_STRING(line);
  for (int t = 0; t < TINYPROFILER_MAX_NUM_OF_THREADS; t += 1)
    TINYPROFILER_FREE(_g_prof_data[t].sample);
  TINYPROFILER_FREE(line);
}

#ifndef profB
#define profB(name) _profB(0, (unsigned long)_prof_time(), sizeof(name), name)
#endif

#ifndef profE
#define profE(name) _profE(0, (unsigned long)_prof_time(), sizeof(name), name)
#endif

#ifndef profBmt
#define profBmt(tid, name) _profB(tid, (unsigned long)_prof_time(), sizeof(name), name)
#endif

#ifndef profEmt
#define profEmt(tid, name) _profE(tid, (unsigned long)_prof_time(), sizeof(name), name)
#endif

#endif // USE_TINYPROFILER
