/*
 * For Windows (MSVC, clang-cl and MinGW) only.
 * (move to 'bin/functions.c'?)
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

#ifndef _MSC_VER
#include <unistd.h>
#endif

#include "geoipupdate.h"

static int asprintf (char **str_p, const char *format, ...)
{
  va_list args;
  int     rc;

  va_start(args, format);
  rc = vasprintf(str_p, format, args);
  va_end (args);
  exit_if(rc == -1, "Error calling vasprintf: %s\n", strerror(errno));
  return (rc);
}

/*
 * Called by 'xasprintf()'
 */
int vasprintf (char **str_p, const char *format, va_list args)
{
  char buf [2000];

  if (!str_p)
  {
    errno = EINVAL;
    return -1;
  }

  _vsnprintf (buf, sizeof(buf), format, args);
  *str_p = strdup (buf);
  if (*str_p == NULL)
  {
    errno = ENOMEM;
    return -1;
  }
  return strlen (buf);
}

char *strtok_r (char *ptr, const char *sep, char **end)
{
  (void) end;
  return strtok (ptr, sep);
}

#if defined(_MSC_VER)
/*
 * Parse command-line options.
 *
 * (emx+gcc) -- Copyright (c) 1990-1993 by Eberhard Mattes
 * Adapted for Watt-32 TCP/IP by G. Vanem Nov-96
 */

enum _optmode {
      GETOPT_UNIX,        /* options at start of argument list (default)   */
      GETOPT_ANY,         /* move non-options to the end                   */
      GETOPT_KEEP,        /* return options in order                       */
    };

char *optarg          = NULL;
int   optopt          = 0;
int   optind          = 0;        /* Default: first call */
int   opterr          = 1;        /* Default: error messages enabled */
char *optswchar       = "-/";     /* '-' or '/' starts options */
enum  _optmode optmode = GETOPT_UNIX;

static char *next_opt;        /* Next character in cluster of options */
static char *empty = "";      /* Empty string */

static BOOL done;
static char sw_char;

static char **options;        /* List of entries which are options */
static char **non_options;    /* List of entries which are not options */
static int    options_count;
static int    non_options_count;

#define PUT(dst) do {                                    \
                   if (optmode == GETOPT_ANY)            \
                      dst[dst##_count++] = argv[optind]; \
                  } while (0)

#undef ERROR

#define ERROR(str,fmt,ch) do {                  \
                           printf (str);        \
                           if (ch)              \
                              printf (fmt, ch); \
                           puts ("");           \
                         } while (0)

int getopt (int argc, char *const *_argv, const char *opt_str)
{
  char  c;
  char *q;
  int   i, j;
  char **argv = (char **) _argv;

  if (optind == 0)
  {
    optind   = 1;
    done     = FALSE;
    next_opt = empty;
    if (optmode == GETOPT_ANY)
    {
      options     = malloc (argc * sizeof(char*));
      non_options = malloc (argc * sizeof(char*));
      if (!options || !non_options)
      {
        ERROR ("out of memory (getopt)", NULL, 0);
        exit (255);
      }
      options_count     = 0;
      non_options_count = 0;
    }
  }
  if (done)
     return (EOF);

restart:
  optarg = NULL;
  if (*next_opt == 0)
  {
    if (optind >= argc)
    {
      if (optmode == GETOPT_ANY)
      {
        j = 1;
        for (i = 0; i < options_count; ++i)
            argv[j++] = options[i];
        for (i = 0; i < non_options_count; ++i)
            argv[j++] = non_options[i];
        optind = options_count+1;
        free (options);
        free (non_options);
      }
      done = TRUE;
      return (EOF);
    }
    else if (!strchr (optswchar, argv[optind][0]) || argv[optind][1] == 0)
    {
      if (optmode == GETOPT_UNIX)
      {
        done = TRUE;
        return (EOF);
      }
      PUT (non_options);
      optarg = argv[optind++];
      if (optmode == GETOPT_ANY)
         goto restart;
      /* optmode==GETOPT_KEEP */
      return (0);
    }
    else if (argv[optind][0] == argv[optind][1] && argv[optind][2] == 0)
    {
      if (optmode == GETOPT_ANY)
      {
        j = 1;
        for (i = 0; i < options_count; ++i)
            argv[j++] = options[i];
        argv[j++] = argv[optind];
        for (i = 0; i < non_options_count; ++i)
            argv[j++] = non_options[i];
        for (i = optind+1; i < argc; ++i)
            argv[j++] = argv[i];
        optind = options_count + 2;
        free (options);
        free (non_options);
      }
      ++optind;
      done = TRUE;
      return (EOF);
    }
    else
    {
      PUT (options);
      sw_char  = argv[optind][0];
      next_opt = argv[optind] + 1;
    }
  }
  c = *next_opt++;
  if (*next_opt == 0)  /* Move to next argument if end of argument reached */
     optind++;
  if (c == ':' || (q = strchr (opt_str, c)) == NULL)
  {
    if (opterr)
    {
      if (c < ' ' || c >= 127)
           ERROR ("Invalid option", "; character code=0x%.2x", c);
      else ERROR ("Invalid option", " -%c", c);
    }
    optopt = '?';
    return ('?');
  }
  if (q[1] == ':')
  {
    if (*next_opt != 0)         /* Argument given */
    {
      optarg = next_opt;
      next_opt = empty;
      ++optind;
    }
    else if (q[2] == ':')
      optarg = NULL;            /* Optional argument missing */
    else if (optind >= argc)
    {                           /* Required argument missing */
      if (opterr)
         ERROR ("No argument for option", " `-%c'", c);
      c = '?';
    }
    else
    {
      PUT (options);
      optarg = argv[optind++];
    }
  }
  optopt = c;
  return (c);
}
#endif  /* _MSC_VER */
