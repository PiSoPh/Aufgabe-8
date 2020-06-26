#pragma once
#include "Library.h"
#include <iostream>
class Computergames :
    public Library
{
public:
	Computergames(std::string author, std::string title, int ID, int quantity, int release);
	~Computergames();
	using Library::m_type;
	using Library::m_borrowed;
	using Library::m_ID;
	using Library::m_release;
private:
	using Library::m_author;
	using Library::m_title;
	using Library::m_quantity;

};

