/**
 * @file    giPlatformDefines.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    22/01/2021
 * @brief   
 * @bug     No known Bugs.
 */

#pragma once

#define GI_PLATFORM_WIN32 1                     //Windows Platform
#define GI_PLATFORM_LINUX 2                     //Linux Platform


#define GI_COMPILER_MSVC 1                      //Visual Studio Compiler
#define GI_COMPILER_GNUC 2                      //GNUC Compiler
#define GI_COMPILER_INTEL 3                     //Intel Compiler
#define GI_COMPILER_CLANG 4                     //Clang Compiler

#define GI_ARCHITECTURE_X86_32 1                //Intel x86 32 bits
#define GI_ARCHITECTURE_X86_64 2                //Intel x86 64 bits

#define GI_ENDIAN_LITTLE 1                      //Little endian
#define GI_ENDIAN_BIG 2                         //Big endian

//Define the actual endian type (little endian for Windows and Linux)
#define GI_ENDIAN GI_ENDIAN_LITTLE

#define GI_VERSION_MAJOR 0                      //Engine version mayor value
#define GI_VERSION_MINOR 1                      //Engine version minor value
#define GI_VERSION_PATCH 0                      //Engine version patch value

/****************************************************************************/
/**
 * Compiler type and version.
 */
/****************************************************************************/
#if defined(__clang__)
#define GI_COMPILER GI_COMPILER_CLANG
#define GI_COMP_VER __clang_version__
#define GI_THREADLOCAL __thread
#define GI_STDCALL __attribute__((stdcall))
#define GI_CDECL __attribute__((cdecl))
#define GI_FALLTHROUGH [[clang::fallthrough]]
#elif defined(__GNUC__) //Check after Clang, as Clang defines this too
#define GI_COMPILER GI_COMPILER_GNUC
#define GI_COMP_VER (((__GNUC__)*100) + (__GNUC_MINOR__*10) + __GNUC_PATCHLEVEL__)
#define GI_THREADLOCAL __thread
#define GI_STDCALL __attribute__((stdcall))
#define GI_CDECL __attribute__((cdecl))
#define GI_FALLTHROUGH __attribute__((fallthrough));
#elif defined(__INTEL_COMPILER__)
#define GI_COMPILER GI_COMPILER_INTEL
#define GI_COMP_VER __INTEL_COMPILER
#define GI_STDCALL __stdcall
#define GI_CDECL __cdecl
#define GI_FALLTHROUGH
/**
 * GI_THREADLOCAL define is down below because Intel compiler defines it
 * differently based on platform
 */

//Check after Clang and Intel, we could be building with either with VS
#elif defined(_MSC_VER)
#define GI_COMPILER GI_COMPILER_MSVC
#define GI_COMP_VER _MSC_VER
#define GI_THREADLOCAL __declspec(thread)
#define GI_STDCALL __stdcall
#define GI_CDECL __cdecl
#define GI_FALLTHROUGH 
#undef __PRETTY_FUNCTION__
#define __PRETTY_FUNCTION__ __FUNCSIG__
#else
//No know compiler found, send the error to the output (if any)
# pragma error "No know compiler. "
#endif

/*****************************************************************************/
/**
 * See if we can use __forceinline or if we need to use __inline instead
 */
/*****************************************************************************/
#if GI_COMPILER == GI_COMPILER_MSVC           //If we are compiling on Visual Studio
# if GI_COMP_VER >= 1200                      //If we are on Visual Studio 6 or higher
#    define FORCEINLINE __forceinline         //Set __forceinline
#    ifndef RESTRICT                          
#      define RESTRICT __restrict             //No alias hint
#    endif                                    
# endif                                       
#elif defined(__MINGW32__)                    //If we are on a Unix type system
# if !defined(FORCEINLINE)                    
#    define FORCEINLINE __inline              //Set __inline
#    ifndef RESTRICT                          
#      define RESTRICT                        //No alias hint
#    endif                                    
# endif                                       
#else                                         //Any other compiler
# define FORCEINLINE __inline                 //Set __inline
# ifndef RESTRICT                             
#   define RESTRICT __restrict                //No alias hint
# endif
#endif

/*****************************************************************************/
/**
 * Finds the current platform
 */
/*****************************************************************************/
#if defined(__WIN32__) || defined (_WIN32)     //If it's a Windows platform
# define GI_PLATFORM GI_PLATFORM_WIN32
#else                                          //Will consider it as a Linux platform
# define GI_PLATFORM GI_PLATFORM_LINUX
#endif

/*****************************************************************************/
/**
 * Finds the architecture type
 */
 /*****************************************************************************/
#if defined (__x86__64__) || defined (_M_X64)    //If this is a x64 compile
# define GI_ARCH_TYPE GI_ARCHITECTURE_X86_64
#else
# define GI_ARCH_TYPE GI_ARCHITECTURE_X86_32     //If it's a x86 compile
#endif

/*****************************************************************************/
/**
 * Memory Alignment Macros
 */
 /****************************************************************************/
#if GI_COMPILER == GI_COMPILER_MSVC         //If we are compiling on Visual Studio
# define MS_ALIGN(n) __declspec(align(n))
# ifndef GCC_PACK
#   define GCC_PACK(n)
# endif
# ifndef GCC_ALIGN
#   define GCC_ALIGN(n)
# endif
# elif (GI_COMPILER == GI_COMPILER_GNUC)
# define MS_ALIGN(n)
# define GCC_PACK(n)
# define GCC_ALIGN(n) __attribute__( (__aligned(n)) )
#else                                             //If we are on a Unix type system
# define MS_ALIGN(n)
# define GCC_PACK(n) __attribute__( (packed, aligned(n)) )
# define GCC_ALIGN(n) __attribute__( (__aligned(n)) )
#endif



/*****************************************************************************/
/**
 * For throw override 
 */
 /****************************************************************************/
#if GI_COMPILER == GI_COMPILER_MSVC ||                                        \
    GI_COMPILER == GI_COMPILER_INTEL ||                                       \
    GI_COMPILER == GI_COMPILER_GNUC
# define _NOEXCEPT noexcept
#else
# define _NOEXCEPT
#endif



/*****************************************************************************/
/**
 * Library export specifics
 */
 /****************************************************************************/
#if GI_PLATFORM == GI_PLATFORM_WIN32
# if GI_COMPILER == GI_COMPILER_MSVC
#    if defined(GI_STATIC_LIB)
#     define GI_UTILITY_EXPORT
#    else
#     if defined( GI_UTILITY_EXPORTS )
#      define GI_UTILITY_EXPORT __declspec( dllexport )
#    else
#      define GI_UTILITY_EXPORT __declspec( dllimport )
#    endif
#   endif
# else      //Any other Compiler
#   if defined ( GI_STATIC_LIB )
#    define GI_UTILITY_EXPORT
#   else
#     if defined ( GI_UTILITY_EXPORTS )
#       define GI_UTILITY_EXPORT __attribute__ ((dllexport))
#     else
#       define GI_UTILITY_EXPORT __attribute__ ((dllimport))
#     endif
#    endif
#  endif
#  define GI_UTILITY_HIDDEN
#else //Linux/Mac settings
# define GI_UTILITY_EXPORT __attribute__((visibility ("default")))
# define GI_UTILITY_HIDDEN __attribute__((visibility ("hidden")))
#endif

#if GI_PLATFORM == GI_PLATFORM_WIN32
# if GI_COMPILER == GI_COMPILER_MSVC
#    define GI_PLUGIN_EXPORT __declspec(dllexport) 
#  else
#    define GI_PLUGIN_EXPORT __attribute__ ((dllexport))
#  endif
#else //Linux/Mac settings
#  define GI_PLUGIN_EXPORT __attribute__((visibility ("default")))
#endif

/*****************************************************************************/
/**
 * Windows specific Settings
 */
 /****************************************************************************/
//Win32 compiler use _DEBUG for specifying debug builds, For MinGW, we set DEBUG
#if GI_PLATFORM == GI_PLATFORM_WIN32
#  if defined(_DEBUG) || defined(DEBUG)
#    define GI_DEBUG_MODE 1                    //Specifies that we are on a DEBUG build
#  else
#    define GI_DEBUG_MODE 0                    //We are not on a DEBUG
#  endif
#  if GI_COMPILER == GI_COMPILER_INTEL
#    define GI_THREADLOCAL __declspec(thread)  //Set the local thread for the Intel Compiler
#  endif
#endif


/*****************************************************************************/
/**
 * Linux/Apple specific Settings
 */
 /*****************************************************************************/
#if GI_PLATFORM == GI_PLATFORM_LINUX 
#  define stricmp strcasecmp

//If we are on a DEBUG build
#  if defined(_DEBUG) || defined(DEBUG)
#    define GI_DEBUG_MODE 1
#  else
#    define GI_DEBUG_MODE 0
#  endif
#  if GI_COMPILER == GI_COMPILER_INTEL
#    define GI_THREADLOCAL __thread
#  endif
#endif


/*****************************************************************************/
/**
 * Definition of Debug macros
 */
 /****************************************************************************/
#if GI_DEBUG_MODE
#  define GI_DEBUG_ONLY(x) x
#  define GI_ASSERT(x) assert(x)
#else
#  define GI_DEBUG_ONLY(x)
#  define GI_ASSERT(x)
#endif