/*************************************************************************

PROGRAMMER:   Chad Parnin (with Matt Holloway and John Russo)
DATE:		  April 23, 2014
HW:           HW 10
SOURCE:       MyFloatD.cpp
COMPILER:     Visual C++ .NET /  Clang (Apple)

DESCRIPTION:  Program that defines a class MyFloat that can dynamically
              create floats of any size (between 0 and 1).
 
              Has the following characteristics:
 
                - constructors to initialize default size, user defined
                    size, deep copy of class, and destructor
                - overloaded = operators to create unique floats and
                    also allow deep copy of class
                - overloaded istream (extraction) and ostream (insertion)
                    operators to allow "cin >> X" & "cout << X"
                - overloaded +, ==, > operators for comparison / addition

*************************************************************************/
#include <iostream>
using namespace std;

class MyFloat
{
	//private members
    
	enum { DEFAULT_LENGTH = 10 };       // private data members
	char* Num;                          // pointer to create dynamic MyFloat
	int Len;
	int MaxLen;	

public:
	// constructors
    
	~MyFloat();							// destructor
	MyFloat(const MyFloat &S);			// deep copy class constructor
	MyFloat();							// default
	MyFloat(unsigned MaximumLength);    // class constructor of any length
	
	//operators
    
	MyFloat& operator = (char Rhs[]);          // allows X = "0.12345"
	MyFloat& operator = (const MyFloat &Rhs);  // allows deep copy X = Y

	friend ostream& operator << (ostream &Sout, const MyFloat &X);  // overloaded insertion
	friend istream& operator >> (istream &In, MyFloat &X);          // overloaded extraction

	MyFloat operator + (const MyFloat &Rhs);  // overloaded +
	int operator == (const MyFloat &Rhs);     // overloaded ==
	int operator >  (const MyFloat &Rhs);     // overloaded >

	int Digits()
	{
		return Len;
	}

	int MaxDigits()
	{
		return MaxLen;
	}
};

/****************************  Destructor **********************************
 
ACTION:  Frees up memory by destroying the dynamic MyFloat when out of scope.

- - - -  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

MyFloat::~MyFloat()
{
	delete Num;
}

/**********************  Deep Copy Class Constructor *********************
 
ACTION:  Allows class instances of "X = Y".
         Deep copies all elements by creating new dynamic MyFloat.
         Passes in reference to a MyFloat instance.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

MyFloat::MyFloat(const MyFloat &S)
{
	MaxLen = S.MaxLen;
	Len = S.Len;

	// create new dynamic array for deep copy
	// account for index 0 being decimal
	Num = new char[MaxLen + 1];

	if (Num != NULL)			// copy elements
		for (int k = 0; k <= Len; k++)
			Num[k] = S.Num[k];
	else
		MaxLen = 0;				// memory allocation error
}

/**********************  Default Constructor ******************************
 
ACTION:  Default constructor to create new MyFloat and
         initialize elements to 0.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

MyFloat::MyFloat()
{
	Len = 0;
	MaxLen = DEFAULT_LENGTH;
	Num = new char[DEFAULT_LENGTH + 1];  // create new dynamic array
	if (Num == NULL)				
		MaxLen = 0;
}

/**********************  Class Constructor ********************************
 
ACTION:  Constructor to allow MyFloat of user defined size - "MyFloat X(50)"
         Passes in copy of the SIZE the user wants.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

MyFloat::MyFloat(unsigned MaximumLength)
{
	// create new dynamic array of size MaximumLength + 1
	Num = new char[MaximumLength + 1];

	Len = 0;
	if (Num == NULL)
		MaxLen = 0;
	else
		MaxLen = MaximumLength;
}

/***************************  operator=   ********************************

DESCRIPTION: Allows MyFloat assignments of the form X = "0.1223334444".

PARAMETERS:  Rhs (RightHandSide) a null terminated char array that represents
             a floating point number between 0 and 1. Blanks, zeros,
             and letters that precede the decimal point are ignored.

RETURNS:     Reference to *this - the newly changed MyFloat.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

MyFloat& MyFloat::operator = (char Rhs[])
{
	int k = 0, n;

	Len = 0;						// Flag to indicate uninitialized MyFloat

	while ((isspace(Rhs[k]) || Rhs[k] == '0') && Rhs[k] != 0)  //  Skip blanks and zeros
		++k;

	// Rhs[k] == '.' 

	if (Rhs[k] != '.')
		return *this;  // Error, no decimal point

	++k;               // Move to char after '.'

	n = 1;

	while (n <= MaxLen && isdigit(Rhs[k]))  //  Copy rest of string
		Num[n++] = Rhs[k++] - '0';

	Len = n - 1;

	while (n < MaxLen)  // Pad with trailing zeros
		Num[++n] = 0;

	return *this;
}

/***************************  operator =   ********************************
 
 DESCRIPTION: Allows MyFloat assignments of the form X = Y
 
 PARAMETERS:  rightside reference parameter to a MyFloat
 
 RETURNS:     *this - reference to left side of "= operator"

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

MyFloat&  MyFloat::operator = (const MyFloat &Rhs)
{
	int k = 0;

	if (this == &Rhs)  // if identical, return
		return *this;

	if (MaxLen < Rhs.Len)  // not enough room in *this
	{
		delete Num;		   // free memory

		Num = new char[Rhs.Len + 1];  // create another
		if (Num == NULL)
		{
			MaxLen = 0;
			return *this;			  // return reference to leftside
		}
		MaxLen = Rhs.Len;			  // MyFloat now has longer max length
	}
	Len = Rhs.Len;					  // new MyFloat now has length of Rhs

	for (k = 0; k <= Rhs.Len; k++)    // copy everything
		Num[k] = Rhs.Num[k];
	
	return *this;
}

/**********************  operator << **************************************

 DESCRIPTION: Overloaded insertion operator to display MyFloat array
 
 PARAMETERS:  reference to ostream and a MyFloat
 
 RETURNS:     reference to ostream (Sout)

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

ostream& operator << (ostream &Sout, const MyFloat &X)
{
	Sout << "0.";

	if (X.Len == 0)					// if no digits or has an input error
		Sout << "?";

	for (int i = 1; i <= X.Len; i++)
		Sout << int(X.Num[i]);		// convert to an int value

	return Sout;					// return reference to ostream
}

/*********************   operator >>  ***********************************

User defined MyFloat up to DEFAULT_LENGTH

- White space and leading zeros are skipped

- If first non-whitespace char is not a '0' or '.' the function
returns, with this->Len set to 0.

- Digits after the decimal point are stored in this->Num array
 
 PARAMETERS:  reference to istream and a MyFloat
 
 RETURNS:     reference to istream (In)
 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

istream& operator >> (istream &In, MyFloat &X)
{
	char Ch;
	int  N;

	X.Len = 0;

	In >> Ch;                                      //    Skip whitespace.

	if (!In.good() || Ch != '.' && Ch != '0')
		return In;                                 //  NumberofDigits is 0.

	while (isspace(Ch) || Ch == '0')       //  Skip leading zeros and spaces
		Ch = In.get();

	if (Ch != '.' || !In.good())	// Input error or eof
		return In;

	In.get(Ch);                     //  Get first char to right of '.'

	X.Len = 1;					    //  We have at least 1 significant

	N = 0;
	while (isdigit(Ch) && In.good() && N < X.MaxLen)
	{
		X.Num[++N] = Ch - '0';            //  Convert char to int
		Ch = In.get();
	}

	In.putback(Ch);     // put back last character read into input stream

	X.Len = N;

	while (N < X.MaxLen)       // Pad with trailing zeros
		X.Num[++N] = 0;

	return In;
}

/**********************   operator +   ***********************************
 
 DESCRIPTION:  Overloaded member function to add 2 MyFloats
			   (up to DEFAULT_LENGTH), then returns new MyFloat (A).
               Must determine which MyFloat (X or Y) has more digits.
               Adds same indexes then carries to next column if needed,
               just like regular addition.  Carry over into ones place
               is not outputted.
 
 PARAMETERS:   rightside reference to a MyFloat
 
 RETURNS:      newly created MyFloat (A)

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

MyFloat MyFloat::operator + (const MyFloat &Rhs)
{
	MyFloat A;								// create new MyFloat to hold sum
	int Carry = 0, Sum;

	for (int k = MaxLen - 1; k >= 1; k--)		// get ready to do addition from right
	{
		Sum = Num[k] + Rhs.Num[k] + Carry;  // normal addition plus carry bit 

		if (Sum <= 9)						// no need to carry
		{
			A.Num[k] = Sum;
			Carry = 0;
		}
		else                                // need to carry if column is >= 10
		{
			A.Num[k] = Sum % 10;
			Carry = 1;
		}
	}

	if (Len > Rhs.Len)						// adjust lengths accordingly
		A.Len = Len;
	else
		A.Len = Rhs.Len;

	return A;
}

/**********************   operator ==  *************************************
 
 DESCRIPTION:  Overloaded == comparison operator to compare 2 MyFloats
			   (up to DEFAULT_LENGTH).
			   .2" is the same as ".200
 
 PARAMETERS:   rightside reference to a MyFloat
 
 RETURNS:      True or False if they are identical

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

int MyFloat::operator == (const MyFloat &Rhs)
{
  int MaxLength, k;

  if ( Len <= Rhs.Len )		// adjust lengths accordingly
    MaxLength = Rhs.Len;
  else
    MaxLength = Len;

  for ( k = 1; k <= MaxLength; ++k )  // comparing indexes...
    if ( Num[k] != Rhs.Num[k] )
      return 0;

  //  Assert:  All digits from 1..MaxLength are equal

  return 1;
}

/**********************   operator >   ***********************************
 
 DESCRIPTION:  Overloaded > comparison operator.
 
 PARAMETERS:   rightside reference to a MyFloat
 
 RETURNS:      True if lefthand side is greater, false if it's less 

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

int MyFloat::operator >  (const MyFloat &Rhs)
{
	int k, ShortestNumberOfDigits;

	ShortestNumberOfDigits = (Len < Rhs.Len)
		? Len : Rhs.Len;


	for (k = 1; k <= ShortestNumberOfDigits; ++k)
		if (Num[k] < Rhs.Num[k])
			return 0;
		else if (Num[k] > Rhs.Num[k])
			return 1;

	//  Assert: Shorter operand has digits identical to first digits of longer

	if (Len >= Rhs.Len) // Rhs is not shorter and
		return 1;       // therefore not smaller

	else                // *this has more digits
		return 0;
}