#pragma once
#include "CUser.h"

class CUser;
using namespace std;

class CDisplay
{
	protected:
		// Set the wall width left and right of the text.
		static const int m_PaddingWidth = 28;

		// Set the console width for padding.
		static const int m_ConsoleWidth = 120;

		// Alignment methods for center
		static void Padding(void);
		static int LineWidth(void);

	public:

		enum color {
			COLOR_CYAN = 11,
			COLOR_RED = 12,
			COLOR_GREEN = 10,
			COLOR_YELLOW = 14,
			COLOR_DEFAULT = 15
		};

		static void Heading(const string text);
		static void Message(const string text);
		static void Failure(string text);
		static void Success(string text);
		static void Imported(string text);
		static void Text(string message, color color);
		static void Status(string status, string message, color statusColor);
		static void Message(const string text, color colorCode);
		static void Linebreak(const char textFiller);
		static void Input(string message, int& variable);
		static void Input(string message, string& variable);
		static void MenuGate(const string text, CUser user, CUser::user_type permission);
};

