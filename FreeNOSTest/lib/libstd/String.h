#include "Types.h"
#include "Macros.h"
#include "Assert.h"
#include "Sequence.h"
#include "List.h"

//Default maximum length of a String's value.
#define STRING_DEFAULT_SIZE 64

//Abstraction of strings.
class String :public Seuence<char>
{
public:
	//Default constructor.
	//Constructs an empty string with the default size.
	String();

	//Copy constructor.
	String(const String& str);

	//Constructor.
	String(char *s, bool copy = true);

	//Constant constructor.
	String(const char* s, bool copy = false);

	//Signed integer constructor.
	//Creates a String with the textual representation of the given signed integer.
	String(int number);

	//Destructor.
	virtual ~String();

	//Calculates the length of the String.
	virtual Size size() const;

	//number of characters in the string.
	virtual Size count() const;

	//Same as count().
	Size length() const;

	//Get the length of the given character string.
	static Size length(char *str);

	//Get the length of a constant character string.
	static Size length(const char* str);

	//Change the size of the String buffer.
	virtual bool resize(Size size);

	//Make sure at least given number of bytes available.
	virtual bool reserve(Size count);

	//Returns the item at the given position.
	virtual  const char* get(Size position) const;

	//Returns a reference to the item at the given position.
	//Note that this function does not perform bounds checking.
	//Positon must be a valid index.
	virtual const char& at(Size position) const;

	//Return value at the given position.
	virtual const char value(Size position) const;

	//Check if the given character occurs in the String.
	virtual bool contains(char character) const;

	//Tests if this String starts with specified prefix.
	bool startsWith(String& prefix) const;

	//Test if this String starts with the specified prefix.
	bool startsWith(const char* prefix) const;

	//Tests if this String ends with the specified suffix.
	bool endsWith(String& suffix) const;
	bool endsWith(const char* suffix) const;

	//Compares this String to the given String.
	virtual int compareTo(const String& str) const;

	//Compare with another String.
	virtual int compareTo(const String& str, 
						  bool caseSensitive = true)const;

	//Compare with a character string.
	virtual int compareTo(const char* str, 
						  bool caseSensitive = true,
						  Size count = 0) const;

	//Alias for compareTo().
	virtual bool equals(const String& str) const;

	//Matches the String against a mask.
	bool match(const char* mask) const;

	//Returns a new String that contains a copy of this String,
	//starting from index (inclusive), and copies at most size characters.
	String substring(Size index, Size size = 0);

	//split the String into parts separated by a delimiter.
	List<String> split(char delimiter);

	//Split the String into parts separated by a delimiter.
	List<String> split(const String& delimiter);

	//Convert the String to a signed long integer.
	long toLong(Number::Base base = Number::Dec);

	//Pad line with trailing whitespace.
	//This function ensures the last line inside the String
	//is at least the given length in characters, by appending
	//extra whitespace at the end of the line.
	String& pad(Size length);

	//Remove leading and trailing whitespace from the String.
	String& trim();

	//Convert all Characters to lower case.
	String& lower();

	//Convert all Characters to upper case.
	String& upper();

	//Set text-representation of a signed number.
	Size set(long number, Number::Base base = Number::Dec, char* string = ZERO);

	//Set text-representation of an unsigned number.
	Size setUnsigned(ulong number, 
					 Number::Base base = Number::Dec,
					 char* string = ZERO,
					 bool sign =false);

	//Assignment operator.
	void operator = (const char* str);

	//Assignment operator.
	void operator = (const String& str);
	
	//Comparision operator.
	bool operator == (const String& str) const;

	//Inequal operator.
	bool operator != (const String& str) const;

	//Dereference operator (read-only).
	const char* operator*()const;

	//Dereference operator.
	char* operator*();

	//Append character string to the String.
	String & operator <<(const char* str);

	//Append String to another String.
	String& operator <<(const String& str);

	//Append the given number as text to the String 
	String& operator << (long number);

	//Change the default number format representation.
	String& operator << (Number::Base format);

	private:
		//Current value of the String.
		char* m_string;
		//Size of the string buffer, including any NULL byte(s) at the end.
		Size m_size;

		//Length of the string text, excluding NULL byte(s) at the end.
		Size m_count;

		//True if the string buffer is a deep copy, false otherwise.
		bool m_allocated;

		//Number foromat to use for convertions.
		Number::Base m_base;


};