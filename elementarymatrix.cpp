/**
	\file elementarymatrix.cpp
	\brief Code for ElementarySquareMatrix class
*/

#include "elementarymatrix.h"

template <>
ElementarySquareMatrix<IntElement>::ElementarySquareMatrix(const std::string& str_m){
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

template<>
ElementarySquareMatrix<Element>::ElementarySquareMatrix(const std::string& str_m){
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

template <>
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

template <>
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

template <>
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

template <>
SymbolicSquareMatrix SymbolicSquareMatrix::operator+(const SymbolicSquareMatrix& m) const{
	if(n!=m.n) throw std::domain_error("Matrix dimensions don't match");

	SymbolicSquareMatrix mtemp(*this);

	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			mtemp.elements[i][j] = std::unique_ptr<Element>(new CompositeElement(*elements[i][j], *m.elements[i][j],
																			std::plus<int>(), '+'));
		}
	}
	return mtemp;
}

template <>
SymbolicSquareMatrix SymbolicSquareMatrix::operator-(const SymbolicSquareMatrix& m) const{
	if(n!=m.n) throw std::domain_error("Matrix dimensions don't match");

	SymbolicSquareMatrix mtemp(*this);

	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			mtemp.elements[i][j] = std::unique_ptr<Element>(new CompositeElement(*elements[i][j], *m.elements[i][j],
																			std::minus<int>(), '-'));
		}
	}
	return mtemp;

}

template <>
SymbolicSquareMatrix SymbolicSquareMatrix::operator*(const SymbolicSquareMatrix& m) const{
	if(n!=m.n) throw std::domain_error("Matrix dimensions don't match");

	SymbolicSquareMatrix mtemp;

	for (int i = 0; i < n; ++i){
		std::vector<std::unique_ptr<Element>> tempRow;
		for (int j = 0; j < n; ++j){
			CompositeElement tempElement(*elements[i][0], *m.elements[0][j],
										std::multiplies<int>(), '*');
			for (int l = 1; l < n; ++l){
				CompositeElement tempSecondElement(*elements[i][l], *m.elements[l][j],
										std::multiplies<int>(), '*');

				tempElement = CompositeElement(tempElement, tempSecondElement, 
										std::plus<int>(), '+');
			}
			tempRow.push_back(std::unique_ptr<Element>(tempElement.clone()));
		}
		mtemp.elements.push_back(std::move(tempRow));
	}

	mtemp.n = m.n;
	return mtemp;
}

template<>
ConcreteSquareMatrix ConcreteSquareMatrix::operator+(const ConcreteSquareMatrix& m) const{
	ConcreteSquareMatrix mtemp(*this);
	mtemp+=m;
	return mtemp;
}

template<>
ConcreteSquareMatrix ConcreteSquareMatrix::operator-(const ConcreteSquareMatrix& m) const{
	ConcreteSquareMatrix mtemp(*this);
	mtemp-=m;
	return mtemp;
}

template<>
ConcreteSquareMatrix ConcreteSquareMatrix::operator*(const ConcreteSquareMatrix& m) const{
	ConcreteSquareMatrix mtemp(*this);
	mtemp*=m;
	return mtemp;
}