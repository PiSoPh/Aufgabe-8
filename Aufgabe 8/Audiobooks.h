#pragma once
#include <iostream>
#include "Library.h"
class Audiobooks :
    public Library
{
public:
	Audiobooks(std::string author, std::string title, int ID, int quantity, int release);
	~Audiobooks();
	using Library::m_type;
	using Library::m_borrowed;
	using Library::m_ID;
	using Library::m_release;

private:
	using Library::m_author;
	using Library::m_title;
	using Library::m_quantity;
};

