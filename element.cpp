/**
	\file element.cpp
	\brief Code for Element interface-class
*/

#include <ostream>
#include "element.h"

std::ostream& operator<<(std::ostream& os, const Element& elem){
	os << elem.toString();
	return os;
}