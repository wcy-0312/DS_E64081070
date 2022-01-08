#include<iostream>
#include<string>
#include<fstream>
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


void dfs(int **adj_matrix, int size, int entry, bool visited[], ofstream &ofs){
    ofs << entry << " ";
    visited[entry] = true;
    for(int i=0; i<size; i++)
        if(adj_matrix[entry][i]==1 && !visited[i])
            dfs(adj_matrix, size, i, visited, ofs);
    
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
        bool visited[100] = {false};
        dfs(adj_matrix[i] , m, t[i], visited,);
        ofs << endl;
    }
            
    return 0;
}

