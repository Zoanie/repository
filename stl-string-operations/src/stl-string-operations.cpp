//============================================================================
// Name        : stl-string-operations.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : http://anaturb.net/C/string_exapm.htm
//============================================================================


#include <bits/stdc++.h>
#include <boost/lexical_cast.hpp>
#include <string_view>

using namespace std;

template<class T>
void printVector(string name, vector<T> const &vec) {
	cout << name << ": " << endl;
	cout << "  [ ";
	for (T val: vec) {
		cout << val << " ";
	}
	cout << "]" << endl;
}

// https://www.techiedelight.com/iterate-over-characters-string-cpp/
void iterate_over_chars(const string &s)
{
	int slen = s.length();
	// traditional method
    for (auto i=0; i < slen; i++) {
        cout << s[i] << ' ';
    }

    // range based for loop
    for (char const &c: s) {
        std::cout << c << ' ';
    }

    // iterators
    for (auto it = s.cbegin() ; it != s.cend(); ++it) {
        std::cout << *it << ' ';
    }

    // for_each with lambda
    std::for_each(s.begin(), s.end(), [](const char &c){ cout << c << ' ';});

}

int string_constructors()
{
    char const *line = "short line for testing";

	cout << "String Constructors:" << endl;

    // with no arguments
    string s1;
    s1 = "Anatoliy";
    cout << "s1  is: " << s1 << endl;

    // copy constructor
    string s2 (s1);
    cout << "s2  is: " << s2 << endl;

    // one argument
    string s3 (line);
    cout << "s3  is: " << s3 << endl;

    // first argument C string
    // second number of characters
    string s4 (line,10);
    cout << "s4  is: " << s4 << endl;

    // 1 - C++ string
    // 2 - start position
    // 3 - number of characters
    string s5 (s3,6,4); // copy word 'line' from s3
    cout << "s5  is: " << s5 << endl;

    // 1 - number characters
    // 2 - character itself
    string s6 (15,'*');
    cout << "s6  is: " << s6 << endl;

    // 1 - start iterator
    // 2 - end iterator
    string s7 (s3.begin(),s3.end()-5);
    cout << "s7  is: " << s7 << endl;

    // you can instantiate string with assignment
    string s8 = "Anatoliy";
    cout << "s8  is: " << s8 << endl;
    cout << endl;

    return 0;
}

int getline_examples()
{
    string str;
	cout << "Getline Examples:" << endl;

    cout << "Enter string: ";
    getline (cin, str);
    cout << "Str is : " << str << endl;

    ifstream fin("testInputFile.txt");
    vector <string> v;

    cout << endl << "Read data from file" << endl;
    while ( ! fin.eof() )
    {
    	getline (fin, str);
    	v.push_back(str);
    }

    ostream_iterator<string> out_it(cout, "\n");
    copy (v.begin(),v.end(), out_it);
    cout << endl;

    ofstream fout;
    // Open a test file and truncate the data for new output data
	fout.open("testOutputFile.txt", ios::out | ios::trunc);
	if(fout.is_open()) {
	    ostream_iterator<string> fout_it(fout, "\n");
	    copy(begin(v), end(v), fout_it);
	    fout.close();
	}

	return 0;
}

int append_string()
{
    string str = "Nobody is perfect";
    string s   = ""; // empty string
    const char *ch   = "abcdef";

	cout << "String Append Examples:" << endl;

    // append string str at the end of s;
    // return s

	// s.append(string str, size_type pos, size_type n)
	//
    // appends at the end of s a copy of the n characters
    // in str, starting at position pos; if n is too
    // large, characters are copied only until the end
    // of str is reached;
    // returns s
    s.append(str,0,6);
    cout << "s is : " << s << endl;

    // appends copies of the characters in the range [inpIt1,
    // inpIt2] to s; returns s
    string::iterator inpIt1 = str.begin()+6;
                    //start from ' is'
    //string::iterator inpIt2 = str.end();

    s.append(inpIt1,str.end());
    cout << "s is : " << s << endl;

    // appends three !
    s.append(3,'!');
    cout << "s is : " << s << endl;

    // appends the first n characters in ch at the end
    // of s; returns s
    s.append(ch,3);
    cout << "s is : " << s << endl;

    // appends charArray at the end of s; returns s
    s.append(ch,3);
    cout << "s is : " << s << endl;

	return 0;
}

// https://leetcode.com/explore/interview/card/top-interview-questions-easy/127/strings/879/
void reverseString(vector<char>& s)
{
    // Many ways to reverse a string

    // The easy way:
    reverse(begin(s), end(s));
    return;

    // The hard way
    int len = s.size();
    if(len <= 1)
        return;
    char *front = &s[0];
    char *back = &s[len-1];
    char fbuf;
    char bbuf;
    do {
    	// using 2 temporary variables
        fbuf = *front;
        bbuf = *back;
        *back-- = fbuf;
        *front++ = bbuf;
        // using 1 temporary variable
#ifdef ONE_VAR
        char buf = *front;
        *front++ = *back;
        *back++ = buf;
#endif

    } while(front > back);
}

// https://leetcode.com/explore/interview/card/top-interview-questions-easy/127/strings/880/
int reverseInteger(int x)
{
	if(x == 0 || x >= INT_MAX || x <= INT_MIN) { return 0; }
	bool signbit = false;
	int result = 0;
	if (x < 0) {
		signbit = true;
		x *= (-1);
	}
	// remove trailing zeros
	while(x % 10 == 0) {
		x = x/10;
	}
	string s = to_string(x);
    reverse(begin(s), end(s));
    if(signbit) {
        s.insert(0, "-", 1);
    }
    // Two ways to convert a string to an integer: stoi() or stringstream.
    // Only stringstream however, survives converting a number greater than INT_MAX
    stringstream ss(s);
    ss >> result;
	if(result >= INT_MAX || result <= INT_MIN) { return 0; }
    return result;
}

//https://leetcode.com/explore/interview/card/top-interview-questions-easy/127/strings/881/
int firstUniqChar(string s)
{
	vector<int> alpha(26, -1);
	int idx=0;
	for(auto& c : s) {
		int aidx = c - 'a';
		if(alpha[aidx] == -2) {
			idx++;
			continue;
		}

		if(alpha[aidx] == -1) {
			alpha[aidx] = idx;
		}
		else {
			alpha[aidx] = -2;
		}
		idx++;
	}
	int first = INT_MAX;
	for(auto& elem : alpha) {
		if(elem >= 0 && elem < first) first = elem;
	}
	printVector("Alpha", alpha);
	return (first >= 0 && first != INT_MAX) ? first : (-1);
}

// https://leetcode.com/explore/interview/card/top-interview-questions-easy/127/strings/887/
int myAtoi(string s) {
	// Only the space character ' ' is considered a whitespace character
    // string whitespaces (" ");	// (" \t\f\v\n\r");
#ifndef USE_STRING_VIEW
    auto sstart = s.find_first_not_of(" ", 0);
    if(sstart == string::npos) {
    	return 0;
    }
    if(!isdigit(s[sstart])) return 0;
    auto ssend = s.find('.');
    if(ssend != string::npos) {
    	s.erase(ssend);
    }
    else {
    	ssend = s.find_first_not_of("+-0123456789", 0);
        if(ssend != string::npos) {
        	s.erase(ssend);
        }
    }

    int number;
#ifdef CPP_BOOST_LEXICAL_CAST_INCLUDED
    try {
    	number = boost::lexical_cast<int> (s.data() + sstart);
    }
    catch (const boost::bad_lexical_cast &) {
    	return -1;
    }
#else
    // Actually this is all that is needed!
    stringstream ss(s);
    ss >> number;
#endif
	if(number > INT_MAX) {
		return INT_MAX;
	}
	if(number < INT_MIN) {
		return INT_MIN;
	}
	return number;
#else
    /*
     * Using string_view...IS NOT READY FOR PRIME TIME as of 12/2020.
     * !!!
     * Only use std::string_view::data() if the std::string_view‘s view hasn’t been modified and
     * the string being viewed is null-terminated. Using std::string_view::data() of a non-null-terminated
     * string can cause undefined behavior.
     * https://www.learncpp.com/cpp-tutorial/6-6a-an-introduction-to-stdstring_view/
     */
	string_view sv(s);
    auto svstart = sv.find_first_not_of(" ", 0);
    if(svstart == string_view::npos) {
    	return 0;
    }
    auto svend = s.find('.');
    if(svend != string_view::npos) {
    	sv.remove_suffix(sv.size() - svend);
    	cout << "sv = " << sv << ", svend = " << svend << endl;
    }
    int number;
    try {
    	cout << "sv.data = " << sv.data() << ", svstart = " << svstart << endl;
    	// problem with sv.data here...
    	number = boost::lexical_cast<int> (sv.data() + svstart);
    }
    catch (const boost::bad_lexical_cast &) {
    	return -1;
    }
	return number;
#endif
}

// https://leetcode.com/explore/interview/card/top-interview-questions-easy/127/strings/885/
int strStr(string haystack, string needle)
{
    if(needle == "") {
        return 0;
    }
    auto idx = haystack.find(needle);
    if(idx == string::npos) {
        return (-1);
    }
    return idx;
}

// http://www.martinbroadhurst.com/how-to-trim-a-stdstring.html
std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    return ltrim(rtrim(str, chars), chars);
}

int main() {
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "cin reads " << n << endl;
    // Write Your Code Here
    string nums[11] = {"Invalid", "one", "two", "three", "four",
                       "five", "six", "seven", "eight", "nine",
                       "Greater than 9"};
    if(n < 0){
        n=0;
    }
    else if (n>9) {
        n=10;
    }
    cout << nums[n];

    return 0;
    int v_int=0;
    long v_long=0;
    char v_char=0;
    float v_float=0;
    double v_double=0;

    printf("Input: int long char float double: ");
    scanf("%d %ld %c %f %lf", &v_int, &v_long, &v_char, &v_float, &v_double);

    printf("%d\n", v_int);
    printf("%ld\n", v_long);
    printf("%c\n", v_char);
    printf("%.3f\n", v_float);
    printf("%.9lf\n", v_double);
    return 0;

	int iovar[3] = {0};
	int sum = 0;
	for(int i=0; i<3; i++) {
		cout << "Enter a value " << i+1 << ": ";
		cin >> iovar[i];
		sum += iovar[i];
	}
	cout << "Sum = " << sum << endl;
	return 0;

	string twelve_hour("07:05:45PM");
	cout << "12-hour format: " << twelve_hour << endl;
	int stdhour = stoi(twelve_hour);
	bool AM = toupper(twelve_hour[8]) == 'A';
	bool PM = !AM;
	int milhour = 0;
	if(stdhour == 12  && AM) {
		milhour = stdhour - 12;
	}
	else if (stdhour < 12 && PM){
		milhour = stdhour + 12;
	}
	else {
		milhour = stdhour;
	}
	string zero_pad = milhour < 10 ? "0" : "";
	string twenty_four_hour = zero_pad + to_string(milhour) + twelve_hour.substr(2, 6);

	cout << "military time: " << twenty_four_hour << endl;
	return 0;

    cout << "Maximum value for int:           " << numeric_limits<int>::max() << endl;	// 2147483647
    cout << "Minimum value for int:           " << numeric_limits<int>::min() << endl;	// -2147483648
    cout << "Maximum value for long int:      " << numeric_limits<long int>::max() << endl;
    int number = atoi("    21474836.48 and some letters");
	printf("atoi found number %d\n", number);

	number = myAtoi("    21474836.48 and some letters"); // 036854775807");
	printf("myAtoi found number %d\n", number);
	return 0;

	string s("leetcode");
	int result = firstUniqChar(s);

	cout << "Index of first non-repeating char in '" << s << "' = " << result << endl;
	return 0;

	//printf("revInteger(123) = %d\n", reverseInteger(123));
	//printf("revInteger(120) = %d\n", reverseInteger(120));
	//printf("revInteger(-123) = %d\n", reverseInteger(-123));
	//printf("revInteger(0) = %d\n", reverseInteger(0));
	//printf("revInteger(2147483647) = %d\n", reverseInteger(INT_MAX));
	//printf("revInteger(-2147483648) = %d\n", reverseInteger(INT_MIN));
	printf("revInteger(1534236469) = %d\n", reverseInteger(1534236469));


	return 0;

	cout << "http://anaturb.net/C/string_exapm.htm" << endl;
	string_constructors();

	getline_examples();
	append_string();
	return 0;
}
