#include "Computergames.h"
Computergames::Computergames(std::string author, std::string title, int ID, int quantity, int release)
{
	m_type = "Computergame";
	m_borrowed = false;
	m_ID = ID;
	m_author = author;
	m_title = title;
	m_quantity = quantity;
	m_release = release;

	std::cout << "The " << m_type << " \"" << m_title << "\" by " << m_author << " has been added to the library." << std::endl;

}
Computergames::~Computergames()
{
	std::cout << "The " << m_type << " \"" << m_title << "\" by " << m_author << " has been lost to the library fire." << std::endl;
}
