#include <iostream>
#include <string>
#include <radom>

using namespace std;

string generatingAlphabet();
vector<int> frequency();

int main(){
	string alfa = generatingAlphabet();
	
	string plainText;
	cin >> plainText;
	cout << v_frequency.size() << endl;

	int count = 0;
	for(size_t i=0; i<plainText.size(); i++){
		for(size_t j=0; j<alfa.size(); j++){
			
		}
	}

	cout << endl;
	return 0;
}

string generatingAlphabet(){
	char begin = 'a', end = 'z';
	string alfa;

	for(int i=begin; i<=end; i++){
		alfa.push_back(i);
	}

	return alfa;
}

vector<int> frequency(){
	srand(time(NULL));
	vector<int> v_frequency = {8, 2, 3, 4, 12, 2, 2, 6, 7, 1, 1, 4, 2, 6, 7, 2, 1, 6, 6, 9, 3, 1, 2, 1, 2, 1};
	vector<int> v;
	int sum;

	for(int i=0; i<v_frequency.size(); i++)
		sum += v_frequency.at(i);		

	cout << "Mod value: " << sum << endl;

	int count = 0;
	for(size_t i=0; i<v_frequency.size(); i++){
		while(count <= v_frequency.at(i)){
			int aux = rand() % 100;
			v.push_back(aux);
			count++;			
		}		
	}
}
