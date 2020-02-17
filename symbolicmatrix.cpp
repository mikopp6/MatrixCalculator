/**
	\file symbolicmatrix.cpp
	\brief Code for SymbolicSquareMatrix class
*/

#include "symbolicmatrix.h"
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <iostream>

SymbolicSquareMatrix::SymbolicSquareMatrix(const std::string& str_m){
	std::stringstream matrixstring(str_m);
	char c, symbol;
	int row = 0, column = 0, count = 0;
	int value;

	matrixstring >> c;
	if(!matrixstring.good() || c!= '[')
		throw std::invalid_argument("Not valid square matrix");

	matrixstring >> c;
	while(!matrixstring.good() || c!=']'){
		if(!matrixstring.good() || c!= '[')
			throw std::invalid_argument("Not valid square matrix");
		std::vector<std::unique_ptr<Element>> tempRow;
		do{
			symbol = matrixstring.peek();
			if(isalpha(symbol)){
				matrixstring >> c;
				tempRow.push_back(std::unique_ptr<Element>(new VariableElement(c)));
			}else{
				matrixstring >> value;
				if(!matrixstring.good())
					throw std::invalid_argument("Not valid square matrix");
				tempRow.push_back(std::unique_ptr<Element>(new IntElement(value)));
			}
			count++;
			matrixstring >> c;
			if(!matrixstring.good() || (c!=',' && c!=']'))
				throw std::invalid_argument("Not valid square matrix");
		}while(c!=']');
		if(column == 0)
			column = count;
		if(column!= count)
			throw std::invalid_argument("Not valid square matrix");
		count=0;
		elements.push_back(std::move(tempRow));
		row++;
		matrixstring >> c;
	}

	if(column!=row)
		throw std::invalid_argument("Not valid square matrix");
	matrixstring >> c;
	if(!matrixstring.eof())
		throw std::invalid_argument("Not valid square matrix");
	n = row;

}

SymbolicSquareMatrix::SymbolicSquareMatrix(const SymbolicSquareMatrix& m){
	for(const auto& row : m.elements){
		std::vector<std::unique_ptr<Element>> tempRow;
		for(const auto& column : row){
			tempRow.push_back(std::unique_ptr<Element>(column->clone()));
		}
		elements.push_back(std::move(tempRow));
	}
	n = m.n;

}

SymbolicSquareMatrix::SymbolicSquareMatrix(SymbolicSquareMatrix&& m){
	n = m.n;
	elements = std::move(m.elements);
}

SymbolicSquareMatrix::~SymbolicSquareMatrix(){

}

SymbolicSquareMatrix& SymbolicSquareMatrix::operator=(const SymbolicSquareMatrix& m){
	if(elements == m.elements) return *this;

	SymbolicSquareMatrix tempcopy{m};
	n = m.n;
	std::swap(elements,tempcopy.elements);
	return *this;
}

SymbolicSquareMatrix& SymbolicSquareMatrix::operator=(SymbolicSquareMatrix&& m){
	if(elements == m.elements) return *this;	

	n = m.n;
	elements = std::move(m.elements);
	return *this;
}

SymbolicSquareMatrix SymbolicSquareMatrix::transpose() const{
	SymbolicSquareMatrix mtemp;
	std::vector<std::vector<std::unique_ptr<Element>>> tempElements(n);

	for(auto& row : elements){
		int index = 0;
		for(auto& column : row){
			tempElements[index].push_back(std::unique_ptr<Element>(column->clone()));
			index++;
		}
	}

	mtemp.elements = std::move(tempElements);
	mtemp.n = n;
	return mtemp;
}

bool SymbolicSquareMatrix::operator==(const SymbolicSquareMatrix& m) const{
	return toString() == m.toString();
}

void SymbolicSquareMatrix::print(std::ostream& os) const{
	os << toString();
}

std::string SymbolicSquareMatrix::toString() const{
	std::stringstream strm;
	bool eka;

	strm << "[";
	for(auto& row: elements){
		strm << "[";
		eka = true;
		for(auto& col: row){
			if(!eka) strm << ",";
			strm << *col;
			eka = false;
		}
		strm << "]";
	}
	
	strm << "]";
	return strm.str();
}

ConcreteSquareMatrix SymbolicSquareMatrix::evaluate(const Valuation& val) const{
	ConcreteSquareMatrix m;
	int i;
	for(const auto& row : elements){
		std::vector<std::unique_ptr<IntElement>> tempRow;
		for(const auto& column : row){
			try{
				i = column->evaluate(val);
			}
			catch(const std::out_of_range& oor){
				throw std::out_of_range("Out of range, value not mapped");
			}

			tempRow.push_back(std::unique_ptr<IntElement>(new IntElement(i)));
		}
		m.elements.push_back(std::move(tempRow));
	}
	m.n = n;
	return m;
}

std::ostream& operator<<(std::ostream& os, const SymbolicSquareMatrix& m){
	os << m.toString();
	return os;
}
