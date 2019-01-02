#include <climits>
#include <cmath>
#include <algorithm>
#include "SafeMatrix.cpp"

/*
TODO:
	Change the propogate up so that it goes along the diagonal until a border instead of along a border.
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


			//find the max of 2 parents and swap
			while(i > 0 && j > 0){
				if(mp[i][j] > mp[i-1][j] && mp[i][j] > mp[i][j-1]){
					break;
				}
				else if(mp[i-1][j] > mp[i][j-1]){
					std::swap(mp[i][j], mp[i-1][j]);
					i--;
				}
				else{
					std::swap(mp[i][j], mp[i][j-1]);
					j--;
				}
			}

			//If at borders just propogate up.
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

		int getMin(){
			if(size == 0){
				throw new exception;
			}
			int root = mp[0][0];
			mp[0][0] = INT_MAX;
			int i = 0, j = 0;

			while(i < height - 1 && j < length - 1){
				if(mp[i][j] < mp[i+1][j] && mp[i][j] < mp[i][j+1]){
					break;
				}
				else if(mp[i+1][j] < mp[i][j+1]){
					std::swap(mp[i][j], mp[i+1][j]);
					i++;
				}
				else{
					std::swap(mp[i][j], mp[i][j+1]);
					j++;
				}
			}

			while(i < height-1 && mp[i][j] > mp[i+1][j]){
					std::swap(mp[i][j], mp[i+1][j]);
					i++;
			}
			while(j < length-1 && mp[i][j] > mp[i][j+1]){
					std::swap(mp[i][j], mp[i][j+1]);
					j++;
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

		void sort(int k[], int size){
			int dim = sqrt(size) + 1;
			VNT vnt(dim,dim);
			for(int i = 0; i < size; ++i){
				vnt.add(k[i]);
			}

			for(int i = 0; i < size; ++i){
				k[i] = vnt.getMin();
			}

		}

		bool find(int target){
			if(target < mp[0][0]){
				return false;
			}
			else if(target == mp[0][0]){
				return true;
			}

			int maxrow = height-1, minrow = 0;
			int maxcol = length-1, mincol = 0;
			//narrow down to a range of rows.
			while(mp[maxrow][0] > target){
				--maxrow;
			}
			while(mp[minrow][length-1] < target){
				++minrow;
			}

			maxcol = length-1;
			mincol = 0;
			//find the mincol
			while(mp[maxrow][mincol] < target){
				++mincol;
			}
			//find the maxcol
			while(mp[minrow][maxcol] > target){
				--maxcol;
			}


			for(int i = minrow; i <= maxrow; ++i){
				for(int j = mincol; j <= maxcol; ++j){
					if(mp[i][j] == target){
 						return true;
					}
				}
			}
			return false;
		}


};

int main(){

    VNT a(5,6);
    
    for(int i=0;i<30;i++){
        a.add(i*i);
    }
    if(a.find(25)){
        cout<<"Found 25 int VNT table\n";
    }
    if(!a.find(26)){
        cout<<"26 is not in the VNT table\n";
    }
    cout<<"The minimum value in VNT table is: "<<a.getMin()<<endl;
    
    int arr[10]= {2,6,9,0,3,1,8,4,7,5};
    cout<<"Unsorted array is:\n";
    for(auto e:arr)
        cout<<e<<" ";
    cout<<endl;
    
    a.sort(arr,10);
    cout<<"Sorted Array is:\n";
    for(auto e:arr)
        cout<<e<<" ";
    cout<<endl;

}

