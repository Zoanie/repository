//============================================================================
// Name        : boost-multi-index.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.martyndavis.com/?p=633
//============================================================================
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/key_extractors.hpp>

//#include <boost/multi_index/member.hpp>
//#include <boost/multi_index/composite_key.hpp>
//#include <boost/multi_index/ranked_index.hpp>
//#include <boost/multi_index/ordered_index.hpp>
//#include <boost/multi_index/identity.hpp>
//#include <boost/multi_index/indexed_by.hpp>
//#include <boost/multi_index/mem_fun.hpp>
//#include <boost/multi_index/global_fun.hpp>

#include <string>
#include <iostream>
#include <functional>

using namespace std;
using boost::multi_index_container;
using namespace boost::multi_index;

/*
 * Getting Started with Boost MultiIndex
 *
 * Imagine you’ve got a struct like this:
 *
 * 	struct Person
 *  {
 *     std::string  Name,
 *     unsigned int Age,
 *     std::string  PostCode // "Zip" code
 *  };
 *
 * If you created a std::map of Person, “indexed” by, say, an arbitrary ID value,
 * you’d be able to find them quickly by that ID. But what if you wanted then to
 * find everyone over the age of 50? You might consider creating a secondary “index”
 * structure, a std::multimap that keys on age and its data is the ID, i.e. the
 * key into your main structure. This will work, of course, but you now have two
 * data structures to worry about, and to keep synchronized. And control access
 * to in the presence of multiple threads. If you then find you want other “indices”
 * it just gets even more complicated.
 *
 */
struct Vehicle
{
    size_t       Id;
    std::string  Make;
    std::string  Model;
    unsigned int YearMade;
    bool         SingleCylinder;
};

// Index "tags" used by Boost MultiIndex.
// Only purpose is to allow us to refer to indices
// by name rather than a "magic" positional number
struct IdxPrimaryKey{};
struct IdxYearMade{};
struct IdxMakeModel{};
struct IdxSingleCylinder{};

template<typename Tidx, typename Trecord>
void IterateOver(
    const Tidx& idx,
    std::function<void(const Trecord& rec)> func
    )
{
    auto it = idx.begin();
    while ( it != idx.end() )
    {
        func(*it++);
    }
}

// https://gksquiz.blogspot.com/2015/04/pointers-into-arrays-c-mcq.html
void cpp_mcq()
{
	// 2 rows of 4 elements
	int a[2][4] = {3, 6, 9, 12, 15, 18, 21, 24};
	// a[1] = Pointer to a[1][0]
	// (a[1] + 2) = Pointer to: Second row of 4 elements a[1] + index 2 in second row
	// (a + 1) = Pointer to (address of) &a[1][0]
	// *(a + 1) = a[1][0]
	// *(a + 1) + 2) = a[1][2]
	//
	cout << *(a[1] + 2) << *(*(a + 1) + 2) << 2[1[a]];
	return;
}
/*
 * Second example: https://steemit.com/cpp/@jd3/c-boost-multiindex-intro
 *
 * Other example: https://theboostcpplibraries.com/boost.multiindex
 *
 */
class car {
public:
    std::string name;

    car(const std::string& name, int hp, bool is_fast)
        : name(name), hp_(hp), is_fast_(is_fast) {}

    bool isFast() const { return is_fast_; }
    friend int getHp(const car& c); // { return c.hp_; }
private:
    int         hp_;
    bool        is_fast_;
};

int getHp(const car& c) { return c.hp_; }

void carTest()
{
    namespace bmi = boost::multi_index;
    typedef multi_index_container<
    	car,         // element data structure
		indexed_by<  // Here is put the interfaces you will use with the container
        	// interface 0
			hashed_unique<  // - all names must be unique and lookup by has value
            	// look up by member variable
            	// < data_struct,  type,  member variable >
				member<car, string, &car::name>
				>,  // looked up by name
			// interface 1
			hashed_non_unique<  // - not unique and look up by member function
					// look up by constant member function
					//  < data_struct, type, member function >
					const_mem_fun<car, bool, &car::isFast> >,  // looked up by isFast()
			// interface 2
			ordered_non_unique< // - ordered not unique look up by global function
				// look up by global function
				//        param_type, return type, function name
				global_fun<const car&, int, getHp> >    // looked up by global function getHp()
    	>
	> cars_multi_idx_type;  // new container type

    cars_multi_idx_type cars;

    // Each car we put in this container now must have a unique name.
    cars.insert(car("mustang", 400, true));
    cars.insert(car("prius",   180, false));
    cars.insert(car("370z",    350, true));
    cars.insert(car("camaro",  380, true));

    // Member function find: when you don't specify an interface, the first one is used by default.
    auto itr = cars.find("mustang");
    if (itr != cars.end())
        cout << itr->isFast() << endl;

    // First thing you do is get the interface, unless you are using the 0th interface by default
    // to access an index (interface).

    // Now we are using the get() method to use the 'ordered_non_unique<>' interface.
    auto& hp_index = cars.get<2>();

    // Now you can look up cars as if they were contained in an ordered_non_unique container
    // with a the global function getHp() used to return an iterator to the cars hp_.
    auto begin = hp_index.lower_bound(300);
    auto end   = hp_index.upper_bound(500);

    // For each hp_index from begin to end get the rest of the car object
    for_each(begin, end, [](const car& c) {
        std::cout << c.name;
        if (c.isFast())
            cout << " is fast!\n";
        else
        	cout << " is slooow...\n";
    });

    // You can also make other iterators to different indexes (interfaces) by projecting them.
    // A name iterator using interface 0 is created with our existing 'hp_index' iterator 'begin'.
    auto name_itr    = cars.project<0>(begin);
    auto last_name_itr    = cars.project<0>(end);
    while(name_itr != cars.end())
    {
    	cout << "Name itr begin to cars.end() found " << name_itr->name << endl;
    	name_itr++;
    }
    name_itr    = cars.project<0>(begin);
    while(name_itr != last_name_itr)
    {
    	cout << "Name itr begin to end found " << name_itr->name << endl;
    	name_itr++;
    }

    //auto is_fast_itr = cars.project<1>(begin);

    /* Get an iterator from an element */
    itr = cars.find("mustang");
    const car& c = *itr;
    itr = cars.iterator_to(c);

    /*
     * You CAN NOT change an element with an iterator. This is beacuse the iterator is only used
     * for the specific interface. If you want to modify an element you will need to update it
     * for use with every interface. To update an element you use the member function modify and
     * pass the iterator and a lambda function. The lambda function will get a reference to your
     * object, car, at the position of the itr. Now you can change the car object.
     */
    cars.modify(itr, [](car& c) {
        c.name = "shelby cobra";  // changes 'mustang' to 'shelby cobra'
    });

    /* modify by key */
    cars.modify_key(itr, [](std::string& n) {
        n = "shelby cobra";
    });

    /* Replace elements */
    cars.replace(itr, car("civic", 200, false));
}

int main()
{

    // Definition of our "database" format:
    multi_index_container<
        Vehicle,
        indexed_by<
            // The "primary key"
            ordered_unique<
                tag<IdxPrimaryKey>,
                member<Vehicle, size_t, &Vehicle::Id>
            >,
            // A simple key
            ordered_non_unique<
                tag<IdxYearMade>,
                member<
                    Vehicle, unsigned int, &Vehicle::YearMade
                >
            >,
            // Another simple key
            ordered_non_unique<
                tag<IdxSingleCylinder>,
                member<
                    Vehicle, bool, &Vehicle::SingleCylinder
                >
            >,
            // A composite key:
            ordered_non_unique<
                tag<IdxMakeModel>,
                composite_key<
                    Vehicle,
                    member<
                        Vehicle, std::string, &Vehicle::Make
                    >,
                    member<
                        Vehicle, std::string, &Vehicle::Model
                    >
                >
            >
        >
    > vehicles;

    vehicles.insert( { 1, "Vincent", "Rapide",    1950, false } );
    vehicles.insert( { 2, "BSA",     "Gold Star", 1958, false } );
    vehicles.insert( { 3, "Triumph", "Thruxton",  2010, false } );
    vehicles.insert( { 4, "Ariel",   "Square 4",  1959, false } );
    vehicles.insert( { 5, "Brough",  "Superior",  1925, false } );
    vehicles.insert( { 6, "Vincent", "Comet",     1951, true  } );
    vehicles.insert( { 7, "Norton",  "Commando",  1973, false } );

    // Iterate using "primary key" (ID) as index
    auto& idxId = vehicles.get<IdxPrimaryKey>();
    std::cout << "---------------------\n"
              << "Ordered by ID:\n" << std::endl;
    IterateOver<decltype(idxId), Vehicle>(
            idxId,
            [](const Vehicle& vec
        )
        {
            std::cout   << vec.Id << ": " << vec.Make
                        << " " << vec.Model << std::endl;
        }
    );

    std::cout << "---------------------\n"
              << "Ordered by year of manufacture:\n" << std::endl;
    // Iterate using year of manufacture as our index:
    auto& idxSimple = vehicles.get<IdxYearMade>();
    IterateOver<decltype(idxSimple), Vehicle>(
            idxSimple,
            [](const Vehicle& vec
        )
        {
            std::cout   << vec.YearMade << ": " << vec.Make
                        << " " << vec.Model << std::endl;
        }
    );

    std::cout << "---------------------\n"
              << "Ordered by marque then model:\n" << std::endl;
    // Iterate using our composite key (make/model):
    auto& idxComposite = vehicles.get<IdxMakeModel>();
    IterateOver<decltype(idxComposite), Vehicle>(
        idxComposite, [](const Vehicle& vec)
        {
            std::cout << vec.Make << " "
                      << vec.Model << std::endl;
        }
    );
    std::cout << "---------------------" << std::endl;

    {
        // Find a specific item:
        auto it = idxId.find(5); // should check result IRL!
        std::cout << "Item 5 is " << it->Make << " " << it->Model
                  << std::endl;
    }
    std::cout << "---------------------\n"
              << "Bikes made in the fifties:\n" << std::endl;

    {
        // Find a range of items -- bikes made in the 50s:
        auto it    = idxSimple.lower_bound( 1950 );
        auto itEnd = idxSimple.upper_bound( 1959 );
        while ( it != itEnd )
        {
            std::cout << it->Make << " " << it->Model << " ("
                      << it->YearMade << ")" << std::endl;
            ++it;
        }
    }
    std::cout << "---------------------\n"
              << "Single-cylinder bikes:\n" << std::endl;
    {
        // Find a range of items -- bikes with just one pot
        auto& idxSinglePot = vehicles.get<IdxSingleCylinder>();
        auto pr = idxSinglePot.equal_range( true );
        auto it = pr.first;
        auto itEnd = pr.second;
        while ( it != itEnd )
        {
            std::cout << it->Make << " " << it->Model << " ("
                      << it->YearMade << ")" << std::endl;
            ++it;
        }
    }
    std::cout << "---------------------" << std::endl;

    /*
    cout << "CPP MCQ:" << endl;
    cpp_mcq();

    cout << "Multi-index Car Container:" << endl;
	*/
	carTest();

    return 0;
}
