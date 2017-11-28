#include "LinnFile.h"

#include "System.h"
#include "string.h"



LinnFile::LinnFile(LinnFileSystem *f, LinnInode *i)
: fs(f), inode(i)
{
	m_size = inode->size;
	m_access = inode->mode;
}

LinnFile::~LinnFile()
{
}

Error LinnFile::read(IOBuffer & buffer, Size size, Size offset)
{
	LinnSuperBlock *sb;
	Size bytes = 0, blockNr = 0;
	u64 storageOffset, copyOffset = offset;
	u8 *block;
	Size total = 0;
	Error e;

#warning very inefficient.blocks are not cached from storage and thrown away each time.

	/* Initialize variables. */
	sb = fs->getSuperBlock();
	block = new u8[sb->blockSize];

	/* Skip ahead blocks. */
	while ((sb->blockSize * (blockNr + 1)) <= copyOffset)
	{
		blockNr++;
	}
	/* Adjust the copy offset within this block. */
	copyOffset -= sb->blockSize * blockNr;

	/* Loop all blocks. */
	while (blockNr < LINN_INODE_NUM_BLOCKS(sb, inode) &&
		total < size && inode->size - (offset + total) > 0)
	{
		/* Calculate the offset in storage for this block. */
		storageOffset = fs->getOffset(inode, blockNr);

		/* Fetch the next block. */
		if (fs->getStorage()->read(storageOffset, block, sb->blockSize) < 0)
		{
			delete block;
			return EIO;
		}
		/* Calculate the number of bytes to copy. */
		bytes = sb->blockSize - copyOffset;

		/* Respect the inode size. */
		if (bytes > inode->size - (offset + total))
		{
			bytes = inode->size - (offset + total);
		}
		/* Respect the remote process buffer. */
		if (bytes > size - total)
		{
			bytes = size - total;
		}
		/* Copy into the buffer. */
		if ((e = buffer.write(block + copyOffset, bytes, total)) < 0)
		{
			delete block;
			return e;
		}
		/* Update state. */
		total += bytes;
		copyOffset = 0;
		blockNr++;
	}
	/* Success. */
	delete block;
	return (Error)total;
}
