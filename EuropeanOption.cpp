#include "EuropeanOption.h"// Declarations of functions
#include <math.h> // For mathematical functions, e.g. exp()


double EuropeanOption::PutPrice() 
{
	double tmp = sig * sqrt(T);
	double d1 = (log(U / K) + (b + (sig*sig)*0.5) * T) / tmp;
	double d2 = d1 - tmp;
	return (K * exp(-r * T)* CND(-d2)) - (U * exp((b - r)*T) * CND(-d1));
}

// Kernel Functions
double EuropeanOption::CallPrice() 
{
	double tmp = sig * sqrt(T);
	double d1 = (log(U / K) + (b + (sig*sig)*0.5) * T) / tmp;
	double d2 = d1 - tmp;
	return (U * exp((b - r)*T) * CND(d1)) - (K * exp(-r * T)* CND(d2));
}

double EuropeanOption::CallDelta() 
{
	double tmp = sig * sqrt(T);
	double d1 = (log(U / K) + (b + (sig*sig)*0.5) * T) / tmp;
	return exp((b - r)*T) * CND(d1);
}
double EuropeanOption::PutDelta() 
{
	double tmp = sig * sqrt(T);
	double d1 = (log(U / K) + (b + (sig*sig)*0.5) * T) / tmp;
	return exp((b - r)*T) * (CND(d1) - 1.0);
}
void EuropeanOption::init()
{ // Initialise all default values
// Default values
	r = 0.08;
	sig = 0.30;
	K = 65.0;
	T = 0.25;
	U = 60.0; // U == stock in this case
	b = r; // Black and Scholes stock option model (1973)
	optType = "C"; // European Call Option (the default type)
}
void EuropeanOption::copy( EuropeanOption& o2)
{
	r = o2.r;
	sig = o2.sig;
	K = o2.K;
	T = o2.T;
	U = o2.U;
	b = o2.b;
	optType = o2.optType;
}
EuropeanOption::EuropeanOption()
{ // Default call option
	init();
}
EuropeanOption::EuropeanOption( EuropeanOption& o2)
{ // Copy ructor
	copy(o2);
}
EuropeanOption::EuropeanOption( std::string& optionType)
{ // Create option type
	init();
	optType = optionType;
	if (optType == "c")
		optType = "C";
}
EuropeanOption::~EuropeanOption()
{ // Destructor
}
EuropeanOption& EuropeanOption::operator = ( EuropeanOption& opt2)
{ // Assignment operator (deep copy)
	if (this == &opt2) return *this;
	copy(opt2);
	return *this;
}
// Functions that calculate option price and sensitivities
double EuropeanOption::Price() 
{
	if (optType == "C")
	{
		return CallPrice();
	}
	else
		return PutPrice();
}
double EuropeanOption::Delta() 
{
	if (optType == "C")
		return CallDelta();
	else
		return PutDelta();
}
// Modifier functions
void EuropeanOption::toggle()
{ // Change option type (C/P, P/C)
	if (optType == "C")
		optType = "P";
	else
		optType = "C";
}

double EuropeanOption::CND(double d) 
{
	 double       A1 = 0.31938153;
	 double       A2 = -0.356563782;
	 double       A3 = 1.781477937;
	 double       A4 = -1.821255978;
	 double       A5 = 1.330274429;
	 double RSQRT2PI = 0.39894228040143267793994605993438;

	double
		K = 1.0 / (1.0 + 0.2316419 * fabs(d));

	double
		cnd = RSQRT2PI * exp(-0.5 * d * d) *
		(K * (A1 + K * (A2 + K * (A3 + K * (A4 + K * A5)))));

	if (d > 0)
		cnd = 1.0 - cnd;

	return cnd;
}
