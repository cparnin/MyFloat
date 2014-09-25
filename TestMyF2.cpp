/*************************************************************************
 PROGRAMMER: John Russo, modified some by Matt Holloway
 SOURCE:     TestMyF2.cpp
 
 COMPILER:   Visual C++ .NET
 
 ACTION:     Driver to test functions in the class member functions of
 MyFloat2.CPP. At the present, these include.
 
 >>            Reads a MyFloat from standard intput. Standard
 reading conventions should be followed.
 
 <<            Writes a leading 0, a decimal point, and the
 digits in a MyFloat to standard output. If the
 MyFloat is unititialized, a "0.?" is output.
 
 Digits        Returns the number of valid digits of a
 MyFloat.
 
 MaxDigits     Returns the maximum number of valid digits of
 MyFloat.
 
 =             Converts a string representing a float between
 0 and 1 to a MyFloat. For example, if X is an
 instance of MyFloat, a programmer could use
 X = "0.1234567";
 
 ==            Returns 1 if two MyFloats are equal, 0 otherwise.
 
 >             Returns 1 if left hand side MyFloat is greater
 than the rhs, 0 otherwise.
 
 +             Computes the sum of two MyFloats.
 See MyFloat.cpp for a description of how
 MyFloats are implemented.
 
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#include "MyFloat2.cpp"     //  Name of your class definition. Use pathname
//    if file not in current working directory.
#include <ctype.h>
#include <iostream>
#include <iomanip>
using namespace std;

void DisplayOptions();     //  Menu related functions.
void GetChoice(char& Ch);
int  SpaceBarToContinue();

void TestRead();           //  Drivers to test functions in MyFloat class
void TestWrite();
void TestPlus();
void TestDigits();
void TestAssignment();
void TestComparison();
void TestEfficiency();

//==============================  main   =================================

int main()
{
    char Choice;
    
    do
    {
        DisplayOptions();
        
        GetChoice(Choice);
        
        cout << "\n\n\n";
        
        switch ( Choice )
        {
            case '1': TestRead();
                break;
                
            case '2': TestAssignment();
                break;
                
            case '3': TestDigits();
                break;
                
            case '4': TestComparison();
                break;
                
            case '5': TestPlus();
                break;
                
            case '6': TestEfficiency();
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
int SpaceBarToContinue()
{
    char Ch;
    
    cout << "\n\n--------------------------------------------------"
    "  Spacebar continues test: ";
    
    cin.get(Ch);
    
    cin.ignore(10,'\n');
    
    return ( Ch == ' ' );
}

/***********************  DisplayOptions   *******************************
 
 Displays a menu of choices.
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void DisplayOptions()
{
    cout << " \nTesting Member Functions of MyFloat Class\n";
    
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    
    cout << "   1)  Test >> operator \n";
    
    cout << "   2)  Test =  operator \n";
    
    cout << "   3)  Test MaxDigits and Digits \n";
    
    cout << "   4)  Test == and > operators \n";
    
    cout << "   5)  Test + operator \n";
    
    cout << "   6)  Test + execution speed \n";
    
    cout << "   Q)  Quit program\n\n";
    
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
    cin.ignore(10,'\n');  //remove newline or any leftover characters
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
        cin >> X;
        cin.ignore(1000, '\n');         //  Discard all chars in input stream.
        
        if ( X.Digits() == 0 )       //  No significant digits
            cout << "\nInput error! ";
        
        cout << "\nAfter read,   X = '"<< X << "'\n";
        
    }
    while ( SpaceBarToContinue() );
}

/*********************  TestDigits   *************************************
 
 Allows testing of the member functions Digits and MaxDigits.
 
 This routine assumes that input and output functions for MyFloats
 have been written and debugged.
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestDigits()
{
    MyFloat X;
    
    cout <<"\n============ Testing Digits and MaxDigits  ==============\n\n";
    
    cout << "X.MaxDigits() = " << X.MaxDigits() << " \n\n";
    
    do
    {
        cout << "\nEnter MyFloat ==> ";
        cin >> X;
        cin.ignore(1000, '\n');         //  Discard all chars in input stream.
        cout << "\nDigits(" << X << ") = " << X.Digits() << endl;
    }
    while ( SpaceBarToContinue() );
}

/*********************  TestAssignment   *********************************
 
 Allows testing of the member functions "=" of MyFloat.
 
 This routine assumes that input and output functions for MyFloats
 have been written and debugged.
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestAssignment()
{
    MyFloat X;
    char    X_Str[100];
    
    cout << "\n------------  Testing \"=\" for MyFloat --------------------\n";
    do
    {
        cout << "\nEnter string holding float: ";
        
        cin.getline(X_Str, 100);
        
        X = X_Str;  // Call MyFloat = operator
        
        if ( X.Digits() == 0 )       //  Error in string format
            cout << "\nFormat error! ";
        
        cout << "\nAfter assignment,     'X = "<< X << "'" << endl;
    }
    while ( SpaceBarToContinue() );
}

/*********************  TestComparison   *********************************
 
 Allows testing of the member function operator==.
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestComparison()
{
    MyFloat X, Y;
    
    cout << "\n\n============  Testing \"==\" and \">\" for MyFloat  ================\n";
    
    do
    {
        cout << "\nEnter X  ==> ";
        cin >> X;
        cin.ignore(1000, '\n');         //  Discard all chars in input stream.
        cout << "\nEnter Y  ==> ";
        cin >> Y;
        cin.ignore(1000, '\n');         //  Discard all chars in input stream.
        
        cout << "\n\n";
        
        if ( X == Y )
        {
            cout << X; cout << " == " << Y;
        }
        else  if ( X > Y )
        {
            cout << X; cout << " > " << Y;
        }
        else if ( Y > X )
        {
            cout << Y; cout << " > " << X;
        }
    }
    while ( SpaceBarToContinue() );
}

/*********************  TestPlus   ***************************************
 
 Allows testing of the member function operator+.
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestPlus()
{
    MyFloat X, Y, Sum;
    
    cout << "\n\n++++++++++++  Testing \"+\"  for MyFloat  ++++++++++++++++\n"
    << "                  (Do not use leading zero)\n";
    do
    {
        cout << "\nEnter X  ==> ";
        cin >> X;
        cin.ignore(1000, '\n');         //  Discard all chars in input stream.
        
        cout << "\nEnter Y  ==> ";
        cin >> Y;
        
        cin.ignore(1000, '\n');         //  Discard all chars in input stream.
        cout << "\n\n";
        
        cout << "    X + Y = ";
        
        Sum = X + Y;
        
        cout << Sum << "\n\n";
        
    }
    while ( SpaceBarToContinue() );
}

/*************************   CPU_Seconds  ********************************
 
 Returns the number of CPU seconds that have elapsed since the last
 time this function was called. Uses the library function clock() in
 time.h, which returns CPU ticks used since calling program was
 started. On an IBM PC, a tick is 1/18.2 seconds, so the shortest
 event that can be timed is about 0.05 seconds. On other systems, a
 tick may be shorter, and the constant CLOCKS_PER_SECOND (defined in
 time.h) is used below. This helps the code below to be more portable.
 
 The example below shows how to use this function to time a section
 of code
 
 CPU_Seconds();                         // Initialize timer.
 <Section of code to be timed here>
 ExecutionTime = CPU_Seconds();
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#include <time.h>

float CPU_Seconds()
{
    float         NewReading,
    SecondsSinceLastCall;
    static float  OldReading = 0;
    
    NewReading =  clock()/(float)CLOCKS_PER_SEC;    // Check the clock
    SecondsSinceLastCall = NewReading - OldReading; // Find elapsed time
    OldReading = NewReading;                        // Save for next call
    
    return SecondsSinceLastCall;
}

/*********************  TestEfficiency  **********************************
 
 Computes and displays the amount of time required to add two floats and
 two MyFloats NUMBER_OF_ADDITIONS times. Since long int addition is much
 faster, fewer MyFloat sums are calculated, but the time is multiplied
 by SCALING_FACTOR, so a legitimate comparison is made.
 
 NUMBER_OF_ADDITIONS may needs to be adjusted, depending on the speed
 of the machine on which it is run.
 
 The resolution of the PC clock is only about 0.05 seconds.
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestEfficiency()
{
    
    const  int  SCALING_FACTOR = 10;            //  Used to save testing time
    
    const  long NUMBER_OF_ADDITIONS = 10000000, //  Change for slower machines
    
    FW =  6;
    
    MyFloat X1,
    X2;
    
    X1 = "0.1234567899";  //  Use the same numbers for MyFloat additions.
    X2 = "0.1111111111111111";
    
    float A = 0.12345678999,
    B = 0.1111111111111111;
    
    float ExecutionTime_Float,
    ExecutionTime_MyFloat;
    
    cout << setprecision(2)              //  2 digits of accuracy
    << setiosflags(ios::fixed)      //  Defeat scientific notation.
    << setiosflags(ios::showpoint); //  Always display decimal point
    
    do
    {
        cout << "\nPerforming " << NUMBER_OF_ADDITIONS << " float additions...  ";
        
        CPU_Seconds();                                   // Initialize clock
        long N;
        for (N = 1; N <= NUMBER_OF_ADDITIONS;  ++N )
            A + B;
        ExecutionTime_Float = CPU_Seconds();
        
        cout << "Time: " << setw(FW) << ExecutionTime_Float << endl;
        
        cout << "\nPerforming " << NUMBER_OF_ADDITIONS << " MyFloat additions...  ";
        
        CPU_Seconds();
        for ( N = 1; N <= NUMBER_OF_ADDITIONS/SCALING_FACTOR;  ++N )
            X1 + X2;
        
        ExecutionTime_MyFloat = SCALING_FACTOR * CPU_Seconds();
        
        cout << "Time: " << setw(FW) << ExecutionTime_MyFloat << endl << endl;
        
        cout << "Addition of floats is: " << ExecutionTime_MyFloat/ExecutionTime_Float
        << " times faster than addition of MyFloats.\n";
    }
    while ( SpaceBarToContinue()) ;
}
