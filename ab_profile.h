/**
 *  @(#) ab_profile.h
 */
#ifndef _AB_PROFILE_H_
#define _AB_PROFILE_H_

#include <stdarg.h>

#define ab_assert(expr, rv) \
    if(!(expr)) {\
        ab_error(#expr" is null or 0");\
        return rv;\
    }

enum ab_profile_flag {
    FLAG_DEBUG = 0,
    FLAG_WARN  = 1,
    FLAG_ERROR = 2
};

#define ab_debug(fmt, args...) \
    ab_profile_inner(FLAG_DEBUG, __FILE__, __LINE__, fmt, ## args)

#define ab_warn(fmt, args...) \
    ab_profile_inner(FLAG_WARN, __FILE__, __LINE__, fmt, ## args)

#define ab_error(fmt, args...) \
    ab_profile_inner(FLAG_ERROR, __FILE__, __LINE__, fmt, ## args)

#define ab_profile(flag, fmt, args...) \
    ab_profile_inner(flag, __FILE__, __LINE__, fmt, ## args)

int ab_profile_inner(int flag, 
                     const char* file,
                     const long line,
                     const char* fmt, ...);

#endif /* _AB_PFOILE_H_ */

