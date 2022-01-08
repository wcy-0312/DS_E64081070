#include<iostream>
#include<string>
#include<fstream>
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


void bfs(int **adj_matrix, int size, int entry, ofstream &ofs){
    vector<bool> visited(size, false);
    vector<int> q;
    q.push_back(entry);
    visited[entry] = true;
    int curr;

    
    while (!q.empty())
    {
        curr = q[0];
        ofs << curr << " ";
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

    // read/write file
    ifstream ifs;
    string inputpath;

    cout << "Input file path: ";
    getline(cin, inputpath);
    ifs.open(inputpath);

    inputpath.replace(inputpath.find("in"), 2, "out");
    ofstream ofs(inputpath);

    if (!ifs.is_open()){
        cout << "Failed to open file." << endl;
        return 1;
    }else{
        ifs >> n;  
    }
    
    adj_matrix = create_3D_Array(n);
    for(int k=0; k<n; k++){
        ifs >> m >> t[k];
        for(int i=0; i<m; i++){
            for(int j=0; j<m; j++){
                ifs >> adj_matrix[k][i][j];
            }
        }     
    }    
    
    for(int i=0; i<n; i++){
        bfs(adj_matrix[i] , m, t[i], ofs);
        ofs << endl;
    }
            
    return 0;
}

