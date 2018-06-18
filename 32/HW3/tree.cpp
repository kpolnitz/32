//
//  tree.cpp
//  actualHW3
//
//  Created by Kaela Polnitz on 2/10/18.
//  Copyright © 2018 Kaela Polnitz. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <cassert>
using namespace std;


/*
    Replace the incorrect implementations of the countIncludes and the order functions below with correct ones that use recursion in a useful way. Except in the code for the split function that we give you below, your solution must not use the keywords while, for, or goto. You must not use global variables or variables declared with the keyword static, and you must not modify the function parameter lists. You must not use any references or pointers as parameters except for the parameters representing arrays and the parameters of the exchange function we provided. If any of the parameters n1, n2, or n is negative, act as if it were zero.
 */

// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//	10 50 40 20 50 40 30
// then for this value of a2     the function must return
//	10 20 40			1
//	10 40 30			2
//	20 10 40			0
//	50 40 30			3
int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
    if (n2 <= 0 && n1 <= 0)
        return 1;
    if (n2 > n1) //check this
        return 0;
    if (n2 <= 0)
        return 1;
    if (n1 <= 0)
        return 1; //DO SOMETHING
    if(a1[0] == a2[0])
    {
        return countIncludes(a1+1, n1-1, a2+1, n2-1) + countIncludes(a1+1, n1-1, a2, n2);
        //account for moving on the next in n2, OR checking for that element again
    }
        //keep looking through a1 for something
    
    return countIncludes(a1+1, n1-1, a2, n2);
        
        
    
     // This is incorrect.
}

// Exchange two doubles
//WE WILL NOT EDIT THIS
void exchange(double& x, double& y)
{
    double t = x;
    x = y;
    y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is > splitter come before all the other elements,
// and all the elements whose value is < splitter come after all
// the other elements.  Upon return, firstNotGreater is set to the
// index of the first element in the rearranged array that is
// <= splitter, or n if there is no such element, and firstLess is
// set to the index of the first element that is < splitter, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotGreater, a[i] > splitter
//   * for firstNotGreater <= i < firstLess, a[i] == splitter
//   * for firstLess <= i < n, a[i] < splitter
// All the elements > splitter end up in no particular order.
// All the elements < splitter end up in no particular order.




//WE WILL NOT EDIT THIS
//greater to smaller
void split(double a[], int n, double splitter,
           int& firstNotGreater, int& firstLess)
{
    //NO PARTICULAR ORDER
    //firstNotGreater, firstLess are going to be changed, pointless as passed in
    if (n < 0)
        n = 0;
    
    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
    //  Every element earlier than position firstNotGreater is > splitter
    //  Every element from position firstNotGreater to firstUnknown-1 is
    //    == splitter
    //  Every element from firstUnknown to firstLess-1 is not known yet
    //  Every element at position firstLess or later is < splitter
    
    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess)
    {
        if (a[firstUnknown] < splitter)
        {
            firstLess--;
            exchange(a[firstUnknown], a[firstLess]);
        }
        else
        {
            if (a[firstUnknown] > splitter)
            {
                exchange(a[firstNotGreater], a[firstUnknown]);
                firstNotGreater++;
            }
            firstUnknown++;
        }
    }
}

// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.
void order(double a[], int n)
{
    int firstNotGreat;
    int firLess;
    if (n <= 1) //already organized if there is only one item
        return;
    int midpoint = n/2;
    split(a, n, a[midpoint], firstNotGreat, firLess);
    order(a, firstNotGreat); //sort the first part
    order(a+firstNotGreat, n-firLess); //sort the remainder
   
    //go through and organize before the first blip, and afterwards
    //divide and conquer
  
    return;  // This is not always correct.
}

/*
int main()
{
    double nums[7] = {10, 50, 40, 20, 50, 40, 30};
    double nums2[3] = {10, 20, 40};
    double nums3[3] = {10, 40, 30};
    double nums4[4] = {20, 10, 40};
    double nums5[5] = {50, 40, 30};
    
    
    cout << countIncludes(nums, 7, nums2, 3) << endl;
    cout << countIncludes(nums, 7, nums3, 3) << endl;
    cout << countIncludes(nums, 7, nums4, 3) << endl;
    cout << countIncludes(nums, 7, nums5, 3) << endl;
    order(nums, 7);
    for (int i = 0; i < 7; i++)
        cout << nums[i] << " ";
    
    
    
}
 */
