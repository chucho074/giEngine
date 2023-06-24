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
#include <string>

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
      tmpOut += "usemtl mat"+ toString(matID) + "\n";
      matID++;


      //Faces data
      String faces;
      for (int32 i = 0; i+9 <= mesh->m_facesList.size(); i += 9) {
        /*int32 v1 = mesh->m_facesList[i] + 1;
        int32 v2 = mesh->m_facesList[i + 1] + 1;
        int32 v3 = mesh->m_facesList[i + 2] + 1;
        faces += "f " + toString(v1) + '/' + toString(v1) + '/' + toString(v1) + ' ' 
                      + toString(v2) + '/' + toString(v2) + '/' + toString(v2) + ' ' 
                      + toString(v3) + '/' + toString(v3) + '/' + toString(v3) + '\n';*/

        int32 actual = mesh->m_facesList[i];
        faces += "f " + toString(mesh->m_facesList[i] + 1) + '/' + toString(mesh->m_facesList[i + 1] + 1) + '/' + toString(mesh->m_facesList[i + 2] + 1) + ' '
                      + toString(mesh->m_facesList[i + 3] + 1) + '/' + toString(mesh->m_facesList[i + 4] + 1) + '/' + toString(mesh->m_facesList[i + 5] + 1) + ' '
                      + toString(mesh->m_facesList[i + 6] + 1) + '/' + toString(mesh->m_facesList[i + 7] + 1) + '/' + toString(mesh->m_facesList[i + 8] + 1) + '\n';
      }
      tmpOut += faces;
    }

    //To change

    //Material data
    tmpOutMtl += "newmtl mat0\n";
    tmpOutMtl += "illum 4\n";

    tmpOutMtl += ("Kd "+ toString(1.00)+ " "+ toString(1.00)+ " "+ toString(1.00)+"\n");
    tmpOutMtl += ("Ks "+ toString(0.90)+ " "+ toString(0.90)+ " "+ toString(0.90)+"\n");
    tmpOutMtl += ("Ka "+ toString(1.00)+ " "+ toString(1.00)+ " "+ toString(1.00)+"\n");
    tmpOutMtl += ("Tf "+ toString(1.00)+ " "+ toString(1.00)+ " "+ toString(1.00)+"\n");
    tmpOutMtl += ("Ni "+ toString(1.00)+"\n");
    

    //Write files
    ofstream fout(inPath.string());
    fout << tmpOut;
    
    Path tmpMtlPath = inPath;
    tmpMtlPath.replace_extension(".mtl");

    ofstream foutMtl(tmpMtlPath.string());
    foutMtl << tmpOutMtl;
  }

}