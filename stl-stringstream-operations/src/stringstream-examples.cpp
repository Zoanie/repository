//============================================================================
// Name        : stringstream-examples.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.geeksforgeeks.org/stringstream-c-applications/
//============================================================================

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Good info at: http://ee.usc.edu/~redekopp/cs103/slides/Unit14_Streams.pdf
/*
 * Choosing an I/O strategy
 *
 * 1. Does data use delimiters?
 * 	  - Yes, uses newlines:  Use getline(), '>>' does not recognize difference between space and newline
 * 	  - Yes, uses character: Use getline() with optional 3rd char argument
 * 	  - No, whitespaces only: Use '>>' to skip all whitespaces and convert data type
 * 2. If Yes from step 1, does data need to be broken into smaller pieces?
 *    - Yes: Use stringstream and extract using '>>'
 *    - No: Use string retuned by getline()
 * 3. Is the number of items to be read a constant or variable?
 *    - Yes: Use a for loop and extract values using '>>' to place data into a vector.
 *    - No: Use a while loop with test for failure
 */

/*
 * Stream Class
 *
 * istream is a general purpose input stream. cin is an example of an istream.
 * ostream is a general purpose output stream. cout is an example of an ostream.
 */
/*
 * Extract words between 2 delimiters and insert into a vector.
 *
 * Example testFile1.txt: "garbage stuff....then first delimiter ->(All the words I care about)<- second delimiter and the rest"
 */
vector<string> extractWordsBetweenDelimiters(string fname, char delim1, char delim2)
{
vector<string> targetWords;
ifstream inputFile(fname);

    if(inputFile.fail()) {
    	cout << "Unable to open file " << fname << endl;
    	return targetWords;
    }

	string fline;
	// gets text up to, but not including the first delimiter character.
	getline(inputFile, fline, delim1);

	cout << "Found text string: "<< fline << endl;

	// gets text starting just after first delimiter, through but not including the second delimiter character.
	getline(inputFile, fline, delim2);

	stringstream ss(fline);
	string word;
	while(ss >> word) {
		targetWords.push_back(word);
	}
	inputFile.close();

	return targetWords;
}
/*
 * Code to extract an integer from the string using stringstream:
 *
 * Example: convertYearString("2020");
 * Here we declare a string object with value “2020” and an int object “year”.
 * Next, we use the stringstream class constructor to construct a stringstream
 * object from the string object. Then using the extraction operator (>>), the
 * value is extracted into year. From the above code, the value of year will
 * be 2020.
 */
int convertYearString(string s)
{
	int year;
	stringstream (s)>>year;
	return year;
}

int countWords(string str)
{
    // breaking input into word using string stream
    stringstream s(str); // Used for breaking words
    string word; // to store individual words

    printf("word count string '%s'\n", str.c_str());

    int count = 0;
    while (s >> word)
        count++;

    printf("count = %d\n", count);

    return count;
}


/*
 * Reading from file I/O or streams:
 * 1. Try to read data (>> or getline)
 * 2. Check if operation failed
 * 3. Only use the data if read succeeded
 *
 */
vector<int> readFileNumsToVector(string fname)
{
	vector<int> nums;
	ifstream ifile(fname);

    if(ifile.fail()) {
    	cout << "Unable to open file " << fname << endl;
    	return nums;
    }

	int x;
	// calling >> in an input stream returns a boolean true/false on operation success
    while(ifile >> x) {
    	nums.push_back(x);
    }
    ifile.close();
    return nums;
}

/*
 * How to read and parse CSV files
 * https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c
 */
vector<string> getNextLineAndSplitIntoTokens(string fname)
{
    vector<string> result;
    string line;

	ifstream ifile(fname);

    if(ifile.fail()) {
    	cout << "Unable to open file " << fname << endl;
    	return result;
    }

    istream& str = ifile;

    getline(str,line);

    cout << "getline: '" << line << "'" << endl;

    stringstream lineStream(line);
    string   cell;
    string	 word;
	stringstream ss(line);
	ss >> cell;

    while(getline(lineStream, cell, ','))
    {
    	//cout << "cell='" << cell << "'" << endl;
    	stringstream ss(cell);
    	ss >> word;
    	//cout << "word='" << word << "'" << endl;
        result.push_back(word);
    }

    // This checks for a trailing comma with no data after it.
    if (!lineStream && cell.empty())
    {
        // If there was a trailing comma then add an empty element.
        result.push_back("");
    }
    ifile.close();

    return result;
}

vector<string> getCSVdata(string fname)
{
    vector<string> result;
	ifstream  data(fname);

    if(data.fail()) {
    	cout << "Unable to open file " << fname << endl;
    	return result;
    }

	string line;
	while(getline(data,line))
	{
		stringstream  lineStream(line);
		string        cell;
		while(getline(lineStream,cell,','))
		{
	    	stringstream ss(cell);
	        string	 word;
	    	ss >> word;
			// load the vector
	        result.push_back(word);
		}
	}
	data.close();
    return result;
}

vector<string> getCSVstring(string str) {
	stringstream ss(str);
	vector<int> result;
	char ch;
	int elem;
	// format must be 'a,b,c,d...', with a leading integer
	// The '>>' operator applied to an input stream is known as the extraction operator:
	//   - Extracts and parses characters sequentially from the stream into rhs 8/16/32/64b type.
	//   - Returns basic_istream (*this)
	//   - The extracted value or sequence is not returned, but directly stored in the rhs argument.
	//   - Errors: eof=input sequence has not more chars available, failbit=no chars extracted,
	//     or not valid for rhs type, badbit=bad input stream
	if(ss.peek() == ',')
		ss >> ch;
	while(ss >> elem) {
	    result.push_back(elem);
	    ss >> ch;
	}
	return result;
}

template<class T>
void printVector(vector<T> const &vec) {
	cout << "Vector:" << endl;
	cout << "  [";
	for (T val: vec) {
		cout << val << "|";
	}
	cout << "]" << endl;
}

int main() {
	cout << "https://www.geeksforgeeks.org/stringstream-c-applications/" << endl;

    printf("Testing stl stringstream()\n");

	countWords("I'll have 2 number 9s");

	printf("Converting year string '2020' to int: year = %d\n", convertYearString("2020"));
	vector<string> dummy = extractWordsBetweenDelimiters("dummy.txt", '(', ')');

	vector<string> targetWords = extractWordsBetweenDelimiters("testFile1.txt", '(', ')');

	printf("Extracting Words Between Delimiters: \n");
	printVector(targetWords);

	printf("getNextLineAndSplitIntoTokens: \n");
	targetWords = getNextLineAndSplitIntoTokens("testFile2.txt");
	printVector(targetWords);

	printf("getCSVdata: \n");
	targetWords = getCSVdata("testFile2.txt");
	printVector(targetWords);

	return 0;
}
