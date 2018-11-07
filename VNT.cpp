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
		
			int i = 0, j = 0;
			int potential_i, potential_j;
			//while we dont have an available cell in col 1;
			while(mp[i][j] != INT_MAX){
				//if last row, move to the right
				if(i == height-1){
					while(mp[i][j] != INT_MAX){
						if(j == length - 1){
							cout << "We shouldnt get to this code because that means the container is full";
							break;
						}
						++j;
					}
					break;
					
				}
				i++;
			}
			//If the entire last diagonal was full well use this location.
			potential_i = i;
			potential_j = j;

			//For now lets go back a diagonal and check if its full or not.
			if(j > 0){
				--j;
			}else{
				--i;
			}

			//now we have the i,j of the begining of diagonal to place elem.
			while(true){
				--i;
				++j;
				if(i < 0 || j > length-1){
					i = potential_i;
					j = potential_j;
					break;
				}
				else if(mp[i][j] == INT_MAX){
					break;
				}
			}

			mp[i][j] = elem;

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

		int min(){
			if(size == 0){
				throw new exception;
			}
			int root = mp[0][0];
			mp[0][0] = INT_MAX;
			int i = 0, j = 0;
			while(i < height)
			while(mp[i+1][j] < mp[i][j] || mp[i][j+1] < mp[i][j]){

			}

			return root;
		}

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

