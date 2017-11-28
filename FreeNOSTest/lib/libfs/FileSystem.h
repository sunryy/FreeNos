#pragma once
#include "intel/pc/System.h"
#include "ChannelServer.h"
#include "Vector.h"
#include "Directory.h"
#include "Device.h"
#include "File.h"
#include "FileCache.h"
#include "FileSystemPath.h"
#include "FileSystemMessage.h"
#include "FileSystemRequest.h"

//Abstract filesystem class.
class FileSystem :public ChannelServer<FileSystem, FileSystemMessage>
{
	//Ctr
	FileSystem(const char *path);

	/**
	* Destructor function.
	*/
	virtual ~FileSystem();

	/**
	* Get mount path
	*
	* @return Mount path of the filesystem
	*/
	const char * getMountPath() const;

	/**
	* Get root directory.
	*
	* @return Root directory pointer
	*/
	Directory * getRoot();

	/**
	* @brief Mount the FileSystem.
	*
	* This function is responsible for mounting the
	* FileSystem.
	*
	* @return True if mounted successfully, false otherwise.
	*/
	Error mount();

	/**
	* Register a new File.
	*
	* @param file File object pointer.
	* @param path The path for the File.
	* @return Error code.
	*/
	Error registerFile(File *file, const char *path, ...);

	/**
	* Register a new File with variable arguments.
	*
	* @param file File object pointer.
	* @param path The path for the File.
	* @param args Variable argument list.
	* @return Error code.
	*/
	Error registerFile(File *file, const char *path, va_list args);

	/**
	* @brief Create a new file.
	* @param type Describes the type of file to create.
	* @param deviceID Optionally specifies the device identities to create.
	* @return Pointer to a new File on success or ZERO on failure.
	*/
	virtual File * createFile(FileType type, DeviceID deviceID);

	/**
	* Inserts a file into the in-memory filesystem tree.
	*
	* @param file File to insert.
	* @param pathFormat Formatted full path to the file to insert.
	* @param ... Argument list.
	* @return Pointer to the newly created FileCache, or NULL on failure.
	*/
	FileCache * insertFileCache(File *file, const char *pathFormat, ...);

	/**
	* Inserts a file into the in-memory filesystem tree.
	*
	* @param file File to insert.
	* @param pathFormat Formatted full path to the file to insert.
	* @param args Argument list.
	* @return Pointer to the newly created FileCache, or NULL on failure.
	*/
	FileCache * insertFileCache(File *file, const char *pathFormat, va_list args);

	/**
	* @brief Process an incoming filesystem request using a path.
	*
	* This message handler is responsible for processing any
	* kind of FileSystemMessages which have an FileSystemAction using
	* the path field, such as OpenFile.
	*
	* @param msg Incoming request message.
	* @see FileSystemMessage
	* @see FileSystemAction
	*/
	void pathHandler(FileSystemMessage *msg);

	/**
	* Called when a sleep timeout is expired
	*
	* This function does a retry on all FileSystemRequests
	*/
	virtual void timeout();

	/**
	* Retry any pending requests
	*
	* @return True if retry is needed again, false if all requests processed
	*/
	bool retryRequests();

	protected:
		//Process a FileSystemRequest.
		Error processRequest(FileSystemRequest *req);

		/**
		* @brief Change the filesystem root directory.
		*
		* This function set the root member to the given
		* Directory pointer. Additionally, it inserts '/.' and '/..'
		* references to the file cache.
		*
		* @param newRoot A Directory pointer to set as the new root.
		*
		* @see root
		* @see insertFileCache
		*/
		void setRoot(Directory *newRoot);

		/**
		* @brief Retrieve a File from storage.
		*
		* This function is responsible for walking the
		* given FileSystemPath, retrieving each uncached File into
		* the FileCache, and returning a pointer to corresponding FileCache
		* of the last entry in the given path.
		*
		* @param path A path to lookup from storage.
		* @return Pointer to a FileCache on success, ZERO otherwise.
		*/
		FileCache * lookupFile(FileSystemPath *path);

		/**
		* Search the cache for an entry.
		* @param path Full path of the file to find.
		* @return Pointer to FileCache object on success, NULL on failure.
		*/
		FileCache * findFileCache(char *path);

		/**
		* Search the cache for an entry.
		* @param path Full path of the file to find.
		* @return Pointer to FileCache object on success, NULL on failure.
		*/
		FileCache * findFileCache(String *path);

		/**
		* Search the cache for an entry.
		* @param path Full path of the file to find.
		* @return Pointer to FileCache object on success, NULL on failure.
		*/
		FileCache * findFileCache(FileSystemPath *p);

		/**
		* Process a cache hit.
		* @param cache FileCache object which has just been referenced.
		* @return FileCache object pointer.
		*/
		virtual FileCache * cacheHit(FileCache *cache);

		/**
		* Cleans up the entire file cache (except opened file caches and root).
		* @param cache Input FileCache object. ZERO to clean up all from root.
		*/
		void clearFileCache(FileCache *cache = ZERO);

		//Root entry of the filesystem tree.
		FileCache *m_root;

		//Mount point.
		const char *m_mountPath;

		//Contains ongoing requests.
		List<FileSystemRequest *> *m_requests;
};

