#pragma once

#include "CUser.h"
#include <chrono>

class CAuthentication
{
	private:
		CUser m_StoredUsers[3]; // because we dont have a database.
		unsigned int m_StoredUserCount; // count the users being stored.
		unsigned int m_LoginAttempts; // store the incorrect login count.

		void InitiateUsersFromFile(void);
		CUser m_CurrentUser;   // keep the details of logged in user.

public:

		CAuthentication(void);
		int GetLoginAttemptCount(void);
		void StoreUser(CUser user);
		bool AttemptLogin(string username, string password);
		CUser CurrentUser(void);
};

