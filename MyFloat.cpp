/***********************  MyFloat Class  ******************************
Name:  Chad Parnin
Date:  March 9, 2014
Homework#:  HW 5
Source File:  MyFloat.cpp
Action:  This program creates an abstract data type called MyFloat.
		 It is a class that can read, add, and compare decimal
		 fractions up to 20 digits long (after the decimal).
		 C++ cannot provide such accuracy with floats, which is
		 why an ADT class needs to be created.  Chars are converted
		 to ints in Number[] to limit memory use.
		 The specification and implementation file are all in this file.
		 Testing the class is being done on seperate file called
		 TestMyFl.cpp.
***********************************************************************/
#include <iostream>
using namespace std;

class MyFloat
{
private:
	enum { MAX_DIGITS = 20 };
	char Number[MAX_DIGITS + 1];  // decimal is index 0, numbers start at index 1
	char NumberofDigits;

public:
	MyFloat();  // default constructor
	int Digits();  // counts # of digits
	int MaxDigits();  // always 20
	void Read();  // reads a MyFloat from user
	void Write();  // displays to screen, const to ensure data is not changed
	MyFloat operator+ (MyFloat X);  // overloaded so we can add 2 MyFloats
	int operator== (MyFloat X);  // overloaded so we can compare 2 MyFloats
};  // End of specification file

//implementation file follows

/******  MyFloat constructor  **********
The default constructor that initializes
Number[] and NumberofDigits to 0.
***************************************/
MyFloat::MyFloat()
{
	for (int i = 0; i < MAX_DIGITS; i++)
		Number[i] = 0;
	NumberofDigits = 0;
}

/*************  Digits  ******************
Returns the number of digits in a MyFloat.
*****************************************/
int MyFloat::Digits()
{
	return NumberofDigits;
}

/**********  MaxDigits  ****************
Returns the maximum number of digits
in a MyFloat.
***************************************/
int MyFloat::MaxDigits()
{
	return MAX_DIGITS;
}

/*********************  Read  **************************
Reads a MyFloat and stores numbers into character array
of max size 21.  Remaining elements set to 0.  
Skips leading whitespaces.
Index 0 will be decimal point, and remaining elements
must be digits (20 max numbers).
*******************************************************/
void MyFloat::Read()
{
	int k = 0;
	char Ch;
	do
	{
		cin.get(Ch);  // get user input
	} while (Ch != '.');  // look for decimal
	Number[0] = Ch;  // index 0 is now a decimal
	cin.get(Ch);
	while ((isdigit(Ch)) && (k < MAX_DIGITS))
	{
		Number[k + 1] = Ch - '0';  // store in array and convert to an int
		k++;
		cin.get(Ch);
	}
	cin.putback(Ch);  // put "\n" back in buffer
	NumberofDigits = k;
	for (++k; k <= MAX_DIGITS; k++)  // convert remaining elements to "\0"
		Number[k] = '0' - '0';
}

/*******************  Write  ************************
Displays "0." before writing MyFloat array to output.
If no digits, then display "?".
Converts to int for output.
****************************************************/
void MyFloat::Write()
{
	cout << "0.";

	if (NumberofDigits == 0)  // if no digits / has an input error
		cout << "?";

	for (int i = 1; i <= NumberofDigits; i++)  // display user defined instance
		cout << int(Number[i]);
}

/*****************  operator +  *************************
Overloaded member function to add 2 MyFloats from caller,
then returns new MyFloat (Z).
Must determine which MyFloat (X or Y) has more digits.
Adds same indexes then carries to next column if needed,
just like regular addition.  Carry over into ones place
is not outputed.
********************************************************/
MyFloat MyFloat::operator+ (MyFloat Y)  // passing in right hand operand "MyFloat Y" from "Z = X + Y"
										// left hand operand "MyFloat X" is "Number[]"
{
	MyFloat Z;  // create a MyFloat to store sum of "X + Y"

	int CarryCount = 0;  // column carry count for addition > 9
	if (NumberofDigits >= Y.NumberofDigits)  // Need to determine which MyFloat has more digits
											 // so no numbers are left out.  We have to do this
											 // so as not to display unecessary 0's at the end
											 // this "if statement" is if lefthand operand is bigger (X)
	{
		for (int i = NumberofDigits; i > 0; i--)  // use the MyFloat that has more digits
		{
			Z.Number[i] = Number[i] + Y.Number[i];
			Z.NumberofDigits++;
			if (CarryCount == 1)  // add the carry amount if appropriate
				++Z.Number[i];
			if (Z.Number[i] > 9)  // determine if carrying needed during addition  
			{
				Z.Number[i] = Z.Number[i] % 10; // only use rightmost digit if sum is > 9
				CarryCount = 1;
			}
			else
				CarryCount = 0;
		}
	}
	if (NumberofDigits < Y.NumberofDigits)  // if righthand operand is bigger (Y)
	{
		for (int i = Y.NumberofDigits; i > 0; i--)
		{
			Z.Number[i] = Number[i] + Y.Number[i];
			Z.NumberofDigits++;
			if (CarryCount == 1)
				++Z.Number[i];
			if (Z.Number[i] > 9)
			{
				Z.Number[i] = Z.Number[i] % 10;
				CarryCount = 1;
			}
			else
				CarryCount = 0;
		}
	}
	return Z;  // return MyFloat Z (which has the sum of X + Y arrays)
}

/*****************  operator ==  *************************
Overloaded member function to compare 2 MyFloats (x and Y)
Accounts for the fact that ".2" is the same as ".20"
*********************************************************/
int MyFloat::operator== (MyFloat Y)  // passing in right hand operand "MyFloat Y" from "X == Y"
									 // Left hand operand "MyFloat X" is "Number[]"
{
	for (int i = 1; i < MAX_DIGITS; i++)
	{
		if (Number[i] == Y.Number[i])
			continue;
		else
			return 0;  // if index doesn't match- they don't match
	}
	return 1;  // they do match- return true
}