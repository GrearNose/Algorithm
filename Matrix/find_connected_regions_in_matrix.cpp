#include <algorithm>
#include <ctime>
#include <queue>
#include <map>
#include <iostream>
using namespace std;

/*
Find the all connected regions in the matrix. A connected region is a set of
nodes(elements) in the matrix directly or indirectly adajecent in eight
directions (transitive). The func find out all these regions by BFS traversing.
Args
matrix: an 2d array representing the matrix, with non-zero elements
        indicating connectiviy.
N: number of rows of the matrix;
M: number of collumns of the matrix;
four_directions: a flag to indicate if true that nodes can only be connected
        in four direction, i.e., up, down, left, right, otherwise, eight
        directions are considered.
return: a vector of connected regions, each connected region is
        a vector of index pairs.
*/
template <typename T>
vector<vector<pair<int,int>>*>* connected_regions_in_matrix(T *matrix[],
    int N, int M, bool four_directions = false)
{
    vector<vector<pair<int,int>>*> *regions = new vector<vector<pair<int,int>>*>();
    queue<pair<int,int>> total; // all nodes forming the connected regions.
    queue<pair<int,int>> cur;   // current connected region.
    map<pair<int,int>,bool>visited; // bitmap to record the visiting.

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
             // use non-zero to indicate connectivity.
            if (matrix[i][j])
            {
                pair<int,int> p(i,j);
                total.push(p);
                visited[p] = false;
            }
        }
    }

    while(!total.empty())
    {
        vector<pair<int,int>> *cur_region = new vector<pair<int,int>>();
        while(cur.empty() && !total.empty())
        {
            pair<int,int> p = total.front();
            total.pop();
            if (!visited[p])
                cur.push(p);
        }
        // use BFS to gather all connected nodes in curent region.
        while(!cur.empty()) 
        {
            pair<int,int> p0 = cur.front();
            cur.pop();
            visited[p0] = true;
            cur_region->push_back(p0);
            int r = p0.first;
            int c = p0.second;

            for (int i = r-1; i <= r+1; ++i)
            {
                for (int j = c-1; j <= c+1; ++j)
                {
                    if (i<0 || j<0 || i>=N || j>=M || (i==r && j==c))
                        continue;
                    if(four_directions)
                    {
                        // the two nodes in the upper corners.
                        // and the two nodes in the lower cornners.
                       if (((i==r-1) && (j==c-1||j==c+1))\
                            || ((i==r+1) && (j==c-1||j==c+1)))
                        continue;
                    }
                    pair<int,int> p(i,j);
                    if (matrix[i][j] && !visited[p])
                    {
                        visited[p] = true;
                        cur.push(p);
                    }
                }
            }
        }
        if(!cur_region->empty())
            regions->push_back(cur_region);
    }
    return regions;
}

void test()
{
    int N=0, M=0, **arr=NULL;
    scanf("%d,%d", &N, &M); // size of the matrix, separeted by ",".
    if (N<=0 || M<=0)
    {
        cout << "invalid matrix size!" << endl;
        return;
    }
    printf("matrix size: %d,%d\n", N,M);
    cout << "the matrix: " << endl;
    arr = new int*[N];
    for (int i = 0; i < N; ++i)
    {
        arr[i] = new int[M];
        for (int j = 0; j < M; ++j)
        {
            int tmp;
            scanf("%d",&tmp);
            printf("%d ", tmp);
            arr[i][j] = tmp;
            if (j < M-1)
                getchar(); // nums are separated by ",".
        }
        cout << endl;
    }
    cout << "gather the connectd regions ... " << endl;
    vector<vector<pair<int,int>>*> *regions\
        = connected_regions_in_matrix(arr, N, M);
        // = connected_regions_in_matrix(arr, N, M, true);
    cout << "the connected regions: " << endl;
    int cnt_regions = 1;
    for(vector<pair<int, int>>*r : *regions)
    {
        for(pair<int,int>p : *r)
        {
            printf("[%d,%d] ", p.first, p.second);
            int r,c;
            r = p.first;
            c = p.second;
            arr[r][c] = cnt_regions;
        }
        ++ cnt_regions;
        cout << endl;
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            if (arr[i][j])
                cout << arr[i][j] << " ";
            else
                cout << ". ";
        }
        cout << endl;
    }

}

int main(int argc, char const *argv[])
{
    test();

    return 0;
}