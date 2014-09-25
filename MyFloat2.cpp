/***********************  MyFloat Class  ******************************
Name:  Chad Parnin
Date:  March 23, 2014
Homework#:  HW 6
Source File:  MyFloat2.cpp
Action:  -This program builds on the first Float Class project.

		 -It alters the "read and write" member functions
		 to support overloading for class instances (for example:
		 cout << "MyFloatType").  Cascading is supported.

		 -Two additional member functions are added:  > for comparison
		 and = to assign (for example: we can assign ".987" to a 
		 MyFloat instance by using "X = .987").  Cascading is supported.
***********************************************************************/
#include <iostream>
using namespace std;

class MyFloat
{
private:
	enum { MAX_DIGITS = 20 };
	unsigned char Number[MAX_DIGITS + 1];
	unsigned char NumberofDigits;

public:
	MyFloat()  // default constructor
	{
		NumberofDigits = 0;
	}
	int Digits()
	{
		return NumberofDigits;
	}
	int MaxDigits()
	{
		return MAX_DIGITS;
	}
	friend istream& operator >> (istream& Fin, MyFloat &X);  // overloaded read.
															 // declared "friend" to support
															 // lefthand side not being class member
	friend ostream& operator << (ostream& Fout, const MyFloat &X);  // overloaded write - declared "friend".
	MyFloat operator + (MyFloat X);  // overloaded to add 2 MyFloats
	int operator == (const MyFloat& Y);  // overloaded for comparison
	int operator > (const MyFloat& Y);  
	MyFloat& operator = (const char RightSide[]);  // overloaded for assignment
};

/*****************  operator >>  *********************************
Reads a MyFloat and stores a maximum of 20 numbers after decimal.
Supports overloading and cascading in order to do"cin >> X >> Y"
where X and Y are class instances.
Skips leading whitespaces.
Index 0 is '.'.
All elements after that should be digits.
Remaining elements padded with zeros.
Returns "Fin" - a reference to istream.
Class instance passed in by reference to eliminate
need to copy entire class into function (which would be by value).
******************************************************************/
istream& operator >> (istream& Fin, MyFloat &X)
{
	int k = 0;
	char Ch;
	do
	{
		Fin >> Ch;  // get user input
	} while (Ch != '.');  // skip until decimal
	X.Number[0] = Ch;  // index 0 is now a decimal

	Fin.get(Ch);
	while ((Fin.good()) && (isdigit(Ch)) && (k < X.MAX_DIGITS))
	{
		X.Number[++k] = Ch - '0';  // convert to an int and store in array
		Fin.get(Ch);
	}
	Fin.putback(Ch);  // put newline back in buffer
	X.NumberofDigits = k;
	for (++k; k <= X.MAX_DIGITS; k++)  // convert remaining elements to "0"
		X.Number[k] = 0;

	return Fin;  // return reference to istream
}

/****************  operator <<  *********************
Writes a MyFloat to standard output.
Supports overloading and cascading in order to do
"cout << X << Y" where X and Y are class instances.
Returns "Fout", a reference to ostream.
Class instance passed in by reference to eliminate
need to copy entire class into function
(which would be by value)
****************************************************/
ostream& operator << (ostream& Fout, const MyFloat &X)
{
	Fout << "0.";

	if (X.NumberofDigits == 0)  // if no digits or has an input error
		cout << "?";

	for (int i = 1; i <= X.NumberofDigits; i++)
		Fout << int(X.Number[i]);  // display an int value

	return Fout;  // return reference to ostream
}

/*****************  operator +  ****************************
Overloaded member function to add 2 MyFloats,
then returns new MyFloat (Z).
Adds same indexes then carries to next column if needed,
just like regular addition.  Carry over into ones place
is not outputted.
Determines which MyFloat (X or Y) has more digits after
adding- then Z takes that NumberOfDigits.
Passing in right hand operand "MyFloat Y" from "Z = X + Y".
Left hand operand "MyFloat X" is "Number[]"
***********************************************************/
MyFloat MyFloat::operator + (MyFloat Y)  
{
	MyFloat Z;
	int Carry = 0, Sum;

	for (int k = MAX_DIGITS; k >= 1; k--)
	{
		Sum = Number[k] + Y.Number[k] + Carry;  // add a column

		if (Sum <= 9)  // no carry addition
		{
			Z.Number[k] = Sum;
			Carry = 0;
		}
		else  // carry addition
		{
			Z.Number[k] = Sum % 10;
			Carry = 1;
		}
	}

	if (NumberofDigits > Y.NumberofDigits)  // set Z number of digits the higher array
		Z.NumberofDigits = NumberofDigits;
	else
		Z.NumberofDigits = Y.NumberofDigits;

	return Z;
}

/******************  operator ==  *************************
Overloaded member function to compare 2 MyFloats by looking
at each index.
Accounts for the fact that ".2" is the same as ".20"
Passing in right hand operand "MyFloat Y" from "if X == Y"
Left hand operand "MyFloat X" is "Number[]"
**********************************************************/
int MyFloat::operator == (const MyFloat& Y)  
{
	for (int i = 1; i < MAX_DIGITS; i++)
	{
		if (Number[i] == Y.Number[i])
			continue;
		else
			return 0;  // doesn't match- return false
	}
	return 1;  // they do match- return true
}

/*****************  operator =  ***************************
Overloaded member function to convert a string representing
a float to a MyFloat class instance.
For example:  A user could enter X = ".8987" that would
store the string into X, a class instance.
Can be cascaded (X = Y = Z).
Passes in Rightside[] to store into Number[] class member.
***********************************************************/

MyFloat& MyFloat::operator = (const char RightSide[])
{
	int k = 0;
	int i = 0;

	while (RightSide[k] != '.')  // look for decimal
		k++;
	Number[i] = RightSide[k];  // Number[0] is now decimal
	++k;
	while ((isdigit(RightSide[k])) && (k <= MAX_DIGITS) && (RightSide[k] != 0))
	{
		Number[++i] = RightSide[k] - '0';  // duplicate and convert to int
		k++;
	}
	NumberofDigits = i;

	return *this;  // return reference to lefthand side
}

/*****************  operator >  ***************************
Overloaded member function to compare 2 MyFloats by looking
at each index.
Passing in right hand operand "MyFloat Y" from "if X > Y"
Left hand operand "MyFloat X" is "Number[]"
**********************************************************/

int MyFloat::operator > (const MyFloat& Y)
{
	int k = 1;

	while (k <= NumberofDigits || k <= Y.NumberofDigits)
	{
		if (Number[k] > Y.Number[k])
			return 1;
		else if (Number[k] < Y.Number[k])
			return 0;
		else
			++k;
	}
}