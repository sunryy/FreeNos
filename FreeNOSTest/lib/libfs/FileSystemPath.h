#pragma once
#include "List.h"
#include "ListIterator.h"
#include "Types.h"
#include "String.h"
#include "string.h"

//Maximum length of a filesystem path.
#define PATHLEN 64

//The default FileSystemPath separator.
#define DEFAULT_SEPARATOR '/'

//Shortcut to the separator field.
#define SEPARATOR(x)	\
	(this->separator == (x))

//Test for an End of Line.
#define EOL(s, x) \
	((x) == (s) + length - 1)

//Simple filesystem path parser.
class FileSystemPath{
public:
	//Empty constructor.
	FileSystemPath() :fullPath(ZERO), parentPath(ZERO)
	{

	}

	FileSystemPath(char *path, char separator = DEFAULT_SEPARATOR)
		:fullPath(ZERO), fullLength(ZERO), parentPath(ZERO)
	{
		parse(path, separator);
	}

	/**
	* Constructor using a String.
	* @param s String containing the path to parse.
	* @param separator Pathname separator.
	*/
	FileSystemPath(String *s, char separator = DEFAULT_SEPARATOR)
		: fullPath(ZERO), fullLength(ZERO), parentPath(ZERO)
	{
		parse((char *)**s, separator);
	}

	//Dtr
	~FileSystemPath()
	{
		for (ListIterator<String *> i(path); i.hasCurrent(); i++)
		{
			delete i.current();
		}
		path.clear();
		if (parentPath) 
		{
			delete parentPath;
		}

		if (fullPath)
		{
			delete fullPath;
		}
		
	}


	//Parses a given character string as the path.
	void parse(char *p, char sep = DEFAULT_SEPARATOR)
	{
		const char *cur = p;
		char *parentStr = ZERO;

		//Skip heading separators.
		while (*cur && *cur==sep)
		{
			cur++;
		}
		//Save parameters.
		p = (char *)cur;
		separator = sep;
		fullLength = strlen((char *)cur);
		fullPath = new String(cur);
		String str(p);

		//Split the path into parts.
		List<String> parts = str.split(sep);
		for (ListIterator<String> i(parts); i.hasCurrent(); i++)
		{
			path.append(new String(i.current()));
		}
		//Create parent , if any.
		if (path.head() && path.head()->next)
		{
			//Allocate buffer.
			parentStr = new char[strlen(p)];
			memset(parentStr, 0, strlen(p));

			//Constrcut parent path.
			for (List<String *>::Node *l = path.head(); l && l->next; l = l->next)
			{
				strcat(parentStr, **l->data);
				if (l->next && l->next->next)
				{
					strncat(parentStr, &separator, 1);
				}
			}
			//Save the path, thn release buffer.
			parentPath = new String(parentStr);
			delete parentStr;
		}
	}

	/**
	* Retrieve the full path of our parent.
	* @return Path of our parent.
	*/
	String * parent()
	{
		return parentPath;
	}

	/**
	* The name of the last element in the path.
	* @return Name of the base.
	*/
	String * base()
	{
		return path.last();
	}

	/**
	* Get the full path as a String instance.
	* @return String instance.
	*/
	String * full()
	{
		return fullPath;
	}

	/**
	* Returns a List of separate path elements.
	* @return Pointer to a List.
	*/
	List<String *> * split()
	{
		return &path;
	}

	/**
	* Get Length of our full path.
	* @return Length.
	*/
	Size length()
	{
		return fullLength;
	}

private:
	//The path split in pieces.
	List<String *> path;

	//Full input path.
	String *fullPath;

	//Full length of the given path.
	Size fullLength;

	//Full path to our parent.
	String *parentPath;

	//Separator character.
	char separator;
};