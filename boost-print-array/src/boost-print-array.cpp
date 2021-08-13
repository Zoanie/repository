//============================================================================
// Name        : boost-print-array.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.boost.org/doc/libs/1_60_0/libs/multi_array/example/print_array.cpp
//============================================================================

#include "boost/multi_array.hpp"
#include <iostream>
#include <numeric>

using namespace std;


/*
 *
 * The index_bases member function returns a container with each dimension's index base.
 * The shape member function returns a container with each dimension's extent (size).
 * You can use both of these to determine the range of indices for each dimension:
 *
 * https://stackoverflow.com/questions/9179389/boostmulti-array-looping
 */
typedef boost::multi_array<double, 3> boost_3d_array_type;
typedef boost_3d_array_type::index index_3d_type;

void print3dArray(const boost_3d_array_type& a)
{
    // Query extents of each array dimension
    index_3d_type iMin = a.index_bases()[0];
    index_3d_type iMax = iMin + a.shape()[0] - 1;
    index_3d_type jMin = a.index_bases()[1];
    index_3d_type jMax = jMin + a.shape()[1] - 1;
    index_3d_type kMin = a.index_bases()[2];
    index_3d_type kMax = kMin + a.shape()[2] - 1;

    for (index_3d_type i=iMin; i<=iMax; ++i)
    {
        for (index_3d_type j=jMin; j<=jMax; ++j)
        {
            for (index_3d_type k=kMin; k<=kMax; ++k)
            {
                std::cout << a[i][j][k];
                if(k != jMax) cout << ", ";
            }
        }
    }
}

typedef boost::multi_array<double, 2> boost_2d_array_type;
typedef boost_2d_array_type::index index_2d_type;

void print2dArray(const boost_2d_array_type& a)
{
    // Query extents of each array dimension
    index_2d_type iMin = a.index_bases()[0];
    index_2d_type iMax = iMin + a.shape()[0] - 1;
    index_2d_type jMin = a.index_bases()[1];
    index_2d_type jMax = jMin + a.shape()[1] - 1;

    cout << "[";
    for (index_2d_type i=iMin; i<=iMax; ++i)
    {
        cout << "[";
        for (index_2d_type j=jMin; j<=jMax; ++j)
        {
        	cout << a[i][j];
            if(j != jMax) cout << ", ";
        }
        cout << "]";
    }
    cout << "]";
}

int main()
{
  typedef   boost::multi_array<double, 2> array_type;
  array_type A(boost::extents[4][6]);
  array_type::element* itr = A.data();

  for (int i = 0; i < 4 * 6; i++)
      *itr++ = i;

  print2dArray(A);

  return 0;
}

//  The output is:
// [[0,1,2],[3,4,5]]
