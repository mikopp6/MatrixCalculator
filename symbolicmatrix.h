#ifndef SYMBOLICMATRIX_H_INCLUDED
#define SYMBOLICMATRIX_H_INCLUDED
#include "element.h"
#include "intelement.h"
#include "varelement.h"
#include "concretematrix.h"
#include <vector>
#include <ostream>
#include <string>
#include <memory>

class SymbolicSquareMatrix{

private:
	/**
		\brief Integer to store matrix dimension (n x n)
	*/
	int n;
	/**
		\brief Matrix is stored in a 2D vector containing unique pointers to Elements
	*/
	std::vector<std::vector<std::unique_ptr<Element>>> elements;
public:
	/**
		\brief Empty constructor
	*/
	SymbolicSquareMatrix():n{0}{};
	/**
		\brief Parametric constructor
		\param Matrix in string form, eg. "[[i11,i12][i21,i22]]"
		\throw std::invalid_argument if matrix is in wrong format, or not a square matrix
	*/
	SymbolicSquareMatrix(const std::string& str_m);
	/**
		\brief Copy constructor
		\param Matrix to be copied from
	*/
	SymbolicSquareMatrix(const SymbolicSquareMatrix& m);
	/**
		\brief Move Constructor
		\param Matrix to move
	*/
	SymbolicSquareMatrix(SymbolicSquareMatrix&& m);
	/**
		\brief Destructor
	*/
	virtual ~SymbolicSquareMatrix();
	/**
		\brief Assignment operator for SymbolicSquareMatrix
		\param SymbolicSquareMatrix to assign from
		\return Resulting SymbolicSquareMatrix
	*/	
	SymbolicSquareMatrix& operator=(const SymbolicSquareMatrix& m);
	/**
		\brief Move-assignment operator for SymbolicSquareMatrix
		\param SymbolicSquareMatrix to move-assign from
		\return Resulting SymbolicSquareMatrix
	*/	
	SymbolicSquareMatrix& operator=(SymbolicSquareMatrix&& m);
	/**
		\brief Method for transposing a matrix
		\return Transposed matrix
	*/	
	SymbolicSquareMatrix transpose() const;
	/**
		\brief Operator for checking if two SymbolicSquareMatrixes are equal
		\param SymbolicSquareMatrix to compare to
		\return Boolean, true if equal, false if not
	*/
	bool operator==(const SymbolicSquareMatrix& m) const;
	/**
		\brief Prints matrix as string using toString to ostream
		\param Ostream to output in
	*/
	void print(std::ostream& os) const;
	/**
		\brief Turns matrix into string in format [[i11,i12][i21,i22]]
		\return String representation
	*/	
	std::string toString() const;
	/**
		\brief Method for evaluating SymbolicSquareMatrix using valuation map
		\param Valuation map
		\return Instance of ConcreteMatrixClass
	*/
	ConcreteSquareMatrix evaluate(const Valuation& val) const;
	
};

std::ostream& operator<<(std::ostream& os, const SymbolicSquareMatrix& m);

#endif