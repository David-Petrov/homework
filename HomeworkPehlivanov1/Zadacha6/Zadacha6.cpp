/*
6. Двоичното търсене работи по следния начин:
a. намира лява и дясна граница на редица
b. намира средата
c. ако елементът точно в средата е търсеният от нас, връща индекса
d. ако елементът в средата е по-голям от търсения от нас, повтаря алгоритъма
в лявата част
e. ако елементът в средата е по-малък от търсения от нас, повтаря алгоритъма
в дясната част
f. ако границите се срещнат и елементът не е открит, връща -1.

Напишете функция, реализираща двоично търсене( масивът от числа, който се подава на
функцията трябва да е предварително сортиран!).
*/

#include <iostream>
#include <string>
#include <algorithm>
#include "Validation.h"

using namespace std;

int searchElement(int* arr, int number, int startIndex, int endIndex);

int main()
{
    int length = getValidNumberInput<unsigned int, unsigned int>("array length (>0)");
    int* arr = new int[length];

    for (int i = 0; i < length; i++)
    {
        arr[i] = getValidNumberInput<int, int>(to_string(i+1) + ". int");
    }

    int n = getValidNumberInput<int, int>("int to search for");

    //sort the array, not interesting, so we do it the lazy way
    sort(arr, arr + length);

    //let the user see his beautifully ordered elements
    cout << "Sorted array: ";
    for (int i = 0; i < length; i++)
    {
        cout << arr[i] << ' ';
    }
    cout << '\n';

    //start recursion!!!
    int index = searchElement(arr, n, 0, length);

    if (index == -1)
    {
        cout << "Your element (" << n << ") was not found!\n";
    }
    else
    {
        cout << "Your element (" << n << ") was found at index "<<index<<"!\n";
    }

    return 0;
}

int searchElement(int* arr, int number, int startIndex, int endIndex)
{
    //if the boundaries have met, we're at a deadend and thus return -1
    if (startIndex >= endIndex)
    {
        return -1;
    }

    //calculate the middle index in the classical way
    int middle = startIndex + (endIndex - startIndex) / 2;

    //if we found it, yuppy yay yey! return the index we found it at
    if (arr[middle] == number)
    {
        return middle;
    }

    //if what we found was bigger than the desired number, perform the same search on the left side
    if (arr[middle] > number)
    {
        return searchElement(arr, number, startIndex, middle);
    }
    //otherwise do the same, but on the right side of the array
    else
    {
        return searchElement(arr, number, middle + 1, endIndex);
    }
}