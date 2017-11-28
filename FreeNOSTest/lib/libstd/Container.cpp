#include "Container.h"


Container::Container()
{
}

Container::~Container()
{
}

bool Container::isEmpty()
{
	return count() == 0;
}

bool Container::reserve(Size size)
{
	if (this->size() > size)
	{
		return true;
	}
	return resize(size);
}

bool Container::shrink(Size size){
	return resize(this->size() - size);
}

Size Container::squeeze(){
	return size();
}

bool Container::resize(Size size){
	return false;
}

