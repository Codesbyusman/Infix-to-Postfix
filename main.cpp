#include <iostream>

using namespace std;

//stack implementation
struct stackData
{
    char data;
    stackData *next; //pointing to next in the stack
};

class stack
{

private:
    stackData *top; //the top of stack

public:
    //constructor
    stack()
    {
        top = NULL; //no stack
    }

    //for inserting into stack
    void push(char d)
    {

        //making the memory to be added
        stackData *add = new stackData;
        add->data = d;

        //seting the pointers
        add->next = top; //null not other element than this-- for first time then will points to top
        top = add;       //the added will be top of stack
    }

    char pop()
    {
        char returnMe;

        //if stack is not empty
        if (!isEmpty())
        {
            returnMe = top->data; //saving the top data

            //deleting the top
            stackData *temp = top;

            //point to the next of top
            top = top->next;

            //deleteing the node
            delete temp;
        }
        else
        {
            cout << "\n\t Stack is empty " << endl;
        }

        return returnMe;
    }

    char readTop()
    {
        return top->data; //only reads the data of top
    }

    //to check stack is empty or not
    bool isEmpty()
    {
        if (top == NULL)
        {
            return 1; //is empty
        }

        return 0; // is not empty
    }

    //clearing the stck
    void clear()
    {

        //poping elements until the stack is not empty
        while (!isEmpty())
        {
            pop();
        }
    }

    void displayStack()
    {
        stackData *temp = top;

        while (temp)
        {
            cout << temp->data << endl;
            temp = temp->next;
        }
    }
};

//will check precedence of operators
//if the precedence of first one is more than will return true else false
//operator 1 is in the stack the stored and operator 2 is new coming from the expression
bool precedence(char operator1, char operator2)
{

    //dealing the braces
    //if opening encountered mean no use of the operators in stack thus
    if (operator1 == '(')
    {
        return false;
    }
    else if (operator2 == '(')
    {
        //if opening braces also in the stack than that can't do anything until closing not match
        return false;
    }
    else if (operator2 == ')')
    {
        //the opening encountered in the expression now pop
        return true;
    }

    if (operator1 == operator2)
    {
        //mean same precedence will be true
        return true;
    }
    else if (operator1 == '^')
    {
        //^ highest
        return true;
    }
    else if (operator1 == '*' || operator1 == '/')
    {
        //greater than other + -
        return true;
    }
    else if (operator1 == '-' || operator2 == '+' || operator1 == '+' || operator2 == '-')
    {
        return true;
    }

    return false;
}

void convertTopostfix(string, string &);

int main()
{

    string infix = "";   //the entered
    string postfix = ""; //the converted

    cout << "\n\t Enter the expression : ";
    getline(cin, infix);

    convertTopostfix(infix, postfix);

    cout << "\n\t Postfix expression is : " << postfix << endl
         << endl;

    return 0;
}

void convertTopostfix(string infix, string &postfix)
{

    int i = 0;

    //making the stack for operator holder
    stack operatorStack;

    char frominfix = 0;

    //taking first character
    frominfix = infix[i];

    //converting the infix to postfix
    while (frominfix != '\0') //untill infix string not ends
    {

        //if operand append to postfix
        if (!(frominfix == '^' || frominfix == '*' || frominfix == '/' || frominfix == '+' || frominfix == '-' || frominfix == '%' || frominfix == '(' || frominfix == ')'))
        {
            //ignoring the space
            if (frominfix != ' ')
            {
                postfix += frominfix;
            }
        }
        else //operator push on stack and take from stack id there
        {
            //poping if the stack have some operator and entered operator have if more precedence
            while (!operatorStack.isEmpty() && precedence(operatorStack.readTop(), frominfix))
            {
                //now pop expressions and append
                postfix += operatorStack.pop();
            }

            //if stack is empty or symbol was not closing ) than push operator to stack
            //will come down after checking above loop
            if (operatorStack.isEmpty() || frominfix != ')')
            {
                operatorStack.push(frominfix); //store operator to stack
            }
            else
            {
                //will pop and will enter here when only ) will be entered so the others in
                // between operators will be poped thus removing the ( from stack too

                operatorStack.pop();
            }
        }

        i++;
        frominfix = infix[i];
    }

    //if any operator remained in the stack that will be appended at last
    while (!operatorStack.isEmpty())
    {
        postfix += operatorStack.pop();
    }
}