#include "squareRoot.h"

using namespace std;

/* *ONLY RUN THIS FILE* */ 

int main()
{

    //Inputs
    string radicand;
    int decimalPlace;
    cout << "Enter a non-negative integer that you would like to take the square root of! : ";
    cin >> radicand;
    cout << "How many decimal places would you like to see? ";
    cin >> decimalPlace;

    // Taking the square root then displaying
    SquareRoot ans(radicand, decimalPlace);
    cout << "The square root is : " << ans.takeSquareRoot();
}