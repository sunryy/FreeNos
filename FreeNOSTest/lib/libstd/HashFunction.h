#pragma once
#include "Types.h"
#include "String.h"

//Prime number used by FNV hashing.
#define FNV_PRIME 16777619

//Initial value of the FNV internal state.
#define FNV_INIT 0x811c9dc5

//Compute a hash using the FNV algorithm.
Size hash(const String &key, Size mod);

Size hash(int key, Size mod);