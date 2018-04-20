#pragma once
#include "CUser.h"
#include "CMenuOption.h"

using namespace std;

class CMenuGate
{

	// how many selections we will have.
	// menu, function, permission
	CMenuOption menus[9];

	public:
		CMenuGate();
		~CMenuGate();

		void Add(CMenuOption menu);
};

