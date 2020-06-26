#pragma once
#include <map>
#include <vector>
#include <set>
#include <iostream>
class Library
{
public:
	Library();
	~Library();

	//Variables for derivative Classes:
	std::string m_type; //Type of Publication, inherited by Books, Audiobooks and Computergames
	bool m_borrowed; //Flag to show if book, audiobook or computergame is still available
	int m_ID; //needed to borrow and return items
	std::string m_author;
	std::string m_title;
	int m_quantity;
	int m_release; //year the item has been released
	std::multiset<Library*> m_books; //Collection of all books
	std::multiset<Library*> m_audiobooks; //Collection of all Audiobooks
	std::multiset<Library*> m_computergames; //Collection of all Computergames
	std::multiset<Library*> m_stuff_borrowed; //Vector of every item currently borrowed
	void createLog(Library* const& i, std::string action);

	//Variables for User Management:
	bool loginSuccesfull;
	std::map<int, Library*> m_users; //map for usermanagement first = unique ID, second = User-Object
	std::string m_username;
	std::string m_password;
	std::string m_currentUser;
	int UserCount = 1;
	bool login(); //for returning customers
	void createUsers(); //for new customers
	bool logout();


	//Functions for Librarymanagement
	void fillLib(); //adds books and stuff to the library, needs to be called by main right at the beginning
	void list(std::multiset<Library*> type);
	void borrowItem(int borrowcount); //called in main
	void returnItem();
	void adminFunct();
	std::multiset<Library*> getMultiset(std::string type);


private:
	void borrow(std::multiset<Library*> type);
	void m_return(std::multiset<Library*> type);
};

