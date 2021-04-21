/**
* @file		CImageLoader.h
* @author	Jesús Alberto Del Moral Cupil
* @e	    idv18c.jmoral@uartesdigitales.edu.mx
* @date		14/10/2020
* @brief	Read Image Files.
* @bug		No known Bugs.
**/

/**
* @include
**/
#pragma once
#include "giPrerequisitesCore.h"
#include "giStdHeaders.h"
#include <fstream>
#include "Windows.h"

namespace giEngineSDK {
  /**
  * @class    CImageLoader.
  * @brief    Read image files.
  * @bug      No known Bugs.
  **/
  class GI_CORE_EXPORT CImageLoader {
  public:

    ///Default constructor
    CImageLoader();

    ///Destructor
    ~CImageLoader();

    /**
    * @brief    Read data from file.
    * @param    inFileName Name of the file.
    * @bug      No known Bugs.
    **/
    void 
    loadBMP(String inFileName);

    /**
    * @brief    Getter for Width.
    * @bug      No known Bugs.
    * @return   Returns the width.
    **/
    unsigned int 
    getWidth() { return m_Width; }

    /**
    * @brief    Getter for Height.
    * @bug      No known Bugs.
    * @return   Returns the height.
    **/
    unsigned int 
    getHeight() { return m_Height; }

    /**
    * @brief    Getter for bytes per pixel.
    * @bug      No known Bugs.
    * @return   Returns the bytes.
    **/
    unsigned int 
    getBPP() { return m_BPP; }

    /**
    * @brief    Getter for image.
    * @bug      No known Bugs.
    * @return   Returns the data of the image.
    **/
    const char* 
    getImgData() { return m_Img.data(); }

    /**
    * @brief    Getter for line pitch.
    * @bug      No known Bugs.
    * @return   Returns the length in bytes of a line.
    **/
    unsigned int 
    getPitch() { return m_Width * m_BPP; }

    /**
    * @brief    Getter for full image size.
    * @bug      No known Bugs.
    * @return   Returns the full size in bytes.
    **/
    unsigned int 
    getImgSize() { return m_Width * m_Height * m_BPP; }

    /**
    * @brief    Clears the variables to use it again.
    * @bug      No known Bugs.
    **/
    void 
    clearData();

  private:

    ///Image Width
    unsigned int m_Width = 0;

    ///Image Height
    unsigned int m_Height = 0;

    ///Bytes per pixel
    unsigned int m_BPP = 0;

    ///Image Data bytes
    Vector<char> m_Img;
  };
}