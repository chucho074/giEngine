/**
 * @file    giPrerequisitesOmniverse.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/01/2022
 * @brief   The prerequisites for the core.
 * @bug     No known Bugs.
 */

 /**
  * @include
  */
#pragma once

#include <giPrerequisitesUtilities.h>
#include <giMath.h>


  /*****************************************************************************/
  /**
   * Library export specifics
   */
   /****************************************************************************/
#if GI_PLATFORM == GI_PLATFORM_WIN32
# if GI_COMPILER == GI_COMPILER_MSVC
#    if defined(GI_STATIC_LIB)
#     define GI_OMNIVERSE_EXPORT
#    else
#     if defined( GI_OMNIVERSE_EXPORTS )
#      define GI_OMNIVERSE_EXPORT __declspec( dllexport )
#    else
#      define GI_OMNIVERSE_EXPORT __declspec( dllimport )
#    endif
#   endif
# else      //Any other Compiler
#   if defined ( GI_STATIC_LIB )
#    define GI_OMNIVERSE_EXPORT
#   else
#     if defined ( GI_CORE_EXPORTS )
#       define GI_OMNIVERSE_EXPORT __attribute__ ((dllexport))
#     else
#       define GI_OMNIVERSE_EXPORT __attribute__ ((dllimport))
#     endif
#    endif
#  endif
#  define GI_OMNIVERSE_HIDDEN
#else //Linux/Mac settings
# define GI_OMNIVERSE_EXPORT __attribute__((visibility ("default")))
# define GI_OMNIVERSE_HIDDEN __attribute__((visibility ("hidden")))
#endif
