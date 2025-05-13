/**
 * @file    giDirectoryWatcher.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       edgv24c.jmoral@uartesdigitales.edu.mx
 * @date    08/5/2025
 */

/**
 * @include
 */
#pragma once
#include "giPrerequisitesUtilities.h"

namespace giEngineSDK {

  using dirEntry = fsys::directory_entry;
  using dirIter = fsys::directory_iterator;

  class DirectoryWatcher {
  public:
    DirectoryWatcher(const Path& inPath) {
      m_rootDir = inPath;
      m_currentPath = inPath;
      scanDir();
    }
  
    ~DirectoryWatcher() = default;
  
  
    inline void refresh() {
      scanDir();
    }
  
  
    const Vector<dirEntry>&
      getDirEntries() const {
      return m_dirEntries;
    }
  
    const Path& getCurrenPath() const {
      return m_currentPath;
    }
  
  
  private:
  
    void scanDir() {
      m_dirEntries.clear();
      for(const auto& entry : dirIter(m_currentPath)) {
        m_dirEntries.push_back(entry);
      }
    }
  
    Path m_rootDir;
    Path m_currentPath;
    Vector<dirEntry> m_dirEntries;
  };
}