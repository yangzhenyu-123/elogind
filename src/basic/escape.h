/* SPDX-License-Identifier: LGPL-2.1+ */
#pragma once

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <uchar.h>

#include "string-util.h"
#include "missing_type.h"

/* What characters are special in the shell? */
/* must be escaped outside and inside double-quotes */
#define SHELL_NEED_ESCAPE "\"\\`$"

/* Those that can be escaped or double-quoted.
 *
 * Stricly speaking, ! does not need to be escaped, except in interactive
 * mode, but let's be extra nice to the user and quote ! in case this
 * output is ever used in interactive mode. */
#define SHELL_NEED_QUOTES SHELL_NEED_ESCAPE GLOB_CHARS "'()<>|&;!"

/* Note that we assume control characters would need to be escaped too in
 * addition to the "special" characters listed here, if they appear in the
 * string. Current users disallow control characters. Also '"' shall not
 * be escaped.
 */
#define SHELL_NEED_ESCAPE_POSIX "\\\'"

typedef enum UnescapeFlags {
        UNESCAPE_RELAX      = 1 << 0,
        UNESCAPE_ACCEPT_NUL = 1 << 1,
} UnescapeFlags;

typedef enum EscapeStyle {
        ESCAPE_BACKSLASH = 1,
        ESCAPE_POSIX     = 2,
} EscapeStyle;

char *cescape(const char *s);
char *cescape_length(const char *s, size_t n);
int cescape_char(char c, char *buf);

int cunescape_length_with_prefix(const char *s, size_t length, const char *prefix, UnescapeFlags flags, char **ret);
static inline int cunescape_length(const char *s, size_t length, UnescapeFlags flags, char **ret) {
        return cunescape_length_with_prefix(s, length, NULL, flags, ret);
}
static inline int cunescape(const char *s, UnescapeFlags flags, char **ret) {
        return cunescape_length(s, strlen(s), flags, ret);
}
int cunescape_one(const char *p, size_t length, char32_t *ret, bool *eight_bit, bool accept_nul);

char *xescape_full(const char *s, const char *bad, size_t console_width, bool eight_bits);
static inline char *xescape(const char *s, const char *bad) {
        return xescape_full(s, bad, SIZE_MAX, false);
}
#if 0 /// UNNEEDED by elogind
char *octescape(const char *s, size_t len);
#endif // 0
char *escape_non_printable_full(const char *str, size_t console_width, bool eight_bit);

#if 0 /// UNNEEDED by elogind
char *shell_escape(const char *s, const char *bad);
#endif // 0
char* shell_maybe_quote(const char *s, EscapeStyle style);
