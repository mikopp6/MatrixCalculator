/**
	\file element.h
	\brief Header for Element class
*/

#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED
#include <string>
#include <sstream>
#include <ostream>
#include "valuation.h"

/**
	\class Element
	\brief Base for TElement(IntElement and VariableElement) and CompositeElement
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

/**
	\brief Operator for checking if two Elements are equal
	\param Element to compare
	\param Element to compare to
	\return Boolean, true if equal, false if not
*/
bool operator==(const Element& elem1, const Element& elem2);


/**
	\class TElement
	\brief Generic class for IntElement and VariableElement
*/
template <typename Type>
class TElement : public Element{

private:
	/**
		\brief Value to store
	*/
	Type val;

public:
	/**
		\brief Empty constructor, sets value 0
	*/
	TElement():val(0){}
	/**
		\brief Parametric constructor
		\param Value to store
	*/
	explicit TElement(Type t):val(t){}
	/**
		\brief Default destructor
	*/
	virtual ~TElement() = default;
	/**
		\brief Method to get value
		\return Value of type char or int
	*/
	Type getVal() const{
		return val;
	}
	/**
		\brief Method to get value
		\tparam Value of type char or int
	*/
	void setVal(Type v){
		val = v;
	}
	/**
		\brief Virtual method to clone Element
		\return Retuns pointer to cloned Element
	*/
	virtual Element* clone() const override{
		return new TElement<Type>(*this);
	}
	/**
		\brief Method for turning Element into string
		\return String format of Element
	*/
	virtual std::string toString()const override{
		std::stringstream s;
		s << val;
		return s.str();
	}
	/**
		\brief Method for evaluating Element according to valuation map
		\param Used valuation map
		\return Encapsulated Element
	*/
	virtual int evaluate(const Valuation& val)const override;
	/**
		\brief Method for TElement<Type> addition
		\tparam Int value to use in operation
		\return Returns TElement<Type>, in this case IntElement
	*/	
	TElement<Type>& operator+=(const TElement<Type>& i);
	/**
		\brief Method for TElement<Type> subtraction
		\tparam Int value to use in operation
		\return Returns TElement<Type>, in this case IntElement
	*/	
	TElement<Type>& operator-=(const TElement<Type>& i);
	/**
		\brief Method for TElement<Type> multiplication
		\tparam Int value to use in operation
		\return Returns TElement<Type>, in this case IntElement
	*/	
	TElement<Type>& operator*=(const TElement<Type>& i);


};

using IntElement = TElement<int>;
using VariableElement = TElement<char>;

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



#endif // ELEMENT_H_INCLUDED

