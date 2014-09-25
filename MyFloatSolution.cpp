/**********************************************************************
  Programmer  :  Matt Holloway
  Source      :  MyFloat.cpp
  Compiler    :  Visual C++ .NET

  Description :Partially implements a class, "MyFloat" that permits work
               with floating point numbers between 0 and 1 that have 20
               digits of accuracy.

  Data         Digits of MyFloats are stored in character array
               of [1.. MAX_DIGITS +1], with the zero subscript ignored.
               For example, after storing the real number 0.1207
               in the array Number, the array would look as follows.

            0     1     2     3     4               19   20
         |-----+-----+-----+-----+-----+-       -+-----+-----+
  Number | --- |  1  |  2  |  0  |  7  |   ...   |  0  |  0  |
         |-----+-----+-----+-----+-----+-       -+-----+-----+

	       with the tail end padding with zeros.

           MAX_DIGITS - constant that holds the maximum number of
                        digits of accuracy for MyFloat members.

           NumberofDigits - holds the number of digits that are used
                            to hold the MyFloat.
                            If NumberofDigits is 0,  a MyFloat should
                            be regarded as unitialized or an error.

  Member
  Functions : Digits     Returns number of digits in a MyFloat.

              MaxDigits  Returns the maximum number of allowed digits in MyFloat

              Read       Reads a MyFloat from standard input, if error is
                         detected in reading MyFloat X, X.Digits() should
                         return a 0.

              Write      Writes a leading 0, a decimal point, and then the
                         digits in MyFloat to standard output.  If MyFloat
                         has 0 digits, then error occured, output should be
                         "0.?"

              +          Adds two MyFloats variables X and Y together and
                         stores results in Z.  Standard addition rules apply.
                         Carry over into the ones field is ignored

              ==         returns a 1 if two MyFloats are equal, 0 otherwise


------------------------------------------------------------------------*/
#include <iostream>
#include <ctype.h>
using namespace std;

class MyFloat
{
  private:
    enum {MAX_DIGITS = 20};             // private data members
    char Number[MAX_DIGITS + 1];
    char NumberofDigits;

  public:

    MyFloat()                   // inline default constructor
    {
      NumberofDigits = 0;
    }

    int Digits()                // returns number of digits
    {
      return NumberofDigits;
    }

    int MaxDigits()             // returns maximum number of digits
    {
      return MAX_DIGITS;
    }

    void Read();                // reads a MyFloat from standard input
    void Write() const;         // writes a MyFloat to standard output

    MyFloat operator+ (MyFloat N);  //overloads + for addition of MyFloats

    int operator== (const MyFloat& Rhs); // allows comparison of MyFloats

    friend void AssignValue(MyFloat &X);
  //  Needed only when testing the file testwrt.cpp that test write function
};


/*******************************  Write  **********************************
   Displays a MyFloat X with accuracy to X.NumberofDigits decimal places

-------------------------------------------------------------------------*/
void MyFloat::Write() const
{
  cout << "0.";

  if (NumberofDigits != 0)
     for (int i = 1; i <= NumberofDigits; i++)
	cout << int(Number[i]);           // convert char to int to display
  else
     cout << "?";

}


/*********************************  Read   *******************************
  Uses the following rules in reading a MyFloat

  - White space and leading zero's are skipped

  - if first non-whitespace is not a '0' or a '.' the function returns
    with NumberofDigits set to 0

  - Digits after the decimal point are stored in array Digit

  - Input stops when non-numeric char is encountered. This character is
    left in buffer
-----------------------------------------------------------------------*/
void MyFloat::Read()
{
  int k = 0;
  char Ch;

  NumberofDigits = 0;      //default for illegal or bad input

  cin >> Ch;               // skip leading white spaces

  if ( !cin.good() || (Ch != '0' && Ch != '.'))
     return;                         // bad input, NumberofDigits = 0, return

  while ( Ch == '0' || isspace(Ch) )
     Ch = cin.get();                  // skip leading zero's and spaces

  if ( Ch != '.' || !cin.good() )
     return;                      // if no decimal, bad input, or EOF, return

  Ch = cin.get();                 //get character after decimal

  while ( cin.good() && isdigit(Ch) && k < MAX_DIGITS )
  {
    Number[++k] = Ch - '0';         // convert char to int and store
    Ch = cin.get();                 // get next character
   }

  cin.putback(Ch);     // leave terminating char in input stream
  NumberofDigits = k;

  while ( k < MAX_DIGITS )
    Number[++k] = 0;            // pad number with trailing zero's
}


/*****************************  operator+  ******************************
  Action  :  Will add two MyFloats together and return the MyFloat value.
             Standard addition rules apply, carry over into ones is
             ignored.

  Returns  :  A MyFloat that has addition of two other MyFloats
-----------------------------------------------------------------------*/
MyFloat MyFloat::operator+ (MyFloat N)
{
  MyFloat A;
  int Carry = 0, Sum;

  for (int k = MAX_DIGITS; k >= 1; k--)
    {
      Sum = Number[k] + N.Number[k] + Carry;

      if (Sum <= 9)
	{
	 A.Number[k] = Sum;
	 Carry = 0;
	}
      else
	{
	 A.Number[k] = Sum % 10;
	 Carry = 1;
	}
    }

  if (NumberofDigits > N.NumberofDigits)
     A.NumberofDigits = NumberofDigits;
  else
     A.NumberofDigits = N.NumberofDigits;

  return A;
}

/******************************  operator==  ******************************
  Action  :  Allows two MyFloats to be compared with "=="

  Returns :  1 if two MyFloats are equal, otherwise returns a 0

  Precondition : tail end of Number array is padding with zero's
-------------------------------------------------------------------------*/
int MyFloat::operator== (const MyFloat &R)
{
  int MaxLength;

  if ( NumberofDigits >= R.NumberofDigits )
      MaxLength = NumberofDigits;                // finds longer number
  else
      MaxLength = R.NumberofDigits;

  for (int i = 1; i <= MaxLength; i++)         // if different digits
    if ( Number[i] != R.Number[i] )            // then numbers different
      return 0;

  // Assert:: All digits from 1.. Maxlength are equal

  return 1;
}