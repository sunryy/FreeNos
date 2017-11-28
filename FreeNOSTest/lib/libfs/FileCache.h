#pragma once

#include "HashTable.h"
#include "File.h"
//Cached in-memory file.
typedef struct FileCache
{
	//Ctr
	FileCache(File *f, const char *n, FileCache *p)
	:file(f), valid(true), parent(p)
	{
		name = n;
		if (p && p != this)
		{
			p->entries.insert(name, this);
		}
	}

	//Comparision operator.
	bool operator == (FileCache *fc)
	{
		return file == fc->file;
	}

	//File pointer
	File *file;

	//Our name.
	String name;

	//Contains childs.
	HashTable<String, FileCache *> entries;

	//Is this entry still valid?.
	bool valid;

	//Parent
	FileCache *parent;
};

