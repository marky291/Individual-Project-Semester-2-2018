#pragma once

using namespace std;

class CUser
{
	private:
		string m_Username;
		string m_Password;
		char m_UserType;

	public:

		/**
		* Role Types available to users.
		*/
		enum user_type {
			USERTYPE_MANAGER = 'M',
			USERTYPE_ASSISTANT = 'A',
		};

		CUser();

		CUser(const string username, const string password, user_type type);

		string GetUsername();

		/**
		 * Check if the username matches the input text.
		 * 
		 * @param username of the string to compare against username.
		 * 
		 * @return boolean condition result.
		 */
		bool HasUsername(string username);

		/**
		 * Check if the password matches the input param
		 * 
		 * @param password of the string to compare against.
		 * 
		 * @return boolean condition result.
		 */
		bool HasPassword(string password);

		/**
		 * Check if the user has the equivelant permission.
		 * 
		 * @param type of the enum that should be compared.
		 * 
		 * @return boolean condition result.
		 */
		bool HasPermission(user_type type);

		/**
		* Convert a string input to its usertype alternative.
		* This allows a default with invalid characters.
		*
		* @param type string input to be converted.
		*
		* @return void
		*/
		static user_type StringToType(string type);
};

