#ifndef GEN_HPP
#define GEN_HPP

#include <cstdlib>
#include <iostream>
#include <cstdint>


using namespace std;


struct Gen{
	char item;
	Gen* next;
	Gen* prev;
	void setItem(const char& newItem);
	
	Gen(const char&,Gen*,Gen*);
};

#endif