#pragma once
#include <iostream>
#include "Library.h"
class Books :
    public Library
{
public:
	Books(int release, std::string author, std::string title, int ID, int quantity);
	~Books();
private:
	using Library::m_type;
	using Library::m_borrowed;
	using Library::m_ID;
	using Library::m_author;
	using Library::m_title;
	using Library::m_quantity;
	using Library::m_release;
};

