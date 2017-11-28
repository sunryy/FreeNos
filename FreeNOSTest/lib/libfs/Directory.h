#pragma once
#include "intel/pc/System.h"
#include "List.h"
#include "File.h"
#include "FileSystemPath.h"
#include "stdio.h"

//Maximum length of a filename.
#define DIRENT_LEN	64

//Describes an entry inside a Directory.
typedef struct Dirent{
	//Name of the file.
	char name[DIRENT_LEN]

	//type of file.
	FileType type;

	//Compares this Dirent with another Dirent instance.
	bool operator == (struct Dirent *dir){
		return strcmp(name, dir->name) == 0;
	}
}
Dirent;

//Directory File functionality.
//A Directory is a File which may have serveral child File's.Each
//child File which also is a Directory, may in turn have child File's.
//This way, a FileSystem can form a tree of File's and Directories.
class Directory :public File{
	//Ctr
	Directory();

	//Dtr
	virtual ~Directory();

	//Read directory entries.
	virtual Error read(IOBuffer & buffer, Size size, Size offset);

	//Retrieve a File storage.
	virtual File *lookup(const char *name);

	//Insert a new directory entry.
	void insert(FileType type, const char *name, ...);

	//Remove a directory entry.
	void remove(const char *name);


private:
	//Retrieve a directory entry by it's name.
	Dirent *get(const char *name);

	//List of directory entries.
	List<Dirent *> entries;
};