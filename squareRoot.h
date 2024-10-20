#pragma once

#include <iostream>
#include <string>

using namespace std;

class SquareRoot
{
private:
    string radicand;  // The number the user gives to take the square root of.
    int decimalPlace; // The amount of numbers the user wants to see of the full answer.
    int pairsSize;    // How big the new array of pairs should be.
    string answer;    // Through each iteration, answer gets another number added to it until the end where it will be the full answer.

    // The string array to hold onto pairs. This could be more efficent by not using an array and doing it all in a loop
    // However I find that it is unreadable and confusing.
    string *pairs;

    // Multiplies the two strings together and returns the result in a new string. Only works if multiplier < 10
    string multiplyStrings(string multiplicand, string multiplier);

    // Removes the leading zeros of the argument.
    string removeLeadingZeros(string paddedString);

    // Subtracts subtrahend from minuend and returns the exact difference.
    string subtractStrings(string minuend, string subtrahend);

    // Returns true if the first parameter is larger than the second, otherwise returns false.
    bool isBiggerThan(string num1, string num2);

    // Finds the largest square that goes into the 2 digit argument. Also adds the base to the answer.
    // Parameters passed by reference so we can change the actual variable.
    void findLargestSquare(string &difference, string &subtractor);

    // Splits the radicand into pairs and input it into the pairs array.
    void splitIntoPairs();

    // Creates a temp answer, copies the current answer into it with a decimal and reassigns.
    void addDecimal();

    // Long divide the remaining pairs, once again passing parameters as reference to change their values.
    void longDivide(string &difference, string &subtractor);

public:
    // Constructor needs a radicand and decimal place.
    SquareRoot(string aRadicand, int aDecimalPlace);

    // Takes the square root by going through the radicand pair by pair. Returns the answer.
    string takeSquareRoot();

    // Destructer to delete the pairs array, I believe in this program it wont matter.
    ~SquareRoot();
};