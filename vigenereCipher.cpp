/*
 * Vigenère Cipher implementation in C++
 * Reference: Simon Singh, The Code Book, 1999, pg. 66.
 *
 * Compile: $ g++ -Wall vigenereCipher.cpp -o vigenereCipher.x
 * Run: $ vigenereCipher.x 
 * */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Assignments for all the functions
void vigenereSquare(string plainText, string key);
string generatingAlphabet();

int main(){
	string plainText, key;

	cout << "Plain text: ";
	cin >> plainText;
	cout << "Key: ";
	cin >> key;

	vigenereSquare(plainText, key);

	cout << endl;
	return 0;
}

void vigenereSquare(string plainText, string key){
	char m[26][26] = {};
	string alfa, keyWord; 
	vector<int> v_plainText, v_keyWord;

	int i = 0, controller = 0, size = plainText.size();
	while(1){
		keyWord.push_back(key.at(i % (key.size())));
		i++;
		controller++;
		if(controller == size){
			break;
		}
	}
	cout << "Key word: " << keyWord << endl;

	alfa = generatingAlphabet();
	alfa = alfa.substr(1) + alfa.at(0);

	for(int i=0; i<26; i++){
		for(int j=0; j<26; j++){
			m[i][j] = alfa.at((j+i)%26);
		}
	}	

	cout << "Cipher text: ";
	//int aux_p, aux_k;
	for(size_t k=0; k<plainText.size(); k++){
		for(size_t l=0; l<alfa.size(); l++){
			if(alfa.at(l) == plainText.at(k)){
				//aux_p = l+1;				
				//cout << l+1 << " ";
				v_plainText.push_back(l+1);
			}
		}
	}

	for(size_t m=0; m<keyWord.size(); m++){
		for(size_t n=0; n<alfa.size(); n++){
			if(alfa.at(n) == keyWord.at(m)){
				//aux_k = n;
				//cout << n << " ";
				v_keyWord.push_back(n);
			}
		}
	}	

	for(size_t z=0; z<v_plainText.size(); z++){
		int i = v_plainText.at(z);
		int j = v_keyWord.at(z);

		cout << m[i][j];
	}

	/*cout << endl;
	for(auto e : v_plainText)
		cout << e << " ";

	cout << endl;
	for(auto e : v_keyWord)
		cout << e << " ";*/

	cout << endl;
	for(int i=0; i<26; i++){
		cout << endl;
		for(int j=0; j<26; j++){
			cout << m[i][j] << " ";
		}
	}

}

string generatingAlphabet(){
	char begin = 'a', end = 'z';
	string alfa;

	for(int i=begin; i<=end; i++){
		alfa.push_back(i);
	}

	return alfa;
}
