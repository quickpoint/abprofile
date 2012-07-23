/**
 *  @(#) ab_profile.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "ab_profile.h"

int main(int argc, char* argv[]) {
    ab_error("this is a dump error text.");

    return EXIT_SUCCESS;
}

static void time_it(char* time_str, size_t time_str_size) {
    time_t tt;
    struct tm* local_time;

    time(&tt);
    local_time = localtime(&tt);
    strftime(time_str, time_str_size, "%Y-%m-%d %H:%M:%S", local_time);

    return;
}
  
int ab_profile_inner(int flag,
                     const char* file,
                     const long line,
                     const char* fmt,
                     ...) {
    va_list args;

    char time_str[10+1+8+1]; /* yyyy-MM-dd HH:mm:ss */
    FILE* fp = NULL;

    static char* debug_log = NULL;
    static char* error_log = NULL;
    static size_t init_flag = 0;
    
    if(!init_flag) {
        init_flag = 1;
        debug_log = getenv("PROFILE_DEBUG");
        if(NULL == debug_log) debug_log = "debug.log";
        error_log = getenv("PROFILE_ERROR");
        if(NULL == error_log) error_log = "error.log";
    }

    switch(flag) {
        case FLAG_DEBUG:
            fp = fopen(debug_log, "a");
            if(!fp) return -1;
            time_it(time_str, sizeof(time_str));
            fprintf(fp, "%s DEBUG (%d:%s:%ld) ", time_str, getpid(), file, line);
            break;
        case FLAG_WARN:
            fp = fopen(error_log, "a");
            if(!fp) return -1;
            time_it(time_str, sizeof(time_str));
            fprintf(fp, "%s WARN (%d:%s:%ld) ", time_str, getpid(), file, line);
            break;
        case FLAG_ERROR:
            fp = fopen(error_log, "a");
            if(!fp) return -1;
            time_it(time_str, sizeof(time_str));
            fprintf(fp, "%s ERROR (%d:%s:%ld) ", time_str, getpid(), file, line);
            break;
        default:

            break;
    }

    va_start(args, fmt);
    vfprintf(fp, fmt, args);
    va_end(args);

    fprintf(fp, "\n");
    fclose(fp);

    return 0;
}
