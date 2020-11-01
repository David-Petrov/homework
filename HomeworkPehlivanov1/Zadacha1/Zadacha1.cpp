/**
* 1. Да се напише рекурсивна функция, която представя число от десетична в двоична бройна система.
*/

#include <iostream>
#include<vector>
#include "Validation.h"

using namespace std;

const double epsilon = numeric_limits<double>::epsilon();

string presentDecimalPartAsBinary(double, vector<double>&);
string presentAsBinary(unsigned long long);
bool same(double, double);

static int indexRepeatedRest = -1;

int main()
{
    double d;
    while (true) {
        d = getValidNumberInput<double, unsigned long long>(); //from Validation.h

        string binary;

        //if negative, just add a minus to the front of the binary representation and continue working with the abs value
        if (d < 0)
        {
            binary += '-';
            d *= -1;
        }

        //get the whole part
        unsigned long long wholePart = (long long)d;
        //get the decimal part
        double decimalPart = d - wholePart; //biggest problem of our periodicity detection mechanism: 1.1 - 1 != 0.1.... 
                                        //which makes me very sad and thus the recursion fails to recognize periodical binary decimals for bigger input....
        
        //important to store the division rests in order to detect periodicity
        vector<double> rests = vector<double>();

        binary += (wholePart == 0 ? "0" : presentAsBinary(wholePart)); //first present the integer part of our number

        //and if the decimal part is virtually different than zero
        if (!same(decimalPart, 0))
        {
            //add the decimal point
            binary += '.';

            //and present the decimal part in binary
            string dec = presentDecimalPartAsBinary(decimalPart, rests);

            //use our static indexRepeatedRest globally, so if a rest has been repeated, then our decimal part is periodical
            //and we'd want to put nice little brackets around it, so the user can know :)
            if (indexRepeatedRest != -1)
            {
                dec.insert(indexRepeatedRest, "(");
                dec.insert(dec.end(), 1, ')');
            }

            //add the decimal part to our string representation
            binary += dec;
        }

        //finally print our initial double to our user in binary.
        cout << "Binary representation: " << binary << "\n";
    }

    return 0;
}

//method assumes that 0 < d < 1
string presentDecimalPartAsBinary(double d, vector<double>& rests)
{
    //if we've reached the zero, then we're finitely done
    if (same(d, 0))
    {
        return "";
    }

    //check for infinite loop (thus a periodic decimal part)
    indexRepeatedRest = -1;
    for (unsigned int i = 0; i < rests.size(); i++)
    {
        if (same(d, rests[i]))
        {
            indexRepeatedRest = i;
            break;
        }
    }
    // if we alread got the same rest before, then we're in an infinite loop - break it
    if (indexRepeatedRest != -1)
    {
        return "";
    }

    //add the new rest to the list
    rests.push_back(d);

    //proceed with the typical recursive algorithm:
    //1) multiply by 2
    //2) take whole part
    //3) input the rest into the same method until we're finished
    d *= 2;
    int wholePart = (int)d;
    d -= wholePart;
    
    return (char)('0' + wholePart) + presentDecimalPartAsBinary(d, rests);
}

//method assumes 0 < n
string presentAsBinary(unsigned long long n)
{
    if (n == 0) {
        return "";
    }
    //just the classical natural number to binary recursive conversion stuff
    return presentAsBinary(n / 2) + (char)('0' + n % 2);
}

//almost proper double comparison
//main problem: epsilon is an absolute difference test, not relative to a and b
//couldn't really decide which approach would be better, since a and b may vary from large to really small
bool same(double a, double b)
{
    return abs(a - b) < epsilon;
}