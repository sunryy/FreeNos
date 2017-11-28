#include "intel/pc/System.h"
#include "MemoryContext.h"
#include "Core.h"
#include "IO.h"

IO::IO()
{
	m_base = 0;
}

uint IO::getBase() const
{
	return m_base;
}

void IO::setBase(uint base)
{
	m_base = base;
}

IO::Result IO::map(Address phys, Size size, Memory::Access access)
{
	m_range.virt = 0;
	m_range.phys = phys;
	m_range.access = access;
	m_range.size = size;

	if (!isKernel)
	{
		if (VMCtl(SELF, Map, &m_range) != API::Success)
		{
			return MapFailure;
		}
		
	}
	else
	{
		m_range.access &= ~Memory::User;

		MemoryContext *ctx = MemoryContext::getCurrent();
		if (!ctx)
		{
			return MapFailure;
		}
		if (ctx->findFree(size, MemoryMap::kernelPrivate, &m_range.virt)!=MemoryContext::Success)
		{
			return OutOfMemory;
		}
		if (ctx->map(m_range.virt, phys, m_range.access)!= MemoryContext::Success)
		{
			return MapFailure;
		}
	}
	m_base = m_range.virt;
	return Success;
}

IO::Result IO::unmap()
{
	if (!isKernel)
	{
		if (VMCtl(SELF, UnMap, &m_range) != API::Success)
		{
			return MapFailure;
		}
		
	}
	else
	{
		MemoryContext *ctx = MemoryContext::getCurrent();
		if (!ctx)
		{
			return MapFailure;
		}
		if (ctx->unmapRange(&m_range)!= MemoryContext:Success)
		{
			return MapFailure;
		}

	}
	return Success;
}