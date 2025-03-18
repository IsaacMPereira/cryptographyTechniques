#include <iostream>
#include <string>

using namespace std;

//Assignments for all the functions
void vigenereSquare();
string shiftedAlphabet(int shift);
string generatingAlphabet();

int main(){
	vigenereSquare();

	cout << endl;
	return 0;
}

void vigenereSquare(){
	string m[26][26];

	int rowsController = 0;
	for(int i=1; i<=26; i++){
		string aux = shiftedAlphabet(i);
		cout << "@" << aux << endl;
		for(int j=0; j<26; j++){
			for(int k=0; k<26; k++){
				for(auto e : aux){
					if(k == rowsController){
						m[j][k] = e;
					}
				}
			}
		}
		rowsController++;
	}

	for(int i=0; i<26; i++){
		cout << endl;
		for(int j=0; j<26; j++){
			cout << m[i][j] << " ";
		}
	}
}

string shiftedAlphabet(int shift){
	int controller = 0;
	string alfa, alfaShifted;

	alfa = generatingAlphabet();

	while(controller != 26){
		if(shift == 26)
			shift = 0;

		alfaShifted.push_back(alfa.at(shift));

		shift++;
		controller++;
	}

	/*for(auto e : alfa)
	  cout << e << " ";

	  cout << endl;
	  for(auto e : alfaShifted)
	  cout << e << " ";*/

	return alfaShifted;
}

string generatingAlphabet(){
	char begin = 'a';
	string alfa;

	for(int i=begin; i<='z'; i++){
		alfa.push_back(i);
	}

	return alfa;
}
