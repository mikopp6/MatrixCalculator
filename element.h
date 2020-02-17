/**
	\file element.h
	\brief Header for Element interface-class
*/

#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED
#include "valuation.h"
#include <string>
#include <ostream>

/**
	\class Element
	\brief Base/interface for IntElement and VariableElement
*/
class Element{

public:
	/**
		\brief Default destructor
	*/
	virtual ~Element() = default;
	/**
		\brief Virtual method to clone Element
		\return Retuns pointer to cloned Element
	*/
	virtual Element* clone() const = 0;
	/**
		\brief Method for turning Element into string
		\return String format of Element
	*/
	virtual std::string toString() const = 0;
	/**
		\brief Method for evaluating Element according to valuation map
		\param Used valuation map
		\return Encapsulated Element
	*/
	virtual int evaluate(const Valuation& val) const = 0;

};

/**
	\brief Output operator
	\param Ostream to output in
	\param Element to output
	\return Ostream
*/
std::ostream& operator<<(std::ostream& os, const Element& elem);

#endif