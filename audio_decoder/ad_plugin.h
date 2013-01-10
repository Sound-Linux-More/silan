#ifndef __AD_PLUGIN_H__
#define __AD_PLUGIN_H__
#include <stdint.h>
#include "audio_decoder/ad.h"

#define dbg(A, B, ...) ad_debug_printf(__func__, A, B, ##__VA_ARGS__)

#ifndef __PRI64_PREFIX
#if (defined __X86_64__ || defined __LP64__)
# define __PRI64_PREFIX  "l"
#else
# define __PRI64_PREFIX  "ll"
#endif
#endif

#ifndef PRIu64
# define PRIu64   __PRI64_PREFIX "u"
#endif
#ifndef PRIi64
# define PRIi64   __PRI64_PREFIX "i"
#endif

extern int ad_debug_level;

void ad_debug_printf(const char* func, int level, const char* format, ...);

typedef struct {
	int     (*eval)(const char *);
	void *  (*open)(const char *, struct adinfo *);
	int     (*close)(void *);
	int     (*info)(void *, struct adinfo *);
	int64_t (*seek)(void *, int64_t);
	ssize_t (*read)(void *, float *, size_t);
} ad_plugin;

int     ad_eval_null(const char *);
void *  ad_open_null(const char *, struct adinfo *);
int     ad_close_null(void *);
int     ad_info_null(void *, struct adinfo *);
int64_t ad_seek_null(void *, int64_t);
ssize_t ad_read_null(void *, float*, size_t);

/* hardcoded backends */
const ad_plugin * adp_get_sndfile();
const ad_plugin * adp_get_ffmpeg();
#endif
