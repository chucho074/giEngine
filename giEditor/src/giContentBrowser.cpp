/**
 * @file    giContentBrowser.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    01/06/2022
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giContentBrowser.h"


ContentBrowser::ContentBrowser(Path inWorkingDir) {
  m_workingDirectory = inWorkingDir;
  m_currentDirectory = m_workingDirectory;
  init();
}

void
ContentBrowser::init() {
  m_windowFlags |= ImGuiWindowFlags_NoCollapse;
}

void 
ContentBrowser::update(float inDeltaTime) {
  
}

void 
ContentBrowser::render() {

  ImGui::Begin("Content Browser", nullptr, m_windowFlags);

  //Back Button
  if (m_currentDirectory != m_workingDirectory) {
    if (ImGui::Button("<-")) {
      m_currentDirectory = m_currentDirectory.parent_path();
    }
  }

  //Iterate in directory
  for (auto& tmpIterator : fsys::directory_iterator(m_workingDirectory)) {

    const auto& tmpPath = tmpIterator.path();
    auto relativePath = fsys::relative(tmpPath, m_workingDirectory);
    String relativePathString = tmpPath.string();
    //Show Folders
    if (tmpIterator.is_directory()) {
      if (ImGui::Button(relativePathString.c_str())) {
        m_currentDirectory /= tmpPath.filename();
      }
    }
    //Show files
    else {
      if (ImGui::Button(relativePathString.c_str())) {
        
      }
    }
  }

  ImGui::End();
}

void 
ContentBrowser::destroy() {
  
}
