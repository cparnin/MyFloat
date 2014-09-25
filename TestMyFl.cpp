/*************************************************************************

PROGRAMMER: John Russo  and  Matt Holloway
SOURCE:     TestMyFl.cpp

COMPILER:   Visual C++ .NET

ACTION:     Driver to test functions in the class member function of
MyFloat.cpp. At present, these include:

Read          Reads a MyFloat from standard input. Standard
reading conventions should be followed.

Write         Writes a leading 0, a decimal point, and the
digits in a MyFloat to standard output.

Digits        Returns the number of digits of a MyFloat.

MaxDigits     Returns the maximum number of digits of MyFloat.

+             Adds two MyFloat variables together using standard
addition rules. Carry over into the ones place on
left of decimal is ignored and left to be zero.
Example output:
X   0.514
+ Y   0.52
-----------
Z   0.034       note 5+5 resulted in 0 with no
carry over into ones place

==            Returns 1 if two MyFloats are equal, 0 otherwise.


IMPORTANT:  The program assumes that the Write function has been tested
and is working properly. Consider using the following
simple program to test your Write function first:
But first go into your MyFloat.cpp file and put the following
prototype in after your other prototypes, when this small
program works go back in and then remove this prototype.
Prototype is as follows: Type in whole line as is

friend void AssignValue(MyFloat& X);

Then create a little program and do and type as follows:

#include <iostream>
#include "MyFloat.cpp"
using namespace std;

void AssignValue(MyFloat& X)
{
X.Number[1] = 1;
X.Number[2] = 2;
X.Number[3] = 3;          // run program first this way with
X.NumberofDigits = 3;     // these numbers then change
}                           // X.NumberofDigits = 0, to test
// "0.?", which stands for an error

void main()
{
MyFloat X;

AssignValue(X);

cout << "X = ";
X.Write();
cout << endl << "Press Enter key to continue";
cin.ignore();
}

**NOTE** In MyFloat class data member "char Number[]" ignore the zero
subscript when filling in the Number array, so start at
subscript number 1

**NOTE** On Read member function.  Use cin.putback(Ch) after last successful
input before you leave this function. This will put back the
newline character into the input buffer.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#include "MyFloat.cpp"      //  Name of your class definition. Use pathname
//   if file not in current working directory.
#include <iostream>
#include <ctype.h>
using namespace std;

void DisplayOptions();       //  Menu related functions.
void GetChoice(char& Ch);
int  SpaceBarToContinue();

void TestRead();            //  Drivers to test functions in MyFloat class
void TestWrite();
void TestDigits();
void TestAddition();
void TestComparison();

//==============================  main   =================================
void main()
{
	char Choice;

	do
	{
		DisplayOptions();

		GetChoice(Choice);

		cout << "\n\n\n";

		switch (Choice)
		{
		case '1': TestRead();
			break;

		case '2': TestAddition();
			break;

		case '3': TestDigits();
			break;

		case '4': TestComparison();
			break;

		case 'Q':;           // Exit
		};
	} while (Choice != 'Q');
}

/***********************  SpaceBarToContinue    **************************

Displays "Press Spacebar then Enter key to continue:"
Returns 1 iff Spacebar pressed.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
int SpaceBarToContinue()
{
	char Ch;

	cout << "\n\n---------------------------"
		"  Press Spacebar then Enter key to continue: ";

	cin.get(Ch);
	cin.ignore(10, '\n');   //gets rid of newline left in buffer

	return (Ch == ' ');
}

/***********************  DisplayOptions   *******************************

Displays a menu of choices.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void DisplayOptions()
{
	cout << " \nTesting Member Functions of MyFloat Class\n";

	cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	cout << "   1)  Test Read function \n";

	cout << "   2)  Test + operator \n";

	cout << "   3)  Test MaxDigits and Digits \n";

	cout << "   4)  Test ==  operator \n";

	cout << "   Q)  Quit program \n\n";

	cout << "Choice? ";
}

/***********************  GetChoice   ************************************

Reads a char from the keyboard, provides a redirectable echo and
upcases the char.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void GetChoice(char& Ch)
{
	cin.get(Ch);
	Ch = toupper(Ch);
}

/*********************  TestRead   ***************************************

Allows testing of the member function Read of MyFloat.

The Write function is assumed to be correct!
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestRead()
{
	MyFloat X;

	cout << "\n>>>>>>>>  Testing Read function  >>>>>>>>>>>>\n";
	do
	{
		cout << "\nEnter a MyFloat ==> ";
		X.Read();
		cin.ignore(1000, '\n');         //  Discard all chars in input stream.

		if (X.Digits() == 0)       //  No significant digits
			cout << "\nInput error! ";

		cout << "\nAfter read,   X = '";
		X.Write();
		cout << "'\n";

	} while (SpaceBarToContinue());
}

/*********************  TestDigits   *************************************

Allows testing of the member functions Digits and MaxDigits.

This routine assumes that input and output functions for MyFloats
have been written and debugged.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestDigits()
{
	MyFloat X;

	cout << "\n============ Testing Digits and MaxDigits  ==============\n\n";

	cout << "X.MaxDigits() = " << X.MaxDigits() << " \n\n";

	do
	{
		cout << "\nEnter MyFloat ==> ";
		X.Read();
		cin.ignore(1000, '\n');           //  Discard all chars in input stream.
		cout << "\nDigits("; X.Write();
		cout << ") = " << X.Digits() << endl;
	} while (SpaceBarToContinue());
}

/*********************  TestAddition   *********************************

Allows testing of the member functions "+" of MyFloat.

This routine assumes that input and output functions for MyFloats
have been written and debugged.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestAddition()
{
	MyFloat X, Y, Z;

	cout << "\n------------  Testing \"+\" for MyFloat --------------------\n";
	do
	{
		cout << "\nEnter a MyFloat X ==> ";
		X.Read();
		cin.ignore(1000, '\n');         //  Discard all chars in input stream.

		if (X.Digits() == 0)         //  Error in input X, no digits
		{
			cout << "\nFormat error! ";
			cout << "\n     'X = ";
			X.Write();
			cout << "'" << endl;
			continue;                   // no more input redo loop
		}

		cout << "\nEnter another MyFloat Y ==> ";
		Y.Read();
		cin.ignore(1000, '\n');         //  Discard all chars in input stream.

		if (Y.Digits() == 0)         //  Error in input Y, no digits
		{
			cout << "\nFormat error! ";
			cout << "\n     'Y = ";
			Y.Write();
			cout << "'" << endl;
			continue;                 // no calculation redo loop
		}

		Z = X + Y;                     // add two MyFloats together

		if (Z.Digits() == 0)         //  Error in addition
			cout << "\nFormat error! ";

		cout << "\n  X    ";
		X.Write();

		cout << "\n+ Y    ";
		Y.Write();

		cout << "\n---------";
		int i;
		for (i = 1; i <= Z.Digits(); i++)   // this displays '---------'
			cout << "-";                          // to output device
		cout << "\n  Z    ";

		Z.Write();
	} while (SpaceBarToContinue());
}

/*********************  TestComparison   *********************************

Allows testing of the member function operator==.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestComparison()
{
	MyFloat X, Y;

	cout << "\n\n============  Testing \"==\"  for MyFloat  ================\n";

	do
	{
		cout << "\nEnter X  ==> ";
		X.Read();
		cin.ignore(1000, '\n');             //  Discard all chars in input stream.
		cout << "\nEnter Y  ==> ";
		Y.Read();
		cin.ignore(1000, '\n');             //  Discard all chars in input stream.

		cout << "\n\n";

		if (X == Y)
		{
			X.Write(); cout << " is equal to "; Y.Write();
		}
		else
		{
			X.Write(); cout << " is NOT equal to "; Y.Write();
		}
	} while (SpaceBarToContinue());
}