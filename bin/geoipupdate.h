
#ifndef GEOIPUPDATE_H
#define GEOIPUPDATE_H (1)

#include <curl/curl.h>
#include <stdlib.h>

typedef struct edition_s {
    char *edition_id;
    struct edition_s *next;
} edition_s;

typedef struct {
    int account_id;
    char license_key[13];
    edition_s *first;
} license_s;

typedef struct {
    license_s license;

    // user might change these before geoipupdate_s_init
    int skip_peer_verification;
    int skip_hostname_verification;
    int preserve_file_times;
    int do_not_overwrite_database_directory;
    char *license_file;
    char *database_dir;
    char *host;
    char *proto;
    char *proxy;               // 1.2.3.4, 1.2.3.4:1234
    char *proxy_user_password; // user:pwd
    char *lock_file;           // Path to a global runtime lock file.
    int verbose;
    CURL *curl;

} geoipupdate_s;

geoipupdate_s *geoipupdate_s_new(void);
void geoipupdate_s_delete(geoipupdate_s *gu);
void edition_delete_all(geoipupdate_s *gu);

int edition_count(geoipupdate_s *gu);
void edition_insert_once(geoipupdate_s *gu, const char *edition_id);
edition_s *edition_new(const char *edition_id);
void edition_delete(edition_s *p);

void exit_unless(int expr, const char *fmt, ...);
void say_if(int expr, const char *fmt, ...);
void *xcalloc(size_t, size_t);

#define NO_ACCOUNT_ID (-1)
#define GEOIP_USERAGENT "geoipupdate/" VERSION

#define exit_if(expr, ...) exit_unless(!(expr), ##__VA_ARGS__)

void xasprintf(char **, const char *, ...);

#ifdef _WIN32
  #include <stdarg.h>
  #include <io.h>

  #ifndef __MINGW32__
    extern char *optarg;
    extern int   opterr;
    extern int   optopt;
    extern int   getopt (int argc, char *const *argv, const char *opt_string);
  #endif

  extern int   vasprintf (char **str_p, const char *format, va_list args);
  extern char *strtok_r (char *ptr, const char *sep, char **end);

  #ifndef S_ISREG
  #define S_ISREG(m)  (((m) & _S_IFMT) == _S_IFREG)
  #endif

  #ifndef S_ISDIR
  #define S_ISDIR(m)  (((m) & _S_IFMT) == _S_IFDIR)
  #endif

  #ifndef W_OK
  #define W_OK 2
  #endif
#endif

#endif
