#include <iostream>

using namespace std;

int main(){
	char begin = 'a', end = 'z';
	string alfa;

	for(int i=begin; i<=end; i++){
		alfa.push_back(i);
	}

	for(size_t i=0; i<alfa.size(); i++){
		cout << alfa.at(i) << "|" << i+1 << " ";
	}

	cout << endl;
	return 0;
}
