/**
	\file compositeelement.h
	\brief Header for CompositeElement class
*/

#ifndef COMPOSITEELEMENT_H_INCLUDED
#define COMPOSITEELEMENT_H_INCLUDED
#include <functional>
#include "element.h"
#include "valuation.h"
#include <string>
#include <functional>
#include <memory>

/**
	\class CompositeElement
	\brief A composite class for element
*/
class CompositeElement : public Element{

private:
	/**
		\brief First Element operand uniquepointer
	*/	
	std::unique_ptr<Element> oprnd1;
	/**
		\brief Second Element operand uniquepointer
	*/
	std::unique_ptr<Element> oprnd2;
	/**
		\brief std::function op_fun used in math operations, two Int parameters, returns int
	*/
	std::function<int(int,int)> op_fun;
	/**
		\brief Char indicating mathematical operation
	*/
	char op_ch;

public:
	/**
		\brief Parametric constructor
		\param First Element
		\param Second Element
		\param Function to be used
		\param Char indicating mathematical operation
	*/
	CompositeElement(const Element& e1, const Element& e2, const std::function<int(int,int)>& op, char opc);
	/**
		\brief Copy constructor
		\param CompositeElement to copy
	*/
	CompositeElement(const CompositeElement& e);
	/**
		\brief Assignment operator
		\param CompositeElement to assign from
		\return Assigned CompositeElement
	*/
	CompositeElement& operator=(const CompositeElement& e);
	/**
		\brief Default destructor
	*/
	virtual ~CompositeElement() = default;
	/**
		\brief Method to clone CompositeElement
		\return Retuns pointer to cloned CompositeElement
	*/
	virtual Element* clone() const override;
	/**
		\brief Turns CompositeElement into string
		\return String format of CompositeElement
	*/
	virtual std::string toString() const override;
	/**
		\brief Evaluates according to valuation map
		\param Used valuation map
		\return Returns op_fun(oprnd1->evaluate(val),oprmnd2->evaluate(val))
	*/
	virtual int evaluate(const Valuation& val) const override;
};

#endif // COMPOSITEELEMENT_H_INCLUDED