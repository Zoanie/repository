//============================================================================
// Name        : fb-coding-question.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.youtube.com/watch?v=4UWDyJq8jZg
//============================================================================

// set_union example
#include <iostream>     // std::cout
#include <algorithm>    // std::set_union, std::sort
#include <vector>       // std::vector
#include <set>

using namespace std;

/*
 * Center of mass formula:
 *
 *                   sum of all (position X mass)
 * center of mass = ----------------------------
 *                      sum of all masses
 */

struct vital_record {
	int year_of_birth;
	int year_of_death;
};

vital_record test_population[] =
	{{1920, 2010},{1925, 1980},{1930, 2005},{1985, 1995},{1985, 1985},
	 {1946, 2015},{1930, 1990},{1946, 2010},{1947, 2015},{1955, 2000}};

/*
 */
int main () {
	int first[] = {5,10,15,20,25};
	int second[] = {50,40,30,20,10};
	std::vector<int> v(10);                      // 0  0  0  0  0  0  0  0  0  0
	std::vector<int>::iterator it;

	std::sort (first,first+5);     //  5 10 15 20 25
	std::sort (second,second+5);   // 10 20 30 40 50

	it=std::set_union (first, first+5, second, second+5, v.begin());
	// 5 10 15 20 25 30 40 50  0  0
	v.resize(it-v.begin());                      // 5 10 15 20 25 30 40 50

#ifdef REMOVED
	std::cout << "The union has " << (v.size()) << " elements:\n";
	for (it=v.begin(); it!=v.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
#endif

	int numer_of_records = sizeof(test_population)/sizeof(struct vital_record);
	int year_of_birth = 0;
	int year_of_death = 0;
	int population_size = 0;
	int max_population_size = 0;
	int max_population_year = 0;
	int last_year = 0;
	int first_year = 2021;

	multiset<int> population_yob;
	multiset<int> population_yod;

	for(int i=0; i<numer_of_records; i++)
	{
		year_of_birth = test_population[i].year_of_birth;
		year_of_death = test_population[i].year_of_death;
		if(year_of_death == year_of_birth)
			year_of_death += 1;	// measurement of population includes full birth year

		population_yob.insert(year_of_birth);
		population_yod.insert(year_of_death);

		if(last_year < year_of_birth)
			last_year = year_of_birth;
		if(first_year > year_of_birth)
			first_year = year_of_birth;
	}

	for(int year=first_year; year<last_year; year++)
	{
		population_size += population_yob.count(year) - population_yod.count(year);
		cout << "At year " << year << " population was " << population_size << " people" << endl;;
		if(max_population_size < population_size)
		{
			max_population_size = population_size;
			max_population_year = year;
		}
	}

	cout << "At year " << max_population_year << " population was maximum at " << max_population_size << " people" << endl;;

	return 0;
}


