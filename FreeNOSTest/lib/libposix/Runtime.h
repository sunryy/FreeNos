#pragma once

#include <Macros.h>
#include <Types.h>
#include <Vector.h>
#include <String.h>
#include <ChannelClient.h>
#include "FileSystemMount.h"
#include "FIleDescriptor.h"

//C(++) program entry point.
int main(int argc, char** argv);

//Retrieve the ProcessID of the FileSystemMount for the given path.
ProcessID findMount(const char *path);

//Lookup the ProcessID of a FileSystemMount by a filedescriptor number.
ProcessID findMount(int files);

void refreshMounts;

//FileDescriptors table.
Vector<FileDescriptor> *getFiles();

//Get mounts table.
FileSystemMount *getMounts();

//Get Current directory String
String *getCurrentDirectory();