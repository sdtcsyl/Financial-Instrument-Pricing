#pragma once
#include <iostream>
#include <string>

// EurpeanOption.hpp
class EuropeanOption
{
private:
	void init(); // Initialise all default values
	void copy( EuropeanOption& o2);
	// "Kernel" functions for option calculations
	double CallPrice() ;
	double PutPrice() ;
	double CallDelta() ;
	double PutDelta();
	double CND(double d);
public:
	// Public member data for convenience only
	double r; // Interest rate
	double sig; // Volatility
	double K; // Strike price
	double T; // Expiry date
	double U; // Current underlying price
	double b; // Cost of carry
	std::string optType; // Option name (call, put)
public:
	// Constructors
	EuropeanOption(); // Default call option
	EuropeanOption( EuropeanOption& option2); // Copy ructor
	EuropeanOption( std::string& optionType); // Create option type
	// Destructor
	virtual ~EuropeanOption();
	// Assignment operator
	EuropeanOption& operator = ( EuropeanOption& option2);
	// Functions that calculate option price and (some) sensitivities
	double Price() ;
	double Delta() ;
	// Modifier functions
	void toggle(); // Change option type (C/P, P/C)
};
