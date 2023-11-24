#include <iostream>
#include <cmath>
#include <stack>
#include <sstream>

using namespace std;

class Calculator
{
public:
    int evaluateExpression(const string &expression)
    {
        stack<int> values;
        stack<char> operators;

        istringstream iss(expression);
        char token;
        while (iss >> token)
        {
            if (isdigit(token))
            {
                iss.putback(token);
                int value;
                iss >> value;
                values.push(value);
            }
            else if (token == '+' || token == '-' || token == '*' || token == '(')
            {
                operators.push(token);
            }
            else if (token == ')')
            {
                while (operators.top() != '(')
                {
                    applyOperator(operators.top(), values);
                    operators.pop();
                }
                operators.pop(); // Pop '('
            }
            else if (token == 'a')
            {               // 'a' là ký tự đầu của abs
                char op[3]; // abs
                iss.read(op, 3);
                int operand;
                iss >> operand;
                values.push(abs(operand));
            }
        }

        while (!operators.empty())
        {
            applyOperator(operators.top(), values);
            operators.pop();
        }

        return values.top();
    }

private:
    void applyOperator(char op, stack<int> &values)
    {
        int operand2 = values.top();
        values.pop();
        int operand1 = values.top();
        values.pop();

        switch (op)
        {
        case '+':
            values.push(operand1 + operand2);
            break;
        case '-':
            values.push(operand1 - operand2);
            break;
        case '*':
            values.push(operand1 * operand2);
            break;
        }
    }
};

int main()
{
    Calculator calculator;
    string expression = "3+(4 - abs(-5))*6";
    int result = calculator.evaluateExpression(expression);
    cout << result << endl;

    return 0;
}
