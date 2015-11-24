/*
* Author: Tomáš Růžička, t_ruzicka (at) email.cz
* 2015
*/

#ifndef HEADERS_H
#define HEADERS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdint>
#include <windows.h>
#include <winbio.h>

typedef          int8_t    int8;
typedef          uint8_t   uint8;
typedef unsigned char      uchar;
typedef          int16_t   int16;
typedef          uint16_t  uint16;
typedef unsigned short     ushort;
typedef          int32_t   int32;
typedef          uint32_t  uint32;
typedef unsigned int       uint;
typedef unsigned long      ulong;
typedef          int64_t   int64;
typedef          long long llong;
typedef          uint64_t  uint64;
typedef unsigned long long ullong;

namespace NBmp
{
  static const uint32 BMP_HEADER_SIGNATURE_LENGHT = 0x02;
  static const uint32 BMP_HEADER_SIGNATURE_LENGHT_0 = 0x03;
  static const char   BMP_HEADER_SIGNATURE[BMP_HEADER_SIGNATURE_LENGHT_0] = "BM";

  static const uint32 BMP_HEADER_RESERVED = 0x00;
  static const uint32 BMP_HEADER_FILE_DATA_OFFSET = 0x36;
  static const uint32 BMP_INFO_HEADER_SIZE = 0x28;
  static const uint16 BMP_INFO_HEADER_PLANES = 0x01;
  static const uint16 BMP_INFO_HEADER_BITS_PER_PIXEL_8 = 0x08;
  static const uint16 BMP_INFO_HEADER_BITS_PER_PIXEL_24 = 0x18;
  static const uint16 BMP_INFO_HEADER_BITS_PER_PIXEL_32 = 0x20;
  static const uint32 BMP_INFO_HEADER_COMPRESSION = 0x00;
  static const uint32 BMP_INFO_HEADER_PIXEL_PER_METER_X = 0x00;
  static const uint32 BMP_INFO_HEADER_PIXEL_PER_METER_Y = 0x00;
  static const uint32 BMP_INFO_HEADER_COLORS = 0x00;
  static const uint32 BMP_INFO_HEADER_USED_COLORS = 0x00;

  static const uint32 BMP_8B_COLORS = 0x01;
  static const uint32 BMP_24B_COLORS = 0x03;
  static const uint32 BMP_32B_COLORS = 0x04;
}

struct SColor
{
  uint8 r;
  uint8 g;
  uint8 b;
  uint8 a;

  inline SColor() : r(0), g(0), b(0), a(255) {}
};

struct SBmpInfoHeader
{
  uint32 headerSize;
  uint32 width;
  uint32 height;
  uint16 planes;
  uint16 bitsPerPixel;
  uint32 compression;
  uint32 imageSize;
  uint32 pixelPerMeterX;
  uint32 pixelPerMeterY;
  uint32 colors;
  uint32 usedColors;

  inline SBmpInfoHeader() : headerSize(0), width(0), height(0), planes(0), bitsPerPixel(0), compression(0), imageSize(0), pixelPerMeterX(0), pixelPerMeterY(0), colors(0), usedColors(0) {}
};

struct SBmpImage
{
  std::string signature;
  uint32 fileSize;
  uint32 reserved;
  uint32 dataOffset;
  SBmpInfoHeader infoHeader;
  std::vector<SColor> colorTable;
  std::vector<SColor> data;
  uint8 dataPaddingSize;

  inline SBmpImage() : fileSize(0), reserved(0), dataOffset(0), dataPaddingSize(0)
  {
    signature.resize(NBmp::BMP_HEADER_SIGNATURE_LENGHT);
    memset(&signature[0], 0, sizeof(char)* NBmp::BMP_HEADER_SIGNATURE_LENGHT);
  }
};

class CFile
{
  private:
  std::ofstream *out;

  public:
  inline CFile() { out = new std::ofstream(); }
  inline CFile(std::string path) : CFile() { open(path); }
  inline ~CFile() { delete out; }

  inline void open(std::string path) { out->open(path, std::ofstream::binary); }
  //inline void read(void *dest, uint32 bytes) const { out->read(reinterpret_cast<char *>(src), bytes); }
  inline void write(const void *src, uint32 bytes) const { out->write(reinterpret_cast<const char *>(src), bytes); }
  inline uint32 tell() const { out->tellp(); }
  inline uint32 seek(int32 pos, std::ios_base::seekdir way) const { out->seekp(pos, way); }
  inline void close() { out->close(); }

  inline const std::ofstream *getFile() const { return out; }
};

#endif // HEADERS_H