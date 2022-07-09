#include <iostream>
#include "stack.h"
#include <vector>
#include <string>
#include <sstream>

using namespace cop4530;


int precedenceCheck(std::string s)  // Checks if operator is higher precendence
{
    if (s == "*" || s == "/")
        return 2;

    if (s == "+" || s == "-")
        return 1;

    else
        return 0;
}


int main()
{
    do  // Main Function Loop
    {
        Stack<std::string> stack;       // default values are set at the beginning of loop
        std::string convertedOpp;
        bool isNumberOpp = true, error = false;
        int operators = 0, operands = 0;
        std::string input;
        std::vector<std::string> strVec= {};

        std::cout << "Please enter an infix operation or type EXIT (all numbers will eval the operation as well): ";

        while (std::cin >> input)   // Input Tokenizer
        {
            if (input == "exit" || input == "EXIT")
                return 0;       // end program

            if (!isdigit(input[0]) && precedenceCheck(input) == 0 && input[0] != '(' && input[0] != ')')
                isNumberOpp = false;    // if character is detected, turn off evaluation

            strVec.push_back(input);    // store token

            if (std::cin.peek() == '\n' || std::cin.peek() == EOF)
                break;  // if end if detected, end loop
        }

        for (int i = 0; i < strVec.size(); i++)     // Conversion Loop
        {
            if (i != 0)
            {
                // If two operators are next to each other, set error
                if (precedenceCheck(strVec[i-1]) != 0 && precedenceCheck(strVec[i]) != 0)
                {
                    std::cout << "ERROR: Operation written incorrectly" << std::endl;
                    error = true;
                    break;
                }
            }

            if (strVec[i] != "+" && strVec[i] != "-" && strVec[i] != "*" && strVec[i] != "/"
                && strVec[i] != "(" && strVec[i] != ")")
            {
                convertedOpp += strVec[i] + " ";    // pass any operands through to string
                operands++;
            }

            else if (strVec[i] == "(")
                stack.push(strVec[i]);  // push ( to stack

            else if (strVec[i] == ")")
            {
                while (stack.top() != "(")  // pass to string and pop stack until ( is reached in stack
                {
                    convertedOpp += stack.top() + " ";
                    stack.pop();
                }
                stack.pop();    // ...then pop (
            }
            else{       // if +, -, *, or / is encountered
                while (!stack.empty())
                {
                    if (precedenceCheck(strVec[i]) > precedenceCheck(stack.top()))
                        break;      // if current operator is higher in precedence, don't pop anything
                    convertedOpp += stack.top() + " ";
                    stack.pop();    // push to string and pop stack
                }
                stack.push(strVec[i]);  // push current operator to stack
                operators++;
            }
        }

        if (operands - 1 != operators)  // if there are not normal amount of operators and operands ...
        {
            if (operands > operators)
            {
                std::cout << "ERROR: Too many operands" << std::endl;
                error = true;
            }
            if (operands <= operators)
            {
                std::cout << "ERROR: Too many operators" << std::endl;
                error = true;
            }
        }

        while (!stack.empty() && !error)    // Empties rest of stack to string
        {
            std::string top = stack.top();
            if ( top == "(" || top == ")")  // Checks if there are leftover parenthesis
            {
                std::cout << "ERROR: Mismatched Parenthesis" << std::endl;
                error = true;
            }
            convertedOpp += top + " ";
            stack.pop();
        }

        if (error)  // Prompts user for input again if error is detected
            continue;

        std::cout << convertedOpp << std::endl;     // prints string

        // evaluate operation after conversion
        if (isNumberOpp)
        {
            std::stringstream numOpp(convertedOpp);     // uses stringstream for tokenizing
            strVec.clear();        // clears vector and input string
            input.clear();
            Stack<float> floatStack;    // new stack for computations

            while (numOpp >> input)     // Tokenizes Post-Fix Operation
            {
                strVec.push_back(input);    // puts tokens in vector
                if (numOpp.peek() == '\n' || numOpp.peek() == EOF)
                    break;
            }
            for (int i = 0; i < strVec.size(); i++)
            {
                if (isdigit(strVec[i].at(0)))   // push any numbers into stack
                    floatStack.push(std::stof(strVec[i]));

                else
                {
                    float firstNum = floatStack.top();  // takes top two numbers for evaluation
                    floatStack.pop();
                    float secondNum = floatStack.top();
                    floatStack.pop();

                    if (strVec[i] == "+")
                        floatStack.push(firstNum + secondNum);
                    if (strVec[i] == "-")
                        floatStack.push(secondNum - firstNum);
                    if (strVec[i] == "*")
                        floatStack.push(firstNum * secondNum);
                    if (strVec[i] == "/")
                        floatStack.push(secondNum / firstNum);
                }
            }
            std::cout << floatStack.top() << std::endl; // prints evaluated operation
            floatStack.pop();   // pops answer from stack
        }
    }while (true); // end function
}
