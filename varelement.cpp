/**
	\file varelement.cpp
	\brief Code for VariableElement class
*/

#include "varelement.h"
#include <string>
#include <iostream>
#include <stdexcept>

VariableElement::VariableElement():VariableElement('0'){}

VariableElement::VariableElement(char v):val(v){}

char VariableElement::getVal() const{
	return val;
}

void VariableElement::setVal(char v){
	val = v;
}

Element* VariableElement::clone() const{
	return new VariableElement(*this);
}

std::string VariableElement::toString() const{
	std::string s;
	s += val;
	return s;
}

int VariableElement::evaluate(const Valuation& v) const{
	int i;
	try{
		i = v.at(val);
	}
	catch(const std::out_of_range& oor){
		throw;
	}
	return i;
}

bool VariableElement::operator==(const VariableElement& i) const{
	return val==i.val;
}