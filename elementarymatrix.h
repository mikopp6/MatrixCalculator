/**
	\file elementarymatrix.h
	\brief Header and code for ElementarySquareMatrix class
*/

#ifndef ELEMENTARYMATRIX_H_INCLUDED
#define ELEMENTARYMATRIX_H_INCLUDED
#include <string>
#include <sstream>
#include <ostream>
#include <vector>
#include "element.h"
#include "compositeelement.h"
#include "valuation.h"
#include <vector>

/**
	\class ElementarySquareMatrix
	\brief Generic class for ConcreteSquareMatrix and SymbolicSquareMatrix
*/
template <typename Type>
class ElementarySquareMatrix{

private:
	/**
		\brief Integer to store matrix dimension (n x n)
	*/
	int n;
	/**
		\brief Matrix is stored in a 2D vector containing unique pointers to Element-objects
	*/
	std::vector<std::vector<std::unique_ptr<Type>>> elements;
	
	friend ElementarySquareMatrix<Element>;

public:

	/**
		\brief Empty constructor
	*/
	ElementarySquareMatrix():n{0}{};

	/**
		\brief Parametric constructor
		\param Matrix in string form, eg. "[[i11,i12][i21,i22]]"
		\throw std::invalid_argument if matrix is in wrong format, or not a square matrix
	*/
	explicit ElementarySquareMatrix(const std::string& str_m);

	/**
		\brief Copy constructor
		\param Matrix to be copied from
	*/
	ElementarySquareMatrix(const ElementarySquareMatrix& m){
		for(const auto& row : m.elements){
			std::vector<std::unique_ptr<Type>> tempRow;
			for(const auto& column : row){
				Type* tempPtr = dynamic_cast<Type*>(column->clone());
				tempRow.push_back(std::unique_ptr<Type>(tempPtr));
			}
			elements.push_back(std::move(tempRow));
		}
		n = m.n;
	}

	/**
		\brief Move Constructor
		\param Matrix to move
	*/
	ElementarySquareMatrix(ElementarySquareMatrix&& m){
		n = m.n;
		elements = std::move(m.elements);
	}

	/**
		\brief Default destructor
	*/
	virtual ~ElementarySquareMatrix() = default;

	/**
		\brief Assignment operator for ElementarySquareMatrix
		\tparam ElementarySquareMatrix to assign from
		\return Resulting ElementarySquareMatrix
	*/	
	ElementarySquareMatrix<Type>& operator=(const ElementarySquareMatrix<Type>& m){
		if(elements == m.elements) return *this;

		ElementarySquareMatrix<Type> tempcopy{m};
		n = m.n;
		std::swap(elements,tempcopy.elements);
		return *this;
	}

	/**
		\brief Move-assignment operator for ElementarySquareMatrix
		\tparam ElementarySquareMatrix to move-assign from
		\return Resulting ElementarySquareMatrix
	*/	
	ElementarySquareMatrix<Type>& operator=(ElementarySquareMatrix<Type>&& m){
		if(elements == m.elements) return *this;	
		n = m.n;
		elements = std::move(m.elements);
		return *this;
	}

	/**
		\brief Method for transposing a matrix
		\return Transposed matrix
	*/	
	ElementarySquareMatrix transpose() const{
		ElementarySquareMatrix<Type> mtemp;
		std::vector<std::vector<std::unique_ptr<Type>>> tempElements(n);
	
		for(auto& row : elements){
			int index = 0;
			for(auto& column : row){
				Type* tempPtr = dynamic_cast<Type*>(column->clone());
				tempElements[index].push_back(std::unique_ptr<Type>(tempPtr));
				index++;
			}
		}

		mtemp.elements = std::move(tempElements);
		mtemp.n = n;
		return mtemp;
	}

	/**
		\brief Operator for checking if two ElementarySquareMatrices are equal
		\param ElementarySquareMatrix to compare to
		\return Boolean, true if equal, false if not
	*/
	bool operator==(const ElementarySquareMatrix& m) const{
		return toString() == m.toString();
	}

	/**
		\brief Prints matrix as string using toString to ostream
		\param Ostream to output in
	*/
	void print(std::ostream& os) const{
		os << toString();
	}

	/**
		\brief Turns matrix into string in format [[i11,i12][i21,i22]]
		\return String representation
	*/	
	std::string toString() const{
		std::stringstream strm;

		strm << "[";
		for(auto& row: elements){
			strm << "[";
			bool first = true;
			for(auto& col: row){
				if(!first) strm << ",";
				strm << *col;
				first = false;
			}
			strm << "]";
		}

		strm << "]";
		return strm.str();
	}
	/**
		\brief Method for evaluating a SymbolicSquareMatrix
		\param Valuation map to be used
		\return Resulting ConcreteSquareMatrix
	*/	
	ElementarySquareMatrix<IntElement> evaluate(const Valuation& val) const{
		ElementarySquareMatrix<IntElement> m;
		int i;
		for(const auto& row : elements){
			std::vector<std::unique_ptr<IntElement>> tempRow;
			for(const auto& column : row){
				try{
					i = column->evaluate(val);
				}
				catch(const std::out_of_range& oor){
					throw std::out_of_range("Out of range, values not mapped");
				}
	
					tempRow.push_back(std::unique_ptr<IntElement>(new IntElement(i)));
				}
				m.elements.push_back(std::move(tempRow));
			}
			m.n = n;
		return m;
	}
	/**
		\brief Operator for ConcreteSquareMatrix addition
		\param ConcreteSquareMatrix to add with
		\return Result of addition
		\throw std::domain_error if matrix dimensions dont match
	*/
	ElementarySquareMatrix<IntElement>& operator+=(const ElementarySquareMatrix<IntElement>& m);
	/**
		\brief Operator for ConcreteSquareMatrix subtraction
		\param ConcreteSquareMatrix to subtract with
		\return Result of subtraction
		\throw std::domain_error if matrix dimensions dont match
	*/	
	ElementarySquareMatrix<IntElement>& operator-=(const ElementarySquareMatrix<IntElement>& m);
	/**
		\brief Operator for ConcreteSquareMatrix multiplication
		\param ConcreteSquareMatrix to multiply with
		\return Result of multiplication
		\throw std::domain_error if matrix dimensions dont match
	*/	
	ElementarySquareMatrix<IntElement>& operator*=(const ElementarySquareMatrix<IntElement>& m);
	/**
		\brief Operator for ElementarySquareMatrix addition
		\tparam ElementarySquareMatrix to subtract with
		\return Result of addition
		\throw std::domain_error if matrix dimensions dont match
	*/
	ElementarySquareMatrix<Type> operator+(const ElementarySquareMatrix<Type>& m) const;
	/**
		\brief Operator for ElementarySquareMatrix subtraction
		\tparam ElementarySquareMatrix to subtract with
		\return Result of subtraction
		\throw std::domain_error if matrix dimensions dont match
	*/
	ElementarySquareMatrix<Type> operator-(const ElementarySquareMatrix<Type>& m) const;
	/**
		\brief Operator for ElementarySquareMatrix multiplication
		\tparam ElementarySquareMatrix to subtract with
		\return Result of multiplication
		\throw std::domain_error if matrix dimensions dont match
	*/
	ElementarySquareMatrix<Type> operator*(const ElementarySquareMatrix<Type>& m) const;

};

/**
	\brief Output operator
	\param Ostream to output in
	\param SymbolicSquareMatrix to output
	\return Ostream
*/
template <typename Type>
std::ostream& operator<<(std::ostream& os, const ElementarySquareMatrix<Type>& m){
	os << m.toString();
	return os;
}

using ConcreteSquareMatrix = ElementarySquareMatrix<IntElement>;
using SymbolicSquareMatrix = ElementarySquareMatrix<Element>;

#endif // ELEMENTARYMATRIX_H_INCLUDED