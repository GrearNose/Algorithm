#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size();
        int len2 = nums2.size();
        if ((len1 + len2) % 2 == 1)
            return findKth((len1+len2)/2+1, nums1, 0, nums2, 0);
        else
            return  (findKth((len1+len2)/2, nums1, 0, nums2, 0)
                   + findKth((len1+len2)/2 + 1, nums1, 0, nums2, 0)) / 2;
    }

    double findKth(int k, vector<int>&A, int offset1, vector<int>B, int offset2)
    {
        // cout << "K:" << k << " A:" << offset1 << " " << A.size() << " B:" << offset2 << " " << B.size() << endl;
        if (A.size()-offset1 > B.size()-offset2)
        {
            // cout << A.size()-offset1 << ", " <<  B.size()-offset2 << " Swap A and B" << endl;
            return findKth(k, B, offset2, A, offset1);
        }

        if (offset1 == A.size())
            return B[k-1];
        if (k == 1)
            return min(A[offset1], B[offset2]);

        int p1 = min(A.size()-offset1, k/2);
        int p2 = k - p1;

        if (A[offset1+p1-1] == B[offset2+p2-1])
            return A[offset1+p1-1];
        else if (A[offset1+p1-1] < B[offset2+p2-1]) // discard left part of A
            return findKth(k-p1, A, offset1+p1, B, offset2);
        else // discard left part of B
            return findKth(k-p2, A, offset1, B, offset2+p2);
    }
    int min(int a, int b){return a<b? a:b;}
};

int main(int argc, char const *argv[])
{
    Solution sln;
    vector<int> n1,n2;
    n1.push_back(1),n1.push_back(2),n1.push_back(3),n1.push_back(4);
    n2.push_back(5),n2.push_back(6),n2.push_back(7),n2.push_back(8);
    cout << sln.findMedianSortedArrays(n1,n2);
    return 0;
}