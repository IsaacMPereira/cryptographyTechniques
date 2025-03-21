/*
 * Vigenère Cipher implementation in C++
 * Reference: Simon Singh, The Code Book, 1999, pg. 66, chapter: Le Ciffre Indéchiffrable.
 *
 * Compile: $ g++ -Wall vigenereCipher.cpp -o vigenereCipher.x
 * Run: $ vigenereCipher.x 
 * */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//Assignments for all the functions
string erasingEmptySpaces(const string &s);
string lowerCasing(string s);
void vigenereSquare(string plainText, string key);
string generatingKeyWord(string key, int size);
string generatingAlphabet();

int main(){
	string plainText, key;

	cout << "Plain text: ";
	getline(cin, plainText);
	plainText = erasingEmptySpaces(plainText);
	plainText = lowerCasing(plainText);
	
	cout << "Key: ";
	getline(cin, key);
	key = erasingEmptySpaces(key);
	key = lowerCasing(key);

	vigenereSquare(plainText, key);

	cout << endl;
	return 0;
}

//Erasing the empty spaces in the string
string erasingEmptySpaces(const string &s){
	string result = s;

	result.erase(remove_if(result.begin(), result.end(), ::isspace), result.end());	

	return result;
}

//Put the string in lower case
string lowerCasing(string s){
	string result;

	for(size_t i=0; i<s.size(); i++){
		if(s.at(i) >= 'A' and s.at(i) <= 'Z'){
			s.at(i) = s.at(i) - ('A' - 'a');
			result.push_back(s.at(i));
		}else if(s.at(i) >= 'a' and s.at(i) <= 'z'){
			result.push_back(s.at(i));
		}
	}

	return result;
}

void vigenereSquare(string plainText, string key){
	char m[26][26] = {};
	string alfa, keyWord; 
	vector<int> v_plainText, v_keyWord; //Vectors for plainText and keyWord indices

	int size = plainText.size();
	keyWord = generatingKeyWord(key, size);
	cout << "Key word: " << keyWord << endl;

	alfa = generatingAlphabet();
	alfa = alfa.substr(1) + alfa.at(0); //Ensuring that the first line of the square is gonna be shifted by 1

	//Creating the square in fact
	for(int i=0; i<26; i++){
		for(int j=0; j<26; j++){
			m[i][j] = alfa.at((i+j)%26);
		}
	}	

	//Obtening the corret indices for key word and the plain text, bouth according to the alphabet
	for(size_t k=0; k<plainText.size(); k++){
		for(size_t l=0; l<alfa.size(); l++){
			if(alfa.at(l) == plainText.at(k)){
				v_plainText.push_back(l+1);
			}
		}
	}
	for(size_t m=0; m<keyWord.size(); m++){
		for(size_t n=0; n<alfa.size(); n++){
			if(alfa.at(n) == keyWord.at(m)){
				v_keyWord.push_back(n);
			}
		}
	}	

	//Matching the right element in the square according to the ordered pair obtened by the last two for-loops
	cout << "Cipher text: ";
	for(size_t z=0; z<v_plainText.size(); z++){
		int i = v_plainText.at(z);
		int j = v_keyWord.at(z);

		cout << m[i][j];
	}

	//Printting the square just for a better visualization
	/*cout << endl;
	for(int i=0; i<26; i++){
		cout << endl;
		for(int j=0; j<26; j++){
			cout << m[i][j] << " ";
		}
	}*/
}

string generatingKeyWord(string key, int size){
	int i=0, controller=0;
	string keyWord;

	while(1){
		keyWord.push_back(key.at(i % (key.size())));
		i++;
		controller++;
		if(controller == size){
			break;
		}
	}

	return keyWord;
}

string generatingAlphabet(){
	char begin = 'a', end = 'z';
	string alfa;

	for(int i=begin; i<=end; i++){
		alfa.push_back(i);
	}

	return alfa;
}
