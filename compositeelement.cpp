/**
	\file compositeelement.cpp
	\brief Code for CompositeElement class
*/	
#include "compositeelement.h"
#include "element.h"
#include <string>
#include <sstream>

CompositeElement::CompositeElement(const Element& e1, const Element& e2,
								const std::function<int(int,int)>& op, char opc){
	oprnd1 = std::unique_ptr<Element>(e1.clone());
	oprnd2 = std::unique_ptr<Element>(e2.clone());
	op_fun = op;
	op_ch = opc;

}

CompositeElement::CompositeElement(const CompositeElement& e){
	oprnd1 = std::unique_ptr<Element>(e.oprnd1->clone());
	oprnd2 = std::unique_ptr<Element>(e.oprnd2->clone());
	op_fun = e.op_fun;
	op_ch = e.op_ch;
}

CompositeElement& CompositeElement::operator=(const CompositeElement& e){
	CompositeElement tempcopy(e);
	
	oprnd1 = std::move(tempcopy.oprnd1);
	oprnd2 = std::move(tempcopy.oprnd2);
	op_fun = tempcopy.op_fun;
	op_ch = tempcopy.op_ch;

	return *this;
}

Element* CompositeElement::clone() const{
	return new CompositeElement(*this);
}

std::string CompositeElement::toString() const{
	std::stringstream strm;
	strm << "(" << oprnd1->toString();
	strm << op_ch;
	strm << oprnd2->toString() << ")";
	return strm.str();
}

int CompositeElement::evaluate(const Valuation& val) const{
	return op_fun(oprnd1->evaluate(val),oprnd2->evaluate(val));
}