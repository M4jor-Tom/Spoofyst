#pragma once

#include "Net.h"

using namespace std;

class WebNode
{
private:
	list<Net> _networks;

public:
	//Constructors
	WebNode();

	//Setters
	void setNetworks();

	//Displayers
	void displayNetworks();
};