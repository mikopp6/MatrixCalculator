/**
	\file concretematrix.h
	\brief Header for ConcreteSquareMatrix class
*/

#ifndef CONCRETEMATRIX_H_INCLUDED
#define CONCRETEMATRIX_H_INCLUDED
#include "intelement.h"
#include <vector>
#include <ostream>
#include <string>
#include <memory>

class SymbolicSquareMatrix;

/**
	\class ConcreteSquareMatrix
	\brief Class for square matrixes
*/
class ConcreteSquareMatrix {
private:
	/**
		\brief Integer to store matrix dimension (n x n)
	*/
	int n;
	/**
		\brief Matrix is stored in a 2D vector containing unique pointers to IntElements
	*/
	std::vector<std::vector<std::unique_ptr<IntElement>>> elements;

	friend SymbolicSquareMatrix;
public:
	/**
		\brief Empty constructor
	*/
	ConcreteSquareMatrix():n{0}{};
	/**
		\brief Parametric constructor
		\param Matrix in string form, eg. "[[i11,i12][i21,i22]]"
		\throw std::invalid_argument if matrix is in wrong format, or not a square matrix
	*/
	ConcreteSquareMatrix(const std::string& str_m);
	/**
		\brief Copy constructor
		\param Matrix to be copied from
	*/
	ConcreteSquareMatrix(const ConcreteSquareMatrix& m);
	/**
		\brief Move Constructor
		\param Matrix to move
	*/
	ConcreteSquareMatrix(ConcreteSquareMatrix&& m);
	/**
		\brief Destructor
	*/
	virtual ~ConcreteSquareMatrix();
	/**
		\brief Assignment operator for ConcreteSquareMatrix
		\param ConcreteSquareMatrix to assign from
		\return Resulting ConcreteSquareMatrix
	*/	
	ConcreteSquareMatrix& operator=(const ConcreteSquareMatrix& m);
	/**
		\brief Move-assignment operator for ConcreteSquareMatrix
		\param ConcreteSquareMatrix to move-assign from
		\return Resulting ConcreteSquareMatrix
	*/	
	ConcreteSquareMatrix& operator=(ConcreteSquareMatrix&& m);
	/**
		\brief Method for transposing a matrix
		\return Transposed matrix
	*/	
	ConcreteSquareMatrix transpose() const;
	/**
		\brief Operator for ConcreteSquareMatrix addition
		\param ConcreteSquareMatrix to add with
		\return Result of addition
		\throw std::domain_error if matrix dimensions dont match
	*/		
	ConcreteSquareMatrix& operator+=(const ConcreteSquareMatrix& m);
	/**
		\brief Operator for ConcreteSquareMatrix subtraction
		\param ConcreteSquareMatrix to subtract with
		\return Result of subtraction
		\throw std::domain_error if matrix dimensions dont match
	*/
	ConcreteSquareMatrix& operator-=(const ConcreteSquareMatrix& m);
	/**
		\brief Operator for ConcreteSquareMatrix multiplication 
		\param ConcreteSquareMatrix to multiply with
		\return Result of multiplying
		\throw std::domain_error if matrix dimensions dont match
	*/
	ConcreteSquareMatrix& operator*=(const ConcreteSquareMatrix& m);
	
	/**
		\brief Operator for checking if two ConcreteSquareMatrixes are equal
		\param ConcreteSquareMatrix to compare to
		\return Boolean, true if equal, false if not
	*/
	bool operator==(const ConcreteSquareMatrix& m) const;
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

};

/**
	\brief Operator for adding two ConcreteSquareMatrixes (using operator+=)
	\param First ConcreteSquareMatrix to use in addition
	\param Second ConcreteSquareMatrix to use in addition
	\return Result of addition
	\throw std::domain_error if matrix dimensions dont match
*/
ConcreteSquareMatrix operator+(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2);
/**
	\brief Operator for subtracting with two ConcreteSquareMatrixes (using operator-=)
	\param First ConcreteSquareMatrix to use in subtraction
	\param Second ConcreteSquareMatrix to use in subtraction
	\return Result of subtraction
	\throw std::domain_error if matrix dimensions dont match
*/
ConcreteSquareMatrix operator-(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2);
/**
	\brief Operator for multiplying two ConcreteSquareMatrixes (using operator*=)
	\param First ConcreteSquareMatrix to use in multiplication
	\param Second ConcreteSquareMatrix to use in multiplication
	\return Result of multiplying
	\throw std::domain_error if matrix dimensions dont match
*/

ConcreteSquareMatrix operator*(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2);

/**
	\brief Output operator
	\param Ostream to output in
	\param ConcreteSquareMatrix to output
	\return Ostream
*/
std::ostream& operator<<(std::ostream& os, const ConcreteSquareMatrix& m);
	
#endif