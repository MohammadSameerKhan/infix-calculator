/**
 * Mohammad Sameer Khan 
 * gx6174jg
 * InfixCalculator
 * 19/03
 */
 
#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;


class InfixCalculator {
private:
    string infix_expression;

    bool is_well_formed(const string &expr) 
    {
        
        for (size_t i = 0; i < expr.size(); ++i) 
        {
            char ch = expr[i];
            if (!(isdigit(ch) || ch == '(' || ch == ')' || ch == '+' || ch == '-' || ch == '*' || ch == '/')) 
            {
                return false;
            }
        }
        return true;
    }

    bool has_balanced_brackets(const string &expr) 
    {
        stack<char> bracket_stack;
        
        for (char ch : expr) 
        {
            if (ch == '(') 
            {
                bracket_stack.push(ch);
            } else if (ch == ')') 
            
            {
                if (bracket_stack.empty()) 
                {
                    return false;
                }
                
                bracket_stack.pop();
            }
        }
    
        return bracket_stack.empty();
    }

    
    int precedence(char op) 
    {
        
        if (op == '+' || op == '-') 
        {
            return 1;
        
        } 
        
        else if (op == '*' || op == '/') 
        
        {
            return 2;
        }
        
        return 0;
    }
    
      
    string infix_to_postfix(const string &expr) 
    {
        string postfix;
        stack<char> op_stack;
        
        for (char ch : expr) 
        {
            if (isdigit(ch)) 
            {
                postfix += ch;
            
            } 
            
            else if (ch == '(') 
            
            {
                op_stack.push(ch);
            
            } 
            
            else if (ch == ')') 
            
            {
                while (!op_stack.empty() && op_stack.top() != '(') 
                {
                    postfix += op_stack.top();
                    op_stack.pop();
                }
                               
                op_stack.pop();
            
            } 
            
            else 
            
            {
                
                while (!op_stack.empty() && precedence(ch) <= precedence(op_stack.top())) 
                
                {
                    postfix += op_stack.top();
                    op_stack.pop();
                }
                
                op_stack.push(ch);
            }
        }

        while (!op_stack.empty()) 
        
        {
            postfix += op_stack.top();
            op_stack.pop();
        }

        
        return postfix;
    }

    int evaluate_postfix(const string &postfix) 
    {
        
        stack<int> operand_stack;
        
        for (char ch : postfix) 
        {
            
            if (isdigit(ch)) 
            
            {
                operand_stack.push(ch - '0');
            
            } 
            
            else 
            
            {
                int op2 = operand_stack.top();
                operand_stack.pop();
                int op1 = operand_stack.top();
                operand_stack.pop();

                switch (ch) 
                {
                    case '+':
                        operand_stack.push(op1 + op2);
                        break;
                    case '-':
                        operand_stack.push(op1 - op2);
                        break;
                    case '*':
                        operand_stack.push(op1 * op2);
                        break;
                    case '/':
                        operand_stack.push(op1 / op2);
                        break;
                }
            }
        }

        return operand_stack.top();
    }

public:
    
    InfixCalculator() {}

    bool set_expression(const string &expr) 
    {
        if (is_well_formed(expr) && has_balanced_brackets(expr)) 
        {
            infix_expression = expr;
            return true;
        }
        return false;
    }

    int evaluate() {
        string postfix_expression = infix_to_postfix(infix_expression);
        return evaluate_postfix(postfix_expression);
    }
};

int main() 
{
    
    InfixCalculator calculator;
    string expression;
    
    while (true) 
    {
        cout << "Enter an infix expression (or type 'exit' to quit): ";
        getline(cin, expression);

        
        if (expression == "exit") 
        {
            break;
        }
              
        if (calculator.set_expression(expression)) 
        {
            
            int result = calculator.evaluate();
            
            cout << "The result of the expression is: " << result << endl;
        
        } 
        
        else 
        
        {
            cout << "Invalid expression! Please enter a valid infix expression." << endl;
        }
    }

    return 0;
}