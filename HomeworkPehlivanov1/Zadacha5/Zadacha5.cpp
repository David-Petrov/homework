// Zadacha5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <regex>
#include <string>

using namespace std;

int evaluate(string expression);
string remove_char(string str, char c);

//that would've been our validation regex I spent 3 hours on... but unfortunately, c++ std's regex does not support recursion, which makes me sad
//regex valid_expression("^(?<val>([\\d]+(?<act>[\\+*]\\g<val>)*|\\(\\g<val>\\)))\\g<act>*$");
//instead we'll have to go with a sloppier initial validation....
regex valid_symbols("^[\\d \\+*()]+$");

int main()
{
    string expression;
    int result;
    while (true) {
        //read whole line as the expression
        getline(cin, expression);

        //remove all spaces from string
        expression = remove_char(expression, ' '); 

        //just ignore empty input
        if (expression == "") continue; 

        //validate used symbols
        if (!regex_match(expression, valid_symbols))
        {
            cout << "Invalid expression: contains illegal symbols (only chars allowed: digits, '+', '*', '(', ')')!\n";
            continue;
        }

        //time to start the engine
        result = evaluate(expression);

        //if an error message has been printed, don't show the error code to the user (-1)
        if (result == -1) continue;

        //otherwise show our precious result to the user :3
        cout << result << '\n';
    }

    return 0;
}

int evaluate(string expression)
{
    //in case something like "3+" or "3(+)5" has been input 
    if (expression == "")
    {
        cout << "Invalid expression: used operation on empty numbers!" << '\n';
        return -1;
    }

    /*
    * scan input for correctness
    */
    int parenthesesBalance = 0;//the good ol' neat technique to examine the correct logical  placement of braces 
    bool parenthesesDisplaced = false; //the count might be equal, but they need to be consequent (i.e. no "3)+(5" allowed)
    bool foundParentheses = false; //crucial to know if our current (nested) expression has no more parentheses, so we can evaluate it directly
    char c; //temp for current char when iterating
    int countActionSigns = 0; //counter for the operation signs

    for (string::size_type i = 0; i < expression.size(); i++) {
        c = expression[i];

        //we found an opening!
        if (c == '(')
        {
            foundParentheses = true; //so there are some!
            parenthesesBalance++; //increase count
        }
        //we found a closing, so
        else if (c == ')')
        {
            parenthesesBalance--; //decrease count
        }
        else if (c == '+' || c == '*')
        {
            countActionSigns++;//meanwhile count our operation signs
        }


        //if at some point while iterating the count of ) exceeds the count of (, then they're displaced
        if (parenthesesBalance < 0)
        {
            parenthesesDisplaced = true;
        }
    }
    /*
    * End of correctness scan
    * Start displaying messages
    */

    //we found an unequal count of ( and )
    if (parenthesesBalance != 0)
    {
        cout << "Invalid expression: contains unequal number of parentheses!" << '\n';
        return -1;
    }

    //parentheses were not placed logically, albeit with equal count
    if (parenthesesDisplaced)
    {
        cout << "Invalid expression: parentheses are displaced and not consecutive!" << '\n';
        return -1;
    }

    /*
    *It's main logic time! 
    */
    //if no parentheses, then we're ready to execute consecutively
    if (!foundParentheses)
    {
        //if no actions are contained
        if (countActionSigns == 0)
        {
            //time to convert our number to int
            return stoi(expression);
        }

        //strings to hold both sides of the first encountered operation from right to left
        string leftSide, rightSide;
        char c, action = '-';
        string* currentSide = &rightSide; //starting with the right side in order to have left-to-right associativity of operations with no priority
        for (string::size_type i = 0; i < expression.size(); i++) {
            c = expression[expression.size() - i - 1];//remember - from right to left!

            //if no previous + or * has been detected, make the switch now!
            if (action == '-' && (c == '+' || c == '*'))
            {
                action = c; //save the action
                currentSide = &leftSide; //start wrigint the left side
                continue; //continue to next char ;)
            }

            //keep writing the current side of the expression (remember - we're reading right to left!)
            *currentSide = c + *currentSide;
        }

        //keep the recursing to the left (until we reach the further most left operation)
        int left = evaluate(leftSide);
        if (left == -1) return -1;

        //evaluate the right side (in the case of no parentheses, this must be a plain number, but still)
        int right = evaluate(rightSide);
        if (right == -1) return -1;

        //finally evaluate the result depending on the action found (at this point, there must be one found, so it's either + or *)
        return action == '+' ? (left + right) : (left * right);
    }
    //IF THERE ARE PARENTHESES THOUGH
    else
    {
        string inside; //will hold the inside part of outer parentheses at equal level
        string replaced; //will represent the initial expression after replacing the inside of the top level parentheses with their corresponding value
        parenthesesBalance = 0; //reuse our good old friend to keep track of parentheses placement
        char c;
        for (string::size_type i = 0; i < expression.size(); i++) {
            c = expression[i];

            //encountered an opening (
            if (c == '(')
            {
                //if we're inside an upper level parentheses block, keep writing to the 'inside'
                if (parenthesesBalance > 0)
                {
                    inside += c;
                }
                //and don't forget to increase the balance
                ++parenthesesBalance;

                //very important continue, we don't need the parentheses in our 'replaced' string ;)
                continue;
            }
            //encountered a closing )
            else if (c == ')')
            {
                //firstly, decrement the balance
                --parenthesesBalance;

                //if we reached the zero, then that's the top level closing )
                if (parenthesesBalance == 0)
                {
                    //evaluate the inside of the parentheses block, triggering a recursion
                    int insideVal = evaluate(inside);
                    if (insideVal == -1) return -1; //if errors, rethrow the error code accordingly

                    //concatenate the value of the inside to the new expression
                    replaced += to_string(insideVal);
                    //refresh the 'inside' string
                    inside = "";
                    //and skip the )
                    continue;
                }
            }
            //if c (the current char) is not a parentheses and the balance is 0, we're still at the top level and not inside a (block)
            else if (parenthesesBalance == 0)
            {
                replaced += c;//so keep writing our narrow replaced string
            }

            //And finally, if balance > 0, then we're inside a (block), so we write to the 'inside' string
            if (parenthesesBalance > 0)
            {
                inside += c;
            }
        }

        //Finally, simply evaluate 'replaced', which contains no more parentheses
        return evaluate(replaced);
    }
}

//utility function to remove a given char from string
//used to trim spaces from input :)
string remove_char(string str, char c)
{
    string removed;
    removed.reserve(str.size()); // optional, avoids buffer reallocations in the loop
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (str[i] != c)
        {
            removed += str[i];
        }
    }

    return removed;
}