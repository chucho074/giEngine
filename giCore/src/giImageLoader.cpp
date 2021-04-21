/**
 * @file    ImageLoader.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e      idv18c.jmoral@uartesdigitales.edu.mx
 * @date    14/10/2020
 * @brief  Read Image Files.
 * @bug    No known Bugs.
 */

/**
 * @include
 */
#include "giImageLoader.h"

namespace giEngineSDK {

  ImageLoader::ImageLoader() {

  }


  ImageLoader::~ImageLoader() {


  }


  void 
  ImageLoader::loadBMP(String inFileName) {

    //Clear the variables to use it
    clearData();

    std::ifstream FS;
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;

    //Open File
    FS.open(inFileName, std::ios::binary);

    //Save header from file
    FS.read((char*)&fileHeader, sizeof(fileHeader));
    FS.read((char*)&infoHeader, sizeof(infoHeader));

    //Save height and width
    m_width = infoHeader.biWidth;
    m_height = infoHeader.biHeight;
    m_BPP = infoHeader.biBitCount / 8;

    //Resize to data vector
    m_img.resize(infoHeader.biSizeImage);

    //Read image from file
    FS.read(m_img.data(), m_img.size());

    char temp = 0;
    for (int i = infoHeader.biSizeImage - 1 - m_BPP; i >= 0; i -= m_BPP) {
      //0xbbggrraa
      //0xaarrggbb
      temp = m_img[i + 1];
      m_img[i + 1] = m_img[i + 3];
      m_img[i + 3] = temp;


      /*std::cout << "R: " << int(m_img[i] & 0xff) <<
             " G: " << int(m_img[i + 1] & 0xff) <<
             " B: " << int(m_img[i + 2] & 0xff) << std::endl;*/
    }

    //Close File
    FS.close();
  }


  void 
  ImageLoader::clearData() {
    m_width = 0;
    m_height = 0;
    m_BPP = 0;
    m_img.clear();
  }
}