/**
	\file tests.cpp
	\brief Tests for all classes
*/
#include "catch.hpp"
#include "element.h"
#include "compositeelement.h"
#include "elementarymatrix.h"
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <sstream>


TEST_CASE("IntElement tests", "intelement"){
	IntElement firstobj;
	CHECK(firstobj.getVal()==0);
	IntElement secondobj(5);
	CHECK(secondobj.getVal()==5);
	firstobj.setVal(3);
	CHECK(firstobj.getVal()==3);

	firstobj+=secondobj;
	CHECK(firstobj.getVal()==8);
	firstobj-=secondobj;
	CHECK(firstobj.getVal()==3);
	firstobj*=secondobj;
	CHECK(firstobj.getVal()==15);

	IntElement addition = firstobj+secondobj;
	CHECK(addition.getVal()==20);
	IntElement subtraction = firstobj-secondobj;
	CHECK(subtraction.getVal()==10);
	IntElement multiplication = firstobj*secondobj;
	CHECK(multiplication.getVal()==75);

	std::stringstream out;
	out << firstobj;
	CHECK(out.str()=="15");
	secondobj.setVal(15);
	CHECK(firstobj==secondobj);	
}

TEST_CASE("VariableElement tests", "varelement"){
	VariableElement firstobj;
	CHECK(firstobj.getVal()==0);
	VariableElement secondobj('f');
	CHECK(secondobj.getVal()=='f');
	firstobj.setVal('k');
	CHECK(firstobj.getVal()=='k');

	std::stringstream out;
	out << firstobj;
	CHECK(out.str()=="k");
	secondobj.setVal('k');
	CHECK(firstobj==secondobj);

	Valuation valu;
	valu['a'] = 123;
	valu['b'] = -123;

	CHECK(valu.at('b') == -123);
	CHECK_THROWS(firstobj.evaluate(valu));
}

TEST_CASE("CompositeElement tests", "compositeelement"){
	IntElement firstobj(5);
	VariableElement secondobj('f');

	CompositeElement first(firstobj, secondobj, std::plus<int>(), '+');
	CHECK(first.toString() == "(5+f)");

	CompositeElement second(first);
	CHECK(second == first);

	CompositeElement third = first;
	CHECK(third.toString() == first.toString());
}



TEST_CASE("ConcreteSquareMatrix correct tests", "concretematrix_correct"){
	ConcreteSquareMatrix firstMatrix("[[3,5,7][1,2,2][4,4,6]]");
	CHECK(firstMatrix.toString() == "[[3,5,7][1,2,2][4,4,6]]");
	ConcreteSquareMatrix copyConstructed(firstMatrix);
	CHECK(copyConstructed.toString() == firstMatrix.toString());
	ConcreteSquareMatrix moveCopyConstructed(std::move(copyConstructed));
	CHECK(moveCopyConstructed.toString() == "[[3,5,7][1,2,2][4,4,6]]");

	ConcreteSquareMatrix assignment;
	assignment = firstMatrix;
	CHECK(assignment == firstMatrix);

	ConcreteSquareMatrix moveAssigned;
	moveAssigned = std::move(firstMatrix);
	CHECK(moveAssigned.toString() == "[[3,5,7][1,2,2][4,4,6]]");

	ConcreteSquareMatrix transposed = moveAssigned.transpose();
	CHECK(transposed.toString() == "[[3,1,4][5,2,4][7,2,6]]");

	ConcreteSquareMatrix mathMatrix("[[3,5,7][1,2,2][4,4,6]]");
	ConcreteSquareMatrix mathMatrixTwo("[[3,1,4][5,2,4][7,2,6]]");

	ConcreteSquareMatrix addition = mathMatrix + mathMatrixTwo;
	CHECK(addition.toString() == "[[6,6,11][6,4,6][11,6,12]]");
	
	ConcreteSquareMatrix subtraction = mathMatrix - mathMatrixTwo;
	CHECK(subtraction.toString() == "[[0,4,3][-4,0,-2][-3,2,0]]");

	ConcreteSquareMatrix multiplication = mathMatrix * mathMatrixTwo;
	CHECK(multiplication.toString() == "[[83,27,74][27,9,24][74,24,68]]");

	std::stringstream out;
	out << mathMatrix;
	CHECK(out.str() == "[[3,5,7][1,2,2][4,4,6]]");

	mathMatrix.print(out);
	CHECK(out.str() == "[[3,5,7][1,2,2][4,4,6]][[3,5,7][1,2,2][4,4,6]]");	
}

TEST_CASE("ConcreteSquareMatrix incorrect tests and exceptions", "concretematrix_incorrect"){
	CHECK_NOTHROW(ConcreteSquareMatrix("[]"));
	CHECK_NOTHROW(ConcreteSquareMatrix("[[1]]"));
	CHECK_NOTHROW(ConcreteSquareMatrix("[[1,2][1,2]]"));
	CHECK_NOTHROW(ConcreteSquareMatrix("[[3,5,7,8][5,7,3,8][7,3,5,8][7,3,5,8]]"));

	CHECK_THROWS(ConcreteSquareMatrix("[[2.5,-2][3,2]]"));
	CHECK_THROWS(ConcreteSquareMatrix("[[1,2]]/[[3,5]]"));
	CHECK_THROWS(ConcreteSquareMatrix("[[1]]ttett"));
	CHECK_THROWS(ConcreteSquareMatrix("[[1]] x"));
	CHECK_THROWS(ConcreteSquareMatrix("[[1,2]]"));
	CHECK_THROWS(ConcreteSquareMatrix("[[-3,14][24,5]"));
	CHECK_THROWS(ConcreteSquareMatrix("F"));
	CHECK_THROWS(ConcreteSquareMatrix("[F"));
	CHECK_THROWS(ConcreteSquareMatrix("[[F]]"));
	CHECK_THROWS(ConcreteSquareMatrix("[[-3,14][24,5,5]"));

	ConcreteSquareMatrix matrixOne("[[3,5][1,2]]");
	ConcreteSquareMatrix matrixTwo("[[3,1,4][5,2,4][7,2,6]]");

	CHECK_THROWS(matrixOne*=matrixTwo);
	CHECK_THROWS(matrixOne+=matrixTwo);
	CHECK_THROWS(matrixOne-=matrixTwo);
}

TEST_CASE("SymbolicSquareMatrix correct tests", "Symbolicmatrix_correct"){
	SymbolicSquareMatrix firstMatrix("[[x,5,7][1,y,2][z,4,6]]");
	CHECK(firstMatrix.toString() == "[[x,5,7][1,y,2][z,4,6]]");
	SymbolicSquareMatrix copyConstructed(firstMatrix);
	CHECK(copyConstructed.toString() == firstMatrix.toString());
	SymbolicSquareMatrix moveCopyConstructed(std::move(copyConstructed));
	CHECK(moveCopyConstructed.toString() == "[[x,5,7][1,y,2][z,4,6]]");

	SymbolicSquareMatrix assignment;
	assignment = firstMatrix;
	CHECK(assignment == firstMatrix);

	SymbolicSquareMatrix moveAssigned;
	moveAssigned = std::move(firstMatrix);
	CHECK(moveAssigned.toString() == "[[x,5,7][1,y,2][z,4,6]]");

	SymbolicSquareMatrix transposed = moveAssigned.transpose();
	CHECK(transposed.toString() == "[[x,1,z][5,y,4][7,2,6]]");

	std::stringstream out;
	out << transposed;
	CHECK(out.str() == "[[x,1,z][5,y,4][7,2,6]]");

	transposed.print(out);
	CHECK(out.str() == "[[x,1,z][5,y,4][7,2,6]][[x,1,z][5,y,4][7,2,6]]");

	Valuation valu;
	valu['x'] = 3;
	valu['y'] = 2;
	valu['z'] = 4;

	SymbolicSquareMatrix vtest("[[x,5,7][1,y,2][z,4,6]]");
	CHECK(vtest.toString() == "[[x,5,7][1,y,2][z,4,6]]");

	ConcreteSquareMatrix evaluated = vtest.evaluate(valu);
	CHECK(evaluated.toString() == "[[3,5,7][1,2,2][4,4,6]]");

	valu.erase('z');
	CHECK_THROWS(evaluated = vtest.evaluate(valu));

	valu['z'] = 4;
	SymbolicSquareMatrix mathMatrix("[[x,5,7][1,y,2][z,4,6]]");
	SymbolicSquareMatrix mathMatrixTwo("[[3,1,4][5,2,4][7,2,6]]");

	SymbolicSquareMatrix addition = mathMatrix + mathMatrixTwo;
	CHECK(addition.toString() == "[[(x+3),(5+1),(7+4)][(1+5),(y+2),(2+4)][(z+7),(4+2),(6+6)]]");
	ConcreteSquareMatrix solvedAddition = addition.evaluate(valu);
	CHECK(solvedAddition.toString() == "[[6,6,11][6,4,6][11,6,12]]");
	
	SymbolicSquareMatrix subtraction = mathMatrix - mathMatrixTwo;
	CHECK(subtraction.toString() == "[[(x-3),(5-1),(7-4)][(1-5),(y-2),(2-4)][(z-7),(4-2),(6-6)]]");
	ConcreteSquareMatrix solvedSubtraction = subtraction.evaluate(valu);
	CHECK(solvedSubtraction.toString() == "[[0,4,3][-4,0,-2][-3,2,0]]");

	SymbolicSquareMatrix multiplication = mathMatrix * mathMatrixTwo;
	ConcreteSquareMatrix solvedMultiplication = multiplication.evaluate(valu);
	CHECK(solvedMultiplication.toString() == "[[83,27,74][27,9,24][74,24,68]]");

}

TEST_CASE("SymbolicSquareMatrix incorrect tests and exceptions", "symbolicmatrix_incorrect"){
	CHECK_NOTHROW(SymbolicSquareMatrix("[]"));
	CHECK_NOTHROW(SymbolicSquareMatrix("[[1]]"));
	CHECK_NOTHROW(SymbolicSquareMatrix("[[1,2][1,2]]"));
	CHECK_NOTHROW(SymbolicSquareMatrix("[[3,5,7,8][5,7,3,8][7,3,5,8][7,3,5,8]]"));

	CHECK_THROWS(SymbolicSquareMatrix("[[2.5,-2][3,2]]"));
	CHECK_THROWS(SymbolicSquareMatrix("[[ä.5,-2][3,2]]"));
	CHECK_THROWS(SymbolicSquareMatrix("[[1,2]]/[[3,5]]"));
	CHECK_THROWS(SymbolicSquareMatrix("[[1]]ttett"));
	CHECK_THROWS(SymbolicSquareMatrix("[[1]] x"));
	CHECK_THROWS(SymbolicSquareMatrix("[[1,2]]"));
	CHECK_THROWS(SymbolicSquareMatrix("[[-3,14][24,5]"));
	CHECK_THROWS(SymbolicSquareMatrix("F"));
	CHECK_THROWS(SymbolicSquareMatrix("[F"));
	CHECK_THROWS(SymbolicSquareMatrix("[[-3,14][24,5,5]"));
}