#include "Game/File.h"

File::File()
    : state(2)
{
    fileSize = 0;
    fileBuffer = 0;
    readPos = 0;
}

File::~File()
{
    fileBuffer = 0;
    state = 2;
    readPos = 0;
    fileSize = 0;
}
