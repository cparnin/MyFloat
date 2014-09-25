/*************************************************************************
 
 PROGRAMMER: John Russo  slightly modified by Matt Holloway
 SOURCE:     TestDyMF.cpp
 COMPILER:   Visual C++ .NET
 
 ACTION:     Tests some the functions in the class defined in MyFloatD.CPP,
 a dynamically allocated class that implements floats that
 have perfect accuracy in representing decimals.
 
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "MyFloatD.cpp"   //  Name of your class definition.
#include <iostream>
#include <iomanip>
using namespace std;

void DisplayTestingOptions();
void GetChoice(char& Ch);

void TestInputOperator();
void TestAssignment();
void TestCopyConstructor();
void TestComparison();
void TestPlus();
void TestDestructor();

float CPU_Seconds();

//==============================  main   =================================

int main()
{
    char    Choice;
    
    do
    {
        
        DisplayTestingOptions();
        
        GetChoice(Choice);
        
        switch ( Choice )
        {
            case '1': TestCopyConstructor();
                break;
            case '2': TestAssignment();
                break;
            case '3': TestInputOperator();
                break;
            case '4': TestPlus();
                break;
            case '5': TestComparison();
                break;
            case '6': TestDestructor();
                break;
            case 'Q':      ;                           // Exit
        };
    }
    while ( Choice != 'Q' );
    
    return 0;
}

/***********************  SpaceBarToContinue    **************************
 
 Displays "Spacebar to continue" and returns 1 iff Spacebar pressed.
 
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
int SpaceBarToContinue(char* Message = "  Spacebar continues this test")
{
    char Ch;
    
    cout << "\n------------------------------------------"
    <<   Message;
    Ch = cin.get();
    
    return ( Ch == ' ' );
}

/***********************  DisplayTestingOptions   ************************
 
 Displays a menu of choices.
 
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void DisplayTestingOptions()
{
    const char* TAB = "     ";  // Provides menu spacing
    
    cout << "\n\n";
    cout << "\n----------------------------------"
    "------------------------------------\n\n";
    
    cout << TAB << "1)  Test copy constructor     ";
    
    cout << TAB << "2)  Test assignment operator \n";
    
    cout << TAB << "3)  Test >> input function    ";
    
    cout << TAB << "4)  Test + operator       \n";
    
    cout << TAB << "5)  Test == operator          ";
    
    cout << TAB << "6)  Test destructor       \n";
    
    cout << TAB << "Q)  Quit program\n\n";
    
    cout << "Choice? ";
    
}

/***********************  GetChoice   ************************************
 
 Reads a char from the keyboard, provides a redirectable echo and
 upcases the char.
 
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void GetChoice(char& Ch)
{
    cin >> Ch;
    Ch = toupper(Ch);
    
}

/*********************  TestInputOperator   ******************************
 
 Allows testing of the member functions ">>" of MyFloat.
 
 The insertion operator << is assumed to be correct.
 
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestInputOperator()
{
    MyFloat X;
    
    cout << "\n\n>>>>>>>>>>>>>  Testing input operator >>>>>>>>>>>>>>>>>\n";
    do
    {
        cout << "\nEnter MyFloat ==> ";
        cin  >> X;
        
        cout << "\nAfter the read,  X = '" << X << "'\n\n";
    }
    while ( SpaceBarToContinue() );
    
    if (cin.peek() != EOF)
        cin.ignore(1000, '\n');
    
}


/*********************  TestAssignment   *********************************
 
 Allows testing of the member function "=" of MyFloat. If a deep copy
 assignment operator has not been written, the code below will give
 unexpected output.
 
 This routine assumes that input and output functions for MyFloats
 have been written and debugged.
 
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestAssignment()
{
    MyFloat X(10), Y(10);
    
    cout << "\n\n------------  Testing '='  for MyFloats   --------------------\n\n";
    
    X = "0.1234567890";
    
    Y = X;                // This must be a deep copy
    
    X = "0.0";            // Or this will change Y!
    
    cout << "\nAfter the assignments, X = \"0.1234567890\", Y = X, and X = 0.0, "
    << "Y = " << Y << endl;
    
}


/*********************  TestPlus   ***************************************
 
 Allows testing of the member function operator+. At the present time,
 it allows testing only of addition for MyFloats that have the default
 length.
 
 NOTE:  Calls two of the copy constructors. The copy constructor also
 needs to be working correctly for + to work.
 
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestPlus()
{
    MyFloat X(12), Y, Sum;
    
    
    cout << "\n\n++++++++++++++++  Testing \"+\"  for MyFloat  ++++++++++++++++\n"
    << "                  (Do not use leading zero)\n";
    do
    {
        cout << "\nEnter X  ==>   ";
		cin >> X;
        cin.ignore(1000, '\n');         //  Discard all chars in input stream.
        
        cout << "\nEnter Y  ==> + ";
        cin >> Y;
        
        cin.ignore(1000, '\n');         //  Discard all chars in input stream.
        cout << "             ";
        
        for ( int k = 1; k <= X.Digits() + 3 || k <= Y.Digits() + 3 ; ++k )
            cout << '-';
        
        cout << "\n              ";
        
        Sum = X + Y;
        
        cout << Sum << "\n\n";
        
    }
    while ( SpaceBarToContinue() );
}


/*********************  TestCopyConstructor   ****************************
 
 Allows testing of the copy constructor that is called automatically
 under certain circumstances.
 
 Note that that the default constructor and the overloaded "=" operator
 must also be working properly.
 
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestCopyConstructor()
{
    MyFloat X;      // Default constructor called
    
    X = "0.12345";  // Overloaded "=" operator called
    
    MyFloat Y = X;  // Copy constructor called
    
    X = "0.0";
    
    cout << "\n\n============ Testing copy constructor  ================\n\n";
    cout << "NOTE: This function also calls default constructor and '='operator. \n\n\n";
    
    cout << "After 'X = 0.0',  Y = " << Y << "\nNote that Y should be 0.12345\n";
    
}

/*********************  TestComparison   *********************************
 
 Allows testing of the member function operator+. At the present time,
 it allows testing only of addition for MyFloats that have the default
 length.
 
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestComparison()
{
    MyFloat A, B, Sum;
    
    
    cout << "\n\n== == == == ==  Testing \"== \" for MyFloat  == == == == == \n\n";
    
    cout << "MyFloat variables have maximum length of " << A.MaxDigits() << endl;
    do
    {
        cout << "\nEnter A  ==> ";
        cin  >> A;
        cout << "\nEnter B  ==> ";
        cin  >>  B;
        
        cout << "\n (A == B) is " << ((A == B) ? "TRUE " : "FALSE ") << endl;
        
        
    }
    while ( SpaceBarToContinue() );
}


/*********************  TestDestructor  **********************************
 
 Tests to see if the class destructor has been correctly written. If not
 this program may crash.
 
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestDestructor()
{
    
    const unsigned long REPETITIONS = 70000;
    
    for ( unsigned long N = 1;  N <= REPETITIONS;  ++N )
    {
        MyFloat X(10000);  // Create 1000 digit MyFloat
    }                 // X goes out of scope at each repetition
    
    // If the destructor is not correct, each repetition of the
    // loop above will caused some memory leak and the call to
    // new below will fail.
    
    int* A = new int[120];
    
    if ( A == NULL )
        cout << "\n\nYour memory has leaked away!\n";
    else
    {
        delete [] A;
        cout << "\n\n~~~~~~~~~~~~~~  destructor is OK!  ~~~~~~~~~~~~~~~\n";
    }
    SpaceBarToContinue(" spacebar to continue");
}