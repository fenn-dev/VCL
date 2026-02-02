#pragma once
#include "VCL_TYPES.h"

extern void* GetStdHandle(w32 nStdHandle);
extern int   WriteFile(void* hFile, const void* lpBuffer, w32 nBytes, w32* lpWritten, void* lpOverlapped);
extern void  ExitProcess(w32 uExitCode);

#define VNL_STDOUT (w32)-11