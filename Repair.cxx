#include <algorithm> // find(), move(), move_backward(), equal(), swap(), lexicographical_compare() // written by Chris Huynh
#include <cstddef> // size_t
#include <iomanip> // setw()
#include <string>
#include <cstdlib>
#include <cmath>
#include <fstream>

#include "Repair.hpp"

namespace // unnamed, autonomous namespace
{
// Avoid direct equality comparisons on floating point numbers.
// Two values are equal if they are "close enough", which is represented
// by Epsilon.
// Usually, this is a pretty small number, but since we are dealing with
// money for a repair cost (only two, maybe three decimal places) we can
// be a bit more tolerant.
// Two floating point values are considered equal if they are within
// EPSILON of each other.
constexpr auto EPSILON = 1.0E-4;
}

/**********************************************
** Public implementations, types, and objects
** for class Repair
************************************************/

/************************
** Constructor
************************/
Repair::Repair(const std::string& name, const std::string& vehicle, const std::string& date, const std::string& services, const double& cost)
// Use the constructor initialization list
: _name(name), _vehicle(vehicle), _date(date), _services(services), _cost(cost)
{} // Avoid setting values in constructor's body (when possible)

/*************************
** Queries or getters
**************************/
std::string Repair::name() const
{
return _name;
}

std::string Repair::vehicle() const
{
return _vehicle;
}

std::string Repair::date() const
{
return _date;
}

std::string Repair::services() const
{
return _services;
}

double Repair::cost() const
{
return _cost;
}

/***********************************
** Mutators or setters
************************************/
void Repair::set_name(const std::string& newName)
{
_name = newName;
}

void Repair::set_vehicle(const std::string& newVehicle)
{
_vehicle = newVehicle;
}

void Repair::set_date(const std::string& newDate)
{
_date = newDate;
}

void Repair::set_services(const std::string& newServices)
{
_services = newServices;
}

void Repair::set_cost(double newCost)
{
_cost = newCost;
}

/***********************************
** Friend functions: read and write
************************************/

std::istream& operator>>(std::istream& stream, Repair& request)
{
Repair workingItem;

char delimiter = ',';

// written by Chris Huynh
// Assume fields are separated by commas and string attributes are enclosed with double quotes. For example:
// "John Doe", "Isuzu", "9/29 10:00 am", "synthetic oil change" , 91.11
  
stream >> std::quoted(workingItem._name) >> delimiter
>> std::quoted(workingItem._vehicle) >> delimiter
>> std::quoted(workingItem._date) >> delimiter
>> std::quoted(workingItem._services) >> delimiter
>> workingItem._cost;

// If all okay, move workingItem into the returned request.
// Copying the information also "works" but moving is more
// efficient. Note this uses Repair's move assignment operator. // written by Chris Huynh
if (stream) request = std::move(workingItem);

return stream;
}

std::ostream& operator<<(std::ostream& stream, const Repair& request)
{
const std::string delimiter = ", ";
  
stream << std::quoted(request.name()) << delimiter
<< std::quoted(request.vehicle()) << delimiter
<< std::quoted(request.date()) << delimiter
<< std::quoted(request.services()) << delimiter
<< request.cost();
  
return stream;
}


/*************************************************
** Ordinary functions: Relational Operators
**************************************************/
bool operator==(const Repair& lhs, const Repair& rhs)
{
// Implement equality in terms of less than to enforce identical
// column priority ordering and floating point epsilon comparison tolerance.  // written by Chris Huynh
return lhs.name() == rhs.name()
&& lhs.vehicle() == rhs.vehicle()
&& lhs.date() == rhs.date()
&& lhs.services() == rhs.services()
&& std::abs(lhs.cost() - rhs.cost()) < EPSILON;
}

bool operator!=(const Repair& lhs, const Repair& rhs)
{
return !(lhs == rhs);
}
// written by Chris Huynh
