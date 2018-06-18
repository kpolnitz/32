//
//  linear.cpp
//  actualHW3
//
//  Created by Kaela Polnitz on 2/10/18.
//  Copyright © 2018 Kaela Polnitz. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;
// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
/*
bool somePredicate(double x)
{
    return x == 2.3;
}
 */

bool allTrue(const double a[], int n)
{
    //ALMOST CORRECT
    if (n<=0)
        return false;
    if(n==1)                    //if the only element, just check if the 0th element is true or false
    {
       if (!somePredicate(a[n-1]))
           return false;
        return true;
    }
    if(!somePredicate(a[n-1]))
        return false;

    return allTrue(a,n-1);
    
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const double a[], int n)
{
    //int count = 0;
    if (n <= 0)
        return 0;
    if (!somePredicate(a[n-1]))
    {
        return countFalse(a, n-1) + 1;
        //count++;
    }
    
    return countFalse(a, n-1); //it's true, don't add to count
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const double a[], int n)
{
    if (n <= 0) //if it is input, or you iterate all the way down and you get nothing
        return -1;
    int first = firstFalse(a+1, n-1)+1;
    if(!somePredicate(a[0]))
            return 0;
    else
    {
    //iterate through
    if (first - 1 == -1)
        return -1;
    }
    return first;
}

// Return the subscript of the smallest double in the array (i.e.,
// the one whose value is <= the value of all elements).  If more
// than one element has the same smallest value, return the smallest
// subscript of such an element.  If the array has no elements to
// examine, return -1.
int indexOfMin(const double a[], int n)
{
    //search from the beginning
    if (n<=0)
        return -1;
    int index=indexOfMin(a+1,n-1) + 1; //index through
    if (n==1)
        return 0;
    
    if(a[0] <= a[index])
        return 0; //will add 0 + number of recursions through!
        
    
    return index;  // This is incorrect.
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{
    //cover both 0, one is zero the other is not,etc.
    if(n2 > n1)
        return false;
    
    if (n1 == 0 && n2 == 0)
        return true;
      
    
    //front to back
    //doesn't have to be consecutive
    if (n1 <= 0)
        return false;
    if (n2 <= 0)
        return true;
    if(a1[0] != a2[0])
        return includes(a1+1,n1-1,a2,n2);

    return includes(a1+1, n1-1, a2+1, n2-1);
   
    // This is not always correct.
}


/*

int main()
{
    double nums1[10] = {2.4, 3.0, 34.0, 6.7, 8.9, 3.5, 7.3, 9.2, 1.4, 5.4};
    double nums2[10] = {2.4, 3.0, 34.0, 6.7, 8.9, 3.5, 7.3, 9.2, 1.4, 5.3};
    double nums3[5] = {10, 20, 20};
    
    double nums4[7] = {10, 50, 40, 20, 50, 40, 30};
    double nums5[3] = {50, 30, 20};
    double nums6[6] = {2, 2, 3.4, 2.9, 1.3, 2};
    double nums8[7] = {1, 2.4, 2.4, 1.9, 2.9, 2.73, 2.0};

    assert(includes(nums1, 0, nums2, 1) == false); //works
    assert(includes(nums4, 7, nums5, 3) == false); //works
    assert(countFalse(nums6, 6)==6); //works
    assert(indexOfMin(nums1, 10)==8); //works
    cout << indexOfMin(nums8, 7) << endl; //works
    
    //assert(allTrue(nums8, 7) == false); //works
    
    
    
}
 */
