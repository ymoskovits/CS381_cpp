#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
//3x^2 6x 9 x^5
//2x 4x^5 -3
using namespace std;

static ifstream in("input.txt");
static ofstream out("output.txt");

// void add(map<int,int>& a, map<int,int>& b, map<int,int>& res){
	
// 	for(pair<int,int> term : a){ 
// 		res[term->first] += a[term->first];
// 	}
// }

void add(map<int,int>& a, map<int,int>& b, map<int,int>& res){
	res = b;
	for(pair<int,int> term : a){ 
		res[term.first] += term.second;
	}
	// return res;
}

void subtract(map<int,int>& a, map<int,int>& b, map<int,int>& res){
	res = a;
	for(pair<int,int> term : b){ 
		res[term.first] -= term.second;
	}
	// return res;
}

void multiply(map<int,int>& a, map<int,int>& b, map<int,int>& res){
	// for(int i = 0; i < 100; ++i){
	// 	res[i] = 0;
	// }
	// for(int i = 0; i < 100; ++i){
	// 	for(int j = 0; j < 100; ++j){
	// 		res[i + j] += a[i] * b[j];
	// 	}
	// }\

	res.clear();

	for(pair<int, int> p : a){
		for(pair<int,int> q : b){
			res[p.first + q.first] += p.second * q.second;
		}
	}
}

void print(map<int,int>& m){
	out << endl;
	bool first_term = true;
	for(map<int,int>::reverse_iterator rit = m.rbegin(); rit != m.rend(); ++rit){
		if(rit->second == 0){
			continue;
		}
		if(rit->second > 0 && !first_term){
			out << "+";
		}
		if(rit->second != 1){
			out << rit->second;
		}
		if(rit->first != 0){
			out << "x";
			if(rit->first != 1){
				out << "^" << rit->first;
			}
		}
		first_term = false;
		
	}
	out << endl;
}



int main(){
	double coef;
	int exp;
	string line;


	// double polya[100] = {0}; // we will store the coeficients[4] = 12 for 12x^4
	// double polyb[100] = {0};
	// double ans[100] = {0};

	map<int,int> poly1, poly2, sum;



	//Get every pair of lines/polynomials;
	while(getline(in, line)){
		poly1.clear();
		poly2.clear();
		sum.clear();
		stringstream stream(line);
		out << line << endl;

		//Zero out for next set
		// for(int i = 0; i < 100; ++i){
		// 	poly1[i] = 0;
		// 	poly2[i] = 0;
		// }

		while(stream >> coef){
			stream >> exp;
			poly1[exp] = coef;
		}

		getline(in, line);
		stringstream streamb(line);
		out << line << endl;

		while(streamb >> coef){
			streamb >> exp;
			poly2[exp] = coef;
		}

		print(poly1); print(poly2);

		add(poly1, poly2, sum);
		out << "\nAdded: ";	print(sum);

		subtract(poly1, poly2, sum);
		out << "\nSubtracted: ";	print(sum);

		multiply(poly1, poly2, sum);
		out << "\nmultiplied: ";	print(sum); out << endl;
		
	}

	return 0;
}
