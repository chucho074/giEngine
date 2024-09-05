/**
 * @file    giExporter.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    04/05/2023
 * @brief   A basic exporter.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include "giModel.h"

namespace giEngineSDK {
  class GI_CORE_EXPORT Exporter
  {
   public:
  	Exporter() = default;
  	~Exporter() = default;
    
    static void
  	ExportObj(Path inPath, SharedPtr<Model> inModel);

    static void
    ExportMtl(Path inPath);

    static Path 
    ExportAsObj(Path inPath, String inFileType);

   private:
    
  };
   
}