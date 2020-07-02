#include "Books.h"
Books::Books(int release, std::string author, std::string title, int ID, int quantity)
{
	m_type = "Book";
	m_author = author;
	m_title = title;
	m_ID = ID;
	m_borrowed = false;
	m_quantity = quantity;
	m_release = release;

	std::cout << "The " << m_type << " \"" << m_title << "\" by " << m_author << " has been added to the library." << std::endl;

}

Books::~Books()
{
	std::cout << "The " << m_type << " \"" << m_title << "\" by " << m_author << " has been lost to the library fire." << std::endl;
}