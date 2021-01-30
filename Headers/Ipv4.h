#pragma once
#include "../Menu/Headers/Menu.h"

#include <vector>

using namespace std;

typedef unsigned short int usi;

class Ipv4
{
private:
	vector<usi> _words;

public:
	//Constructors
	Ipv4();
	Ipv4(const string &stringyIp);
	Ipv4(const usi& word1, const usi& word2, const usi& word3, const usi& word4);// , const usi& who);
	Ipv4(const Ipv4 &toCopy);

	//Getters
	string toString() const;
	stringstream toSstream() const;

	//Static functions
	static vector<usi> readIp(const string &stringyIp);
};