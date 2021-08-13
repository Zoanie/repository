//============================================================================
// Name        : testdome-questions.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.testdome.com/d/cpp-interview-questions/7
//============================================================================

#include <tuple>
#include <stdexcept>
#include <iostream>
#include <string>
#include <cmath>
#include <utility>
#include <unordered_set>
#include <vector>
#include <string>
#include <deque>
#include <stdexcept>
#include <deque>
#include <functional>
#include <algorithm>
#include <boost/lexical_cast.hpp>
#include <cctype>
#include <iterator>


using namespace std;

class TrainComposition
{
public:
    void attachWagonFromLeft(int wagonId)
    {
        //cout << "left is wagon " << wagonId << endl;
        trainWagons.emplace_back(wagonId);
    }

    void attachWagonFromRight(int wagonId)
    {
        //cout << "right is wagon " << wagonId << endl;
        trainWagons.emplace_front(wagonId);
    }

    int detachWagonFromLeft()
    {
    	int wagon = trainWagons.back();
        //cout << "removing left wagon " << wagon << endl;
        trainWagons.pop_back();
        return wagon;
    }

    int detachWagonFromRight()
    {
        int wagon = trainWagons.front();
        //cout << "removing right wagon " << wagon << endl;
        trainWagons.pop_front();
        return wagon;
    }

private:
    deque<int> trainWagons;
};

#ifndef RunTests
int trainTest()
{
    TrainComposition train;
    train.attachWagonFromLeft(7);
    train.attachWagonFromLeft(13);
    std::cout << train.detachWagonFromRight() << "\n"; // 7
    std::cout << train.detachWagonFromLeft(); // 13
    return 0;
}
#endif

#include <iostream>
#include <string>
#include <vector>

class MultipleChoiceTest
{
public:
    MultipleChoiceTest(int questionsCount)
    {
        this->questionsCount = questionsCount;
        answers.resize(questionsCount);
        times.resize(questionsCount);
        for (int i = 0; i < questionsCount; i++)
        {
            answers[i] = 0;
            times[i] = 0;
        }
    }

    void setAnswer(int questionIndex, int answer)
    {
        answers[questionIndex] = answer;
    }

    int getAnswer(int questionIndex) const
    {
        return answers[questionIndex];
    }

protected:
    int questionsCount;
    vector<int> answers;
    vector<int> times;

};

class TimedMultipleChoiceTest : public MultipleChoiceTest
{
public:
    TimedMultipleChoiceTest(int questionsCount)
        : MultipleChoiceTest(questionsCount)
    {
        //times.resize(questionsCount);
    }

    void setTime(int questionIndex, int time)
    {
        times[questionIndex] = time;
    }

    int getTime(int questionIndex) const
    {
        return times[questionIndex];
    }

};

void executeTest()
{
    TimedMultipleChoiceTest test(5);
    for (int i = 0; i < 5; i++)
    {
        test.setAnswer(i, i);
    }

    for (int i = 0; i < 5; i++)
    {
        std::cout << "Question " << i + 1 << ", correct answer: " << test.getAnswer(i) << "\n";
    }
}

int mc_test_main()
{
    for (int i = 0; i < 3; i++)
    {
        std::cout << "Test: " << i + 1 << "\n";
        executeTest();
    }
    return 0;
}

/*
 * As part of a data processing pipeline, complete the implementation of the makePipeline method:
 *   o The method should accept a vector of functions, and it should return a new function that
 *     accepts one parameter arg.
 *   o The returned function should call the first function in the makePipeline with the parameter
 *     arg, and call the second function with the result of the first function.
 *   o The returned function should continue calling each function in the makePipeline in order,
 *     following the same pattern, and return the value from the last function.
 */

template<class T>
function<T (T)> makePipeline(const vector<function<T (T)>>& funcs) {
    return [&funcs] (const T& arg) {
        T v = arg; // initial value
        for (const auto &f: funcs) {
            v = f(v); // sequentially apply a function.
        }
        return v;
    };
}

int makePipelineMain()
{
    vector<function<int (int)>> functions;
    functions.push_back([] (int x) -> int { return x * 3; });
    functions.push_back([] (int x) -> int { return x + 1; });
    functions.push_back([] (int x) -> int { return x / 2; });

    // std::function<int (int)> func = makePipeline(functions);
    auto func = makePipeline(functions);
    cout << "makePipeline function returns " << func(3) << endl; // should print 5
    return 0;
}

// Inserts a key in arr[] of given capacity. n is current
// size of arr[]. This function returns n+1 if insertion
// is successful, else n.
int insertSorted(int arr[], int n, int key, int capacity)
{
    // Cannot insert more elements if n is already
    // more than or equal to capcity
    if (n >= capacity)
        return n;

    int i;
    for (i = n - 1; (i >= 0 && arr[i] > key); i--)
        arr[i + 1] = arr[i];

    arr[i + 1] = key;

    return (n + 1);
}

// Get a count of numbers less than a specified number
int countLessThanNumbers(const vector<int>& sortedVector, int testVal)
{

    auto itlow = lower_bound(begin(sortedVector), end(sortedVector), testVal);
    return (itlow - begin(sortedVector));

}

int countMoreThanNumbers(const vector<int>& sortedVector, int testVal)
{

    auto ithigh = upper_bound(begin(sortedVector), end(sortedVector), testVal);
    return (end(sortedVector) - ithigh);

}


#ifndef RunTests
void countNumbersMain()
{
    vector<int> v { 1, 3, 5, 7, 9, 15, 20 };
    cout << "Count of numbers lt than 6 = " << countLessThanNumbers(v, 6) << endl;
    cout << "Count of numbers gt than 6 = " << countMoreThanNumbers(v, 6) << endl;
}
#endif
/*
 * 1. Quadratic Equation
Implement the function findRoots to find the roots of the quadratic equation: ax2 + bx + c = 0.
If the equation has only one solution, the function should return that solution as both elements
of the pair. The equation will always have at least one solution.

The roots of the quadratic equation can be found with the following formula:

x = (-b +/- sqrt(b**2 - (4*a*c)) / 2*a

For example, the roots of the equation 2x**2 + 10x + 8 = 0 are -1 and -4.
 */
pair<double, double> findRoots(double a, double b, double c)
{
	double num1 = 0.0;
	double num2 = 0.0;
	pair<double, double> result;
	pair<double, double> nan_result;

	nan_result = make_pair(nan(""), nan(""));

	if(isnan(a) || isnan(b) || isnan(c)) {
		return nan_result;
	}
	// divide by zero or very small is nan result
	if(a == 0.0 ) {
		return (nan_result);
	}

	// There are some other strange cases, that can generate a NaN result, but
	// the test question does not seem to be testing against all possibilities.
	// I'm going to add them anyway.
    if (isinf(a) || isinf(b) || isinf(c)) {
		return (nan_result);
    }

	double bsqrd_minus_4ac = b*b - (4*a*c);

	// sqrt of a negative number is nan result
	if( (bsqrd_minus_4ac < 0) || ((bsqrd_minus_4ac == 0.0) && signbit(bsqrd_minus_4ac)) ) {
		return nan_result;
	}

	double sqrt_b_sqrd_minus_4ac = sqrt(bsqrd_minus_4ac);
	num1 = ((-b) + sqrt_b_sqrd_minus_4ac) / (2*a);
	num2 = ((-b) - sqrt_b_sqrd_minus_4ac) / (2*a);

	result = make_pair(num1, num2);

	return result;

    throw std::logic_error("Waiting to be implemented");
}

void find_roots_v2(double a, double b, double c, double *root1, double *root2)
{
	double num1 = 0.0;
	double num2 = 0.0;


	if(isnan(a) || isnan(b) || isnan(c)) {
		*root1 = nan("");
		*root2 = nan("");
	}
	// divide by zero or very small is nan result
	if(a == 0.0 ) {
		*root1 = nan("");
		*root2 = nan("");
	}

	double bsqrd_minus_4ac = b*b - (4*a*c);

	// sqrt of a negative number is nan result
	if( (bsqrd_minus_4ac < 0) || ((bsqrd_minus_4ac == 0.0) && signbit(bsqrd_minus_4ac)) ) {
		*root1 = nan("");
		*root2 = nan("");
	}

	double sqrt_b_sqrd_minus_4ac = sqrt(bsqrd_minus_4ac);
	num1 = ((-b) + sqrt_b_sqrd_minus_4ac) / (2*a);
	num2 = ((-b) - sqrt_b_sqrd_minus_4ac) / (2*a);

	*root1 = num1;
	*root2 = num2;
}

#include <iostream>
#include <vector>


vector<string> unique_names(const vector<string>& names1, const vector<string>& names2)
{
	vector<string> result;
	unordered_set<string> names_set;
	for(auto name : names1)
		names_set.emplace(name);
	for(auto name : names2)
		names_set.emplace(name);
	for(auto name : names_set)
		result.emplace_back(name);
	/*
	result.insert(result.end(), names1.begin(), names1.end() );
	copy(names2.begin(), names2.end(), back_inserter(result) );
	sort(result.begin(), result.end() );
	unique(result.begin(), result.end() );
	*/


	return result;
}

#ifndef RunTests
int unique_main()
{
    vector<string> names1 = {"Ava", "Emma", "Olivia"};
    vector<string> names2 = {"Olivia", "Sophia", "Emma"};

    vector<string> result = unique_names(names1, names2);
    for(auto element : result)
    {
        cout << element << ' '; // should print Ava Emma Olivia Sophia
    }
    return 0;
}
#endif


class TextInput
{
public:
    virtual void add(char c) { value += c; }

    virtual ~TextInput() {}

    std::string getValue() { return value; }


    string value;
};

class NumericInput : public TextInput
{
    virtual void add(char c) {
        if(isdigit(c)) {
           value += c;
        }
    }
};

#ifndef RunTests
int text_main()
{
    TextInput* input = new NumericInput();
    input->add('1');
    input->add('a');
    input->add('0');
    std::cout << input->getValue();
    return 0;
}
#endif
class Node
{
public:
    Node(int value, Node* left, Node* right)
    {
        this->value = value;
        this->left = left;
        this->right = right;
    }

    int getValue() const
    {
        return value;
    }

    Node* getLeft() const
    {
        return left;
    }

    Node* getRight() const
    {
        return right;
    }

private:
    int value;
    Node* left;
    Node* right;
};

class BinarySearchTree
{
public:
    static bool contains(const Node& root, int value)
    {
    	const Node *currentNode = &root;
    	while(currentNode){
    		if(value < currentNode->getValue()){
    			currentNode = currentNode->getLeft();
    		} else if(value > currentNode->getValue()){
    			currentNode = currentNode->getRight();
    		} else if (currentNode->getValue() == value) {
    			return true;
    		}
    	}
    	return false;
    }
};

pair<int, int> findTwoSum(const vector<int>& list, int sum)
{
	auto no_numbers = make_pair(-1, -1);
	int list_size = list.size();
	if(list_size < 2) {
		return no_numbers;
	}
	unordered_map<int, int> sum_map;
	pair<int, int> last_pair;
	sum_map.emplace(list[0], 0);
	int target = sum - list[0];
	bool found_pair = false;

	for(int i=1; i<list_size; i++)
	{
		printf("\nTesting list[%d] = %d", i, list[i]);
		target = sum - list[i];
		auto it = sum_map.find(target);
		if(it != end(sum_map)) {
			if(it->first == target) {
				//printf("\nFound matching sum %d for index pairs %d=%d, %d=%d\n", sum, it->second, it->first, i, list[i]);
				last_pair = make_pair(it->second, i);
				found_pair = true;
			}
		}
		else {
			sum_map.emplace(list[i], i);
		}
	}
	if(found_pair) {
		return last_pair;
	}
	return no_numbers;
}


class Song
{
public:
    static int SongCount;

    Song(std::string name): name(name), nextSong(NULL) {
    	SongCount++;
    }

    void next(Song* song)
    {
        this->nextSong = song;
    }

    bool isRepeatingPlaylist()
    {
    	playList.reserve(2*SongCount);

    	Song* song = this;
    	Song* prevSong;
    	Song* nextSong;

		prevSong = nextSong = song;

    	while(song != NULL)
    	{
        	if(playList.find(song->name) != playList.end()) {
        		return true;
        	}
        	else {
            	playList.emplace(name);
        	}
        	song = song->nextSong;

			prevSong = prevSong->nextSong;
			nextSong = nextSong->nextSong;
			nextSong = (nextSong != NULL) ? nextSong->nextSong : nextSong;
			if(prevSong == NULL || nextSong == NULL)
				return false;
			if(prevSong == nextSong)
				return true;
    	}
    	return false;
    }

	bool isLoop(Song *song) {
		Song* prevSong;
		Song* nextSong;

		prevSong = nextSong = song;

		do {
			prevSong = prevSong->nextSong;
			nextSong = nextSong->nextSong;
			nextSong = (nextSong != nullptr) ? nextSong->nextSong : nextSong;
		} while(prevSong && nextSong && prevSong != nextSong);

		return (prevSong == nextSong) ? true : false;
	}


private:
    const std::string name;
    Song* nextSong;
    unordered_set<string> playList;
};

int Song::SongCount = 0;


#ifndef RunTests
int main()
{
	unique_main();
	return 0;


	int arr[6] = {3,1,5,7,5,9};

	int test;
	test = arr[2]++;

	cout << "Array[2] = " << arr[2] << ", test = " << test;

    vector<int> list = {3, 1, 5, 7, 5, 9};
	findTwoSum(list, 10);

	return 0;

	countNumbersMain();
	return 0;

	makePipelineMain();
	return 0;

	// Test 4
    for (int i = 0; i < 3; i++)
    {
        std::cout << "Test: " << i + 1 << "\n";
        executeTest();
    }
    return 0;

	// Test 3
    Song* first = new Song("Hello");
    Song* second = new Song("Eye of the tiger");

    first->next(second);
    second->next(first);

    std::cout << "isRepeatingPlaylist: " << std::boolalpha << first->isRepeatingPlaylist() << endl;

    cout << "isLoop: " << boolalpha << first->isLoop(first) << endl;

    return 0;

	// Test 2
    Node n1(1, NULL, NULL);
    Node n3(3, NULL, NULL);
    Node n2(2, &n1, &n3);

    std::cout << BinarySearchTree::contains(n2, 3) << endl;

    return 0;

    // Test 1
    std::pair<double,double> roots = findRoots(2, 10, 8);
    std::cout << "Roots: " + std::to_string(roots.first) + ", " + std::to_string(roots.second);
}
#endif
