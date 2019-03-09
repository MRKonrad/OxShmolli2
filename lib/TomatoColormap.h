/*!
 * \file TomatoColormap.h
 * \author Konrad Werys
 * \date 2017/08/23
 */

#ifndef TomatoLIB_SHMOLLICOLORMAP_H
#define TomatoLIB_SHMOLLICOLORMAP_H

#include "CmakeConfigForTomato.h"
#ifdef USE_ITK

// TODO: reading from a file

#include <vector>
#include <string>
#include <iostream>
#include "gdcmGlobal.h"
#include "gdcmBase64.h"

std::string getEncodedSting(std::vector < uint16_t > encodeSource);

std::vector < uint16_t > getShmolliColormapRed3TArray();
std::vector < uint16_t > getShmolliColormapGreen3TArray();
std::vector < uint16_t > getShmolliColormapBlue3TArray();

std::vector < uint16_t > getShmolliColormapRed15TArray();
std::vector < uint16_t > getShmolliColormapGreen15TArray();
std::vector < uint16_t > getShmolliColormapBlue15TArray();


#endif //USE_ITK

#endif //TomatoLIB_SHMOLLICOLORMAP_H
