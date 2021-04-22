/**
 * @file    giPrerequisitesCore.h
 * @author  Jes�s Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    18/04/2021
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
#     define GI_CORE_EXPORT
#    else
#     if defined( GI_CORE_EXPORTS )
#      define GI_CORE_EXPORT __declspec( dllexport )
#    else
#      define GI_CORE_EXPORT __declspec( dllimport )
#    endif
#   endif
# else      //Any other Compiler
#   if defined ( GI_STATIC_LIB )
#    define GI_CORE_EXPORT
#   else
#     if defined ( GI_CORE_EXPORTS )
#       define GI_CORE_EXPORT __attribute__ ((dllexport))
#     else
#       define GI_CORE_EXPORT __attribute__ ((dllimport))
#     endif
#    endif
#  endif
#  define GI_CORE_HIDDEN
#else //Linux/Mac settings
# define GI_CORE_EXPORT __attribute__((visibility ("default")))
# define GI_CORE_HIDDEN __attribute__((visibility ("hidden")))
#endif


namespace giEngineSDK {
#define ALIGN_ELEMENT (0xffffffff)
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x=nullptr;

  using lpcstr = const char*;

  using wchar = wchar_t;

  namespace GI_FORMAT {
    enum E
    {
      kFORMAT_UNKNOWN = 0,
      kFORMAT_R32G32B32A32_TYPELESS = 1,
      kFORMAT_R32G32B32A32_FLOAT = 2,
      kFORMAT_R32G32B32A32_UINT = 3,
      kFORMAT_R32G32B32A32_SINT = 4,
      kFORMAT_R32G32B32_TYPELESS = 5,
      kFORMAT_R32G32B32_FLOAT = 6,
      kFORMAT_R32G32B32_UINT = 7,
      kFORMAT_R32G32B32_SINT = 8,
      kFORMAT_R16G16B16A16_TYPELESS = 9,
      kFORMAT_R16G16B16A16_FLOAT = 10,
      kFORMAT_R16G16B16A16_UNORM = 11,
      kFORMAT_R16G16B16A16_UINT = 12,
      kFORMAT_R16G16B16A16_SNORM = 13,
      kFORMAT_R16G16B16A16_SINT = 14,
      kFORMAT_R32G32_TYPELESS = 15,
      kFORMAT_R32G32_FLOAT = 16,
      kFORMAT_R32G32_UINT = 17,
      kFORMAT_R32G32_SINT = 18,
      kFORMAT_R32G8X24_TYPELESS = 19,
      kFORMAT_D32_FLOAT_S8X24_UINT = 20,
      kFORMAT_R32_FLOAT_X8X24_TYPELESS = 21,
      kFORMAT_X32_TYPELESS_G8X24_UINT = 22,
      kFORMAT_R10G10B10A2_TYPELESS = 23,
      kFORMAT_R10G10B10A2_UNORM = 24,
      kFORMAT_R10G10B10A2_UINT = 25,
      kFORMAT_R11G11B10_FLOAT = 26,
      kFORMAT_R8G8B8A8_TYPELESS = 27,
      kFORMAT_R8G8B8A8_UNORM = 28,
      kFORMAT_R8G8B8A8_UNORM_SRGB = 29,
      kFORMAT_R8G8B8A8_UINT = 30,
      kFORMAT_R8G8B8A8_SNORM = 31,
      kFORMAT_R8G8B8A8_SINT = 32,
      kFORMAT_R16G16_TYPELESS = 33,
      kFORMAT_R16G16_FLOAT = 34,
      kFORMAT_R16G16_UNORM = 35,
      kFORMAT_R16G16_UINT = 36,
      kFORMAT_R16G16_SNORM = 37,
      kFORMAT_R16G16_SINT = 38,
      kFORMAT_R32_TYPELESS = 39,
      kFORMAT_D32_FLOAT = 40,
      kFORMAT_R32_FLOAT = 41,
      kFORMAT_R32_UINT = 42,
      kFORMAT_R32_SINT = 43,
      kFORMAT_R24G8_TYPELESS = 44,
      kFORMAT_D24_UNORM_S8_UINT = 45,
      kFORMAT_R24_UNORM_X8_TYPELESS = 46,
      kFORMAT_X24_TYPELESS_G8_UINT = 47,
      kFORMAT_R8G8_TYPELESS = 48,
      kFORMAT_R8G8_UNORM = 49,
      kFORMAT_R8G8_UINT = 50,
      kFORMAT_R8G8_SNORM = 51,
      kFORMAT_R8G8_SINT = 52,
      kFORMAT_R16_TYPELESS = 53,
      kFORMAT_R16_FLOAT = 54,
      kFORMAT_D16_UNORM = 55,
      kFORMAT_R16_UNORM = 56,
      kFORMAT_R16_UINT = 57,
      kFORMAT_R16_SNORM = 58,
      kFORMAT_R16_SINT = 59,
      kFORMAT_R8_TYPELESS = 60,
      kFORMAT_R8_UNORM = 61,
      kFORMAT_R8_UINT = 62,
      kFORMAT_R8_SNORM = 63,
      kFORMAT_R8_SINT = 64,
      kFORMAT_A8_UNORM = 65,
      kFORMAT_R1_UNORM = 66,
      kFORMAT_R9G9B9E5_SHAREDEXP = 67,
      kFORMAT_R8G8_B8G8_UNORM = 68,
      kFORMAT_G8R8_G8B8_UNORM = 69,
      kFORMAT_BC1_TYPELESS = 70,
      kFORMAT_BC1_UNORM = 71,
      kFORMAT_BC1_UNORM_SRGB = 72,
      kFORMAT_BC2_TYPELESS = 73,
      kFORMAT_BC2_UNORM = 74,
      kFORMAT_BC2_UNORM_SRGB = 75,
      kFORMAT_BC3_TYPELESS = 76,
      kFORMAT_BC3_UNORM = 77,
      kFORMAT_BC3_UNORM_SRGB = 78,
      kFORMAT_BC4_TYPELESS = 79,
      kFORMAT_BC4_UNORM = 80,
      kFORMAT_BC4_SNORM = 81,
      kFORMAT_BC5_TYPELESS = 82,
      kFORMAT_BC5_UNORM = 83,
      kFORMAT_BC5_SNORM = 84,
      kFORMAT_B5G6R5_UNORM = 85,
      kFORMAT_B5G5R5A1_UNORM = 86,
      kFORMAT_B8G8R8A8_UNORM = 87,
      kFORMAT_B8G8R8X8_UNORM = 88,
      kFORMAT_R10G10B10_XR_BIAS_A2_UNORM = 89,
      kFORMAT_B8G8R8A8_TYPELESS = 90,
      kFORMAT_B8G8R8A8_UNORM_SRGB = 91,
      kFORMAT_B8G8R8X8_TYPELESS = 92,
      kFORMAT_B8G8R8X8_UNORM_SRGB = 93,
      kFORMAT_BC6H_TYPELESS = 94,
      kFORMAT_BC6H_UF16 = 95,
      kFORMAT_BC6H_SF16 = 96,
      kFORMAT_BC7_TYPELESS = 97,
      kFORMAT_BC7_UNORM = 98,
      kFORMAT_BC7_UNORM_SRGB = 99,
      kFORMAT_FORCE_UINT = 0xffffffff
    };
  }

  namespace GI_PRIMITIVE_TOPOLOGY {
    enum E
    {
      kPRIMITIVE_TOPOLOGY_UNDEFINED = 0,
      kPRIMITIVE_TOPOLOGY_POINTLIST = 1,
      kPRIMITIVE_TOPOLOGY_LINELIST = 2,
      kPRIMITIVE_TOPOLOGY_LINESTRIP = 3,
      kPRIMITIVE_TOPOLOGY_TRIANGLELIST = 4,
      kPRIMITIVE_TOPOLOGY_TRIANGLESTRIP = 5,
      kPRIMITIVE_TOPOLOGY_LINELIST_ADJ = 10,
      kPRIMITIVE_TOPOLOGY_LINESTRIP_ADJ = 11,
      kPRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ = 12,
      kPRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ = 13,
      kPRIMITIVE_TOPOLOGY_NUM
    };
  }

  namespace GI_DEVICE_FLAG {
    enum E {
      kCREATE_DEVICE_SINGLETHREADED = 0x1,
      kCREATE_DEVICE_DEBUG = 0x2,
      kCREATE_DEVICE_SWITCH_TO_REF = 0x4,
      kCREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS = 0x8,
      kCREATE_DEVICE_BGRA_SUPPORT = 0x20,
      kCREATE_DEVICE_NUM
    };
  }

  namespace GI_DRIVER_TYPE {
    enum E {
      kDRIVER_TYPE_UNKNOWN = 0,
      kDRIVER_TYPE_HARDWARE = (kDRIVER_TYPE_UNKNOWN + 1),
      kDRIVER_TYPE_REFERENCE = (kDRIVER_TYPE_HARDWARE + 1),
      kDRIVER_TYPE_NULL = (kDRIVER_TYPE_REFERENCE + 1),
      kDRIVER_TYPE_SOFTWARE = (kDRIVER_TYPE_NULL + 1),
      kDRIVER_TYPE_WARP = (kDRIVER_TYPE_SOFTWARE + 1)
    };
  }

  namespace GI_FEATURE_LEVEL {
    enum E {
      kFEATURE_LEVEL_9_1 = 0x9100,
      kFEATURE_LEVEL_9_2 = 0x9200,
      kFEATURE_LEVEL_9_3 = 0x9300,
      kFEATURE_LEVEL_10_0 = 0xa000,
      kFEATURE_LEVEL_10_1 = 0xa100,
      kFEATURE_LEVEL_11_0 = 0xb000
    };
  }

  namespace GI_USAGE {
    enum E {
      kUSAGE_DEFAULT = 0,
      kUSAGE_IMMUTABLE = 1,
      kUSAGE_DYNAMIC = 2,
      kUSAGE_STAGING = 3
    };
  }

  namespace GI_BIND_FLAG {
    enum E {
      kBIND_VERTEX_BUFFER = 0x1L,
      kBIND_INDEX_BUFFER = 0x2L,
      kBIND_CONSTANT_BUFFER = 0x4L,
      kBIND_SHADER_RESOURCE = 0x8L,
      kBIND_STREAM_OUTPUT = 0x10L,
      kBIND_RENDER_TARGET = 0x20L,
      kBIND_DEPTH_STENCIL = 0x40L,
      kBIND_UNORDERED_ACCESS = 0x80L
    };
  }

  namespace GI_CPU_ACCESS_FLAG {
    enum E{
      kCPU_ACCESS_WRITE = 0x10000L,
      kCPU_ACCESS_READ = 0x20000L
    };
  }

  namespace GI_SRV_DIMENSION {
    enum E {
      kSRV_DIMENSION_UNKNOWN = 0,
      kSRV_DIMENSION_BUFFER = 1,
      kSRV_DIMENSION_TEXTURE1D = 2,
      kSRV_DIMENSION_TEXTURE1DARRAY = 3,
      kSRV_DIMENSION_TEXTURE2D = 4,
      kSRV_DIMENSION_TEXTURE2DARRAY = 5,
      kSRV_DIMENSION_TEXTURE2DMS = 6,
      kSRV_DIMENSION_TEXTURE2DMSARRAY = 7,
      kSRV_DIMENSION_TEXTURE3D = 8,
      kSRV_DIMENSION_TEXTURECUBE = 9,
      kSRV_DIMENSION_TEXTURECUBEARRAY = 10,
      kSRV_DIMENSION_BUFFEREX = 11
    };
  }

  namespace GI_CLEAR_FLAG {
    enum E {
      kCLEAR_DEPTH = 0x1L,
      kCLEAR_STENCIL = 0x2L
    };
  }
  namespace GI_INPUT_CLASSIFICATION {
    enum E {
      kINPUT_PER_VERTEX_DATA = 0,
      kINPUT_PER_INSTANCE_DATA = 1
    };
  }
}
