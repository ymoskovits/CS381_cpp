#include <climits>
#include <cmath>
#include <algorithm>
#include "SafeMatrix.cpp"

/*
TODO:
	Edit so that we dont make mp it too big (off by one)
*/ 

class VNT : private SafeMatrix<int>{
	int size;
	int capacity;
	public:
		VNT(int m, int n) : SafeMatrix<int>(0, m-1, 0, n-1){
			size = 0;
			capacity = n * m;
			for(int i = 0; i < height; ++i){
				for(int j = 0; j < length; ++j){
					mp[i][j] = INT_MAX;
				}
			}
		}

		void add(int elem){
			if(size == capacity){
				throw new exception;
			}
			int depth = (-1 + sqrt(1 + 8 * size)) / 2.0;
			cout << depth << " ";
			int offset = size - (depth * (depth+1)/2);
			cout << offset << endl;
			//This can be improved possibly
			if(depth >= height-1){
				cout << "HIT"; 
				depth = height-1;
				offset = 0;
				while(mp[depth][offset + 1] != INT_MAX){
					offset++;
				}
				while(mp[depth-1][offset+1] != INT_MAX){
					depth--;
					offset++;
				}
			}
			cout << depth << " " << offset << endl;


			mp[depth][offset] = elem;

			int i = depth, j = offset;

			while(i > 0 && mp[i][j] < mp[i-1][j]){
					std::swap(mp[i][j], mp[i-1][j]);
					i--;
			}
			while(j > 0 && mp[i][j] < mp[i][j-1]){
					std::swap(mp[i][j], mp[i][j-1]);
					j--;
			}

			++size;
		}

		// int min(){
		// 	if(size == 0){
		// 		throw new exception;
		// 	}
		// 	int root = mp[0][0];
		// 	mp[0][0] = INT_MAX;
		// 	int i = 0, j = 0;
		// 	while(i < height)
		// 	while(mp[i+1][j] < mp[i][j] || mp[i][j+1] < mp[i][j]){

		// 	}

		// 	return root;
		// }

		void printmat(){
			for(int i = 0; i < height; ++i){
				for(int j = 0; j < length; ++j){
					if(mp[i][j] == INT_MAX){
						cout << -1 << " ";
					}
					else{
						cout << mp[i][j] << " ";

					}
				}
				cout << endl;
			}
		}

};

int main(){
	VNT a(10,10);
	for(int i = 99; i > 0; --i){
		a.add(i);
	}
	a.printmat();
}

