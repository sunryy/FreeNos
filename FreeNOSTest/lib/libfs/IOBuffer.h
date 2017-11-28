#include "intel/pc/System.h"
#include "Types.h"
#include "FileSystemMessage.h"

//Abstract Input/Output buffer.
class IOBuffer
{
public:
	//Ctr
	IOBuffer(const FileSystemMessage *msg);

	//dtr
	~IOBuffer();

	//Get byte count.
	Size getCount() const;

	/**
	* Get filesystem message.
	*
	* @return FileSystemMessage pointer.
	*/
	const FileSystemMessage * getMessage() const;

	/**
	* Get raw buffer.
	*
	* @return Buffer pointer.
	*/
	const u8 * getBuffer() const;

	/**
	* @brief Read bytes from the I/O buffer.
	*
	* @param buffer Copy bytes from the I/O buffer to this memory address.
	* @param size Number of bytes to copy.
	* @param offset The offset inside the I/O buffer to start reading.
	* @return Number of bytes read on success, and error code on failure.
	*/
	Error read(void *buffer, Size size, Size offset = ZERO) const;

	/**
	* @brief Write bytes to the I/O buffer.
	*
	* @param buffer Contains the bytes to write.
	* @param size Number of bytes to write.
	* @param offset The offset inside the I/O buffer to start writing.
	* @return Number of bytes written on success, and error code on failure.
	*/
	Error write(void *buffer, Size size, Size offset = ZERO) const;

	/**
	* @brief Buffered read bytes from message to the I/O buffer.
	*
	* @return Error code.
	*/
	Error bufferedRead();

	/**
	* @brief Buffered write bytes to the I/O buffer.
	*
	* @param buffer Contains the bytes to write.
	* @param size Number of bytes to write.
	* @param offset The offset inside the I/O buffer to start writing.
	* @return Number of bytes written on success, and error code on failure.
	*/
	Error bufferedWrite(void *buffer, Size size);

	/**
	* Flush write buffers.
	*
	* @return Error code.
	*/
	Error flush();

	/**
	* Byte index operator.
	*
	* @return Byte value at the given index or 0 if index is invalid.
	*/
	u8 operator[] (Size index);

private:

	//Current request being processed.
	const FileSystemMessage *m_message;

	//Buffer for storing temporary data.
	u8 * m_buffer;
	//Buffer size.
	Size m_size;

	//Bytes written to the buffer.
	Size m_count;
};