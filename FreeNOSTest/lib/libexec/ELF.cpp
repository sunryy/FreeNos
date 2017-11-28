#include "ELF.h"

#include "intel/pc/System.h"
#include "unistd.h"
#include "fcntl.h"
#include "string.h"
#include "errno.h"
#include "sys/types.h"


ELF::ELF(u8 *image, Size size)
:ExecutableFormat(image, size)
{

}

ELF::~ELF(){

}

ELF::Result ELF::detect(u8 *program, Size size, ExecutableFormat **fmt)
{
	ELFHeader *header = (ELFHeader *)program;

	/* Verify ELF magic. */
	if (header->ident[ELF_INDEX_MAGIC0] == ELF_MAGIC0 &&
		header->ident[ELF_INDEX_MAGIC1] == ELF_MAGIC1 &&
		header->ident[ELF_INDEX_MAGIC2] == ELF_MAGIC2 &&
		header->ident[ELF_INDEX_MAGIC3] == ELF_MAGIC3)
	{
		/* Only accept current, 32-bit ELF executable programs. */
		if (header->ident[ELF_INDEX_CLASS] == ELF_CLASS_32 &&
			header->version == ELF_VERSION_CURRENT &&
			header->type == ELF_TYPE_EXEC)
		{
			(*fmt) = new ELF(program, size);
			return Success;
		}
	}
	return InvalidFormat;
}

ELF::Result ELF::regions(ELF::Region *regions, Size *count)
{
	ELFSegment *segments;
	ELFHeader *header = (ELFHeader *)m_image;
	Size max = *count, num = header->programHeaderEntryCount, c = 0;

	/* Must be of the same sizes. */
	if (!(header->programHeaderEntrySize == sizeof(ELFSegment) &&
		header->programHeaderEntryCount < 16))
	{
		return InvalidFormat;
	}
	/* Point to the program segments. */
	segments = (ELFSegment *)(m_image + header->programHeaderOffset);
	(*count) = 0;

	/* Fill in the memory regions. */
	for (Size i = 0; i < max && i < num; i++)
	{
		/* We are only interested in loadable segments. */
		if (segments[i].type != ELF_SEGMENT_LOAD)
			continue;

		regions[c].virt = segments[i].virtualAddress;
		regions[c].size = segments[i].memorySize;
		regions[c].access = Memory::User | Memory::Readable | Memory::Writable;
		regions[c].data = new u8[segments[i].memorySize];

		/* Read segment contents from file. */
		MemoryBlock::copy(regions[c].data, m_image + segments[i].offset,
			segments[i].fileSize);

		/* Nulify remaining space. */
		if (segments[i].memorySize > segments[i].fileSize)
		{
			memset(regions[c].data + segments[i].fileSize, 0,
				segments[i].memorySize - segments[i].fileSize);
		}
		c++;
	}
	/* All done. */
	(*count) = c;
	return Success;
}

ELF::Result ELF::entry(Address *entry)
{
	ELFHeader *header = (ELFHeader *)m_image;
	*entry = header->entry;
	return Success;
}
