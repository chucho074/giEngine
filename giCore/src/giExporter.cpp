/**
 * @file    giExporter.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    04/05/2023
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#include "giExporter.h"
#include "giDecoder.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include <stb_image.h>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/Exporter.hpp>      // C++ exporter interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

namespace giEngineSDK {

  void
  Exporter::ExportObj(Path inPath, SharedPtr<Model> inModel) {
    
    String tmpOut;
    String tmpOutMtl;

    //Material data
    tmpOut += ("mtllib " + inPath.stem().string() + ".mtl\n");
    tmpOut += ("g default\n");

    int32 matID = 0;

    for(auto mesh : inModel->m_meshes) {
      //Vertex data
      for(auto vertex : mesh->m_vertexVector) {
        tmpOut += "v "+ toString(vertex.Pos.x)+ " "+ toString(vertex.Pos.y)+ " "+ toString(vertex.Pos.z)+ "\n";
      }

      //Vertex texture Coords
      for (auto vertex : mesh->m_vertexVector) {
        tmpOut += "vt "+ toString(vertex.Tex.x)+ " "+ toString(vertex.Tex.y)+ "\n";
      }

      //Vertex Normals data
      for (auto vertex : mesh->m_vertexVector) {
        tmpOut += "vn "+ toString(vertex.Nor.x)+ " "+ toString(vertex.Nor.y)+ " "+ toString(vertex.Nor.z)+ "\n";
      }

      //Smooth shading
      tmpOut += "s off\n";

      tmpOut += "g "+ inPath.stem().string()+ "_subd:polyToSubd1\n";

      //Usemtl
      tmpOut += "usemtl mat" + toString(matID) + "\n";
      matID++;
      

      //Faces data
      String faces;
      for (int32 i = 0; i < mesh->m_facesList.size(); i += 3) {
      int32 v1 = mesh->m_facesList[i] + 1;
        int32 v2 = mesh->m_facesList[i + 1] + 1;
        int32 v3 = mesh->m_facesList[i + 2] + 1;
        faces += "f " + toString(v1) + '/' + toString(v1) + '/' + toString(v1) + ' '
                      + toString(v2) + '/' + toString(v2) + '/' + toString(v2) + ' '
                      + toString(v3) + '/' + toString(v3) + '/' + toString(v3) + '\n';
      }
      tmpOut += faces;
    }
    ofstream fout(inPath.string());
    fout << tmpOut;
    
    ExportMtl(inPath, inModel);
  }


  void 
  Exporter::ExportMtl(Path inPath, SharedPtr<Model> inModel) {
    auto& RM = g_resourceManager();
    String tmpOutMtl;
    
    int32 matID = 0;
    if (NULL == inModel) {
      tmpOutMtl += "newmtl mat" + toString(matID) + "\n";
      tmpOutMtl += "illum 4\n";

      tmpOutMtl += ("Kd " + toString(1.00) + " " + toString(1.00) + " " + toString(1.00) + "\n");
      tmpOutMtl += ("Ks " + toString(0.00) + " " + toString(0.00) + " " + toString(0.00) + "\n");
      tmpOutMtl += ("Ka " + toString(1.00) + " " + toString(1.00) + " " + toString(1.00) + "\n");
      tmpOutMtl += ("Tf " + toString(1.00) + " " + toString(1.00) + " " + toString(1.00) + "\n");
      tmpOutMtl += ("Ni " + toString(1.00) + "\n");
      //Write files
      Path tmpMtlPath = inPath;
      tmpMtlPath.replace_extension(".mtl");

      ofstream foutMtl(tmpMtlPath.string());
      foutMtl << tmpOutMtl;
      return;
    }

    for (auto mesh : inModel->m_meshes) {

      //Material datap

      tmpOutMtl += "newmtl mat" + toString(matID) + "\n";
      matID++;
      tmpOutMtl += "illum 4\n";

      tmpOutMtl += ("Kd " + toString(1.00) + " " + toString(1.00) + " " + toString(1.00) + "\n");
      tmpOutMtl += ("Ks " + toString(0.90) + " " + toString(0.90) + " " + toString(0.90) + "\n");
      tmpOutMtl += ("Ka " + toString(1.00) + " " + toString(1.00) + " " + toString(1.00) + "\n");
      tmpOutMtl += ("Tf " + toString(1.00) + " " + toString(1.00) + " " + toString(1.00) + "\n");
      tmpOutMtl += ("Ni " + toString(1.00) + "\n");

      //Textures
      if(!mesh->m_textures.empty()) {
        for(auto resource : mesh->m_textures) {
          SharedPtr<Texture> tmpTex = dynamic_pointer_cast<Texture>(RM.getResource(resource.m_id).lock());
          switch(tmpTex->m_type) {
            case TEXTURE_TYPE::kAlbedo: { 
              tmpOutMtl += ("map_Kd " + inPath.parent_path().string() + "/" + tmpTex->m_name + ".png" + "\n");
              break;
            }
            case TEXTURE_TYPE::kSpecular: {
              tmpOutMtl += ("map_Ks " + inPath.parent_path().string() + "/" + tmpTex->m_name + ".png" + "\n");
              break;
            }
            //case TEXTURE_TYPE::kDisplacement: {}
          }
          //Exports the texture as a png if is not already
          ExportAsNewImage(inPath.parent_path().string() + "/" + tmpTex->m_name + ".png", tmpTex->m_fullPath);
        }
      }
    }
    //Write files
    Path tmpMtlPath = inPath;
    tmpMtlPath.replace_extension(".mtl");

    ofstream foutMtl(tmpMtlPath.string());
    foutMtl << tmpOutMtl;
  }

  Path
  Exporter::ExportAsObj(Path inPath, String inFileType) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(inPath.string(), 
                                             aiProcess_Triangulate   
                                             | aiProcess_FlipUVs);

    //Export the model.
    Assimp::Exporter exporter;
    inPath.replace_extension(inFileType);
    exporter.Export(scene, inFileType, inPath.string());
    return inPath;
  }

  void 
  Exporter::ExportAsNewImage(Path inNewFilePath, Path inOldFilePath) {
    int32 w = 0, h = 0, comp = 0;

    comp = 4;

    //Get the information of the image loadead.
    uint8 * tmpImg = stbi_load(inOldFilePath.string().c_str(),
                               &w, 
                               &h, 
                               &comp, 4);

    //Create the texture with the information.
    if (tmpImg) {
      // Write the image to a PNG file
      stbi_write_png(inNewFilePath.string().c_str(), w, h, comp, tmpImg, w * comp);

      //Unload Data
      stbi_image_free(tmpImg);

      // Free the image memory
      //delete[] tmpImg;
      return;
    }
    //Unload Data
    stbi_image_free(tmpImg);
  }
}