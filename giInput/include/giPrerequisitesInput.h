/**
 * @file    giPrerequisitesInput.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    23/09/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include <giPrerequisitesCore.h>


/*****************************************************************************/
/**
 * Library export specifics
 */
/*****************************************************************************/
#if GI_PLATFORM == GI_PLATFORM_WIN32
# if GI_COMPILER == GI_COMPILER_MSVC
#    if defined(GI_STATIC_LIB)
#     define GI_INPUT_EXPORT
#    else
#     if defined( GI_CORE_EXPORTS )
#      define GI_INPUT_EXPORT __declspec( dllexport )
#    else
#      define GI_INPUT_EXPORT __declspec( dllimport )
#    endif
#   endif
# else      //Any other Compiler
#   if defined ( GI_STATIC_LIB )
#    define GI_INPUT_EXPORT
#   else
#     if defined ( GI_INPUT_EXPORTS )
#       define GI_INPUT_EXPORT __attribute__ ((dllexport))
#     else
#       define GI_INTPUT_EXPORT __attribute__ ((dllimport))
#     endif
#    endif
#  endif
#  define GI_INPUT_HIDDEN
#else //Linux/Mac settings
# define GI_INPUT_EXPORT __attribute__((visibility ("default")))
# define GI_INPUT_HIDDEN __attribute__((visibility ("hidden")))
#endif