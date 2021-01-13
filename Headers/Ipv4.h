#pragma once
#include <string>

using namespace std;

typedef unsigned short int usi;

class Ipv4
{
private:
	usi _words[4];
	const usi _mask;
public:
	Ipv4(const usi &word1, const usi& word2, const usi& word3, const usi& word4, const usi& mask);

	string toString() const;
};