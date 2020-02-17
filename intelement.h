/**
	\file intelement.h
	\brief Header for IntElement class
*/

#ifndef INTELEMENT_H_INCLUDED
#define INTELEMENT_H_INCLUDED
#include "valuation.h"
#include "element.h"
#include <ostream>

/**
	\class IntElement
	\brief A class to encapsulate an integer
*/

class IntElement : public Element{

private:
	/**
		\brief Integer to be encapsulated
	*/
	int val;

public:
	/**
		\brief Empty constructor, defaults variable to 0
	*/
	IntElement();
	/**
		\brief Parametric constructor
		\param Integer to be encapsulated
	*/
	IntElement(int v);
	/**
		\brief Default destructor
	*/
	virtual ~IntElement() = default;
	/**
		\brief Method to get integer
		\return Returns integer
	*/
	int getVal() const;
	/**
		\brief Method set/change integer
		\param Integer to encapsulate
	*/
	void setVal(int v);
	/**
		\brief Method to clone IntElement
		\return Retuns pointer to cloned IntElement
	*/
	virtual Element* clone() const override;
	/**
		\brief Turns IntElement into string
		\return String format of IntElement
	*/
	virtual std::string toString() const override;
	/**
		\brief Evaluates according to valuation map
		\param Used valuation map
		\return Encapsulated integer
	*/
	virtual int evaluate(const Valuation& v) const override;
	/**
		\brief Operator for IntElement addition
		\param IntElement to add with
		\return Result of addition
	*/
	IntElement& operator+=(const IntElement& i);
	/**
		\brief Operator for IntElement subtraction
		\param IntElement to subtract with
		\return Result of subtraction
	*/
	IntElement& operator-=(const IntElement& i);
	/**
		\brief Operator for IntElement multiplication 
		\param IntElement to multiply with
		\return Result of multiplying
	*/
	IntElement& operator*=(const IntElement& i);
	/**
		\brief Operator for checking if two IntElements are equal
		\param IntElement to compare to
		\return Boolean, true if equal, false if not
	*/
	bool operator==(const IntElement& i) const;

};

/**
	\brief Operator for adding two IntElements
	\param First IntElement to use in addition
	\param Second IntElement to use in addition
	\return Result of addition
*/
IntElement operator+(const IntElement& firstobj,const IntElement& secondobj);
/**
	\brief Operator for subtracting with two IntElements 
	\param First IntElement to use in subtraction
	\param Second IntElement to use in subtraction
	\return Result of subtraction
*/
IntElement operator-(const IntElement& firstobj,const IntElement& secondobj);
/**
	\brief Operator for multiplying two IntElements
	\param First IntElement to use in multiplication
	\param Second IntElement to use in multiplication
	\return Result of multiplying
*/
IntElement operator*(const IntElement& firstobj,const IntElement& secondobj);


#endif