#include "squareRoot.h"

SquareRoot::SquareRoot(string aRadicand, int aDecimalPlace)
{
    radicand = aRadicand;
    decimalPlace = aDecimalPlace;
    pairsSize = 0;
}

string SquareRoot::multiplyStrings(string number1, string number2)
{
    string result;
    int carry = 0;

    // Starts at the ones place, then goes to the tens, and so on.
    for (int i = number1.length() - 1; i >= 0; i--)
    {
        // Multiply each digit one by one and if the single digit > 9, carry it to the next digit.
        int product = (number1[i] - '0') * stoi(number2);
        if (carry > 0)
        {
            product += carry;
            carry = 0;
        }
        if (product > 9)
        {
            carry = product / 10;
            product %= 10;
        }
        result.insert(0, to_string(product));
    }
    // Add the carry to the front of the result.
    if (carry > 0)
    {
        result.insert(0, to_string(carry));
    }
    return result;
}

string SquareRoot::removeLeadingZeros(string paddedString)
{
    for (int i = 0; i < paddedString.length(); i++)
    {
        if (paddedString[i] != '0' || i == paddedString.length() - 1)
        {
            // Once you find a digit that isnt 0, make a new string from that point on and return it.
            string nonPaddedString(paddedString, i, paddedString.length() - i);
            return nonPaddedString;
        }
    }
    return paddedString;
}

string SquareRoot::subtractStrings(string minuend, string subtrahend)
{

    // Odd cases to make sure the method works properly.
    if (subtrahend[0] == '0')
    {
        subtrahend = removeLeadingZeros(subtrahend);
    }

    if (minuend == "")
    {
        minuend = "0";
    }

    string result;
    bool borrow = 0;

    int minLength = minuend.length();
    int subLength = subtrahend.length();

    // Add padding to the subtrahend which is needed
    string padding(minLength - subLength, '0');
    subtrahend = padding + subtrahend;

    // Subtract each digit in the specific spot, ie: ones spot, tens spot. And borrow when needed.
    for (int i = minuend.length() - 1; i >= 0; i--)
    {
        int digitMin = minuend[i] - '0';
        int digitSub = subtrahend[i] - '0';

        int difference = digitMin - digitSub - borrow;

        if (difference < 0)
        {
            difference += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        result = to_string(difference) + result;
    }
    return removeLeadingZeros(result);
}

bool SquareRoot::isBiggerThan(string num1, string num2)
{
    // Nonpadded numbers only. If num1's length is less it returns false, if it's greater it's true.
    // Otherwise check each digit one by one from the start.
    if (num1.length() < num2.length())
    {
        return false;
    }
    if (num1.length() > num2.length())
    {
        return true;
    }
    for (int i = 0; i < num1.length(); i++)
    {
        if ((num1[i] - '0') > (num2[i] - '0'))
        {
            return true;
        }
        if ((num1[i] - '0') < (num2[i] - '0'))
        {
            return false;
        }
    }
    return false;
}

void SquareRoot::findLargestSquare(string &difference, string &subtractor)
{
    // Check every base (1-9) until you find the one before going over.
    for (int base = 0; base * base <= stoi(pairs[0]); base++)
    {
        answer = to_string(base);
        subtractor = to_string(base * base);

        difference = subtractStrings(pairs[0], subtractor);
    }
}

void SquareRoot::splitIntoPairs()
{
    // Get the length of the radicand (adjusted to always be an even amount of digits) for the amount of pairs
    pairsSize = radicand.length() / 2;
    pairs = new string[pairsSize];

    int pairIndex = 0;

    // Index gets incremented by 2 every time to grab pairs
    for (int index = 0; index <= radicand.length() - 2; index += 2)
    {
        string pair = {radicand[index], radicand[index + 1]};
        pairs[pairIndex] = pair;
        pairIndex++;
    }
}

void SquareRoot::addDecimal()
{
    // The size of the pair array indicates where the decimal goes.
    string tempAns;
    for (int i = 0; i < answer.length() + 1; i++)
    {
        // Copy the current number into the temp answer
        if (i < pairsSize)
        {
            tempAns += answer[i];
        }
        // Copy the next number into the temp answer because were past the decimal now
        else if (i > pairsSize)
        {
            tempAns += answer[i - 1];
        }
        // Place the decimal
        else
        {
            tempAns += ".";
        }
    }
    answer = tempAns;
}

void SquareRoot::longDivide(string &difference, string &subtractor)
{
    for (int i = 1; i <= decimalPlace - 1; i++)
    {
        // Double the current answer
        string answerDoubled = multiplyStrings(answer, "2");

        // This is the variable that holds onto the answer, concated and then multiplied
        string concatMultiplied = "0";

        // This is so we can hold onto the x outside of the for loop.
        int tempx = 0;
        
        // If theres more to grab from pairs.
        if (i < pairsSize)
        {
            difference = difference + pairs[i];
            // Does the same as removeLeadingZeros in theory. However, when using the method I created it failed.
            difference.erase(0, difference.find_first_not_of('0'));
        }
        // Otherwise grab 00 instead of a pair.
        else
        {
            difference = difference + "00";
            difference.erase(0, difference.find_first_not_of('0'));
        }
        // Algorithm for finding the next digit to add to answer. 
        for (int x = 0; !isBiggerThan(concatMultiplied, difference) && x < 10; x++)
        {
            concatMultiplied = multiplyStrings(answerDoubled + to_string(x + 1), to_string(x + 1));
            tempx = x;
        }
        subtractor = multiplyStrings(answerDoubled + to_string(tempx), to_string(tempx));
        answer += to_string(tempx);
        difference = subtractStrings(difference, subtractor);
    }
}

string SquareRoot::takeSquareRoot()
{
    if (radicand.length() % 2 == 1)
    {
        radicand = "0" + radicand;
    }

    splitIntoPairs();

    string subtractor;
    string difference;

    findLargestSquare(difference, subtractor);

    longDivide(difference, subtractor);

    addDecimal();

    return answer;
}

SquareRoot::~SquareRoot()
{
    delete[] pairs;
    pairs = nullptr;
}
