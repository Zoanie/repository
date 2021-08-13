//============================================================================
// Name        : boost-multi-array.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://sureshamrita.wordpress.com/2012/03/07/boost-multiarray-some-examples/
//============================================================================

#include <iostream>
// To disable range checking (for performance reasons in production releases),
// define the BOOST_DISABLE_ASSERTS preprocessor macro prior to including multi_array.hpp in your application.
#include <boost/multi_array.hpp>
#include <boost/array.hpp>
#include <boost/cstdlib.hpp>
#include <numeric>
/*
 * The Boost Multidimensional Array Library, https://www.boost.org/doc/libs/1_57_0/libs/multi_array/doc/user.html
 *
 * "Boost MultiArray is a more efficient and convenient way to express N-dimensional arrays than existing
 *  alternatives (especially the std::vector<std::vector<...>> formulation of N-dimensional arrays)."
 *
 * Notes:
 *   o A valid performance comparison with a native N X N array needs careful attention to compiler optimization.
 *     https://stackoverflow.com/questions/446866/boostmulti-array-performance-question.
 *
 */
using namespace std;

typedef boost::multi_array<double, 2> array_type;
typedef boost::multi_array_types::extent_range range;	// this one allows negative indexes!
typedef array_type::index index;


int main() {
    const int rows = 3;
    const int cols = 5;
    array_type A(boost::extents[rows][cols]);			// 3x5

    array_type::element* itr = A.data();
    for (int i = 0; i < rows * cols; i++)
        *itr++ = i;

    cout << "displaying matrix" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    cout << "row sum" << endl;
    for (int i = 0; i < rows; i++)
        cout << accumulate(A[i].begin(), A[i].end(), 0.0) << " ";
    cout << endl << endl;


    cout << "row sum - another method" << endl;
    typedef array_type::index_range range;
    for (int i = 0; i < rows; i++) {
        array_type::array_view<1>::type myview =
                A[boost::indices[i][range()]];
        cout << accumulate(myview.begin(), myview.end(), 0.0) << " ";
    }
    cout << endl << endl;

    cout << "col sum" << endl;
    for (int i = 0; i < cols; i++) {
        array_type::array_view<1>::type myview =
                A[boost::indices[range()][i]];
        cout << accumulate(myview.begin(), myview.end(), 0.0) << " ";
    }
    cout << endl << endl;

    cout << "displaying odd positioned  elements in a row" << endl;
    for (int i = 0; i < rows; i++) {
        array_type::array_view<1>::type myview =
                A[boost::indices[i][range(0,5,2)]];
        copy(myview.begin(),myview.end(),ostream_iterator<double>(cout," "));
        cout << endl;
    }
    cout << endl << endl;


    cout << "displaying even positioned  elements in a row" << endl;
    for (int i = 0; i < rows; i++) {
        array_type::array_view<1>::type myview =
                A[boost::indices[i][range(1,5,2)]];
        copy(myview.begin(),myview.end(),ostream_iterator<double>(cout," "));
        cout << endl;
    }
    cout << endl << endl;

    cout << "replacing even positioned  elements with -10 " << endl;
    for (int i = 0; i < rows; i++) {
        array_type::array_view<1>::type myview =
                A[boost::indices[i][range(1,5,2)]];
        fill(myview.begin(),myview.end(),-10);
    }
    cout << "displaying matrix" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
    cout << endl << endl;

    return 0;
}
