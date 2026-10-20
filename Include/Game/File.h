#pragma once

#include "types.h"
#include <nn/fs/fs_FileStream.h>

class File
{
public:
    u8 state; //+0
    nn::fs::FileStream stream; //+4
    u32 fileSize; //+0x20
    u8 *fileBuffer; //+0x24
    u32 readPos; //+0x28

    File();
    ~File();
};
