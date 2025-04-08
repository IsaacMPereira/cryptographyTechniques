#include <iostream>
#include <string>
//#include <radom>
#include <set>
#include <vector>

using namespace std;

string generatingAlphabet();
set<int> frequency();

int main(){
	set<int> v;

	string alfa = generatingAlphabet();
	
	//string plainText;
	//cin >> plainText;

	v = frequency();
	for(auto e : v)
		cout << e << " ";

	cout << endl;
	return 0;
}

string generatingAlphabet(){
	char begin = 'a', end = 'z';
	string alfa;

	for(int i=begin; i<=end; i++)
		alfa.push_back(i);

	return alfa;
}

set<int> frequency(){
	srand(time(NULL));
	vector<int> v_frequency = {8, 2, 3, 4, 12, 2, 2, 6, 7, 1, 1, 4, 2, 6, 7, 2, 1, 6, 6, 9, 3, 1, 2, 1, 2, 1};
	set<int> v;
	int sum=0;

	int s1 = v_frequency.size();
	for(int i=0; i<s1; i++)
		sum += v_frequency.at(i);		

	cout << v_frequency.size() << endl;

	for(auto e : v_frequency)
		cout << e << " ";

	cout << endl << "Mod value: " << sum << endl;

	int aux;
	size_t z = sum;
	while(v.size() != z){
		aux = rand() % 100;
		v.insert(aux);
	}

	cout << endl << v.size() << endl;

	return v;
}
