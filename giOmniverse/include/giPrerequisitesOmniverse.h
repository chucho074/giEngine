/**
 * @file    giPrerequisitesOmniverse.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/01/2022
 * @brief   The prerequisites for the core.
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



#include <mutex>
#include <memory>
#include <condition_variable>

#include <OmniClient.h>
#include <OmniUsdLive.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/metrics.h>
#include <pxr/base/gf/matrix4f.h>
#include <pxr/base/gf/vec2f.h>
#include <pxr/usd/usdUtils/pipeline.h>
#include <pxr/usd/usdUtils/sparseValueWriter.h>
#include <pxr/usd/usdShade/material.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/primRange.h>
#include <pxr/usd/usdGeom/primvar.h>
#include <pxr/usd/usdShade/input.h>
#include <pxr/usd/usdShade/output.h>
#include <pxr/usd/usdGeom/xform.h>
#include <pxr/usd/usdShade/materialBindingAPI.h>
#include <pxr/usd/usdLux/distantLight.h>
#include <pxr/usd/usdLux/domeLight.h>
#include <pxr/usd/usdShade/shader.h>
#include <pxr/usd/usd/modelAPI.h>
#include <pxr/usd/usd/common.h>


PXR_NAMESPACE_USING_DIRECTIVE


// Globals for Omniverse Connection and base Stage
static UsdStageRefPtr gStage;

// Omniverse logging is noisy, only enable it if verbose mode (-v)
static bool gOmniverseLoggingEnabled = false;

// Global for making the logging reasonable
static std::mutex gLogMutex;


// Multiplatform array size
#define HW_ARRAY_COUNT(array) (sizeof(array) / sizeof(array[0]))

// Private tokens for building up SdfPaths. We recommend
// constructing SdfPaths via tokens, as there is a performance
// cost to constructing them directly via strings (effectively,
// a table lookup per path element). Similarly, any API which
// takes a token as input should use a predefined token
// rather than one created on the fly from a string.
TF_DEFINE_PRIVATE_TOKENS(
  _tokens,
  (box)
  (DistantLight)
  (DomeLight)
  (Looks)
  (Root)
  (Shader)
  (st)

  // These tokens will be reworked or replaced by the official MDL schema for USD.
  // https://developer.nvidia.com/usd/MDLschema
  (Material)
  ((_module, "module"))
  (name)
  (out)
  ((shaderId, "mdlMaterial"))
  (mdl)

  // Tokens used for USD Preview Surface
  (diffuseColor)
  (normal)
  (file)
  (result)
  (varname)
  (rgb)
  (RAW)
  (sRGB)
  (surface)
  (PrimST)
  (UsdPreviewSurface)
  ((UsdShaderId, "UsdPreviewSurface"))
  ((PrimStShaderId, "UsdPrimvarReader_float2"))
  (UsdUVTexture)
);

