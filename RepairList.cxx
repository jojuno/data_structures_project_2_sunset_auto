#include <string>     // string
#include <fstream>
#include <iterator>   // next()
#include <stdexcept>  // invalid_argument

#include "RepairList.hpp"

using std::string;
using std::ifstream;

/**********************************************
**  Public/private implementations, types, and objects
** for class RepairList
************************************************/

/*************************************
**  Friend functions: read and write
**************************************/

std::ostream & operator<<( std::ostream & stream, const RepairList & repairlist )
{
	for( const auto & request : repairlist._dailyList )   stream << '\n' << std::setw(5) << request;
	
	return stream;
}


std::istream & operator>>( std::istream & stream, RepairList & repairlist )
{
	Repair request;

	while(stream) {
		stream >> request;
		repairlist.addToList(std::move(request));
	}

	return stream;
}

/***********************
** Constructor
************************/
// TO DO
RepairList::RepairList() = default;

/*********************
** Destructor
*********************/
// TO DO
RepairList::~RepairList() = default;

/************************
** Assignment operator
************************/
// TO DO
RepairList & RepairList::operator+=( const RepairList & rhs)
{
	// Concatenate the right hand side list of repair requests to this list by repeatedly adding each repair at the end of the current repair list
	for (auto it = rhs._dailyList.begin(); it != rhs._dailyList.end(); ++it) {
		addToList(*it);
	}
	return *this;
	       	
}

/***********************
** Queries or getters
************************/
// TO DO
// return the size of the list
// If you decide to use std::forward_list, keep in mind that some implementations of a singly linked list maintain the size (number of elements in the list).  // std::forward_list does not. The size of singly linked list must be calculated on demand by walking the list from beginning to end counting the
// number of elements visited.  The STL's std::distance() function does that, or you can write your own loop.
std::size_t RepairList::size() const
{
	// return the size of the list
	return _dailyList.size();
}

// TO DO
// return the current repair
Repair RepairList::currRepair() const
{
	return *(_nowServicing);
}

/***********************
** Mutators
************************/

// read the list of advanced repair requests from
// the specified file
void RepairList::loadAdvanceList( const std::string& filename )
{
  std::ifstream inFile(filename);
  Repair newRequest;

  if( inFile.is_open() )
    {
      // Read each line
      while (inFile >> newRequest) {
	addToList(newRequest);
      }

      inFile.close();  // file closes 
      _nowServicing = _dailyList.begin();
    }
  else
    {
      throw std::invalid_argument( "Could not open " + filename );
    }
}

// TO DO
// the current repair has been serviced so 
// move the iterator to the next request
void RepairList::next()
{
	//it + 1 not defined
	_nowServicing++;
}


// TO DO
// add a repair request to the current list
void RepairList::addToList( const Repair& newRequest )
{
	_dailyList.push_back(newRequest);
}

// TO DO
// insert a repair request coming from a loyal customer
// right after the current iterator but do not make
// changes to the current iterator
void RepairList::insertLoyal( const Repair& newRequest )
{
	//declare a new it because you can't modify the current one
	auto it = _nowServicing;
	_dailyList.insert(++it, newRequest);

}
