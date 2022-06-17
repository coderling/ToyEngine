
#ifndef TOY_LIB_API_H
#define TOY_LIB_API_H

#ifdef AS_STATIC_LIB
#  define TOY_LIB_API
#  define NOT_TOY_LIB_API
#else
#  ifndef TOY_LIB_API
#    ifdef Common_EXPORTS
        /* We are building this library */
#      define TOY_LIB_API 
#    else
        /* We are using this library */
#      define TOY_LIB_API 
#    endif
#  endif

#  ifndef NOT_TOY_LIB_API
#    define NOT_TOY_LIB_API 
#  endif
#endif

#ifndef DEPRECATED_TOY_LIB_API
#  define DEPRECATED_TOY_LIB_API __attribute__ ((__deprecated__))
#endif

#ifndef DEPRECATED_TOY_LIB_API_EXPORT
#  define DEPRECATED_TOY_LIB_API_EXPORT TOY_LIB_API DEPRECATED_TOY_LIB_API
#endif

#ifndef DEPRECATED_TOY_LIB_API_NO_EXPORT
#  define DEPRECATED_TOY_LIB_API_NO_EXPORT NOT_TOY_LIB_API DEPRECATED_TOY_LIB_API
#endif

#if 1 /* DEFINE_NO_DEPRECATED */
#  ifndef WITHOUT_DEPRECATED
#    define WITHOUT_DEPRECATED
#  endif
#endif

#endif /* TOY_LIB_API_H */
