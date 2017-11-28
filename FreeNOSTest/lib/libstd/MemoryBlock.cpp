#include "MemoryBlock.h"

#include "Macros.h"

void* MemoryBlock::set(void *dest, int ch, unsigned count)
{
	char* temp;
	for (temp = (char*)dest; count != 0; count--)
	{
		*temp++ = ch;
	}
	return (dest);
}

Size MemoryBlock::copy(void* dest, const void* src, Size count){
	const char* sp = (const char*)src;
	char* dp = (char*)dest;
	for (Size i = count; i != 0; i--)
	{
		*dp++ = *sp++;
	}
	return (count);
}

Size MemoryBlock::copy(char* dst, char* src, Size count){
	char* d = dst;
	const char* s = src;
	unsigned n = count;

	//Copy as many bytes as will fit
	if (n != 0)
	{
		while (--n != 0)
		{
			if ((*d++ = *s++) == '\0')
			{
				break;
			}
		}
	}
	//Not enough room in dst, add NUL and traverse rest of src
	if (n==0)
	{
		if (count!=0)
		{
			*d = '\0';
		}
		while (*s++)
		{
			;
		}
	}
	return (s - src - 1);
}

bool MemoryBlock::compare(const char* p1, const char* p2, Size count){
	for (Size i = count; i > 0 || !count; i--)
	{
		if (!count && (*p1 == ZERO || *p2 ==ZERO))
		{
			break;
		}
		if (*p1 != *p2)
			break;
		p1++, p2++;
	}
	return (*p1 == *p2);
}