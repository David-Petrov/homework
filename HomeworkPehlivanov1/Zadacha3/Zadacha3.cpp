/*
* Дадени са естествените числа n и k, където 1 ≤ k ≤ n. Да се дефинира рекурсивна функция, която намира сумата на естествените числа от 1 до n със стъпка k.
* Пример: при n = 15 и k = 3: 1 + 4 + 7 + 10 + 13 = 35
*/

#include <iostream>
#include "Validation.h"

using namespace std;

unsigned int sumRecursiveStep(unsigned int start, unsigned int end, unsigned int step);

int main()
{
    //get a valid natural number k
    unsigned int k;
    do {
        k = getValidNumberInput<unsigned int, unsigned int>("k (int, >= 1)");
    } while (k < 1);

    //get a valid natural number n
    unsigned int n;
    do {
        n = getValidNumberInput<unsigned int, unsigned int>("n (int, >= k)");
    } while (n < k);

    cout << sumRecursiveStep(1, n, k) << "\n";

    return 0;
}

unsigned int sumRecursiveStep(unsigned int start, unsigned int end, unsigned int step)
{
    //if the start overcame the end, it's time to stop (return 0 for proper calculations - not changing the result)
    if (start > end)
    {
        return 0;
    }

    //keep expecting the next k'th number until n
    return start + sumRecursiveStep(start + step, end, step);
}