#pragma once
#include "../Menu/Headers/Menu.h"

using namespace std;

typedef unsigned short int usi;

class Ipv4
{
private:
	usi _words[4];
	const usi _who;

public:
	//Constructors
	Ipv4(const usi &word1, const usi& word2, const usi& word3, const usi& word4, const usi& who);
	Ipv4(const Ipv4 &toCopy);

	//Getters
	string toString() const;
	stringstream toSstream() const;
	//usi getIdentity() const;

	//Constants
	static const usi
		USER = 1,
		ROUTER = 2,
		OTHER = 3;
};