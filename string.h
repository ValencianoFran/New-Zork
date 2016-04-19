#ifndef _STRING__
#define _STRING__

#include<string.h>
#include<stdio.h>
#include"vector.h"

class String
{
private:

	char* my_string = nullptr;
	unsigned int max_size = 0;// = strlen(my_string) + 1;

public:

	String();
	String(const char* str);
	String(const String& other);
	unsigned int lenght() const;
	char* c_str() const;
	bool empty() const;

	bool operator==(const String &other) const;
	bool operator==(const char* string) const;

	//bool operator==(const char*) const;
	void operator=(const String& other);
	void operator=(const char* other);
	bool operator!=(const char* other) const;
	bool operator!=(const String& other) const;
	void operator+=(const String& other);
	String operator+(const String& other);
	char return_word(const int& number) const;
	void tolower_method();
	int const spaces() const;
	//void Token(String &str, Vector<String> &strings);
	void String::TokenizeString(char*, Vector<String>&);
	~String();
};




#endif