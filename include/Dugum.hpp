#ifndef DUGUM_HPP
#define DUGUM_HPP

#include <cstdlib>
#include <iostream>
#include "Kromozom.hpp"


using namespace std;


struct Dugum{
	Kromozom* item;
	Dugum* next;
	
	Dugum(Kromozom*,Dugum*);
};

#endif