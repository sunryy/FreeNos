#include "HashFunction.h"

#include "Assert.h"

Size hash(const String &key, Size mod)
{
	Size ret = FNV_INIT;
	Size size = key.length();

	assertRead(key);
	assert(mod > 0);
	for (Size i = 0; i < size; i++)
	{
		ret *= FNV_PRIME;
		ret ^= key[i];
	}
	return (ret % mod);
}

Size hash(int key, Size mod){
	Size ret = FNV_INIT;
	assert(mod > 0);

	for (Size i = 0; i < 4; i++)
	{
		ret *= FNV_PRIME;
		ret ^= (((uint)key) >> (i * 8)) & 0xff;
	}
	return (ret % mod);
}


