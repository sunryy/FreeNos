#pragma once
namespace Character{
	//Test for a decimal digit.
	inline bool isDigit(char c){
		return c >= '0' && c <= '9';
	}

	//Test for a wildcard character.
	inline bool isWildcard(char c){
		return c == '*';
	}

	//Test for a lowercase letter.
	inline bool isLower(char c){
		return (c) >= 'a' && (c) <= 'z';
	}

	//Test for an uppercase letter.
	inline bool isUpper(char c){
		return (c) >= 'A' && (c) <= 'Z';
	}

	//Test for an alphabetic character.
	inline bool isAlpha(char c){
		return isUpper(c) || isLower(c);
	}

	//Test for an alphanumeric character.
	inline bool isAlnum(char c){
		return isAlpha(c) || isDigit(c);
	}

	//Test for a blank character.
	inline bool isBlank(char c){
		return (c) == ' ' || (c) == '\t';
	}

	//Test for a white-space character.
	inline bool isWhitespace(char c){
		return (c) == '\v' || (c) == '\f' ||
			(c) == '\r' || (c) == '\n' || isBlank(c);
	}

	//Convert the letter c to lowercase.
	inline char lower(char c){
		return (c >= 'A' && c <= 'Z') ? (c + 32) : (c);
	}

	//COnverts the letter c to uppercase.
	inline char upper(char c){
		return (c >= 'a' && c <= 'z') ? (c - 32) : (c);
	}

}