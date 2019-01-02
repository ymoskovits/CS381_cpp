#include <iostream>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

int main(){
	map<string, vector<pair<int,int> > > dict;
	string line, word;
	stringstream stream;
	int line_num = -1, word_num = 0;
	while(getline(cin, line)){
		stringstream stream(line);
		line_num++; word_num = -1;
		while(stream >> word){
			word_num++;
			dict[word].push_back(make_pair(line_num, word_num));
		}
	}

	for(pair<string, vector<pair<int,int> > > p : dict){
		cout << p.first << " " << p.second.size() << "[";
		for(int i = 0; i < p.second.size(); ++i){
			cout << "(" << p.second[i].first << "," << p.second[i].second << ")";
			if(i != p.second.size()-1){
				cout << ",";
			}
		}
		cout << "]" << endl;
	}

	return 0;
}