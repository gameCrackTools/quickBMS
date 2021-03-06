/*
ntcompress 0.1
by Luigi Auriemma
e-mail: aluigi@autistici.org
web:    aluigi.org

dumped from NTCompress.exe of Nintendo Wii Revolution SDK

supported types:
- 0x30
- 0x40

unsupported types (huffman?) probably handled by other algorithms in QuickBMS:
- 0x00,0x10,0x20,0x70

how to retrieve the type from a file:
- type = (bytes[0] & 0xf0) - 0x10

usage:
- ntcompress_init();
- ntcompress_30(in, insz, out);
- // or
- ntcompress_40(in, insz, out);
- ntcompress_free(NULL);
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef WIN32
    #include <windows.h>
#endif



// variables and buffers guessed by the tool
static unsigned char *ntcompress_0043a788 = NULL;



static /*const*/ unsigned char ntcompress_dump[] = {
    0x83,0xec,0x10,0x53,0x55,0x8b,0x6c,0x24,0x20,0x56,0x0f,0xb6,0xf0,0xbb,0x01,0x00,
    0x00,0x00,0x8b,0xce,0x89,0x5c,0x24,0x14,0xd3,0xe3,0x57,0x33,0xff,0x33,0xd2,0x3c,
    0x08,0x8d,0x4b,0xff,0x89,0x4c,0x24,0x1c,0x76,0x11,0x0f,0xb7,0x45,0x00,0x83,0xc5,
    0x02,0xc7,0x44,0x24,0x10,0x02,0x00,0x00,0x00,0xeb,0x0f,0x0f,0xb6,0x45,0x00,0x83,
    0xc5,0x01,0xc7,0x44,0x24,0x10,0x01,0x00,0x00,0x00,0x8d,0x04,0x85,0x04,0x00,0x00,
    0x00,0x39,0x44,0x24,0x2c,0x89,0x44,0x24,0x14,0x0f,0x82,0x8a,0x00,0x00,0x00,0x39,
    0x44,0x24,0x10,0x73,0x79,0x8d,0x0c,0x1b,0x8b,0x5c,0x24,0x18,0x89,0x4c,0x24,0x2c,
    0x3b,0xd6,0x73,0x31,0x8b,0xce,0x2b,0xca,0x83,0xe9,0x01,0xc1,0xe9,0x03,0x83,0xc1,
    0x01,0x01,0x4c,0x24,0x10,0x8d,0x14,0xca,0xeb,0x06,0x8d,0x9b,0x00,0x00,0x00,0x00,
    0x0f,0xb6,0x45,0x00,0xc1,0xe7,0x08,0x0b,0xf8,0x83,0xc5,0x01,0x83,0xe9,0x01,0x75,
    0xef,0x8b,0x44,0x24,0x14,0x3b,0x5c,0x24,0x2c,0x73,0x1c,0x8b,0xca,0x2b,0xce,0x8b,
    0xc7,0xd3,0xe8,0x8b,0x4c,0x24,0x24,0x23,0x44,0x24,0x1c,0x83,0xc3,0x01,0x66,0x89,
    0x44,0x59,0xfe,0x8b,0x44,0x24,0x14,0x2b,0xd6,0x39,0x44,0x24,0x10,0x72,0xa1,0x8b,
    0x54,0x24,0x24,0x5f,0x5e,0x5d,0x66,0x89,0x1a,0x5b,0x83,0xc4,0x10,0xc3,0x8b,0x5c,
    0x24,0x18,0x8b,0x54,0x24,0x24,0x66,0x89,0x1a,0x5f,0x5e,0x5d,0x5b,0x83,0xc4,0x10,
    0xc3,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,
    0x81,0xec,0x98,0x00,0x00,0x00,0xa1,0x04,0x90,0x41,0x00,0x33,0xc4,0x89,0x84,0x24,
    0x94,0x00,0x00,0x00,0x8b,0x84,0x24,0x9c,0x00,0x00,0x00,0x53,0x55,0x56,0x0f,0xb6,
    0xb4,0x24,0xac,0x00,0x00,0x00,0x57,0x0f,0xb7,0x38,0x8d,0x2c,0x78,0x8d,0x58,0x02,
    0x8d,0x4e,0xfe,0xb8,0x01,0x00,0x00,0x00,0xd3,0xe0,0x68,0x80,0x00,0x00,0x00,0x6a,
    0x00,0x89,0x7c,0x24,0x1c,0x8d,0x48,0xff,0x0f,0xb7,0xd1,0x89,0x54,0x24,0x28,0x8d,
    0x4e,0xff,0xba,0x01,0x00,0x00,0x00,0xd3,0xe2,0x89,0x6c,0x24,0x18,0x0f,0xb7,0xca,
    0x0f,0xb7,0xd0,0x8d,0x44,0x24,0x2c,0x50,0x89,0x4c,0x24,0x24,0x89,0x54,0x24,0x28,
    0xe8,0x6b,0x4e,0x00,0x00,0x8d,0x4e,0x01,0xba,0x01,0x00,0x00,0x00,0xd3,0xe2,0x83,
    0xc4,0x0c,0x3b,0xfa,0x76,0x07,0x33,0xc0,0xe9,0xbd,0x00,0x00,0x00,0x3b,0xdd,0xbf,
    0x01,0x00,0x00,0x00,0x8b,0xd3,0x0f,0x83,0xa9,0x00,0x00,0x00,0x8d,0x64,0x24,0x00,
    0x8b,0xcf,0x83,0xe1,0x07,0xb8,0x01,0x00,0x00,0x00,0xd3,0xe0,0x8b,0xcf,0xc1,0xe9,
    0x03,0x8a,0x4c,0x0c,0x24,0x84,0xc1,0x75,0x7e,0x0f,0xb7,0x32,0x0f,0xb7,0x4c,0x24,
    0x20,0x0f,0xb7,0xc6,0x23,0xc1,0x8b,0xca,0x83,0xe1,0xfc,0x66,0x85,0xf6,0x8d,0x44,
    0x00,0x02,0x8d,0x0c,0x41,0x75,0x0b,0x8b,0x5c,0x24,0x14,0x83,0xc3,0xfc,0x3b,0xfb,
    0x73,0x55,0x3b,0xcd,0x73,0xa0,0x8b,0xce,0x23,0x4c,0x24,0x18,0x66,0x85,0xc9,0x74,
    0x1e,0x8b,0xcf,0x83,0xe1,0xfe,0x03,0xc8,0x8b,0xd9,0xc1,0xeb,0x03,0x8d,0x6c,0x1c,
    0x24,0x83,0xe1,0x07,0xb3,0x01,0xd2,0xe3,0x08,0x5d,0x00,0x8b,0x6c,0x24,0x10,0x23,
    0x74,0x24,0x1c,0x66,0x85,0xf6,0x74,0x1f,0x8b,0x6c,0x24,0x10,0x8b,0xcf,0x83,0xe1,
    0xfe,0x8d,0x4c,0x01,0x01,0x8b,0xc1,0x83,0xe1,0x07,0xb3,0x01,0xc1,0xe8,0x03,0xd2,
    0xe3,0x8d,0x44,0x04,0x24,0x08,0x18,0x83,0xc2,0x02,0x83,0xc7,0x01,0x3b,0xd5,0x0f,
    0x82,0x5b,0xff,0xff,0xff,0xb8,0x01,0x00,0x00,0x00,0x8b,0x8c,0x24,0xa4,0x00,0x00,
    0x00,0x5f,0x5e,0x5d,0x5b,0x33,0xcc,0xe8,0xa0,0x4a,0x00,0x00,0x81,0xc4,0x98,0x00,
    0x00,0x00,0xc3,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,
    0x83,0x7a,0x10,0x00,0x75,0x21,0x8b,0x42,0x04,0x3b,0x42,0x08,0x76,0x03,0x0c,0xff,
    0xc3,0x8b,0x0a,0x0f,0xb6,0x0c,0x08,0x83,0xc0,0x01,0x89,0x4a,0x0c,0x89,0x42,0x04,
    0xc7,0x42,0x10,0x08,0x00,0x00,0x00,0x8b,0x42,0x10,0x8d,0x48,0xff,0x8b,0x42,0x0c,
    0xd3,0xe8,0x89,0x4a,0x10,0x24,0x01,0xc3,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,
    0x84,0xc0,0x75,0x03,0x33,0xc0,0xc3,0x53,0x55,0x56,0x0f,0xb6,0xf0,0x39,0x72,0x10,
    0x57,0x73,0x34,0x8b,0x7a,0x08,0xbb,0x08,0x00,0x00,0x00,0xeb,0x03,0x8d,0x49,0x00,
    0x8b,0x42,0x04,0x3b,0xc7,0x77,0x42,0xc1,0x62,0x0c,0x08,0x8b,0x2a,0x0f,0xb6,0x2c,
    0x28,0x8b,0x4a,0x0c,0x01,0x5a,0x10,0x0b,0xe9,0x83,0xc0,0x01,0x89,0x6a,0x0c,0x89,
    0x42,0x04,0x39,0x72,0x10,0x72,0xd9,0x8b,0x7a,0x10,0x8b,0x42,0x0c,0x2b,0xfe,0x8b,
    0xcf,0xd3,0xe8,0x8b,0xce,0xbb,0x01,0x00,0x00,0x00,0xd3,0xe3,0x89,0x7a,0x10,0x5f,
    0x5e,0x83,0xeb,0x01,0x5d,0x23,0xc3,0x5b,0xc3,0x5f,0x5e,0x5d,0x83,0xc8,0xff,0x5b,
    0xc3,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,
    0x83,0xec,0x20,0x53,0x55,0x8b,0x6c,0x24,0x30,0x33,0xdb,0x83,0xfd,0x04,0x89,0x5c,
    0x24,0x08,0x73,0x09,0x5d,0x83,0xc8,0xff,0x5b,0x83,0xc4,0x20,0xc3,0x56,0x8b,0x74,
    0x24,0x30,0x8b,0x06,0xc1,0xe8,0x08,0x57,0x89,0x44,0x24,0x14,0xbf,0x04,0x00,0x00,
    0x00,0x75,0x1c,0x83,0xfd,0x08,0x0f,0x82,0x6f,0x02,0x00,0x00,0x8b,0x46,0x04,0xc7,
    0x44,0x24,0x18,0x08,0x00,0x00,0x00,0x8b,0x7c,0x24,0x18,0x89,0x44,0x24,0x14,0x8b,
    0xcd,0x2b,0xcf,0x51,0x8d,0x14,0x37,0x52,0x68,0x88,0xa7,0x43,0x00,0xb0,0x09,0xe8,
    0x6c,0xfc,0xff,0xff,0x03,0xf8,0x83,0xc4,0x0c,0x3b,0xfd,0x0f,0x83,0x3a,0x02,0x00,
    0x00,0x6a,0x09,0x68,0x88,0xa7,0x43,0x00,0xe8,0x53,0xfd,0xff,0xff,0x83,0xc4,0x08,
    0x85,0xc0,0x0f,0x84,0x23,0x02,0x00,0x00,0x8b,0xc5,0x2b,0xc7,0x50,0x8d,0x0c,0x37,
    0x51,0x68,0x88,0xaf,0x43,0x00,0xb0,0x05,0xe8,0x33,0xfc,0xff,0xff,0x03,0xf8,0x83,
    0xc4,0x0c,0x3b,0xfd,0x89,0x7c,0x24,0x18,0x0f,0x83,0xfd,0x01,0x00,0x00,0x6a,0x05,
    0x68,0x88,0xaf,0x43,0x00,0xe8,0x16,0xfd,0xff,0xff,0x83,0xc4,0x08,0x85,0xc0,0x0f,
    0x84,0xe6,0x01,0x00,0x00,0x33,0xc0,0x2b,0xef,0x39,0x5c,0x24,0x14,0x8d,0x14,0x37,
    0x89,0x54,0x24,0x1c,0x89,0x44,0x24,0x20,0x89,0x5c,0x24,0x28,0x89,0x5c,0x24,0x2c,
    0x89,0x6c,0x24,0x24,0x0f,0x86,0xb5,0x01,0x00,0x00,0xeb,0x08,0x8d,0x64,0x24,0x00,
    0x8b,0x44,0x24,0x20,0xbe,0x8a,0xa7,0x43,0x00,0x8d,0xa4,0x24,0x00,0x00,0x00,0x00,
    0x85,0xdb,0x75,0x20,0x3b,0xc5,0x76,0x04,0x0c,0xff,0xeb,0x29,0x8b,0x4c,0x24,0x1c,
    0x0f,0xb6,0x14,0x01,0x83,0xc0,0x01,0x89,0x54,0x24,0x28,0x89,0x44,0x24,0x20,0xbb,
    0x08,0x00,0x00,0x00,0x8b,0x44,0x24,0x28,0x8d,0x4b,0xff,0xd3,0xe8,0x8b,0xd9,0x89,
    0x5c,0x24,0x2c,0x24,0x01,0x0f,0xb7,0x16,0x0f,0xbe,0xc8,0x8b,0xfa,0x83,0xe7,0x7f,
    0x84,0xc0,0x8d,0x7c,0x79,0x02,0x0f,0x8c,0x5f,0x01,0x00,0x00,0xb8,0x00,0x01,0x00,
    0x00,0xd3,0xf8,0x83,0xe6,0xfc,0x85,0xc2,0x75,0x09,0x8b,0x44,0x24,0x20,0x8d,0x34,
    0x7e,0xeb,0x9d,0x0f,0xb7,0x04,0x7e,0x66,0x3d,0x00,0x01,0x73,0x17,0x8b,0x4c,0x24,
    0x10,0x8b,0x54,0x24,0x3c,0x88,0x04,0x11,0x83,0xc1,0x01,0x89,0x4c,0x24,0x10,0xe9,
    0x0d,0x01,0x00,0x00,0x0f,0xb6,0xc0,0x83,0xc0,0x03,0x0f,0xb7,0xe8,0xbe,0x8a,0xaf,
    0x43,0x00,0x85,0xdb,0x75,0x26,0x8b,0x44,0x24,0x20,0x3b,0x44,0x24,0x24,0x76,0x04,
    0x0c,0xff,0xeb,0x29,0x8b,0x4c,0x24,0x1c,0x0f,0xb6,0x14,0x01,0x83,0xc0,0x01,0x89,
    0x54,0x24,0x28,0x89,0x44,0x24,0x20,0xbb,0x08,0x00,0x00,0x00,0x8b,0x44,0x24,0x28,
    0x8d,0x4b,0xff,0xd3,0xe8,0x8b,0xd9,0x89,0x5c,0x24,0x2c,0x24,0x01,0x0f,0xb7,0x16,
    0x0f,0xbe,0xc8,0x8b,0xfa,0x83,0xe7,0x07,0x84,0xc0,0x8d,0x7c,0x79,0x02,0x0f,0x8c,
    0xc7,0x00,0x00,0x00,0xb8,0x10,0x00,0x00,0x00,0xd3,0xf8,0x83,0xe6,0xfc,0x85,0xc2,
    0x75,0x05,0x8d,0x34,0x7e,0xeb,0x9b,0x0f,0xb7,0x34,0x7e,0x33,0xff,0x66,0x85,0xf6,
    0x76,0x35,0x81,0xc6,0xff,0xff,0x00,0x00,0x66,0x85,0xf6,0xbf,0x01,0x00,0x00,0x00,
    0x76,0x25,0x8d,0x54,0x24,0x1c,0xe8,0x25,0xfd,0xff,0xff,0x66,0x0f,0xbe,0xc8,0x8d,
    0x14,0x3f,0x66,0x0b,0xca,0x81,0xc6,0xff,0xff,0x00,0x00,0x66,0x85,0xf6,0x0f,0xb7,
    0xf9,0x77,0xdf,0x8b,0x5c,0x24,0x2c,0x8b,0x44,0x24,0x10,0x0f,0xb7,0xcd,0x03,0xc8,
    0x83,0xc7,0x01,0x3b,0x4c,0x24,0x14,0x77,0x62,0x0f,0xb7,0xcf,0x3b,0xc1,0x72,0x5b,
    0x8b,0x54,0x24,0x20,0x8b,0x44,0x24,0x18,0x03,0xd0,0x3b,0x54,0x24,0x38,0x77,0x4b,
    0x66,0x85,0xed,0x76,0x28,0x8b,0x74,0x24,0x10,0x8b,0x7c,0x24,0x3c,0x8b,0xc6,0x2b,
    0xc1,0x03,0xc7,0x8a,0x08,0x81,0xc5,0xff,0xff,0x00,0x00,0x88,0x0c,0x3e,0x83,0xc6,
    0x01,0x83,0xc0,0x01,0x66,0x85,0xed,0x77,0xea,0x89,0x74,0x24,0x10,0x8b,0x6c,0x24,
    0x24,0x8b,0x54,0x24,0x10,0x3b,0x54,0x24,0x14,0x0f,0x82,0x51,0xfe,0xff,0xff,0x8b,
    0x44,0x24,0x10,0x5f,0x5e,0x5d,0x5b,0x83,0xc4,0x20,0xc3,0x5f,0x5e,0x5d,0x83,0xc8,
    0xff,0x5b,0x83,0xc4,0x20,0xc3,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,
    0x33,0xc9,0x89,0x08,0xc7,0x40,0x04,0x00,0x00,0x00,0x80,0x89,0x48,0x08,0x88,0x48,
    0x0c,0x89,0x48,0x10,0xc3,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,
    0x53,0x57,0xbf,0x01,0x00,0x00,0x00,0xd3,0xe7,0x88,0x4e,0x0c,0x8d,0x1c,0xbd,0x00,
    0x00,0x00,0x00,0x53,0xe8,0x10,0x46,0x00,0x00,0x53,0x89,0x06,0xe8,0x08,0x46,0x00,
    0x00,0x89,0x46,0x04,0x33,0xc9,0x83,0xc4,0x08,0x33,0xc0,0x3b,0xf9,0x76,0x13,0x90,
    0x8b,0x16,0x89,0x0c,0x82,0x8b,0x56,0x04,0x89,0x0c,0x82,0x83,0xc0,0x01,0x3b,0xc7,
    0x72,0xee,0x5f,0x89,0x4e,0x08,0x5b,0xc3,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,
    0x8a,0x4a,0x0c,0x83,0xec,0x10,0x53,0xbb,0x01,0x00,0x00,0x00,0xd3,0xe3,0x56,0x33,
    0xf6,0x57,0x3b,0xde,0x89,0x72,0x08,0x76,0x14,0x8b,0x02,0x8b,0xcb,0x8d,0x49,0x00,
    0x8b,0x38,0x01,0x7a,0x08,0x83,0xc0,0x04,0x83,0xe9,0x01,0x75,0xf3,0x8b,0x42,0x08,
    0xdb,0x42,0x08,0x85,0xc0,0x55,0x7d,0x06,0xd8,0x05,0x88,0x61,0x41,0x00,0xdc,0x3d,
    0x80,0x61,0x41,0x00,0x33,0xed,0x33,0xc9,0x3b,0xde,0x89,0x74,0x24,0x14,0x89,0x72,
    0x08,0xd9,0x5c,0x24,0x10,0x0f,0x86,0x88,0x00,0x00,0x00,0xd9,0x44,0x24,0x10,0xdd,
    0x05,0x78,0x61,0x41,0x00,0x8b,0x02,0x8b,0x3c,0x88,0x8d,0x34,0x88,0x8b,0xc7,0x85,
    0xc0,0x89,0x44,0x24,0x18,0xdb,0x44,0x24,0x18,0x7d,0x06,0xd8,0x05,0x88,0x61,0x41,
    0x00,0xd9,0x7c,0x24,0x10,0x0f,0xb7,0x44,0x24,0x10,0xd8,0xca,0x0d,0x00,0x0c,0x00,
    0x00,0x85,0xff,0x89,0x44,0x24,0x18,0xd8,0xc1,0xd9,0x6c,0x24,0x18,0xdf,0x7c,0x24,
    0x18,0x8b,0x44,0x24,0x18,0x89,0x06,0xd9,0x6c,0x24,0x10,0x74,0x11,0x8b,0x02,0x83,
    0x3c,0x88,0x00,0x8d,0x04,0x88,0x75,0x06,0xc7,0x00,0x01,0x00,0x00,0x00,0x8b,0x02,
    0x8b,0x34,0x88,0x01,0x72,0x08,0x39,0x2c,0x88,0x8d,0x04,0x88,0x72,0x06,0x8b,0x28,
    0x89,0x4c,0x24,0x14,0x83,0xc1,0x01,0x3b,0xcb,0x72,0x8a,0x8b,0x74,0x24,0x14,0xdd,
    0xd9,0xdd,0xd8,0x8b,0x0a,0x8b,0x42,0x08,0x8d,0x0c,0xb1,0xbe,0x00,0x00,0x01,0x00,
    0x2b,0xf0,0x01,0x31,0x8b,0x42,0x04,0xc7,0x42,0x08,0x00,0x00,0x01,0x00,0xc7,0x00,
    0x00,0x00,0x00,0x00,0xb8,0x01,0x00,0x00,0x00,0x3b,0xd8,0x5d,0x76,0x1b,0x8b,0xff,
    0x8b,0x4a,0x04,0x8b,0x32,0x8b,0x74,0x86,0xfc,0x03,0x74,0x81,0xfc,0x8d,0x0c,0x81,
    0x83,0xc0,0x01,0x3b,0xc3,0x89,0x31,0x72,0xe7,0x5f,0x5e,0x5b,0x83,0xc4,0x10,0xc3,
    0x83,0xec,0x08,0x33,0xc0,0x39,0x44,0x24,0x0c,0x55,0x8b,0x6c,0x24,0x14,0x0f,0x86,
    0x7f,0x01,0x00,0x00,0x53,0x57,0x8a,0x14,0x08,0x88,0x54,0x24,0x0f,0x83,0xc0,0x01,
    0xc7,0x44,0x24,0x10,0x00,0x00,0x00,0x00,0xeb,0x06,0x8d,0x9b,0x00,0x00,0x00,0x00,
    0x8a,0x14,0x08,0x83,0xc0,0x01,0xf6,0x44,0x24,0x0f,0x80,0x0f,0xb6,0xd2,0x74,0x2d,
    0x66,0x0f,0xb6,0x3c,0x08,0x33,0xdb,0x8a,0x7c,0x08,0x01,0x83,0xc0,0x01,0x0f,0xb7,
    0xff,0x81,0xca,0x00,0x01,0x00,0x00,0x83,0xc0,0x01,0x0b,0xfb,0x8b,0x1e,0x83,0x04,
    0x93,0x01,0x8d,0x14,0x93,0x0f,0xb7,0xd7,0x8b,0x7d,0x00,0xeb,0x02,0x8b,0x3e,0x83,
    0x04,0x97,0x01,0xd0,0x64,0x24,0x0f,0x3b,0x44,0x24,0x18,0x8d,0x14,0x97,0x0f,0x83,
    0x0d,0x01,0x00,0x00,0x8a,0x14,0x08,0x83,0xc0,0x01,0xf6,0x44,0x24,0x0f,0x80,0x0f,
    0xb6,0xd2,0x74,0x2d,0x66,0x0f,0xb6,0x3c,0x08,0x33,0xdb,0x8a,0x7c,0x08,0x01,0x83,
    0xc0,0x01,0x0f,0xb7,0xff,0x81,0xca,0x00,0x01,0x00,0x00,0x83,0xc0,0x01,0x0b,0xfb,
    0x8b,0x1e,0x83,0x04,0x93,0x01,0x8d,0x14,0x93,0x0f,0xb7,0xd7,0x8b,0x7d,0x00,0xeb,
    0x02,0x8b,0x3e,0x83,0x04,0x97,0x01,0xd0,0x64,0x24,0x0f,0x3b,0x44,0x24,0x18,0x8d,
    0x14,0x97,0x0f,0x83,0xb9,0x00,0x00,0x00,0x8a,0x14,0x08,0x83,0xc0,0x01,0xf6,0x44,
    0x24,0x0f,0x80,0x0f,0xb6,0xd2,0x74,0x2d,0x66,0x0f,0xb6,0x3c,0x08,0x33,0xdb,0x8a,
    0x7c,0x08,0x01,0x83,0xc0,0x01,0x0f,0xb7,0xff,0x81,0xca,0x00,0x01,0x00,0x00,0x83,
    0xc0,0x01,0x0b,0xfb,0x8b,0x1e,0x83,0x04,0x93,0x01,0x8d,0x14,0x93,0x0f,0xb7,0xd7,
    0x8b,0x7d,0x00,0xeb,0x02,0x8b,0x3e,0x83,0x04,0x97,0x01,0xd0,0x64,0x24,0x0f,0x3b,
    0x44,0x24,0x18,0x8d,0x14,0x97,0x73,0x69,0x8a,0x14,0x08,0x83,0xc0,0x01,0xf6,0x44,
    0x24,0x0f,0x80,0x0f,0xb6,0xd2,0x74,0x2d,0x66,0x0f,0xb6,0x3c,0x08,0x33,0xdb,0x8a,
    0x7c,0x08,0x01,0x83,0xc0,0x01,0x0f,0xb7,0xff,0x81,0xca,0x00,0x01,0x00,0x00,0x83,
    0xc0,0x01,0x0b,0xfb,0x8b,0x1e,0x83,0x04,0x93,0x01,0x8d,0x14,0x93,0x0f,0xb7,0xd7,
    0x8b,0x7d,0x00,0xeb,0x02,0x8b,0x3e,0x83,0x04,0x97,0x01,0xd0,0x64,0x24,0x0f,0x3b,
    0x44,0x24,0x18,0x8d,0x14,0x97,0x73,0x19,0x8b,0x54,0x24,0x10,0x83,0xc2,0x04,0x83,
    0xfa,0x08,0x89,0x54,0x24,0x10,0x0f,0x82,0xa4,0xfe,0xff,0xff,0xe9,0x85,0xfe,0xff,
    0xff,0x5f,0x5b,0x8b,0xd6,0xe8,0x36,0xfd,0xff,0xff,0x8b,0xd5,0x5d,0x83,0xc4,0x08,
    0xe9,0x2b,0xfd,0xff,0xff,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,
    0x53,0x56,0xbe,0x01,0x00,0x00,0x00,0xd3,0xe6,0x88,0x4f,0x0c,0x8d,0x1c,0xb5,0x00,
    0x00,0x00,0x00,0x53,0xe8,0xe0,0x42,0x00,0x00,0x53,0x89,0x07,0xe8,0xd8,0x42,0x00,
    0x00,0x89,0x47,0x04,0x83,0xc4,0x08,0x33,0xc0,0x85,0xf6,0x76,0x19,0x8d,0x49,0x00,
    0x8b,0x0f,0xc7,0x04,0x81,0x01,0x00,0x00,0x00,0x8b,0x57,0x04,0x89,0x04,0x82,0x83,
    0xc0,0x01,0x3b,0xc6,0x72,0xea,0x89,0x77,0x08,0x5e,0x5b,0xc3,0xcc,0xcc,0xcc,0xcc,
    0x8a,0x48,0x0c,0x8b,0x10,0x56,0xbe,0x01,0x00,0x00,0x00,0xd3,0xe6,0x0f,0xb7,0x4c,
    0x24,0x08,0x83,0x04,0x8a,0x01,0x83,0x40,0x08,0x01,0x8d,0x14,0x8a,0x83,0xc1,0x01,
    0x3b,0xce,0x73,0x11,0x8b,0x50,0x04,0x83,0x04,0x8a,0x01,0x8d,0x14,0x8a,0x83,0xc1,
    0x01,0x3b,0xce,0x72,0xef,0x81,0x78,0x08,0x00,0x00,0x01,0x00,0x72,0x4e,0x8b,0x08,
    0x83,0x39,0x01,0x76,0x02,0xd1,0x29,0x8b,0x48,0x04,0xc7,0x01,0x00,0x00,0x00,0x00,
    0x8b,0x10,0x8b,0x0a,0x89,0x48,0x08,0xb9,0x01,0x00,0x00,0x00,0x3b,0xf1,0x76,0x2c,
    0x57,0x83,0x3c,0x8a,0x01,0x76,0x03,0xd1,0x2c,0x8a,0x8b,0x50,0x04,0x8b,0x38,0x8b,
    0x7c,0x8f,0xfc,0x03,0x7c,0x8a,0xfc,0x8d,0x14,0x8a,0x89,0x3a,0x8b,0x10,0x8b,0x3c,
    0x8a,0x01,0x78,0x08,0x83,0xc1,0x01,0x3b,0xce,0x72,0xd6,0x5f,0x5e,0xc3,0xcc,0xcc,
    0x53,0x8b,0xd9,0x33,0xd2,0x55,0x57,0x8b,0xf8,0x8b,0x46,0x04,0xf7,0x73,0x08,0x0f,
    0xb7,0x4c,0x24,0x10,0x8b,0x53,0x04,0x8b,0x2e,0x03,0xc9,0x03,0xc9,0x8b,0x14,0x0a,
    0x0f,0xaf,0xd0,0x03,0xd5,0x89,0x16,0x8b,0x13,0x8b,0x0c,0x0a,0x0f,0xaf,0xc8,0x83,
    0x7c,0x24,0x14,0x00,0x89,0x4e,0x04,0x74,0x0f,0x8b,0x54,0x24,0x10,0x52,0x8b,0xc3,
    0xe8,0x2b,0xff,0xff,0xff,0x83,0xc4,0x04,0x83,0xcb,0xff,0x3b,0x2e,0x8d,0x6b,0x02,
    0x76,0x45,0x80,0x46,0x0c,0x01,0x39,0x6e,0x10,0x8a,0x46,0x0c,0x76,0x39,0x0f,0xb6,
    0xc0,0x50,0x8d,0x4b,0x09,0xe8,0xb6,0xed,0xff,0xff,0x01,0x5e,0x10,0x83,0xc4,0x04,
    0x39,0x6e,0x10,0xc6,0x46,0x0c,0x00,0x76,0x1e,0x8d,0xa4,0x24,0x00,0x00,0x00,0x00,
    0x6a,0x00,0xb9,0x08,0x00,0x00,0x00,0xe8,0x94,0xed,0xff,0xff,0x01,0x5e,0x10,0x83,
    0xc4,0x04,0x39,0x6e,0x10,0x77,0xe9,0x81,0x7e,0x04,0x00,0x00,0x00,0x01,0x73,0x65,
    0x8a,0x46,0x03,0x3c,0xff,0x88,0x44,0x24,0x10,0x75,0x05,0x01,0x6e,0x10,0xeb,0x45,
    0x83,0x7e,0x10,0x00,0x76,0x35,0x0f,0xb6,0x4e,0x0c,0x51,0xb9,0x08,0x00,0x00,0x00,
    0xe8,0x5b,0xed,0xff,0xff,0x83,0xc4,0x04,0x01,0x5e,0x10,0x74,0x1e,0x8d,0x49,0x00,
    0x68,0xff,0x00,0x00,0x00,0xb9,0x08,0x00,0x00,0x00,0xe8,0x41,0xed,0xff,0xff,0x01,
    0x5e,0x10,0x83,0xc4,0x04,0x83,0x7e,0x10,0x00,0x77,0xe5,0x8a,0x54,0x24,0x10,0x88,
    0x56,0x0c,0x89,0x6e,0x10,0xc1,0x26,0x08,0xc1,0x66,0x04,0x08,0x81,0x7e,0x04,0x00,
    0x00,0x00,0x01,0x72,0x9b,0x5f,0x5d,0x5b,0xc3,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,
    0x83,0x7e,0x10,0x00,0x57,0x8b,0xf8,0x76,0x43,0x0f,0xb6,0x46,0x0c,0x50,0xb9,0x08,
    0x00,0x00,0x00,0xe8,0xf8,0xec,0xff,0xff,0x83,0x46,0x10,0xff,0x83,0xc4,0x04,0x83,
    0x7e,0x10,0x00,0x76,0x27,0xeb,0x09,0x8d,0xa4,0x24,0x00,0x00,0x00,0x00,0x8b,0xff,
    0x68,0xff,0x00,0x00,0x00,0xb9,0x08,0x00,0x00,0x00,0xe8,0xd1,0xec,0xff,0xff,0x83,
    0x46,0x10,0xff,0x83,0xc4,0x04,0x83,0x7e,0x10,0x00,0x77,0xe4,0x0f,0xb6,0x4e,0x03,
    0x51,0xb9,0x08,0x00,0x00,0x00,0xe8,0xb5,0xec,0xff,0xff,0x0f,0xb7,0x56,0x02,0x52,
    0xb9,0x08,0x00,0x00,0x00,0xe8,0xa6,0xec,0xff,0xff,0x8b,0x06,0xc1,0xe8,0x08,0x50,
    0xb9,0x08,0x00,0x00,0x00,0xe8,0x96,0xec,0xff,0xff,0x8b,0x0e,0x51,0xb9,0x08,0x00,
    0x00,0x00,0xe8,0x89,0xec,0xff,0xff,0x83,0xc4,0x10,0x5f,0xc3,0xcc,0xcc,0xcc,0xcc,
    0x83,0xec,0x2c,0x55,0x8b,0x6c,0x24,0x34,0x56,0x57,0x8d,0x44,0x24,0x24,0x33,0xff,
    0xe8,0x1b,0xfa,0xff,0xff,0x8b,0x4c,0x24,0x44,0x8d,0x44,0x24,0x14,0xe8,0x4e,0xec,
    0xff,0xff,0x39,0x7c,0x24,0x40,0x0f,0x86,0xa4,0x00,0x00,0x00,0x53,0x8d,0x49,0x00,
    0x8a,0x04,0x2f,0x88,0x44,0x24,0x13,0x83,0xc7,0x01,0xc7,0x44,0x24,0x14,0x00,0x00,
    0x00,0x00,0x8a,0x04,0x2f,0x83,0xc7,0x01,0xf6,0x44,0x24,0x13,0x80,0x6a,0x01,0x8d,
    0x74,0x24,0x2c,0x74,0x42,0x66,0x0f,0xb6,0x0c,0x2f,0x66,0x0f,0xb6,0xc0,0x33,0xd2,
    0x8a,0x74,0x2f,0x01,0x83,0xc7,0x01,0x0f,0xb7,0xd9,0x8b,0x4c,0x24,0x50,0x0d,0x00,
    0x01,0x00,0x00,0x50,0x8d,0x44,0x24,0x20,0x0b,0xda,0x83,0xc7,0x01,0xe8,0xde,0xfd,
    0xff,0xff,0x8b,0x4c,0x24,0x58,0x6a,0x01,0x53,0x8d,0x44,0x24,0x28,0xe8,0xce,0xfd,
    0xff,0xff,0x83,0xc4,0x10,0xeb,0x15,0x66,0x0f,0xb6,0xc8,0x8d,0x44,0x24,0x1c,0x51,
    0x8b,0x4c,0x24,0x54,0xe8,0xb7,0xfd,0xff,0xff,0x83,0xc4,0x08,0xd0,0x64,0x24,0x13,
    0x3b,0x7c,0x24,0x44,0x73,0x19,0x8b,0x44,0x24,0x14,0x83,0xc0,0x01,0x83,0xf8,0x08,
    0x89,0x44,0x24,0x14,0x0f,0x82,0x78,0xff,0xff,0xff,0xe9,0x61,0xff,0xff,0xff,0x5b,
    0x8d,0x74,0x24,0x24,0x8d,0x44,0x24,0x14,0xe8,0x93,0xfe,0xff,0xff,0x6a,0x04,0x8d,
    0x7c,0x24,0x18,0xe8,0x08,0xec,0xff,0xff,0x8b,0x44,0x24,0x1c,0x83,0xc4,0x04,0x5f,
    0x5e,0x5d,0x83,0xc4,0x2c,0xc3,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,
    0x83,0xec,0x2c,0xa1,0x04,0x90,0x41,0x00,0x33,0xc4,0x89,0x44,0x24,0x28,0x53,0x55,
    0x8b,0x6c,0x24,0x40,0x56,0x8b,0x74,0x24,0x3c,0x57,0x8b,0x7c,0x24,0x44,0x8d,0x04,
    0x7f,0x50,0xe8,0x52,0x3f,0x00,0x00,0x6a,0x0c,0x6a,0x02,0x56,0x8b,0xcf,0x8b,0xd8,
    0xe8,0x0b,0xea,0xff,0xff,0x83,0xc4,0x10,0xb1,0x09,0x8d,0x74,0x24,0x28,0x89,0x44,
    0x24,0x10,0xe8,0x09,0xf9,0xff,0xff,0xb1,0x0c,0x8d,0x74,0x24,0x18,0xe8,0xfe,0xf8,
    0xff,0xff,0x8d,0x4f,0xff,0x81,0xf9,0xfe,0xff,0xff,0x00,0x77,0x13,0xc1,0xe7,0x08,
    0x83,0xcf,0x50,0x89,0x7d,0x00,0xc7,0x44,0x24,0x14,0x04,0x00,0x00,0x00,0xeb,0x12,
    0xc7,0x45,0x00,0x50,0x00,0x00,0x00,0x89,0x7d,0x04,0xc7,0x44,0x24,0x14,0x08,0x00,
    0x00,0x00,0x8b,0x44,0x24,0x10,0x8d,0x54,0x24,0x18,0x52,0x50,0x8d,0x74,0x24,0x30,
    0x8b,0xcb,0xe8,0x39,0xfa,0xff,0xff,0xb1,0x09,0x8b,0xfe,0xe8,0xe0,0xfb,0xff,0xff,
    0xb1,0x0c,0x8d,0x7c,0x24,0x20,0xe8,0xd5,0xfb,0xff,0xff,0x8b,0x44,0x24,0x18,0x8b,
    0xcf,0x51,0x8b,0xd6,0x8b,0x74,0x24,0x20,0x52,0x03,0xee,0x55,0x50,0x53,0xe8,0x3d,
    0xfe,0xff,0xff,0x8b,0x4c,0x24,0x54,0x83,0xc4,0x1c,0x5f,0x03,0xc6,0x5e,0x5d,0x5b,
    0x33,0xcc,0xe8,0x65,0x3f,0x00,0x00,0x83,0xc4,0x2c,0xc3,0xcc,0xcc,0xcc,0xcc,0xcc,
    0x33,0xd2,0xf7,0x73,0x08,0x33,0xd2,0x56,0x33,0xf6,0x57,0x8b,0xc8,0x8b,0x44,0x24,
    0x0c,0x2b,0x44,0x24,0x10,0xf7,0xf1,0x8a,0x4b,0x0c,0xba,0x01,0x00,0x00,0x00,0xd3,
    0xe2,0x83,0xea,0x01,0x8b,0xf8,0x74,0x1d,0x8b,0x43,0x04,0xeb,0x03,0x8d,0x49,0x00,
    0x8d,0x0c,0x32,0xd1,0xe9,0x39,0x3c,0x88,0x76,0x04,0x8b,0xd1,0xeb,0x03,0x8d,0x71,
    0x01,0x3b,0xf2,0x72,0xeb,0x8b,0x53,0x04,0x39,0x3c,0xb2,0x8d,0x0c,0xb2,0x8b,0xc6,
    0x76,0x0a,0x83,0xe9,0x04,0x83,0xe8,0x01,0x39,0x39,0x77,0xf6,0x5f,0x5e,0xc3,0xcc,
    0x51,0x53,0x55,0x8b,0x6e,0x04,0x57,0x8b,0x3e,0x8b,0xd8,0x8b,0x46,0x08,0x57,0x50,
    0x8b,0xc5,0xe8,0x89,0xff,0xff,0xff,0x33,0xd2,0x0f,0xb7,0xc8,0x8b,0xc5,0xf7,0x73,
    0x08,0x8b,0x53,0x04,0x89,0x4c,0x24,0x14,0x0f,0xb7,0xc9,0x03,0xc9,0x03,0xc9,0x8b,
    0x14,0x0a,0x8b,0x6c,0x24,0x14,0x83,0xc4,0x08,0x0f,0xaf,0xd0,0x03,0xd7,0x89,0x16,
    0x8b,0x13,0x8b,0x0c,0x0a,0x0f,0xaf,0xc8,0x83,0x7c,0x24,0x18,0x00,0x89,0x4e,0x04,
    0x74,0x0b,0x55,0x8b,0xc3,0xe8,0x36,0xfb,0xff,0xff,0x83,0xc4,0x04,0xbf,0x00,0x00,
    0x00,0x01,0x39,0x7e,0x04,0x73,0x27,0xeb,0x07,0x8d,0xa4,0x24,0x00,0x00,0x00,0x00,
    0x8b,0x54,0x24,0x14,0xc1,0x66,0x08,0x08,0xb0,0x08,0xe8,0x31,0xf4,0xff,0xff,0x01,
    0x46,0x08,0xc1,0x66,0x04,0x08,0xc1,0x26,0x08,0x39,0x7e,0x04,0x72,0xe2,0x5f,0x66,
    0x8b,0xc5,0x5d,0x5b,0x59,0xc3,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,
    0x83,0xec,0x54,0xa1,0x04,0x90,0x41,0x00,0x33,0xc4,0x89,0x44,0x24,0x50,0x8b,0x4c,
    0x24,0x5c,0x53,0x55,0x8b,0x6c,0x24,0x68,0x33,0xdb,0x83,0xf9,0x04,0x56,0x8b,0x74,
    0x24,0x64,0x73,0x15,0x5e,0x5d,0x83,0xc8,0xff,0x5b,0x8b,0x4c,0x24,0x50,0x33,0xcc,
    0xe8,0x27,0x3e,0x00,0x00,0x83,0xc4,0x54,0xc3,0x8b,0x06,0xc1,0xe8,0x08,0x89,0x44,
    0x24,0x0c,0xc7,0x44,0x24,0x10,0x04,0x00,0x00,0x00,0x75,0x14,0x83,0xf9,0x08,0x72,
    0xd3,0x8b,0x46,0x04,0x89,0x44,0x24,0x0c,0xc7,0x44,0x24,0x10,0x08,0x00,0x00,0x00,
    0x57,0xb1,0x09,0x8d,0x7c,0x24,0x40,0xe8,0x34,0xfa,0xff,0xff,0xb1,0x0c,0x8d,0x7c,
    0x24,0x50,0xe8,0x29,0xfa,0xff,0xff,0x8b,0x4c,0x24,0x14,0x33,0xc0,0x89,0x44,0x24,
    0x1c,0x89,0x44,0x24,0x24,0x89,0x44,0x24,0x28,0x8b,0x44,0x24,0x6c,0x2b,0xc1,0x03,
    0xf1,0x83,0xf8,0x04,0x89,0x74,0x24,0x18,0x89,0x44,0x24,0x20,0x0f,0x86,0x01,0x01,
    0x00,0x00,0x8d,0x44,0x24,0x2c,0xe8,0xa5,0xf6,0xff,0xff,0xb0,0x08,0x8d,0x54,0x24,
    0x18,0xe8,0x5a,0xf3,0xff,0xff,0x8b,0xf8,0xb0,0x08,0xc1,0xe7,0x08,0xe8,0x4e,0xf3,
    0xff,0xff,0x8b,0xf0,0x0b,0xf7,0xb0,0x08,0xc1,0xe6,0x08,0xe8,0x40,0xf3,0xff,0xff,
    0x8b,0xf8,0x0b,0xfe,0xb0,0x08,0xc1,0xe7,0x08,0xe8,0x32,0xf3,0xff,0xff,0x0b,0xc7,
    0x39,0x5c,0x24,0x10,0x89,0x44,0x24,0x34,0x0f,0x86,0xa0,0x00,0x00,0x00,0x8b,0xff,
    0x8d,0x4c,0x24,0x18,0x6a,0x01,0x51,0x8d,0x74,0x24,0x34,0x8d,0x44,0x24,0x48,0xe8,
    0x5c,0xfe,0xff,0xff,0x0f,0xb7,0xc0,0x83,0xc4,0x08,0x66,0x3d,0x00,0x01,0x73,0x08,
    0x88,0x04,0x2b,0x83,0xc3,0x01,0xeb,0x6c,0x0f,0xb6,0xd0,0x8d,0x44,0x24,0x18,0x6a,
    0x01,0x83,0xc2,0x03,0x50,0x8d,0x74,0x24,0x34,0x8d,0x44,0x24,0x58,0x0f,0xb7,0xfa,
    0xe8,0x2b,0xfe,0xff,0xff,0x0f,0xb7,0xcf,0x66,0x05,0x01,0x00,0x03,0xcb,0x83,0xc4,
    0x08,0x3b,0x4c,0x24,0x10,0x0f,0xb7,0xc0,0x77,0x59,0x0f,0xb7,0xc8,0x3b,0xd9,0x72,
    0x52,0x8b,0x54,0x24,0x1c,0x8b,0x44,0x24,0x14,0x03,0xd0,0x3b,0x54,0x24,0x6c,0x77,
    0x42,0x66,0x85,0xff,0x76,0x1e,0x8b,0xc5,0x2b,0xc1,0x8d,0x9b,0x00,0x00,0x00,0x00,
    0x8a,0x0c,0x18,0x81,0xc7,0xff,0xff,0x00,0x00,0x88,0x0c,0x2b,0x83,0xc3,0x01,0x66,
    0x85,0xff,0x77,0xec,0x3b,0x5c,0x24,0x10,0x0f,0x82,0x62,0xff,0xff,0xff,0x5f,0x5e,
    0x5d,0x8b,0xc3,0x5b,0x8b,0x4c,0x24,0x50,0x33,0xcc,0xe8,0xbd,0x3c,0x00,0x00,0x83,
    0xc4,0x54,0xc3,0x8b,0x4c,0x24,0x60,0x5f,0x5e,0x5d,0x5b,0x33,0xcc,0x83,0xc8,0xff,
    0xe8,0xa7,0x3c,0x00,0x00,0x83,0xc4,0x54,0xc3,

    0x8b,0x54,0x24,0x0c,0x8b,0x4c,0x24,0x04,0x85,0xd2,0x74,0x69,0x33,0xc0,0x8a,0x44,
    0x24,0x08,0x84,0xc0,0x75,0x16,0x81,0xfa,0x00,0x01,0x00,0x00,0x72,0x0e,0x83,0x3d,
    0x4c,0x26,0x46,0x00,0x00,0x74,0x05,0xe9,0x5b,0x3c,0x00,0x00,0x57,0x8b,0xf9,0x83,
    0xfa,0x04,0x72,0x31,0xf7,0xd9,0x83,0xe1,0x03,0x74,0x0c,0x2b,0xd1,0x88,0x07,0x83,
    0xc7,0x01,0x83,0xe9,0x01,0x75,0xf6,0x8b,0xc8,0xc1,0xe0,0x08,0x03,0xc1,0x8b,0xc8,
    0xc1,0xe0,0x10,0x03,0xc1,0x8b,0xca,0x83,0xe2,0x03,0xc1,0xe9,0x02,0x74,0x06,0xf3,
    0xab,0x85,0xd2,0x74,0x0a,0x88,0x07,0x83,0xc7,0x01,0x83,0xea,0x01,0x75,0xf6,0x8b,
    0x44,0x24,0x08,0x5f,0xc3,0x8b,0x44,0x24,0x04,0xc3,

    /*INT3*/ 0xcc };



// anti DEP limitation, allocation is necessary
void *ntcompress_alloc(void *dump, int dumpsz) {
    int     pagesz;
    void    *ret;

    pagesz = (dumpsz + 4095) & (~4095); // useful for pages? mah

#ifdef WIN32
    ret = VirtualAlloc(
        NULL,
        pagesz,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_EXECUTE_READWRITE);    // write for memcpy
#else
    ret = malloc(pagesz);
    mprotect(
        ret,
        pagesz,
        PROT_EXEC | PROT_WRITE);    // write for memcpy
#endif
    memcpy(ret, dump, dumpsz);
    return(ret);
}


static  unsigned char   *ntcompress_mem = NULL;
int (__cdecl *ntcompress_30)(void *in, int insz, void *out) = NULL;
int (__cdecl *ntcompress_40)(void *in, int insz, void *out) = NULL;
//int (__cdecl *ntcompress_00)(void *in, int insz, void *out, int one) = NULL;



// lame just to save some memory because the tool doesn't free it
#define ntcompress_auto_freex   64
static int      ntcompress_auto_freen = 0;
static  void    *ntcompress_auto_free[ntcompress_auto_freex] = {NULL};



void __cdecl *ntcompress_myalloc(int size) {
    void    *ret;
    int     i;

    if(size < 0) {
        for(i = 0; i < ntcompress_auto_freex; i++) {
            if(ntcompress_auto_free[i]) {
                free(ntcompress_auto_free[i]);
                ntcompress_auto_free[i] = NULL;
            }
        }
        ntcompress_auto_freen = 0;
        return(NULL);
    }

    ret = calloc(size, 1);
    if(ntcompress_auto_freen >= ntcompress_auto_freex) ntcompress_auto_freen = 0;
    ntcompress_auto_free[ntcompress_auto_freen++] = ret;
    return(ret);
}



void __cdecl ntcompress_init(void) {
    unsigned char   *p;

    if(!ntcompress_mem) {
        ntcompress_0043a788 = calloc(/*0x806 + 0x2000*/ 0x1000, 1);

        ntcompress_mem = ntcompress_alloc(ntcompress_dump, sizeof(ntcompress_dump));

        #define PATCHIT(X,Y) *(int *)((char *)ntcompress_mem + X) = (int)(Y);
        PATCHIT(0x00000389, ntcompress_0043a788 + 0x00000000) // push 43A788
        PATCHIT(0x000003a4, ntcompress_0043a788 + 0x00000000) // push 43A788
        PATCHIT(0x000003c2, ntcompress_0043a788 + 0x00000800) // push 43AF88
        PATCHIT(0x000003e1, ntcompress_0043a788 + 0x00000800) // push 43AF88
        PATCHIT(0x00000425, ntcompress_0043a788 + 0x00000002) // mov esi, 43A78A
        PATCHIT(0x000004be, ntcompress_0043a788 + 0x00000802) // mov esi, 43AF8A
        #undef PATCHIT

        #define PATCHIT_FUNC(X,Y)   *(int *)((char *)(ntcompress_mem + (X) + 1)) = (Y) - (ntcompress_mem + (X) + 1 + 4);
        #define PATCHIT_NOP(X,Y)    memset(ntcompress_mem + (X),  0x90, Y);
        PATCHIT_NOP(0x106,  5)
        PATCHIT_NOP(0x257,  5)
        PATCHIT_NOP(0xd92,  5)
        PATCHIT_NOP(0xed0,  5)
        PATCHIT_NOP(0x103a, 5)
        PATCHIT_NOP(0x1050, 5)
        for(p = ntcompress_mem + sizeof(ntcompress_dump) - 3; p >= ntcompress_mem; p--) {
            if(!memcmp(p, "\x8b\x54\x24", 3)) break;    // alloca() like
        }
        PATCHIT_FUNC(0x170, p)
        p = (void *)ntcompress_myalloc;
        PATCHIT_FUNC(0x624, p)
        PATCHIT_FUNC(0x62c, p)
        PATCHIT_FUNC(0x954, p)
        PATCHIT_FUNC(0x95c, p)
        PATCHIT_FUNC(0xce2, p)
        #undef PATCHIT_FUNC
        #undef PATCHIT_NOP

        ntcompress_30 = (void *)(ntcompress_mem + 0x330);
        ntcompress_40 = (void *)(ntcompress_mem + 0xea0);
    }
}



void __cdecl ntcompress_free(void *buff) {
    int     i;

    if(buff) {
        for(i = 0; i < ntcompress_auto_freex; i++) {
            if(buff == ntcompress_auto_free[i]) {
                free(ntcompress_auto_free[i]);
                ntcompress_auto_free[i] = NULL;
                return;
            }
        }
        free(buff);
    } else {
        ntcompress_myalloc(-1);
    }
}



int __cdecl ntcompress_type(int first_byte) {
    return((first_byte & 0xf0) - 0x10);
}

