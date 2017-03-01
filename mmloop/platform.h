#pragma once
#ifndef _MMLOOP_PLATFORM_H_
#define _MMLOOP_PLATFORM_H_

// address the operating systems
#if defined(_WIN32) || defined(WIN32)
#  undef  WIN32
#  define WIN32
#  undef  _WIN32
#  define _WIN32
#endif

#if defined(_WIN64) || defined(WIN64)
#  undef  WIN64
#  define WIN64
#  undef  _WIN64
#  define _WIN64
#endif
#if defined(WIN64) || defined(WIN32) || defined(_Windows) || defined(__MINGW32__)
#  define OS_MSWIN
#elif defined (__linux) || defined (__linux__) || defined(_MSYS)
#  define OS_LINUX
#else
#error unsupported operating system
#endif

#ifndef MMLOOP_EXPORTS
#define MMLOOP_EXPORTS
#endif

#ifdef OS_MSWIN
#  ifdef MMLOOP_EXPORTS
#    define MM_LOOP_API __declspec(dllexport)
#  else
#    define MM_LOOP_API __declspec(dllimport)
#  endif
#else
#  define MM_LOOP_API
#endif // OS

typedef unsigned int  uint;


#endif