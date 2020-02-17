/**
	\file varelement.h
	\brief Header for VariableElement class
*/

#ifndef VARELEMENT_H_INCLUDED
#define VARELEMENT_H_INCLUDED
#include "valuation.h"
#include "element.h"
#include <string>
#include <ostream>

/**
	\class VariableElement
	\brief A class to encapsulate a character
*/
class VariableElement : public Element{

private:
	/**
		\brief Character to be encapsulated
	*/	
	char val;

public:
	/**
		\brief Empty constructor, defaults variable to 0
	*/
	VariableElement();
	/**
		\brief Parametric constructor
		\param Character to be encapsulated
	*/
	VariableElement(char v);
	/**
		\brief Default destructor
	*/
	virtual ~VariableElement() = default;
	/**
		\brief Method to get character
		\return Returns character
	*/	
	char getVal() const;
	/**
		\brief Method set/change character
		\param Character to encapsulate
	*/
	void setVal(char v);
	/**
		\brief Method to clone VariableElement
		\return Retuns pointer to cloned VariableElement
	*/
	virtual Element* clone() const override;
	/**
		\brief Turns VariableElement into string
		\return String format of VariableElement
	*/
	virtual std::string toString() const override;
	/**
		\brief Evaluates according to valuation map
		\param Used valuation map
		\return Integer corresponding to objects character on given map
	*/
	virtual int evaluate(const Valuation& val) const override;
	/**
		\brief Operator for checking if two VariableElements are equal
		\param VariableElement to compare to
		\return Boolean, true if equal, false if not
	*/
	bool operator==(const VariableElement& i) const;
};


#endif