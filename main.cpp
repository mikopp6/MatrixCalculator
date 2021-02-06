/**
	\file main.cpp
	\brief Main driver for the SquareMatrixCalculator program
*/

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <ostream>
#include <sstream>
#include <map>
#include <stack>
#include "element.h"
#include "compositeelement.h"
#include "elementarymatrix.h"
#include "valuation.h"

int main(int argc, char** argv){

	int result = Catch::Session().run(argc,argv);
	if(result != 0)
		return result;

	std::stack<ElementarySquareMatrix<Element>> matrixStack;
	Valuation valuation;
	std::string input;
	char firstChar;
	char c;
	int value;

	while(input != "quit"){
		std::cout << "Input, ""quit"" exits: ";
		std::cin >> input;
		firstChar = input.at(0);
		switch(firstChar){
			case '[':
				try{
					matrixStack.push(SymbolicSquareMatrix(input));
				}catch(const std::invalid_argument& e){
					std::cerr << e.what() << ", try again" << std::endl;
					break;
				}
				break;
			case '+': case '-': case '*':{
				if(matrixStack.size() < 2){
					std::cout << "Less than 2 matrices in stack, operation not possible" << std::endl;
					break;
				}
				SymbolicSquareMatrix firstMatrix(matrixStack.top());
				matrixStack.pop();
				SymbolicSquareMatrix secondMatrix(matrixStack.top());
				matrixStack.pop();
				SymbolicSquareMatrix result;
				try{
					if(firstChar == '+')
						result = firstMatrix + secondMatrix;
					if(firstChar == '-')
						result = firstMatrix - secondMatrix;
					if(firstChar == '*')
						result = firstMatrix * secondMatrix;
				}catch(const std::domain_error& e){
					std::cerr << e.what() << ". Stack cleared, please try again." << std::endl;
					break;
				}
				std::cout << result << std::endl;
				matrixStack.push(result);
				break;
			}
			case '=':{
				if(matrixStack.empty()){
					std::cout << "Stack empty" << std::endl;
					break;
				}
				ConcreteSquareMatrix evaluated;
				try{
					evaluated = matrixStack.top().evaluate(valuation);
				}catch(const std::out_of_range& e){
					std::cerr << e.what() << ", try again" << std::endl;
					break;
				}
				std::cout << evaluated << std::endl;
				break;
			}
			default:
				if(isalpha(firstChar)){
					std::stringstream tempStream(input);
					tempStream >> c;
					tempStream >> c;
					tempStream >> value;
					valuation[firstChar] = value;
					break;
				}
				std::cout << "Invalid input, try again" << std::endl;
				break;
		}
	}

	return result;
}