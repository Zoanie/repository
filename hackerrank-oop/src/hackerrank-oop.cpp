//============================================================================
// Name        : hackerrank-oop.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.hackerrank.com/challenges/
//============================================================================
#include <bits/stdc++.h>

using namespace std;


/*
 * Class Student
 * https://www.hackerrank.com/challenges/classes-objects/problem
 * 
You have to create a class, named Student, representing the student's details, as mentioned above, 
and store the data of a student. Create setter and getter functions for each element; that is, the 
class should at least have following functions:

get_age, set_age
get_first_name, set_first_name
get_last_name, set_last_name
get_standard, set_standard
Also, you have to create another method to_string() which returns the string consisting of the 
above elements, separated by a comma(,). You can refer to stringstream for this.

Input Format

Input will consist of four lines.
The first line will contain an integer, representing the age. The second line will contain a string, 
consisting of lower-case Latin characters ('a'-'z'), representing the first_name of a student.
The third line will contain another string, consisting of lower-case Latin characters ('a'-'z'), 
representing the last_name of a student.
The fourth line will contain an integer, representing the standard of student.

Note: The number of characters in first_name and last_name will not exceed 50.

Output Format
The code provided by HackerRank will use your class members to set and then get the elements of the Student class.

Sample Input
15
john
carmack
10

Sample Output
15
carmack, john
10

15,john,carmack,10
 */


// https://www.hackerrank.com/challenges/classes-objects/problem
class StudentVitale {
private:
    int age;
    int standard;
    string first_name;
    string last_name;
    vector<int> scores;

public:
    StudentVitale() {
        scores.assign(5,0);
        age = 0;
        standard = 0;
        first_name.assign("not assigned");
        last_name = "not assigned";
    }
    int get_age() const {
        return age;
    }

    void set_age(int age) {
        this->age = age;
    }

    const string& get_first_name() const {
        return first_name;
    }

    void set_first_name(const string &firstName) {
        first_name = firstName;
    }

    const string& get_last_name() const {
        return last_name;
    }

    void set_last_name(const string &lastName) {
        last_name = lastName;
    }

    int get_standard() const {
        return standard;
    }

    void set_standard(int standard) {
        this->standard = standard;
    }

    void input() {
        for(auto& score : scores) {
            cin >> score;
        }
    }

    int calculateTotalScore() {
        //return accumulate(begin(scores), end(scores), 0);
        int total_score = 0;
        for(auto& sum : scores) {
            total_score += sum;
        }
        return total_score;
    }

    string to_string() {
        stringstream ss;
        ss << age << "," << first_name << "," << last_name << "," <<  standard << endl;
        return ss.str();
    }
};

// Custom exception
class BadLengthException : public exception {
public:
    int N;
    BadLengthException(int N) {
        this->N=N;
    };
    int what() {
        return this->N;
    }
};


bool checkUsername(string username) {
    bool isValid = true;
    int n = username.length();
    // "throw by value, catch by reference
    if(n < 5) {
        throw BadLengthException(n);
    }
    for(int i = 0; i < n-1; i++) {
        if(username[i] == 'w' && username[i+1] == 'w') {
            isValid = false;
        }
    }
    return isValid;
}

// https://medium.com/@thege3e/c-user-defined-exceptions-b06aef48427f
int testUserDefinedException() {
    int T; cin >> T;
    while(T--) {
        string username;
        cin >> username;
        try {
            bool isValid = checkUsername(username);
            if(isValid) {
                cout << "Valid" << '\n';
            } else {
                cout << "Invalid" << '\n';
            }
            // "throw by value, catch by reference
        } catch (BadLengthException& e) {
            cout << "Too short: " << e.what() << '\n';
            throw;	// When re-throwing an exception e, prefer just throw
        }
    }
    return 0;
}

/*
 * Box It!
 * https://www.hackerrank.com/challenges/box-it/problem
 *
Design a class named Box whose dimensions are integers and private to the class.
The dimensions are labeled: length l, breadth b, and height h.

The default constructor of the class should initialize l, b, and h to 0.

The parameterized constructor Box(int length, int breadth, int height) should
initialize Box's l,b and h to length, breadth and height.

The copy constructor BoxB(Box B) should set l,b and h to B's l,b and h, respectively.

Apart from the above, the class should have  functions:
    int getLength() - Return box's length
    int getBreadth() - Return box's breadth
    int getHeight() - Return box's height
    long long CalculateVolume() - Return the volume of the box

Overload the operator < for the class Box. Box A < Box B if:
    1. A.l < B.l
    2. A.b < B.b and A.l == B.l
    3. A.h < B.h and A.b == B.b and A.l == B.l

Overload operator << for the class Box(). if:
    B is and object of class Box:    cout << B should print B.l, B.b and B.h
    on a single line separated by spaces.

For Example:
Box b1; // Should set b1.l = b1.b = b1.h = 0;
Box b2(2, 3, 4); // Should set b1.l = 2, b1.b = 3, b1.h = 4;
b2.getLength(); // Should return 2
b2.getBreadth(); // Should return 3
b2.getheight(); // Should return 4
b2.CalculateVolume(); // Should return 24
bool x = (b1 < b2); // Should return true based on the conditions given
cout<<b2; // Should print 2 3 4 in order.

Constraints:
    0 <= l,h,h <= 10**5
    Two boxes being compared using the < operator will not have all three dimensions equal.
 */
class Box {
private:
    int l; int b; int h;
public:
    Box() {
        l = 0; b = 0; h = 0;
    }

    Box(int length, int breadth, int height): l(length), b(breadth), h(height)
    {
    }

    int getBreadth() const {
        return b;
    }

    int getHeight() const {
        return h;
    }

    int getLength() const {
        return l;
    }

    long long CalculateVolume() {
        long long result = b;
        result *= h;
        result *= l;
        return result;
    }

    // copy constructor
    Box(const Box &B) {
        b = B.b; h = B.h; l = B.l;
    }

    // operator '<' overload
    // https://www.tutorialspoint.com/cplusplus/relational_operators_overloading.htm
    bool operator<(const Box& B) {
        if(l < B.l) return true;
        else if((b < B.b) && (l == B.l)) return true;
        else if((h < B.h) && (b == B.b) && (l == B.l)) return true;
        else return false;
    }

    // operator '<<' overload
    // https://www.tutorialspoint.com/cplusplus/input_output_operators_overloading.htm
    friend ostream &operator<<(ostream &output, const Box& B) {
        output << B.l << " " << B.b << " " << B.h;
        return output;
    }
};

void check2()
{
    int n;
    cout << "Enter number of tests: " << flush;
    cin>>n;
    Box temp;
    for(int i=0;i<n;i++)
    {

        int type;
        cin>>type;
        if(type ==1)
        {

            cout << "Test " << i+1 << " Creating default Box: " << endl;
            cout<<temp<<endl;
        }
        if(type == 2)
        {
            cout << "Test " << i+1 << " Creating Box type 2: " << endl;
            int l,b,h;
            cout << "Enter box 'length breadth height': " << flush;
            cin>>l>>b>>h;
            Box NewBox(l,b,h);
            temp=NewBox;
            cout << "Box type 2: ";
            cout<<temp<<endl;
        }
        if(type==3)
        {
            cout << "Test " << i+1 << " Creating Box type 3: " << endl;
            cout << "Enter box 'length breadth height': " << flush;
            int l,b,h;
            cin>>l>>b>>h;
            Box NewBox(l,b,h);
            if(NewBox<temp)
            {
                cout<<"Smaller than box" << endl;
            }
            else
            {
                cout<<"Greater than box" << endl;
            }
        }
        if(type==4)
        {
            cout << "Test " << i+1 << " Calculating Box volume: " << endl;
            cout << "Box volume: " << flush;
            cout<<temp.CalculateVolume()<<endl;
        }
        if(type==5)
        {
            cout << "Test " << i+1 << " Creating copy of box: " << endl;
            Box NewBox(temp);
            cout<<NewBox<<endl;
        }

    }
    cout << "Tests complete" << endl;
}

int box_it_main() {

    Box b1; // Should set b1.l = b1.b = b1.h = 0;
    Box b2(2, 3, 4); // Should set b1.l = 2, b1.b = 3, b1.h = 4;
    b2.getLength();	// Should return 2
    b2.getBreadth(); // Should return 3
    b2.getHeight();	// Should return 4
    b2.CalculateVolume(); // Should return 24
    bool x = (b1 < b2);	// Should return true based on the conditions given
    if(x) cout << "Correct: Box b2 is greater than b1" << endl;
    else cout << "Incorrect: Box b2 is not greater than b1" << endl;
    cout << b2 << endl; // Should print 2 3 4 in order.

    check2();

    return 0;

    int age, standard;
    string first_name, last_name;
    cout << "https://www.hackerrank.com/challenges/" << endl;

    cin >> age >> first_name >> last_name >> standard;

    StudentVitale st;
    st.set_age(age);
    st.set_standard(standard);
    st.set_first_name(first_name);
    st.set_last_name(last_name);


    cout << st.get_age() << "\n";
    cout << st.get_last_name() << ", " << st.get_first_name() << "\n";
    cout << st.get_standard() << "\n";
    st.input();
    cout << st.to_string();
    cout << "Total Score: " << st.calculateTotalScore() << endl;

    return 0;
}

/*
 * Exceptional Server
 * https://www.hackerrank.com/challenges/exceptional-server/problem
 *
In this challenge, you are required to handle error messages while working with small
computational server that performs complex calculations.  It has a function that takes
large numbers as its input and returns a numeric result. Unfortunately, there are
various exceptions that may occur during execution.

Complete the code in your editor so that it prints appropriate error messages, should
anything go wrong. The expected behavior is defined as follows:
	o If the compute function runs fine with the given arguments, then print the
	  result of the function call.
	o If it fails to allocate the memory that it needs, print "Not enough memory".
	o If any other standard C++ exception occurs, print Exception: S where S is the
	  exception's error message.
	o If any non-standard exception occurs, print "Other Exception".

Input Format
The first line contains an integer, T, the number of test cases.
Each of the  subsequent lines describes a test case as  space-separated integers,
A and B, respectively.

Constraints
1 <= T <= 1000
0 <= A, B <= 2**60
 */
class Server {
private:
    static int load;
public:
    static int compute(long long A, long long B) {
        load += 1;
        if(A < 0) {
            throw std::invalid_argument("A is negative");
        }
        vector<int> v(A, 0);
        int real = -1, cmplx = sqrt(-1);
        if(B == 0) throw 0;
        real = (A/B)*real;
        int ans = v.at(B);
        return real + A - B*ans;
    }
    static int getLoad() {
        return load;
    }
};
int Server::load = 0;

// https://www.hackerrank.com/challenges/exceptional-server/problem
int exceptional_server() {
    int T; cin >> T;
    while(T--) {
        long long A, B;
        cin >> A >> B;
        Server MyServer;
        int result = 0;
        try {
            result = MyServer.compute(A, B);
            cout << result << endl;
        } catch (const std::bad_alloc& e) {
            cout << "Not enough memory" << endl;
        } catch (const std::exception& e) {
            cout << "Exception: " << e.what() << endl;
        } catch (...) {
            cout << "Other Exception" << endl;
        }
    }
    cout << Server::getLoad() << endl;
    return 0;
}

/*
 * Virtual Functions
 *
This problem is to get you familiar with virtual functions. Create three classes Person, Professor and Student.
The class Person should have data members name and age. The classes Professor and Student should inherit from
the class Person. The class Professor should have two integer members: publications and cur_id. There will be
two member functions: getdata and putdata. The function getdata should get the input from the user: the name,
age and publications of the professor. The function putdata should print the name, age, publications and the
ur_id of the professor. The class Student should have two data members: marks, which is an array of size 6 and
cur_id. It has two member functions: getdata and putdata. The function getdata should get the input from the
user: the name, age, and the marks of the student in 6 subjects. The function putdata should print the name, age,
sum of the marks and the cur_id of the student. For each object being created of the Professor or the Student
class, sequential id's should be assigned to them starting from 1. Solve this problem using virtual functions,
constructors and static variables. You can create more data members if you want.

Input Format:
The first line of input contains the number of objects that are being created. If the first line of input for
each object is 1, it means that the object being created is of the Professor class, you will have to input the
name, age and publications of the professor. If the first line of input for each object is 2, it means that the
object is of the Student class, you will have to input the name, age and the marks of the student in 6 subjects.

Constraints
1 <= len <= 100, where len is the lenght of the name
1<= age <= 80
1<= publications <= 1000
0<= marks <= 100, where are the marks of the student in each subject

Output Format:
If the object is of type Professor, print the space separated name, age, publications and id on a new line.
If the object is of the Student class, print the space separated name, age, the sum of the marks in 6 subjects
and id on a new line.

Sample Input:
4
1
Walter 56 99
2
Jesse 18 50 48 97 76 34 98
2
Pinkman 22 10 12 0 18 45 50
1
White 58 87

Sample Output:
Walter 56 99 1
Jesse 18 403 1
Pinkman 22 135 2
White 58 87 2

 */

// The class Person should have data members name and age
class Person {
public:

    Person() {
        age = 0;
    }
    virtual ~Person() {}

    virtual void getdata() {
        cin >> name >> age;
    }
    virtual void putdata() {
        cout << name << " " << age << endl;
    }

protected:
    string name;
    int age;
};

/*
The class Professor should have two integer members: publications and cur_id.
There will be two member functions: getdata and putdata. The function getdata
should get the input from the user: the name, age and publications of the professor.
The function putdata should print the name, age, publications and the cur_id of
the professor.
 */
class Professor: public Person {
private:
    int publications;
    int cur_id;

public:
    static int cur_professors_id;
    Professor() {
        publications = 0;
        cur_id = ++cur_professors_id;
    }
    virtual ~Professor(){}

    virtual void getdata() {
        cin >> name >> age >> publications;
    }
    virtual void putdata() {
        cout << name << " " << age << " " << publications << " " << cur_id << endl;
    }
};
int Professor::cur_professors_id = 0;

/*
The class Student should have two data members: marks, which is an array of size 6
and cur_id. It has two member functions: getdata and putdata. The function getdata
should get the input from the user: the name, age, and the marks of the student in
subjects. The function putdata should print the name, age, sum of the marks and
the cur_id of the student.
 */
class Student: public Person {
private:
    vector<int> marks;
    int cur_id;

public:
    static int cur_students_id;
    Student() {
        marks.assign(6,0);
        cur_id = ++cur_students_id;
    }
    virtual ~Student(){}

    // The function getdata should get the input from the user: the name, age,
    // and the marks of the student in subjects.
    virtual void getdata() {
        cin >> name >> age;
        for(auto& mark : marks) {
            cin >> mark;
        }
    }
    // The function putdata should print the name, age, sum of the marks and
    // the cur_id of the student.
    virtual void putdata() {
        cout << name << " " << age << " ";
        int sum = 0;
        for(auto& mark : marks) {
            sum += mark;
        }
        cout << sum << " " << cur_id << endl;
    }

};
int Student::cur_students_id = 0;

/*
 * Accessing Inherited Functions
 *
You are given three classes A, B and C. All three classes implement their own version of func.

In class A, func multiplies the value passed as a parameter by 2.
In class B, func multiplies the value passed as a parameter by 3.
In class C, func multiplies the value passed as a parameter by 5.

You are given a class D.  You need to modify the class D and implement the function update_val
which sets D's val to new_val by manipulating the value by only calling the func defined in
classes A, B and C.

It is guaranteed that new_val has only 2,3 and 5 as its prime factors.

Input Format:
Implement class D's function update_val. This function should update D's val only by calling
A, B and C's func.

Constraints
1<= new_val <= 10000
Note: The new_val only has 2,3 and 5 as its prime factors.

Sample Input
new_val = 30

Sample Output
A's func will be called once.
B's func will be called once.
C's func will be called once.

Explanation:
Initially, val=1.
A's func is called once:
    val = val*2
    val = 2

B's func is called once:
    val = val*3
    val = 6

C's func is called once:
    val = val*5
    val = 30

Example 2:
Input:
3600

Output:
Value = 3600
A's func called 4 times
B's func called 2 times
C's func called 2 times
 */
class A {
public:
    A(){
        callA = 0;
    }
private:
    int callA;
    void inc(){
        callA++;
    }

protected:
    void func(int & a){
        a = a * 2;
        inc();
    }
public:
    int getA(){
        return callA;
    }
};

class B {
public:
    B(){
        callB = 0;
    }
private:
    int callB;
    void inc(){
        callB++;
    }
protected:
    void func(int & a){
        a = a * 3;
        inc();
    }
public:
    int getB(){
        return callB;
    }
};

class C {
public:
    C(){
        callC = 0;
    }
private:
    int callC;
    void inc(){
        callC++;
    }
protected:
    void func(int & a){
        a = a * 5;
        inc();
    }
public:
    int getC(){
        return callC;
    }
};

class D: public A, public B, public C {
    int val;
public:
    //Initially val is 1
    D(){
        val = 1;
    }

    //Implement this function
    void update_val(int new_val) {

        while (new_val %2 == 0){
            A::func(val);
            new_val = new_val/2;
        }
        for (int i = 3; i <= sqrt(new_val); i = i+2){
            while (new_val %i == 0){
                if(i==3)
                    B::func(val);
                else
                    C::func(val);
                new_val = new_val/i;
            }
        }
        if (new_val > 2) {
            C::func(val);
        }
    }
    //For Checking Purpose
    void check(int new_val); //Do not delete this line.
};

void D::check(int new_val)
{
    update_val(new_val);
    cout << "Value = " << val << endl << "A's func called " << getA() << " times " << endl << "B's func called " << getB() << " times" << endl << "C's func called " << getC() << " times" << endl;
}

void printPrimeFactors(int n) {
    while (n%2 == 0){
        cout<<"2, ";
        n = n/2;
    }
    for (int i = 3; i <= sqrt(n); i = i+2){
        while (n%i == 0){
            cout<<i<<", ";
            n = n/i;
        }
    }
    if (n > 2)
        cout<<"[" << n<<"]";
    cout << endl;
}

// https://www.hackerrank.com/challenges/accessing-inherited-functions/problem
int main()
{
    D d;
    //int new_val;
    //cin >> new_val;
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    printPrimeFactors(3600);
    d.check(3600);

}
