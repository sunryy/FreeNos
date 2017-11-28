#include "String.h"
#include "stdlib.h"

extern C void itoa(char *buffer, int divisor, int number){
	String s;
	Number::Base base = Number::Dec;

	switch (divisor)
	{
	case 10: base = Number::Dec; break;
	case 16: base = Number::Hex; break;
	}

	s.set(number, base, buffer);
}