#include "stdafx.h"
#include "CDisplay.h"

using namespace std;

/**
 * Return the final line width based on the wall spacing.
 * 
 * @return integer
 */
int CDisplay::LineWidth(void)
{
	return CDisplay::m_ConsoleWidth - CDisplay::m_PaddingWidth * 2;
}

/**
 * Walls allows the messages to attain a central position on the console
 * Also allows greater customization on the spaces
 */
void CDisplay::Padding()
{
	cout << setw(CDisplay::m_PaddingWidth) << setfill(' ') << ' ';
}

/**
 * Headings consist of a message with a line break.
 */
void CDisplay::Heading(const string text)
{
	cout << endl;

	CDisplay::Message(text);

	CDisplay::Linebreak('-');
}

/**
 * Display a message based on the central location made from walls.
 * 
 * @return void
 */
void CDisplay::Message(const string text)
{
	Message(text, COLOR_DEFAULT);
}

void CDisplay::Failure(const string text)
{
	system("cls"); // clear console.
	Message(" "); // space from the top
	Status("[Error]: ", text, COLOR_RED);
}

void CDisplay::Success(const string text)
{
	system("cls"); // clear console.
	Message(" "); // space from the top
	Status("[Success]: ", text, COLOR_GREEN);
}

void CDisplay::Imported(const string text)
{
	Status("[Imported]: ", text, COLOR_CYAN);
}

void CDisplay::Text(string message, color color)
{
	CDisplay::Padding();

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(console, color);

	cout << message;

	SetConsoleTextAttribute(console, COLOR_DEFAULT);
}

void CDisplay::Status(string status, string message, color statusColor)
{
	CDisplay::Padding();

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(console, statusColor);

	cout << status;

	SetConsoleTextAttribute(console, COLOR_DEFAULT);

	cout << message << endl;
}

void CDisplay::Message(const string text, color colorCode)
{
	CDisplay::Padding();

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(console, colorCode);

	cout << text << endl;

	SetConsoleTextAttribute(console, COLOR_DEFAULT);
}

/**
 * Display center position for inputting string varaibles from input.
 * 
 * We do not base the message on line width because user input sits 
 * next to message.
 */
void CDisplay::Input(string message, string& variable)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(console, COLOR_YELLOW);

	CDisplay::Padding();

	cout << message;

	while (true)
	{
		getline(cin, variable);

		if (variable != "")
		{
			break;
		}

		CDisplay::Text("[Cannot be Blank] " + message, COLOR_CYAN);
	}

	SetConsoleTextAttribute(console, COLOR_DEFAULT);
}

void CDisplay::MenuGate(const string text, CUser user, CUser::user_type required_permission_Type)
{
	if (user.HasPermission(required_permission_Type))
	{
		 CDisplay::Message(text);

		 return;
	}

	CDisplay::Text(text, CDisplay::COLOR_DEFAULT);
	CDisplay::Message("[Invalid Permission]", CDisplay::COLOR_RED);
}

/**
 * Display center position for inputting a integer variable from input.
 *
 * We do not base the message on line width because user input sits 
 * next to message.
 */
void CDisplay::Input(string message, int& variable)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(console, COLOR_YELLOW);

	CDisplay::Padding();

	cout << message;

	while (true)
	{
		if (cin >> variable)
		{
			if (variable < 100 && variable >= 0)
			{
				break;
			}
		}

		CDisplay::Text("[Between 0-99] " + message, COLOR_CYAN);

		cin.clear();

		cin.ignore(INT_MAX, '\n');
	}

	cin.ignore();

	SetConsoleTextAttribute(console, COLOR_DEFAULT);
}

/*
 * Seperator for lines or segements of text from one another.
 */
void CDisplay::Linebreak(const char textFiller)
{
	CDisplay::Padding();

	cout << setw(CDisplay::LineWidth()) << setfill(textFiller) << left << textFiller;
	
	cout << endl;
}
