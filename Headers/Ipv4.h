#pragma once
#include "../Menu/Headers/Menu.h"

#include <vector>

using namespace std;

typedef unsigned short int usi;

class Ipv4
{
private:
	vector<usi> _words;
	const string _label;

public:
	//Constructors
	Ipv4(const string &stringyIp, const string &label);
	Ipv4(const usi& word1, const usi& word2, const usi& word3, const usi& word4, const string &label);
	Ipv4(const Ipv4 &toCopy);

	//Getters
	string getLabel() const;
	string toString(bool label) const;
	stringstream toSstream(bool label) const;

	//Static functions
	static vector<usi> readIp(const string &stringyIp);
	static string getHostName();
};