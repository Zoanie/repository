//============================================================================
// Name        : hacker-rank-messages-order.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.hackerrank.com/challenges/messages-order/problem
//============================================================================

#include <bits/stdc++.h>

using namespace std;

template<class T>
void printMatrix(string name, vector<vector<T>> const &mat) {
    cout << "Matrix " << name << ":" << endl;
    cout << "[" << endl;
    for (vector<T> row: mat) {
        cout << "  [ ";
        for (T val: row) {
            cout << val << " ";
        }
        cout << "]" << endl;
    }
    cout << "]" << endl;
}

/*
 * Message Order
 * https://www.hackerrank.com/challenges/messages-order/problem
Your task is to implement classes Message and MessageFactory according to the below specification:
Class Message is required to store a text value of type std::string and provide a public getter
const string& get_text() which is expected to return this text value. Besides that, it should
implement the < operator that will be used in fix_order() method of the recipient to fix the
order of received messages. Feel free to implement any other methods and class/instance variables.
In particular, you can implement any additional constructors, but make sure that you provide an
empty constructor, i.e. the one without arguments.

Class MessageFactory is required to have an empty constructor, and implement a method Message
create_message(const string& text) that is expected to return a Message object storing the value
of text argument. Feel free to implement any other methods and class/instance variables of this
class.

The locked code template will act as follows. First, it creates objects message_factory and
recipient. These objects are of types MessageFactory and Recipient respectively. Then, it reads
messages from the standard input, and then it will use the provided Network class to simulate
sending the messages to the recipient. The Network class randomly shuffles the passes messages
and then it passes them to the recipient using recipient.receive(const Message&) method. After
all messages are delivered, the recipient uses its own method print_messages to print all the
received messages to the standard output, and just before doing that, it uses its own fix_order
method to fix the order of retrieved messages. For that purpose, it uses std::sort() algorithm
to sort the std::vector of received messages and this is the reason your Message class
implementation has to provide the < operator.

Input Format:
The input is read by the provided locked code template. It contains several lines of text
messages in the order that they will be sent over the network.

Constraints:
There will be at most  lines in the input.
Each line will contain at most  characters

Output Format:
The output should be produced by the provided locked code template and it is produced as
described in details in the statement. The expected order of printed messages is the same
as the one in the input.

 */

class Message {
public:
    static int MsgSeqNo;

    Message() { set_next_seqno(); }
    Message(const string& text_msg) {
        set_next_seqno();
        set_text(text_msg);
    }
    const string& get_text() {
        return text_message;
    }
    void set_text(const string& text_msg) {
        text_message = text_msg;
    }
    void set_next_seqno() { msg_seqno = ++MsgSeqNo; };
    const int get_msg_seqno() { return msg_seqno; };
    bool operator <(Message& msg) {
        if(msg_seqno < msg.get_msg_seqno()) {
            return true;
        }
        return false;
    };

private:
    string text_message;
    int msg_seqno;
};

int Message::MsgSeqNo = 0;

class MessageFactory {
public:
    MessageFactory() {}
    Message create_message(const string& text) {
        Message msg(text);
        return msg.get_text();
    }
};

class Recipient {
public:
    Recipient() {}
    void receive(const Message& msg) {
        messages_.push_back(msg);
    }
    void print_messages() {
        fix_order();
        for (auto& msg : messages_) {
            cout << msg.get_text() << endl;
        }
        messages_.clear();
    }
private:
    void fix_order() {
        sort(messages_.begin(), messages_.end());
    }
    vector<Message> messages_;
};

class Network {
public:
    static void send_messages(vector<Message> messages, Recipient& recipient) {
    // simulates the unpredictable network, where sent messages might arrive in unspecified order
        random_shuffle(messages.begin(), messages.end());
        for (auto msg : messages) {
            recipient.receive(msg);
        }
    }
};

/*
 * Overload Operators
 * https://www.hackerrank.com/challenges/overload-operators/problem
 *
You are given a class - Complex.

class Complex
{
public:
    int a,b;
};

Operators are overloaded by means of operator functions, which are regular functions with special names.
Their name begins with the operator keyword followed by the operator sign that is overloaded.
The syntax is:

type operator sign (parameters) { ... body ... }

You need to overload operators + and << for the Complex class.
The operator + should add complex numbers according to the rules of complex addition:

    (a+ib)+(c+id) = (a+c) + i(b+d)

Overload the stream insertion operator << to add "a + ib" to the stream:

    cout<<c<<endl;

The above statement should print "a + ib" followed by a newline where a=c.a and b=c.b.

Input Format:
The overloaded operator + should receive two complex numbers ( and ) as parameters.
It must return a single complex number.

The overloaded operator << should add "a + ib" to the stream where a is the real part
and b is the imaginary part of the complex number which is then passed as a parameter
to the overloaded operator.

Output Format:
As per the problem statement, for the output, print "a + ib" followed by a newline
where a=c.a and b=c.b.

Sample Input:
3+i4
5+i6

Sample Output:
8+i10

Explanation:
Given output after performing required operations (overloading + operator) is 8+i10.
 */
class Complex
{
public:
    int a;  // real
    int b;  // imaginary

    /*
     * Inside the object
    Complex operator+ (Complex const &complex_num) {
       Complex result = *this;
       result.a += complex_num.a;
       result.b += complex_num.b;
       return result;
    }
    */

    /*
    friend ostream& operator<<(ostream& os, Complex const &complex_num) {
        os << complex_num.a << "+i" << complex_num.b;
        return os;
    }
    */

};

// https://stackoverflow.com/questions/2425906/operator-overloading-outside-class
// Overload as a non-member uses pass by value (pbval) and pass by reference (pbref)
Complex operator+ (Complex pbval, Complex const& pbref) {
    pbval.a += pbref.a;
    pbval.b += pbref.b;
    return pbval;
}

ostream& operator<<(ostream& os, Complex const &complex_num) {
    os << complex_num.a << "+i" << complex_num.b;
    return os;
}

/*
 * Overloading Ostream Operator
 * https://www.hackerrank.com/challenges/overloading-ostream-operator/problem
 *
The task is to overload the << operator for Person class in such a way that for p
being an instance of class Person the result of:

std::cout << p << " " << <some_string_value> << std::endl;

produces the following output:

first_name=<first_name>,last_name=<last_name> <some_string_value>

Sample Input:
john doe registered

Sample Output:
first_name=john,last_name=doe registered
 */
class Person {
public:
    Person(const string& first_name, const string& last_name) : first_name_(first_name), last_name_(last_name) {}
    const string& get_first_name() const {
      return first_name_;
    }
    const string& get_last_name() const {
      return last_name_;
    }
    friend ostream& operator<<(ostream& os, const Person &p) {
        os << "first_name=" << p.get_first_name() << ",last_name=" << p.get_last_name();
        return os;
    }

private:
    string first_name_;
    string last_name_;
};

/*
 * Operator Overloading
 * https://www.hackerrank.com/challenges/operator-overloading/problem
 *
You are given a main() function which takes a set of inputs to create two matrices
and prints the result of their addition. You need to write the class Matrix which
has a member a of type vector<vector<int> >. You also need to write a member function
to overload the operator +. The function's job will be to add two objects of Matrix
type and return the resultant Matrix.

Input Format
First line will contain the number of test cases T. For each test case, there are three
lines of input. The first line of each test case will contain two integers N and M
which denote the number of the rows and columns respectively of the two matrices that
will follow on the next two lines. These next two lines will each contain N * M elements
describing the two matrices in row-wise format i.e. first M elements belong to the first
row,next M elements belong to the second row and so on.

Sample Input:
1           // 1 test
2 2         // N x M
2 2 2 2     // matrix1
1 2 3 4     // matrix2

Sample Output:
3 4
5 6

Explanation:
The sum of first matrix and the second matrix is the matrix given in the output.
 */
class Matrix {
public:
    vector<vector<int>> a;

    Matrix() {}

    // Source for C++ operator overloading guidelines:
    // http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html
    // Copy operator '='
    Matrix& operator=(const Matrix &rhs) {
        // We must prevent self-assignment
        if(this != &rhs) {
            // Deallocate, allocate new space and copy
            a = rhs.a;
        }
        return *this;
    }

    // Assignment operator '+='
    Matrix& operator+=(const Matrix &rhs) {
        *this = *this + rhs;
        return *this;
    }

    // Binary arithmetic operator '+'
    Matrix operator+ (const Matrix& rhs) {
        // Normally the dimensions need to be verified. Here we skip testing.
        Matrix result;
        result.a = rhs.a;  // 2d-vector copy
        //cout << "Vector a: \n" << *this << endl;
        int num_rows = a.size();
        int num_cols = a[0].size();
        for(int i=0; i<num_rows; i++) {
            for(int j=0; j<num_cols; j++) {
                //printf("res[%d][%d] = a[%d][%d] + b[%d][%d]", i, j, i, j, i, j);
                //printf(" = %d + %d\n", a[i][j], rhs.a[i][j]);
                result.a[i][j] = a[i][j] + rhs.a[i][j];
            }
        }
        return result;
    }

    friend ostream &operator<<(ostream &output, const Matrix& m) {
        for(size_t i = 0; i < m.a.size(); ++i) {
            for(size_t j = 0; j < m.a[0].size(); ++j)
            {
                output << m.a[i][j] << "  ";
                if(j == m.a[0].size() - 1)
                    output << endl;
            }
        }
        return output;
    }
};


int matrix_test() {
   int cases,k;
   cin >> cases;
   for(k=0;k<cases;k++) {
      Matrix x;
      Matrix y;
      Matrix result;
      int n,m,i,j;
      cin >> n >> m;
      for(i=0;i<n;i++) {
         vector<int> b;
         int num;
         for(j=0;j<m;j++) {
            cin >> num;
            b.push_back(num);
         }
         x.a.push_back(b);
      }
      for(i=0;i<n;i++) {
         vector<int> b;
         int num;
         for(j=0;j<m;j++) {
            cin >> num;
            b.push_back(num);
         }
         y.a.push_back(b);
      }

      printMatrix("X", x.a);
      printMatrix("Y", y.a);
      cout << "Result = Matrix X + Matrix Y =" << endl;
      result = x+y;
      for(i=0;i<n;i++) {
         for(j=0;j<m;j++) {
            cout << result.a[i][j] << " ";
         }
         cout << endl;
      }

      result = x;
      cout << "Result = Matrix X =" << endl;
      for(i=0;i<n;i++) {
         for(j=0;j<m;j++) {
            cout << result.a[i][j] << " ";
         }
         cout << endl;
      }

      result += x;
      cout << "Result += Matrix X =" << endl;
      for(i=0;i<n;i++) {
         for(j=0;j<m;j++) {
            cout << result.a[i][j] << " ";
         }
         cout << endl;
      }

   }
   return 0;
}
#define toStr(a) #a

int main() {

    matrix_test();
    return 0;
    Person p("Carlos", "Navarrette");

    cout << p << " " << "Ole!" << endl;
    return 0;
    cout << "https://www.hackerrank.com/challenges/messages-order/problem" << endl;
    //cout << toStr(Result =) << ' ' << "hello" << endl;

    return 0;
    MessageFactory message_factory;
    Recipient recipient;
    vector<Message> messages;
    string text;
    while (getline(cin, text)) {
        messages.push_back(message_factory.create_message(text));
        cout << "Created msg: " << messages.back().get_text() << endl;
    }
    Network::send_messages(messages, recipient);
    recipient.print_messages();
    return 0;
}
