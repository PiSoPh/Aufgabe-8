#pragma once
#include "Library.h"
#include <iostream>

class Users :
    public Library
{
public:
	Users(std::string username, std::string password);
	~Users();
private:
	using Library::m_username;
	using Library::m_password;


};

