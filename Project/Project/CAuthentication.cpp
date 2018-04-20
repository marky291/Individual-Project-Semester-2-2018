#include "stdafx.h"
#include "CAuthentication.h"
#include "CDisplay.h"

CAuthentication::CAuthentication(void) :
	m_CurrentUser(CUser()),
	m_StoredUserCount(0),
	m_LoginAttempts(0)
{
	InitiateUsersFromFile();
}

int CAuthentication::GetLoginAttemptCount()
{
	return m_LoginAttempts;
}

void CAuthentication::StoreUser(CUser user)
{
	m_StoredUsers[m_StoredUserCount++] = user;
}


bool CAuthentication::AttemptLogin(string username, string password)
{
	for (int i = 0; i < 3; i++)
	{
		if (m_StoredUsers[i].HasUsername(username))
		{
			if (m_StoredUsers[i].HasPassword(password))
			{
				m_CurrentUser = m_StoredUsers[i];

				return true;
			}

			// no need to check other users.
			break;
		}
	}

	m_LoginAttempts++;

	return false;
}

CUser CAuthentication::CurrentUser()
{
	return m_CurrentUser;
}

void CAuthentication::InitiateUsersFromFile()
{
	string row;

	vector<string> columns; // reinvent the wheel == false;

	ifstream file("users.dat");

	// If file was not read.
	if (file.fail())
	{
		std::exception("Unable to locate users.dat for authenticating users.");
	}

	while (getline(file, row))
	{
		// Clear vector elements.
		columns.clear();

		// Track the character count we are working with.
		int substr_previous_position = 0;
		int substr_current_position = 0;

		// Store each column data to the vector
		while ((substr_current_position = row.find(',', substr_previous_position)) != string::npos)
		{
			columns.push_back(row.substr(substr_previous_position, substr_current_position - substr_previous_position));

			substr_previous_position = substr_current_position + 2;
		}

		// Store last delimeter to the vector.
		columns.push_back(row.substr(substr_previous_position));

		// Convert the string from file into a readable user type format.
		CUser::user_type permission_type = CUser::StringToType(columns[2]);

		// Store the read user into the application for application usage.
		StoreUser(CUser(columns[0], columns[1], permission_type));
	}
}
