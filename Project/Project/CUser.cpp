#include "stdafx.h"
#include "CUser.h"

CUser::CUser() :
	m_Username(""),
	m_Password(""),
	m_UserType(' ')
{
}

CUser::CUser(const string username, const string password, user_type type) :
	m_Username(username),
	m_Password(password),
	m_UserType(type)
{
}

string CUser::GetUsername(void)
{
	return m_Username;
}

bool CUser::HasUsername(string username)
{
	return m_Username == username;
}

bool CUser::HasPassword(string password)
{
	return m_Password == password;
}

/**
* Check if the user has the equivelant permission.
*
* @param type of the enum that should be compared.
*
* @return bool of the condition.
*/
bool CUser::HasPermission(user_type type)
{
	return m_UserType >= type;
}

/**
* Convert a string input to its usertype alternative.
* This allows a default with invalid characters.
*
* @param type string input to be converted.
*
* @return user_type of the associated context.
*/
CUser::user_type CUser::StringToType(string type)
{
	if (type == "M")
	{
		return CUser::USERTYPE_MANAGER;
	}

	return CUser::USERTYPE_ASSISTANT;
}