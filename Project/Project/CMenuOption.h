#pragma once

using namespace std;

#include "CUser.h"

class CMenuOption
{
	public:
		CMenuOption(const string text, const string function, CUser::user_type permission);
};

