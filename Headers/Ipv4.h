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
	pid_t _attackerPid;

public:
	//Constructors
	Ipv4(const string &stringyIp, const string &label);
	Ipv4(const usi& word1, const usi& word2, const usi& word3, const usi& word4, const string &label);
	Ipv4(const Ipv4 &toCopy);

	//Destructors
	~Ipv4();

	//Setters
	bool setAttackerPid(const pid_t attackerPid);

	//Getters
	string getLabel() const;
	string toString(bool label) const;
	stringstream toSstream(bool label) const;
	pid_t getAttackerPid() const;

	//Static functions
	static vector<usi> readIp(const string &stringyIp);
	static string getHostName();
};