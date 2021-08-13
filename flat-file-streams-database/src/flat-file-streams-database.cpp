//============================================================================
// Name        : flat-file-streams-database.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : http://www.cplusplus.com/forum/beginner/191199/
//============================================================================

#include <iostream>
#include <set>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

struct person
{
    // let us keep it simple for now
    string first_name ; // invariant: no embedded spaces eg. "Bjarne"
    string last_name ; // invariant: no embedded spaces eg. "Stroustrup"
    string date_of_birth ; // invariant: no embedded spaces eg. "30-December-1950"
};

// write the information to an output stream as a single line of text
// first_name<space>last_name<space>date_of_birth
ostream& put_person( ostream& stm, const person& per )
{ return stm << per.first_name << ' ' << per.last_name << ' ' << per.date_of_birth ; }

// same as above, overloaded stream insertion operator
ostream& operator<< ( ostream& stm, const person& per )
{ return put_person( stm, per ) ; }

// read the information written with put_person from an input stream into per
istream& get_person( istream& stm, person& per )
{
    string line ;
    // function ws removes whitespace from input stream
    if( getline( stm >> ws, line ) ) // if a non-empty line of text was read successfully
    {
        istringstream strstm(line) ; // create a stream that reads from the line of text

        // if first_name<space>last_name<space>date_of_birth<end_of_string> was successfully read, we are done
        if( strstm >> per.first_name >> per.last_name >> per.date_of_birth ) return stm ;
    }

    // handle input failure
    stm.clear( stm.failbit ) ; // put the stream into a failed state
    return stm ; // and return it
}

// same as above, overloaded stream insertion operator
istream& operator>> ( istream& stm, person& per )
{ return get_person( stm, per ) ; }

// !!! This is how the database is sorted by last name !!!
// make the type person LessThanComparable
// keep it simple for now: compare only last_name, case-sensitive
bool operator< ( const person& a, const person& b ) { return a.last_name < b.last_name ; }

int main()
{
    const string file_name = "heroes.txt" ;

    {
        // create a std::set of persons
        // std::set an associative container that contains a sorted set of unique objects
        //          the default comparison function assumes that the type is LessThanComparable (uses the < operator)
    	// Note: The defined above overload operator 'bool operator<' overrides the default comparison function to sort on last_name.
        // http://en.cppreference.com/w/cpp/container/set
        std::set<person> heroes =
        {
            { "Donald","Knuth", "January-10-1938" },
            { "Alan", "Kay", "May-17-1940" },
            { "Dennis", "Ritchie", "September-9-1941" },
            { "Ken", "Thompson", "February-4-1943" },
            { "Alan", "Kay", "May-17-1940" },
            { "Alex", "Stepanov", "November-16-1950" },
        };

       ofstream file(file_name) ; // open a file for writing
       // http://www.stroustrup.com/C++11FAQ.html#for
       for( const auto& hero : heroes ) {
    	   file << hero << '\n' ; // write each person to the file
       }
    }

    {
       set<person> heroes ; // create an empty set of persons

       {
           ifstream file(file_name) ; // open the file for reading
           person a_hero ;
           while( file >> a_hero ) heroes.insert(a_hero) ; // insert each person read from the file into the set
       }

       // add stroustrup to the set of persons
       // http://en.cppreference.com/w/cpp/container/set/insert
       heroes.insert( { "Bjarne", "Stroustrup", "30-December-1950" } ) ;

       // query on (case-sensitive) last name "Ritchie"
       // http://en.cppreference.com/w/cpp/container/set/find
       const auto iter = heroes.find( { "", "Ritchie", "" } ) ; // specify last name
       if( iter != heroes.end() ) // if found, print last and first name, date of birth
            cout << "found: " << iter->last_name << ", " << iter->first_name << " (born " << iter->date_of_birth << ")\n" ;

       // print out the list of persons, sorted on last name
       int n = 0 ;
       cout << "\n----------\nheroes\n--------------\n" ;
       for( const auto& hero : heroes ) cout << ++n << ". " << hero << '\n' ;

       // write the updated list back to the file
       {
           ofstream file(file_name) ; // open a file for writing
           for( const auto& hero : heroes ) file << hero << '\n' ; // write each person to the file
       }

       // print out the contents of the updated file
       cout << "\n\n----------\ncontents of file '" << file_name << "'\n--------------\n\n"
                 << ifstream(file_name).rdbuf() ;
    }
}
