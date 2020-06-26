#define _CRT_SECURE_NO_WARNINGS // for time functions 
#include "Library.h"
#include "Library.h"
#include "Audiobooks.h"
#include "Books.h"
#include "Computergames.h"
#include "Users.h"

#include <ctime> // Date & Time
#include <fstream> //Read and Write from/to File

using namespace std;


Library::Library()
{
	loginSuccesfull == false;

}

Library::~Library()
{
	map<int, Library*>::iterator it;
	for (it = m_users.begin(); it != m_users.end(); ++it)
	{
		cout << "User " << it->second->m_username << " has died in a library fire." << endl;
		m_users.erase(it);
	}
	for (auto& z : m_audiobooks)
	{
		cout << "Audiobook \"" << z->m_title << "\" has burned to ashes in a library fire." << endl;
		delete z;
	}
	for (auto& y : m_books)
	{
		cout << "Book \"" << y->m_title << "\" has burned to ashes in a library fire." << endl;
		delete y;
	}
	for (auto& i : m_computergames)
	{
		cout << "Computergame \"" << i->m_title << "\" has burned to ashes in a library fire." << endl;
		delete i;
	}
	for (auto& t : m_stuff_borrowed)
	{
		delete t;
	}
}


//Adds books and stuff to the library, needs to be called right in beginning of main!
void Library::fillLib()
{
	//Add Books to library
	initializer_list<Library*> books = {new Books("Newt Scamander", "All you need to know about keeping Sentient Stick-Bugs", 1, 2, 2010),
		new Books("All Might", "Go Beyond Plus Ultra", 2, 1, 1993),
		new Books("Albert Einstein", "Cheers to the third Worldwar", 3, 10, 2012)}; //initialiserlist
	m_books.insert(books);


	//Add Computergames to library
	initializer_list<Library*> computergames = { new Computergames("EA", "Fifa 19", 1, 5, 2018),
		new Computergames("CD Project RED", "The Witcher 3: Wild Hunt", 2, 2, 2015) }; //initialiserlist
	m_computergames.insert(computergames);

	//Add Audiobooks to library
	initializer_list<Library*> audiobooks = {new Audiobooks("Monkey D. Ruffy", "Navigating the World Seas A-Z", 1, 5, 1998),
		new Audiobooks("Donald Trump", "How to become the biggest Troll of them All - Read by the Master himself", 2, 3, 2016) }; //initialiserlist
	m_audiobooks.insert(audiobooks);

	//add an admin user to the program (mainly for testing purposes)
	m_users.insert(pair<int, Library*>(0, new Users("admin", "test")));

}

//only lists Library currently not borrowed
void Library::list(multiset<Library*> type)
{
	for (auto& i : type)
	{
		if (i->m_borrowed == false && i->m_quantity != 0)
			cout << "ID:" << i->m_ID << " " << i->m_author << " - " << i->m_title << " " << "Quantity: " << i->m_quantity << "Release: " << i->m_release  << endl;
	}
}

//function called in main
void Library::borrowItem(int borrowcount)
{
	int iBuffer = 0;
	if (borrowcount < 2)
	{
		cout << "Which item would you like to borrow? " << endl;
		cout << "1. Book" << endl;
		cout << "2. Computergame" << endl;
		cout << "3. Audiobook" << endl;

		cin >> iBuffer;

		switch (iBuffer)
		{
		case 1: borrow(m_books);
			break;
		case 2: borrow(m_computergames);
			break;
		case 3: borrow(m_audiobooks);
			break;
		}
	}
	else
	{
		cout << "Sorry, you can't borrow anything more today." << endl;
	}
}

//function called in main
void Library::returnItem()
{
	int iBuffer = 0;
	cout << "Which item would you like to return? " << endl;
	cout << "1. Book" << endl;
	cout << "2. Computergame" << endl;
	cout << "3. Audiobook" << endl;

	cin >> iBuffer;

	switch (iBuffer)
	{
	case 1: m_return(m_books);
		break;
	case 2: m_return(m_computergames);
		break;
	case 3: m_return(m_audiobooks);
		break;
	};

}

void Library::adminFunct() //function to check certain variables during runtime
{
	cout << "Stuff borrowed:" << endl;
	for (auto& x : m_stuff_borrowed)
	{
		cout << "ID:" << x->m_ID << " " << x->m_author << " - " << x->m_title << " " << "Quantity: " << x->m_quantity << endl;
	}

	cout << "Users:" << endl;
	for (auto& x : m_users)
	{
		cout << "Name:" << x.second->m_username << endl;
	}
}

multiset<Library*> Library::getMultiset(string type)
{
	if (type == "book")
	{
		return m_books;
	}
	else if (type == "computergame")
	{
		return m_computergames;
	}
	else
	{
		return m_audiobooks;
	}
}


void Library::borrow(multiset<Library*> type)
{
	int iBuffer = 0;
	bool validChoice;
	cout << "Library available:" << endl;
	list(type);
	cout << "Please choose by typing in the ID" << endl;
	cin >> iBuffer;
	for (auto& i : type)
	{
		if (iBuffer == i->m_ID)
		{
			i->m_quantity--;
			if (i->m_quantity == 0)
			{
				i->m_borrowed = true;
			}
			cout << "You have successfully borrowed " << i->m_title << endl;
			m_stuff_borrowed.insert(i);
			createLog(i, "borrowed");
		}
	}
}

void Library::m_return(std::multiset<Library*> type)
{
	int iBuffer = 0;
	int iCounter = 0;
	bool validChoice;
	if (m_stuff_borrowed.size() == 0)
	{
		cout << "Nothing to be returned at the moment" << endl;
	}
	else
	{
		cout << "Books IDs:" << endl;
		list(m_stuff_borrowed); //lists all Library currently borrowed.
		cout << "Please choose by typing in the ID" << endl;
		cin >> iBuffer;
		for (auto& i : type)
		{
			if (iBuffer == i->m_ID)
			{
				i->m_quantity++;
				cout << "You have successfully returned " << i->m_title << endl;
				createLog(i, "returned");
			}
			for (auto& j : m_stuff_borrowed)
			{
				iCounter++;
				if (i->m_title == j->m_title)
				{
					m_stuff_borrowed.erase(i); //remove pointer from the vector without calling the objects destructor
					break; //if break not set, the loop will be executed one more time resulting in an exception
				}
			}
		}
	}

}


//Parameter: Current Object in borrow or return-Function
void Library::createLog(Library* const &i, std::string action)
{
	//Getting todays date and converting it to a string
	time_t rawtime;
	struct tm* timeinfo;
	char dateBuffer[20];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(dateBuffer, sizeof(dateBuffer), "%d-%m-%y", timeinfo);

	std::string date(dateBuffer); //Convert current date to String
	
	std::string fileLocation = "C:\\Users\\PiaDu\\OneDrive\\Documents\\FH KE\\Zweites Semester\\Programmieren 2\\Library\\"; //replace with own filelocation

	std::string logName = (fileLocation + date + "-Ausleihe.txt");

	//Opening/Creating the log-File
	std::ofstream file;
	file.open(logName, std::ios_base::app); //open file and set write mode to append
	if (file.is_open())
	{
		//get current time:
		char timeBuffer[20];
		struct tm* sTm;
		time_t now = time(0);
		sTm = gmtime(&now);
		strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", sTm);
		//write current time in logfile
		file << timeBuffer;
		//write what was borrowed/returned in logfile
		file << " " + m_currentUser + " " + action + ":"; //HH:MM:SS user returned/borrowed:
		file << "\nType: ";
		file << i->m_type;
		file << "\nAuthor: ";
		file << i->m_author;
		file << "\nTitel: ";
		file << i->m_title + "\n";

		file.close(); //close ofstream

	}
	else
	{
		cout << "Unable to open Log-File.";
	}	

}

bool Library::login()
{
	std::string username;
	std::string password;
	while (loginSuccesfull == false)
	{
		cout << "Please enter your username: " << endl;
		cin >> username;
		cout << "Please enter your password: " << endl;
		cin >> password;

		for (auto x : m_users)
		{
			if ((x.second->m_username == username) && (x.second->m_password == password))
			{
				cout << "Welcome back " << username << endl;
				loginSuccesfull = true;
				m_currentUser = username;
				break;
			}
		}
	}
	return loginSuccesfull;
}

void Library::createUsers()
{
	bool usernameTaken = false;
	std::string username;
	std::string password;

	do
	{
		cout << "Please choose your username: " << endl;
		cin >> username;
		cout << "Please enter a password: " << endl;
		cin >> password;
		map<int, Library*>::iterator it;
		for (it = m_users.begin(); it != m_users.end(); it++)
		{
			if (username == it->second->m_username)
			{
				cout << "Sorry, this username is taken." << endl;
				usernameTaken == true; //sets flag in case username is taken
			}
			else
			{
				m_users.insert(pair<int, Library*>(UserCount, new Users(username, password)));
				++UserCount;
				usernameTaken == false;
				break; //otherwise it will loop through one more time as array is now bigger
			}
		}

	} while (usernameTaken == true);
}

bool Library::logout()
{
	loginSuccesfull = false;
	return loginSuccesfull;
}

