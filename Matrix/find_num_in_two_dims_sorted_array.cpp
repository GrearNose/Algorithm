#include <vector>
#include <ctime>
#include <iostream>
using namespace std;

class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        int n,m;
        n = array.size();
        m = array[0].size();
        // assume n > m, then do bisearch within each col.
        int times = m, upper = n;
        bool withinRow = false;
        // when n < m, do bisearch within each row.
        if (n < m)
        {
            upper = m;
            times = n;
            withinRow = true;
        }
        for(int k =0; k < times; ++ k)
        {
            int i, j;
            int l = 0, h = upper;
            while(l <= h)
            {
                int mid = (l+h) >> 1;
                if(withinRow)
                {
                    i = k;
                    j = mid;
                }
                else
                {
                    i = mid;
                    j = k;
                }
                if (target == array[i][j])
                    return true;
                else if(target > array[i][j])
                    l = j + 1;
                else
                    h = j - 1;
            }
        }
        return false;
    }

};


int main(int argc, char const *argv[])
{
    int row = 3, col = 9;
    vector<vector<int>> arr;
    int mx = row * col ;
    srand(time(NULL));
    cout << "the array: " << endl;
    for (int i = 0; i < row; ++i)
    {
        int num = rand()%mx;
        vector<int> *r = new vector<int>(col);
        for (int j = 0; j < col; ++j)
        {
            num += rand()%mx;
            (*r).push_back(num);
            cout << num << " ";
        }
        cout << endl;
        arr.push_back(*r);
    }
    int target = mx + rand() % mx;
    Solution solu;
    cout << "finding " << target << ":" << solu.Find(target, arr) << endl;
    return 0;
}