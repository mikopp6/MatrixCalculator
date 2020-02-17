/**
	\file concretematrix.cpp
	\brief Code for ConcreteSquareMatrix class
*/

#include "concretematrix.h"
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <iostream>

ConcreteSquareMatrix::ConcreteSquareMatrix(const std::string& str_m){
	std::stringstream matrixstring(str_m);
	char c;
	int row = 0, column = 0, count = 0;
	int value;

	matrixstring >> c;
	if(!matrixstring.good() || c!= '[')
		throw std::invalid_argument("Not valid square matrix");

	matrixstring >> c;
	while(!matrixstring.good() || c!=']'){
		if(!matrixstring.good() || c!= '[')
			throw std::invalid_argument("Not valid square matrix");
		std::vector<std::unique_ptr<IntElement>> tempRow;
		do{
			matrixstring >> value;
			if(!matrixstring.good())
				throw std::invalid_argument("Not valid square matrix");
			count++;
			tempRow.push_back(std::unique_ptr<IntElement>(new IntElement(value)));
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

ConcreteSquareMatrix::ConcreteSquareMatrix(const ConcreteSquareMatrix& m){
	for(const auto& row : m.elements){
		std::vector<std::unique_ptr<IntElement>> tempRow;
		for(const auto& column : row){
			tempRow.push_back(std::unique_ptr<IntElement>(new IntElement(*column)));
		}
		elements.push_back(std::move(tempRow));
	}
	n = m.n;
}

ConcreteSquareMatrix::ConcreteSquareMatrix(ConcreteSquareMatrix&& m){
	n = m.n;
	elements = std::move(m.elements);
}

ConcreteSquareMatrix::~ConcreteSquareMatrix(){
	
}

ConcreteSquareMatrix& ConcreteSquareMatrix::operator=(const ConcreteSquareMatrix& m){
	if(elements == m.elements) return *this;

	ConcreteSquareMatrix tempcopy{m};
	n = m.n;
	std::swap(elements,tempcopy.elements);
	return *this;
}

ConcreteSquareMatrix& ConcreteSquareMatrix::operator=(ConcreteSquareMatrix&& m){
	if(elements == m.elements) return *this;	
	n = m.n;
	elements = std::move(m.elements);
	return *this;
}

ConcreteSquareMatrix ConcreteSquareMatrix::transpose() const{
	ConcreteSquareMatrix mtemp;
	std::vector<std::vector<std::unique_ptr<IntElement>>> tempElements(n);

	for(auto& row : elements){
		int index = 0;
		for(auto& column : row){
			tempElements[index].push_back(std::unique_ptr<IntElement>(new IntElement(*column)));
			index++;
		}
	}

	mtemp.elements = std::move(tempElements);
	mtemp.n = n;
	return mtemp;
}

ConcreteSquareMatrix& ConcreteSquareMatrix::operator+=(const ConcreteSquareMatrix& m){
	if(n!=m.n)
		throw std::domain_error("Matrix dimensions don't match");

	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			*elements[i][j] += *m.elements[i][j];
		}
	}

	return *this;
}

ConcreteSquareMatrix& ConcreteSquareMatrix::operator-=(const ConcreteSquareMatrix& m){
	if(n!=m.n)
		throw std::domain_error("Matrix dimensions don't match");

	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			*elements[i][j] -= *m.elements[i][j];
		}
	}

	return *this;
}

ConcreteSquareMatrix& ConcreteSquareMatrix::operator*=(const ConcreteSquareMatrix& m){
	if(n!=m.n)
		throw std::domain_error("Wrong dimensions for multiplication");

	ConcreteSquareMatrix temp(*this);

	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			for (int l = 0; l < n; ++l){
				*temp.elements[i][j] += *elements[i][l] * *m.elements[l][j];
			}
		}
	}
	temp -= *this;
	elements = std::move(temp.elements);
	return *this;
}

bool ConcreteSquareMatrix::operator==(const ConcreteSquareMatrix& m) const{
	return toString() == m.toString();
}
void ConcreteSquareMatrix::print(std::ostream& os) const{
	os << toString();
}

std::string ConcreteSquareMatrix::toString() const{
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

ConcreteSquareMatrix operator+(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2){
	ConcreteSquareMatrix mtemp(m1);
	mtemp+=m2;
	return mtemp;
}

ConcreteSquareMatrix operator-(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2){
	ConcreteSquareMatrix mtemp(m1);
	mtemp-=m2;
	return mtemp;
}

ConcreteSquareMatrix operator*(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2){
	ConcreteSquareMatrix mtemp(m1);
	mtemp*=m2;
	return mtemp;
}

std::ostream& operator<<(std::ostream& os, const ConcreteSquareMatrix& m){
	os << m.toString();
	return os;
}