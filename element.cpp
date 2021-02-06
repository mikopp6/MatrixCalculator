/**
	\file element.cpp
	\brief Code for Element class
*/

#include <ostream>
#include "element.h"

std::ostream& operator<<(std::ostream& os, const Element& elem){
	os << elem.toString();
	return os;
}

bool operator==(const Element& elem1, const Element& elem2){
	return elem1.toString() == elem2.toString();
}

template<>
int TElement<int>::evaluate(const Valuation& v) const{
	return val;
}

template<>
int TElement<char>::evaluate(const Valuation& v) const{
	return v.at(val);
}

template<>
IntElement& IntElement::operator+=(const IntElement& i){
	val = val+i.val;
	return *this;
}

template<>
IntElement& IntElement::operator-=(const IntElement& i){
	val = val-i.val;
	return *this;
}

template<>
IntElement& IntElement::operator*=(const IntElement& i){
	val = val*i.val;
	return *this;
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