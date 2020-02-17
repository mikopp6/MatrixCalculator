/**
	\file intelement.cpp
	\brief Code for IntElement class
*/

#include "intelement.h"
#include <string>
#include <sstream>

IntElement::IntElement():IntElement(0){}

IntElement::IntElement(int v):val(v){}


int IntElement::getVal() const{
	return val;
}

void IntElement::setVal(int v){
	val = v;
}

Element* IntElement::clone() const{
	return new IntElement(*this);
}

std::string IntElement::toString() const{
	std::string s = std::to_string(val);
	return s;
}

int IntElement::evaluate(const Valuation& v) const{
	return val;
}


IntElement& IntElement::operator+=(const IntElement& i){
	val = val+i.val;
	return *this;
}

IntElement& IntElement::operator-=(const IntElement& i){
	val = val-i.val;
	return *this;
}

IntElement& IntElement::operator*=(const IntElement& i){
	val = val*i.val;
	return *this;
}

bool IntElement::operator==(const IntElement& i) const{
	return val==i.val;
}

IntElement operator+(const IntElement& firstobj, const IntElement& secondobj){
	IntElement result(firstobj);
	result+=secondobj;
	return result;
}

IntElement operator-(const IntElement& firstobj, const IntElement& secondobj){
	IntElement result(firstobj);
	result-=secondobj;
	return result;
}

IntElement operator*(const IntElement& firstobj, const IntElement& secondobj){
	IntElement result(firstobj);
	result*=secondobj;
	return result;
}