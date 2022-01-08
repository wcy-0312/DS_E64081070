#include<iostream>
#include<vector>
#include <cstdlib>
using namespace std;

int ***create_3D_Array(int n)
{
	int ***A = new int**[n];
	for (int i = 0 ; i < n ; i++)
	{
		A[i] = new int*[100];
		for (int j = 0 ; j < 100 ; j++)
		{
			A[i][j] = new int[100];
		}
	}
	for (int i = 0 ; i < n ; i++)
		for (int j = 0 ; j < 100 ; j++)
			for (int k = 0 ; k < 100 ; k++)
				A[i][j][k] = 0;
	return A;
}


void bfs(int **adj_matrix, int size, int entry){
    vector<bool> visited(size, false);
    vector<int> q;
    q.push_back(entry);
    visited[entry] = true;
    int curr;

    
    while (!q.empty())
    {
        curr = q[0];
        cout << curr << " ";
        q.erase(q.begin());

        for(int i=0; i<size; i++){
            if(adj_matrix[curr][i]==1 && !visited[i]){
                q.push_back(i);
                visited[i] = true;
            }
        }
    }
    
    
}

int main(){

    
    int ***adj_matrix;
    int n; // number of datasets
    int m, t[100]; // number of vertices & entry
    
    cin >> n;
    adj_matrix = create_3D_Array(n);
    for(int k=0; k<n; k++){
        cin >> m >> t[k];
        for(int i=0; i<m; i++){
            for(int j=0; j<m; j++){
                cin >> adj_matrix[k][i][j];
            }
        }     
    }
    cout << endl;    
    
    for(int i=0; i<n; i++){
        bfs(adj_matrix[i] , m, t[i]);
        cout << endl;
    }
            
    return 0;
}

