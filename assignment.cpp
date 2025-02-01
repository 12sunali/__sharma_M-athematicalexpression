#include <iostream>
#include <stack>
#include <cctype>
using namespace std;

// Function to evaluate the expression
double evaluate_expression(const string &expression)
{
    stack<double> operands; // Stack to store operands (numbers)
    stack<char> operators;  // Stack to store operators (+, -, *, /)

    int n = expression.size();
    int i = 0;

    while (i < n)
    {
        char c = expression[i];

        // Skip spaces
        if (c == ' ')
        {
            i++;
            continue;
        }

        // If the character is a digit, form the number and push it to operands
        if (isdigit(c))
        {
            double num = 0;
            while (i < n && isdigit(expression[i]))
            {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            operands.push(num);
        }

        // If the character is '(', push it to operators stack
        else if (c == '(')
        {
            operators.push(c);
            i++;
        }

        // If the character is ')', solve the expression within the parentheses
        else if (c == ')')
        {
            while (!operators.empty() && operators.top() != '(')
            {
                double right = operands.top();
                operands.pop();
                double left = operands.top();
                operands.pop();
                char op = operators.top();
                operators.pop();

                if (op == '+')
                    operands.push(left + right);
                else if (op == '-')
                    operands.push(left - right);
                else if (op == '*')
                    operands.push(left * right);
                else if (op == '/')
                    operands.push(left / right);
            }
            operators.pop(); // Pop '('
            i++;
        }

        // If the character is an operator, handle precedence and apply operators
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            while (!operators.empty() && (operators.top() == '*' || operators.top() == '/' ||
                                          (operators.top() == '+' || operators.top() == '-') && (c == '+' || c == '-')))
            {
                double right = operands.top();
                operands.pop();
                double left = operands.top();
                operands.pop();
                char op = operators.top();
                operators.pop();

                if (op == '+')
                    operands.push(left + right);
                else if (op == '-')
                    operands.push(left - right);
                else if (op == '*')
                    operands.push(left * right);
                else if (op == '/')
                    operands.push(left / right);
            }
            operators.push(c); // Push the current operator
            i++;
        }
    }

    // Process any remaining operators
    while (!operators.empty())
    {
        double right = operands.top();
        operands.pop();
        double left = operands.top();
        operands.pop();
        char op = operators.top();
        operators.pop();

        if (op == '+')
            operands.push(left + right);
        else if (op == '-')
            operands.push(left - right);
        else if (op == '*')
            operands.push(left * right);
        else if (op == '/')
            operands.push(left / right);
    }

    return operands.top(); // The final result is the only element in the operands stack
}

int main()
{
    string expression1 = "25+5-(4*5-5)";
    string expression2 = "24-8+9*2-10/5";

    cout << "Result of expression 1: " << evaluate_expression(expression1) << endl; // Output: 15
    cout << "Result of expression 2: " << evaluate_expression(expression2) << endl; // Output: 32

    return 0;
}
