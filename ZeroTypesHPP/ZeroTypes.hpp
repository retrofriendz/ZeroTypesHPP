/*

ZeroTypes Library
Open source license: BSD 
(http://github.com/h3rb/ZeroTypes)

Author: H. Elwood Gilliland III
Copyright (c) 2007-2017

*/

#pragma once
#if !defined(__cplusplus)
#error C++ Compiler Required
#else
#ifndef _ZEROTYPES_HPP_
#define _ZEROTYPES_HPP_ 1

#pragma warning (disable:4100)
#pragma warning (disable:4101)

// Call this on application startup.  Inits work strings and the seeder.
inline void InitZeroTypesLibrary();

inline void ZIndexed_Rigorous_Test();

// Removed due to problems: // #include <algorithm> // for std::min/max, string_infix ...
#include <string>
#include <stdbool.h>
#include <iostream>
//#include <algorithm>
#include <fstream>
#include <sstream>
#include <streambuf>

#if !defined(DEBUG) && defined(_DEBUG)
#define DEBUG _DEBUG
#endif

#if !defined(DONT_DECLARE_OUTPUT)
#ifdef DEBUG
#define OUTPUT(str,...) output__(str, ##__VA_ARGS__)
#else
#define OUTPUT(std,...) 
#endif
#endif

// having, true-or-false (diminished meaning of bool) parameter specifiers...
// Used to mark a parameter being presented a bool as a signal rather than a parameter-as-tested-value signal.  (See implementation...)
typedef bool trueorfalse;
typedef bool having; // symbol name idea came after reading about /using/ C++ keyword on http://stackoverflow.com/questions/10747810/what-is-the-difference-between-typedef-and-using-in-c11
                     // Sometimes the implementation uses the presence of a bool typed parameter to allow for a quick variant of a function/method of same name
                     // This is a slight brainly optimization that adds functionality where it was already present, and the typedef(s) above simplify programmer interface by
                     // embedding the nuance right in the code.  Most compilers would treat this as an alias, so bool and Zbool can still be provided when cast,
                     // but if you see /having/, passing it a bool variable isn't meaningful, you must test its value if it is to mean something.  The alternative
                     // would be to collude the code with cryptic numbers like "Concatenate2..." ... which is also done in some places, but is avoided where-ever possible.
                     // Prior to creating these typedefs, the implementation did not specify when true or false would lead to the feature being activated at the parameter level.


                     // Basic cross-platform soft error reporting function.
                     // Put a breakpoint on the calls to this to catch your issues with the debugger in debug mode.
inline void output__(const char *fmt, ...);

// Basic cross-platform string formatting printf style
inline std::string FMT(const char *fmt, ...);

// POD-type replacements
#define Zb Zbool
#define Zi Zint
#define Zf Zfloat
#define Zd Zdouble
#define Zui Zuint
#define Zus Zushort

// Divide by zero protection and report

#define DIV_BY_ZERO_PROTECTION 1

#if !defined(DIV_BY_ZERO_REPORTING) && ( defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_OUTPUT) )
//#define DIV_BY_ZERO_REPORTING 1
//  Use /D compiler option to set
#endif

// Unsigned subtraction "wrap" protection and report

#define UNSIGNED_SUBTRACTION_WRAP_PROTECTION 1

#if !defined(UNSIGNED_SUBTRACTION_WRAP_REPORTING) && ( defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_OUTPUT) )
#define UNSIGNED_SUBTRACTION_WRAP_REPORTING 1
#endif

// Unsigned addition "wrap" protection and report

#define UNSIGNED_ADDITION_WRAP_PROTECTION 1

#if !defined(UNSIGNED_ADDITION_WRAP_REPORTING) && ( defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_OUTPUT) )
#define UNSIGNED_ADDITION_WRAP_REPORTING 1
#endif

// Unsigned multiplication "wrap" protection and report

#define UNSIGNED_MULTIPLY_WRAP_PROTECTION 1

#if !defined(UNSIGNED_MULTIPLY_WRAP_REPORTING) && ( defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_OUTPUT) )
#define UNSIGNED_MULTIPLY_WRAP_REPORTING 1
#endif

/// Zbool /////////////////////////////////////////////////////////////////////////////////////////// start

class Zbool {
public:
 bool value;
 Zbool() { value=false; }
 Zbool( bool b ) { this->value=b; }
 operator bool *() { return &value; }
 Zbool *operator()() { return this; }
 Zbool& operator= ( const bool b ) { value=b; return *this; }
 Zbool& operator|= ( const bool b ) { value|=b; return *this; }
 Zbool& operator&= ( const bool b ) { value&=b; return *this; }
 const bool operator-() { return !value; }
 operator bool() { return value; }
};

/// Zbool /////////////////////////////////////////////////////////////////////////////////////////// end

/// Zwas //////////////////////////////////////////////////////////////////////////////////////////// start

class Zwas {
public:
 bool value,was;
 Zwas() { value=was=false; }
 Zwas( bool b ) { this->value=b; was=false; }
 operator bool *() { return &value; }
 Zwas *operator()() { return this; }
 Zwas& operator= ( const bool b ) { was=value; value=b; return *this; }
 Zwas& operator|= ( const bool b ) { value|=b; return *this; }
 Zwas& operator&= ( const bool b ) { value&=b; return *this; }
 void Store() {
  was=value;
 }
 const bool operator-() { return !value; }
 operator bool() { return value; }
};

/// Zwas //////////////////////////////////////////////////////////////////////////////////////////// end

// Forward declarations
class Zbyte;
class Zushort;
class Zuint;
class Zint;
class Zdouble;

/// Zfloat ////////////////////////////////////////////////////////////////////////////////////////// start

class Zfloat {
public:
 float value;
 Zfloat() { value=0.0f; }
 Zfloat( float value ) { this->value=value; }
 std::string toString() { return std::to_string(value);} 
 float abs() { return std::abs(value); }
 operator std::string() { return toString(); }
 operator float() { return value; }
 operator float *() { return &value; }
 Zfloat *operator()() { return this; }
 float operator()( int i ) { return value=(float)i; }
 float operator()( float f ) { return value=f; }
 float operator()( double d ) { return value=(float)d; }
 float operator()( Zbyte &b );
 float operator()( Zuint &i );
 float operator()( Zint &i );
 float operator()( Zfloat &f );
 float operator()( Zdouble &d );
 Zfloat& operator= ( const unsigned char b ) { value=(float) b; return *this; }
 Zfloat& operator= ( const unsigned int i ) { value=(float) i; return *this; }
 Zfloat& operator= ( const int i ) { value=(float) i; return *this; }
 Zfloat& operator= ( const float f ) { value=f; return *this; }
 Zfloat& operator= ( const double d ) { value=(float) d; return *this; }
 Zfloat& operator= ( const Zbyte& b );
 Zfloat& operator= ( const Zuint& i );
 Zfloat& operator= ( const Zint& i );
 Zfloat& operator= ( const Zfloat& f ) { value=f.value; return *this; }
 Zfloat& operator= ( const Zdouble& d );
 Zfloat& operator= ( const std::string& s );
 Zfloat& operator+= ( const Zfloat& f ) { value+=f.value; return *this; }
 Zfloat& operator-= ( const Zfloat& f ) { value-=f.value; return *this; }
 Zfloat& operator*= ( const Zfloat& f ) { value*=f.value; return *this; }
 Zfloat& operator/= ( const Zfloat& f ) { value/=f.value; return *this; }
 Zfloat& operator+= ( const Zint& i );
 Zfloat& operator-= ( const Zint& i );
 Zfloat& operator*= ( const Zint& i );
 Zfloat& operator/= ( const Zint& i );
 Zfloat& operator+= ( const unsigned char f ) { value+=(float)f; return *this; }
 Zfloat& operator-= ( const unsigned char f ) { value-=(float)f; return *this; }
 Zfloat& operator*= ( const unsigned char f ) { value*=(float)f; return *this; }
 Zfloat& operator/= ( const unsigned char f ) { value/=(float)f; return *this; }
 Zfloat& operator+= ( const unsigned short f ) { value+=(float)f; return *this; }
 Zfloat& operator-= ( const unsigned short f ) { value-=(float)f; return *this; }
 Zfloat& operator*= ( const unsigned short f ) { value*=(float)f; return *this; }
 Zfloat& operator/= ( const unsigned short f ) { value/=(float)f; return *this; }
 Zfloat& operator+= ( const int f ) { value+=(float)f; return *this; }
 Zfloat& operator-= ( const int f ) { value-=(float)f; return *this; }
 Zfloat& operator*= ( const int f ) { value*=(float)f; return *this; }
 Zfloat& operator/= ( const int f ) { value/=(float)f; return *this; }
 Zfloat& operator+= ( const unsigned int f ) { value+=(float)f; return *this; }
 Zfloat& operator-= ( const unsigned int f ) { value-=(float)f; return *this; }
 Zfloat& operator*= ( const unsigned int f ) { value*=(float)f; return *this; }
 Zfloat& operator/= ( const unsigned int f ) { value/=(float)f; return *this; }
 Zfloat& operator+= ( const float f ) { value+=f; return *this; }
 Zfloat& operator-= ( const float f ) { value-=f; return *this; }
 Zfloat& operator*= ( const float f ) { value*=f; return *this; }
 Zfloat& operator/= ( const float f ) { value/=f; return *this; }
 Zfloat& operator+= ( const double f ) { value+=(float)f; return *this; }
 Zfloat& operator-= ( const double f ) { value-=(float)f; return *this; }
 Zfloat& operator*= ( const double f ) { value*=(float)f; return *this; }
 Zfloat& operator/= ( const double f ) { value/=(float)f; return *this; }
 Zfloat& operator++ (int) { value+=1.0f; return *this; }
 Zfloat& operator-- (int) { value-=1.0f; return *this; }
 const float operator-() { return -value; }
 bool operator !() { return ( value == 0.0f ); }
 // Not used intentionally to create warning:
 // operator double() { return (double) value; }
 // operator int() { return (int) value; }
 // Causes ambiguity, because this is removed, the resulting issue (no better solution, see C2593)
 // (mixed type comparisons require explicit casts) is described in the test:
 // operator double() { return (double) value; }
 // operator int() { return (int) value; }
};

// Mixed type interactions
inline float operator+ ( const Zfloat& a, const Zint& b );
inline float operator+ ( const Zint& a, const Zfloat& b );
inline float operator* ( const Zfloat& a, const Zint& b );
inline float operator* ( const Zint& a, const Zfloat& b );
// Float and itself
inline float operator+ ( const Zfloat& a, const Zfloat& b );
inline float operator- ( const Zfloat& a, const Zfloat& b );
inline float operator* ( const Zfloat& a, const Zfloat& b );
inline float operator/ ( const Zfloat& a, const Zfloat& b );
/* Creates C2593 for some reason...
float operator+ ( Zfloat a, Zfloat b );
float operator- ( Zfloat a, Zfloat b );
float operator* ( Zfloat a, Zfloat b );
float operator/ ( Zfloat a, Zfloat b );
*/
// Casted int operations
inline float operator+ ( const Zfloat& a, int b );
inline float operator- ( const Zfloat& a, int b );
inline float operator* ( const Zfloat& a, int b );
inline float operator/ ( const Zfloat& a, int b );
inline float operator+ ( int b, const Zfloat& a );
inline float operator- ( int b, const Zfloat& a );
inline float operator* ( int b, const Zfloat& a );
inline float operator/ ( int b, const Zfloat& a );
// Float operations
inline float operator+ ( const Zfloat& a, float b );
inline float operator- ( const Zfloat& a, float b );
inline float operator* ( const Zfloat& a, float b );
inline float operator/ ( const Zfloat& a, float b );
inline float operator+ ( float b, const Zfloat& a );
inline float operator- ( float b, const Zfloat& a );
inline float operator* ( float b, const Zfloat& a );
inline float operator/ ( float b, const Zfloat& a );
// Casted double operations (leans toward double precision)
inline float operator+ ( const Zfloat& a, double b );
inline float operator- ( const Zfloat& a, double b );
inline float operator* ( const Zfloat& a, double b );
inline float operator/ ( const Zfloat& a, double b );
inline float operator+ ( double b, const Zfloat& a );
inline float operator- ( double b, const Zfloat& a );
inline float operator* ( double b, const Zfloat& a );
inline float operator/ ( double b, const Zfloat& a );
// Boolean operations
inline bool operator>= ( const Zfloat& a, const Zfloat& b );
inline bool operator>= ( const Zfloat& a, const Zbyte& b );
inline bool operator>= ( const Zfloat& a, const Zushort& b );
inline bool operator>= ( const Zfloat& a, const Zuint& b );
inline bool operator>= ( const Zfloat& a, const Zint& b );
inline bool operator>= ( const Zfloat& a, const Zdouble& b );
inline bool operator>= ( const Zbyte& a, const Zfloat& b );
inline bool operator>= ( const Zushort& a, const Zfloat& b );
inline bool operator>= ( const Zuint& a, const Zfloat& b );
inline bool operator>= ( const Zint& a, const Zfloat& b );
inline bool operator>= ( const Zdouble& a, const Zfloat& b );
inline bool operator>= ( const Zfloat& a, int b );
inline bool operator>= ( const Zfloat& a, float b );
inline bool operator>= ( const Zfloat& a, double b );
inline bool operator>= ( int a, const Zfloat& b );
inline bool operator>= ( float a, const Zfloat& b );
inline bool operator>= ( double a, const Zfloat& b );
inline bool operator== ( const Zfloat& a, const Zfloat& b );
inline bool operator== ( const Zfloat& a, const Zbyte& b );
inline bool operator== ( const Zfloat& a, const Zushort& b );
inline bool operator== ( const Zfloat& a, const Zuint& b );
inline bool operator== ( const Zfloat& a, const Zint& b );
inline bool operator== ( const Zfloat& a, const Zdouble& b );
inline bool operator== ( const Zbyte& a, const Zfloat& b );
inline bool operator== ( const Zushort& a, const Zfloat& b );
inline bool operator== ( const Zuint& a, const Zfloat& b );
inline bool operator== ( const Zint& a, const Zfloat& b );
inline bool operator== ( const Zdouble& a, const Zfloat& b );
inline bool operator== ( const Zfloat& a, int b );
inline bool operator== ( const Zfloat& a, float b );
inline bool operator== ( const Zfloat& a, double b );
inline bool operator== ( int a, const Zfloat& b );
inline bool operator== ( float a, const Zfloat& b );
inline bool operator== ( double a, const Zfloat& b );
inline bool operator!= ( const Zfloat& a, const Zfloat& b );
inline bool operator!= ( const Zfloat& a, const Zbyte& b );
inline bool operator!= ( const Zfloat& a, const Zushort& b );
inline bool operator!= ( const Zfloat& a, const Zuint& b );
inline bool operator!= ( const Zfloat& a, const Zint& b );
inline bool operator!= ( const Zfloat& a, const Zdouble& b );
inline bool operator!= ( const Zbyte& a, const Zfloat& b );
inline bool operator!= ( const Zushort& a, const Zfloat& b );
inline bool operator!= ( const Zuint& a, const unsigned int b );
inline bool operator!= ( const Zuint& a, const int b );
inline bool operator!= ( const Zuint& a, const Zfloat& b );
inline bool operator!= ( const Zint& a, const Zfloat& b );
inline bool operator!= ( const Zdouble& a, const Zfloat& b );
inline bool operator!= ( const Zfloat& a, int b );
inline bool operator!= ( const Zfloat& a, float b );
inline bool operator!= ( const Zfloat& a, double b );
inline bool operator!= ( int a, const Zfloat& b );
inline bool operator!= ( float a, const Zfloat& b );
inline bool operator!= ( double a, const Zfloat& b );
inline bool operator<= ( const Zfloat& a, const Zfloat& b );
inline bool operator<= ( const Zfloat& a, const Zbyte& b );
inline bool operator<= ( const Zfloat& a, const Zushort& b );
inline bool operator<= ( const Zfloat& a, const Zuint& b );
inline bool operator<= ( const Zfloat& a, const Zint& b );
inline bool operator<= ( const Zfloat& a, const Zdouble& b );
inline bool operator<= ( const Zbyte& a, const Zfloat& b );
inline bool operator<= ( const Zushort& a, const Zfloat& b );
inline bool operator<= ( const Zuint& a, const Zfloat& b );
inline bool operator<= ( const Zint& a, const Zfloat& b );
inline bool operator<= ( const Zdouble& a, const Zfloat& b );
inline bool operator<= ( const Zfloat& a, int b );
inline bool operator<= ( const Zfloat& a, float b );
inline bool operator<= ( const Zfloat& a, double b );
inline bool operator<= ( int a, const Zfloat& b );
inline bool operator<= ( float a, const Zfloat& b );
inline bool operator<= ( double a, const Zfloat& b );
inline bool operator> ( const Zfloat& a, const Zfloat& b );
inline bool operator> ( const Zfloat& a, const Zbyte& b );
inline bool operator> ( const Zfloat& a, const Zushort& b );
inline bool operator> ( const Zfloat& a, const Zuint& b );
inline bool operator> ( const Zfloat& a, const Zint& b );
inline bool operator> ( const Zfloat& a, const Zdouble& b );
inline bool operator> ( const Zbyte& a, const Zfloat& b );
inline bool operator> ( const Zushort& a, const Zfloat& b );
inline bool operator> ( const Zuint& a, const Zfloat& b );
inline bool operator> ( const Zint& a, const Zfloat& b );
inline bool operator> ( const Zdouble& a, const Zfloat& b );
inline bool operator> ( const Zfloat& a, int b );
inline bool operator> ( const Zfloat& a, float b );
inline bool operator> ( const Zfloat& a, double b );
inline bool operator> ( int a, const Zfloat& b );
inline bool operator> ( float a, const Zfloat& b );
inline bool operator> ( double a, const Zfloat& b );
inline bool operator< ( const Zfloat& a, const Zfloat& b );
inline bool operator< ( const Zfloat& a, const Zbyte& b );
inline bool operator< ( const Zfloat& a, const Zushort& b );
inline bool operator< ( const Zfloat& a, const Zuint& b );
inline bool operator< ( const Zfloat& a, const Zint& b );
inline bool operator< ( const Zfloat& a, const Zdouble& b );
inline bool operator< ( const Zbyte& a, const Zfloat& b );
inline bool operator< ( const Zushort& a, const Zfloat& b );
inline bool operator< ( const Zuint& a, const Zfloat& b );
inline bool operator< ( const Zint& a, const Zfloat& b );
inline bool operator< ( const Zdouble& a, const Zfloat& b );
inline bool operator< ( const Zfloat& a, int b );
inline bool operator< ( const Zfloat& a, float b );
inline bool operator< ( const Zfloat& a, double b );
inline bool operator< ( int a, const Zfloat& b );
inline bool operator< ( float a, const Zfloat& b );
inline bool operator< ( double a, const Zfloat& b );

/// Zfloat ////////////////////////////////////////////////////////////////////////////////////////// end

/// Zbyte ////////////////////////////////////////////////////////////////////////////////////////// start

class Zbyte {
public:
 unsigned char value;
 Zbyte() { value=0; }
 Zbyte( unsigned char value ) { this->value=value; }
 operator unsigned char *() { return &value; }
 Zbyte *operator()() { return this; }
 bool Get(const unsigned char bit)          { return ((value) & (1<<(bit))) ? true : false; }
 void Set(const unsigned char bit, const bool on) { if (on) value |= (bit); else value &= ~(bit); }
 unsigned char operator()( unsigned char b ) { return value=b; }
 unsigned char operator()( unsigned int i ) { return value=(unsigned char)i; }
 unsigned char operator()( int i ) { return value=(unsigned char) i; }
 unsigned char operator()( float f ) { return value=(unsigned char) f; }
 unsigned char operator()( double d ) { return value=(unsigned char) d; }
 unsigned char operator()( Zuint &i );
 unsigned char operator()( Zint &i );
 unsigned char operator()( Zfloat &f );
 unsigned char operator()( Zdouble &d );
 Zbyte& operator= ( const unsigned char b ) { value=b; return *this; }
 Zbyte& operator= ( const int i ) { value=(unsigned char)i; return *this; }
 Zbyte& operator= ( const float f ) { value=(unsigned char)f; return *this; }
 Zbyte& operator= ( const double d ) { value=(unsigned char) d; return *this; }
 Zbyte& operator= ( const Zbyte& i ) { value=i.value; return *this; }
 Zbyte& operator= ( const Zuint& i );
 Zbyte& operator= ( const Zint& i );
 Zbyte& operator= ( const Zfloat& f );
 Zbyte& operator= ( const Zdouble& d );
 Zbyte& operator= ( const std::string& s );
 Zbyte& operator+= ( const Zbyte& i ) { value+=i.value; return *this; }
 Zbyte& operator-= ( const Zbyte& i ) { value-=i.value; return *this; }
 Zbyte& operator*= ( const Zbyte& i ) { value*=i.value; return *this; }
 Zbyte& operator/= ( const Zbyte& i ) { value/=i.value; return *this; }
 Zbyte& operator+= ( const unsigned char i ) { value+=i; return *this; }
 Zbyte& operator-= ( const unsigned char i ) { value-=i; return *this; }
 Zbyte& operator*= ( const unsigned char i ) { value*=i; return *this; }
 Zbyte& operator/= ( const unsigned char i ) { value/=i; return *this; }
 Zbyte& operator+= ( const unsigned short i ) { value+=(unsigned char)i; return *this; }
 Zbyte& operator-= ( const unsigned short i ) { value-=(unsigned char)i; return *this; }
 Zbyte& operator*= ( const unsigned short i ) { value*=(unsigned char)i; return *this; }
 Zbyte& operator/= ( const unsigned short i ) { value/=(unsigned char)i; return *this; }
 Zbyte& operator+= ( const int i ) { value+=(unsigned char)i; return *this; }
 Zbyte& operator-= ( const int i ) { value-=(unsigned char)i; return *this; }
 Zbyte& operator*= ( const int i ) { value*=(unsigned char)i; return *this; }
 Zbyte& operator/= ( const int i ) { value/=(unsigned char)i; return *this; }
 Zbyte& operator+= ( const unsigned int i ) { value+=(unsigned char)i; return *this; }
 Zbyte& operator-= ( const unsigned int i ) { value-=(unsigned char)i; return *this; }
 Zbyte& operator*= ( const unsigned int i ) { value*=(unsigned char)i; return *this; }
 Zbyte& operator/= ( const unsigned int i ) { value/=(unsigned char)i; return *this; }
 Zbyte& operator+= ( const float i ) { value+=(unsigned char)i; return *this; }
 Zbyte& operator-= ( const float i ) { value-=(unsigned char)i; return *this; }
 Zbyte& operator*= ( const float i ) { value*=(unsigned char)i; return *this; }
 Zbyte& operator/= ( const float i ) { value/=(unsigned char)i; return *this; }
 Zbyte& operator+= ( const double i ) { value+=(unsigned char)i; return *this; }
 Zbyte& operator-= ( const double i ) { value-=(unsigned char)i; return *this; }
 Zbyte& operator*= ( const double i ) { value*=(unsigned char)i; return *this; }
 Zbyte& operator/= ( const double i ) { value/=(unsigned char)i; return *this; }
 Zbyte& operator++ (int) { value+=1; return *this; }
 Zbyte& operator-- (int) { value-=1; return *this; }
 operator unsigned char() { return value; }
 bool operator !() { return ( value == 0 ); }
 // Not used intentionally to create warning:
 // operator float() { return (float)value; }
 // operator double() { return (double)value; }
 // Causes ambiguity, because this is removed, the resulting issue (no better solution, see C2593)
 // (mixed type comparisons require explicit casts) is described in the test:
 // operator float() { return (float) value; }
 // operator float() { return (double) value; }
};


inline unsigned char operator+ ( const Zbyte& a, const Zbyte& b );
inline unsigned char operator- ( const Zbyte& a, const Zbyte& b );
inline unsigned char operator* ( const Zbyte& a, const Zbyte& b );
inline unsigned char operator/ ( const Zbyte& a, const Zbyte& b );
inline unsigned char operator+ ( Zbyte a, Zbyte b );
inline unsigned char operator- ( Zbyte a, Zbyte b );
inline unsigned char operator* ( Zbyte a, Zbyte b );
inline unsigned char operator/ ( Zbyte a, Zbyte b );
// Casted unsigned int operations
inline unsigned char operator+ ( const Zbyte& a, unsigned char b );
inline unsigned char operator- ( const Zbyte& a, unsigned char b );
inline unsigned char operator* ( const Zbyte& a, unsigned char b );
inline unsigned char operator/ ( const Zbyte& a, unsigned char b );
inline unsigned char operator+ ( unsigned char b, const Zbyte& a );
inline unsigned char operator- ( unsigned char b, const Zbyte& a );
inline unsigned char operator* ( unsigned char b, const Zbyte& a );
inline unsigned char operator/ ( unsigned char b, const Zbyte& a );
// Casted int operations
inline unsigned char operator+ ( const Zbyte& a, int b );
inline unsigned char operator- ( const Zbyte& a, int b );
inline unsigned char operator* ( const Zbyte& a, int b );
inline unsigned char operator/ ( const Zbyte& a, int b );
inline unsigned char operator+ ( int b, const Zbyte& a );
inline unsigned char operator- ( int b, const Zbyte& a );
inline unsigned char operator* ( int b, const Zbyte& a );
inline unsigned char operator/ ( int b, const Zbyte& a );
// Float operations (leans toward float precision)
inline unsigned char operator+ ( const Zbyte& a, float b );
inline unsigned char operator- ( const Zbyte& a, float b );
inline unsigned char operator* ( const Zbyte& a, float b );
inline unsigned char operator/ ( const Zbyte& a, float b );
inline unsigned char operator+ ( float b, const Zbyte& a );
inline unsigned char operator- ( float b, const Zbyte& a );
inline unsigned char operator* ( float b, const Zbyte& a );
inline unsigned char operator/ ( float b, const Zbyte& a );
// Casted double operations (leans toward double precision)
inline unsigned char operator+ ( const Zbyte& a, double b );
inline unsigned char operator- ( const Zbyte& a, double b );
inline unsigned char operator* ( const Zbyte& a, double b );
inline unsigned char operator/ ( const Zbyte& a, double b );
inline unsigned char operator+ ( double b, const Zbyte& a );
inline unsigned char operator- ( double b, const Zbyte& a );
inline unsigned char operator* ( double b, const Zbyte& a );
inline unsigned char operator/ ( double b, const Zbyte& a );
// Boolean operations
inline bool operator>= ( const Zbyte& a, const Zbyte& b );
inline bool operator>= ( const Zbyte& a, int b );
inline bool operator>= ( const Zbyte& a, float b );
inline bool operator>= ( const Zbyte& a, double b );
inline bool operator>= ( int a, const Zbyte& b );
inline bool operator>= ( float a, const Zbyte& b );
inline bool operator>= ( double a, const Zbyte& b );
inline bool operator== ( const Zbyte& a, const Zbyte& b );
inline bool operator== ( const Zbyte& a, int b );
inline bool operator== ( const Zbyte& a, float b );
inline bool operator== ( const Zbyte& a, double b );
inline bool operator== ( int a, const Zbyte& b );
inline bool operator== ( float a, const Zbyte& b );
inline bool operator== ( double a, const Zbyte& b );
inline bool operator!= ( const Zbyte& a, const Zbyte& b );
inline bool operator!= ( const Zbyte& a, int b );
inline bool operator!= ( const Zbyte& a, float b );
inline bool operator!= ( const Zbyte& a, double b );
inline bool operator!= ( int a, const Zbyte& b );
inline bool operator!= ( float a, const Zbyte& b );
inline bool operator!= ( double a, const Zbyte& b );
inline bool operator<= ( const Zbyte& a, const Zbyte& b );
inline bool operator<= ( const Zbyte& a, int b );
inline bool operator<= ( const Zbyte& a, float b );
inline bool operator<= ( const Zbyte& a, double b );
inline bool operator<= ( int a, const Zbyte& b );
inline bool operator<= ( float a, const Zbyte& b );
inline bool operator<= ( double a, const Zbyte& b );
inline bool operator> ( const Zbyte& a, const Zbyte& b );
inline bool operator> ( const Zbyte& a, int b );
inline bool operator> ( const Zbyte& a, float b );
inline bool operator> ( const Zbyte& a, double b );
inline bool operator> ( int a, const Zbyte& b );
inline bool operator> ( float a, const Zbyte& b );
inline bool operator> ( double a, const Zbyte& b );
inline bool operator< ( const Zbyte& a, const Zbyte& b );
inline bool operator< ( const Zbyte& a, int b );
inline bool operator< ( const Zbyte& a, float b );
inline bool operator< ( const Zbyte& a, double b );
inline bool operator< ( int a, const Zbyte& b );
inline bool operator< ( float a, const Zbyte& b );
inline bool operator< ( double a, const Zbyte& b );


/// Zbyte ///////////////////////////////////////////////////////////////////////////////////////// end

/// Zushort ////////////////////////////////////////////////////////////////////////////////////////// start

class Zushort {
public:
 unsigned short value;
 Zushort() { value=0; }
 Zushort( unsigned short value ) { this->value=value; }
 operator unsigned short *() { return &value; }
 Zushort *operator()() { return this; }
 unsigned short operator()( unsigned short z ) { return value=(unsigned short)z; }
 unsigned short operator()( unsigned char b ) { return value=(unsigned short)b; }
 unsigned short operator()( unsigned int i ) { return value=(unsigned short)i; }
 unsigned short operator()( int i ) { return value=(unsigned short) i; }
 unsigned short operator()( float f ) { return value=(unsigned short) f; }
 unsigned short operator()( double d ) { return value=(unsigned short) d; }
 unsigned short operator()( Zuint &i );
 unsigned short operator()( Zint &i );
 unsigned short operator()( Zfloat &f );
 unsigned short operator()( Zdouble &d );
 Zushort& operator= ( const unsigned short z ) { value=z; return *this; }
 Zushort& operator= ( const unsigned char b ) { value=(unsigned short)b; return *this; }
 Zushort& operator= ( const int i ) { value=(unsigned short)i; return *this; }
 Zushort& operator= ( const float f ) { value=(unsigned short)f; return *this; }
 Zushort& operator= ( const double d ) { value=(unsigned short) d; return *this; }
 Zushort& operator= ( const Zushort& i ) { value=i.value; return *this; }
 Zushort& operator= ( const Zbyte& i ) { value=(unsigned short)i.value; return *this; }
 Zushort& operator= ( const Zuint& i );
 Zushort& operator= ( const Zint& i );
 Zushort& operator= ( const Zfloat& f );
 Zushort& operator= ( const Zdouble& d );
 Zushort& operator= ( const std::string& s );
 Zushort& operator+= ( const unsigned char i ) { value+=(unsigned short)i; return *this; }
 Zushort& operator-= ( const unsigned char i ) { value-=(unsigned short)i; return *this; }
 Zushort& operator*= ( const unsigned char i ) { value*=(unsigned short)i; return *this; }
 Zushort& operator/= ( const unsigned char i ) { value/=(unsigned short)i; return *this; }
 Zushort& operator+= ( const unsigned short i ) { value+=(unsigned short)i; return *this; }
 Zushort& operator-= ( const unsigned short i ) { value-=(unsigned short)i; return *this; }
 Zushort& operator*= ( const unsigned short i ) { value*=(unsigned short)i; return *this; }
 Zushort& operator/= ( const unsigned short i ) { value/=(unsigned short)i; return *this; }
 Zushort& operator+= ( const int i ) { value+=(unsigned short)i; return *this; }
 Zushort& operator-= ( const int i ) { value-=(unsigned short)i; return *this; }
 Zushort& operator*= ( const int i ) { value*=(unsigned short)i; return *this; }
 Zushort& operator/= ( const int i ) { value/=(unsigned short)i; return *this; }
 Zushort& operator+= ( const unsigned int i ) { value+=(unsigned short)i; return *this; }
 Zushort& operator-= ( const unsigned int i ) { value-=(unsigned short)i; return *this; }
 Zushort& operator*= ( const unsigned int i ) { value*=(unsigned short)i; return *this; }
 Zushort& operator/= ( const unsigned int i ) { value/=(unsigned short)i; return *this; }
 Zushort& operator+= ( const float i ) { value+=(unsigned short)i; return *this; }
 Zushort& operator-= ( const float i ) { value-=(unsigned short)i; return *this; }
 Zushort& operator*= ( const float i ) { value*=(unsigned short)i; return *this; }
 Zushort& operator/= ( const float i ) { value/=(unsigned short)i; return *this; }
 Zushort& operator+= ( const double i ) { value+=(unsigned short)i; return *this; }
 Zushort& operator-= ( const double i ) { value-=(unsigned short)i; return *this; }
 Zushort& operator*= ( const double i ) { value*=(unsigned short)i; return *this; }
 Zushort& operator/= ( const double i ) { value/=(unsigned short)i; return *this; }
 Zushort& operator++ (int) { value+=1; return *this; }
 Zushort& operator-- (int) { value-=1; return *this; }
 operator unsigned short() { return value; }
 operator int() { return -(int)value; }
 bool operator !() { return ( value == 0 ); }
 // Not used intentionally to create warning:
 // operator float() { return (float)value; }
 // operator double() { return (double)value; }
 // Causes ambiguity, because this is removed, the resulting issue (no better solution, see C2593)
 // (mixed type comparisons require explicit casts) is described in the test:
 // operator float() { return (float) value; }
 // operator float() { return (double) value; }
};


inline unsigned short operator+ ( const Zushort& a, const Zushort& b );
inline unsigned short operator- ( const Zushort& a, const Zushort& b );
inline unsigned short operator* ( const Zushort& a, const Zushort& b );
inline unsigned short operator/ ( const Zushort& a, const Zushort& b );
inline unsigned short operator+ ( Zushort a, Zushort b );
inline unsigned short operator- ( Zushort a, Zushort b );
inline unsigned short operator* ( Zushort a, Zushort b );
inline unsigned short operator/ ( Zushort a, Zushort b );
// Casted unsigned int operations
inline unsigned short operator+ ( const Zushort& a, unsigned char b );
inline unsigned short operator- ( const Zushort& a, unsigned char b );
inline unsigned short operator* ( const Zushort& a, unsigned char b );
inline unsigned short operator/ ( const Zushort& a, unsigned char b );
inline unsigned short operator+ ( unsigned char b, const Zushort& a );
inline unsigned short operator- ( unsigned char b, const Zushort& a );
inline unsigned short operator* ( unsigned char b, const Zushort& a );
inline unsigned short operator/ ( unsigned char b, const Zushort& a );
// Casted int operations
inline unsigned short operator+ ( const Zushort& a, int b );
inline unsigned short operator- ( const Zushort& a, int b );
inline unsigned short operator* ( const Zushort& a, int b );
inline unsigned short operator/ ( const Zushort& a, int b );
inline unsigned short operator+ ( int b, const Zushort& a );
inline unsigned short operator- ( int b, const Zushort& a );
inline unsigned short operator* ( int b, const Zushort& a );
inline unsigned short operator/ ( int b, const Zushort& a );
// Float operations (leans toward float precision)
inline unsigned short operator+ ( const Zushort& a, float b );
inline unsigned short operator- ( const Zushort& a, float b );
inline unsigned short operator* ( const Zushort& a, float b );
inline unsigned short operator/ ( const Zushort& a, float b );
inline unsigned short operator+ ( float b, const Zushort& a );
inline unsigned short operator- ( float b, const Zushort& a );
inline unsigned short operator* ( float b, const Zushort& a );
inline unsigned short operator/ ( float b, const Zushort& a );
// Casted double operations (leans toward double precision)
inline unsigned short operator+ ( const Zushort& a, double b );
inline unsigned short operator- ( const Zushort& a, double b );
inline unsigned short operator* ( const Zushort& a, double b );
inline unsigned short operator/ ( const Zushort& a, double b );
inline unsigned short operator+ ( double b, const Zushort& a );
inline unsigned short operator- ( double b, const Zushort& a );
inline unsigned short operator* ( double b, const Zushort& a );
inline unsigned short operator/ ( double b, const Zushort& a );

/// Zbyte ///////////////////////////////////////////////////////////////////////////////////////// end

/// Zint ////////////////////////////////////////////////////////////////////////////////////////// start

class Zint {
public:
 int value;
 Zint() { value=0; }
 Zint( int value ) { this->value=value; }
 inline int abs() { return value < 0 ? -value : value; } // Macos does not define abs(int)
 inline bool On(int bits) { return this->value & bits; }
 inline bool Off(int bits) { return !On(bits); }
 inline void Set(int bits) { this->value |= bits; }
 inline void Unset(int bits) { this->value &= ~bits; }
 inline void Toggle(int bits) { this->value ^= bits; }
 inline int Left(int bits) { return value << bits; }
 inline int Right(int bits) { return value >> bits; }
 /// This seems to be problematic.  Removing.
// int Min(int other) { return std::min(value, other); }
// int Max(int other) { return std::max(value, other); }
 bool Exceeds(int other) { return value > other; }
 bool ExceededBy(int other) { return other > value; }
 bool Greater(int other) { return Exceeds(other); }
 bool Lesser(int other) { return ExceededBy(other); }
 bool Equals(int other) { return value == other; }
 bool NotEquals(int other) { return other != value; }
 bool GreaterEquals(int other) { return value >= other; }
 bool LesserEquals(int other) { return value <= other; }
 inline int Minus(int other) { return value - other; }
 inline int Plus(int other) { return value + other; }
 std::string toString() { return std::to_string(value); }
 operator std::string() { return toString(); }
 operator int() { return value; }
 operator int *() { return &value; }
 Zint *operator()() { return this; }
 int operator()( int i ) { return value=i; }
 int operator()( float f ) { return value=(int)f; }
 int operator()( double d ) { return value=(int)d; }
 int operator()( Zbyte &i );
 int operator()( Zuint &i );
 int operator()( Zint &i ) { return value=i.value; }
 int operator()( Zfloat &f );
 int operator()( Zdouble &d );
 Zint& operator= ( const int i ) { value=i; return *this; }
 Zint& operator= ( const float f ) { value=(int)f; return *this; }
 Zint& operator= ( const double d ) { value=(int) d; return *this; }
 Zint& operator= ( const Zint& i ) { value=i.value; return *this; }
 Zint& operator= ( const Zbyte& b );
 Zint& operator= ( const Zuint& i );
 Zint& operator= ( const Zfloat& f );
 Zint& operator= ( const Zdouble& d );
 Zint& operator= ( const std::string& s );
 Zint& operator+= ( const Zint& i ) { value+=i.value; return *this; }
 Zint& operator-= ( const Zint& i ) { value-=i.value; return *this; }
 Zint& operator*= ( const Zint& i ) { value*=i.value; return *this; }
 Zint& operator/= ( const Zint& i ) { value/=i.value; return *this; }
 Zint& operator+= ( const Zfloat& f );
 Zint& operator-= ( const Zfloat& f );
 Zint& operator*= ( const Zfloat& f );
 Zint& operator/= ( const Zfloat& f );
 Zint& operator+= ( const unsigned char i ) { value+=(int)i; return *this; }
 Zint& operator-= ( const unsigned char i ) { value-=(int)i; return *this; }
 Zint& operator*= ( const unsigned char i ) { value*=(int)i; return *this; }
 Zint& operator/= ( const unsigned char i ) { value/=(int)i; return *this; }
 Zint& operator+= ( const unsigned short i ) { value+=(int)i; return *this; }
 Zint& operator-= ( const unsigned short i ) { value-=(int)i; return *this; }
 Zint& operator*= ( const unsigned short i ) { value*=(int)i; return *this; }
 Zint& operator/= ( const unsigned short i ) { value/=(int)i; return *this; }
 Zint& operator+= ( const int i ) { value+=i; return *this; }
 Zint& operator-= ( const int i ) { value-=i; return *this; }
 Zint& operator*= ( const int i ) { value*=i; return *this; }
 Zint& operator/= ( const int i ) { value/=i; return *this; }
 Zint& operator+= ( const unsigned int i ) { value+=(int)i; return *this; }
 Zint& operator-= ( const unsigned int i ) { value-=(int)i; return *this; }
 Zint& operator*= ( const unsigned int i ) { value*=(int)i; return *this; }
 Zint& operator/= ( const unsigned int i ) { value/=(int)i; return *this; }
 Zint& operator+= ( const float i ) { value+=(int)i; return *this; }
 Zint& operator-= ( const float i ) { value-=(int)i; return *this; }
 Zint& operator*= ( const float i ) { value*=(int)i; return *this; }
 Zint& operator/= ( const float i ) { value/=(int)i; return *this; }
 Zint& operator+= ( const double i ) { value+=(int)i; return *this; }
 Zint& operator-= ( const double i ) { value-=(int)i; return *this; }
 Zint& operator*= ( const double i ) { value*=(int)i; return *this; }
 Zint& operator/= ( const double i ) { value/=(int)i; return *this; }
 Zint& operator++ (int) { value+=1; return *this; }
 Zint& operator-- (int) { value-=1; return *this; }
 const int operator-() { return -value; }
 // operator size_t() { return (size_t)value; }
 operator unsigned int() { return (unsigned int) value; }
 operator float() { return (float) value; }
 operator double() { return (double) value; }
 bool operator !() { return ( value == 0 ); }
 // Not used intentionally to create warning:
 // operator float() { return (float)value; }
 // operator double() { return (double)value; }
 // Causes ambiguity, because this is removed, the resulting issue (no better solution, see C2593)
 // (mixed type comparisons require explicit casts) is described in the test:
 // operator float() { return (float) value; }
 // operator float() { return (double) value; }
};


inline int operator+ ( const Zint& a, const Zint& b );
inline int operator- ( const Zint& a, const Zint& b );
inline int operator* ( const Zint& a, const Zint& b );
inline int operator/ ( const Zint& a, const Zint& b );
/* Creates C2593 for some reason...
int operator+ ( Zint a, Zint b );
int operator- ( Zint a, Zint b );
int operator* ( Zint a, Zint b );
int operator/ ( Zint a, Zint b );
*/
// Casted int operations
inline int operator+ ( const Zint& a, int b );
inline int operator- ( const Zint& a, int b );
inline int operator* ( const Zint& a, int b );
inline int operator/ ( const Zint& a, int b );
inline int operator% ( const Zint& a, int b );
inline int operator+ ( int b, const Zint& a );
inline int operator- ( int b, const Zint& a );
inline int operator* ( int b, const Zint& a );
inline int operator/ ( int b, const Zint& a );
inline int operator% ( int b, const Zint& a );
// Float operations (leans toward float precision)
inline int operator+ ( const Zint& a, float b );
inline int operator- ( const Zint& a, float b );
inline int operator* ( const Zint& a, float b );
inline int operator/ ( const Zint& a, float b );
inline int operator+ ( float b, const Zint& a );
inline int operator- ( float b, const Zint& a );
inline int operator* ( float b, const Zint& a );
inline int operator/ ( float b, const Zint& a );
// Casted double operations (leans toward double precision)
inline int operator+ ( const Zint& a, double b );
inline int operator- ( const Zint& a, double b );
inline int operator* ( const Zint& a, double b );
inline int operator/ ( const Zint& a, double b );
inline int operator+ ( double b, const Zint& a );
inline int operator- ( double b, const Zint& a );
inline int operator* ( double b, const Zint& a );
inline int operator/ ( double b, const Zint& a );
// Modulo
inline int operator% ( const Zint &a, const Zint &b );
// Boolean operations
inline bool operator>= ( const Zint& a, const Zint& b );
inline bool operator>= ( const Zint& a, unsigned int b );
inline bool operator>= ( const Zint& a, int b );
inline bool operator>= ( const Zint& a, float b );
inline bool operator>= ( const Zint& a, double b );
inline bool operator>= ( unsigned int a, const Zint& b );
inline bool operator>= ( int a, const Zint& b );
inline bool operator>= ( float a, const Zint& b );
inline bool operator>= ( double a, const Zint& b );
inline bool operator== ( const Zint& a, const Zbyte& b );
inline bool operator== ( const Zint& a, const Zushort& b );
inline bool operator== ( const Zint& a, const Zuint& b );
inline bool operator== ( const Zint& a, const Zdouble& b );
inline bool operator== ( const Zbyte& a, const Zint& b );
inline bool operator== ( const Zushort& a, const Zint& b );
inline bool operator== ( const Zuint& a, const Zint& b );
inline bool operator== ( const Zdouble& a, const Zint& b );
inline bool operator== ( const Zint& a, const Zint& b );
inline bool operator== ( const Zint& a, unsigned int b );
inline bool operator== ( const Zint& a, int b );
inline bool operator== ( const Zint& a, float b );
inline bool operator== ( const Zint& a, double b );
inline bool operator== ( unsigned int a, const Zint& b );
inline bool operator== ( int a, const Zint& b );
inline bool operator== ( float a, const Zint& b );
inline bool operator== ( double a, const Zint& b );
inline bool operator!= ( const Zint& a, const Zint& b );
inline bool operator!= ( const Zint& a, unsigned int b );
inline bool operator!= ( const Zint& a, int b );
inline bool operator!= ( const Zint& a, float b );
inline bool operator!= ( const Zint& a, double b );
inline bool operator!= ( unsigned int a, const Zint& b );
inline bool operator!= ( int a, const Zint& b );
inline bool operator!= ( float a, const Zint& b );
inline bool operator!= ( double a, const Zint& b );
inline bool operator<= ( const Zint& a, const Zint& b );
inline bool operator<= ( const Zint& a, unsigned int b );
inline bool operator<= ( const Zint& a, int b );
inline bool operator<= ( const Zint& a, float b );
inline bool operator<= ( const Zint& a, double b );
inline bool operator<= ( unsigned int a, const Zint& b );
inline bool operator<= ( int a, const Zint& b );
inline bool operator<= ( float a, const Zint& b );
inline bool operator<= ( double a, const Zint& b );
inline bool operator> ( const Zint& a, const Zint& b );
inline bool operator> ( const Zint& a, unsigned int b );
inline bool operator> ( const Zint& a, int b );
inline bool operator> ( const Zint& a, float b );
inline bool operator> ( const Zint& a, double b );
inline bool operator> ( unsigned int a, const Zint& b );
inline bool operator> ( int a, const Zint& b );
inline bool operator> ( float a, const Zint& b );
inline bool operator> ( double a, const Zint& b );
inline bool operator< ( const Zint& a, const Zint& b );
inline bool operator< ( const Zint& a, unsigned int b );
inline bool operator< ( const Zint& a, int b );
inline bool operator< ( const Zint& a, float b );
inline bool operator< ( const Zint& a, double b );
inline bool operator< ( unsigned int a, const Zint& b );
inline bool operator< ( int a, const Zint& b );
inline bool operator< ( float a, const Zint& b );
inline bool operator< ( double a, const Zint& b );

/// Zint ////////////////////////////////////////////////////////////////////////////////////////// end

/// Zuint ////////////////////////////////////////////////////////////////////////////////////////// start

enum Zuint_bits {
 Zuint_0 =0x1,
 Zuint_1 =0x2,
 Zuint_2 =0x4,
 Zuint_3 =0x8,
 Zuint_4 =0x10,
 Zuint_5 =0x20,
 Zuint_6 =0x40,
 Zuint_7 =0x80,
 Zuint_8 =0x100,
 Zuint_9 =0x200,
 Zuint_10=0x400,
 Zuint_11=0x800,
 Zuint_12=0x1000,
 Zuint_13=0x2000,
 Zuint_14=0x4000,
 Zuint_15=0x8000,
 Zuint_16=0x10000,
 Zuint_17=0x20000,
 Zuint_18=0x40000,
 Zuint_19=0x80000,
 Zuint_20=0x100000,
 Zuint_21=0x200000,
 Zuint_22=0x400000,
 Zuint_23=0x800000,
 Zuint_24=0x1000000,
 Zuint_25=0x2000000,
 Zuint_26=0x4000000,
 Zuint_27=0x8000000,
 Zuint_28=0x10000000,
 Zuint_29=0x20000000,
 Zuint_30=0x40000000,
 Zuint_31=0x80000000
};

class Zuint {
public:
 unsigned int value;
 Zuint() { value=0; }
 Zuint( unsigned int value ) { this->value=value; }
 std::string toString() { return std::to_string(value); }
 operator std::string() { return toString(); }
 operator unsigned int() { return value; }
 operator unsigned int *() { return &value; }
 Zuint *operator()() { return this; }
 unsigned int operator()( unsigned int i ) { return value=i; }
 unsigned int operator()( int i ) { return value=(unsigned int) i; }
 unsigned int operator()( float f ) { return value=(unsigned int)f; }
 unsigned int operator()( double d ) { return value=(unsigned int)d; }
 unsigned int operator()( Zbyte &i );
 unsigned int operator()( Zuint &i ) { return i.value; }
 unsigned int operator()( Zint &i );
 unsigned int operator()( Zfloat &f );
 unsigned int operator()( Zdouble &d );
 bool isOn( unsigned int bitwise_flag ) {
  return ( value & bitwise_flag ) > 0;
 }
 bool isOff( unsigned int bitwise_flag ) { return !isOn(bitwise_flag); }
 void Toggle( unsigned int bitwise_flag, bool on ) {
  if ( on ) value = value | bitwise_flag;
  else value = value & ~bitwise_flag;
 }
 Zuint& operator= ( const unsigned int i ) { value=i; return *this; }
 Zuint& operator= ( const int i ) { value=i; return *this; }
 Zuint& operator= ( const float f ) { value=(int)f; return *this; }
 Zuint& operator= ( const double d ) { value=(int) d; return *this; }
 Zuint& operator= ( const Zuint& i ) { value=i.value; return *this; }
 Zuint& operator= ( const Zbyte& b );
 Zuint& operator= ( const Zint& i );
 Zuint& operator= ( const Zfloat& f );
 Zuint& operator= ( const Zdouble& d );
 Zuint& operator= ( const std::string& s );
 Zuint& operator+= ( const Zuint& i ) { value+=i.value; return *this; }
 Zuint& operator-= ( const Zuint& i ) { value-=i.value; return *this; }
 Zuint& operator*= ( const Zuint& i ) { value*=i.value; return *this; }
 Zuint& operator/= ( const Zuint& i ) { value/=i.value; return *this; }
 Zuint& operator+= ( const Zint& i ) { value+=(unsigned int) i.value; return *this; }
 Zuint& operator-= ( const Zint& i ) { value-=(unsigned int) i.value; return *this; }
 Zuint& operator*= ( const Zint& i ) { value*=(unsigned int) i.value; return *this; }
 Zuint& operator/= ( const Zint& i ) { value/=(unsigned int) i.value; return *this; }
 Zuint& operator+= ( const unsigned char i ) { value+=(unsigned int) i; return *this; }
 Zuint& operator-= ( const unsigned char i ) { value-=(unsigned int) i; return *this; }
 Zuint& operator*= ( const unsigned char i ) { value*=(unsigned int) i; return *this; }
 Zuint& operator/= ( const unsigned char i ) { value/=(unsigned int) i; return *this; }
 Zuint& operator+= ( const unsigned short i ) { value+=(unsigned int) i; return *this; }
 Zuint& operator-= ( const unsigned short i ) { value-=(unsigned int) i; return *this; }
 Zuint& operator*= ( const unsigned short i ) { value*=(unsigned int) i; return *this; }
 Zuint& operator/= ( const unsigned short i ) { value/=(unsigned int) i; return *this; }
 Zuint& operator+= ( const int i ) { value+=(unsigned int) i; return *this; }
 Zuint& operator-= ( const int i ) { value-=(unsigned int) i; return *this; }
 Zuint& operator*= ( const int i ) { value*=(unsigned int) i; return *this; }
 Zuint& operator/= ( const int i ) { value/=(unsigned int) i; return *this; }
 Zuint& operator+= ( const unsigned int i ) { value+=i; return *this; }
 Zuint& operator-= ( const unsigned int i ) { value-=i; return *this; }
 Zuint& operator*= ( const unsigned int i ) { value*=i; return *this; }
 Zuint& operator/= ( const unsigned int i ) { value/=i; return *this; }
 Zuint& operator+= ( const float i ) { value+=(unsigned int) i; return *this; }
 Zuint& operator-= ( const float i ) { value-=(unsigned int) i; return *this; }
 Zuint& operator*= ( const float i ) { value*=(unsigned int) i; return *this; }
 Zuint& operator/= ( const float i ) { value/=(unsigned int) i; return *this; }
 Zuint& operator+= ( const double i ) { value+=(unsigned int) i; return *this; }
 Zuint& operator-= ( const double i ) { value-=(unsigned int) i; return *this; }
 Zuint& operator*= ( const double i ) { value*=(unsigned int) i; return *this; }
 Zuint& operator/= ( const double i ) { value/=(unsigned int) i; return *this; }
 Zuint& operator++ (int) { value+=1; return *this; }
 Zuint& operator-- (int) { value-=1; return *this; }
 operator int() { return (int) value; }
 bool operator !() { return ( value == 0 ); }
 // Not used intentionally to create warning:
 // operator float() { return (float)value; }
 // operator double() { return (double)value; }
 // Causes ambiguity, because this is removed, the resulting issue (no better solution, see C2593)
 // (mixed type comparisons require explicit casts) is described in the test:
 // operator float() { return (float) value; }
 // operator float() { return (double) value; }
};

inline bool operator< ( unsigned int a, const Zuint& b );

inline unsigned int operator+ ( const Zuint& a, const Zuint& b );
inline unsigned int operator- ( const Zuint& a, const Zuint& b );
inline unsigned int operator* ( const Zuint& a, const Zuint& b );
inline unsigned int operator/ ( const Zuint& a, const Zuint& b );
// Casted unsigned int operations
inline unsigned int operator+ ( const Zuint& a, int b );
inline unsigned int operator- ( const Zuint& a, int b );
inline unsigned int operator* ( const Zuint& a, int b );
inline unsigned int operator/ ( const Zuint& a, int b );
inline unsigned int operator+ ( int b, const Zuint& a );
inline unsigned int operator- ( int b, const Zuint& a );
inline unsigned int operator* ( int b, const Zuint& a );
inline unsigned int operator/ ( int b, const Zuint& a );
// Casted int operations
inline unsigned int operator+ ( const Zuint& a, int b );
inline unsigned int operator- ( const Zuint& a, int b );
inline unsigned int operator* ( const Zuint& a, int b );
inline unsigned int operator/ ( const Zuint& a, int b );
inline unsigned int operator+ ( int b, const Zuint& a );
inline unsigned int operator- ( int b, const Zuint& a );
inline unsigned int operator* ( int b, const Zuint& a );
inline unsigned int operator/ ( int b, const Zuint& a );
// Float operations (leans toward float precision)
inline unsigned int operator+ ( const Zuint& a, float b );
inline unsigned int operator- ( const Zuint& a, float b );
inline unsigned int operator* ( const Zuint& a, float b );
inline unsigned int operator/ ( const Zuint& a, float b );
inline unsigned int operator+ ( float b, const Zuint& a );
inline unsigned int operator- ( float b, const Zuint& a );
inline unsigned int operator* ( float b, const Zuint& a );
inline unsigned int operator/ ( float b, const Zuint& a );
// Casted double operations (leans toward double precision)
inline unsigned int operator+ ( const Zuint& a, double b );
inline unsigned int operator- ( const Zuint& a, double b );
inline unsigned int operator* ( const Zuint& a, double b );
inline unsigned int operator/ ( const Zuint& a, double b );
inline unsigned int operator+ ( double b, const Zuint& a );
inline unsigned int operator- ( double b, const Zuint& a );
inline unsigned int operator* ( double b, const Zuint& a );
inline unsigned int operator/ ( double b, const Zuint& a );

/// Zuint ////////////////////////////////////////////////////////////////////////////////////////// end

/// Zdouble ////////////////////////////////////////////////////////////////////////////////////////// start

class Zdouble {
public:
 double value;
 Zdouble() { value=0.0; }
 Zdouble( double value ) { this->value=value; }
 std::string toString() { return std::to_string(value); }
 operator std::string() { return toString(); }
 double abs() { return std::abs(value); }
 operator double() { return value; }
 operator double *() { return &value; }
 Zdouble *operator()() { return this; }
 double operator()( int i ) { return value=(double)i; }
 double operator()( float f ) { return value=(double)f; }
 double operator()( double d ) { return value=d; }
 double operator()( Zbyte &b );
 double operator()( Zuint &i );
 double operator()( Zint &i );
 double operator()( Zfloat &f );
 double operator()( Zdouble &d ) { return d.value; }
 Zdouble& operator= ( const int i ) { value=(double)i; return *this; }
 Zdouble& operator= ( const float f ) { value=(double)f; return *this; }
 Zdouble& operator= ( const double d ) { value=d; return *this; }
 Zdouble& operator= ( const Zbyte& b );
 Zdouble& operator= ( const Zuint& b );
 Zdouble& operator= ( const Zint& i );
 Zdouble& operator= ( const Zfloat& f );
 Zdouble& operator= ( const Zdouble& d ) { value=d.value; return *this; }
 Zdouble& operator= ( const std::string& s );
 Zdouble& operator+= ( const Zbyte& b ) { value+=(double)b.value; return *this; }
 Zdouble& operator-= ( const Zbyte& b ) { value-=(double)b.value; return *this; }
 Zdouble& operator*= ( const Zbyte& b ) { value*=(double)b.value; return *this; }
 Zdouble& operator/= ( const Zbyte& b ) { value/=(double)b.value; return *this; }
 Zdouble& operator+= ( const Zint& i ) { value+=(double)i.value; return *this; }
 Zdouble& operator-= ( const Zint& i ) { value-=(double)i.value; return *this; }
 Zdouble& operator*= ( const Zint& i ) { value*=(double)i.value; return *this; }
 Zdouble& operator/= ( const Zint& i ) { value/=(double)i.value; return *this; }
 Zdouble& operator+= ( const Zuint& i ) { value+=(double)i.value; return *this; }
 Zdouble& operator-= ( const Zuint& i ) { value-=(double)i.value; return *this; }
 Zdouble& operator*= ( const Zuint& i ) { value*=(double)i.value; return *this; }
 Zdouble& operator/= ( const Zuint& i ) { value/=(double)i.value; return *this; }
 Zdouble& operator+= ( const Zfloat& f ) { value+=(double)f.value; return *this; }
 Zdouble& operator-= ( const Zfloat& f ) { value-=(double)f.value; return *this; }
 Zdouble& operator*= ( const Zfloat& f ) { value*=(double)f.value; return *this; }
 Zdouble& operator/= ( const Zfloat& f ) { value/=(double)f.value; return *this; }
 Zdouble& operator+= ( const Zdouble& d ) { value+=d.value; return *this; }
 Zdouble& operator-= ( const Zdouble& d ) { value-=d.value; return *this; }
 Zdouble& operator*= ( const Zdouble& d ) { value*=d.value; return *this; }
 Zdouble& operator/= ( const Zdouble& d ) { value/=d.value; return *this; }
 Zdouble& operator+= ( const unsigned char d ) { value+=(double) d; return *this; }
 Zdouble& operator-= ( const unsigned char d ) { value-=(double) d; return *this; }
 Zdouble& operator*= ( const unsigned char d ) { value*=(double) d; return *this; }
 Zdouble& operator/= ( const unsigned char d ) { value/=(double) d; return *this; }
 Zdouble& operator+= ( const unsigned short d ) { value+=(double) d; return *this; }
 Zdouble& operator-= ( const unsigned short d ) { value-=(double) d; return *this; }
 Zdouble& operator*= ( const unsigned short d ) { value*=(double) d; return *this; }
 Zdouble& operator/= ( const unsigned short d ) { value/=(double) d; return *this; }
 Zdouble& operator+= ( const int d ) { value+=(double) d; return *this; }
 Zdouble& operator-= ( const int d ) { value-=(double) d; return *this; }
 Zdouble& operator*= ( const int d ) { value*=(double) d; return *this; }
 Zdouble& operator/= ( const int d ) { value/=(double) d; return *this; }
 Zdouble& operator+= ( const unsigned int d ) { value+=(double) d; return *this; }
 Zdouble& operator-= ( const unsigned int d ) { value-=(double) d; return *this; }
 Zdouble& operator*= ( const unsigned int d ) { value*=(double) d; return *this; }
 Zdouble& operator/= ( const unsigned int d ) { value/=(double) d; return *this; }
 Zdouble& operator+= ( const float d ) { value+=(double) d; return *this; }
 Zdouble& operator-= ( const float d ) { value-=(double) d; return *this; }
 Zdouble& operator*= ( const float d ) { value*=(double) d; return *this; }
 Zdouble& operator/= ( const float d ) { value/=(double) d; return *this; }
 Zdouble& operator+= ( const double d ) { value+=d; return *this; }
 Zdouble& operator-= ( const double d ) { value-=d; return *this; }
 Zdouble& operator*= ( const double d ) { value*=d; return *this; }
 Zdouble& operator/= ( const double d ) { value/=d; return *this; }
 Zdouble& operator++ (int) { value+=1.0; return *this; }
 Zdouble& operator-- (int) { value-=1.0; return *this; }
 const double operator-() { return -value; }
 bool operator !() { return ( value == 0.0 ); }
 // Not used intentionally to create warning:
 // operator float() { return (float) value; }
 // operator int() { return (int) value; }
 // Causes ambiguity, because this is removed, the resulting issue (no better solution, see C2593)
 // (mixed type comparisons require explicit casts) is described in the test:
 // operator int() { return (int) value; }
 // operator float() { return (float) value; }
};

// Mixed type operations
inline double operator+ ( const Zdouble& a, const Zfloat& b );
inline double operator+ ( const Zfloat& a, const Zdouble& b );
inline double operator+ ( const Zdouble& a, const Zint& b );
inline double operator+ ( const Zint& a, const Zdouble& b );
inline double operator* ( const Zdouble& a, const Zfloat& b );
inline double operator* ( const Zfloat& a, const Zdouble& b );
inline double operator* ( const Zdouble& a, const Zint& b );
inline double operator* ( const Zint& a, const Zdouble& b );
// Zdouble and itself
inline double operator+ ( const Zdouble& a, const Zdouble& b );
inline double operator- ( const Zdouble& a, const Zdouble& b );
inline double operator* ( const Zdouble& a, const Zdouble& b );
inline double operator/ ( const Zdouble& a, const Zdouble& b );
/* Creates C2593 for some reason...
double operator+ ( Zdouble a, Zdouble b );
double operator- ( Zdouble a, Zdouble b );
double operator* ( Zdouble a, Zdouble b );
double operator/ ( Zdouble a, Zdouble b );
*/
// Casted int operations
inline double operator+ ( const Zdouble& a, int b );
inline double operator- ( const Zdouble& a, int b );
inline double operator* ( const Zdouble& a, int b );
inline double operator/ ( const Zdouble& a, int b );
inline double operator+ ( int b, const Zdouble& a );
inline double operator- ( int b, const Zdouble& a );
inline double operator* ( int b, const Zdouble& a );
inline double operator/ ( int b, const Zdouble& a );
// Float operations
inline double operator+ ( const Zdouble& a, float b );
inline double operator- ( const Zdouble& a, float b );
inline double operator* ( const Zdouble& a, float b );
inline double operator/ ( const Zdouble& a, float b );
inline double operator+ ( float b, const Zdouble& a );
inline double operator- ( float b, const Zdouble& a );
inline double operator* ( float b, const Zdouble& a );
inline double operator/ ( float b, const Zdouble& a );
// Casted double operations (leans toward double precision)
inline double operator+ ( const Zdouble& a, double b );
inline double operator- ( const Zdouble& a, double b );
inline double operator* ( const Zdouble& a, double b );
inline double operator/ ( const Zdouble& a, double b );
inline double operator+ ( double b, const Zdouble& a );
inline double operator- ( double b, const Zdouble& a );
inline double operator* ( double b, const Zdouble& a );
inline double operator/ ( double b, const Zdouble& a );
// Boolean operations
inline bool operator>= ( const Zdouble& a, const Zdouble& b );
inline bool operator>= ( const Zdouble& a, int b );
inline bool operator>= ( const Zdouble& a, float b );
inline bool operator>= ( const Zdouble& a, double b );
inline bool operator>= ( int a, const Zdouble& b );
inline bool operator>= ( float a, const Zdouble& b );
inline bool operator>= ( double a, const Zdouble& b );
inline bool operator== ( const Zdouble& a, const Zdouble& b );
inline bool operator== ( const Zdouble& a, int b );
inline bool operator== ( const Zdouble& a, float b );
inline bool operator== ( const Zdouble& a, double b );
inline bool operator== ( int a, const Zdouble& b );
inline bool operator== ( float a, const Zdouble& b );
inline bool operator== ( double a, const Zdouble& b );
inline bool operator!= ( const Zdouble& a, const Zdouble& b );
inline bool operator!= ( const Zdouble& a, int b );
inline bool operator!= ( const Zdouble& a, float b );
inline bool operator!= ( const Zdouble& a, double b );
inline bool operator!= ( int a, const Zdouble& b );
inline bool operator!= ( float a, const Zdouble& b );
inline bool operator!= ( double a, const Zdouble& b );
inline bool operator<= ( const Zdouble& a, const Zdouble& b );
inline bool operator<= ( const Zdouble& a, int b );
inline bool operator<= ( const Zdouble& a, float b );
inline bool operator<= ( const Zdouble& a, double b );
inline bool operator<= ( int a, const Zdouble& b );
inline bool operator<= ( float a, const Zdouble& b );
inline bool operator<= ( double a, const Zdouble& b );
inline bool operator> ( const Zdouble& a, const Zdouble& b );
inline bool operator> ( const Zdouble& a, int b );
inline bool operator> ( const Zdouble& a, float b );
inline bool operator> ( const Zdouble& a, double b );
inline bool operator> ( int a, const Zdouble& b );
inline bool operator> ( float a, const Zdouble& b );
inline bool operator> ( double a, const Zdouble& b );
inline bool operator< ( const Zdouble& a, const Zdouble& b );
inline bool operator< ( const Zdouble& a, int b );
inline bool operator< ( const Zdouble& a, float b );
inline bool operator< ( const Zdouble& a, double b );
inline bool operator< ( int a, const Zdouble& b );
inline bool operator< ( float a, const Zdouble& b );
inline bool operator< ( double a, const Zdouble& b );


/// Zfloat ////////////////////////////////////////////////////////////////////////////////////////// end

// Other ZeroTypes


#define Zp Zpointer
#define Zdis Zdisposable
#define Zdis_manual Zpointer           // Means you gotta dispose yourself.  Used in places where the class wants to use forward declared stuff and can't use Zdis

#ifndef null
#define null nullptr
#else
#error Zpointer.h could not override null as nullptr because null is already defined.
#endif

/// Zpointer //////////////////////////////////////////////////////////////////////////////////////// start

template<class T>
class Zpointer {
public:
 T *pointer;
 Zpointer() { pointer=nullptr; }
 Zpointer( T *value ) { this->pointer=value; }
 ~Zpointer() {
  return;
 }
 Zpointer( Zpointer<T>& p ) { this->pointer=p.pointer; }
 void Delete() {
  if ( pointer ) {
   delete pointer;
   pointer=nullptr;
  }
 }
 void Delete( T *replace ) {
  if ( pointer ) {
   delete pointer;
   pointer=replace;
  }
 }
 operator T*() { return pointer; }
 T operator* ( Zpointer<T>& t ) { return *pointer; }
 // T **operator& ( Zpointer<T>& t ) { return &pointer; }
 Zpointer<T>& operator()( T *value ) { pointer=value; return *this; }
 Zpointer<T>& operator()( Zpointer<T>& t ) { pointer=t.pointer; return *this; }
 Zpointer<T>& operator= ( T *value ) { pointer=value; return *this; }
 Zpointer<T>& operator= ( Zpointer<T>& t ) { pointer=t.pointer; return *this; }
 T *operator->() {
#if defined(DEBUG) || defined(DEBUG_OUTPUT)
  if ( !pointer ) {
   OUTPUT("Zpointer:->() referenced when null.\n");
  }
#endif
  return pointer;
 }
};

typedef Zpointer<void>   Pvoid;
typedef Zpointer<int>    Pint;
typedef Zpointer<float>  Pfloat;
typedef Zpointer<double> Pdouble;

/*
* Protected zPointer which only allows itself to be set once,
* used mainly for debugging.
*/
template<class T>
class pZpointer {
public:
 int set;
 T *pointer;
 pZpointer() { set = 0; pointer = nullptr; }
 pZpointer(T *value) { set = 0; this->pointer = value; }
 ~pZpointer() {
  return;
 }
 pZpointer( pZpointer<T>& p ) { this->pointer=p.pointer; }
 void Delete() {
  if ( pointer ) {
   delete pointer;
   pointer=nullptr;
  }
 }
 operator T*() { return pointer; }
 T operator* ( pZpointer<T>& t ) { return *pointer; }
 // T **operator& ( Zpointer<T>& t ) { return &pointer; }
 bool Protected() {
  if ( set == 1 ) {
   OUTPUT("pZpointer Warning: protected pointer assigned twice!\n");
   return false;
  } else set++;
  return true;
 }
 pZpointer<T>& operator()( T *value ) { if (Protected()) return *this; pointer=value; return *this; }
 pZpointer<T>& operator()( Zpointer<T>& t ) { if (Protected()) return *this; pointer=t.pointer; return *this; }
 pZpointer<T>& operator()( pZpointer<T>& t ) { if (Protected()) return *this; pointer=t.pointer; return *this; }
 pZpointer<T>& operator= ( T *value ) { if (Protected()) return *this; pointer=value; return *this; }
 pZpointer<T>& operator= ( Zpointer<T>& t ) { if (Protected()) return *this; pointer=t.pointer; return *this; }
 pZpointer<T>& operator= ( pZpointer<T>& t ) { if (Protected()) return *this; pointer=t.pointer; return *this; }
 T *operator->() {
#if defined(DEBUG) || defined(DEBUG_OUTPUT)
  if ( !pointer ) {
   OUTPUT("pZpointer:->() referenced when null.\n");
  }
#endif
  return pointer;
 }
};
#define pZp pZpointer

// Notes from the underground
/*
class Zvoid : public Zpointer<void> {
public:
Zvoid() { .. }
Zvoid(void* value) : Zpointer<void>(value) { .. }
Zvoid(Zvoid& p) : Zpointer<void>(p) { .. } 
using Zpointer<void>::operator =;
};
*/

// On debugging pointers:  Zpointer could be attached to a historical pointer system
// that keeps track of all assignments, accesses, etc.

/// Zpointer //////////////////////////////////////////////////////////////////////////////////////// end

/// Zdisposable ///////////////////////////////////////////////////////////////////////////////////// start

template<class T>
class Zdisposable {
public:
 T *pointer;
 Zdisposable() {
  pointer=nullptr;
 }
 void I() { Instantiate(); }
 void Instantiate() {
  if ( !pointer ) pointer=new T;
 }
 void Deinstantiate() {
  if ( pointer ) {
   delete pointer;
   pointer=nullptr;
  }
 }
 void Recycle() {
  if ( pointer ) delete pointer;
  pointer=new T;
 }
 void Recycle( T *replacement ) {
  if ( pointer ) delete pointer;
  pointer=replacement;
 }
 operator T*() { return pointer; }
 T *operator= ( T *replacement ) {
  Recycle(replacement);
  return pointer;
 }
 T *operator= ( Zdisposable<T>& t ) {
  if ( pointer ) {
   if ( pointer != t.pointer ) Deinstantiate();
  }
  pointer=t.pointer;
  t.pointer=null;
  return pointer;
 }
 T operator* ( Zdisposable<T>& t ) { return *pointer; }
 T operator& ( Zdisposable<T>& t ) { return &pointer; }
 // T **operator& ( Zpointer<T>& t ) { return &pointer; }
 T *operator->() {
  if ( !pointer ) {
   Instantiate();
  }
  return pointer;
 }
 ~Zdisposable() {
  Deinstantiate();
 }
};
#define Zdis Zdisposable

/// Zdisposable ///////////////////////////////////////////////////////////////////////////////////// end

// Lightweight vector.

template<class T>
class ZIndexed {
public:
 T oob;
 T *list;
 size_t unit,length,w,h;
 ZIndexed() {
  list=nullptr;
  w=h=0;
  length=0;
  unit=sizeof(T);
  //  ZeroMemory(&oob,(SIZE_T)unit);
  memset(&oob, 0, sizeof(oob));
 }
 ZIndexed( size_t length ) { Size(length); }
 ZIndexed( size_t w, size_t h ) { Size(w,h); }
 bool inBounds( int i ) {
  if ( i < 0 ) return false;
  size_t index=(size_t) i;
  if ( index >= length ) return false;
  return true;
 }
 bool inBounds( int i, int j ) {
  if ( i < 0 || j < 0 ) return false;
  size_t index=(size_t) (i+j*w);
  if ( index >= length ) return false;
  return true;
 }
 void Swap( ZIndexed<T> *values ) {
  T *tempList = list;
  size_t tempLength = length;
  size_t tempW = w;
  size_t tempH = h;
  list=values->list;
  length=values->length;
  w=values->w;
  h=values->h;
  values->list=tempList;
  values->length=tempLength;
  values->w=tempW;
  values->h=tempH;
 }
 T *Increase() {
  size_t newsize=length+1;
  Size(newsize,true);
  return Element((unsigned int) newsize-1);
 }
 void IncreaseW() {
  IncreaseW(w+1);
 }
 void IncreaseH() {
  IncreaseH(h+1);
 }
 void IncreaseW( size_t neww ) {
  if ( neww < w ) { ClipW(neww); return; }
  if ( neww == w ) return;
  if ( h == 0 ) Size(neww,1);
  else {
   size_t desiredLength=neww*h;
   T *newlist;
   try { newlist= new T[desiredLength]; } catch (std::bad_alloc& ba) {
    OUTPUT("NEW: bad_alloc caught: %s requesting %d\n", ba.what(), (int) (sizeof(T)*desiredLength) );
   }
   for ( int i=0; i<w; i++ ) for ( int j=0; j<h; j++ ) newlist[i+j*w]=list[i+j*w];
   delete[] list;
   length=desiredLength;
   list=newlist;
   w=neww;
  }
 }
 void IncreaseH( size_t newh ) {
  if ( newh < h ) { ClipH(newh); return; }
  if ( newh == h ) return;
  if ( w == 0 ) Size(1,newh);
  else {
   size_t desiredLength=w*newh;
   T *newlist;
   try { newlist= new T[desiredLength]; } catch (std::bad_alloc& ba) {
    OUTPUT("NEW: bad_alloc caught: %s requesting %d\n", ba.what(), (int) (sizeof(T)*desiredLength) );
   }
   for ( int i=0; i<w; i++ ) for ( int j=0; j<h; j++ ) newlist[i+j*w]=list[i+j*w];
   delete[] list;
   length=desiredLength;
   list=newlist;
   h=newh;
  }
 }
 void ClipW() {
  if ( w==1 ) { Size(0); return; }
  else if ( w==0 ) return;
  ClipW(w-1);
 }
 void ClipH() {
  if ( h==1 ) { Size(0); return; }
  else if ( h==0 ) return;
  ClipW(h-1);
 }
 void ClipW( size_t neww ) {
  if ( neww==0 ) Size(0);
  else
   if ( neww > w ) IncreaseW(neww);
   else {
    size_t desiredLength=neww*h;
    T *newlist;
    try { newlist= new T[desiredLength]; } catch (std::bad_alloc& ba) {
     OUTPUT("NEW: bad_alloc caught: %s requesting %d\n", ba.what(), (int) (sizeof(T)*desiredLength) );
    }
    for ( int i=0; i<neww; i++ ) for ( int j=0; j<h; j++ ) newlist[i+j*w]=list[i+j*w];
    delete[] list;
    length=desiredLength;
    list=newlist;
    w=neww;
   }
 }
 void ClipH( size_t newh ) {
  if ( newh==0 ) Size(0);
  else
   if ( newh > h ) IncreaseH(newh);
   else {
    size_t desiredLength=w*newh;
    T *newlist;
    try { newlist= new T[desiredLength]; } catch (std::bad_alloc& ba) {
     OUTPUT("NEW: bad_alloc caught: %s requesting %d\n", ba.what(), (int) (sizeof(T)*desiredLength) );
    }
    for ( int i=0; i<w; i++ ) for ( int j=0; j<newh; j++ ) newlist[i+j*w]=list[i+j*w];
    delete[] list;
    length=desiredLength;
    list=newlist;
    h=newh;
   }
 }
 void Size( size_t w, size_t h ) {
  Size(w*h);
  this->w=w;
  this->h=h;
 }
 // Cannot have Size(w,h,keep) because it must be arbitrarily made later
 void Size( size_t desiredLength, having keep ) {
  if ( length==desiredLength ) return;
  if ( desiredLength == 0 ) {
   if ( list ) {
    delete[] list;
    list=nullptr;
   }
   length=0;
   return;
  }
  if ( list ) {
   T *newlist;
   try { newlist= new T[desiredLength]; } catch (std::bad_alloc& ba) {
    OUTPUT("NEW: bad_alloc caught: %s requesting %d\n", ba.what(), (int) (sizeof(T)*desiredLength) );
    return;
   }
   int kept=(int) ( length < desiredLength ? length : desiredLength );
   for ( int i=0; i<kept; i++ ) newlist[i]=list[i];
   delete[] list;
   length=desiredLength;
   list=newlist;
  } else {
   length=desiredLength;
   try { list= new T[desiredLength]; } catch (std::bad_alloc& ba) {
    OUTPUT("NEW: bad_alloc caught: %s requesting %d\n", ba.what(), (int) (sizeof(T)*desiredLength) );
    return;
   }
  }
 }
 void Size( size_t desiredLength ) {
  if ( length==desiredLength ) return;
  if ( desiredLength == 0 ) {
   if ( list ) delete[] list;
   list=nullptr;
   length=0;
   w=0;
   h=0;
   return;
  }
  if ( list ) {
   delete[] list;
   try { list= new T[desiredLength]; } catch (std::bad_alloc& ba) {
    OUTPUT("NEW: bad_alloc caught: %s requesting %d\n", ba.what(), (int) (sizeof(T)*desiredLength) );
   }
  } else {
   try { list= new T[desiredLength]; } catch (std::bad_alloc& ba) {
    OUTPUT("NEW: bad_alloc caught: %s requesting %d\n", ba.what(), (int) (sizeof(T)*desiredLength) );
   }
  }
  length=desiredLength;
 }
 T *Element( unsigned int index ) {
  return &list[index];
 }
 T *Element( unsigned int x, unsigned int y ) {
  return &list[x+y*w];
 }
 T *Element( unsigned int index, bool boundaryCheck ) {
  if ( index >= (unsigned int) length ) return nullptr;
  return &list[index];
 }
 T *Element( unsigned int x, unsigned int y, bool boundaryCheck ) {
  unsigned int index=x+y*w;
  if ( index > (unsigned int) length ) return nullptr;
  return &list[index];
 }
 T Value( unsigned int index ) {
  return list[index];
 }
 T Value( unsigned int x, unsigned int y ) { // unbounded
  return list[x+y*w];
 }
 T Value( unsigned int index, bool boundaryCheck ) {
  if ( index >= (unsigned int) length ) return oob;
  return list[index];
 }
 T Value( unsigned int x, unsigned int y, bool boundaryCheck ) {
  int linear=x+y*w;
  if ( linear > (unsigned int) length ) return oob;
  return list[linear];
 }
 T &Wrap(int index) {
#if defined(DEBUG) || defined(DEBUG_OUTPUT)
  if ( length == 0 ) {
   OUTPUT("Warning: length was 0 when Indexed<T>.Wrap() was called\n");
   return oob;
  }
#endif
  return (*this)[(index<0?-index:index)%length]; // Macos doesn't have abs(int)
 }
 T &operator[] (unsigned int index) {
#if defined(DEBUG) || defined(DEBUG_OUTPUT)
  if ( index >= (unsigned int) length ) {
   OUTPUT("Warning: %d was out of bounds when requested on type %s\n",
    (int) index, typeid(*this).name());
   return oob;
  }
#endif
  return list[index];
 }
 T &operator() (unsigned int x, unsigned int y) {
  unsigned int linear=(unsigned int)(x+y*w);
#if defined(DEBUG) || defined(DEBUG_OUTPUT)
  if ( linear >= (unsigned int) length ) {
   OUTPUT("Warning: %d (%d,%d) was out of bounds when requested on type %s\n",
    linear, (int)x, (int)y, typeid(*this).name());
   return oob;
  }
#endif
  return list[linear];
 }
 T &operator() (unsigned int index) {
  return list[index];
 }
 ~ZIndexed() {
  if ( list ) delete[] list;
 }
};

///////////////////////////////////////////////////////////////////////////

/*******************************************************************
* Utility macros.
*/
#ifndef PI
#define PI          3.1415926535897932384626433832795
#endif
#ifndef TWO_PI
#define TWO_PI     (3.1415926535897932384626433832795*2.0)
#endif
#ifndef HALF_PI
#define HALF_PI    (3.1415926535897932384626433832795/2.0)
#endif
#ifndef QUARTER_PI
#define QUARTER_PI (3.1415926535897932384626433832795/4.0)
#endif
#define THREE_QUARTERS_PI HALF_PI+QUARTER_PI

#define PIf          3.1415926535897932384626433832795f
#define TWO_PIf     (3.1415926535897932384626433832795f*2.0f)
#define HALF_PIf    (3.1415926535897932384626433832795f/2.0f)
#define QUARTER_PIf (3.1415926535897932384626433832795f/4.0f)
#define THREE_QUARTERS_PIf HALF_PIf+QUARTER_PIf

#define PI_Simple 3.1415926
#define TWO_PI_Simple 3.1415926*2

#define zEPSILON 1e-6f
#ifndef MACHINE_EPSILON
#define MACHINE_EPSILON FLT_EPSILON
#endif

//#define EPSILON   FLT_EPSILON// 0.000000000000000111022302463

// math
#define BETWEEN(v,A,B)             ( (A)<(B) ? (v) > (A) && (v) < (B) : (v) < (A) && (v) > (B) )
#define BETWEENInclusive(v,A,B)    ( (A)<(B) ? (v) >= (A) && (v) <= (B) : (v) <= (A) && (v) >= (B) )
#define WITHIN(x,y,x1,y1,x2,y2)    ( (x) >= (x1) && (x) <= (x2) && (y) >= (y1) && (y) <= (y2) )
#define WITHIN3D(x,y,z,x1,y1,z1,x2,y2,z2) ( (x) >= (x1) && (x) <= (x2) && (y) >= (y1) && (y) <= (y2) && (z) >= (z1) && (z) <= (z2) )
#define WITHINCLUSIVE(x,y,x1,y1,x2,y2) ( (x) > (x1) && (x) < (x2) && (y) > (y1) && (y) < (y2) )
#define WITHIN75(ar,m)             ( abs( (ar) - (m) ) < (ar)*0.75 )
#define interpolate(l, v0, v32)    ( (v0) + (l) * ((v32)-(v0)) / 32 )
#define INTERPOLATE(min, max, percent)   ( (min) + ((max) - (min) / (percent) == 0 ? 1 : (percent) ) )
#define LERP1(a,b,r)               ( UMIN(a,b) + (UMAX(a,b) - UMIN(a,b)) * r )
#define bLERP1(from,to,r)          ( (to-from) * r )
#define UMIN(a, b)                 ((a) < (b) ? (a) : (b))
#define UMAX(a, b)                 ((a) > (b) ? (a) : (b))
#define URANGE(less, b, more)            ((b) < (less) ? (less) : ((b) > (more) ? (more) : (b))) // clamp B between A and C
#define INRANGE(x,ra,rb,yes,no)    ((x) >= (ra) && (x) <= (rb) ? (yes) : (no))
#ifndef CLAMP
#define CLAMP(a,b)                 ( (a) < 0 ? 0 : (a) > (b) ? (b) : (a) )
#endif
#define CLAMPTO(v,a,b)             ( (v) < (a) ? (a) : ( (v) > (b) ? (b) : (v) ) )
#define UWRAP(a,b,c)               ((b) > (c) ? (b)-(c) : (b) < (a) ? (b)+(c))
#define SQ(a)                      ((a)*(a))
#ifndef SIGN
#define SIGN(a)                    ( (a) >= 0 ? 1 : -1 )
#endif
#define LINEATE(x,y,x_size)        ( ((x)+(y)*(x_size)) )
#define FINDDESC(x,y,tnum)         ( ((x)*(y)%(tnum)) )
#define NEARBY(a,b,nearness)       ( ((a)-(nearness)) < (b) && ((a)+(nearness)) > b )

#define MIN2MAX(t,a,b) if ( a > b ) { t temp; temp=a; a=b; b=temp; } 
#define MIN2MAXT(t,s,e) if ( s.x > e.x ) { t temp; temp=s.x; s.x=e.x; e.x=temp; } if ( s.y > e.y ) { t temp; temp=s.y; s.y=e.y; e.y=temp; }

#define RANDRANGE(func,max,max2,division) ( ((max)-func(0.0,(max2)))/(func(1.0,division)) )

// Moves numbers toward a value by a delta if not near
#define TOWARDS(v,t,d)         if(BETWEEN(v,(t)-(d),(t)+(d))){}else if((t)>v)v+=(d);else if((t)<(v))v-=(d);
#define TOWARDSTOP(v,t,d)      if(BETWEEN(v,(t)-(d),(t)+(d))){v=t;}else if((t)>v)v+=(d);else if((t)<(v))v-=(d);
//  clip b to a-c
#define RANGE(a, b, c)            ((b) < (a) ? (a) : ((b) > (c) ? (c) : (b)))
///#define NEARZERO(b)               (RANGE(-EPSILON,b,EPSILON)) /// Does not work!

#define ADIFF(a,b)                 ( (a) < (b) ? ((b)-(a)) : ((a)-(b)) )


/// Zstring (UTF-8) ("lite" version) ///////////////////////////////////////////////////////////////////////////////////////// start
using namespace std;

class Zstring;
class Strings;

// To keep within stacksize, we must remove bytes, so we'll remove 8k (originally this was 16384)
#define STRING_SIZE          (8192)

class ZeroTypesStringBuffers {
public:
	char buf[STRING_SIZE];
	char buf2[STRING_SIZE];
	char buf3[STRING_SIZE];
	char tbuf[128];
	ZeroTypesStringBuffers() {
		for (int i = 0; i < STRING_SIZE; i++) {
			buf[i] = '\0';
			buf2[i] = '\0';
			buf3[i] = '\0';
			if ( i < 128 ) tbuf[i]='\0';
		}
	}
	char *Buf() { return buf; }
	char *Buf2() { return buf2; }
	char *Buf3() { return buf3; }
	char *Tbuf() { return tbuf; }
};

ZeroTypesStringBuffers &ZTSB() {
	static ZeroTypesStringBuffers ztsb;
	return ztsb;
}

// strings
#define LOWER(c)                ((c) >= 'A' && (c) <= 'Z' ? (c)+'a'-'A' : (c))
#define UPPER(c)                ((c) >= 'a' && (c) <= 'z' ? (c)+'A'-'a' : (c))
#define IS_ALPHA(c)             ((c) >= 'A' && (c) <= 'Z' || (c) >= 'a' && (c) <= 'z')
#define IS_VOWEL(c)             ((c) == 'A' || (c) == 'a' || \
                                 (c) == 'E' || (c) == 'e' || \
                                 (c) == 'I' || (c) == 'i' || \
                                 (c) == 'O' || (c) == 'o' || \
                                 (c) == 'U' || (c) == 'u'    )

#define _FILLER(c)     ( c == ' ' || c == ',' || c == '=' || c == '\n' || c == '\r' || c == '\t' )
#define _SEP(c)        ( c == '\'' || c == '"' || c == '\'' )
#define _NESTERS(c)    ( c == '{' || c == '[' || c == '(' )
#define _NESTERE(c)    ( c == '}' || c == ']' || c == ')' )
#define _EXPRESSIVE(c) ( c == '+' || c == '/' || c == '-' || c =='%' || c == '*' || c == '<' || c == '>' )

// Converts common types to strings using FMT()
#define B2S(b) (string(b?"Yes":"No"))
#define I2S(i) (FMT("%d",(int)i).c_str())
#define F2S(f) (FMT("%f",(float)f).c_str())
#define D2S(d) (FMT("%f",(double)d).c_str())
#define F22S(f) (FMT("%1.2f",(float)f).c_str())
#define D22S(d) (FMT("%1.2f",(double)d).c_str())
#define F42S(f) (FMT("%1.4f",(float)f).c_str())
#define D42S(d) (FMT("%1.4f",(double)d).c_str())
#define I2S2(i) (FMT("%d",(int)i))
#define F2S2(f) (FMT("%f",(float)f))
#define D2S2(d) (FMT("%f",(double)d))
#define F22S2(f) (FMT("%1.2f",(float)f))
#define D22S2(d) (FMT("%1.2f",(double)d))
#define F42S2(f) (FMT("%1.4f",(float)f))
#define D42S2(d) (FMT("%1.4f",(double)d))

inline void rtrim(string& s, const string& delimiters = " \f\n\r\t\v");
inline void ltrim(string& s, const string& delimiters = " \f\n\r\t\v");
inline void  trim(string& s, const string& delimiters = " \f\n\r\t\v");
// Gather until next substring match or end of string (returns the point right after the substring)
inline const char *gather_to(const char *argument, const char *substr, string *buf);
// Replace search with substitute one time
inline void replaceOnce(string& in, string const &search, string const &substitute);
// Replace all with substitute
inline void replaceAll(string& in, string const &search, string const &substitute);
// Replace all with substitute
inline string replace_all(const string& in, const string& search, const string& substitute);
// Does the string end with the ending?
inline bool endsWith(string const &fullString, string const &ending);
// Does the string end with the ending?
inline bool endsWith(const char *searching, const char *find, bool removePadding);
// Counts the number of "words" (strings of non-spaces separated by spaces) in a string.     Not the best way (should use one_arg)?
inline int words(const char *argument);
// Compare strings, case insensitive.   * Return true if different (compatibility with historical functions).
inline bool str_cmp(const char *astr, const char *bstr);
// Compare strings, case insensitive.   * Return true if different (compatibility with historical functions).
inline bool str_cmp(string astr, string bstr);
// Is the char a digit?
inline bool is_digit(char c);
// Is character in this list of characters
inline bool char_in(char c, const char *list);
// Compare strings, case sensitive. * Return true if different (compatibility with historical functions).
inline bool str_cmp_case(const char *astr, const char *bstr);
// Convert to lower case
inline string lower(string a);
// Return true if an argument is completely numeric.
inline bool is_integer(const char *arg);
// Return true if an argument is completely numeric.
inline bool is_decimal(const char *arg);
// Checks for integer using atoi error handling, decimal only (base-10, no floats).  Does not return the value if valid (tiny inefficiency). Source: http://www.gidforums.com/t-17778.html
inline bool is_int(string k);
// Checks for hexidecimal
inline bool is_hex(string k);
// checks for float
inline bool is_float(string k);
// Converts from hex to int
inline int from_hex(string hex);
// Converts to hex from int
inline string to_hexidecimal(int i);
// Pick off one argument from a string and return the rest. * Understands quotes and {}=[], treats interim commas and equal signs as space. Uses the stack so not recommended for large strings (use string_argument);
inline const char *one_argument(const char *args, char *arg_first);
// Pick off one argument from a string and return the rest. * Understands quotes and {}=[], treats interim commas and equal signs as space. Uses the stack so not recommended for large strings (use string_argument);
inline const char *one_argument_case(const char *args, char *arg_first);
// Pick off one argument from a string and return the rest. * Uses std::string thus dynamic and doesn't use the stack. Understands quotes and {}=[](), treats interim commas and equal signs as space.
inline const char *string_argument(const char *argument, string *arg_first, bool slash_comments=true, bool pound_comments=true);
// Pick off one argument from a string and return the rest. * Uses std::string thus dynamic and doesn't use the stack. Understands quotes and {}=[](), treats interim commas and equal signs as space.
inline const char *string_argument(const char *argument, Zstring *arg_firstz);
// Pick off one argument from a string and return the rest without lowering case. * Uses std::string thus dynamic and doesn't use the stack. Understands quotes and {}=[](), treats interim commas and equal signs as space.
inline const char *string_argument_case(const char *argument, string *arg_first);
// Pick off one argument from a string and return the rest without lowering case. * Uses std::string thus dynamic and doesn't use the stack. Understands quotes and {}=[](), treats interim commas and equal signs as space.
inline const char *string_argument_case(Zstring &sep, const char *argument, string *arg_first);
// Pick off one argument from a string and return the rest. * Uses std::string thus dynamic and doesn't use the stack. Understands quotes and {}=[](), treats interim commas and equal signs as space.
inline const char *string_argument_end(const char *argument, string *arg_first, char *sep);
// Compare strings, case insensitive, for prefix matching. * Return true if hay not a prefix of haystack (compatibility with historical functions).
inline bool str_prefix(const char *astr, const char *bstr);
// Compare strings, case sensitive, for prefix matching. * Return true if astr not a prefix of bstr (compatibility with historical functions).
inline bool str_prefix_case(const char *astr, const char *bstr);
// Makes a string into its lower-case counterpart
inline string strtolower(const char *input);
// Compare strings, case insensitive, for match anywhere. * Returns true if shorter string not part of longer string. (compatibility with historical functions).
inline bool str_infix(const char *astr, const char *bstr);
// Compare strings, case insensitive, for match anywhere. * Returns true if shorter string not part of longer string. (compatibility with historical functions).
inline bool string_infix(string astr, string bstr);
// Compare strings, case insensitive, for match anywhere. * Returns true if shorter string not part of longer string. (compatibility with historical functions).
inline bool str_infix_case(const char *astr, const char *bstr);
// Compare strings, case insensitive, for suffix matching. * Return true if astr not a suffix of bstr (compatibility with historical functions).
inline bool str_suffix(const char *astr, const char *bstr);
// Return a random character from this list, uses uniform()
inline char randomChar(const char *list);
// Indentation state
std::string &indention() {
	static Zstring _indention;
	return _indention.value;
}
// Increase indentation
inline void incdent();
// Decrease indentation
inline void decdent();
// Reset indentation
inline void nodent();
// Low-brow alphanumeric hash.
inline string Hash(int len);
// Low-brow hash compare
inline bool HashCompare5(string *a, string *b);
// Pseudo-
inline string RomanNumerals(int v);
// Convert forward to back slash
inline string slash_to_backslash(const char * s);
// Convert backslash to forward slash
inline string backslash_to_slash(const char * s);
// Make sure there is a trailing forward slash
inline string trailing_slash(const char *s);
// Make sure there is a trailing back-slash
inline string trailing_backslash(const char *s);
// Break down a path/filename and get the basename of the deepest element
inline string basename(const char *path, char sep);


class Zstring {
public:
 string value, result;
 unsigned int length;
 const char *p;
 Zstring() {
  value=string("");
  result=string("");
  length=0;
  p=null;
 }
 Zstring( const char *value ) {
  this->value=string(value);
  result=string("");
  rewind();
 }
 Zstring( const string &value ) {
  this->value=value;
  result=string("");
  rewind();
 }
 Zstring *self() { return this; }
 bool inside( const char * key ) {
  return (value.find(string(key)) != string::npos);
 }
 bool prefix( const char * partial ) {
  return !str_prefix(partial,c_str());
 }
 bool insideCaseless( const char * key ) {
  return str_infix(key,c_str());
 }
 bool is_inside( const char * cloud );
 bool ending( const char *s ) {
  return endsWith(lower(value).c_str(),lower(string(s)).c_str());
 }
 bool Contains( const char *s ) {
  string needle=string(s);
  if ( value.find(needle.c_str()) != std::string::npos ) return true;
  return false;
 }
 bool contains( const char *s ) {
  string needle=string(s);
  string haystack=strtolower(value.c_str());
  /*
  std::transform(haystack.begin(), haystack.end(), haystack.begin(), [](unsigned char c){ 
  //  return std::tolower(c);
  return tolower(c);
  });
  */
  if ( haystack.find(needle.c_str()) != std::string::npos ) return true;
  return false;
 }	
 bool contains( char c ) {
  const char *p=value.c_str();
  while ( *p != '\0' ) {
   if ( *p == c ) return true;
   p++;
  }
  return false;
 }
 int count( char c ) {
  int i=0;
  const char *p=value.c_str();
  while ( *p != '\0' ) {
   if ( *p == c ) i++;
   p++;
  }
  return i;
 }
 char At( unsigned int index ) {
  if ( index >= length ) return '\0';
  return value.at(index);
 }
 void Set( unsigned int index, char c ) {
  if ( index == 0 ) {
   value=value.substr(1,length-1);
  } else if ( index == length-1 ) {
   value=value.substr(0,length-2);
   value+=c;
  } else if ( index > length ) return;
  else value=value.substr(0,index-1)+c+value.substr(index+1,length-index-1);
  rewind();
 }
 int first( char c ) {
  const char *p=value.c_str();
  int i=0;
  while ( *p != '\0' ) {
   if ( *p == c ) return i;
   i++;
  }
  return -1;
 }
 const char *first( const Zstring& in ) {
  const char *p=string_argument(in.value.c_str(),&value);
  rewind();
  return p;
 }
 const char *first( const string& in ) {
  const char *p=string_argument(in.c_str(),&value);
  rewind();
  return p;
 }
 const char *first( const char *in ) {
  const char *p=string_argument(in,&value);
  rewind();
  return p;
 }
 char last() { return At(length-1); }
 const char *word( int number, char *out=buf ) {
  rewind();
  for ( int i=0; i<number; i++ ) next(out);
  return out;
 }
 bool word( const char *matches, int number, char *out=buf ) {
  rewind();
  for ( int i=0; i<number; i++ ) next(out);
  return !str_cmp(matches,out);
 }
 char *next( char *out=buf ) {
  p=one_argument(p,out);
  return out;
 }
 char *next_case( char *out=buf ) {
  p=one_argument_case(p,out);
  return out;
 }
 void Limit( const char *in, size_t truncation ) {
  if ( strlen(in) < truncation ) (*this)=in;
  else {
   (*this)="";
   for ( size_t i=0; i<truncation; i++ ) {
    (*this)+=in[i];
   }
  }
 }
 const char *Next( Zstring &sep ) {
  p=string_argument_case(sep,p,&result);
  return result.c_str();
 }
 const char *Next() {
  p=string_argument(p,&result);
  return result.c_str();
 }
 const char *Next_case() {
  p=string_argument_case(p,&result);
  return result.c_str();
 }
 const char *Peek() {
  string_argument(p,&result);
  return result.c_str();
 }
 const char *NextSOL() {
  while ( *p != '\0' && *p != '\n' ) p++;
  if ( *p != '\0' && *p == '\n' ) p++;
  if ( *p != '\0' && *p == '\r' ) p++;
  return p;
 }
 void rewind() {
  p=value.c_str();
  length=(unsigned int) this->value.length();
 }
 bool is_number() { return is_integer(value.c_str()) || is_decimal(value.c_str()); }
 int integer() { return atoi(value.c_str()); }
 double decimal() { return atof(value.c_str()); }
 bool Empty() {
  Zstring temp=*this;
  temp/=" ";
  return ( length == 0 || temp.length == 0 );
 }
 void Clear() { value=string(""); length=0; }
 string *operator &() { return &value; } // some debate here
 const char *c_str() { return value.c_str(); }
 operator const char *() { return value.c_str(); }
 operator char *() { return (char *) value.c_str(); }
 operator std::string() { return value; }
 operator std::string*() { return &value; }
 Zstring *operator ++() { return this; }
 void operator= (const char *s ) {
  value=s?string(s):"";
  rewind();
 }
 void operator= (string s) {
  value=s;
  rewind();
 }
 Zstring& operator/= ( string b ) {
  replaceAll(value,b,string(""));
  rewind();
  return *this;
 }
 Zstring& operator/= ( Zstring& b ) {
  replaceAll(value,b,string(""));
  rewind();
  return *this;
 }
 operator int() {
  if (is_decimal(value.c_str())) return (int)(atof(value.c_str()));  // rounding?
  else return (int)atoi(value.c_str());
 }
 bool isExactly( const char *b ) {  
  const char *p,*q;
  p=value.c_str();
  q=b;
  while ( *p != '\0' && *q != '\0' ) {
   if (*p != *q) return false;
   p++;
   q++;
  }
  if (*p != *q) return false;
  return true;
 }
 int Compare( const char *b ) {  
  const char *p,*q;
  p=value.c_str(); while ( *p != '\0' && !IS_ALPHA(*p) ) p++;
  q=b; while ( *q != '\0' && !IS_ALPHA(*q) ) q++;
  while ( *p!= '\0' && *q!='\0' ) {
   if ( (int) LOWER(*p) > (int) LOWER(*q) ) return 1;
   if ( (int) LOWER(*p) < (int) LOWER(*q) ) return -1;
   p++; while ( *p != '\0' && !IS_ALPHA(*p) ) p++;
   q++; while ( *q != '\0' && !IS_ALPHA(*q) ) q++;
  }
  if ( *p != '\0' ) return 1;
  if ( *q != '\0' ) return -1;
  return 0;
 }
 operator float() { return (float) atof(value.c_str()); }
 operator double() { Zstring result(value); result/="$"; result/=","; return atof(result.value.c_str()); }
 operator unsigned int() { return length; }
 Zstring& operator --(int) { if ( length > 0 ) { value=value.substr(0,value.size()-1); rewind(); } return *this; }
 Zstring& operator --() { if ( length > 0 ) { value=value.substr(1,value.size()); rewind(); } return *this; }
 Zstring& operator +=( unsigned char c ) { value+=c; rewind(); return *this; }
 Zstring& operator +=( char c ) { char buf[2]; buf[0]=c; buf[1]='\0'; value=value+string(buf); rewind(); return *this; }
 Zstring& operator +=( const string& b ) { value+=b; rewind(); return *this; }
 Zstring& operator +=( const Zstring& b ) { value+=b.value; rewind(); return *this; }
 Zstring& operator +=( const char *b ) { value+=string(b); rewind(); return *this; }
 Zstring& operator -=( const Zstring& b ) { replaceOnce(value,b.value,string("")); rewind(); return *this; }
 Zstring& operator -=( const char *b ) { replaceOnce(value,string(b),string("")); rewind(); return *this; }
 Zstring& operator -=( const string& b ) { replaceOnce(value,b,string("")); rewind(); return *this; }
 Zstring& operator -=( char c ) { char buf[2]; buf[0]=c; buf[1]='\0'; replaceAll(value,string(buf),string("")); rewind(); return *this; }
 Zstring& operator /=( char c ) { char buf[2]; buf[0]=c; buf[1]='\0'; replaceOnce(value,string(buf),string("")); rewind(); return *this; }
 Zstring& operator +=( float f ) { value+=FMT(" %1.2f",(float)f); rewind(); return *this; }
 Zstring& operator +=( double d ) { value+=FMT(" %1.4f",(double)d); rewind(); return *this; }
 Zstring& operator +=( int i ) { value+=FMT(" %d",(int)i); rewind(); return *this; }
 Zstring& operator -=( int i ) {
  rewind();
  const char *w=value.c_str();
  while ( i > 0 ) {
   i--;
   w=Next();
  }
  value=string(this->p);
  rewind();
  return *this;
 }
 string Words();
 string LimitTo( int len );
 string WordWrap( int linelen );
 bool operator !() { return ( Empty() ); }
 bool operator () ( const char *partial ) { return !str_prefix(value.c_str(),partial); }
 bool operator () ( const string& partial ) { return !str_prefix(value.c_str(),partial.c_str()); }
 bool operator () ( const char *partial, bool anywhere ) { return !str_infix(value.c_str(),partial); }
 bool operator () ( const string& partial, bool anywhere ) { return !str_infix(value.c_str(),partial.c_str()); }
 char operator[] (unsigned int index) { return At(index); }
 char operator() (unsigned int index) { return At(index%length); }
 Zstring& operator() ( const char *search, const char *replace ) { replaceAll(value,string(search),string(replace)); rewind(); return *this; }
 string operator() ( int start, int count ) {
  return value.substr( start, count );
 }
 void rTrim(const string& delimiters = " \f\n\r\t\v") {
  rtrim(value,delimiters);
  rewind();
 }
 void lTrim(const string& delimiters = " \f\n\r\t\v") {
  ltrim(value,delimiters);
  rewind();
 }
 void Trim(const string& delimiters = " \f\n\r\t\v") {
  trim(value,delimiters);
  rewind();
 }
 bool begins(const char *s) {
  int len=(int)strlen(s);
  if ( len > (int) value.length() ) return false;
  const char *p=value.c_str();
  const char *q=s;
  for ( int i=0; i<len; i++,p++,q++ ) if ( LOWER(*p) != LOWER(*q) ) return false;
  return true;
 }
};

inline bool operator==( const Zstring& a, const Zstring& b );
inline bool operator==( const Zstring& a, const char *b );
inline bool operator==( const char *b , const Zstring& a );
inline bool operator!=( const Zstring& a, const Zstring& b );
inline bool operator!=( const Zstring& a, const char *b );
inline bool operator!=( const char *b , const Zstring& a );
inline string operator+ ( const Zstring& a, const Zstring& b );
inline string operator+ ( const Zstring& a, const string& b );
inline string operator+ ( const string& a, const Zstring& b );
inline string operator+ ( const Zstring& a, const int& b );
inline string operator+ ( const Zstring& a, const unsigned int& b );
inline string operator+ ( const Zstring& a, const float& b );
inline string operator+ ( const Zstring& a, const double& b );
inline string operator+ ( const int& a, const Zstring& b );
inline string operator+ ( const unsigned int& a, const Zstring& b );
inline string operator+ ( const float& a, const Zstring& b );
inline string operator+ ( const double& a, const Zstring& b );
inline string operator+ ( string a, Zint& b );
inline string operator+ ( string a, Zuint& b );
inline string operator+ ( string a, Zfloat& b );
inline string operator+ ( string a, Zdouble& b );
/* Creates C2593
string operator+ ( Zint& a, string b );
string operator+ ( Zuint& a, string b );
string operator+ ( Zfloat& a, string b );
string operator+ ( Zdouble& a, string b );
*/
inline int operator+ ( Zint& a, Zint& b );
inline float operator+ ( Zfloat& a, Zfloat& b );
inline double operator+ ( Zdouble& a, Zdouble& b );
inline string operator+ ( const Zstring& a, char c );
inline string operator+ ( char c, const Zstring& a );
inline string operator- ( const Zstring& a, const Zstring& b );
inline string operator- ( const Zstring& a, const string& b );
inline string operator- ( const string& b, const Zstring& a );
inline string operator- ( const Zstring& a, const char *b );
//string operator- ( const char *b, const Zstring& a );
inline string operator/ ( const Zstring& a, const Zstring& b );
inline string operator/ ( const Zstring& a, const string& b );
inline string operator/ ( const string& b, const Zstring& a );
inline string operator/ ( const Zstring& a, const char *b );
inline string operator/ ( const char *b, const Zstring& a );
inline string operator* ( const Zstring& a, unsigned int i );
inline int operator* ( const Zstring& a, string b );
inline int operator* ( string a, const Zstring& b );
inline int operator* ( const Zstring& a, const char *B );
inline int operator* ( const Zstring& a, const Zstring& b );
	   
/// Zstring ///////////////////////////////////////////////////////////////////////////////////////// end

// Random Number Stuff, needed for lists to return random elements

inline void init_seeder(void); // called by InitZeroTypesLibrary();
inline void reseed(void);
inline double uniform (void);
inline double uniform ( bool reseed );
#define PSEUDORAND_MAX 0x7fff
inline int zpseudorandom( unsigned int s, unsigned int x );
inline double zrandom(double x);
inline int iround ( float f );
inline int iround ( double d );
inline int ilerp( int start, int end, float percent );
inline int ilerpw( int start, int end, float percent );
inline int ilerp( int start, int end, double percent );
inline int ilerpw( int start, int end, double percent );
inline double double_range( double L, double H );
inline float float_range( float L, float H );
inline int number_range( int L, int H );
inline int upto( int M );
inline int upto( int M, int seed );
inline float Gauss();

//////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ListItem and LinkedList

#define CLONE(single,code) single *Duplicate() { single *a=new single; {code} return a; }
#define DUPE(membername) {a->membername=membername;}
#define DUPELIST(membername,membername_single) { EACH(membername->first,membername_single,b) a->membername->Append(b->Duplicate()); }
#define DUPESLIST(membername,membername_single) { EACH(membername.first,membername_single,b) a->membername.Append(b->Duplicate()); }

class ListItem {
public:
 Zint leashes,rtid;
 ListItem *next;
 ListItem *prev;
 ListItem(void) { next=prev=null; }
 virtual ~ListItem() {} // Source: Meyers Effective C++, removed due to vile reprocussions, then re-added due to complaints.
 virtual void Virtual(void) {}
 virtual string identity() { ///RTTI///
  string classname=typeid(*this).name();
  string discard;
  const char *q=string_argument(classname.c_str(),&discard); // discards the words "class or struct"
  return string(q);
 }
 virtual bool is( const char *classnamed ) {
  string id=identity();
  return ( !str_cmp(id.c_str(),classnamed) );
 }
 // Note: there is a bug in MSVC2010EE here that makes the following 'virtual' cause the linker to bust.
 /* virtual */ void fromString( const char *st ) {
  string c=identity();
  OUTPUT("ListItem: fromString() called on base class (RTTI class was: %s).\n",c.c_str());
 }
 virtual string toString() {
  return identity()+string(" default virtual toString");
 }
 //virtual void BinaryRead( BinaryFile *open ) {} // read data from an already open binary file (ifstream method)
 //virtual void BinaryWrite( BinaryFile *open ) {} // write the data to an already open binary file (ifstream method)
 //virtual void KeyedRead( KeyedDataStore *open ) {}
 //virtual void KeyedWrite( KeyedDataStore *open ) {}
 bool isAfter( ListItem *I ) {
  ListItem *c=I;
  while ( c ) {
   c=c->next;
   if ( c==this ) return true;
  }
  return false;
 }
 bool isBefore( ListItem *I ) {
  ListItem *c=I;
  while ( c ) {
   c=c->prev;
   if ( c==this ) return true;
  }
  return false;
 }
};


#define CLONES(single,plural) void Duplicate( plural *in ) { EACH(in->first,single,s) Append(s->Duplicate()); }

// Unfortunately, the following macro does not work. See COLLECTION() as a legacy example of the root of this ONE-MANY-DONE concept.
//#define PLURAL(single,plural,definition) class plural : public LinkedList { public: CLEARLISTRESET(single); definition };
// So, we're going to use triplets instead.

// MSVC 2015 NOTE:  Sometimes the linter will incorrectly lint the MANY() _MANY() PLURAL() and related clauses with "Expected a declaration"  This usually goes away eventually, however it may indicate a problem in the cpp related to the collection class


// These are just renamings of the of the referenced ones below.
// Anonymous   
#define _ONE(type_name,code1)        SINGLE(type_name,code1)    
#define _MANY(single,plural,code2)   PLURAL(single,plural,code2)
#define _DONE(type_name)             ENDSET(type_name)          
// Named (usually preferred)
#define ONE(type_name,code1)                                           SINGLE_NAMED(type_name,code1)
#define MANY(single,singleHandle,singleHandles,keyname,plural,code2)   PLURAL_NAMED(single,singleHandle,singleHandles,keyname,plural,code2)
#define DONE(type_name)                                                ENDSET_NAMED(type_name)    

#define ZMANY(single,plural,code2,keyname) MANY(single,single##Handle,single##Handles,keyname,plural,code2)

#define VERYMANY(single,singleHandle,singleHandles,singleHandlesHandle,singleHandlesHandles,keyname,plural,code2)  \
 ENDITEM(single); HANDLES(single,singleHandle,singleHandles,keyname); \
 HANDLEHANDLES(singleHandles,singleHandlesHandle,singleHandlesHandles,keyname); \
 LIST(plural,code2) single *named(const char *k) { FOREACH(single,s) if ( !str_cmp(s->name.c_str(),k) ) return s; return null; } single *firstNamed( const char *k ) { FOREACH(single,s) if ( s->name.inside(k) ) return s; return null; } void nameSearch( singleHandles *out, const char *k ) { FOREACH(single,s) if ( s->name.inside(k) ) out->Add(s); } void nameMatches( singleHandles *out, const char *k ) { FOREACH(single,s) if ( !str_cmp(k,s->name.c_str()) ) out->Add(s); } void nameGroup( singleHandles *out, const char *k ) { FOREACH(single,s) if ( s->name.begins(k) ) out->Add(s); }
// Add Zint id; after ONE(), after MANY() use this to generate NextID
#define AUTOKEY(single) int GetNextAvailableID() { int next_id=0; bool found=true; while ( found ) { next_id++; found=false; FOREACH(single,p) if ( p->id == next_id ) { found=true; break; } } return next_id; } single *GetByID( int id ) { FOREACH(single,s) if ( s->id == id ) return s; return null; }
#define ADDAPPEND(single) single *Add() { single *p=new single; p->id=GetNextAvailableID(); Append(p); return p; }
#define DROPHANDLED(single,handle,handles) void Drop( handles *in ) { EACH(in->first,handle,h) { Remove(h->p); delete h->p; } in->Clear(); }
// For childs of ListItem
#define C_ONE(type_name,child,code1) CSINGLE(type_name,child,code1)    
// Childs named (usually preferred)
#define CONEN(type_name,child,code1) CSINGLE_NAMED(type_name,child,code1)    

// Indexed by id (not sorted)
#define IONE(type_name,code1)                                           SINGLE_NAMED(type_name,code1) Zint id;
#define IMANY(single,singleHandle,singleHandles,keyname,plural,code2)   PLURAL_NAMED(single,singleHandle,singleHandles,keyname,plural,code2) AUTOKEY(single); ADDAPPEND(single); KEYWORDSGroup(keyname,single); WORDKEYSGroup(keyname,single); DROPHANDLED(single,singleHandle,singleHandles);
#define IDONE(type_name)                                                ENDSET_NAMED(type_name)    

// Instead of using a template, use these macros to quickly define 'blocks' of one-and-many collection code.
// One
#define ITEM(type_name,code1)  class type_name : public ListItem { public: type_name() : ListItem() { {code1} }
#define ENDITEM(type_name)     };
// Many
#define LIST(type_name,code1)  class type_name : public LinkedList { public: type_name() : LinkedList() { {code1} }
#define ENDLIST(type_name)     CLEARLISTRESET(type_name) };
// Custom Child of One
#define CITEM(type_name,child,code1)  class type_name : public child { public: type_name() : child() { {code1} }
#define CENDITEM(type_name)     };
// One-Many-Done structure
#define SINGLE(type_name,code1)     ITEM(type_name,code1)
#define PLURAL(single,plural,code2) ENDITEM(single); LIST(plural,code2)
#define ENDSET(type_name)           ENDLIST(type_name)
// You can use the following to create a named instance instead of an anonymous instance (default) which is searchable by some default properties.
#define SINGLE_NAMED(type_name,code1)      ITEM(type_name,code1) Zstring name; type_name( const char *n ) { name=n; {code1} } 
#define PLURAL_NAMED(single,singleHandle,singleHandles,keyname,plural,code2)  ENDITEM(single); HANDLES(single,singleHandle,singleHandles,keyname); LIST(plural,code2) single *named(const char *k) { FOREACH(single,s) if ( !str_cmp(s->name.c_str(),k) ) return s; return null; } single *firstNamed( const char *k ) { FOREACH(single,s) if ( s->name.inside(k) ) return s; return null; } void nameSearch( singleHandles *out, const char *k ) { FOREACH(single,s) if ( s->name.inside(k) ) out->Add(s); } void nameMatches( singleHandles *out, const char *k ) { FOREACH(single,s) if ( !str_cmp(k,s->name.c_str()) ) out->Add(s); } void nameGroup( singleHandles *out, const char *k ) { FOREACH(single,s) if ( s->name.begins(k) ) out->Add(s); }
#define ENDSET_NAMED(type_name)            ENDLIST(type_name)
// No default constructor
#define _ONE_(type_name)       SINGLE_(type_name) 
#define ITEM_(type_name)  class type_name : public ListItem { public: 
#define SINGLE_(type_name)     ITEM_(type_name)

// These are used to expedite override of fromString() code, WORD and TAG are strung together with elses
#define KEYWORDS(code)                  void fromString( const char *s, const char *path_prefix="" ) { OUTPUT("in[%s] ",(typeid(*this).name()) ); Zstring _in(s); const char *w=_in.Next(); while ( *w != '\0' ) { {code} NEXTWORD } }
#define NEXTWORD w=_in.Next();
#define KEYWORD(constcharstring,code)   if ( !str_cmp(w,constcharstring) ) { NEXTWORD {code} }
#define SUBWORDdis(constcharstring,zdis) KEYWORD(constcharstring,{zdis.Recycle(); zdis->fromString(w);})
#define SUBWORD(constcharstring,object)  KEYWORD(constcharstring,{object.fromString(w);})
#define SSUBWORD(constcharstring,object) KEYWORD(constcharstring,{object.fromString(w);})
#define KEYTAG(constcharstring,code)    if ( !str_cmp(w,constcharstring) ) {code}
#define TAGWORD(constcharstring,zbool)   KEYTAG(constcharstring,{zbool=true;})
#define NUMWORD(constcharstring,zvalue)  KEYWORD(constcharstring,{zvalue=w;})
#define TXTWORD(constcharstring,zvalue)  KEYWORD(constcharstring,{zvalue=b64k_decode(w);})
#define ENUMWORD(constcharstring,value,type)   KEYWORD(constcharstring,{value=(type)atoi(w);})
#define SUBFILE(constcharstring,object)  KEYWORD(constcharstring,{string fs=file_as_string(w);object.fromString(fs.c_str());})
#define KEYWORDS_INCLUDE(filenam3,staticclassvar) { OUTPUT("<--Loading file:`%s`---\n",filenam3);  string f=file_as_string(filenam3); staticclassvar.fromString(f.c_str()); }
#define KEYWORDS_PATH_INCLUDE(pathnam3,staticclassvar) { OUTPUT("<--Loading all files from path:`%s`---\n",pathnam3); Strings *list=ls(pathnam3,true,true,true); if ( !list ) return; EACH(list->first,String,s) KEYWORDS_INCLUDE(s->s.c_str(),staticclassvar); delete list; }
// Same as above but lets you put some code for post processing after the key-scanning loop
#define KEYWORDS_POST(code,post) void fromString( const char *s, const char *path_prefix="" ) { OUTPUT("in[%s] ",(typeid(*this).name()) ); Zstring _in(s); const char *w=_in.Next(); while ( *w != '\0' ) { {code} /* do not call NEXTWORD to support KEYWORDS_INCLUDE, call manually */ } {post} }
#define BADKEY(t)                       { OUTPUT("\n>< %s:fromString() Bad keyword `%s`, advancing to next\n",t,w); }
#define BADKEYWORD                      { OUTPUT("\n>< Bad keyword `%s`, advancing to next\n",w); }
// Just some aliases
#define WORD(constcharstring,code) KEYWORD(constcharstring,code)
#define TAG(constcharstring,code)  KEYTAG(constcharstring,code)

// Now for toString() code
#define WORDKEYS(code)                  string toString( const char *path_prefix="" ) { OUTPUT("out[%s] ",(typeid(*this).name()) ); Zstring _out; {code} return _out.value; }
#define WORDKEY(constcharstring,value)  { _out+=constcharstring+string(" {")+value+string("}\n"); }
#define TXTKEY(constcharstring,value)   { if ( strlen(value.c_str()) > 0 ) { _out+=constcharstring+string(" {")+b64k_encode(value.c_str())+string("}\n"); } }
#define NUMBKEY(constcharstring,value)  { _out+=constcharstring+string(" {")+value.toString()+string("}\n"); }
#define ENUMKEY(constcharstring,value)  { _out+=constcharstring+FMT(" %d",(int)value)+string("\n"); }
#define TAGKEY(constcharstring,value)   { if ( value ) _out+=constcharstring+string("\n"); }
#define SUBKEY(constcharstring,object)  { _out+=constcharstring+string(" {")+object->toString()+string("}\n"); }
#define SUBKEYCustom(constcharstring,object,call) { _out+=constcharstring+string(" {")+object->call()+string("}\n"); }
#define SSUBKEY(constcharstring,object) { _out+=constcharstring+string(" {")+object.toString()+string("}\n"); }
#define SSUBKEYCustom(constcharstring,object,call) { _out+=constcharstring+string(" {")+object.call()+string("}\n"); }
#define SUBSETKEY(constcharstring,set,handle) { Zstring subset; EACH(set.first,handle,s) subset+=s->SingleKey()+string(" {")+s->p->toString()+string("}\n"); _out+=constcharstring+string(" {")+subset+string("}\n"); }
#define SUBSETFILE(filenam3,set,handle) { OUTPUT("---Saving file:`%s`-->\n",filenam3); Zstring subset; EACH(set.first,handle,s) subset+=s->SingleKey()+string(" {")+s->p->toString()+string("}\n"); string_as_file(subset.c_str(),filenam3); }
#define SUBSETPATH(pathnam3,prefix,postfix,set,handle) { OUTPUT("---Saving files to path:`%s`-->\n",pathnam3); Zstring subset; Zstring filenam3; int fi=0; EACH(set.first,handle,s) { fi++; subset=s->SingleKey()+string(" {")+s->p->toString()+string("}\n"); filenam3=string(pathnam3)+string(prefix)+I2S(fi)+string(postfix); string_as_file(subset.c_str(),filenam3.c_str()); } }

// Same as above but let you provide a name for the function instead of the default toString and fromString
#define NKEYWORDS(fun,code) void fun( const char *s ) { Zstring in(s); const char *w=in.c_str(); while ( *w != '\0' ) { {code} NEXTWORD } }
#define NWORDKEYS(fun,code) string fun() { Zstring _out; {code} return _out.value; }

#define KEYWORDSGroup(keyname,type) void fromString( const char *s ) { OUTPUT("in<<%s<< ",(typeid(*this).name()) ); int loaded=0; Zstring in(s); const char*w=in.Next(); while ( *w != '\0' ) { if ( !str_cmp(w,keyname) ) { w=in.Next(); type *k=new type; k->fromString(w); Append(k); loaded++; } w=in.Next(); OUTPUT(" < Loaded %d %s\n",loaded,keyname ); } }
#define WORDKEYSGroup(keyname,type) string toString() { OUTPUT("out>>%s>> ",(typeid(*this).name()) ); string out=string("\n"); FOREACH(type,k) out+=keyname+string(" {")+k->toString()+string("}\n"); OUTPUT(" > Saved %d %s\n",count.value,keyname ); return out; }
#define KEYSWORDSGroups(keyname,type) KEYWORDSGroup(keyname,type) WORDKEYSGroup(keyname,type)

// These macros do not work due to problems with Parent->Child virtuals not being called...
//#define SORTABLE(single,code) int Compare( ListItem *a, ListItem *b ) { single *A=(single *)a; single *B=(single *)b; int result=0; {code} return result; }
//#define COMPARABLE(single,code,comparator) int Compare( ListItem *a, ListItem *b, void *value ) { single *A=(single *)a; single *B=(single *)b; comparator *comparing=(comparator *)value; int result=0; {code} return result; }
// The below macro works, because it implements the function on the list.  Better because you can have multiple sorts on the same list.
// Use in the following way:  SORTING(NameOfSort,{/*precomputation*/},{}
#define SORTING(single,SortName,precomputation,compare_neg1_means_earlier,postcomputation)   void SortName() {                    \
  {precomputation}                    \
  if ( count < 2 ) return;            \
  LinkedList list;                    \
  list.first=first; first=null;       \
  list.last=last; last=null;          \
  list.count=count; count=0;          \
  ListItem *q=list.first;             \
  list.Remove(q);                     \
  Append(q);                          \
  while(list.first) {                 \
   ListItem *a=list.first;            \
   list.Remove(a);                    \
   bool inserted=false;               \
   EACH(this->first,ListItem,b) {     \
    int result=0;                     \
    single *A=(single *)a;            \
    single *B=(single *)b;            \
    {compare_neg1_means_earlier}      \
    if ( result < 0 ) {               \
     this->InsertBefore(a,b);         \
     inserted=true;                   \
     break;                           \
    }                                 \
   }                                  \
   if ( !inserted ) Append(a);        \
  }                                   \
  {postcomputation}                   } 


// Class template:
// SINGLE_NAMED();
// PLURAL_NAMED();
// ENDSET_NAMED();
// results in NAMED() class instantiator, which does not work due to C++ language constraints.
// evidence: #define NAMED(single,construct1,class1,plural,construct2,class2) SINGLE_NAMED(single,construct1); class1 PLURAL_NAMED(single,plural,construct2); class2 ENDSET_NAMED(single);

// This version permits a child:
#define CSINGLE(type_name,child,code1)       CITEM(type_name,child,code1)
// For named searchable lists:
#define CSINGLE_NAMED(type_name,child,code1) CITEM(type_name,child,code1) Zstring name; type_name( const char *n ) { name=n; code1 } 

// Example usage and base override:
// SINGLE(single,{});          (put methods,etc relevant to a single element here)
// PLURAL(single,plural,{});   (put methods,etc relevant to the group here)
// ENDSET(plural);             (ends the section)
// HANDLED(single,...          (extension functions for creation secondary reference, auto generates code for you)
// HANDLED(plural,...          (" ")

#define CLEARLIST(t)   void Clear() { \
   t *n; for ( t *p=(t *) first; p; p=n ) { \
    n=(t *)(p->next); delete p; \
   } \
  }
#define CLEARLISTRESET(t)   void Clear() { \
   t *n; for ( t *p=(t *) first; p; p=n ) { \
    n=(t *)(p->next); delete p; \
   } \
   first=null; last=null; count=0; \
  }
#define ADDLIST(t,r,h)  void Add( t *p ) { h *s= new h(); s->r=p; Append(s); }
#define ADDLISTNAMED(a,t,r,h) void Add( t *p ) { h *s= new h(); s->r=p; s->name=a; Append(s); }
#define FOREACH(t,v)  for ( t *v=(t *) first; v; v=(t *) v->next )
/* Will not work: ??? */
#define FOREACHN(t,v,c) { t *n; for ( t *v=(t *) first; v; v=n ) { n=(t *) v->next; {c} } }
#define FOREACHREV(t,v) for ( t *v=(t *) last; v; v=(t *) v->prev )
#define EACH(head,t,v)  for ( t *v=(t *) head; v; v=(t *) v->next )
#define EACHREV(last,t,v)  for ( t *v=(t *) last; v; v=(t *) v->prev )
#define EACHN(head,t,v,c) { t *n; for ( t *v=(t *) head; v; v=n ) { n=(t *) v->next; {c} } }
#define EACHPAIR(head1,t,v,head2,tt,v2,c)  { t *v=(t *) head1; tt *v2=(tt *)head2; \
 while ( v && v2 ) { \
 {c} \
 v=(t *)v->next; v2=(tt *)v2->next; \
 } }

/* Does not work: */
//#define EACH2(head,t,v,head2,t2,v2,c)  { t *v=(t *) head; t2 *v2=(t2 *)head2; while ( v && v2 ) { c { v=(t *)v->next; v2=(t2 *)v2->next ); } }; }

// These macros are the way to make all objects in a list call the same simple function, such as Between() or Render() or Init() etc.
#define CALLEACH(single,function) void function() { FOREACH(single,s) s->function(); }
#define CALLEACH1(single,function,code_after) void function() { FOREACH(single,s) { s->function(); } code_after }
#define CALLEACH2(single,function,code_each) void function() { FOREACH(single,s) { s->function(); code_each } }
#define CALLEACH3(single,function,code_each,code_after) void function() { FOREACH(single,s) { s->function(); code_each } code_after }
#define CALLEACH4(single,_prototype,_call,code_after) void _prototype { FOREACH(single,s) { _call } code_after }

// These macros do the same as above but preserve the 'next' pointer so that the object can be removed from the list in-transit.
#define CALLEACHN(single,function) void function() { FOREACHN(single,s) s->function(); }
#define CALLEACHN1(single,function,code_after) void function() { FOREACHN(single,s) { s->function(); } code_after }
#define CALLEACHN2(single,function,code_each) void function() { FOREACHN(single,s) { s->function(); code_each } }
#define CALLEACHN3(single,function,code_each,code_after) void function() { FOREACHN(single,s) { s->function(); code_each } code_after }
#define CALLEACHN4(single,_prototype,_call,code_after) void _prototype { FOREACHN(single,s) { _call } code_after }

// Specialized versions of callback used in the scripting language (see references)
#define RENDERLIST(ts,t) class ts : public LinkedList { public: CLEARLISTRESET(t); void Render( GLWindow *surface ) { FOREACH(t,g) g->Render(surface); } void Between() { FOREACH(t,g) g->Between(); } };
#define RENDERLIST2(t) RENDERLIST(ts,t);

// Legacy version of the ONE MANY DONE concept.
#define COLLECTION(t,i) class t : public LinkedList { public: CLEARLISTRESET(i); }

// Allows you to define a simple customized sort method for a collection. // Old Style: Use SORTING() now.
#define LL_SORTER(sort,plural,single,compare) \
 void sort() { \
  if ( count < 2 ) return; \
  plural list; list.first=first; list.last=last; list.count=count; \
  single *q=(single *) list.first; list.Remove(q); Append(q); \
  while(list.first) { \
   single *p=(single *) list.first; list.Remove(p); \
   bool inserted=false; \
   EACH(this->first,single,t) { \
    int result=this->compare(p,t); \
    if ( result <= 0 ) { \
     this->InsertBefore(p,t); inserted=true; break; \
    } \
   } \
   if ( !inserted ) Append(p); \
  } \
 }

class LinkedList : public ListItem {
public:
 Zint count;
 ListItem *first;
 ListItem *last;

 LinkedList(void) : ListItem() { first=last=null; }

 //virtual void BinaryRead( BinaryFile *open ); // default works in most cases
 //virtual void BinaryWriteData( BinaryFile *open ) {}
 //virtual void BinaryReadData( BinaryFile *open ) {}
 //virtual void ReadAppend( BinaryFile *open ) {}
 //virtual void BinaryWrite( BinaryFile *open ); // default works in most cases

 virtual string identity() { ///RTTI///
  string classname=string(typeid(*this).name());
  string discard;
  const char *q=string_argument((char *)classname.c_str(),&discard); // discards the words "class or struct"
  return string(q);
 }
 virtual string identity( bool useChar ) { ///RTTI///
  const char *classname=typeid(*this).name();
  string discard;
  const char *q=string_argument(classname,&discard); // discards the words "class or struct"
  return string(q);
 }
 bool ListIteminList( ListItem *item ) {
  FOREACH(ListItem,i) if ( i==item ) return true;
  return false;
 }
 void sendBack(ListItem *L) { if ( !L->prev ) return; Remove(L); Prepend(L); }
 void sendFront(ListItem *L) { if ( !L->next ) return; Remove(L); Append(L); }
 void sendUp(ListItem *L, bool wrap=true);
 void sendDown(ListItem *L, bool wrap=true);
 virtual void Append(ListItem *L);
 void _Append(ListItem *L);
 void Prepend(ListItem *L);
 ListItem *Element(int i);
 ListItem *Element(int i, bool wrap);
 int Element(ListItem *item);
 virtual ListItem *Any() {
  if ( count==0 ) return null;
  if ( count==1 ) return first;
  return Element(upto((int)count*1234)%count.value);
 }
 virtual ListItem *Any( int seed );
 // Returns i==count on failure to find, use ListIteminList()
 int IndexOf( ListItem *L ) { int i=0; FOREACH(ListItem,item) { if ( item == L ) break; i++; } return i; }
 void InsertBefore(ListItem *insert,ListItem *before);
 void InsertAfter(ListItem *insert, ListItem *after);
 void InsertAt(ListItem *insert, int i);
 void _Remove(ListItem *L);
 void Remove(ListItem *L) { _Remove(L); }
 void RemoveAll(void);
 ListItem *ReplaceListItem(ListItem *L,ListItem *N) {
  N->prev=L->prev;
  N->next=L->next;
  if ( N->prev ) N->prev->next=N;
  if ( N->next ) N->next->prev=N;
  L->next=null;
  L->prev=null;
  delete L;
  return N;
 }
 void Delete(ListItem *L);
 void Delete(ListItem **L);
 void AppendAndDispose( LinkedList *toAppend ) {
  Concat(toAppend);
  delete toAppend;
 }
 //void DeleteAll(void);//never, use CLEARLIST(class) macro

 void RandomizeOrder();
 void RandomizeOrder(int seed);
 void ReverseOrder() {
  LinkedList temporary;
  EACHN(first,ListItem,L,{
   Remove(L);
  temporary.Prepend(L);
   });
  this->first=temporary.first;
  this->last=temporary.last;
  this->count=temporary.count;
  temporary.first=temporary.last=NULL;
  temporary.count=0;
 }
 // Moves L to current list, empties L
 void Concat( LinkedList *L ) {
  if ( L->count <= 0 ) return;
  if ( count == 0 ) {
   count=L->count;
   first=L->first;
   last=L->last;
  } else {
   count+=L->count;
   last->next=L->first;
   L->first->prev=last;
   last=L->last;
  }
  L->first=null;
  L->last=null;
  L->count=0;
 }

 virtual void Clear() {
  //#if defined(DEBUG)
  if ( first ) EACHN(first,ListItem,L,{
   Remove(L);
  delete L;
   });
  count=0;
  last=first=null;
  //#endif
 }
 virtual ~LinkedList() { 
  Clear();
 }
};

/// HANDLES, lists of specialty classes that point to list items of specific classes ONE..MANY..DONE automatically creates these ///

// Internal unnamed handles
#define HANDLING(single,handle,singlekey) \
 class handle:public ListItem{public: \
  Zp<single> p; \
  handle():ListItem() { } \
  void fromString(char *st) { \
   p.Delete(); \
   p=new single; \
   p->fromString(st); \
  } \
  std::string SingleKey() { return string(singlekey); }\
  virtual string toString() { \
   if(p) return p->toString(); \
   else return string(""); \
  } \
 };

#define HANDLINGS(single,handle,handles,singlekey) \
 class handles:public LinkedList{public: \
  virtual handle*Add(single*q) { \
   handle*n=new handle; \
   n->p=q; \
   Append(n); \
   return n; \
  } \
  virtual handle*Add(single*q,handle *after) { \
   handle*n=new handle; \
   n->p=q; \
   InsertAfter(n,after); \
   return n; \
  } \
  single *find(single *q) { FOREACH(handle,s) if ( s->p==q ) return s->p; return null; } \
  handle *find(single *q, having returnHandle) { FOREACH(handle,s) if ( s->p==q ) return s; return null; } \
  std::string SingleKey() { return std::string(singlekey); }\
  bool Includes(single *q) { FOREACH(handle,s) if ( s->p==q ) return true; return false; } \
  void Delete(single*r){ FOREACH(handle,n) if(n->p==r){ Remove(n);delete n;return;} } \
  void Drop(single*r){ FOREACH(handle,n) if(n->p==r){ Remove(n);delete n;return;} } \
  CLEARLISTRESET(handle); \
 };
// \ // needs a fix on mac SKEYSTART SKEY(singlekey,{SPARAMNode(single);}) SKEYEND(identity(true)); \

// Mega-handle without names
#define HANDLED(single,handle,handles,handleshandle,handleshandles) \
 class handles; class handleshandle; class handleshandles; \
 class handle:public ListItem{ public:\
  Zp<single> p; \
  Zp<handles> parent; \
  virtual void fromString(char *st) { p->fromString(st); } \
  virtual void fromString(string k) { p->fromString((char*)k.c_str()); } \
  virtual string toString() { return p->toString(); } \
 }; \
 class handles:public LinkedList{ public:\
  virtual handle*Add(single*q) {\
   handle*n=new handle; \
   n->p=q; \
   n->parent=this; \
   Append(n); \
   return n; \
  } \
  virtual handle*Add(single*q,handle *after) {\
   handle*n=new handle; \
   n->p=q; \
   n->parent=this; \
   InsertAfter(n,after); \
   return n; \
  } \
  single *find(single *q) { FOREACH(handle,s) if ( s->p==q ) return s->p; return null; } \
  handle *find(single *q,bool returnHandle) { FOREACH(handle,s) if ( s->p==q ) return s; return null; } \
  bool Includes(single *q) { FOREACH(handle,s) if ( s->p==q ) return true; return false; } \
  void Delete(single*r){ FOREACH(handle,n) if(n->p==r){Remove(n);delete n;return;} } \
  void Drop(single*r){ FOREACH(handle,n) if(n->p==r){Remove(n);delete n;return;} } \
  CLEARLISTRESET(handle); \
  ~handles(){Clear();} \
 }; \
 class handleshandle:public ListItem{ public:\
  Zp<handles> p; \
  Zp<handleshandles> parent; \
 }; \
 class handleshandles:public LinkedList{ public: \
  handleshandle*Add(handles*q){ \
   handleshandle*n=new handleshandle; \
   n->p=q; \
   n->parent=this; \
   Append(n); \
   return n; \
  } \
  handles *find(handles *q) { FOREACH(handleshandle,s) if ( s->p==q ) return s->p; return null; } \
  handles *find(handles *q,bool returnHandle) { FOREACH(handleshandle,s) if ( s->p==q ) return s; return null; } \
  void Delete(handles *r) { FOREACH(handleshandle,s)if(s->p==r){Remove(s);delete s;return;} } \
  void Drop(handles *r) { FOREACH(handleshandle,s)if(s->p==r){Remove(s);delete s;return;} } \
  CLEARLISTRESET(handleshandle); \
  ~handleshandles(){Clear();} \
 };

// Class Name, Class Handle Class Name, Plural Handle Class Name, Plural Plural Handles Class Name
#define HANDLES(single,handle,handles,singlekey) HANDLING(single,handle,singlekey) HANDLINGS(single,handle,handles,singlekey);
#define HANDLEHANDLES(single,handle,handles,singlekey) HANDLES(single,handle,handles,singlekey);

// Defines classes under a named handle
#define NAMED(single,handle,handles) \
 class handles; \
 class handle:public ListItem{ public: \
  Zstring name; \
  Zp<single> p; \
  Zp<handles> parent; \
 }; \
 class handles:public LinkedList{ public: \
 virtual handle*Add(single*q,string m) { \
  handle*n=new handle; \
  n->name=m; \
  n->p=q; \
  n->parent=this; \
  Append(n); \
  return n; \
 } \
 handle*find(string k){ \
  FOREACH(handle,n) if(!str_cmp((char*)n->name.c_str(),(char*)k.c_str())) return n; \
  return null; \
 } \
 void Delete(single*r){ \
  FOREACH(handle,n) if(n->p==r){Remove(n);delete n;return;} \
 } \
 CLEARLISTRESET(handle); \
 ~handles(){Clear();} \
 };

// Generic Handle
HANDLES(ListItem,ListItemHandle,ListItemHandles,"ListItem");

// Optimization for real-time type information
#define RONE(type_name,rtid_code,code1)   SINGLE_NAMED(type_name,{ rtid=rtid_code; code1 })
#define RC_ONE(type_name,rtid_code,childof,code1) C_ONE(type_name,childof,{ rtid=rtid_code; code1})

//////////////////////////////////////////////////////////////////////// End ListItem / LinkedList

//////////////////////////////////////////////////////////////////////// String/Strings collection class

inline string UnStringSpecialCodes( string k );
inline string StringSpecialCodes( string k );

#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include <string>
using namespace std;

class String : public ListItem {
public:
 string s;
 int integer;
 float floating;
 char c;
 String() : ListItem() {
  s = string("");
  integer=0;
  floating=0.0f;
  c='\0';
 } 
 String( const char *i ) : ListItem() {
  s=string(i);
  integer=0;
  floating=0.0f;
  c='\0';
 }
 String( string i ) : ListItem() {
  s=i;
  integer=0;
  floating=0.0f;
  c='\0';
 }
 String( string i, bool UsesSpecialCodes ) : ListItem() {
  s = UnStringSpecialCodes(i);
  integer=0;
  floating=0.0f;
  c='\0';
 }
 String( String *t ) : ListItem() {
  s=t->s;
  integer=t->integer;
  floating=t->floating;
  c='\0';
 }
 String *Duplicate() { return new String(this); }
 String( const char *k, int i ) {
  integer=i;
  s = string(k);
  prev=next=nullptr;
 }
 const char *c_str(void); // converts the node to a C-str
 virtual ListItem *Copy() {
  return (ListItem *) new String( this );
 }
 virtual void fromString( const char *s ) {
  string key; const char *p= s;
  bool carryover = false;
  while(*p!='\0') {
   if (carryover) carryover = false;
   else p=string_argument_case(p,&key);
   if ( key.length() < 1 ) continue; 
   this->s=UnStringSpecialCodes(key);
   p=string_argument_case(p,&key); 
   if ( is_integer((char *) key.c_str()) ) {
    integer=atoi(key.c_str());
    p=string_argument_case(p,&key); 
   } else if ( is_decimal((char *) key.c_str()) ) {
    floating=(float)atof(key.c_str());
   } else carryover = true;
   if ( is_decimal((char *) key.c_str()) ) {
    floating=(float)atof(key.c_str());
    p=string_argument_case(p,&key); 
   } else carryover = true;
  }
 }
 virtual string toString() {
  string out=string("");
  out+=indention()+string("{")+StringSpecialCodes(this->s)+string("}");
  if ( integer != 0 ) {
   char buf[80];
   FMT(buf,80," %d",(int) integer);
   out+=string(buf);
  }
  if ( floating != 0.0f ) {
   char buf[80];
   FMT(buf,80," %1.9f",(float) floating);
   out+=string(buf);
  }
  return out;
 }
};

class KeyValuePair : public String {
public:
 virtual string toString() {
  return string("{")+s+string("} \"")+value+string("\"");
 }
 string value;
 KeyValuePair() {
  s = string("");
  value = string("");
  prev=next=null;
 }
 KeyValuePair( KeyValuePair *t ) {
  prev=next=null;
  s=t->s;
  integer=t->integer;
  floating=t->floating;
  value=t->value;
 }
 KeyValuePair( const char *k, const char *v ) {
  s = string(k);
  value = string(v);
  prev=next=null;
 }
 KeyValuePair( const char *k, int i ) {
  static char buf[1024];
  integer=i;
  s = string(k);
  FMT( buf,1024, "%d", (int) i );
  value=string(buf);
  prev=next=null;
 }
 KeyValuePair( const char *k, float f ) {
  static char buf[1024];
  floating =f;
  s = string(k);
  FMT( buf,1024,  "%f", (float) f );
  value=string(buf);
  prev=next=null;
 }
 void Set( int i ) {  
  static char buf[1024];
  integer=i;
  FMT( buf,1024, "%d", (int) i );
  value=string(buf);
 }
 void Set( float f ) {  
  static char buf[1024];
  floating =f;
  FMT( buf,1024,  "%f", (float) f );
  value=string(buf);
 }
 void Set( const char *v ) {
  value=string(v);
 }
 void Set( const char *k, const char *v ) {
  s=string(k);
  value=string(v);
 }
 virtual ListItem *Copy() {
  return new KeyValuePair( this );
 }
};

#ifndef va_start
#include <varargs.h>
#endif

const char *string_error() {
	static const char _string_error = '\0';
	return &_string_error;
}

class Strings : public LinkedList {
public:
 void DuplicateAsStrings( Strings *out ) {
  FOREACH(String,x) out->Add(x->c_str(),x->integer,x->floating);
 }
 // Populate with a list of files in a folder (non-recursive).
 void ls_( const char *targetPath, bool listFiles=true, bool prependPath=true, bool filterOSFiles=true );
 void files( const char *t ) { ls_(t); }
 void folder( const char *t ) { ls_(t); }
 void fromSimpleString( const string& in ) {
  string piece=string("");
  const char *p=string_argument(in.c_str(),&piece);
  while ( piece.length() > 0 ) {
   this->Add(piece);
   p=string_argument(p,&piece);
  }
 }
 void fromSimpleString( const char *in ) {
  string piece=string("");
  const char *p=string_argument(in,&piece);
  while ( *p != '\0' ) {
   this->Add(piece);
   p=string_argument(p,&piece);
  }
 }
 void Output() { OUTPUT("%s", toString().c_str() ); }
 virtual string toStringList() {
  string out=string("");
  FOREACH(String,s) {
   out+=string("{")+s->s+string("}\n");
  }
  return out;
 }
 void fromStringList( const char * s ) {
  Zstring in(s);
  const char *w=in.Next();
  while ( *w != '\0' ) {
   String *str=new String(w);
   Append(str);
   w=in.Next();
  }
 }
 virtual string toStringDecimalList() {
  string out=string("");
  FOREACH(String,s) { out+=string("{")+s->s+string("} ")+FMT("%1.2f",s->floating)+string("\n"); }
  return out;
 }
 void fromStringDecimalList( const char * s ) {
  Zstring in(s);
  const char *w=in.Next();
  while ( *w != '\0' ) {
   String *str=new String(w);
   w=in.Next();
   str->floating=(float)atof(w);
   Append(str);
   w=in.Next();
  }
 }
 virtual string toStringIntegerList() {
  string out=string("");
  FOREACH(String,s) {
   out+=string("{")+s->s+string("} ")+FMT("%1.2f",s->integer)+string("\n");
  }
  return out;
 }
 void fromStringIntegerList( const char * s ) {
  Zstring in(s);
  const char *w=in.Next();
  while ( *w != '\0' ) {
   String *str=new String(w);
   w=in.Next();
   str->integer=atoi(w);
   Append(str);
   w=in.Next();
  }
 }
 string toString() {
  string out=string("");
  incdent();
  FOREACH(String,s) {
   string classname=typeid(*s).name();
   string discard;
   const char *q=string_argument(classname.c_str(),&discard); // discards the words "class or struct"
   if ( !str_cmp(q,"String") ) out+=indention()+string("string {\n")+s->toString()+string("}\n");
   else
    if ( !str_cmp(q,"KeyValuePair") ) {
     KeyValuePair *kv=(KeyValuePair *)s;
     out+=indention()+string("kv {\n")+kv->toString()+string("}\n");
    }
  }
  decdent();
  return out;
 }
 int longest() {
  int candidate=0;
  FOREACH(String,s) if ( (int)s->s.length() < candidate ) candidate=(int)s->s.length();
  return candidate;
 }
 String *Longest() {
  String *candidate=null;
  FOREACH(String,s) if ( candidate ) candidate=s;
  return candidate;
 }
 Strings() : LinkedList() {}
 // Strings( const char *filename ) : LinkedList() {  Load(filename); } /* Returns a list of lines */
 String *Add( const char *s ) {
  String *S=new String(s);
  S->integer=count;
  Append(S);
  return S;
 }
 String *Add( string s ) {
  String *S=new String(s);
  S->integer=count;
  Append(S);
  return S;
 }
 String *Add( const char *s, char c ) {
  Append(new String(s));
  String *L=(String *) last;
  L->c=c;
  return L;
 }
 String *Add( char c, const char *s ) {
  Append(new String(s));
  String *L=(String *) last;
  L->c=c;
  return L;
 }
 String *Add( string s, char c ) {
  Append(new String(s));
  String *L=(String *) last;
  L->c=c;
  return L;
 }
 String *Add( char c, string s ) {
  Append(new String(s));
  String *L=(String *) last;
  L->c=c;
  return L;
 }
 String *Add( const char *s, int i ) {
  Append(new String(s));
  String *L=(String *) last;
  L->integer=i;
  return L;
 }
 String *Add( string s, int i ) {
  Append(new String(s));
  String *L=(String *) last;
  L->integer=i;
  return L;
 }
 String *Add( const char *s, float i ) {
  Append(new String(s));
  String *L=(String *) last;
  L->floating=i;
  return L;
 }
 String *Add( string s, float i ) {
  Append(new String(s));
  String *L=(String *) last;
  L->floating=i;
  return L;
 }
 String *Add( string s, int i, float f ) {
  Append(new String(s));
  String *L=(String *) last;
  L->integer=i;
  L->floating=f;
  return L;
 }
 String *Add( const char *s, int i, float f ) {
  Append(new String(s));
  String *L=(String *) last;
  L->integer=i;
  L->floating=f;
  return L;
 }
 KeyValuePair *addKeyValue( const char *s, const char *v ) {
  KeyValuePair *k=new KeyValuePair( s, v );
  Append(k);
  return k;
 }
 KeyValuePair *addKeyValue( const char *s, int v ) {
  KeyValuePair *k=new KeyValuePair( s, v );
  Append(k);
  return k;
 }
 KeyValuePair *addKeyValue( const char *s, float v ) {
  KeyValuePair *k=new KeyValuePair( s, v );
  Append(k);
  return k;
 }
 // void Load( const char *filename );  /* Returns a list of lines */
 // void Save( const char *filename );
 bool inList( string s );
 String *matchPrefix( const char *s );
 void matchesPrefix( const char *s, Strings *out );
 // caseless match or returns null
 String *match( const char *s );
 String *find( string s );
 String *find( const char *s );
 String *find( const char c ) {
  FOREACH(String,s) if ( s->c==c ) return s;
  return null;
 }
 String *find( int i ) {
  FOREACH(String,s) if ( s->integer==i ) return s;
  return null;
 }
 const char *AnyChar() {
  String *ele=(String *)Any();
  if ( !ele ) {
   OUTPUT("Strings:AnyChar() found no random element (is the list empty?)\n");
  }
  return ele->c_str();
 }
 const char *AnyChar( int seed ) {
  String *ele=(String *)Any(seed);
  if ( !ele ) {
   OUTPUT("Strings:AnyChar(%d) found no random element (is the list empty?)\n", (int) seed);
  }
  return ele->c_str();
 }
 const char *Chars( int i ) {
  FOREACH(String,s) if ( s->integer==i ) return s->s.c_str();
  OUTPUT("Strings:Chars(%d) reports no such element in list, returning empty string\n", (int) i);
  return string_error();
 }
 // Gets the value or empty string if none
 string Get( int i ) {
  String *s=(String *) Element(i);
  if ( s ) return s->s;
  return string("");
 }
 // Gets the value, then tests if the value matches the expected caseless comparison
 bool Is( int i, std::string caselessMatch ) {
  String *s=(String *) Element(i);
  Zstring test;
  if (s) test = s->s;
  return test == caselessMatch;
 }
 // Gets the value or empty string if none, wraps
 string Get( int i, having modulo ) {
  String *s=(String *) Element(i % count.value);
  if ( s ) return s->s;
  return string("");
 }
 string strings( int i ) {
  FOREACH(String,s) if ( s->integer==i ) return s->s;
  return string("");
 }
 bool includes( Strings *all_of_these ) {
  FOREACH(String,s) EACH(all_of_these->first,String,t) if ( str_cmp(s->s.c_str(),t->s.c_str()) ) return false;
  return true;
 }
 bool is_included( Strings *cloud ) {
  EACH(cloud->first,String,t) FOREACH(String,s) if ( str_cmp(s->s.c_str(),t->s.c_str()) ) return false;
  return true;
 }
 String *findCaseless( string s );
 String *findCaseless( const char *s );
 String *findSubstring( const char *s );
 String *contains( const char *s ) { return findSubstring(s); }
 String *findNextSubstring( String *start, const char *s );
 string concatToNextSubstring( String *start, const char *end );
 int IndexOf( String *s );
 string Concatenate( having Seamless ); // Returns duplicated concatenations of Strings
 string Concatenate( char seperator='\n' ); // Returns duplicated concatenations of Strings
 void appendFromString( const char *s, char c );
 void appendFromString( string s, char c );
 void show(void);
 void show( const char *sep, const char *end );
 // Splits using string_argument
 void SplitPush( const char *s );
 // Splits by seperator char
 void SplitPush( string s, char seperator );
 // Splits by char_isof, ex. delimiters of newline/space="\n "
 void SplitPush( const char *s, const char *delimiters );
 // Splits by seperator char
 void SplitPush( const char *s, char seperator );
 // Splits by script language rules
 void ScriptPush( const char *s );
 void Push( string s );
 void Push( const char *s );
 String *PushAndGet( const char *s );
 void DuplicateAndPush( const char * s );
 void DuplicateAndPush( Strings *in ) { Copy(in); }
 void Copy( Strings *ss ) {
  EACH(ss->first,String,s) Append( s->Copy() );
 }
 void ClearThenCopy( Strings *ss ) {
  Clear();
  Copy(ss);
 }
 void printf( const char * fmt, ...) {
  static char buf [32768];
  va_list args;
  va_start(args, fmt);
  vsprintf_s(buf, fmt, args);
  va_end(args);
  Push(buf);
 }
 SORTING(String,SortAZ,{},{
  const char *p=A->c_str(); while ( *p != '\0' && !IS_ALPHA(*p) ) p++;
 const char *q=B->c_str(); while ( *q != '\0' && !IS_ALPHA(*q) ) q++;
 while ( *p!= '\0' && *q!='\0' ) {
  if ( (int) LOWER(*p) > (int) LOWER(*q) ) { result=1; break; }
  if ( (int) LOWER(*p) < (int) LOWER(*q) ) { result=-1; break; }
  p++; while ( *p != '\0' && !IS_ALPHA(*p) ) p++;
  q++; while ( *q != '\0' && !IS_ALPHA(*q) ) q++;
 }
 if ( result ==0 && *p != '\0' ) result=1;
 if ( result ==0 && *q != '\0' ) result=-1;
  },{});
 bool NotMatchesKeyValues( Strings *pairs ) {
  FOREACH(KeyValuePair,k) {
   KeyValuePair *kv=(KeyValuePair *) pairs->find(k->s);
   if ( kv->value != k->value ) return true;
  }
  return false;
 }
 virtual CLEARLISTRESET(String);
 ~Strings(void) { Clear(); }
};

inline Strings *ls( const char *targetPath, bool listFiles=true, bool prependPath=true, bool filterOSFiles=true );
inline Strings *ls( const char *targetPath, bool listFiles, bool prependPath, Strings *filters );

/**
* \class Cartesian
* \brief Implements simple cartesian operations common to UI and graphics
* Used by this framework to process 2D and some 3D geometry related to interfaces and graphics
*/
enum CartesianForms {
 cartesian_default=-1,
 cartesian_none,
 cartesian_point,
 cartesian_line_rect,
 cartesian_box,
 cartesian_triangle,
 cartesian_circle,
 cartesian_sphere,
};

class CoplanarLinesResult;
class CoplanarLinesResults;
struct BoxCollisionResults;
class Cartesians;
class CartesianApproximation;
ONE(Cartesian, { Zero(); })
public:
 CartesianForms form;
 double 
  // Top left far point, or 2D point A
  x, y, z,
  // Cubic size (width, height, depth)
  w, h, d,       
  // Bottom right near point, or 2D point B
  x2, y2, z2,    
  // Result of the Angle() line angle calculation, or an angle provided for use later
  a,             
  // "Radius" for spheres and circles
  R,             
  // the "W" coordinate, not width, for four dimensional points
  W,             
  // Result of a distance calculation
  length,        
  // For rectangular areas
  area,          
  // For cubic volumes
  volume;        
 // Used by collision methods to mark whether or not a point exists, could also be considered "valid" indicator.
 Zbool exists;   
 // Used to approximate a circle, geometric figure or curve (a list of lines or triangles)
 Zdis<CartesianApproximation> approximation; 
 static int PntOnLine(int px, int py, int qx, int qy, int tx, int ty);
 Cartesian( Cartesian *in ) : ListItem() {
  x = in->x;  y = in->y;  z = in->z;
  w = in->w;  h = in->h;  d = in->d;
  x2 = in->x2;  y2 = in->y2;  z2 = in->z2;
  a = in->a;  R = in->R;  W = in->W;
  length = in->length;  area = in->area;  volume = in->volume;
  exists = in->exists;
 }
 Cartesian( Cartesian &in ) : ListItem() {
  x = in.x;  y = in.y;  z = in.z;
  w = in.w;  h = in.h;  d = in.d;
  x2 = in.x2;  y2 = in.y2;  z2 = in.z2;
  a = in.a;  R = in.R;  W = in.W;
  length = in.length;  area = in.area;  volume = in.volume;
  exists = in.exists;
 }
 Cartesian(int x, int y) : ListItem() { Set(x, y); form = cartesian_point; }
 Cartesian(double x, double y) : ListItem() { Set(x, y); form = cartesian_point; }
 Cartesian(int x, int y, int z) : ListItem() { Set(x, y, z); form = cartesian_point; }
 Cartesian(double x, double y, double z) : ListItem() { Set(x, y, z); form = cartesian_point; }
 Cartesian(int x, int y, int w, int h) : ListItem() { Set(x, y, w, h); form = cartesian_line_rect; }
 Cartesian(having corners, int x, int y, int x2, int y2) : ListItem() { Corners(x, y, x2, y2); form = cartesian_line_rect; }
 Cartesian(having corners, double x, double y, double x2, double y2) : ListItem() { Corners(x, y, x2, y2); form = cartesian_line_rect; }
 Cartesian(double x, double y, double w, double h) : ListItem() { Set(x, y, w, h); form = cartesian_line_rect; }
 Cartesian(int x, int y, int z, int w, int h, int d) : ListItem() { Cube(x, y, z, w, h, d); form = cartesian_box; }
 Cartesian(having corners, int x, int y, int z, int w, int h, int d) : ListItem() { Corners(x, y, z, w, h, d); form = cartesian_box; }
 Cartesian(double x, double y, double z, double w, double h, double d) : ListItem() { Cube(x,y,z,w,h,d); form = cartesian_box; }
 Cartesian(having corners, double x, double y, double z, double w, double h, double d) : ListItem() { Corners(x, y, z, w, h, d); form = cartesian_box; }
 void Zero() { form = cartesian_none; x = y = z = w = h = d = x2 = y2 = z2 = a = R = W = length = 0.0; exists = false; }
 void Reset() { Zero(); }
 void Set( const Cartesian *in ) {
  x = in->x;  y = in->y;  z = in->z;  w = in->w;  h = in->h;  d = in->d;  x2 = in->x2;  y2 = in->y2;  z2 = in->z2;
  area = in->area;  length = in->length;  volume = in->volume;  exists = in->exists;
 }
 void Set( Cartesian *in ) {
  x = in->x;  y = in->y;  z = in->z;  w = in->w;  h = in->h;  d = in->d;  x2 = in->x2;  y2 = in->y2;  z2 = in->z2;
  area = in->area;  length = in->length;  volume = in->volume;  exists = in->exists;
 }
 void Set( Cartesian &in ) {
  x = in.x;  y = in.y;  z = in.z;  w = in.w;  h = in.h;  d = in.d;  x2 = in.x2;  y2 = in.y2;  z2 = in.z2;
  area = in.area;  length = in.length;  volume = in.volume;  exists = in.exists;
 }
 void Set( int x, int y ) {
  this->x  = (double)(x);
  this->y  = (double)(y);
  this->x2 = this->x + this->w;
  this->y2 = this->y + this->h;
  Distance();
 }
 void Set( double x, double y ) {
  this->x  = x;
  this->y  = y;
  this->x2 = this->x + this->w;
  this->y2 = this->y + this->h;
  Distance();
 }
 void Set( double x, double y, double z ) {
  this->x  = x;
  this->y  = y;
  this->z  = z;
  this->x2 = this->x + this->w;
  this->y2 = this->y + this->h;
  this->z2 = this->z + this->d;
  Distance();
 }
 void Set( double x, double y, double w, double h ) {
  this->x  = x;
  this->y  = y;
  this->w  = w;
  this->h  = h;
  this->x2 = x + w;
  this->y2 = y + h;
  Distance();
  form = cartesian_line_rect;
 }
 void Set( int x, int y, int w, int h ) {
  this->x  = (double)(x);
  this->y  = (double)(y);
  this->w  = (double)(w);
  this->h  = (double)(h);
  this->x2 = (double)(x + w);
  this->y2 = (double)(x + h);
  Distance();
  form = cartesian_line_rect;
 }
 void Corners( int x, int y, int x2, int y2 ) {
  this->x  = (double)(x < x2 ? x : x2);
  this->y  = (double)(y < y2 ? y : y2);
  this->x2 = (double)(x < x2 ? x2 : x);
  this->y2 = (double)(y < y2 ? y2 : y);
  this->w  = (double)(this->x2 - this->x);
  this->h  = (double)(this->y2 - this->y);
  Distance();
  form = cartesian_line_rect;
 }
 void Set( int x, int y, int z ) {
  this->x  = (double)(x < x2 ? x : x2);
  this->y  = (double)(y < y2 ? y : y2);
  this->z  = (double)(z < z2 ? z : z2);
  this->x2 = this->x + this->w;
  this->y2 = this->y + this->h;
  this->z2 = this->z + this->d;
  Distance();
 }
 void Set(int x, int y, int z, int w, int h, int d) { Cube(x, y, z, w, h, d); }
 void Set(double x, double y, double z, double w, double h, double d) { Cube(x, y, z, w, h, d); }
 void Cube( int x, int y, int z, int w, int h, int d ) {
  this->x  = (double)(x);
  this->y  = (double)(y);
  this->z  = (double)(z);
  this->w  = (double)(w);
  this->h  = (double)(h);
  this->d  = (double)(d);
  this->x2 = (double)(x + w);
  this->y2 = (double)(y + h);
  this->z2 = (double)(z + d);
  form = cartesian_box;
  Distance();
 }
 void Cube( double x, double y, double z, double w, double h, double d ) {
  this->x  = x;
  this->y  = y;
  this->z  = z;
  this->w  = w;
  this->h  = h;
  this->d  = d;
  this->x2 = this->x + this->w;
  this->y2 = this->y + this->h;
  this->z2 = this->z + this->d;
  form = cartesian_box;
  Distance();
 }
 void Line(double x, double y, double x2, double y2) { Corners(x, y, x2, y2); }
 void Corners( double x, double y, double x2, double y2 ) {
  this->x  = x < x2 ? x : x2;
  this->y  = y < y2 ? y : y2;
  this->x2 = x < x2 ? x2 : x;
  this->y2 = y < y2 ? y2 : y;
  this->w  = this->x2 - this->x;
  this->h  = this->y2 - this->y;
  form = cartesian_line_rect;
  Distance();
 }
 void Corners( int x, int y, int z, int x2, int y2, int z2 ) {
  this->x  = (double)(x < x2 ? x : x2);
  this->y  = (double)(y < y2 ? y : y2);
  this->z  = (double)(z < z2 ? z : z2);
  this->x2 = (double)(x < x2 ? x2 : x);
  this->y2 = (double)(y < y2 ? y2 : y);
  this->z2 = (double)(z < z2 ? z2 : z);
  this->w  = (double)(this->x2 - this->x);
  this->h  = (double)(this->y2 - this->y);
  this->d  = (double)(this->z2 - this->z);
  form = cartesian_box;
  Distance();
 }
 void Corners( double x, double y, double z, double x2, double y2, double z2 ) {
  this->x  = x < x2 ? x : x2;
  this->y  = y < y2 ? y : y2;
  this->z  = z < z2 ? z : z2;
  this->x2 = x < x2 ? x2 : x;
  this->y2 = y < y2 ? y2 : y;
  this->z2 = z < z2 ? z2 : z;
  this->w  = this->x2 - this->x;
  this->h  = this->y2 - this->y;
  this->d  = this->z2 - this->z;
  form = cartesian_box;
  Distance();
 }
 //! Returns the minimum x-value of x or x2 (when treating a AA)
 double MinX() { return (x < x2 ? x : x2); }
 //! Returns the minimum y-value of y or y2 (when treating a AA)
 double MinY() { return (y < y2 ? y : y2); }
 //! Returns the minimum z-value of z or z2 (when treating a AA)
 double MinZ() { return (z < z2 ? z : z2); }
 //! Returns the maximum x-value of x or x2 (when treating a AA)
 double MaxX() { return (x > x2 ? x : x2); }
 //! Returns the maximum y-value of y or y2 (when treating a AA)
 double MaxY() { return (y > y2 ? y : y2); }
 //! Returns the maximum z-value of z or z2 (when treating a AA)
 double MaxZ() { return (z > z2 ? z : z2); }
 //! Exports the maximum point
 Cartesian *Max() {
  double mx = MaxX(), my = MaxY(), mz = MaxZ();
  return new Cartesian(mx,my,mz);
 }
 //! Exports the minimum point
 Cartesian *Min() {
  double mx = MinX(), my = MinY(), mz = MinZ();
  return new Cartesian(mx,my,mz);
 }
 //! Calculates the area of the rectangular region described herein
 double Area() { return area = w*h; }
 //! Calculates the volume of the AA cubic region described herein
 double Volume() { return volume = w*h*d; }
 int _X() { return (int)(x); }
 int _Y() { return (int)(y); }
 int _Z() { return (int)(z); }
 int _W() { return (int)(w); }
 int _H() { return (int)(h); }
 int _D() { return (int)(d); }
 int _X2() { return (int)(x2); }
 int _Y2() { return (int)(y2); }
 int _Z2() { return (int)(z2); }
 //! Is tx, ty within this rectangle?
 bool Within( int tx, int ty ) {
  double dtx = (double)(tx);
  double dty = (double)(ty);
  return dtx >= x && dtx < x2 && dty >= y && dty < y2;
 }
 //! Is tx, ty, tz within this cube?
 bool Within( int tx, int ty, int tz ) {
  double dtx = (double)(tx);
  double dty = (double)(ty);
  double dtz = (double)(tz);
  return dtx >= x && dtx < x2 && dty >= y && dty < y2 && dtz >= z && dtz < z2;
 }
 //! Is tx, ty within this rectangle?
 bool Within( double dtx, double dty ) {
  return dtx >= x && dtx < x2 && dty >= y && dty < y2;
 }
 //! Is tx, ty, tz within this cube?
 bool Within( double dtx, double dty, double dtz ) {
  return dtx >= x && dtx < x2 && dty >= y && dty < y2 && dtz >= z && dtz < z2;
 }
 //! Is tx, ty within this rectangle?
 bool WithinInside(double dtx, double dty) {
  return dtx > x && dtx < x2 && dty > y && dty < y2;
 }
 //! Is tx, ty, tz within this cube?
 bool WithinInside(double dtx, double dty, double dtz) {
  return dtx > x && dtx < x2 && dty > y && dty < y2 && dtz > z && dtz < z2;
 }
 //! Is tx, ty within (inclusively) this rectangle?
 bool WithinInclusive( int tx, int ty ) {
  double dtx = (double)(tx);
  double dty = (double)(ty);
  return dtx >= x && dtx <= x2 && dty >= y && dty <= y2;
 }
 //! Is tx, ty, tz within (inclusively) this cube?
 bool WithinInclusive( int tx, int ty, int tz ) {
  double dtx = (double)(tx);
  double dty = (double)(ty);
  double dtz = (double)(tz);
  return dtx >= x && dtx <= x2 && dty >= y && dty <= y2 && dtz >= z && dtz <= z2;
 }
 //! Is dtx, dty within (inclusively) this rectangle?
 bool WithinInclusive( double dtx, double dty ) {
  return dtx >= x && dtx <= x2 && dty >= y && dty <= y2;
 }
 //! Is dtx, dty, dtz within this cube?
 bool WithinInclusive( double dtx, double dty, double dtz ) {
  return dtx >= x && dtx <= x2 && dty >= y && dty <= y2 && dtz >= z && dtz <= z2;
 }
 //! Calculate naively (use LineBox for verbose) if this cartesian is a line within the provided box
 bool Within( Cartesian box ) { return (box.Within(x, y) && box.Within(x2, y2)); }
 //! Calculate if we as a rectangle overlap b rectangle
 bool Overlaps( Cartesian &b ) { return ! ( x > b.x2 || b.x > x2 || y > b.y2 || b.y > y2); }
 //! Calculate and return the midpoint
 Cartesian *Midpoint() { return new Cartesian( 0.5 * x + 0.5 * x2, 0.5 * y + 0.5 * y2, 0.5 * z + 0.5 * z2 ); }
 //! Calculate and return the centroid
 Cartesian *Centroid() { return Midpoint(); }
 //! Convert degrees to radians
 static double to_rad( double deg ) { return deg * 0.017453292519943; }
 //! Convert radians to degrees
 static double to_deg( double rad ) { return rad * 57.295779513082321; }
 //! Returns a 2d "line angle" (in radians)
 double Angle() { return ( a = atan2( (y2-y), (x2-x) ) ); }
 //! Returns a 3d "spherical angle" where X=(x,y), Y=(y,z) and Z=(z,x)
 Cartesian *Angle3d() { return new Cartesian( Angle(), atan2((y2 - y), (z2 - z)), atan2((x2 - x), (z2 - z)) ); }
 //! Length
 double Magnitude() { return Distance(); }
 //! Distance
 double Magnitude( Cartesian other ) { return Distance(other); }
 //! Magnitude
 double Distance( Cartesian other ) {
  if ( x==other.x && y==other.y ) return 0.0;
  return sqrt( ((x - other.x) * (x - other.x)) + ((y - other.y) * (y - other.y)) ) ;
 }
 //! Distance of line
 double Distance() {
  if ( x==x2 && y==y2 ) return 0.0;
  return length = sqrt( ((x - x2) * (x - x2)) + ((y - y2) * (y - y2)) ) ;
 }
 //! 3D Magnitude (Cubic)
 double Magnitude3d() { return Distance3d(); }
 //! 3D Magnitude (Cubic / 3D Distance)
 double Distance3d() {
  double d2d = Distance();
  if ( x==x2 && y==y2 && z==z2 ) return 0.0;
  return length = sqrt(((d2d*d2d)+((z2-z)*(z2-z))));
 }
 //! Set *this to a point on provided line
 bool PointOn( double t, Cartesian line ) {
  if (t < 0.0 || t > 1.0) return false;
  if (t == 1.0) Set(line.x2,line.y2);
  else if (t == 0.0) Set(line.x,line.y);
  else Set( (1.0 - t) * line.x + t * line.x2, (1.0 - t) * line.y + t * line.y2, (1.0 - t) * line.z + t * line.z2 );
  form = cartesian_point;
  return true;
 }
 //! General utility Lerp function used by other Lerp functions
 static double Lerp(double a, double b, double t) { if (a == b) return a; return (1.0 - t) * a + t * b; }
 //! Lerp between p->p2 in three dimensions
 Cartesian *Lerp( double t ) {
  return new Cartesian( Lerp(x,x2,t), Lerp(y,y2,t), Lerp(z,z2,t) );
 }
 //! Lerp between x,y,z and incoming point b
 Cartesian *Lerp( double t, Cartesian b ) {
  return new Cartesian( true, Lerp(x,b.x,t), Lerp(y,b.y,t), Lerp(z,b.z,t), Lerp(x2,b.x2,t), Lerp(y2,b.y2,t), Lerp(z2,b.z2,t) );
 }
 //! Lerp between and incoming points a and b and set ourself
 void Lerp( double t, Cartesian a, Cartesian b ) {
  Corners( Lerp(a.x,b.x,t), Lerp(b.y,b.y,t), Lerp(b.z,b.z,t), Lerp(b.x2,b.x2,t), Lerp(b.y2,b.y2,t), Lerp(b.z2,b.z2,t) );
 }
 //! Set the size of the cubic region, relative to the original x,y,z point
 void Size( double w, double h, double d ) { Cube(this->x, this->y, this->z, w, h, d); }
 //! Scale the region from x,y,z point to a new size relative the original size
 void Scale( double factor ) { Set( x,y,z,w*factor,h*factor,d*factor ); }
 //! Scale the region maintaining the center's location
 void Scale( having same_center, double factor ) {
  Cartesian *center = Midpoint();
  Set(0.0, 0.0, 0.0, w*factor, h*factor, d*factor);
  MoveBy(center->x - w / 2.0, center->y - h / 2.0, center->z - d / 2.0);
  delete center;
 }
 //! Offset the region by a delta
 void MoveBy(int dx, int dy) { Set(x + (double)(dx), y + (double)(dy), z, w, h, d); }
 //! Offset the region by a delta
 void MoveBy(int dx, int dy, int dz) { Set(x + (double)(dx), y + (double)(dy), z + (double)(dz), w, h, d); }
 //! Offset the region by a delta
 void MoveBy(double dx, double dy) { Set(x + dx, y + dy, z, w, h, d); }
 //! Offset the region by a delta
 void MoveBy(double dx, double dy, double dz) { Set(x + dx, y + dy, z + dz, w, h, d); }
 //! Packs a triangle into the Cartesian class.
 void Triangle( int ax, int ay, int az, int bx, int by, int bz, int cx, int cy, int cz ) {
  Triangle( (double)(ax), (double)(ay), (double)(az), (double)(bx), (double)(by), (double)(bz), (double)(cx), (double)(cy), (double)(cz) );
 }
 //! Packs a triangle into the Cartesian class.
 void Triangle( double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz ) {
  Ax(ax); Ay(ay); Az(az); Bx(bx); By(by); Bz(bz); Cx(cx); Cy(cy); Cz(cz);  
 }
 //! Unpacks triangular point values
 double Ax() { return x; } double Bx() { return x2; } double Cx() { return w; }
 double Ay() { return y; } double By() { return y2; } double Cy() { return h; }
 double Az() { return z; } double Bz() { return z2; } double Cz() { return d; }
 //! Packs triangle point values
 void Ax( int i ) { double v = (double)(i); x=v; }
 void Ay( int i ) { double v = (double)(i); y=v; }
 void Az( int i ) { double v = (double)(i); z=v; }
 void Bx( int i ) { double v = (double)(i); x2=v; }
 void By( int i ) { double v = (double)(i); y2=v; }
 void Bz( int i ) { double v = (double)(i); z2=v; }
 void Cx( int i ) { double v = (double)(i); w=v; }
 void Cy( int i ) { double v = (double)(i); h=v; }
 void Cz( int i ) { double v = (double)(i); d=v; }
 //! Packs triangle point values
 void Ax( double v ) { x=v; } void Ay( double v ) { y=v; } void Az( double v ) { z=v; }
 void Bx( double v ) { x2=v; } void By( double v ) { y2=v; } void Bz( double v ) { z2=v; }
 void Cx( double v ) { w=v; } void Cy( double v ) { h=v; } void Cz( double v ) { d=v; }
 //! Retrieves a packed triangle.
 void Triangle( Cartesian &A, Cartesian &B, Cartesian &C ) {
 }
 //! Packs a circle
 void Circle(int x, int y, double R) { Set(x, y); this->R = R; w = R * 2.0; form=cartesian_circle; }
 //! Packs a circle
 void Circle(double x, double y, double R) { Set(x, y); this->R = R; w = R * 2.0; form=cartesian_circle; }
 //! Uses the approximation Cartesian list to approximate a circle at a given precision
 void ApproximateCircle( int precision=16 );
 //! Performs validation and calculation of box parameters
 void Box();
 //! Packs a sphere
 void Sphere(int x, int y, int z, double R) { Set(x, y, z); this->R = R; w = h = d = R*2.0; form=cartesian_sphere; }
 //! Packs a sphere
 void Sphere(double x, double y, double z, double R) { Set(x, y, z); this->R = R; w = h = d = R*2.0; form=cartesian_sphere; }
 //! Returns true if a circle and a line are colliding.  If !enter.exists, line starts inside the circle, if !exit.exists, line ended inside circle
 bool CircleLine(Cartesian line, Cartesian &enter, Cartesian &exit, int precision=16);
 //! Returns true if an AA box and a line are colliding.  If !enter.exists, line started outside rectangle, if !exit exists, line ended inside rectangle
 bool RectLine( Cartesian box, BoxCollisionResults &out);
 //! Returns true if the AA box and Line are colliding.  If !enter.exists, line started inside box, if !exit.exists, line ended inside box
 bool LineRect( Cartesian line, BoxCollisionResults &out);
 //! Returns true if a point is inside a circle
 bool PointCircle(Cartesian circle);
 //! Returns true if a line and a line are crossing.  Will not manipulate "point" if !collided, otherwise will write the point of crossing
 bool LineLine( Cartesian otherLine, Cartesian &point);
 //! Returns true if a circle and a circle are colliding.  Returns the intersection points as a line.
 bool CircleCircle(Cartesian circle, Cartesian &intersection);
 //! TODO: Returns true if a sphere and a sphere are colliding.  Returns the overlap.
 bool SphereSphere( Cartesian box, Cartesian &overlap);
 //! Returns true if the 2d rect and 2d rect are colliding.  Returns the overlap.
 bool RectRect(Cartesian b, CoplanarLinesResults &out, Cartesian &overlap);
 //! Distance Point Line (based on code by Paul Bourke), returns intersection (closest point on line to point, perpendicular) and the distance
 bool DistancePointLine(double px, double py, double pz, Cartesian &intersectionOut, double &distOut);
 //! Distance Point Line (based on code by Paul Bourke), returns intersection (closest point on line to point, perpendicular) and the distance
 bool DistancePointLine(Cartesian point, Cartesian &intersectionOut, double &distOut);
 void operator= (const Cartesian& in) { Set(&in); }
 CLONE(Cartesian,{
  DUPE(x);  DUPE(w);  DUPE(x2);
 DUPE(y);  DUPE(h);  DUPE(y2);
 DUPE(z);  DUPE(d);  DUPE(z2);
 DUPE(exists);
 DUPE(W);  DUPE(R);  a->a = this->a;
 DUPE(length);
 DUPE(area);
 DUPE(volume);
  })
  MANY(Cartesian, CartesianHandle, CartesianHandles, "Cartesian", Cartesians, {})
   //! Treating the list as a series of coplanar lines, test another line against it, sorted by distance
   bool Collides( Cartesian line, CoplanarLinesResults &out );
  //! Treating the list as a series of coplanar lines, test another line against it but sort results in reverse distance
  bool Collides( Cartesian line, CoplanarLinesResults &out, bool reverseSort );
  //! Treating the list as a series of coplanar lines, test another series of lines against it
  bool Collides(Cartesians *lines, CoplanarLinesResults &out);
  // Returns the first encountered (not the least) point-to-line test within Tolerance
  Cartesian *OnEdge( double x, double y, double z, double Tolerance, Cartesian &intersection ) {
   Cartesian tpoint(x,y,z);
   FOREACH(Cartesian,L) {
    double D;
    bool onSegment=L->DistancePointLine(tpoint,intersection,D);
    if ( D <= Tolerance ) return L;
   }
   return null;
  }
  Cartesian *Add(double x, double y) { Cartesian *a = new Cartesian(x, y); Append(a); return a; }
  Cartesian *Add(double x, double y, double z) { Cartesian *a = new Cartesian(x, y, z); Append(a); return a; }
  Cartesian *Add(double x, double y, double w, double h) { Cartesian *a = new Cartesian(x, y, w, h); Append(a); return a; }
  Cartesian *Add(double x, double y, double z, double w, double h, double d) { Cartesian *a = new Cartesian(x, y, z, w, h, d); Append(a); return a; }
  Cartesian *Add(having corners, double x, double y, double x2, double y2) { Cartesian *a = new Cartesian(true, x, y, x2, y2); Append(a); return a; }
  Cartesian *Add(having corners, double x, double y, double z, double x2, double y2, double z2) { Cartesian *a = new Cartesian(true, x, y, z, x2, y2, z2); Append(a); return a; }
  Cartesian *Add(int x, int y) { Cartesian *a = new Cartesian(x, y); Append(a); return a; }
  Cartesian *Add(int x, int y, int z) { Cartesian *a = new Cartesian(x, y, z); Append(a); return a; }
  Cartesian *Add(int x, int y, int w, int h) { Cartesian *a = new Cartesian(x, y, w, h); Append(a); return a; }
  Cartesian *Add(int x, int y, int z, int w, int h, int d) { Cartesian *a = new Cartesian(x, y, z, w, h, d); Append(a); return a; }
  Cartesian *Add(having corners, int x, int y, int x2, int y2) { Cartesian *a = new Cartesian(true, x, y, x2, y2); Append(a); return a; }
  Cartesian *Add(having corners, int x, int y, int z, int x2, int y2, int z2) { Cartesian *a = new Cartesian(true, x, y, z, x2, y2, z2); Append(a); return a; }
  DONE(Cartesian);

  bool operator == ( Cartesian& a, Cartesian& b );

  ONE(CoplanarLinesResult,{ Reset(); })
   Zdouble x,y;
  Cartesian segment;
  Zdouble d;
  Cartesian onEdge;
  Zdouble edgeDistance;
  void Reset() {
   x=y=d=edgeDistance=0.0;
   segment.Set(0.0,0.0,0.0,0.0,0.0,0.0);
   onEdge.Set(0.0,0.0,0.0,0.0,0.0,0.0);
  }
  double Distance( double sx, double sy ) { return (double) (d=Cartesian(x,y,sx,sy).Distance()); }
  MANY(CoplanarLinesResult,CoplanarLinesResultHandle,CoplanarLinesResultHandles,"CoplanarLinesResult",CoplanarLinesResults,{})
   Zp<Cartesian> onEdge;
  Zdouble sx,sy;
  //! Sets incoming pointer to the minimum point in the list.
  void Min( Cartesian *min ) {
   if ( count == 0 ) return;
   CoplanarLinesResult *one=(CoplanarLinesResult *)first;
   min->Set(one->x,one->y);
   FOREACH(CoplanarLinesResult,c) {
    if ( c->x < min->x ) min->x=c->x;
    if ( c->y < min->y ) min->y=c->y;
   }
  }
  //! Sets incoming pointer to the maximum point in the list.
  void Max( Cartesian *max ) {
   if ( count == 0 ) return;
   CoplanarLinesResult *one=(CoplanarLinesResult *)first;
   max->Set(one->x,one->y);
   FOREACH(CoplanarLinesResult,c) {
    if ( c->x > max->x ) max->x=c->x;
    if ( c->y > max->y ) max->y=c->y;
   }
  }
  //! All incoming are read-only, new result is added to list
  void Add( Cartesian *line, Cartesian *collision ) {
   CoplanarLinesResult *result=new CoplanarLinesResult;
   result->x=collision->x;
   result->y=collision->y;
   result->segment.Set(line->x,line->y,line->z,line->x2,line->y2,line->z2);
   Append(result);
  }
  SORTING(CoplanarLinesResult,SortDistance,
   { FOREACH(CoplanarLinesResult,L) L->Distance(sx,sy); },
   { if ( A->d < B->d ) result=-1; },
   {}
  );
  DONE(CoplanarLinesResult);

  struct BoxCollisionResults {
  public:
   Zint collisions;
   Zbool collided,startsInside,endsInside,within;
   Zbool top,left,right,bottom;
   Zdouble x,y,x2,y2;
   Zp<Cartesian> onEdge;
   CoplanarLinesResults results;
   void Reset() {
    collisions=0;
    collided=startsInside=endsInside=false;
    top=left=right=bottom=false;
    x=y=x2=y2=0.0;
    onEdge=null;
    within=false;
    results.Clear();
   }
  };

  class CartesianApproximation : public Cartesians {
  public:
   Zp<Cartesian> left, right, top, bottom;
   Cartesian centroid;
  };


  // Implements a string packing algorithm for hashing strings for the HashStore.  
class PackedString : private ZIndexed<uint32_t> {
public:
 inline uint32_t PACK(unsigned char c0, unsigned char c1, unsigned char c2, unsigned char c3) {
  return (c0 << 24) | (c1 << 16) | (c2 << 8) | c3;
 } 
 inline uint32_t PACK(char c0, char c1, char c2, char c3) {
  return PACK((unsigned char)c0, (unsigned char)c1, (unsigned char)c2, (unsigned char)c3);
 }
 PackedString() {}
 PackedString( const char *s, bool lowercase=true ) {
  Set(s,lowercase);
 }
 size_t Length() { return this->length; }
 size_t W() { return this->w; }
 size_t H() { return this->h; }
 uint32_t Get( unsigned int idx ) { return (*this)(idx); }
 void Set( const char *s, bool lowercase=true ) {
  size_t len=strlen(s);
  this->Size(len/4 + (len%4 == 0 ? 0 : 1));
  const char *p=s;
  char c[4];
  memset(c,0,sizeof(char)*4);
  int i=0,j=0;
  while ( *p != '\0' ) {
   c[i]=lowercase ? LOWER(*p) : (*p);
   i++;
   if ( *(p+1) == '\0' || i > 3 ) {
    i=0;
    this->list[j]=PACK(c[0],c[1],c[2],c[3]);
    memset(c,0,sizeof(char)*4);
    j++;
   }
   p++;
  }
 }
 bool exactly( const PackedString *in ) {
  if ( in->length != length ) return false;
  for ( size_t i=0; i<length; i++ ) if ( this->list[i] != in->list[i] ) return false;
  return true;
 }
 PackedString& operator= ( const char *s ) { Set(s,true);  return *this; }
 PackedString& operator&=( const char *s ) { Set(s,false); return *this; }
};


inline bool operator == (PackedString& a, PackedString& b);
inline bool operator != (PackedString& a, PackedString& b);
  

inline bool operator == (PackedString& a, PackedString& b) {
 return a.exactly(&b);
}

inline bool operator != (PackedString& a, PackedString& b) {
 return !a.exactly(&b);
}

// Implements a 2D hash store of packed strings templated to the ListItem and LinkedList ecosystem,
// using ZIndexed for the table.
template<class ITEM, class LIST>
class HashStore : public ListItem {
public:
 ZIndexed<LIST> store;
 size_t depth;
 HashStore( size_t depth=1024 ) : ListItem() {
  this->depth=depth;
  store.Size(depth,depth);
  Init();
 }
 virtual void Init() {}
 LIST *Bucket( PackedString *packed ) {
  unsigned int x=packed->Length() > 0 ? packed->Get(0) : 0;
  unsigned int y=packed->Length() > 1 ? packed->Get(1) : 0;
  x %= (int)depth;
  y %= (int)depth;
  return &store(x,y);
 }
 LIST *Get( unsigned int x ) { return &store(x); }
 LIST *Get( unsigned int x, unsigned int y ) { return &store(x,y); }
 void Append( ITEM *I, PackedString *packed ) {
  LIST *L=Bucket(packed);
  L->Append(I);
 }
 bool Append( ITEM *I, PackedString *packed, bool check_if_stored ) {
  LIST *L=Bucket(packed);
  if ( !L->inList(I) ) {
   L->Append(I);
   return true;
  }
  return false;
 }
 void Prepend( ITEM *I, PackedString *packed ) {
  LIST *L=Bucket(packed);
  L->Prepend(I);
 }
 bool Prepend( ITEM *I, PackedString *packed, bool check_if_stored ) {
  LIST *L=Bucket(packed);
  if ( !L->inList(I) ) {
   L->Prepend(I);
   return true;
  }
  return false;
 }
 bool Stored( ITEM *I, PackedString *packed ) {
  LIST *L=Bucket(packed);
  return ( L->inList(I) );
 }
 ITEM *Extract( ITEM *I, PackedString *packed ) {
  LIST *L=Bucket(packed);
  L->Remove(I);
  return I;
 }
 void Restore( ITEM *I, PackedString *packed ) {
  Extract(I);
  Append(I,packed);
 }
 void RestorePrepend( ITEM *I, PackedString *packed ) {
  Extract(I);
  Prepend(I,packed);
 }
 /* To be used in the template instantiation:
 int Total() {
  int total=0;
  size_t length=SQ(depth);
  for ( unsigned int i=0; i<length; i++ ) total+=store(i).count.value;
  return total;
 }
 */
};

 // String Indexer
 // (String hashing template based on ZIndexed)

template<class LISTITEMCHILD>
class StringIndexed {
public:
 ZIndexed<LinkedList> lists;
 Zint last_index;
 Zint index_iterator;
 Zp<LinkedList> lists_iterator;
 Zp<ListItem> list_iterator;
 StringIndexed() {
  Init();
 }
 void Init( size_t depth=256 ) {
  Depth(depth);
  Rewind();
 }
 void Rewind() {
  index_iterator=0;
  lists_iterator=&lists[index_iterator];
  list_iterator=lists_iterator->first;
 }
 LISTITEMCHILD *Next() {
  if ( !lists_iterator ) Rewind();
  else {
   if ( list_iterator ) list_iterator=list_iterator->next;
   if ( !list_iterator ) {
    index_iterator++;
    if ( index_iterator >= lists.length ) { Rewind(); return (LISTITEMCHILD *) list_iterator.pointer; }
    lists_iterator=&lists[index_iterator];
    list_iterator=lists_iterator->first;
   }
  }
  return (LISTITEMCHILD *) list_iterator.pointer;
 }
 void Remove() { if ( lists_iterator && list_iterator ) lists_iterator->Remove(list_iterator.pointer); }
 void Depth( size_t depth=256 ) { lists.Size(depth); }
 int Encode( const char *s ) {
  int index=0;
  int len=strlen(s);
  if ( len <= 0 ) return 0;
  int a=len/4;        if ( a > len-1 ) a=len; int c_a=(int)s[a];
  int b=len/2;        if ( b > len-1 ) b=len; int c_b=(int)s[b];
  int c=len/2+len/4;  if ( c > len-1 ) c=len; int c_c=(int)s[c];
  int d=len/3;        if ( d > len-1 ) d=len; int c_d=(int)s[d];
  int e=len/3*2;      if ( e > len-1 ) e=len; int c_e=(int)s[e];
  int f=len-1;        if ( f > len-1 ) f=len; int c_f=(int)s[f];
  return (int)(last_index=((c_a+c_b+c_c+c_d+c_e+c_f)%(int)lists.length));
 }
 LinkedList *GetList( const char * s ) {
  Encode(s);
  return &lists[(size_t)(int)last_index];
 }
 void Store( const char *s, ListItem *single ) {
  LinkedList *list=GetList(s);
  list->Append(single);
 }
 ListItem *SimpleGet( const char *s ) {
  LinkedList *list=GetList(s);
  Zstring test;
  EACH(list->first,ListItem,i) {
   i->GetThisStringIndex(test.self());
   if ( test == s ) return i;
  }
  return null;
 }
 LISTITEMCHILD *Get( const char *s ) {
  LinkedList *list=GetList(s);
  Zstring test;
  EACH(list->first,ListItem,i) {
   i->GetThisStringIndex(test.self());
   if ( test == s ) return (LISTITEMCHILD *)i;
  }
  return null;
 }
 LISTITEMCHILD *Remove( const char *s ) {
  ListItem *got=SimpleGet(s);
  if ( !got ) return null;
  if ( list_iterator == (ListItem *) got ) Next();
  if ( got ) lists[last_index].Remove(got);
  return (LISTITEMCHILD *)got;
 }
 ListItem &operator() ( const char *s ) { return *Get(s); }
};


  // -----

inline string file_as_string(const char *filename);
inline string file_as_string_streams(const char *filename);

inline bool string_as_file(const char *text, const char *fn);
inline bool file_exists(const char *fn);

  //----------------------------------------------------------------------------------


  /// Temporary buffer for int->string conversions
#ifndef va_start
#include <varargs.h>
#endif

#ifndef NEW
#define NEW(v,t) try { v= new t; } catch (bad_alloc& ba) { OUTPUT("NEW: bad_alloc caught: %s\n", ba.what()); v=null; }
#endif
#define CREATE(v,t) t *v=null; try { v= new t; } catch (bad_alloc& ba) { OUTPUT("NEW: bad_alloc caught: %s\n", ba.what()); v=null; }

#ifndef no_init_all
#define no_init_all deprecated
#endif
#include <Windows.h> // for OutputDebugString
  inline void output__(const char * fmt, ...) {
   static char OUT_buf[32768];
   memset(OUT_buf, 0, sizeof(char) * 32768);
   va_list args;
   va_start(args, fmt);
   vsnprintf_s(OUT_buf, 32768, fmt, args);
   va_end(args);
   int wchars = MultiByteToWideChar( CP_UTF8,0,OUT_buf,-1, NULL , 0 );
   wchar_t* msg = new wchar_t[wchars];
   MultiByteToWideChar(CP_UTF8,0,OUT_buf,-1, msg,wchars);
   MultiByteToWideChar(CP_UTF8,MB_PRECOMPOSED,buf,(int)strlen(OUT_buf),msg,0);
   OutputDebugStringW(msg);
   delete[] msg;
  }

#define FORMAT_STRING_SIZE 65536

  inline string FMT(const char*fmt, ...) {
   string s;
   static char FMT_buf[FORMAT_STRING_SIZE];
   va_list args;
   va_start( args, fmt );
   vsprintf_s(FMT_buf, fmt, args);
   va_end(args);
   s=string(FMT_buf);
   return s;
  }

  /// Forward declared type assocations

  /// Zfloat operator= overloads for forward declared types

  inline Zfloat& Zfloat::operator= ( const Zbyte& b   ) { value=(float)b.value; return *this; }
  inline Zfloat& Zfloat::operator= ( const Zuint& i   ) { value=(float)i.value; return *this; }
  inline Zfloat& Zfloat::operator= ( const Zint& i    ) { value=(float)i.value; return *this; }
  inline Zfloat& Zfloat::operator= ( const Zdouble& d ) { value=(float)d.value; return *this; }
  inline Zfloat& Zfloat::operator= ( const std::string& s ) { value=(float)atof(s.c_str()); return *this; }
  inline float Zfloat::operator()( Zbyte &b )   { return value=(float)b.value; }
  inline float Zfloat::operator()( Zuint &i )   { return value=(float)i.value; }
  inline float Zfloat::operator()( Zint &i )    { return value=(float)i.value; }
  inline float Zfloat::operator()( Zfloat &f )  { return value; }
  inline float Zfloat::operator()( Zdouble &d ) { return value=(float)d.value; }
  inline Zfloat& Zfloat::operator+= ( const Zint& i ) { value+=(float)i.value; return *this; }
  inline Zfloat& Zfloat::operator-= ( const Zint& i ) { value-=(float)i.value; return *this; }
  inline Zfloat& Zfloat::operator*= ( const Zint& i ) { value*=(float)i.value; return *this; }
  inline Zfloat& Zfloat::operator/= ( const Zint& i ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( (float) i.value == 0.0f ) {  
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zfloat: divide by zero in /= operation!\n");
#endif
    value=0.0f;
    return *this;
   }
#endif
   value/=(float)i.value;
   return *this;
  }

  /// Zbyte operator= overloads for forward declared types

  inline Zbyte& Zbyte::operator= ( const Zuint& i )   { value=(unsigned char)i.value; return *this; }
  inline Zbyte& Zbyte::operator= ( const Zint& i )    { value=(unsigned char)i.value; return *this; }
  inline Zbyte& Zbyte::operator= ( const Zfloat& f )  { value=(unsigned char)f.value; return *this; }
  inline Zbyte& Zbyte::operator= ( const Zdouble& d ) { value=(unsigned char)d.value; return *this; }
  inline Zbyte& Zbyte::operator= ( const std::string& s ) { value=(unsigned char)atof(s.c_str()); return *this; }
  inline unsigned char Zbyte::operator()( Zuint &i )   { return value=(unsigned char)i.value; }
  inline unsigned char Zbyte::operator()( Zint &i )    { return value=(unsigned char)i.value; }
  inline unsigned char Zbyte::operator()( Zfloat &f )  { return value=(unsigned char)f.value; }
  inline unsigned char Zbyte::operator()( Zdouble &d ) { return value=(unsigned char)d.value; }

  /// Zushort operator= overloads for forward declared types

  inline Zushort& Zushort::operator= ( const Zuint& i )   { value=(unsigned short)i.value; return *this; }
  inline Zushort& Zushort::operator= ( const Zint& i )    { value=(unsigned short)i.value; return *this; }
  inline Zushort& Zushort::operator= ( const Zfloat& f )  { value=(unsigned short)f.value; return *this; }
  inline Zushort& Zushort::operator= ( const Zdouble& d ) { value=(unsigned short)d.value; return *this; }
  inline Zushort& Zushort::operator= ( const std::string& s ) { value=(unsigned short)atof(s.c_str()); return *this; }
  inline unsigned short Zushort::operator()( Zuint &i )   { return value=(unsigned short)i.value; }
  inline unsigned short Zushort::operator()( Zint &i )    { return value=(unsigned short)i.value; }
  inline unsigned short Zushort::operator()( Zfloat &f )  { return value=(unsigned short)f.value; }
  inline unsigned short Zushort::operator()( Zdouble &d ) { return value=(unsigned short)d.value; }

  /// Zuint operator= overloads for forward declared types

  inline Zuint& Zuint::operator= ( const Zbyte& b )   { value=(unsigned int)b.value; return *this; }
  inline Zuint& Zuint::operator= ( const Zint& i )    { value=(unsigned int)i.value; return *this; }
  inline Zuint& Zuint::operator= ( const Zfloat& f )  { value=(unsigned int)f.value; return *this; }
  inline Zuint& Zuint::operator= ( const Zdouble& d ) { value=(unsigned int)d.value; return *this; }
  inline Zuint& Zuint::operator= ( const std::string& s ) { value=(unsigned int)atof(s.c_str()); return *this; }
  inline unsigned int Zuint::operator()( Zbyte &b )   { return value=(unsigned int)b.value; }
  inline unsigned int Zuint::operator()( Zint &i )    { return value=(unsigned int)i.value; }
  inline unsigned int Zuint::operator()( Zfloat &f )  { return value=(unsigned int)f.value; }
  inline unsigned int Zuint::operator()( Zdouble &d ) { return value=(unsigned int)d.value; }

  /// Zint operator= overloads for forward declared types

  inline Zint& Zint::operator= ( const Zbyte& b )   { value=(int)b.value; return *this; }
  inline Zint& Zint::operator= ( const Zuint& i )   { value=(int)i.value; return *this; }
  inline Zint& Zint::operator= ( const Zfloat& f )  { value=(int)f.value; return *this; }
  inline Zint& Zint::operator= ( const Zdouble& d ) { value=(int)d.value; return *this; }
  inline Zint& Zint::operator= ( const std::string& s ) { value=(int)atof(s.c_str()); return *this; }
  inline int Zint::operator()( Zbyte &b )   { return (value=(int)b.value); }
  inline int Zint::operator()( Zuint &i )   { return (value=(int)i.value); }
  inline int Zint::operator()( Zfloat &f )  { return (value=(int)f.value); }
  inline int Zint::operator()( Zdouble &d ) { return (value=(int)d.value); }
  inline Zint& Zint::operator+= ( const Zfloat& f ) { value+=(int)f.value; return *this; }
  inline Zint& Zint::operator-= ( const Zfloat& f ) { value-=(int)f.value; return *this; }
  inline Zint& Zint::operator*= ( const Zfloat& f ) { value*=(int)f.value; return *this; }
  inline Zint& Zint::operator/= ( const Zfloat& f ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( (int) f.value == 0.0f ) {  
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zfloat: divide by zero in /= operation!\n");
#endif
    value=0;
    return *this;
   }
#endif
   value/=(int)f.value;
   return *this;
  }

  /// Zdouble operator= overloads for forward declared types

  inline Zdouble& Zdouble::operator= ( const Zbyte& b )   { value=(double)b.value; return *this; }
  inline Zdouble& Zdouble::operator= ( const Zuint& i )   { value=(double)i.value; return *this; }
  inline Zdouble& Zdouble::operator= ( const Zint& i )    { value=(double)i.value; return *this; }
  inline Zdouble& Zdouble::operator= ( const Zfloat& f )  { value=(double)f.value; return *this; }
  inline Zdouble& Zdouble::operator= ( const std::string& s ) { value=(double)atof(s.c_str()); return *this; }
  inline double Zdouble::operator()( Zbyte &b )  { return value=(double)b.value; }
  inline double Zdouble::operator()( Zuint &i )  { return value=(double)i.value; }
  inline double Zdouble::operator()( Zint &i )   { return value=(double)i.value; }
  inline double Zdouble::operator()( Zfloat &f ) { return value=(double)f.value; }

  /// Zfloat ////////////////////////////////////////////////////////////////////////////////////////// start

  // Mixed type operations
  inline float operator+ ( const Zfloat& a, const Zint& b ) { return (float) b.value + a.value; }
  inline float operator+ ( const Zint& a, const Zfloat& b ) { return (float) a.value + b.value; }
  inline float operator* ( const Zfloat& a, const Zint& b ) { return (float) b.value * a.value; }
  inline float operator* ( const Zint& a, const Zfloat& b ) { return (float) a.value * b.value; }

  // Zfloat and itself
  inline float operator+ ( const Zfloat& a, const Zfloat& b ) { return a.value+b.value; }
  inline float operator- ( const Zfloat& a, const Zfloat& b ) { return a.value-b.value; }
  inline float operator* ( const Zfloat& a, const Zfloat& b ) { return a.value*b.value; }
  inline float operator/ ( const Zfloat& a, const Zfloat& b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b.value == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zfloat: divide by zero in / operation!\n");
#endif
    return 0.0f;
   }
#endif
   return a.value/b.value;
  }
  /* Creates C2593 for some reason...
  inline float operator+ ( Zfloat a, Zfloat b ) { return a.value+b.value; }
  inline float operator- ( Zfloat a, Zfloat b ) { return a.value-b.value; }
  inline float operator* ( Zfloat a, Zfloat b ) { return a.value*b.value; }
  inline float operator/ ( Zfloat a, Zfloat b ) {
  #if defined(DIV_BY_ZERO_PROTECTION)
  if ( b.value == 0.0f ) {
  #if defined(DIV_BY_ZERO_REPORTING)
  OUTPUT("Zfloat: divide by zero in / operation!\n");
  #endif
  return 0.0f;
  }
  #endif
  return a.value/b.value;
  }
  */

  /// Zfloat and int

  // Casted int operations
  inline float operator+ ( const Zfloat& a, int b ) { return a.value+(float)b; }
  inline float operator- ( const Zfloat& a, int b ) { return a.value-(float)b; }
  inline float operator* ( const Zfloat& a, int b ) { return a.value*(float)b; }
  inline float operator/ ( const Zfloat& a, int b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zfloat: divide by zero in / operation!\n");
#endif
    return 0.0f;
   }
#endif
   return a.value/(float)b;
  }
  // Casted int operations reversed
  inline float operator+ ( int b, const Zfloat& a ) { return a.value+(float)b; }
  inline float operator- ( int b, const Zfloat& a ) { return (float)b-a.value; }
  inline float operator* ( int b, const Zfloat& a ) { return a.value*(float)b; }
  inline float operator/ ( int b, const Zfloat& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zfloat: divide by zero in / operation!\n");
#endif
    return 0.0f;
   }
#endif
   return (float)b/a.value;
  }

  /// Zfloat and float

  // Float operations
  inline float operator+ ( float b, const Zfloat& a ) { return a.value+b; }
  inline float operator- ( float b, const Zfloat& a ) { return b-a.value; }
  inline float operator* ( float b, const Zfloat& a ) { return a.value*b; }
  inline float operator/ ( float b, const Zfloat& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zfloat: divide by zero in / operation!\n");
#endif
    return 0.0f;
   }
#endif
   return b/a.value;
  }
  // Float operations reversed
  inline float operator+ ( const Zfloat& a, float b ) { return a.value+b; }
  inline float operator- ( const Zfloat& a, float b ) { return a.value-b; }
  inline float operator* ( const Zfloat& a, float b ) { return a.value*b; }
  inline float operator/ ( const Zfloat& a, float b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zfloat: divide by zero in / operation!\n");
#endif
    return 0.0f;
   }
#endif
   return a.value/b;
  }

  /// Zfloat and double

  // Casted double operations (leans toward double precision)
  inline float operator+ ( double b, const Zfloat& a ) { return (float)((double)a.value+b); }
  inline float operator- ( double b, const Zfloat& a ) { return (float)(b-(double)a.value); }
  inline float operator* ( double b, const Zfloat& a ) { return (float)((double)a.value*b); }
  inline float operator/ ( double b, const Zfloat& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0.0f) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zfloat: divide by zero in / operation!\n");
#endif
    return 0.0f;
   }
#endif
   return (float)(b/(double)a.value);
  }
  // Casted double operations reversed (leans toward double precision)
  inline float operator+ ( const Zfloat& a, double b ) { return (float)((double)a.value+b); }
  inline float operator- ( const Zfloat& a, double b ) { return (float)((double)a.value-b); }
  inline float operator* ( const Zfloat& a, double b ) { return (float)((double)a.value*b); }
  inline float operator/ ( const Zfloat& a, double b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0.0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zfloat: divide by zero in / operation!\n");
#endif
    return 0.0f;
   }
#endif
   return (float)((double)a.value/b);
  }

  // Zfloat boolean operations
  inline bool operator>= ( const Zfloat& a, const Zfloat& b ) { return ( a.value >= b.value );    }
  inline bool operator>= ( const Zfloat& a, const Zbyte& b ) { return ( a.value >= (float) b.value );    }
  inline bool operator>= ( const Zfloat& a, const Zushort& b ) { return ((unsigned short) a.value >= b.value ); }
  inline bool operator>= ( const Zfloat& a, const Zuint& b )   { return ((unsigned int) a.value >= b.value ); }
  inline bool operator>= ( const Zfloat& a, const Zint& b )    { return ((int) a.value >= b.value ); }
  inline bool operator>= ( const Zfloat& a, const Zdouble& b ) { return ((double) a.value >= b.value ); }
  inline bool operator>= ( const Zbyte& a, const Zfloat& b )   { return (a.value >= (unsigned char) b.value ); }
  inline bool operator>= ( const Zushort& a, const Zfloat& b ) { return (a.value >= (unsigned short) b.value ); }
  inline bool operator>= ( const Zuint& a, const Zfloat& b )   { return (a.value >= (unsigned int) b.value ); }
  inline bool operator>= ( const Zint& a, const Zfloat& b )    { return (a.value >= (int) b.value ); }
  inline bool operator>= ( const Zdouble& a, const Zfloat& b ) { return (a.value >= (double) b.value ); }
  inline bool operator>= ( const Zfloat& a, int b )           { return ( (int) a.value >= b );    }
  inline bool operator>= ( const Zfloat& a, float b )         { return ( a.value >= b );          }
  inline bool operator>= ( const Zfloat& a, double b )        { return ( (double) a.value >= b ); }
  inline bool operator>= ( int a, const Zfloat& b )           { return ( a >= (int) b.value );    }
  inline bool operator>= ( float a, const Zfloat& b )         { return ( a >= b.value );          }
  inline bool operator>= ( double a, const Zfloat& b )        { return ( a >= (double) b.value ); }
  inline bool operator== ( const Zfloat& a, const Zbyte& b )   { return ((unsigned char) a.value == b.value ); }
  inline bool operator== ( const Zfloat& a, const Zushort& b ) { return ((unsigned short) a.value == b.value ); }
  inline bool operator== ( const Zfloat& a, const Zuint& b )   { return ((unsigned int) a.value == b.value ); }
  inline bool operator== ( const Zfloat& a, const Zint& b )    { return ((int) a.value == b.value ); }
  inline bool operator== ( const Zfloat& a, const Zdouble& b ) { return ((double) a.value == b.value ); }
  inline bool operator== ( const Zbyte& a, const Zfloat& b )   { return (a.value == (unsigned char) b.value ); }
  inline bool operator== ( const Zushort& a, const Zfloat& b ) { return (a.value == (unsigned short) b.value ); }
  inline bool operator== ( const Zuint& a, const Zfloat& b )   { return (a.value == (unsigned int) b.value ); }
  inline bool operator== ( const Zint& a, const Zfloat& b )    { return (a.value == (int) b.value ); }
  inline bool operator== ( const Zdouble& a, const Zfloat& b ) { return (a.value == (double) b.value ); }
  inline bool operator== ( const Zfloat& a, const Zfloat& b ) { return ( a.value == b.value );    }
  inline bool operator== ( const Zfloat& a, int b )           { return ( (int) a.value == b );    }
  inline bool operator== ( const Zfloat& a, float b )         { return ( a.value == b );          }
  inline bool operator== ( const Zfloat& a, double b )        { return ( (double) a.value == b ); }
  inline bool operator== ( int a, const Zfloat& b )           { return ( a == (int) b.value );    }
  inline bool operator== ( float a, const Zfloat& b )         { return ( a == b.value );          }
  inline bool operator== ( double a, const Zfloat& b )        { return ( a == (double) b.value ); }
  inline bool operator!= ( const Zfloat& a, const Zfloat& b ) { return ( a.value != b.value );    }
  inline bool operator!= ( const Zfloat& a, const Zbyte& b ) { return ( a.value != (float)b.value );    }
  inline bool operator!= ( const Zfloat& a, const Zushort& b ) { return ((unsigned short) a.value != b.value ); }
  inline bool operator!= ( const Zfloat& a, const Zuint& b )   { return ((unsigned int) a.value != b.value ); }
  inline bool operator!= ( const Zfloat& a, const Zint& b )    { return ((int) a.value != b.value ); }
  inline bool operator!= ( const Zfloat& a, const Zdouble& b ) { return ((double) a.value != b.value ); }
  inline bool operator!= ( const Zbyte& a, const Zfloat& b )   { return (a.value != (unsigned char) b.value ); }
  inline bool operator!= ( const Zushort& a, const Zfloat& b ) { return (a.value != (unsigned short) b.value ); }
  inline bool operator!= ( const Zuint& a, const unsigned int b )  { return (a.value != b ); }
  inline bool operator!= ( const Zuint& a, const int b )       { return (a.value != (unsigned int) b ); }
  inline bool operator!= ( const Zuint& a, const Zfloat& b )   { return (a.value != (unsigned int) b.value ); }
  inline bool operator!= ( const Zint& a, const Zfloat& b )    { return (a.value != (int) b.value ); }
  inline bool operator!= ( const Zdouble& a, const Zfloat& b ) { return (a.value != (double) b.value ); }
  inline bool operator!= ( const Zfloat& a, int b )           { return ( (int) a.value != b );    }
  inline bool operator!= ( const Zfloat& a, float b )         { return ( a.value != b );          }
  inline bool operator!= ( const Zfloat& a, double b )        { return ( (double) a.value != b ); }
  inline bool operator!= ( int a, const Zfloat& b )           { return ( a != (int) b.value );    }
  inline bool operator!= ( float a, const Zfloat& b )         { return ( a != b.value );          }
  inline bool operator!= ( double a, const Zfloat& b )        { return ( a != (double) b.value ); }
  inline bool operator<= ( const Zfloat& a, const Zfloat& b ) { return ( a.value <= b.value );    }
  inline bool operator<= ( const Zfloat& a, const Zbyte& b )  { return ( a.value <= (float) b.value ); }
  inline bool operator<= ( const Zfloat& a, const Zushort& b ) { return ((unsigned short) a.value <= b.value ); }
  inline bool operator<= ( const Zfloat& a, const Zuint& b )   { return ((unsigned int) a.value <= b.value ); }
  inline bool operator<= ( const Zfloat& a, const Zint& b )    { return ((int) a.value <= b.value ); }
  inline bool operator<= ( const Zfloat& a, const Zdouble& b ) { return ((double) a.value <= b.value ); }
  inline bool operator<= ( const Zbyte& a, const Zfloat& b )   { return (a.value <= (unsigned char) b.value ); }
  inline bool operator<= ( const Zushort& a, const Zfloat& b ) { return (a.value <= (unsigned short) b.value ); }
  inline bool operator<= ( const Zuint& a, const Zfloat& b )   { return (a.value <= (unsigned int) b.value ); }
  inline bool operator<= ( const Zint& a, const Zfloat& b )    { return (a.value <= (int) b.value ); }
  inline bool operator<= ( const Zdouble& a, const Zfloat& b ) { return (a.value <= (double) b.value ); }
  inline bool operator<= ( const Zfloat& a, int b )           { return ( (int) a.value <= b );    }
  inline bool operator<= ( const Zfloat& a, float b )         { return ( a.value <= b );          }
  inline bool operator<= ( const Zfloat& a, double b )        { return ( (double) a.value <= b ); }
  inline bool operator<= ( int a, const Zfloat& b )           { return ( a <= (int) b.value );    }
  inline bool operator<= ( float a, const Zfloat& b )         { return ( a <= b.value );          }
  inline bool operator<= ( double a, const Zfloat& b )        { return ( a <= (double) b.value ); }
  inline bool operator> ( const Zfloat& a, const Zfloat& b )  { return ( a.value > b.value );    }
  inline bool operator> ( const Zfloat& a, const Zbyte& b )   { return ( a.value > (float) b.value ); }
  inline bool operator> ( const Zfloat& a, const Zushort& b ) { return ((unsigned short) a.value > b.value ); }
  inline bool operator> ( const Zfloat& a, const Zuint& b )   { return ((unsigned int) a.value > b.value ); }
  inline bool operator> ( const Zfloat& a, const Zint& b )    { return ((int) a.value > b.value ); }
  inline bool operator> ( const Zfloat& a, const Zdouble& b ) { return ((double) a.value > b.value ); }
  inline bool operator> ( const Zbyte& a, const Zfloat& b )   { return (a.value > (unsigned char) b.value ); }
  inline bool operator> ( const Zushort& a, const Zfloat& b ) { return (a.value > (unsigned short) b.value ); }
  inline bool operator> ( const Zuint& a, const Zfloat& b )   { return (a.value > (unsigned int) b.value ); }
  inline bool operator> ( const Zint& a, const Zfloat& b )    { return (a.value > (int) b.value ); }
  inline bool operator> ( const Zdouble& a, const Zfloat& b ) { return (a.value > (double) b.value ); }
  inline bool operator> ( const Zfloat& a, int b )            { return ( (int) a.value > b );    }
  inline bool operator> ( const Zfloat& a, float b )          { return ( a.value > b );          }
  inline bool operator> ( const Zfloat& a, double b )         { return ( (double) a.value > b ); }
  inline bool operator> ( int a, const Zfloat& b )            { return ( a > (int) b.value );    }
  inline bool operator> ( float a, const Zfloat& b )          { return ( a > b.value );          }
  inline bool operator> ( double a, const Zfloat& b )         { return ( a > (double) b.value ); }
  inline bool operator< ( const Zfloat& a, const Zfloat& b )  { return ( a.value < b.value );    }
  inline bool operator< ( const Zfloat& a, const Zbyte& b )   { return ( a.value < (float) b.value ); }
  inline bool operator< ( const Zfloat& a, const Zushort& b ) { return ((unsigned short) a.value < b.value ); }
  inline bool operator< ( const Zfloat& a, const Zuint& b )   { return ((unsigned int) a.value < b.value ); }
  inline bool operator< ( const Zfloat& a, const Zint& b )    { return ((int) a.value < b.value ); }
  inline bool operator< ( const Zfloat& a, const Zdouble& b ) { return ((double) a.value < b.value ); }
  inline bool operator< ( const Zbyte& a, const Zfloat& b )   { return (a.value < (unsigned char) b.value ); }
  inline bool operator< ( const Zushort& a, const Zfloat& b ) { return (a.value < (unsigned short) b.value ); }
  inline bool operator< ( const Zuint& a, const Zfloat& b )   { return (a.value < (unsigned int) b.value ); }
  inline bool operator< ( const Zint& a, const Zfloat& b )    { return (a.value < (int) b.value ); }
  inline bool operator< ( const Zdouble& a, const Zfloat& b ) { return (a.value < (double) b.value ); }
  inline bool operator< ( const Zfloat& a, int b )            { return ( (int) a.value < b );    }
  inline bool operator< ( const Zfloat& a, float b )          { return ( a.value < b );          }
  inline bool operator< ( const Zfloat& a, double b )         { return ( (double) a.value < b ); }
  inline bool operator< ( int a, const Zfloat& b )            { return ( a < (int) b.value );    }
  inline bool operator< ( float a, const Zfloat& b )          { return ( a < b.value );          }
  inline bool operator< ( double a, const Zfloat& b )         { return ( a < (double) b.value ); }

  /// Zfloat ////////////////////////////////////////////////////////////////////////////////////////// end

  /// Zbyte ////////////////////////////////////////////////////////////////////////////////////////// start

  inline unsigned char operator+ ( const Zbyte& a, const Zbyte& b ) { return a.value+b.value; }
  inline unsigned char operator- ( const Zbyte& a, const Zbyte& b ) { return a.value-b.value; }
  inline unsigned char operator* ( const Zbyte& a, const Zbyte& b ) { return a.value*b.value; }
  inline unsigned char operator/ ( const Zbyte& a, const Zbyte& b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zbyte: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return a.value/b.value;
  }
  inline unsigned char operator+ ( Zbyte a, Zbyte b ) { return a.value+b.value; }
  inline unsigned char operator- ( Zbyte a, Zbyte b ) { return a.value-b.value; }
  inline unsigned char operator* ( Zbyte a, Zbyte b ) { return a.value*b.value; }
  inline unsigned char operator/ ( Zbyte a, Zbyte b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zbyte: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return a.value/b.value;
  }

  /// Zbyte and uint

  // Casted int operations
  inline unsigned char operator+ ( const Zbyte& a, unsigned char b ) { return a.value+b; }
  inline unsigned char operator- ( const Zbyte& a, unsigned char b ) { return a.value-b; }
  inline unsigned char operator* ( const Zbyte& a, unsigned char b ) {
   return a.value*b;
  }
  inline unsigned char operator/ ( const Zbyte& a, unsigned char b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zbyte: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return a.value/b;
  }
  // Casted int operations reversed
  inline unsigned char operator+ ( unsigned char b, const Zbyte& a ) { return a.value+b; }
  inline unsigned char operator- ( unsigned char b, const Zbyte& a ) { return b-a.value; }
  inline unsigned char operator* ( unsigned char b, const Zbyte& a ) { return a.value*b; }
  unsigned char operator/ ( unsigned char b, const Zbyte& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zbyte: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return b/a.value;
  }

  /// Zuint and int

  // Casted int operations
  inline unsigned char operator+ ( const Zbyte& a, int b ) { return a.value+(unsigned char) b; }
  inline unsigned char operator- ( const Zbyte& a, int b ) { return a.value-(unsigned char) b; }
  inline unsigned char operator* ( const Zbyte& a, int b ) { return a.value*(unsigned char) b; }
  inline unsigned char operator/ ( const Zbyte& a, int b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zbyte: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return a.value/(unsigned char) b;
  }
  // Casted int operations reversed
  inline unsigned char operator+ ( int b, const Zbyte& a ) { return a.value+(unsigned char) b; }
  inline unsigned char operator- ( int b, const Zbyte& a ) { return (unsigned char) b-a.value; }
  inline unsigned char operator* ( int b, const Zbyte& a ) { return a.value*(unsigned char) b; }
  inline unsigned char operator/ ( int b, const Zbyte& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zbyte: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return (unsigned char) b/a.value;
  }

  /// Zbyte and float

  // Float operations (leans toward float precision)
  inline unsigned char operator+ ( float b, const Zbyte& a ) { return (unsigned char)((float)a.value+b); }
  inline unsigned char operator- ( float b, const Zbyte& a ) { return (unsigned char)(b-(float)a.value); }
  inline unsigned char operator* ( float b, const Zbyte& a ) { return (unsigned char)((float)a.value*b); }
  inline unsigned char operator/ ( float b, const Zbyte& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zbyte: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return (unsigned char)(b/(float)a.value);
  }
  // Float operations reversed (leans toward float precision)
  inline unsigned char operator+ ( const Zbyte& a, float b ) { return (unsigned char)((float)a.value+b); }
  inline unsigned char operator- ( const Zbyte& a, float b ) { return (unsigned char)((float)a.value-b); }
  inline unsigned char operator* ( const Zbyte& a, float b ) { return (unsigned char)((float)a.value*b); }
  inline unsigned char operator/ ( const Zbyte& a, float b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zbyte: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif

   return (unsigned char)((float)a.value/b);
  }

  /// Zbyte and double

  // Casted double operations (leans toward double precision)
  inline unsigned char operator+ ( double b, const Zbyte& a ) { return (unsigned char)((double)a.value+b); }
  inline unsigned char operator- ( double b, const Zbyte& a ) { return (unsigned char)(b-(double)a.value); }
  inline unsigned char operator* ( double b, const Zbyte& a ) { return (unsigned char)((double)a.value*b); }
  inline unsigned char operator/ ( double b, const Zbyte& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zbyte: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return (unsigned char)(b/(double)a.value);
  }
  // Casted double operations reversed (leans toward double precision)
  inline unsigned char operator+ ( const Zbyte& a, double b ) { return (unsigned char)((double)a.value+b); }
  inline unsigned char operator- ( const Zbyte& a, double b ) { return (unsigned char)((double)a.value-b); }
  inline unsigned char operator* ( const Zbyte& a, double b ) { return (unsigned char)((double)a.value*b); }
  inline unsigned char operator/ ( const Zbyte& a, double b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0.0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zbyte: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return (unsigned char)((double)a.value/b);
  }


  // Boolean operations
  inline bool operator>= ( const Zbyte& a, const Zbyte& b ) { return ( a.value >= b.value );    }
  inline bool operator>= ( const Zbyte& a, int b )            { return ( a.value >= (unsigned char) b ); }
  inline bool operator>= ( const Zbyte& a, float b )          { return ( a.value >= (unsigned char) b ); }
  inline bool operator>= ( const Zbyte& a, double b )         { return ( a.value >= (unsigned char) b ); }
  inline bool operator>= ( int a, const Zbyte& b )            { return ( (unsigned char) a >= b.value ); }
  inline bool operator>= ( float a, const Zbyte& b )          { return ( (unsigned char) a >= b.value ); }
  inline bool operator>= ( double a, const Zbyte& b )         { return ( (unsigned char) a >= b.value ); }
  inline bool operator== ( const Zbyte& a, const Zbyte& b ) { return ( a.value == b.value );    }
  inline bool operator== ( const Zbyte& a, int b )            { return ( a.value == (unsigned char) b ); }
  inline bool operator== ( const Zbyte& a, float b )          { return ( a.value == (unsigned char) b ); }
  inline bool operator== ( const Zbyte& a, double b )         { return ( a.value == (unsigned char) b ); }
  inline bool operator== ( int a, const Zbyte& b )            { return ( (unsigned char) a == b.value ); }
  inline bool operator== ( float a, const Zbyte& b )          { return ( (unsigned char) a == b.value ); }
  inline bool operator== ( double a, const Zbyte& b )         { return ( (unsigned char) a == b.value ); }
  inline bool operator!= ( const Zbyte& a, const Zbyte& b ) { return ( a.value != b.value );    }
  inline bool operator!= ( const Zbyte& a, int b )            { return ( a.value != (unsigned char) b ); }
  inline bool operator!= ( const Zbyte& a, float b )          { return ( a.value != (unsigned char) b ); }
  inline bool operator!= ( const Zbyte& a, double b )         { return ( a.value != (unsigned char) b ); }
  inline bool operator!= ( int a, const Zbyte& b )            { return ( (unsigned char) a != b.value ); }
  inline bool operator!= ( float a, const Zbyte& b )          { return ( (unsigned char) a != b.value ); }
  inline bool operator!= ( double a, const Zbyte& b )         { return ( (unsigned char) a != b.value ); }
  inline bool operator<= ( const Zbyte& a, const Zbyte& b ) { return ( a.value <= b.value );    }
  inline bool operator<= ( const Zbyte& a, int b )            { return ( a.value <= (unsigned char) b ); }
  inline bool operator<= ( const Zbyte& a, float b )          { return ( a.value <= (unsigned char) b ); }
  inline bool operator<= ( const Zbyte& a, double b )         { return ( a.value <= (unsigned char) b ); }
  inline bool operator<= ( int a, const Zbyte& b )            { return ( (unsigned char) a <= b.value ); }
  inline bool operator<= ( float a, const Zbyte& b )          { return ( (unsigned char) a <= b.value ); }
  inline bool operator<= ( double a, const Zbyte& b )         { return ( (unsigned char) a <= b.value ); }
  inline bool operator> ( const Zbyte& a, const Zbyte& b )  { return ( a.value > b.value );    }
  inline bool operator> ( const Zbyte& a, int b )             { return ( a.value > (unsigned char) b ); }
  inline bool operator> ( const Zbyte& a, float b )           { return ( a.value > (unsigned char) b ); }
  inline bool operator> ( const Zbyte& a, double b )          { return ( a.value > (unsigned char) b ); }
  inline bool operator> ( int a, const Zbyte& b )             { return ( (unsigned char) a > b.value ); }
  inline bool operator> ( float a, const Zbyte& b )           { return ( (unsigned char) a > b.value ); }
  inline bool operator> ( double a, const Zbyte& b )          { return ( (unsigned char) a > b.value ); }
  inline bool operator< ( const Zbyte& a, const Zbyte& b )  { return ( a.value < b.value );    }
  inline bool operator< ( const Zbyte& a, int b )             { return ( a.value < (unsigned char) b ); }
  inline bool operator< ( const Zbyte& a, float b )           { return ( a.value < (unsigned char) b ); }
  inline bool operator< ( const Zbyte& a, double b )          { return ( a.value < (unsigned char) b ); }
  inline bool operator< ( int a, const Zbyte& b )             { return ( (unsigned char) a < b.value ); }
  inline bool operator< ( float a, const Zbyte& b )           { return ( (unsigned char) a < b.value ); }
  inline bool operator< ( double a, const Zbyte& b )          { return ( (unsigned char) a < b.value ); }

  /// Zbyte ////////////////////////////////////////////////////////////////////////////////////////// end


  /// Zushort ////////////////////////////////////////////////////////////////////////////////////////// start

  inline unsigned short operator+ ( const Zushort& a, const Zushort& b ) { return a.value+b.value; }
  inline unsigned short operator- ( const Zushort& a, const Zushort& b ) { return a.value-b.value; }
  inline unsigned short operator* ( const Zushort& a, const Zushort& b ) { return a.value*b.value; }
  inline unsigned short operator/ ( const Zushort& a, const Zushort& b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zushort: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return a.value/b.value;
  }
  inline unsigned short operator+ ( Zushort a, Zushort b ) { return a.value+b.value; }
  inline unsigned short operator- ( Zushort a, Zushort b ) { return a.value-b.value; }
  inline unsigned short operator* ( Zushort a, Zushort b ) { return a.value*b.value; }
  inline unsigned short operator/ ( Zushort a, Zushort b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zushort: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return a.value/b.value;
  }

  inline unsigned short operator+ ( const Zushort& a, unsigned char b ) { return a.value+b; }
  inline unsigned short operator- ( const Zushort& a, unsigned char b ) { return a.value-b; }
  inline unsigned short operator* ( const Zushort& a, unsigned char b ) { return a.value*b; }
  inline unsigned short operator/ ( const Zushort& a, unsigned char b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zushort: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return a.value/b;
  }
  inline unsigned short operator+ ( unsigned char b, const Zushort& a ) { return b+a.value; }
  inline unsigned short operator- ( unsigned char b, const Zushort& a ) { return b-a.value; }
  inline unsigned short operator* ( unsigned char b, const Zushort& a ) { return b*a.value; }
  inline unsigned short operator/ ( unsigned char b, const Zushort& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zushort: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return b/a.value;
  }

  /// Zbyte and uint

  // Casted int operations
  inline unsigned short operator+ ( const Zushort& a, unsigned short b ) { return a.value+b; }
  inline unsigned short operator- ( const Zushort& a, unsigned short b ) { return a.value-b; }
  inline unsigned short operator* ( const Zushort& a, unsigned short b ) { return a.value*b; }
  inline unsigned short operator/ ( const Zushort& a, unsigned short b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zushort: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return a.value/b;
  }
  // Casted int operations reversed
  inline unsigned short operator+ ( unsigned short b, const Zushort& a ) { return a.value+b; }
  inline unsigned short operator- ( unsigned short b, const Zushort& a ) { return b-a.value; }
  inline unsigned short operator* ( unsigned short b, const Zushort& a ) { return a.value*b; }
  inline unsigned short operator/ ( unsigned short b, const Zushort& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zushort: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return b/a.value;
  }

  /// Zushort and int

  // Casted int operations
  inline unsigned short operator+ ( const Zushort& a, int b ) { return a.value+(unsigned short) b; }
  inline unsigned short operator- ( const Zushort& a, int b ) { return a.value-(unsigned short) b; }
  inline unsigned short operator* ( const Zushort& a, int b ) { return a.value*(unsigned short) b; }
  inline unsigned short operator/ ( const Zushort& a, int b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zushort: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return a.value/(unsigned short) b;
  }
  // Casted int operations reversed
  inline unsigned short operator+ ( int b, const Zushort& a ) { return a.value+(unsigned short) b; }
  inline unsigned short operator- ( int b, const Zushort& a ) { return (unsigned short) b-a.value; }
  inline unsigned short operator* ( int b, const Zushort& a ) { return a.value*(unsigned short) b; }
  inline unsigned short operator/ ( int b, const Zushort& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zushort: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return (unsigned short) b/a.value;
  }

  /// Zbyte and float

  // Float operations (leans toward float precision)
  inline unsigned short operator+ ( float b, const Zushort& a ) { return (unsigned short)((float)a.value+b); }
  inline unsigned short operator- ( float b, const Zushort& a ) { return (unsigned short)(b-(float)a.value); }
  inline unsigned short operator* ( float b, const Zushort& a ) { return (unsigned short)((float)a.value*b); }
  inline unsigned short operator/ ( float b, const Zushort& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zushort: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return (unsigned char)(b/(float)a.value);
  }
  // Float operations reversed (leans toward float precision)
  inline unsigned short operator+ ( const Zushort& a, float b ) { return (unsigned short)((float)a.value+b); }
  inline unsigned short operator- ( const Zushort& a, float b ) { return (unsigned short)((float)a.value-b); }
  inline unsigned short operator* ( const Zushort& a, float b ) { return (unsigned short)((float)a.value*b); }
  inline unsigned short operator/ ( const Zushort& a, float b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zushort: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif

   return (unsigned short)((float)a.value/b);
  }

  /// Zbyte and double

  // Casted double operations (leans toward double precision)
  inline unsigned short operator+ ( double b, const Zushort& a ) { return (unsigned short)((double)a.value+b); }
  inline unsigned short operator- ( double b, const Zushort& a ) { return (unsigned short)(b-(double)a.value); }
  inline unsigned short operator* ( double b, const Zushort& a ) { return (unsigned short)((double)a.value*b); }
  inline unsigned short operator/ ( double b, const Zushort& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zushort: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return (unsigned short)(b/(double)a.value);
  }
  // Casted double operations reversed (leans toward double precision)
  inline unsigned short operator+ ( const Zushort& a, double b ) { return (unsigned short)((double)a.value+b); }
  inline unsigned short operator- ( const Zushort& a, double b ) { return (unsigned short)((double)a.value-b); }
  inline unsigned short operator* ( const Zushort& a, double b ) { return (unsigned short)((double)a.value*b); }
  inline unsigned short operator/ ( const Zushort& a, double b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0.0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zbyte: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return (unsigned short)((double)a.value/b);
  }

  /// Zushort ////////////////////////////////////////////////////////////////////////////////////////// end

  /// Zint ////////////////////////////////////////////////////////////////////////////////////////// start

  inline int operator+ ( const Zint& a, const Zint& b ) { return a.value+b.value; }
  inline int operator- ( const Zint& a, const Zint& b ) { return a.value-b.value; }
  inline int operator* ( const Zint& a, const Zint& b ) { return a.value*b.value; }
  inline int operator/ ( const Zint& a, const Zint& b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zint: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return a.value/b.value;
  }
  /* Creates C2593 for some reason...
  int operator+ ( Zint a, Zint b ) { return a.value+b.value; }
  int operator- ( Zint a, Zint b ) { return a.value-b.value; }
  int operator* ( Zint a, Zint b ) { return a.value*b.value; }
  int operator/ ( Zint a, Zint b ) {
  #if defined(DIV_BY_ZERO_PROTECTION)
  if ( b.value == 0 ) {
  #if defined(DIV_BY_ZERO_REPORTING)
  OUTPUT("Zint: divide by zero in / operation!\n");
  #endif
  return 0;
  }
  #endif
  return a.value/b.value;
  }
  */

  /// Zint and int

  // Casted int operations
  inline int operator+ ( const Zint& a, int b ) { return a.value+b; }
  inline int operator- ( const Zint& a, int b ) { return a.value-b; }
  inline int operator* ( const Zint& a, int b ) { return a.value*b; }
  inline int operator/ ( const Zint& a, int b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zint: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return a.value/b;
  }
  int operator% ( const Zint& a, int b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zint: modulo by zero in %% operation!\n");
#endif
    return 0;
   }
#endif
   return a.value%b;
  }
  // Casted int operations reversed
  inline int operator+ ( int b, const Zint& a ) { return a.value+b; }
  inline int operator- ( int b, const Zint& a ) { return b-a.value; }
  inline int operator* ( int b, const Zint& a ) { return a.value*b; }
  inline int operator/ ( int b, const Zint& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zint: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return b/a.value;
  }
  int operator% ( int b, const Zint& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zint: modulo by zero in %% operation!\n");
#endif
    return 0;
   }
#endif
   return b%a.value;
  }

  /// Zint and float

  // Float operations (leans toward float precision)
  inline int operator+ ( float b, const Zint& a ) { return (int)((float)a.value+b); }
  inline int operator- ( float b, const Zint& a ) { return (int)(b-(float)a.value); }
  inline int operator* ( float b, const Zint& a ) { return (int)((float)a.value*b); }
  inline int operator/ ( float b, const Zint& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zint: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return (int)(b/(float)a.value);
  }
  // Float operations reversed (leans toward float precision)
  inline int operator+ ( const Zint& a, float b ) { return (int)((float)a.value+b); }
  inline int operator- ( const Zint& a, float b ) { return (int)((float)a.value-b); }
  inline int operator* ( const Zint& a, float b ) { return (int)((float)a.value*b); }
  inline int operator/ ( const Zint& a, float b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zint: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif

   return (int)((float)a.value/b);
  }

  /// Zint and double

  // Casted double operations (leans toward double precision)
  inline int operator+ ( double b, const Zint& a ) { return (int)((double)a.value+b); }
  inline int operator- ( double b, const Zint& a ) { return (int)(b-(double)a.value); }
  inline int operator* ( double b, const Zint& a ) { return (int)((double)a.value*b); }
  inline int operator/ ( double b, const Zint& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zint: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return (int)(b/(double)a.value);
  }
  // Casted double operations reversed (leans toward double precision)
  inline int operator+ ( const Zint& a, double b ) { return (int)((double)a.value+b); }
  inline int operator- ( const Zint& a, double b ) { return (int)((double)a.value-b); }
  inline int operator* ( const Zint& a, double b ) { return (int)((double)a.value*b); }
  inline int operator/ ( const Zint& a, double b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0.0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zint: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return (int)((double)a.value/b);
  }

  // Modulo

  inline int operator% ( const Zint& b, const Zint& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zint: modulo by zero in %% operation!\n");
#endif
    return 0;
   }
#endif
   return b.value%a.value;
  }

  // Zint boolean operations
  inline bool operator>= ( const Zint& a, const Zint& b ) { return ( a.value >= b.value ); }
  inline bool operator>= ( const Zint& a, unsigned int b ) { return ( (unsigned int) a.value >= b ); }
  inline bool operator>= ( const Zint& a, int b )         { return ( a.value >= b );       }
  inline bool operator>= ( const Zint& a, float b )       { return ( a.value >= (int) b ); }
  inline bool operator>= ( const Zint& a, double b )      { return ( a.value >= (int) b ); }
  inline bool operator>= ( unsigned int a, const Zint& b ) { return ( a >= (unsigned int) b.value ); }
  inline bool operator>= ( int a, const Zint& b )         { return ( a >= b.value );       }
  inline bool operator>= ( float a, const Zint& b )       { return ( (int) a >= b.value ); }
  inline bool operator>= ( double a, const Zint& b )      { return ( (int) a >= b.value ); }
  inline bool operator== ( const Zint& a, const Zbyte& b )   { return ((unsigned char) a.value == b.value ); }
  inline bool operator== ( const Zint& a, const Zushort& b ) { return ((unsigned short) a.value == b.value ); }
  inline bool operator== ( const Zint& a, const Zuint& b )   { return ((unsigned int) a.value == b.value ); }
  inline bool operator== ( const Zint& a, const Zdouble& b ) { return ((double) a.value == b.value ); }
  inline bool operator== ( const Zbyte& a, const Zint& b )   { return (a.value == (unsigned char) b.value ); }
  inline bool operator== ( const Zushort& a, const Zint& b ) { return (a.value == (unsigned short) b.value ); }
  inline bool operator== ( const Zuint& a, const Zint& b )   { return (a.value == (unsigned int) b.value ); }
  inline bool operator== ( const Zdouble& a, const Zint& b ) { return (a.value == (double) b.value ); }
  inline bool operator== ( const Zint& a, const Zint& b ) { return ( a.value == b.value ); }
  inline bool operator== ( const Zint& a, unsigned int b ) { return ( (unsigned int) a.value >= b ); }
  inline bool operator== ( const Zint& a, int b )         { return ( a.value == b );       }
  inline bool operator== ( const Zint& a, float b )       { return ( a.value == (int) b ); }
  inline bool operator== ( const Zint& a, double b )      { return ( a.value == (int) b ); }
  inline bool operator== ( unsigned int a, const Zint& b ) { return ( a == (unsigned int) b.value ); }
  inline bool operator== ( int a, const Zint& b )         { return ( a == b.value );       }
  inline bool operator== ( float a, const Zint& b )       { return ( (int) a == b.value ); }
  inline bool operator== ( double a, const Zint& b )      { return ( (int) a == b.value ); }
  inline bool operator!= ( const Zint& a, const Zint& b ) { return ( a.value != b.value ); }
  inline bool operator!= ( const Zint& a, unsigned int b ) { return ( (unsigned int) a.value != b ); }
  inline bool operator!= ( const Zint& a, int b )         { return ( a.value != b );       }
  inline bool operator!= ( const Zint& a, float b )       { return ( a.value != (int) b ); }
  inline bool operator!= ( const Zint& a, double b )      { return ( a.value != (int) b ); }
  inline bool operator!= ( unsigned int a, const Zint& b ) { return ( a != (unsigned int) b.value ); }
  inline bool operator!= ( int a, const Zint& b )         { return ( a != b.value );       }
  inline bool operator!= ( float a, const Zint& b )       { return ( (int) a != b.value ); }
  inline bool operator!= ( double a, const Zint& b )      { return ( (int) a != b.value ); }
  inline bool operator<= ( const Zint& a, const Zint& b ) { return ( a.value <= b.value ); }
  inline bool operator<= ( const Zint& a, unsigned int b ) { return ( (unsigned int) a.value <= b ); }
  inline bool operator<= ( const Zint& a, int b )         { return ( a.value <= b );       }
  inline bool operator<= ( const Zint& a, float b )       { return ( a.value <= (int) b ); }
  inline bool operator<= ( const Zint& a, double b )      { return ( a.value <= (int) b ); }
  inline bool operator<= ( unsigned int a, const Zint& b ) { return ( a <= (unsigned int) b.value ); }
  inline bool operator<= ( int a, const Zint& b )         { return ( a <= b.value );       }
  inline bool operator<= ( float a, const Zint& b )       { return ( (int) a <= b.value ); }
  inline bool operator<= ( double a, const Zint& b )      { return ( (int) a <= b.value ); }
  inline bool operator> ( const Zint& a, const Zint& b )  { return ( a.value > b.value ); }
  inline bool operator> ( const Zint& a, unsigned int b ) { return ( (unsigned int) a.value > b ); }
  inline bool operator> ( const Zint& a, int b )          { return ( a.value > b );       }
  inline bool operator> ( const Zint& a, float b )        { return ( a.value > (int) b ); }
  inline bool operator> ( const Zint& a, double b )       { return ( a.value > (int) b ); }
  inline bool operator> ( unsigned int a, const Zint& b ) { return ( a > (unsigned int) b.value ); }
  inline bool operator> ( int a, const Zint& b )          { return ( a > b.value );       }
  inline bool operator> ( float a, const Zint& b )        { return ( (int) a > b.value ); }
  inline bool operator> ( double a, const Zint& b )       { return ( (int) a > b.value ); }
  inline bool operator< ( const Zint& a, const Zint& b )  { return ( a.value < b.value ); }
  inline bool operator< ( const Zint& a, unsigned int b ) { return ( (unsigned int) a.value < b ); }
  inline bool operator< ( const Zint& a, int b )          { return ( a.value < b );       }
  inline bool operator< ( const Zint& a, float b )        { return ( a.value < (int) b ); }
  inline bool operator< ( const Zint& a, double b )       { return ( a.value < (int) b ); }
  inline bool operator< ( unsigned int a, const Zint& b ) { return ( a < (unsigned int) b.value ); }
  inline bool operator< ( int a, const Zint& b )          { return ( a < b.value );       }
  inline bool operator< ( float a, const Zint& b )        { return ( (int) a < b.value ); }
  inline bool operator< ( double a, const Zint& b )       { return ( (int) a < b.value ); }

  /// Zint ////////////////////////////////////////////////////////////////////////////////////////// end

  /// Zuint ////////////////////////////////////////////////////////////////////////////////////////// start

  inline unsigned int operator+ ( const Zuint& a, const Zuint& b ) {
   return a.value+b.value;
  }
  inline unsigned int operator- ( const Zuint& a, const Zuint& b ) {
   return a.value-b.value;
  }
  inline unsigned int operator* ( const Zuint& a, const Zuint& b ) {
   return a.value*b.value;
  }
  inline unsigned int operator/ ( const Zuint& a, const Zuint& b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zuint: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return a.value/b.value;
  }

  /// Zuint and uint

  // Casted int operations
  inline unsigned int operator+ ( const Zuint& a, unsigned int b ) {
   return a.value+b;
  }
  inline unsigned int operator- ( const Zuint& a, unsigned int b ) {
   return a.value-b;
  }
  inline unsigned int operator* ( const Zuint& a, unsigned int b ) {
   return a.value*b;
  }
  inline unsigned int operator/ ( const Zuint& a, unsigned int b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zuint: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return a.value/b;
  }
  inline bool operator< ( unsigned int a, const Zuint& b ) { return ( a < b.value ); }
  // Casted int operations reversed
  inline unsigned int operator+ ( unsigned int b, const Zuint& a ) {
   return a.value+b;
  }
  inline unsigned int operator- ( unsigned int b, const Zuint& a ) {
   return b-a.value;
  }
  inline unsigned int operator* ( unsigned int b, const Zuint& a ) {
   return a.value*b;
  }
  inline unsigned int operator/ ( unsigned int b, const Zuint& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zuint: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return b/a.value;
  }

  /// Zuint and int

  // Casted int operations
  inline unsigned int operator+ ( const Zuint& a, int b ) {
   return a.value+(unsigned int) b;
  }
  inline unsigned int operator- ( const Zuint& a, int b ) {
   return a.value-(unsigned int) b;
  }
  inline unsigned int operator* ( const Zuint& a, int b ) {
   return a.value*(unsigned int) b;
  }
  inline unsigned int operator/ ( const Zuint& a, int b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zuint: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return a.value/(unsigned int) b;
  }
  // Casted int operations reversed
  inline unsigned int operator+ ( int b, const Zuint& a ) {
   return a.value+(unsigned int) b;
  }
  inline unsigned int operator- ( int b, const Zuint& a ) {
   return (unsigned int) b-a.value;
  }
  inline unsigned int operator* ( int b, const Zuint& a ) {
   return a.value*(unsigned int) b;
  }
  inline unsigned int operator/ ( int b, const Zuint& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zuint: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return (unsigned int) b/a.value;
  }

  /// Zuint and float

  // Float operations (leans toward float precision)
  inline unsigned int operator+ ( float b, const Zuint& a ) {
   return (unsigned int)((float)a.value+b);
  }
  inline unsigned int operator- ( float b, const Zuint& a ) {
   return (unsigned int)(b-(float)a.value);
  }
  inline unsigned int operator* ( float b, const Zuint& a ) {
   return (unsigned int)((float)a.value*b);
  }
  inline unsigned int operator/ ( float b, const Zuint& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zuint: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return (unsigned int)(b/(float)a.value);
  }
  // Float operations reversed (leans toward float precision)
  inline unsigned int operator+ ( const Zuint& a, float b ) {
   return (unsigned int)((float)a.value+b);
  }
  inline unsigned int operator- ( const Zuint& a, float b ) {
   return (unsigned int)((float)a.value-b);
  }
  inline unsigned int operator* ( const Zuint& a, float b ) {
   return (unsigned int)((float)a.value*b);
  }
  inline unsigned int operator/ ( const Zuint& a, float b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zuint: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif

   return (unsigned int)((float)a.value/b);
  }

  /// Zuint and double

  // Casted double operations (leans toward double precision)
  inline unsigned int operator+ ( double b, const Zuint& a ) {
   return (unsigned int)((double)a.value+b);
  }
  inline unsigned int operator- ( double b, const Zuint& a ) {
   return (unsigned int)(b-(double)a.value);
  }
  inline unsigned int operator* ( double b, const Zuint& a ) {
   return (unsigned int)((double)a.value*b);
  }
  inline unsigned int operator/ ( double b, const Zuint& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zuint: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return (unsigned int)(b/(double)a.value);
  }
  // Casted double operations reversed (leans toward double precision)
  inline unsigned int operator+ ( const Zuint& a, double b ) {
   return (unsigned int)((double)a.value+b);
  }
  inline unsigned int operator- ( const Zuint& a, double b ) {
   return (unsigned int)((double)a.value-b);
  }
  inline unsigned int operator* ( const Zuint& a, double b ) {
   return (unsigned int)((double)a.value*b);
  }
  inline unsigned int operator/ ( const Zuint& a, double b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0.0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zuint: divide by zero in / operation!\n");
#endif
    return 0;
   }
#endif
   return (unsigned int)((double)a.value/b);
  }

  /// Zuint ////////////////////////////////////////////////////////////////////////////////////////// end

  /// Zdouble ////////////////////////////////////////////////////////////////////////////////////////// start

  // Mixed type operations
  inline double operator+ ( const Zdouble& a, const Zfloat& b ) { return a.value + (double) b.value; }
  inline double operator+ ( const Zfloat& a, const Zdouble& b ) { return (double) a.value + b.value; }
  inline double operator+ ( const Zdouble& a, const Zint& b )   { return a.value + (double) b.value; }
  inline double operator+ ( const Zint& a, const Zdouble& b )   { return (double) a.value + b.value; }
  inline double operator* ( const Zdouble& a, const Zfloat& b ) { return a.value * (double) b.value; }
  inline double operator* ( const Zfloat& a, const Zdouble& b ) { return (double) a.value * b.value; }
  inline double operator* ( const Zdouble& a, const Zint& b )   { return a.value * (double) b.value; }
  inline double operator* ( const Zint& a, const Zdouble& b )   { return (double) a.value * b.value; }
  // Zdouble and itself
  inline double operator+ ( const Zdouble& a, const Zdouble& b ) { return a.value+b.value; }
  inline double operator- ( const Zdouble& a, const Zdouble& b ) { return a.value-b.value; }
  inline double operator* ( const Zdouble& a, const Zdouble& b ) { return a.value*b.value; }
  inline double operator/ ( const Zdouble& a, const Zdouble& b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b.value == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zdouble: divide by zero in / operation!\n");
#endif
    return 0.0f;
   }
#endif
   return a.value/b.value;
  }
  /* Creates C2593 for some reason...
  double operator+ ( Zdouble a, Zdouble b ) { return a.value+b.value; }
  double operator- ( Zdouble a, Zdouble b ) { return a.value-b.value; }
  double operator* ( Zdouble a, Zdouble b ) { return a.value*b.value; }
  double operator/ ( Zdouble a, Zdouble b ) {
  #if defined(DIV_BY_ZERO_PROTECTION)
  if ( b.value == 0.0f ) {
  #if defined(DIV_BY_ZERO_REPORTING)
  OUTPUT("Zdouble: divide by zero in / operation!\n");
  #endif
  return 0.0f;
  }
  #endif
  return a.value/b.value;
  }
  */

  /// Zdouble and int

  // Casted int operations (leans toward double precision)
  inline double operator+ ( const Zdouble& a, int b ) { return a.value+(double)b; }
  inline double operator- ( const Zdouble& a, int b ) { return a.value-(double)b; }
  inline double operator* ( const Zdouble& a, int b ) { return a.value*(double)b; }
  inline double operator/ ( const Zdouble& a, int b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zdouble: divide by zero in / operation!\n");
#endif
    return 0.0;
   }
#endif
   return a.value/(double)b;
  }
  // Casted int operations reversed (leans toward double precision)
  inline double operator+ ( int b, const Zdouble& a ) { return a.value+(double)b; }
  inline double operator- ( int b, const Zdouble& a ) { return (double)b-a.value; }
  inline double operator* ( int b, const Zdouble& a ) { return a.value*(double)b; }
  inline double operator/ ( int b, const Zdouble& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0.0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zdouble: divide by zero in / operation!\n");
#endif
    return 0.0;
   }
#endif
   return (double)b/a.value;
  }

  /// Zdouble and float

  // Float operations (leans toward float precision)
  inline double operator+ ( float b, const Zdouble& a ) { return a.value+(double)b; }
  inline double operator- ( float b, const Zdouble& a ) { return (double)b-a.value; }
  inline double operator* ( float b, const Zdouble& a ) { return a.value*(double)b; }
  inline double operator/ ( float b, const Zdouble& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0.0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zdouble: divide by zero in / operation!\n");
#endif
    return 0.0;
   }
#endif
   return (double)b/a.value;
  }
  // Float operations reversed (leans toward float precision)
  inline double operator+ ( const Zdouble& a, float b ) { return a.value+(double)b; }
  inline double operator- ( const Zdouble& a, float b ) { return a.value-(double)b; }
  inline double operator* ( const Zdouble& a, float b ) { return a.value*(double)b; }
  inline double operator/ ( const Zdouble& a, float b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zdouble: divide by zero in / operation!\n");
#endif
    return 0.0;
   }
#endif

   return a.value/(double)b;
  }

  /// Zdouble and double

  // Casted double operations
  inline double operator+ ( double b, const Zdouble& a ) { return a.value+b; }
  inline double operator- ( double b, const Zdouble& a ) { return b-a.value; }
  inline double operator* ( double b, const Zdouble& a ) { return a.value*b; }
  inline double operator/ ( double b, const Zdouble& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( a.value == 0.0) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zdouble: divide by zero in / operation!\n");
#endif
    return 0.0;
   }
#endif
   return b/a.value;
  }
  // Casted double operations reversed
  inline double operator+ ( const Zdouble& a, double b ) { return a.value+b; }
  inline double operator- ( const Zdouble& a, double b ) { return a.value-b; }
  inline double operator* ( const Zdouble& a, double b ) { return a.value*b; }
  inline double operator/ ( const Zdouble& a, double b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
   if ( b == 0.0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
    OUTPUT("Zdouble: divide by zero in / operation!\n");
#endif
    return 0.0;
   }
#endif
   return a.value/b;
  }

  // Boolean operations
  inline bool operator>= ( const Zdouble& a, const Zdouble& b ) { return ( a.value >= b.value );    }
  inline bool operator>= ( const Zdouble& a, int b )            { return ( a.value >= (double) b ); }
  inline bool operator>= ( const Zdouble& a, float b )          { return ( a.value >= (double) b ); }
  inline bool operator>= ( const Zdouble& a, double b )         { return ( a.value >= b );          }
  inline bool operator>= ( int a, const Zdouble& b )            { return ( (double) a >= b.value ); }
  inline bool operator>= ( float a, const Zdouble& b )          { return ( (double) a >= b.value ); }
  inline bool operator>= ( double a, const Zdouble& b )         { return ( a >= b.value );          }
  inline bool operator== ( const Zdouble& a, const Zdouble& b ) { return ( a.value == b.value );    }
  inline bool operator== ( const Zdouble& a, int b )            { return ( a.value == (double) b ); }
  inline bool operator== ( const Zdouble& a, float b )          { return ( a.value == (double) b ); }
  inline bool operator== ( const Zdouble& a, double b )         { return ( a.value == b );          }
  inline bool operator== ( int a, const Zdouble& b )            { return ( (double) a == b.value ); }
  inline bool operator== ( float a, const Zdouble& b )          { return ( (double) a == b.value ); }
  inline bool operator== ( double a, const Zdouble& b )         { return ( a == b.value );          }
  inline bool operator!= ( const Zdouble& a, const Zdouble& b ) { return ( a.value != b.value );    }
  inline bool operator!= ( const Zdouble& a, int b )            { return ( a.value != (double) b ); }
  inline bool operator!= ( const Zdouble& a, float b )          { return ( a.value != (double) b ); }
  inline bool operator!= ( const Zdouble& a, double b )         { return ( a.value != b );          }
  inline bool operator!= ( int a, const Zdouble& b )            { return ( (double) a != b.value ); }
  inline bool operator!= ( float a, const Zdouble& b )          { return ( (double) a != b.value ); }
  inline bool operator!= ( double a, const Zdouble& b )         { return ( a != b.value );          }
  inline bool operator<= ( const Zdouble& a, const Zdouble& b ) { return ( a.value <= b.value );    }
  inline bool operator<= ( const Zdouble& a, int b )            { return ( a.value <= (double) b ); }
  inline bool operator<= ( const Zdouble& a, float b )          { return ( a.value <= (double) b ); }
  inline bool operator<= ( const Zdouble& a, double b )         { return ( a.value <= b );          }
  inline bool operator<= ( int a, const Zdouble& b )            { return ( (double) a <= b.value ); }
  inline bool operator<= ( float a, const Zdouble& b )          { return ( (double) a <= b.value ); }
  inline bool operator<= ( double a, const Zdouble& b )         { return ( a <= b.value );          }
  inline bool operator> ( const Zdouble& a, const Zdouble& b )  { return ( a.value > b.value );    }
  inline bool operator> ( const Zdouble& a, int b )             { return ( a.value > (double) b ); }
  inline bool operator> ( const Zdouble& a, float b )           { return ( a.value > (double) b ); }
  inline bool operator> ( const Zdouble& a, double b )          { return ( a.value > b );          }
  inline bool operator> ( int a, const Zdouble& b )             { return ( (double) a > b.value ); }
  inline bool operator> ( float a, const Zdouble& b )           { return ( (double) a > b.value ); }
  inline bool operator> ( double a, const Zdouble& b )          { return ( a > b.value );          }
  inline bool operator< ( const Zdouble& a, const Zdouble& b )  { return ( a.value < b.value );    }
  inline bool operator< ( const Zdouble& a, int b )             { return ( a.value < (double) b ); }
  inline bool operator< ( const Zdouble& a, float b )           { return ( a.value < (double) b ); }
  inline bool operator< ( const Zdouble& a, double b )          { return ( a.value < b );          }
  inline bool operator< ( int a, const Zdouble& b )             { return ( (double) a < b.value ); }
  inline bool operator< ( float a, const Zdouble& b )           { return ( (double) a < b.value ); }
  inline bool operator< ( double a, const Zdouble& b )          { return ( a < b.value );          }

  /// Zdouble ////////////////////////////////////////////////////////////////////////////////////////// end



  /// Zstring (UTF-8) ////////////////////////////////////////////////////////////////////////////////////////// end

#define FORMAT_STRING_SIZE 65536
  inline string FORMAT(char *b, int len, const char *fmt, ...)
  {
   string s;
   static char buf [FORMAT_STRING_SIZE];
   if ( strlen(fmt) > FORMAT_STRING_SIZE/4 ) {
    OUTPUT("FORMAT(): Warning, format string longer than maximum length.\n");
   }
   else if ( len > FORMAT_STRING_SIZE ) {
    OUTPUT("FORMAT(): Warning, provided buffer length exceeds maximum.\n" );
   }
   va_list args;
   va_start (args, fmt);
   vsprintf_s (buf, fmt, args);
   va_end (args);
   s=string(buf);
   const char *cstr=s.c_str();
   for ( int i=0; i<len; i++ ) {
    b[i]=cstr[i];
    if ( cstr[i]=='\0' ) break;
   }
   b[len-1]='\0';
   return s;
  }

  inline string FORMAT(const char*fmt, ...) {
   string s;
   static char buf[FORMAT_STRING_SIZE];
   va_list args;
   va_start( args, fmt );
   vsprintf_s(buf, fmt, args);
   va_end(args);
   s=string(buf);
   return s;
  }



#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>


  // Work Strings
  char buf[STRING_SIZE];
  char buf2[STRING_SIZE];
  char buf3[STRING_SIZE];

  inline void InitZeroTypesLibrary() {
   for ( int i=0; i<STRING_SIZE; i++ ) buf[i]=buf2[i]=buf3[i]='\0';
   init_seeder();
  }


  inline void rtrim(string& s, const string& delimiters ) {
   s.erase( s.find_last_not_of( delimiters ) + 1 );
  }

  inline void ltrim(string& s,  const string& delimiters ) {
   s.erase( 0, s.find_first_not_of( delimiters ) );
  }

  inline void trim(string& s, const string& delimiters ) {
   s.erase( s.find_last_not_of( delimiters ) + 1 ).erase( 0, s.erase( s.find_last_not_of( delimiters ) + 1 ).find_first_not_of( delimiters ) );
  }


  // Gather until next substring match or end of string (returns the point right after the substring)
  inline const char *gather_to( const char *argument, const char *substr, string *buf ) {
   *buf=string("");
   int substrlen=(int)strlen(substr);
   const char *p=argument;
   bool found=false;
   while ( *p != '\0' && !found ) {
    if ( *p==*substr ) {
     const char *oldp=p;
     const char *q=substr;
     bool match=true;
     int i=0;
     while ( match && i<substrlen ) {
      if ( *p!=*q ) match=false;
      p++;
      q++;
      i++;
     }
     if ( match ) {
      found=true;
      return p;
     }
     else {
      p=oldp;
      *buf+=(*p);
      p++;
     }
    } else {
     *buf+=(*p);
     p++;
    }
   }
   return p;
  }

  inline void replaceOnce(string& in, string const &search, string const &substitute) {
   int found=0;
   string::size_type pos=0;
   while((pos=in.find(search, pos))!=string::npos&&found<1)
   {
    in.erase(pos, search.length());
    in.insert(pos, substitute);
    pos+=substitute.length();
    found++;
   }
  }

  inline void replaceAll(string& in, string const &search, string const &substitute) {
   string::size_type pos=0;
   while((pos=in.find(search, pos))!=string::npos)
   {
    in.erase(pos, search.length());
    in.insert(pos, substitute);
    pos+=substitute.length();
   }
  }

  inline string replace_all(const string& in, const string& search, const string& substitute) {
   string::size_type pos=0;
   string out=in;
   while((pos=out.find(search, pos))!=string::npos)
   {
    out.erase(pos, search.length());
    out.insert(pos, substitute);
    pos+=substitute.length();
   }
   return out;
  }


  inline bool endsWith(string const &fullString, string const &ending) {
   string a=fullString;
   trim(a);
   if (a.length() >= ending.length()) {
    return (0 == a.compare(a.length() - ending.length(), ending.length(), ending));
   } else {
    return false;
   }
  }

  inline bool endsWith( const char *searching, const char *find, bool removePadding ) {
   if ( searching == null ) {
    OUTPUT( "endsWith: null searching.\n" );
    return false;
   }
   if ( find == null ) {
    OUTPUT( "endsWith: null find.\n" );
    return false;
   }
   int L1=(int)strlen(searching);
   if ( L1 == 0 ) return false;
   int L2=(int)strlen(find);
   if ( L1<L2 ) return false;
   if ( L2 == 0 ) {
    OUTPUT("endsWith() warns find string was empty, returning false\n");
    return false;
   }
   string unpadded;
   if ( !removePadding ) unpadded=string(searching);
   else {
    unpadded=string(searching);
    trim(unpadded);
    L1=(int)unpadded.length();
    if ( L1<L2 ) return false;
   }
   const char *tosearch=unpadded.c_str();
   int x=L1-1;
   int y=L2-1;
   while ( y>=0 ) {
    if ( LOWER(tosearch[x]) != LOWER(find[y]) ) {
     return false;
    }
    x--;
    y--;
   }
   return true;
  }

  /*
  * Counts the number of "words" (strings of non-spaces separated by spaces)
  * in a string.     Not the best way (should use one_arg)?
  */
  inline int words(const char *argument )
  {
   int total;
   char *s = (char *) argument;
   total = 0;
   while ( *s != '\0' ) 
    if ( *s != ' ' ) {
     total++;
     while ( *s != ' ' && *s != '\0' ) s++;
    } else s++;
   return total;
  }

  /*
  * Compare strings, case insensitive.
  * Return true if different
  *   (compatibility with historical functions).
  */
  inline bool str_cmp( const char *astr, const char *bstr )
  {
   if ( astr == null ) { 
    OUTPUT( "Str_cmp: null astr.\n" );
    return true;
   }
   if ( *astr == '\0' ) return true;
   if ( bstr == null ) { 
    OUTPUT( "Str_cmp: null bstr.\n" );
    return true;
   }
   if ( *bstr == '\0' ) return true;
   for ( ; *astr || *bstr; astr++, bstr++ ) if ( LOWER(*astr) != LOWER(*bstr) ) return true;
   return false;
  }

  inline bool str_cmp( string astr, string bstr ) {
   return str_cmp( astr.c_str(), bstr.c_str() );
  }

  inline bool is_digit( char c ) {
   return (c =='0' || c == '1' || c == '2' || c == '3' || c == '4' || c =='5' || c =='6' || c=='7' || c == '8' || c == '9' );
  }

  inline bool char_in(char c, const char *list ) {
   int o,O;
   O=(int)strlen(list);
   for ( o=0; o<O; o++ ) if ( list[o] == c ) return true;
   return false;
  }

  /*
  * Compare strings, case sensitive.
  * Return true if different
  *   (compatibility with historical functions).
  */
  inline bool str_cmp_case( const char *astr, const char *bstr )
  {
   if ( astr == null ) { 
    OUTPUT( "Str_cmp: null astr.\n" );
    return true;
   }
   if ( bstr == null ) { 
    OUTPUT( "Str_cmp: null bstr.\n" );
    return true;
   }
   for ( ; *astr || *bstr; astr++, bstr++ ) if ( (*astr) != (*bstr) ) return true;
   return false;
  }

  inline string lower( string a ) {
   Zstring lowered;
   const char *p=a.c_str();
   while ( *p != '\0' ) { char b=LOWER(*p); lowered+=b; p++; }
   return lowered.value;
  }

  inline string upper( string a ) {
   Zstring uppered;
   const char *p=a.c_str();
   while ( *p != '\0' ) { char b=UPPER(*p); uppered+=b; p++; }
   return uppered.value;
  }

  /*
  * Return true if an argument is completely numeric.
  */
  inline bool is_integer( const char *arg ) {
   const char *o=arg;
   bool foundspace=false;
   if ( *arg == '\0' ) return false;
   if ( *arg == '-' ) arg++;
   for ( ; *arg != '\0'; arg++ ) {
    if ( !is_digit(*arg) ) {
     if ( _FILLER(*arg) ) foundspace=true;
     else return false;
    }
   }
   if ( foundspace ) {
    if ( words(o) == 1 ) return true;
    return false;
   }
   return true;
  }

  /*
  * Return true if an argument is completely numeric.
  */
  inline bool is_decimal( const char *arg ) {
   const char *o=arg;
   int periods=0;
   bool foundspace=false;
   if ( *arg == '\0' ) return false;
   while ( _FILLER(*arg) ) arg++;
   if ( *arg == '-' ) arg++;
   for ( ; *arg != '\0'; arg++ ) {
    if ( !is_digit(*arg) ) {
     if ( *arg == '.' ) {
      if ( periods >=1 ) return false;
      periods++;
      arg++;
     } else
      if ( _FILLER(*arg) ) foundspace=true;
      else return false;
    }
   }
   if ( foundspace ) {
    if ( words(o) == 1 ) return true;
    return false;
   }
   return true;
  }

  /*
  * Same as above but uses atoi error handling, decimal only (base-10, no floats).
  * Does not return the value if valid (tiny inefficiency).
  * Source: http://www.gidforums.com/t-17778.html
  */
  inline bool is_int( string k ) {
   const char *in=k.c_str();
   char * last = 0;

   int x1 = atoi(in);
   int x2 = strtol(in, &last, 10);
   if ( *last == '\0' ) // was valid or empty
    if ( k.length() > 0 ) return false;
   return true;
  }

  /*
  * Same as above but uses atoi error handling.  Only base 10 checked.
  * Does not return the value if valid (tiny inefficiency).
  * Source: http://www.gidforums.com/t-17778.html
  */
  inline bool is_hex( string k ) {
   const char *in=k.c_str();
   char *last = null;
   int x1 = atoi(in);
   long x2 = strtol(in, &last, 16);
   if ( last && *last == '\0' ) // was valid or empty
    if ( k.length() > 0 ) return false;
   return true;
  }

  /*
  * Same as above but uses atoi error handling, decimal only (base-10, no floats).
  * Does not return the value if valid (tiny inefficiency).
  * Source: http://www.gidforums.com/t-17778.html
  */
  inline bool is_float( string k ) {
   char * last = 0;
   double x1 = atof(k.c_str());
   long x2 = strtol(k.c_str(), &last, 10);
   if ( *last == '\0' ) // was valid or empty returns false positive (indicating no error, but does not specify why)
    if ( k.length() > 0 ) return false;
   return true;
  }

  inline int from_hex( string hex ) {
   int result;
#if defined(_WINDOWS_)
   sscanf_s(hex.c_str(), "%x", &result);
#else 
   sscanf(hex.c_str(), "%x", &result);
#endif
   return result;
  }

  inline string to_hexidecimal( int i ) {
   char buf[80];
   FMT(buf,80,"%x", (int) i);
   string out=string(buf);
   if ( out.length() == 1 ) out=string("0")+out; // A==0A
   return out;
  }

  /* Pick off one argument from a string and return the rest.
  * Understands quotes and {}=[], treats interim commas and equal signs as space.
  * Uses the stack so not recommended for large strings (use string_argument);
  */
  inline const char *one_argument( const char *args, char *arg_first )
  {
   const char *argument=args;
   char cEnd = ' ';
   if ( argument == null ) return string_error();
   // Advance past spaces and interim commas, equal signs, newlines, skip //comments and #comments
   while ( _FILLER(*argument) || *argument == '#' ) {
    if ( *argument == '/' && *(argument+1) == '/' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
    if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
    else argument++;
   }
   if ( _SEP(*argument) ) {
    cEnd = *argument;
    argument++;
   }
   if ( _NESTERS(*argument) ) { // Handle nested {} or []
    argument++;
    int nests=1;
    while ( *argument != '\0' && _NESTERE(*argument) && nests > 0 ) {
     if ( _NESTERE(*argument) ) {
      nests--;
      argument++;
      if ( nests == 0 ) break;
     } else if ( *argument == '{' || *argument == '[' ) nests++;
     *arg_first=*argument;
     argument++;
     arg_first++;
    }
   } else { // Quotes are the delimiters
    while ( *argument != '\0' ) {
     if ( *argument == '\n' ) {
      argument++; 
      if ( cEnd == ' ' ) break;
     }
     if ( *argument == '\r' ) {
      argument++;
      if ( cEnd == ' ' ) break;
     }
     if ( *argument == ',' && cEnd == ' ' ) break; // end on a comma unless quotes are cEnd
     if ( *argument == '=' && cEnd == ' ' ) break; // end on equal sign unless quotes are cEnd
     if ( *argument == cEnd ) {
      argument++;
      break;
     }
     *arg_first = LOWER(*argument);
     arg_first++;
     argument++;
    }
   }
   *arg_first = '\0';
   // Advance past spaces and interim commas, equal signs, newlines, skip #comments
   while ( _FILLER(*argument) || *argument == '#' ) {
    if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
    else argument++;
   }
   return argument;
  }

  /* Pick off one argument from a string and return the rest.
  * Understands quotes and {}=[], treats interim commas and equal signs as space.
  * Uses the stack so not recommended for large strings (use string_argument);
  */
  inline const char *one_argument_case( const char *args, char *arg_first )
  {
   const char *argument=args;
   char cEnd = ' ';
   if ( argument == null ) return string_error();
   // Advance past spaces and interim commas, equal signs, newlines, skip //comments and #comments
   while ( _FILLER(*argument) || *argument == '#' ) {
    if ( *argument == '/' && *(argument+1) == '/' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
    if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
    else argument++;
   }
   if ( _SEP(*argument) ) {
    cEnd = *argument;
    argument++;
   }
   if ( _NESTERS(*argument) ) { // Handle nested {} or []
    argument++;
    int nests=1;
    while ( *argument != '\0' && _NESTERE(*argument) && nests > 0 ) {
     if ( _NESTERE(*argument) ) {
      nests--;
      argument++;
      if ( nests == 0 ) break;
     } else if ( *argument == '{' || *argument == '[' ) nests++;
     *arg_first=*argument;
     argument++;
     arg_first++;
    }
   } else { // Quotes are the delimiters
    while ( *argument != '\0' ) {
     if ( *argument == '\n' ) {
      argument++; 
      if ( cEnd == ' ' ) break;
     }
     if ( *argument == '\r' ) {
      argument++;
      if ( cEnd == ' ' ) break;
     }
     if ( *argument == ',' && cEnd == ' ' ) break; // end on a comma unless quotes are cEnd
     if ( *argument == '=' && cEnd == ' ' ) break; // end on equal sign unless quotes are cEnd
     if ( *argument == cEnd ) {
      argument++;
      break;
     }
     *arg_first = (*argument);
     arg_first++;
     argument++;
    }
   }
   *arg_first = '\0';
   // Advance past spaces and interim commas, equal signs, newlines, skip #comments
   while ( _FILLER(*argument) || *argument == '#' ) {
    if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
    else argument++;
   }
   return argument;
  }

  /* Pick off one argument from a string and return the rest.
  * Uses std::string thus dynamic and doesn't use the stack.
  * Understands quotes and {}=[](), treats interim commas and equal signs as space.
  */
  inline const char *string_argument( const char *argument, string *arg_first, bool slash_comments, bool pound_comments )
  {
   char cEnd = ' ';
   // char buf[2];
   (*arg_first)=string("");
   if ( argument == null ) return string_error(); // undef behavior? maybe "" is constant
                                                 // Advance past spaces and interim commas, equal signs, newlines, skip //comments and #comments
   while ( _FILLER(*argument) || (*argument == '#' && pound_comments) ) {
    if ( slash_comments && *argument == '/' && *(argument+1) == '/' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
    else if ( pound_comments && *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
    else argument++;
   }
   // Handle nested {} [] (), or quotes "" '' ``
   if ( _NESTERS(*argument) || _SEP(*argument) ) { // Delimiters
    int nests=1;
    char cStart=*argument;
    argument++;
    switch ( cStart ) {
    case '{': cEnd = '}'; break;
    case '[': cEnd = ']'; break;
    case '(': cEnd = ')'; break;
    case '\'': cEnd = '\''; break;
    case '"': cEnd = '"'; break;
    case '`': cEnd = '`'; break;
    }
    while ( *argument != '\0' && nests > 0 ) {
     if ( *argument == cEnd ) {
      nests--;
      if ( nests == 0 ) break;
     } else if ( *argument == cStart ) nests++;
     (*arg_first)+=(*argument);
     argument++;
    }
    argument++;
   } /*else if ( _EXPRESSIVE(*argument) ) {
     (*arg_first)+=*argument;
     }*/ else { // No delimiters, lower case, stop when you hit = , [ { ( + / - * % ! <space>
    while ( *argument != '\0' ) {
     if ( char_in( *argument, "\n\r[{(,= " ) ) break;
     (*arg_first)+=LOWER(*argument);//string(buf);
     argument++;
    }
   }
   // Advance past spaces and interim commas, equal signs, newlines, skip #comments
   while ( _FILLER(*argument) || *argument == '#' ) {
    if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
    else argument++;
   }
   return argument;
  }




  /* Pick off one argument from a string and return the rest.
  * Uses std::string thus dynamic and doesn't use the stack.
  * Understands quotes and {}=[](), treats interim commas and equal signs as space.
  */
  inline const char *string_argument( const char *argument, Zstring *arg_firstz )
  {
   string *arg_first=&arg_firstz->value;
   char cEnd = ' ';
   // char buf[2];
   (*arg_first)=string("");
   if ( argument == null ) return string_error(); // undef behavior? maybe "" is constant
                                                 // Advance past spaces and interim commas, equal signs, newlines, skip //comments and #comments
   while ( _FILLER(*argument) || *argument == '#' ) {
    if ( *argument == '/' && *(argument+1) == '/' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
    else if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
    else argument++;
   }
   // Handle nested {} [] (), or quotes "" '' ``
   if ( _NESTERS(*argument) || _SEP(*argument) ) { // Delimiters
    int nests=1;
    char cStart=*argument;
    argument++;
    switch ( cStart ) {
    case '{': cEnd = '}'; break;
    case '[': cEnd = ']'; break;
    case '(': cEnd = ')'; break;
    case '\'': cEnd = '\''; break;
    case '"': cEnd = '"'; break;
    case '`': cEnd = '`'; break;
    }
    while ( *argument != '\0' && nests > 0 ) {
     if ( *argument == cEnd ) {
      nests--;
      if ( nests == 0 ) break;
     } else if ( *argument == cStart ) nests++;
     (*arg_first)+=(*argument);
     argument++;
    }
    argument++;
   } else { // No delimiters, lower case, stop when you hit = , [ { (
    while ( *argument != '\0' ) {
     if ( char_in( *argument, "\n\r[{(,= " ) ) break;
     (*arg_first)+=LOWER(*argument);//string(buf);
     argument++;
    }
   }
   // Advance past spaces and interim commas, equal signs, newlines, skip #comments
   while ( _FILLER(*argument) || *argument == '#' ) {
    if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
    else argument++;
   }
   arg_firstz->length=(int)arg_firstz->value.length();
   return argument;
  }

  /* Pick off one argument from a string and return the rest without lowering case.
  * Uses std::string thus dynamic and doesn't use the stack.
  * Understands quotes and {}=[](), treats interim commas and equal signs as space.
  */
  inline const char *string_argument_case( const char *argument, std::string *arg_first )
  {
   char cEnd = ' ';
   // char buf[2];
   (*arg_first)=string("");
   if ( argument == null ) return string_error(); // undef behavior? maybe "" is constant
                                                 // Advance past spaces and interim commas, equal signs, newlines, skip //comments and #comments
   while ( _FILLER(*argument) || *argument == '#' ) {
    if ( *argument == '/' && *(argument+1) == '/' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
    else if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
    else argument++;
   }
   // Handle nested {} [] (), or quotes "" '' ``
   if ( _NESTERS(*argument) || _SEP(*argument) ) { // Delimiters
    int nests=1;
    char cStart=*argument;
    argument++;
    switch ( cStart ) {
    case '{': cEnd = '}'; break;
    case '[': cEnd = ']'; break;
    case '(': cEnd = ')'; break;
    case '\'': cEnd = '\''; break;
    case '"': cEnd = '"'; break;
    case '`': cEnd = '`'; break;
    }
    while ( *argument != '\0' && nests > 0 ) {
     if ( *argument == cEnd ) {
      nests--;
      if ( nests == 0 ) break;
     } else if ( *argument == cStart ) nests++;
     (*arg_first)+=(*argument);
     argument++;
    }
    argument++;
   } else { // No delimiters, lower case, stop when you hit = , [ { (
    while ( *argument != '\0' ) {
     if ( char_in( *argument, "\n\r[{(,= " ) ) break;
     (*arg_first)+=(*argument);//string(buf);
     argument++;
    }
   }
   // Advance past spaces and interim commas, equal signs, newlines, skip #comments
   while ( _FILLER(*argument) || *argument == '#' ) {
    if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
    else argument++;
   }
   return argument;
  }


  /* Pick off one argument from a string and return the rest without lowering case.
  * Uses std::string thus dynamic and doesn't use the stack.
  * Understands quotes and {}=[](), treats interim commas and equal signs as space.
  */
  inline const char *string_argument_case( Zstring &sep, const char *argument, std::string *arg_first )
  {
   char cEnd = ' ';
   sep = " ";
   // char buf[2];
   (*arg_first)=string("");
   if ( argument == null ) return string_error(); // undef behavior? maybe "" is constant
   while ( _FILLER(*argument) && *argument != '=' ) argument++;
   // Handle nested {} [] (), or quotes "" '' ``
   if ( _NESTERS(*argument) || _SEP(*argument) ) { // Delimiters
    int nests=1;
    char cStart=*argument;
    argument++;
    sep = ""; sep += cStart;
    switch ( cStart ) {
    case '{': cEnd = '}'; break;
    case '[': cEnd = ']'; break;
    case '(': cEnd = ')'; break;
    case '\'': cEnd = '\''; break;
    case '"': cEnd = '"'; break;
    case '`': cEnd = '`'; break;
    }
    while ( *argument != '\0' && nests > 0 ) {
     if ( *argument == cEnd ) {
      nests--;
      if ( nests == 0 ) break;
     } else if ( *argument == cStart ) nests++;
     // handle JSON escape characters
     if (cEnd == '"' && *argument == '\\') {
      argument++;
      switch (*argument) {
      case '\0': break;
      case '"':
      case '\\': (*arg_first) += (*argument); break;
      case 'b': (*arg_first) += '\b';
      case 't': (*arg_first) += '\t';
      case 'n': (*arg_first) += '\n';
      case 'f': (*arg_first) += '\f';
      case 'r': (*arg_first) += '\r';
      }
     } else (*arg_first)+=(*argument);
     if (*argument == '\0') break;
     argument++;
    }
    argument++;
   } else { // No delimiters, lower case, stop when you hit = , [ { (
    while ( *argument != '\0' ) {
     if ( char_in( *argument, "\n\r[{(,= " ) ) break;
     (*arg_first)+=(*argument);
     if ( *argument != '\0' ) argument++;
    }
   }
   while ( _FILLER(*argument) && *argument != '=' ) argument++;
   return argument;
  }


  /* Pick off one argument from a string and return the rest.
  * Uses std::string thus dynamic and doesn't use the stack.
  * Understands quotes and {}=[](), treats interim commas and equal signs as space.
  */
  inline const char *string_argument_end( const char *argument, string *arg_first, char *sep )
  {
   char cEnd = ' ';
   // char buf[2];
   (*arg_first)=string("");
   if ( argument == null ) return string_error(); // undef behavior? maybe "" is constant
                                                 // Advance past spaces and interim commas, equal signs, newlines, skip //comments and #comments
   while ( _FILLER(*argument) || *argument == '#' ) {
    if ( *argument == '/' && *(argument+1) == '/' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
    else if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
    else argument++;
   }
   // Handle nested {} [] (), or quotes "" '' ``
   if ( char_in(*argument, "{([`'\"") ) { // Delimiters
    int nests=1;
    char cStart=*argument;
    switch ( cStart ) {
    case '{': cEnd = '}'; break;
    case '[': cEnd = ']'; break;
    case '(': cEnd = ')'; break;
    case '\'': cEnd = '\''; break;
    case '"': cEnd = '"'; break;
    case '`': cEnd = '`'; break;
    }
    argument++;
    while ( *argument != '\0' && nests > 0 ) {
     if ( *argument == cEnd ) {
      nests--;
      if ( nests == 0 ) break;
     } else if ( *argument == cStart ) nests++;
     /*buf[0]=*argument;
     buf[1]='\0';*/
     (*arg_first)+=(*argument);//string(buf);
     argument++;
    }
    argument++;
   } else { // No delimiters, lower case, stop when you hit = , [ { (
    while ( *argument != '\0' ) {
     if ( char_in( *argument, "\n\r[{(,= " ) ) { *sep=*argument; } break;
     /*buf[0]=(*argument);
     buf[1]='\0';*/
     (*arg_first)+=LOWER(*argument);//string(buf);
     argument++;
    }
   }
   // Advance past spaces and interim commas, equal signs, newlines, skip #comments
   while ( _FILLER(*argument) || *argument == '#' ) {
    if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
    else argument++;
   }
   return argument;
  }


  /*
  * Compare strings, case insensitive, for prefix matching.
  * Return true if hay not a prefix of haystack
  *   (compatibility with historical functions).
  */
  inline bool str_prefix( const char *astr, const char *bstr )
  {
   if ( astr == null || *astr == '\0' ) {
    OUTPUT( "Str_prefix: null astr.\n" );
    return true;
   }
   if ( bstr == null || *bstr == '\0'  ) {
    OUTPUT( "Str_prefix: null bstr.\n" );
    return true;
   }
   while ( *astr != '\0' && *bstr != '\0' ) {
    if ( LOWER(*astr) != LOWER(*bstr) ) return true;
    astr++;
    bstr++;
   }
   if ( *astr == '\0' ) return false;
   return true;
  }

  /*
  * Compare strings, case sensitive, for prefix matching.
  * Return true if astr not a prefix of bstr
  *   (compatibility with historical functions).
  */
  inline bool str_prefix_case( const char *astr, const char *bstr )
  {
   if ( astr == null || *astr == '\0' ) {
    OUTPUT( "Str_prefix: null astr.\n" );
    return true;
   }
   if ( bstr == null || *bstr == '\0'  ) {
    OUTPUT( "Str_prefix: null bstr.\n" );
    return true;
   }
   while ( *astr != '\0' && *bstr != '\0' ) {
    if ( (*astr) != (*bstr) ) return true;
    astr++;
    bstr++;
   }
   return false;
  }

  inline string strtolower( const char *input ) {
   return lower(string(input));
  }

  /*
  * Compare strings, case insensitive, for match anywhere.
  * Returns true if shorter string not part of longer string.
  *   (compatibility with historical functions).
  */
  inline bool str_infix( const char *astr, const char *bstr ) {
   if ( astr == null || *astr == '\0' ) {
    OUTPUT( "Str_infix: null astr (compared against '%s').\n", bstr );
    return true;
   }
   if ( bstr == null || *bstr == '\0' ) {
    OUTPUT( "Str_infix: null bstr (compared against '%s').\n", astr );
    return true;
   }
   const char *key,*haystack,*q;
   // Figure out which string is shorter, and use that as a key (q)
   if ( strlen(astr) > strlen(bstr) ) {
    haystack= (char *) astr;
    key=q= (char *) bstr;
   } else {
    haystack= (char *) bstr;
    key=q= (char *) astr;
   }
   // Make the keyword lowercase;
   string _key=lower(string(key));
   q=_key.c_str();
   char start=(*q);
   bool found=false;
   while ( *haystack !='\0' && !found ) {
    if ( LOWER(*haystack) != start ) { haystack++; continue; }
    if ( strlen(haystack) < _key.length() ) break;
    q=_key.c_str();
    while ( *q != '\0' && *haystack!='\0' && *q==LOWER(*haystack) ) { q++; haystack++; }
    if ( *q == '\0' ) { found=true; break; }
   }
   return !found;
  }


  /*
  * Compare strings, case insensitive, for match anywhere.
  * Returns true if shorter string not part of longer string.
  *   (compatibility with historical functions).
  */
  inline bool str_infix_case( const char *astr, const char *bstr ) {
   if ( astr == null || *astr == '\0' ) {
    OUTPUT( "Str_infix_case: null astr (compared against '%s').\n", bstr );
    return true;
   }
   if ( bstr == null || *bstr == '\0' ) {
    OUTPUT( "Str_infix_case: null bstr (compared against '%s').\n", astr );
    return true;
   }
   const char *key,*p,*q;
   // Figure out which string is shorter, and use that as a key (q)
   if ( strlen(astr) > strlen(bstr) ) {
    p= (char *) astr;
    key=q= (char *) bstr;
   }
   else {
    p= (char *) bstr;
    key=q= (char *) astr;
   }
   // Make the keyword lowercase;
   char start=(*q);
   int keyLength=(int)strlen(key);
   bool found=false;
   while ( *p!='\0' && !found ) {
    if ( LOWER(*p) != start ) { p++; continue; }
    if ( (int)strlen(p) < keyLength ) break;
    q=key;
    while ( *q != '\0' && *p!='\0' && *q==LOWER(*p) ) { q++; p++; }
    if ( *q == '\0' ) { found=true; break; }
   }
   return !found;
  }

  inline bool string_infix( string astr, string bstr ) {
   string a=string(astr); std::transform(a.begin(), a.end(), a.begin(),(int(*)(int)) std::tolower);
   string b=string(bstr); std::transform(b.begin(), b.end(), b.begin(),(int(*)(int)) std::tolower);
   if ( b.find(a) != string::npos ) return false;
   return true;
  }

  /*
  * Compare strings, case insensitive, for suffix matching.
  * Return true if astr not a suffix of bstr
  *   (compatibility with historical functions).
  */
  inline bool str_suffix( const char *astr, const char *bstr )
  {
   size_t sstr1;
   size_t sstr2;
   if ( !astr || !bstr ) return true;
   sstr1 = strlen(astr);
   sstr2 = strlen(bstr);
   if ( sstr1 <= sstr2 && !str_cmp( astr, bstr + sstr2 - sstr1 ) ) return false;
   else return true;
  }



  // Removes all newlines, limits all spaces to 1
  inline string Zstring::Words() {
   Zstring out;
   out=value;
   out("\n"," ");
   out("\t"," ");
   while ( out.Contains("  ") ) out("  "," ");
   const char *p=value.c_str();
   while ( *p != '\0' ) {
    p++;
    string word;
    p=string_argument_case(p,&word);
    if ( word.length() > 0 ) {
     if ( out.length > 0 ) {
      result+=" ";
     }
     result+=word;
    }
   }
   return out.value;
  }

  // Limits to a length or less without breaking words ex: LimitTo(dog cat fish ~ 6) = dog
  inline string Zstring::LimitTo( int len ) {
   Strings words;
   words.SplitPush(Words().c_str(),' ');
   Zstring out;
   EACH(words.first,String,s) {
    if ( (int)out.length + (int)s->s.length() > len ) break;
    out+=s->s;
   }
   return out.value;
  }

  inline string Zstring::WordWrap( int linelen ) {
   Strings words;
   words.SplitPush(Words().c_str(),' ');
   Zstring out;
   Zint thislinelen;
   EACH(words.first,String,s) {
    int wordlen=(int)s->s.length();
    if ( (int)thislinelen + 1 + wordlen > linelen ) {
     out+="\n";
     out+=s->s+string(" ");
     thislinelen=(int)s->s.length();
    } else {
     out+=s->s+string(" ");
     thislinelen+=wordlen+1;
    }
   }
   return out.value;
  }

  inline bool Zstring:: is_inside( const char * cloud ) {
   Zstring c(cloud);
   Strings it;
   it.SplitPush(cloud);
   Strings us;
   us.SplitPush(this->c_str());
   return it.includes(&us);
  }

  inline bool operator== ( const Zstring& a, const Zstring& b ) {
   bool result= !str_cmp(a.value.c_str(),b.value.c_str());
   if ( !result ) {
    if ( is_decimal(a.value.c_str()) && is_decimal(b.value.c_str()) ) {
     double A=atof(a.value.c_str());
     double B=atof(b.value.c_str());
     return ( A == B );
    }
   }
   return result;
  }

  inline bool operator== ( const Zstring& a, const char * b ) {
   return !str_cmp(a.value.c_str(),b);
  }

  inline bool operator== ( const char * b, const Zstring& a ) {
   return !str_cmp(a.value.c_str(),b);
  }

  inline bool operator!= ( const Zstring& a, const Zstring& b ) {
   bool result= !str_cmp(a.value.c_str(),b.value.c_str());
   if ( !result ) {
    if ( is_decimal(a.value.c_str()) && is_decimal(b.value.c_str()) ) {
     double A=atof(a.value.c_str());
     double B=atof(b.value.c_str());
     return !( A == B );
    }
   }
   return !result;
  }

  inline bool operator!= ( const Zstring& a, const char * b ) {
   return str_cmp(a.value.c_str(),b);
  }

  inline bool operator!= ( const char * b, const Zstring& a ) {
   return str_cmp(a.value.c_str(),b);
  }

  inline string operator+ ( const Zstring& a, const Zstring& b ) {
   return a.value+b.value;
  }

  inline string operator+ ( const Zstring& a, const string& b ) {
   return a.value+b;
  }

  inline string operator+ ( const string& a, const Zstring& b ) {
   return a+b.value;
  }

  inline string operator+ ( const Zstring& a, const int& b ) {
   return a.value+FORMAT(ZTSB().tbuf,128,"%d",(int)b);
  }

  inline string operator+ ( const Zstring& a, const unsigned int& b ) {
   return a.value+FORMAT(ZTSB().tbuf,128,"%d",(int)b);
  }

  inline string operator+ ( const Zstring& a, const float& b ) {
   return a.value+FORMAT(ZTSB().tbuf,128,"%f",(float)b);
  }

  inline string operator+ ( const Zstring& a, const double& b ) {
   return a.value+FORMAT(ZTSB().tbuf,128,"%f",(double)b);
  }

  inline string operator+ ( const int& a, const Zstring& b ) {
   return b.value+FORMAT(ZTSB().tbuf,128,"%d",(int)a);
  }

  inline string operator+ ( const unsigned int& a, const Zstring& b ) {
   return b.value+FORMAT(ZTSB().tbuf,128,"%d",(int)a);
  }

  inline string operator+ ( const float& a, const Zstring& b ) {
   return b.value+FORMAT(ZTSB().tbuf,128,"%f",(float)a);
  }

  inline string operator+ ( const double& a, const Zstring& b ) {
   return b.value+FORMAT(ZTSB().tbuf,128,"%f",(double)a);
  }

  inline string operator+ ( string a, Zint& b )    { return a+b.toString(); }
  inline string operator+ ( string a, Zuint& b )   { return a+b.toString(); }
  inline string operator+ ( string a, Zfloat& b )  { return a+b.toString(); }
  inline string operator+ ( string a, Zdouble& b ) { return a+b.toString(); }
  /* Creates C2593
  string operator+ ( Zint& a, string b )    { return a.toString()+b; }
  string operator+ ( Zuint& a, string b )   { return a.toString()+b; }
  string operator+ ( Zfloat& a, string b )  { return a.toString()+b; }
  string operator+ ( Zdouble& a, string b ) { return a.toString()+b; }
  */


  inline int operator+ ( Zint& a, Zint& b ) { return a.value+b.value; }
  inline float operator+ ( Zfloat& a, Zfloat& b ) { return a.value+b.value; }
  inline double operator+ ( Zdouble& a, Zdouble& b ) { return a.value+b.value; }

  inline string operator+ ( const Zstring& a, char c ) {
   return a.value+c;
  }

  inline string operator+ ( char c, const Zstring& a ) {
   return a.value+c;
  }

  inline string operator- ( const Zstring& a, const Zstring& b ) {
   string result=a.value;
   replaceOnce(result,b.value,string(""));
   return result;
  }

  inline string operator- ( const Zstring& a, const string& b ) {
   string result=a.value;
   replaceOnce(result,b,string(""));
   return result;
  }

  inline string operator- ( const string& b, const Zstring& a ) {
   string result=b;
   replaceOnce(result,a.value,string(""));
   return result;
  }

  inline string operator- ( const Zstring& a, const char *b ) {
   string result=a.value;
   replaceOnce(result,string(b),string(""));
   return result;
  }

  /*
  inline string operator- ( const char *b, const Zstring& a ) {
  string result=string(b);
  replaceOnce(result,a.value,string(""));
  return result;
  }*/

  inline string operator/ ( const Zstring& a, const Zstring& b ) {
   string result=a.value;
   replaceAll(result,b.value,string(""));
   return result;
  }

  inline string operator/ ( const Zstring& a, const string& b ) {
   string result=a.value;
   replaceAll(result,b,string(""));
   return result;
  }

  inline string operator/ ( const string& b, const Zstring& a ) {
   string result=b;
   replaceAll(result,a.value,string(""));
   return result;
  }

  inline string operator/ ( const Zstring& a, const char *b ) {
   string result=a.value;
   replaceAll(result,string(b),string(""));
   return result;
  }

  inline string operator/ ( const char *b, const Zstring& a ) {
   string result=string(b);
   replaceAll(result,a.value,string(""));
   return result;
  }

  inline string operator* ( const Zstring& a, unsigned int i ) {
   string temp=string("");
   for ( unsigned int j=0; j<i; j++ ) {
    temp+=a.value;
   }
   return temp;
  }

  inline int operator* ( const Zstring& a, string b ) {
   if (a.value.length() == 0) return 0;
   int count = 0;
   for (
    size_t offset = a.value.find(b);
    offset != std::string::npos;
    offset = a.value.find(b, offset + b.length())
    ) ++count;
   return count;
  }

  inline int operator* ( string a, const Zstring& b ) {
   if (a.length() == 0) return 0;
   int count = 0;
   for (
    size_t offset = a.find(b.value);
    offset != std::string::npos;
    offset = a.find(b.value, offset + b.value.length())
    ) ++count;
   return count;
  }

  inline int operator* ( const Zstring& a, const char *B ) {
   string b=string(B);
   if (a.value.length() == 0) return 0;
   int count = 0;
   for (
    size_t offset = a.value.find(b);
    offset != std::string::npos;
    offset = a.value.find(b, offset + b.length())
    ) ++count;
   return count;
  }

  inline int operator* ( const Zstring& a, const Zstring& b ) {
   if (a.value.length() == 0) return 0;
   int count = 0;
   for (
    size_t offset = a.value.find(b.value);
    offset != std::string::npos;
    offset = a.value.find(b.value, offset + b.value.length())
    ) ++count;
   return count;
  }

  /// Zstring ////////////////////////////////////////////////////////////////////////////////////////// end



  // This is an up-to-date unit test for the ZIndexed template.
  // Do not define NEVER, simply remove the #if-def block.
  inline void ZIndexed_Rigorous_Test() {
#if defined(NEVER)
   OUTPUT("ZIndexed_Rigorous_Test: Phase I: allocating, initializing and destroying.\n");
   for ( unsigned int i=0; i<100; i++ ) {
    ZIndexed<unsigned int> b;
    b.Size(1024*1024);
    for ( unsigned int j=0; j<1024*1024; j++ ) {
     b(j)=j;
    }
   }
   OUTPUT("ZIndexed_Rigorous_Test: Phase II: resizing.\n");
   ZIndexed<unsigned int> b;
   for ( unsigned int i=0; i<100; i++ ) {
    b.Size(i*i*i);
    for ( unsigned int j=0; j<i*i*i; j++ ) {
     b(j)=j;
    }
   }
   OUTPUT("ZIndexed_Rigorous_Test: Phase III: complex Zero-memory tasks.\n");
   for ( unsigned int i=0; i<100; i++ ) {
    ZIndexed<Zpointer<unsigned int>> c;
    c.Size(i*i*i);
    for ( unsigned int j=0; j<i*i*i; j++ ) {
     c(j)=&i;
    }
   }
   OUTPUT("ZIndexed_Rigorous_Test: Phase IV: complex disposable-memory tasks.\n");
   for ( unsigned int i=0; i<100; i++ ) {
    if ( i % 2 == 0 ) OUTPUT(".");
    ZIndexed<Zdisposable<ZIndexed<unsigned int>>> c;
    c.Size(i);
    for ( unsigned int j=0; j<i; j++ ) {
     c(j).Recycle();
     c(j)->Size(j);
     //   for ( unsigned int k=0; k<j; j++ ) {
     // (*c(j)->Element(k))=k;
     //   }
    }
   }
   OUTPUT("ZIndexed_Rigorous_Test: Phase V: complex disposable-memory tasks with linear increase.\n");
   ZIndexed<Zdisposable<Zstring>> c;
   for ( unsigned int i=0; i<100; i++ ) {
    c.Increase();
    if ( i % 2 == 0 ) OUTPUT(".");
    for ( unsigned int j=0; j<i+1; j++ ) {
     c(j).Recycle();
     //   for ( unsigned int k=0; k<j; j++ ) {
     // (*c(j)->Element(k))=k;
     //   }
    }
   }
   OUTPUT("\n");
   OUTPUT("Indexed_Rigorous_Test: Complete.\n");
#endif
  }

  //////////////////////////////////////////// ListItem and LinkedList

  Zint anyReseed;
  inline ListItem *LinkedList::Any( int seed ) {
   if ( count == 0 ) return null;
   anyReseed++;
   return Element(zpseudorandom(count*2,anyReseed)%count);
  }

  inline void LinkedList::sendUp(ListItem *L, bool wrap)
  {
   if ( wrap ) {
    if ( L->prev ) {
     ListItem *before=L->prev;
     Remove(L);
     InsertBefore(L,before);
    } else {
     Remove(L);
     Append(L);
    }
   } else if ( L->prev ) {
    ListItem *before=L->prev;
    Remove(L);
    InsertBefore(L,before);
   }
  }

  inline void LinkedList::sendDown(ListItem *L, bool wrap)
  {
   if ( wrap ) {
    if ( L->next ) {
     ListItem *after=L->next;
     Remove(L);
     InsertAfter(L,after);
    } else {
     Remove(L);
     Prepend(L);
    }
   } else if ( L->next ) {
    ListItem *after=L->next;
    Remove(L);
    InsertAfter(L,after);
   }
  }

  // Adds to end of list
  inline void LinkedList::Append(ListItem *L) {
   _Append(L);
  }

  // Adds to end of list
  inline void LinkedList::_Append(ListItem *L) {
   count++;
   if ( last ) { 
    last->next=L;
    L->prev=last; 
    L->next=null;
    last=L; 
    return; 
   }
   L->next=L->prev=null;
   first=last=L;
  }

  // Adds to beginning of list
  inline void LinkedList::Prepend(ListItem *L) {
   count++;
   if ( first ) {
    first->prev=L;
    L->next=first;
    L->prev=null;
    first=L;
    return;
   }
   L->next=L->prev=null;
   first=last=L;
  }

  // Finds element at index i, if none returns null
  // 0=first
  inline ListItem *LinkedList::Element(int i) {
   ListItem *l;
   if ( count.value == 0 || i >= count.value ) return null;
   int c=0;
   for ( l=first; l; l=l->next ) {
    if ( c==i ) return l;
    c++;
   }
   if ( first ) return first;
   if ( last ) return last;
   OUTPUT("LinkedList::Element(index) returned null because the list was empty.\n");
   return null;
  }

  inline ListItem *LinkedList::Element(int i, bool wrap) {
   ListItem *l;
   if ( count.value == 0 ) return null;
   i%=count.value;
   int c=0;
   for ( l=first; l; l=l->next ) {
    if ( c==i ) return l;
    c++;
   }
   if ( first ) return first;
   if ( last ) return last;
   OUTPUT("LinkedList::Element(index) returned null because the list was empty.\n");
   return null;
  }

  inline int LinkedList::Element( ListItem *q ) {
   int i=0;
   FOREACH(ListItem,p) if ( p == q ) return i; else i++;
   OUTPUT("LinkedList::Element(item) returned -1 because the item was not found.\n");
   return -1;
  }

  // Inserts element L before p ListItem in List
  inline void LinkedList::InsertBefore(ListItem *insert, ListItem *before) {
   if ( !before ) { Prepend(insert); return; }
   insert->prev=before->prev;
   if ( insert->prev ) insert->prev->next=insert;
   insert->next=before;
   before->prev=insert;
   if ( before == first ) first=insert;
   count++;
  }

  // Inserts element L after p ListItem in List
  inline void LinkedList::InsertAfter(ListItem *insert, ListItem *after) {
   if ( !after ) { Prepend(insert); return; }
   insert->next=after->next;
   if ( after->next ) after->next->prev=insert;
   after->next=insert;
   insert->prev=after;
   if ( after == last ) last=insert;
   count++;
  }

  // Inserts element at index i (before), if index i exists, otherwise returns false
  inline void LinkedList::InsertAt(ListItem *insert, int i) {
   ListItem *p=Element(i);
   InsertBefore(insert,p);
  }

  // Removes element L from list
  inline void LinkedList::_Remove(ListItem *L) {
#if defined(DEBUG)
   if ( !this->ListIteminList(L) ) {
    OUTPUT("Warning: attempted to remove something not in this list.\n\r");
    return;
   }
#endif
   if ( first==L ) {
    if ( first==last ) {
     first=last=null; 
     L->next=L->prev=null;
     count=0;
     return;
    }
    first=first->next;
    if ( first ) first->prev=null;
    L->next=L->prev=null;
    count--;
    return;
   }
   if ( last==L ) {
    last=last->prev;
    if ( last ) last->next=null;
    L->next=L->prev=null;
    count--;
    return;
   }
   ListItem *p=L->prev,*n=L->next;
   if ( p ) p->next=n;
   if ( n ) n->prev=p;
   L->next=L->prev=null;
   count--;
   return;
  }

  // Removes all elements from the list
  inline void LinkedList::RemoveAll(void) {
   first=last=null;
   count=0;
  }

  // Deletes (frees) element L from list
  inline void LinkedList::Delete(ListItem *L) {
   Remove(L);
   delete L;
  }

  // Deletes (frees) element L from list, clears incoming
  inline void LinkedList::Delete(ListItem **L) {
   Remove(*L);
   delete (*L);
   *L=null;
  }


  inline void LinkedList::RandomizeOrder() {
   LinkedList newList;
   EACHN(first,ListItem,i,{
    Remove(i);
   if ( uniform() >= 0.5 ) {
    newList.Prepend(i);
   } else {
    newList.Append(i);
   }
    });
   this->first=newList.first; newList.first=null;
   this->last=newList.last; newList.last=null;
   count=newList.count; newList.count=0;
   return;
  }

  //////////////////////////////////////////// Strings and precursor required math

  inline string UnStringSpecialCodes( string k ) {
   return replace_all(replace_all(k,string("#*$#-1-#$*#"),string("{")),string("#*$#-2-#$*#"),string("}"));
  }

  inline string StringSpecialCodes( string k ) {
   return replace_all(replace_all(k,string("{"),string("#*$#-1-#$*#")),string("}"),string("#*$#-2-#$*#"));
  }


  ///// Random Numbers


  // Constants needed for random generation

  const long m = 2147483647L;
  const long a = 48271L;
  const long q = 44488L;
  const long r = 3399L;

  // A variable used to initialize the generator (should never be 0).
  long r_seed = 12345678L;

  // Integer SQRT
#define MAX_SRT 10000
  static double SRT[MAX_SRT];
  static int SRT_initialized=0;
  inline void init_isqrt( ) { 
   int i; 
   for ( i =0; i< MAX_SRT; i++ ) SRT[i]=sqrt((double)i); 
   SRT_initialized=1; 
  }
  inline float isqrt ( int i ) {
   i=abs(i); 
   if ( i > MAX_SRT-1 ) return (float) sqrt((float) i); 
   return (float) SRT[i]; 
  }

  inline double uniform ()
  {
   long t, lo, hi;
   double u;

   hi = r_seed / q;
   lo = r_seed - q * hi;
   t = a * lo - r * hi;
   if (t > 0)
    r_seed = t;
   else
    r_seed = t + m;
   u = (double) r_seed / (double) m ;

   return u;
  }

  inline double uniform ( bool reseed )
  {
   long t, lo, hi;
   double u;

   hi = r_seed / q;
   lo = r_seed - q * hi;
   if ( reseed ) {
    t = a * lo - r * hi;
    if (t > 0)
     r_seed = t;
    else
     r_seed = t + m;
   }
   u = (double) r_seed / (double) m ;

   return u;
  }

  // Works better with small numbers 0-255, used in Randoms.h,
  // Adheres to RAND_MAX (0x7fff) but is intended to be distinct and non-OS specific
  inline int zpseudorandom( unsigned int s, unsigned int x ) {
   s++;
   x++;
   long S=s;
   long X=x;
   long result=((56789*(X+S*X+S))/2)%PSEUDORAND_MAX;
   return abs((int)result);
  }

  inline long getMillis(void) {
   SYSTEMTIME t;
   GetLocalTime(&t);
   return (long) (t.wYear + t.wMonth + t.wDayOfWeek + t.wDay + t.wHour + t.wMinute + t.wSecond + t.wMilliseconds);
  }

  // Reseeding
  inline void init_seeder() {
   r_seed = (long) ( getMillis() );
   r_seed = (long) (LONG_MIN+uniform()*ULONG_MAX);
   if ( r_seed == 0 ) r_seed++;
  }

  inline void reseed() {
   r_seed = (long) ( getMillis() );
   r_seed = (long) (LONG_MIN+uniform()*ULONG_MAX);
   if ( r_seed == 0 ) r_seed++;
  }

  inline double zrandom(double x) {
   return x*uniform();
  }

  // Properly rounds ints
  inline int iround ( float f ) {
   return (int)(f+0.5f);
  }

  // Properly rounds ints
  inline int iround ( double d ) {
   return (int)(d+0.5);
  }

  // Do a floating point lerp from "start" to "finish"
  inline int ilerp( int start, int end, float percent ) {
   int d;
   if ( start > end ) {
    d=start-end;
    return start-iround( (float) d * percent );
   } else {
    d=end-start;
    return start+iround( (float) d * percent );
   }
  }

  // Do a floating point lerp from "start" to "finish"
  inline int ilerpw( int start, int end, float percent ) {
   float d=((float)ADIFF(start,end));
   if ( start > end ) d=-d;
   return start+iround( d * percent );
  }


  // Do a floating point lerp from "start" to "finish"
  inline int ilerp( int start, int end, double percent ) {
   int d;
   if ( start > end ) {
    d=start-end;
    return start-iround( (double) d * percent );
   } else {
    d=end-start;
    return start+iround( (double) d * percent );
   }
  }

  // Do a floating point lerp from "start" to "finish"
  inline int ilerpw( int start, int end, double percent ) {
   double d=((double)ADIFF(start,end));
   if ( start > end ) d=-d;
   return start+iround( d * percent );
  }

  inline double double_range( double L, double H ) {
   double u=uniform();
   double t=(H-L);
   u*= t;
   return (u) + L;
  }

  inline float float_range( float L, float H ) {
   double u=uniform();
   double t= (double) (H-L);
   u*= t;
   return ((float) u) + L;
  }

  // Randomize an integer in range L-H
  inline int number_range( int L, int H ) {
   double u=uniform();
   int t=H-L;
   u*=(double) t;
   u+=(double) L;
   return iround((float) (u));
  }

  inline int upto( int M ) {
   if ( M==0 ) return 0;
   return number_range(0,M*2)%M;
   //  return (int) (uniform()/*0.999999999999999*/*(double) max);
  }


  // Generating gaussian random number with mean 0 and standard deviation 1.
  inline float Gauss()
  {
   double u1 = uniform();
   double u2 = uniform();
   if (u1 < 1e-6f) u1 = 1e-6f;
   return sqrtf(-2 * logf((float) u1)) * cosf((float)(2*PI*u2));
  }


  inline char randomChar( const char *list ) {
   int c=(int)upto((int)strlen(list));
   return list[c];
  }

  // Used when writing to a file.
  /* in-den-tion (noun) \in-'den(t)-shun\ archaic : indentation;
  a: the action of indenting : the condition of being indented
  b: the blank space produced by indenting
  */

  inline void incdent() {
   indention()+=string(" ");
  }

  inline void decdent() {
   size_t spaces=indention().length();
   spaces--;
   nodent();
   for ( int i=0; i<(int)spaces; i++ ) incdent();
  }

  inline void nodent() {
   indention()=string("");
  }

  // Low-brow alphanumeric hash.
  inline string Hash( int len ) {
   if ( len<1 ) len=1;
   char *buf;
   buf = new char[len+1];
   for ( int i=0; i<len; i++ ) buf[i]=randomChar("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
   buf[len]='\0';
   string s=string(buf);
   delete[] buf;
   return s;
  }


  inline bool HashCompare5( string *a, string *b ) {
   const char *A=a->c_str();
   const char *B=b->c_str();
   return ( A[0]==B[0] && A[1]==B[1] && A[2]==B[2] && A[3]==B[3] && A[4]==B[4] );
  }

  // Pseudo-
  inline string RomanNumerals( int v ) {
   switch ( v ) {
   case 1: return string("I");
   case 2: return string("II");
   case 3: return string("III");
   case 4: return string("IV");
   case 5: return string("V");
   case 6: return string("VI");
   case 7: return string("VII");
   case 8: return string("VIII");
   case 9: return string("IX");
   case 10: return string("X");
   case 11: return string("X1");
   case 12: return string("X2");
   case 13: return string("X3");
   case 14: return string("X4");
   case 15: return string("X5");
   case 16: return string("X6");
   case 17: return string("X7");
   case 18: return string("X8");
   case 19: return string("X9");
   case 20: return string("2X");
   case 21: return string("2Xi");
   case 22: return string("2Xii");
   case 23: return string("2Xiii");
   case 24: return string("2Xiv");
   case 25: return string("2Xv");
   case 26: return string("2Xvi");
   case 27: return string("2Xvii");
   case 28: return string("2Xviii");
   case 29: return string("2X9");
   case 30: return string("3X");
   default:
   {
    char buf[128];
    if ( v%10 == 0 ) FORMAT(buf,128,"%d", (int) v);
    else {
     string numbers=RomanNumerals(v%10);
     numbers=lower(numbers);
     FORMAT(buf,128,"%dX%s", (int)(v/10), numbers.c_str() );
    }
    return string(buf);
   }
   }
  }



  inline string slash_to_backslash( const char * s ) {
   Zstring in(s);
   in("/","\\");
   return in.c_str();
  }

  inline string backslash_to_slash( const char * s ) {
   Zstring in(s);
   in("\\","/");
   return in.c_str();
  }

  inline string trailing_slash( const char *s ) {
   Zstring in(s);
   in.Trim();
   if ( in.last() != '/' ) in+=string("/");
   return in.value;
  }

  inline string basename( const char *path, char sep ) {
   Strings parts;
   parts.SplitPush(path,sep);
   if ( !parts.last ) return string("");
   return ((String *)parts.last)->s;
  }

  inline string trailing_backslash( const char *s ) {
   Zstring in(s);
   in.Trim();
   if ( in.last() != '\\' ) in+=string("\\");
   return in.value;
  }



  /////////////////////////////////////////////////////////////// Strings

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>



  // String

  inline const char *String::c_str() {
   return this->s.c_str();
  }

  inline void Strings::ls_( const char *targetPath, bool listFiles, bool prependPath, bool filterOSFiles ) {
   //Strings *folder=ls(targetPath,listFiles,prependPath,filterOSFiles);
   //if ( folder ) {
   // Concat(folder);
   // delete folder;
   //}
  }

  inline bool Strings::inList( string s ) {
   FOREACH(String,sL) if ( s == sL->s ) return true;
   return false;
  }

  inline String *Strings::matchPrefix( const char *s ) {
   FOREACH(String,sL) if ( sL->s.length() > 0 && strlen(s) > 0 && !str_prefix(sL->c_str(),s) ) return sL;
   return null;
  }

  inline void Strings::matchesPrefix( const char *s, Strings *out ) {
   FOREACH(String,sL) {
    if ( sL->s.length() > 0 && strlen(s) > 0 && !str_prefix(sL->c_str(),s) ) {
     out->Push(sL->s.c_str());
    }
   }
  }

  inline String *Strings::match( const char *s ) {
   FOREACH(String,sL) if ( !str_cmp(sL->c_str(),s) ) return sL;
   return null;
  }

  inline String *Strings::find( string s ) {
   FOREACH(String,sL) if ( s == sL->s ) return sL; 
   return null;
  }

  inline String *Strings::find( const char *s ) {
   string f=string(s);
   FOREACH(String,sL) if ( f == sL->s ) return sL; 
   return null;
  }

  inline String *Strings::findCaseless( const char *s ) {
   string f=string(s);
   FOREACH(String,sL) if ( !str_cmp(s, sL->s.c_str() ) ) return sL; 
   return null;
  }

  inline String *Strings::findCaseless( string s ) {
   string f=string(s);
   FOREACH(String,sL) if ( !str_cmp((char *) s.c_str(), (char *) sL->s.c_str() ) ) return sL; 
   return null;
  }

  inline String *Strings::findSubstring( const char *s ) {
   FOREACH(String, sL) { Zstring z=sL->s; if ( z.contains(s) ) return sL; }
   return nullptr;
  }

  inline String *Strings::findNextSubstring( String *start, const char *s ) {
   String *sL=start;
   while ( sL && string_infix(s,sL->s) ) sL=(String *) sL->next;
   return sL;
  }

  inline string Strings::concatToNextSubstring( String *start, const char *end ) {
   String *e = this->findNextSubstring(start,end);
   string x=string("");
   String *sL=start;
   while ( sL && sL != e ) { x+=sL->s+string("\n"); sL=(String *) sL->next; }
   return x;
  }

  // Returns -1 if not in list
  inline int Strings::IndexOf( String *s ) {
   int i=0;
   FOREACH(String,sL) {
    if ( s == sL ) return i;
    else i++;
   }
   return -1;
  }

  // Returns duplicated concatenations of Strings
  inline string Strings::Concatenate( char seperator ) {
   string e = string("");
   FOREACH(String,sL) {
    e=e+sL->s;
    e.append( 1, seperator );
   }
   return e;
  }

  // Returns duplicated concatenations of Strings
  inline string Strings::Concatenate( having Seamless ) {
   string e = string("");
   FOREACH(String,sL) {
    e=e+sL->s;
   }
   return e;
  }

  inline void Strings::appendFromString( const char *s, char c ) {
   static char temp[STRING_SIZE];
   const char *p= s;
   int i=0;
   while ( *p != '\0' ) {
    if ( *p==c ) {
     temp[i]='\0';
     String *t; NEW(t,String(temp));
     if (!t) {
      OUTPUT("appendFromString: error on allocation, Could not allocate new string.\n");
      return;
     }
     Append(t);
     i=0;
    } else
     temp[i++] =*p;
    p++;
   }
  }

  inline void Strings::appendFromString( string s, char c ) {
   appendFromString( (char *) s.c_str(), c );
  }

  inline void Strings::show()
  { 
   FOREACH(String,s) OUTPUT( "%s\n", s->s.c_str() ); 
  }

  inline void Strings::show( const char *sep, const char *end )
  { 
   FOREACH(String,s) OUTPUT( "%s%s", s->s.c_str(), (s->next ? sep : "") );
   OUTPUT("%s",end);
  }

  // Splits using string_argument
  inline void Strings::SplitPush( const char *s ) {
   const char *p=s;
   while ( *p != '\0' ) {
    string t;
    p=string_argument(p,&t);
    if ( t.length() > 0 ) Push(t);
   }
  }


  // Splits by char_in(), like char_isof, default is newline/space
  inline void Strings::SplitPush( const char *s, const char *delimiterList ) {
   const char *p=s;
   Zstring t;
   while ( *p != '\0' ) {
    if ( char_in(*p,delimiterList) ) if ( t.length > 0 ) { Add(t.c_str()); t=""; }
    else t+=(*p);
    p++;
   }
  }

  inline void Strings::SplitPush( string s, char seperator ) {
   string t;
   static char buf[2];
   buf[0]=seperator;
   buf[1]='\0';
   const char *p=s.c_str();
   while ( *(p=gather_to(p,buf,&t)) != '\0' ) Push(t);
   if ( t.length() > 0 ) Push(t);
  }



  inline void Strings::SplitPush( const char *s, char seperator ) {
   string t;
   static char buf[2];
   buf[0]=seperator;
   buf[1]='\0';
   const char *p=s;
   while ( *(p=gather_to(p,buf,&t)) != '\0' ) Push(t);
   if ( t.length() > 0 ) Push(t);
  }


  // Splits using string_argument
  inline void Strings::ScriptPush( const char *s ) { SplitPush(s); }

  inline void Strings::Push( string s ) {
   String *t; NEW(t,String(s));
   if (!t) {
    OUTPUT("Push: error on allocation, Could not allocate new string.\n");
    return;
   }
   Append(t);
  }

  inline void Strings::Push( const char *s ) {
   String *t; NEW(t,String(s));
   if (!t) {
    OUTPUT("Push: error on allocation, Could not allocate new string.\n");
    return;
   }
   Append(t);
  }

  inline String *Strings::PushAndGet( const char *s ) {
   String *x; NEW(x,String(string(s)));
   if (!x) {
    OUTPUT("PushAndGet: error on allocation, Could not allocate new string.\n");
    return null;
   }
   Append(x);
   return x;
  }

  inline void Strings::DuplicateAndPush( const char *s ) { // No longer different
   String *t; NEW(t,String(s));
   if (!t) {
    OUTPUT("DuplicateAndPush: error on allocation, Could not allocate new string.\n");
    return;
   }
   Append( t );
  }

#include <Windows.h> // for ls()
#include <tchar.h> // for ls()

  // List directory contents
  // http://msdn.microsoft.com/en-us/library/aa365200%28VS.85%29.aspx
  // When listFiles parameter is false, find only subfolder names.
  inline Strings *ls( const char *targetPath, bool listFiles, bool prependPath, bool filterOSFiles ) {
   WIN32_FIND_DATA ffd;
   TCHAR szDir[MAX_PATH];
   size_t length_of_arg;
   HANDLE hFind=INVALID_HANDLE_VALUE;
   DWORD dwError=0;
   string endsWithSlash=trailing_backslash(slash_to_backslash(targetPath).c_str());

   // Check that the input path plus 3 is not longer than MAX_PATH.
   // Three characters are for the "\*" plus NULL appended below.
   length_of_arg = strlen(targetPath);
   if (length_of_arg > (MAX_PATH - 3)) {
    OUTPUT("Strings.h ls() reports directory path is too long.\n");
    return null;
   }

   // Prepare string for use with FindFile functions.  First, copy the
   // string to a buffer, then append '\*' to the directory name.
   char path[MAX_PATH+1];
   FORMAT(path,MAX_PATH+1,"%s*",endsWithSlash.c_str());
   for ( int i=0; i<MAX_PATH; i++ ) szDir[i]=(TCHAR) path[i];

   // Find the first file in the directory.
   hFind = FindFirstFile(szDir, &ffd);

   if (INVALID_HANDLE_VALUE == hFind) {
    OUTPUT("String.h ls() reported error: Error was %d\n", (int) dwError );
    return null;
   }

   Strings *list; NEW(list,Strings);

   // List all the files in the directory with some info about them.
   do {
    bool isFolder=true && (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
    char buf[260];
    FORMAT(buf,260,"%s",ffd.cFileName);
    if ( filterOSFiles ) {
     if ( !str_cmp(buf,".") ) continue;
     if ( !str_cmp(buf,"..") ) continue;
     if ( !str_cmp(buf,"Thumbs.db") ) continue;
    }
    if (!listFiles && isFolder) {
     if ( prependPath ) {
      char buf2[260+1024];
      FORMAT(buf2,260+1024,"%s%s",endsWithSlash.c_str(),buf);
      String *n; NEW(n,String(buf2));
      list->Append(n);
     } else {
      String *n; NEW(n,String(buf));
      if (!n) {
       OUTPUT("ls: error on allocation, Could not allocate new string.\n");
       return null;
      }
      list->Append(n);
     }
    } else if ( !isFolder ) {
     if ( prependPath  ) {
      char buf2[260+1024];
      FORMAT(buf2,260+1024,"%s%s",endsWithSlash.c_str(),buf);
      String *n; NEW(n,String(buf2));
      if (!n) {
       OUTPUT("ls: error on allocation, Could not allocate new string.\n");
       return null;
      }
      list->Append(n);
     } else {
      String *n; NEW(n,String(buf));
      if (!n) {
       OUTPUT("ls: error on allocation, Could not allocate new string.\n");
       return null;
      }
      list->Append(n);
     }
    }
   }
   while (FindNextFile(hFind, &ffd) != 0); 
   dwError = GetLastError();
   if (dwError != ERROR_NO_MORE_FILES) OUTPUT("Strings.h ls() reported an unexpected error (code %d).\n", (int) dwError );
   FindClose(hFind);
   return list;
  }

  inline Strings *ls( const char *targetPath, bool listFiles, bool prependPath, Strings *filters ) {
   WIN32_FIND_DATA ffd;
   size_t length_of_arg;
   HANDLE hFind=INVALID_HANDLE_VALUE;
   DWORD dwError=0;

   string endsWithSlash=trailing_backslash(slash_to_backslash(targetPath).c_str());

   // Check that the input path plus 3 is not longer than MAX_PATH.
   // Three characters are for the "*" plus NULL appended below.
   length_of_arg = strlen(targetPath);
   if (length_of_arg > (MAX_PATH - 3)) {
    OUTPUT("Strings.h ls() reports directory path is too long.\n");
    return null;
   }

   // Prepare string for use with FindFile functions.  First, copy the
   // string to a buffer, then append '*' to the directory name.
   char path[MAX_PATH+1];
   FORMAT(path,MAX_PATH+1,"%s*",endsWithSlash.c_str());
   TCHAR szDir[MAX_PATH];
   for ( int i=0; i<MAX_PATH; i++ ) szDir[i]=(TCHAR) path[i];

   // Find the first file in the directory.
   hFind = FindFirstFile(szDir, &ffd);

   if (INVALID_HANDLE_VALUE == hFind) {
    OUTPUT("String.h ls() reported error: Error was %d\n", (int) dwError );
    return null;
   }

   Strings *list; NEW(list,Strings);
   if (!list) {
    OUTPUT("ls: could not allocate list.\n");
    return null;
   }

   // List all the files in the directory with some info about them.
   do {
    bool isFolder=true && (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
    char buf[260];
    FORMAT(buf,260,"%s",ffd.cFileName);
    if ( filters ) {
     bool found=false;
     EACH(filters->first,String,filter) if ( !str_infix(buf,filter->c_str()) ) found=true;
     if ( found ) continue;
    }
    if (!listFiles && isFolder) {
     if ( prependPath ) {
      static char buf2[260+1024];
      FORMAT(buf2,260+1024,"%s%s",endsWithSlash.c_str(),buf);
      String *n; NEW(n,String(buf2));
      if (!list) {
       OUTPUT("ls: could not allocate list.\n");
       return null;
      }
      list->Append(n);
     } else {
      String *n; NEW(n,String(buf));
      if (!n) {
       OUTPUT("ls: could not allocate string.\n");
       return null;
      }
      list->Append(n);
     }
    } else if ( !isFolder ) {
     if ( prependPath  ) {
      static char buf2[260+1024];
      FORMAT(buf2,260+1024,"%s/%s",targetPath,buf);
      String *n; NEW(n,String(buf2));
      if (!n) {
       OUTPUT("ls: could not allocate string.\n");
       return null;
      }
      list->Append(n);
     } else {
      String *n; NEW(n,String(buf));
      if (!n) {
       OUTPUT("ls: could not allocate string.\n");
       return null;
      }
      list->Append(n);
     }
    }
   }
   while (FindNextFile(hFind, &ffd) != 0); 
   dwError = GetLastError();
   if (dwError != ERROR_NO_MORE_FILES) OUTPUT("Strings.h ls() reported an unexpected error (code %d).\n", (int) dwError );
   FindClose(hFind);
   return list;
  }

  ///////////////////////////////////////////////// Cartesian

  // Source: Paeth, Graphics Gems V
  inline int Cartesian::PntOnLine(int px, int py, int qx, int qy, int tx, int ty) {
   /*
   * given a line through P:(px,py) Q:(qx,qy) and T:(tx,ty)
   * return 0 if T is not on the line through      <--P--Q-->
   *        1 if T is on the open ray ending at P: <--P
   *        2 if T is on the closed interior along:   P--Q
   *        3 if T is on the open ray beginning at Q:    Q-->
   *
   * Example: consider the line P = (3,2), Q = (17,7). A plot
   * of the test points T(x,y) (with 0 mapped onto '.') yields:
   *
   *     8| . . . . . . . . . . . . . . . . . 3 3
   *  Y  7| . . . . . . . . . . . . . . 2 2 Q 3 3    Q = 2
   *     6| . . . . . . . . . . . 2 2 2 2 2 . . .
   *  a  5| . . . . . . . . 2 2 2 2 2 2 . . . . .
   *  x  4| . . . . . 2 2 2 2 2 2 . . . . . . . .
   *  i  3| . . . 2 2 2 2 2 . . . . . . . . . . .
   *  s  2| 1 1 P 2 2 . . . . . . . . . . . . . .    P = 2
   *     1| 1 1 . . . . . . . . . . . . . . . . .
   *      +--------------------------------------
   *        1 2 3 4 5 X-axis 10        15      19
   *
   * Point-Line distance is normalized with the Infinity Norm
   * avoiding square-root code and tightening the test vs the
   * Manhattan Norm. All math is done on the field of integers.
   * The latter replaces the initial ">= MAX(...)" test with
   * "> (ABS(qx-px) + ABS(qy-py))" loosening both inequality
   * and norm, yielding a broader target line for selection.
   * The tightest test is employed here for best discrimination
   * in merging collinear (to grid coordinates) vertex chains
   * into a larger, spanning vectors within the Lemming editor.
   */
   /* addenda: this first set of tests has been added to detect
   * the case where the line is of zero length. Remove this if
   * such a case is impossible.
   */
   if ((px == qx) && (py == qy))   if ((tx == px) && (ty == py)) return 2;
   else return 0;
   if ( abs((qy-py)*(tx-px)-(ty-py)*(qx-px)) >= (UMAX(abs(qx-px), abs(qy-py)))) return(0);
   if (((qx<px)&&(px<tx)) || ((qy<py)&&(py<ty))) return(1);
   if (((tx<px)&&(px<qx)) || ((ty<py)&&(py<qy))) return(1);
   if (((px<qx)&&(qx<tx)) || ((py<qy)&&(qy<ty))) return(3);
   if (((tx<qx)&&(qx<px)) || ((ty<qy)&&(qy<py))) return(3);
   return(2);
  }

  //! Uses the approximation Cartesian list to approximate a circle at a given precision
  inline void Cartesian::ApproximateCircle( int precision ) {
   approximation.Recycle();
   if ( precision < 3 ) precision=3;
   double precisiond = (double)precision;
   for ( int i=0; i<precision; i++ ) {
    double p1=(double)(i)/precisiond;
    double p2=(double)(i+1)/precisiond;
    Cartesian *segment=new Cartesian(true,
     x+(R*cos(TWO_PI*p1)), y+(R*sin(TWO_PI*p1)),
     x+(R*cos(TWO_PI*p2)), y+(R*sin(TWO_PI*p2))
    );
    segment->form = cartesian_line_rect;
    approximation->Append(segment);
   } 
  }

  //! Performs validation and calculation of box parameters
  inline void Cartesian::Box() {
   double lx=MinX();
   double ly=MinY();
   double lz=MinZ();
   double lx2=MaxX();
   double ly2=MaxY();
   double lz2=MaxZ();
   Corners(lx, ly, lz, lx2, ly2, lz2);
   area=w*h;
   volume=w*h*d;
   approximation.Recycle();
   approximation->left=approximation->Add(true,x,y,x,y2);
   approximation->right=approximation->Add(true,x2,y,x2,y2);
   approximation->top=approximation->Add(true,x,y,x2,y);
   approximation->bottom=approximation->Add(true,x,y2,x2,y2);
   approximation->centroid.Set((x+x2)/2.0,(y+y2)/2.0);
  }

  inline bool Cartesian::CircleLine(Cartesian line, Cartesian &enter, Cartesian &exit, int precision) {
   if ( !approximation || approximation->count != precision ) ApproximateCircle(precision);
   CoplanarLinesResults results;
   enter.exists = false;
   exit.exists = false;
   bool result=approximation->Collides(*this,results);
   if ( result ) {
    if ( results.count == 1 ) {
     CoplanarLinesResult *a=(CoplanarLinesResult *) results.first;
     enter.Set(a->x,a->y,a->x,a->y);
     return true;
    } else if ( results.count == 2 ) {
     CoplanarLinesResult *a=(CoplanarLinesResult *) results.first;
     CoplanarLinesResult *b=(CoplanarLinesResult *) results.last;
     exit.Set(a->x,a->y,b->x,b->y);
     return true;
    }
   } else {
    enter.Zero();
    exit.Zero();
   }
   return result;
  }

  //! Returns true if an AAB rectangle and a line are colliding.  If !enter.exists, line started outside rectangle, if !exit exists, line ended inside rectangle
  inline bool Cartesian::RectLine( Cartesian line, BoxCollisionResults &out) {
   return line.LineRect(*this,out); // not yet done!
  }

  //! Returns true if the AAB Box and Line are colliding.  
  inline bool Cartesian::LineRect( Cartesian box, BoxCollisionResults &out ) {
   out.Reset();
   out.startsInside=box.Within(x,y);
   out.endsInside = box.Within(x2, y2);
   // Convert box B to Lines
   if ( !box.approximation || box.approximation->count == 0 ) box.Box();
   out.collided=box.approximation->Collides(*this,out.results);
   if ( out.collided ) {
    out.collisions=out.results.count;
    EACH(out.results.first,CoplanarLinesResult,p) {
     if ( p->segment == *(box.approximation->top) ) {
      out.top=true;
     } else if ( p->segment == *(box.approximation->bottom) ) {
      out.bottom=true;
     } else if ( p->segment == *(box.approximation->left) ) {
      out.left=true;
     } else if ( p->segment == *(box.approximation->right) ) {
      out.right=true;
     }
    }
    if ( out.results.count == 2 ) {
     CoplanarLinesResult *a=(CoplanarLinesResult *) out.results.first;
     CoplanarLinesResult *b=(CoplanarLinesResult *) out.results.last;
     out.x=a->x;
     out.y=a->y;
     out.x2=b->x;
     out.y2=b->y;
     return true;
    } else if ( out.results.count == 1 ) {
     CoplanarLinesResult *a=(CoplanarLinesResult *) out.results.first;
     out.x=a->x;
     out.y=a->y;
     return true;
    }
    return false;
   }
   return out.collided;
  }

  //! Returns true if a point is inside a circle
  inline bool Cartesian::PointCircle( Cartesian circle) { return circle.Distance(*this) < circle.R; }

#define ARBITRARY_SCALE_PRECISON_Cartesian_LineLine (100.0)
  //! Returns true if a line and a line are crossing.  Will not manipulate "point" if !collided, otherwise will write the point of crossing
  inline bool Cartesian::LineLine( Cartesian otherLine, Cartesian &point) {
   point.exists = false;
   // Source: Paul Bourke
   // Incorrectly returns the midpoint of the test line (this)
   // as the collision point when test against line has length of 0,
   // so we use Paeth's PntOnLine function to guestimate collision.
   // Because PntOnLine is integer-based, so normalized values will
   // all collide at their integer equivalents 0,1 (so we scale by
   // an arbitrary value of 100 ... ARBITRARY_SCALE_PRECISON_Cartesian_LineLine)
   if ( otherLine.x==otherLine.x2 && otherLine.y==otherLine.y2 ) {
    int res=Cartesian::PntOnLine(
     (int)(x*ARBITRARY_SCALE_PRECISON_Cartesian_LineLine),(int)(y*ARBITRARY_SCALE_PRECISON_Cartesian_LineLine),
     (int)(x2*ARBITRARY_SCALE_PRECISON_Cartesian_LineLine),(int)(y2*ARBITRARY_SCALE_PRECISON_Cartesian_LineLine),
     (int)(otherLine.x*ARBITRARY_SCALE_PRECISON_Cartesian_LineLine),(int)(otherLine.y*ARBITRARY_SCALE_PRECISON_Cartesian_LineLine)
    );
    point.x=otherLine.x;
    point.y=otherLine.y;
    point.exists = true;
    return (res!=2);
   } else
    if ( x==x2 && y==y2 ) {
     int res=Cartesian::PntOnLine(
      (int)(otherLine.x*ARBITRARY_SCALE_PRECISON_Cartesian_LineLine),(int)(otherLine.y*ARBITRARY_SCALE_PRECISON_Cartesian_LineLine),
      (int)(otherLine.x2*ARBITRARY_SCALE_PRECISON_Cartesian_LineLine),(int)(otherLine.y2*ARBITRARY_SCALE_PRECISON_Cartesian_LineLine),
      (int)(x*100.0),(int)(y*ARBITRARY_SCALE_PRECISON_Cartesian_LineLine)
     );
     point.x=x;
     point.y=y;
     point.exists = true;
     return (res!=2);
    }
   double mua,mub;
   double denom,numera,numerb;
   denom  = (otherLine.y2-otherLine.y) * (x2-x) - (otherLine.x2-otherLine.x) * (y2-y);
   numera = (otherLine.x2-otherLine.x) * (y-otherLine.y) - (otherLine.y2-otherLine.y) * (x-otherLine.x);
   numerb = (x2-x) * (y-otherLine.y) - (y2-y) * (x-otherLine.x);
   /* Are the line coincident? */
   if (abs(numera) < zEPSILON && abs(numerb) < zEPSILON && abs(denom) < zEPSILON) {
    point.x = (x + x2) / 2.0;
    point.y = (y + y2) / 2.0;
    return true;
   }
   /* Are the line parallel */
   if (abs(denom) < zEPSILON) {
    point.x = 0.0;
    point.y = 0.0;
    point.exists = false;
    return false;
   }
   /* Is the intersection along the the segments */
   mua = numera / denom;
   mub = numerb / denom;
   if (mua < 0.0 || mua > 1.0 || mub < 0.0 || mub > 1.0) {
    point.x = 0.0;
    point.y = 0.0;
    point.exists = false;
    return false;
   }
   point.x = x + mua * (x2 - x);
   point.y = y + mua * (y2 - y);
   point.exists = true;
   return true;
  }

  //! Returns true if a circle and a circle are colliding.  Returns the intersection points as a line.
  inline bool Cartesian::CircleCircle( Cartesian circle, Cartesian &intersection) {
   if ( R == 0.0 ) {
    intersection.Zero();
    return circle.Within(x,y);
   } else if ( circle.R == 0.0 ) {
    intersection.Zero();
    return Within(circle.x,circle.y);
   }
   // 'point 1'
   double dx = circle.x - x;
   double dy = circle.y - y;
   // Determine the straight-line distance between the centers. 
   double dd = hypot(dx,dy); // Suggested by Keith Briggs replaces: //d = sqrt((dy*dy) + (dx*dx));
   if (dd > (R + circle.R)) return false;
   else if (dd < abs(R - circle.R)) return false;
   /* 'point 2' is the point where the line through the circle intersection point crosses the line between the circle centers. */
   double sqR=R*R;
   double aa = ((sqR) - (circle.R*circle.R) + (dd*dd)) / (2.0 * dd);
   double dx2 = dx + (dx * aa/dd);
   double dy2 = dy + (dy * aa/dd);
   double hh = sqrt((sqR) - (aa*aa));
   double rx = -dy * (hh/dd);
   double ry = dx * (hh/dd);
   /* Determine the absolute intersection points. */
   intersection.Corners( dx2 + rx, dx2 - rx, dy2 + ry, dy2 - ry );
   return true;
  }

  //! Returns true if a sphere and a sphere are colliding.  Returns the overlap.
  inline bool Cartesian::SphereSphere( Cartesian box, Cartesian &overlap) {
   return true; // does not yet work!
  }

  //! Returns true if the 2d rect and 2d rect are colliding.  Returns the overlap.
  inline bool Cartesian::RectRect( Cartesian b, CoplanarLinesResults &out, Cartesian &overlap ) {
   out.Clear();
   if (!b.approximation) b.Box();
   if (!approximation) Box();
   Cartesian *Abox=null,*Bbox=null; // Abox should be the bigger box
   if ( this->area > b.area ) { Abox=this; Bbox=&b; } else { Abox=&b; Bbox=this; }
   if ( !Bbox->Overlaps(*Abox) ) return false;
   bool colliding=Bbox->approximation->Collides( Abox->approximation, out );
   if ( colliding ) {
    if ( out.count == 1 ) {
     OUTPUT("Box::Collides(box) reports an invalid case where boxes collided on less than two points.\n");
     return true;
    } else if ( out.count == 2 ) {
     CoplanarLinesResult *A=(CoplanarLinesResult *) out.first;
     CoplanarLinesResult *B=(CoplanarLinesResult *) out.last;
     // There's one case where if a,b are on a vertical or horizontal, we must calculate the
     // overlapping box.
     if ( A->x==B->x) { // Both points fall on the x or x2 side
      if ( Bbox->x2 < Abox->MaxX() ) // We're colliding on left side of b
       overlap.Set(Bbox->x2,A->y,A->x,B->y);
      else overlap.Set(Bbox->x,A->y,B->x,B->y);
     } else if ( A->y==B->y ) { // Both points fall on the y or y2 side
      if ( Bbox->y2 < Abox->MaxY() )
       overlap.Set(A->x,A->y,B->x,Bbox->y2);
      else overlap.Set(A->x,Bbox->y,B->x,B->y);
     } else
      overlap.Set(A->x,A->y,B->x,B->y); // thus the name...
    } else if ( out.count > 2 ) {
     // If out->count > 2 the boxes share common sides, so we must find greatest and least points.
     Cartesian min, max;
     out.Min(&min);
     out.Max(&max);
     overlap.Set(min.x,min.y,max.x,max.y);
    }
   }
   if ( out.count == 0 ) {
    if ( area < b.area ) overlap.Set(*this);
    else overlap.Set(b);
   }
   // out->count could be 0 because we are within the box
   return colliding;
  }

  inline bool operator == ( Cartesian& a, Cartesian& b ) {
   return a.x == b.x && a.y == b.y && a.z == b.z && a.x2 == b.x2 && a.y2 == b.y2 && a.z2 == b.z2;
  }

  //! Treating the list as a series of coplanar lines, test another line against it, sorted by distance
  inline bool Cartesians::Collides( Cartesian line, CoplanarLinesResults &out ) {
   out.Clear();
   out.sx=line.x;
   out.sy=line.y;
   Cartesian collision;
   FOREACH(Cartesian,L) if ( L->LineLine(line,collision) ) out.Add(L,&collision);
   out.SortDistance();
   return (out.count > 0);
  }

  //! Treating the list as a series of coplanar lines, test another line against it but sort results in reverse distance
  inline bool Cartesians::Collides( Cartesian line, CoplanarLinesResults &out, bool reverseSort ) {
   out.Clear();
   out.sx=line.x2;
   out.sy=line.y2;
   Cartesian collision;
   FOREACH(Cartesian,L) if ( L->LineLine(line,collision) ) out.Add(L,&collision);
   out.SortDistance();
   out.ReverseOrder();
   return (out.count > 0);
  }

  //! Treating the list as a series of coplanar lines, test another series of lines against it
  inline bool Cartesians::Collides( Cartesians *lines, CoplanarLinesResults &out ) {
   Cartesian collision;
   FOREACH(Cartesian,L) EACH(lines->first,Cartesian,M) if ( L->LineLine(*M,collision) ) {
    out.Add(M,&collision);
   }
   out.SortDistance();
   return (out.count > 0);
  }

  inline string file_as_string( const char *filename ) {
   ifstream input_file(filename);
   if (!input_file.is_open()) {
    cerr << "Could not open the file - '"
     << filename << "'" << endl;
    return string("");
   }
   return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
  }

  inline string file_as_string_streams( const char *filename ) {
   std::ifstream t(filename);
   std::string str;
   t.seekg(0, std::ios::end);   
   str.reserve((unsigned int) t.tellg());
   t.seekg(0, std::ios::beg);
   str.assign((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());
   return str;
  }

  inline bool string_as_file(const char *text, const char *fn) {
   std::ofstream out(fn);
   if (!out.is_open()) return false;
   out << text;
   out.close();
   return true;
  }

  // Tests if a file exists.
  inline bool file_exists(const char *fn) {
   std::ifstream f(fn);
   if (!f.is_open()) return false;
   f.close();
   return true;
  }

#endif // _ZEROTYPES_HPP_
#endif // C++
