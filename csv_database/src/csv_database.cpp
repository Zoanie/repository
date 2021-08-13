//============================================================================
// Name        : csv_database.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.geeksforgeeks.org/csv-file-management-using-c/
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

/*
 * CSV file management using C++
 *
CSV is a simple file format used to store tabular data such as a spreadsheet or a database.
CSV stands for Comma Separated Values. The data fields in a CSV file are separated/delimited
by a comma (‘, ‘) and the individual rows are separated by a newline (‘\n’). CSV File
management in C++ is similar to text-type file management, except for a few modifications.

This article discusses about how to create, update and delete records in a CSV file:

Note: Here, a reportcard.csv file has been created to store the student’s roll number, name
and marks in math, physics, chemistry and biology.
*/
/*
 * Create a record:
 *
	The create operation is similar to creating a text file, i.e. input data from the user and
	write it to the csv file using the file pointer and appropriate delimiters(‘, ‘) between
	different columns and ‘\n’ after the end of each row.
 */
void create()
{
    // file pointer
    fstream fout;

    // opens an existing csv file or creates a new file.
    fout.open("reportcard.csv", ios::out | ios::app);

    cout << "Enter the details of 5 students:"
         << " roll name maths phy chem bio"
		 << endl;

    int i, roll, phy, chem, math, bio;
    string name;

    // Read the input
    for (i = 0; i < 5; i++) {

        cin >> roll
            >> name
            >> math
            >> phy
            >> chem
            >> bio;

        // Insert the data to file
        fout << roll << ", "
             << name << ", "
             << math << ", "
             << phy << ", "
             << chem << ", "
             << bio
             << "\n";
    }
}

/*
 * Read a record:
 *
In reading a CSV file, the following approach is implemented:-

	1. Using getline(), file pointer and ‘\n’ as the delimiter, read an entire row and
	   store it in a string variable.
	2. Using stringstream, separate the row into words.
	3. Now using getline(), the stringstream pointer and ‘, ‘ as the delimiter, read
	   every word in the row, store it in a string variable and push that variable
	   to a string vector.
	4. Retrieve a required column data through row[index]. Here, row[0] always stores
	   the roll number of a student, so compare row[0] with the roll number input by
	   the user, and if it matches, display the details of the student and break from
	   the loop.

	Note: Here, since whatever data reading from the file, is stored in string format,
	so always convert string to the required datatype before comparing or calculating, etc.
 */
void read_record()
{
	// File pointer
	fstream fin;

	// Open an existing file
	fin.open("reportcard.csv", ios::in);

	// Get the roll number
	// of which the data is required
	int rollnum, roll2, count = 0;
	cout << "Enter the roll number "
		<< "of the student to display details: ";
	cin >> rollnum;

	// Read the Data from the file
	// as String Vector
	vector<string> row;
	string line, word, temp;

	while (fin >> temp) {

		row.clear();

		// read an entire row and
		// store it in a string variable 'line'
		getline(fin, line);

		// used for breaking words
		stringstream s(line);

		// read every column data of a row and
		// store it in a string variable, 'word'
		while (getline(s, word, ',')) {

			// add all the column data
			// of a row to a vector
			row.push_back(word);
		}

		// convert string to integer for comparision
		roll2 = stoi(row[0]);

		// Compare the roll number
		if (roll2 == rollnum) {

			// Print the found data
			count = 1;
			cout << "Details of Roll " << row[0] << " : \n";
			cout << "Name: " << row[1] << "\n";
			cout << "Maths: " << row[2] << "\n";
			cout << "Physics: " << row[3] << "\n";
			cout << "Chemistry: " << row[4] << "\n";
			cout << "Biology: " << row[5] << "\n";
			break;
		}
	}
	if (count == 0)
		cout << "Record not found\n";
}

/*
 *
 * Update a record:
 *
The following approach is implemented while updating a record:-
	1. Read data from a file and compare it with the user input, as explained under
	   read operation.
	2. Ask the user to enter new values for the record to be updated.
	3. Update row[index] with the new data. Here, index refers to the required column
	   field that is to be updated.
	4. Write the updated record and all other records into a new file(‘reportcardnew.csv’).
	5. At the end of operation, remove the old file and rename the new file, with the old
	   file name, i.e. remove ‘reportcard.csv’ and rename ‘reportcardnew.csv’ with
	   ‘reportcard.csv’
 */
void update_record()
{
	// File pointer
	fstream fin, fout;

	// Open an existing record
	fin.open("reportcard.csv", ios::in);

	// Create a new file to store updated data
	fout.open("reportcardnew.csv", ios::out);

	int rollnum, roll1, count = 0, i;
	char sub;
	int index, new_marks;
	string line, word;
	vector<string> row;

	// Get the roll number from the user
	cout << "Enter the roll number "
		<< "of the record to be updated: ";
	cin >> rollnum;

	// Get the data to be updated
	cout << "Enter the subject "
		<< "to be updated(M/P/C/B): ";
	cin >> sub;

	// Determine the index of the subject
	// where Maths has index 2,
	// Physics has index 3, and so on
	if (sub == 'm' || sub == 'M')
		index = 2;
	else if (sub == 'p' || sub == 'P')
		index = 3;
	else if (sub == 'c' || sub == 'C')
		index = 4;
	else if (sub == 'b' || sub == 'B')
		index = 5;
	else {
		cout << "Wrong choice.Enter again\n";
		update_record();
	}

	// Get the new marks
	cout << "Enter new marks: ";
	cin >> new_marks;

	// Traverse the file
	while (!fin.eof()) {

		row.clear();

		getline(fin, line);
		stringstream s(line);

		while (getline(s, word, ',')) {
			row.push_back(word);
		}

		roll1 = stoi(row[0]);
		int row_size = row.size();

		if (roll1 == rollnum) {
			count = 1;
			stringstream convert;

			// sending a number as a stream into output string
			convert << new_marks;

			// the str() converts number into string
			row[index] = convert.str();

			if (!fin.eof()) {
				for (i = 0; i < row_size - 1; i++) {

					// write the updated data
					// into a new file 'reportcardnew.csv'
					// using fout
					fout << row[i] << ", ";
				}

				fout << row[row_size - 1] << "\n";
			}
		}
		else {
			if (!fin.eof()) {
				for (i = 0; i < row_size - 1; i++) {

					// writing other existing records
					// into the new file using fout.
					fout << row[i] << ", ";
				}

				// the last column data ends with a '\n'
				fout << row[row_size - 1] << "\n";
			}
		}
		if (fin.eof())
			break;
	}
	if (count == 0)
		cout << "Record not found\n";

	fin.close();
	fout.close();

	// removing the existing file
	remove("reportcard.csv");

	// renaming the updated file with the existing file name
	rename("reportcardnew.csv", "reportcard.csv");
}

/*
 * Delete a record:
 *
The following approach is implemented while deleting a record
	1. Read data from a file and compare it with the user input, as explained
	   under read and update operation.
	2. Write all the updated records, except the data to be deleted, onto a
	   new file(reportcardnew.csv).
	3. Remove the old file, and rename the new file, with the old file’s name.
 */
void delete_record()
{

	// Open FIle pointers
	fstream fin, fout;

	// Open the existing file
	fin.open("reportcard.csv", ios::in);

	// Create a new file to store the non-deleted data
	fout.open("reportcardnew.csv", ios::out);

	int rollnum, roll1, count = 0, i;
	string line, word;
	vector<string> row;

	// Get the roll number
	// to decide the data to be deleted
	cout << "Enter the roll number "
		<< "of the record to be deleted: ";
	cin >> rollnum;

	// Check if this record exists
	// If exists, leave it and
	// add all other data to the new file
	while (!fin.eof()) {

		row.clear();
		getline(fin, line);
		stringstream s(line);

		while (getline(s, word, ',')) {
			row.push_back(word);
		}

		int row_size = row.size();
		roll1 = stoi(row[0]);

		// writing all records,
		// except the record to be deleted,
		// into the new file 'reportcardnew.csv'
		// using fout pointer
		if (roll1 != rollnum) {
			if (!fin.eof()) {
				for (i = 0; i < row_size - 1; i++) {
					fout << row[i] << ", ";
				}
				fout << row[row_size - 1] << "\n";
			}
		}
		else {
			count = 1;
		}
		if (fin.eof())
			break;
	}
	if (count == 1)
		cout << "Record deleted\n";
	else
		cout << "Record not found\n";

	// Close the pointers
	fin.close();
	fout.close();

	// removing the existing file
	remove("reportcard.csv");

	// renaming the new file with the existing file name
	rename("reportcardnew.csv", "reportcard.csv");
}
int A, B, C, D, E, F, G, H, I, J;
int *arr3[10] = {&A, &B, &C, &D, &E, &F, &G, &H, &E, &J};

int main() {
	cout << "https://www.geeksforgeeks.org/csv-file-management-using-c/" << endl;

	int arr[] = {10, 20, 30, 40, 50, 60};
	int arr2[] = {11, 22, 33, 44, 55, 66};
	int *p= (int*)(&arr+1);		// !!! &arr+1 is address 1 integer beyond end of array !!!
	int *q= (int*)(&arr);
	int *r= (int*)(&arr[5]);
	printf("p=%d \n", *(p-1) );
	printf("q=%d \n", *(q+1));
	printf("r=%d \n", *r);
	printf("arr2[0]=%d\n", arr2[0]);

	printf("*(arr3+4) = 0x%X\n", *(arr3+4));
	printf("*(arr3+8) = 0x%X\n", *(arr3+8));

	if(*(arr3+4) == *(arr3+8))
	{
	printf("Pointer array is equal\n");
	}
	else
	{
	printf("Pointer array is Not Equal\n");
	}
	cout << flush;

	int b=5;
	b = printf("Quiz On");
	printf(" ");
	printf("%d", b);
	return 0;
}
