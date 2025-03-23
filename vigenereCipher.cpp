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
#include <regex>
#include <fstream>

using namespace std;

//Assignments for all the functions
string erasingEmptySpaces(const string &s);
bool isAlphabetic(const string &s);
string lowerCasing(string s);
void vigenereSquare(string plainText, string key);
string generatingKeyWord(string key, int size);
string generatingAlphabet();

int main(){
	string plainText, key;

	cout << "Plain text: ";
	getline(cin, plainText);
	plainText = erasingEmptySpaces(plainText);
	if(!isAlphabetic(plainText)){
		cout << "Error. String can't have not alphabetics characteres" << endl;		
		exit(1);
	}
	plainText = lowerCasing(plainText);

	cout << "Key: ";
	getline(cin, key);
	key = erasingEmptySpaces(key);
	if(!isAlphabetic(key)){
		cout << "Error. String can't have not alphabetics characteres" << endl;
		exit(1);
	}
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

//Ensuring that the characteres are alphabetic
bool isAlphabetic(const string &s){
	regex alfaRegex("^[A-Za-z]+$");

	return regex_match(s, alfaRegex);
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
	string alfa, keyWord, cipherText; 
	vector<int> v_plainText, v_keyWord; //Vectors for plainText and keyWord indices
	ofstream file1("vigenereCheckerFile.txt");
	if(!file1.is_open()){
		cout << "Error on opennig vigenereCheckerFile.txt (file1)  in 'w' mode in vigenereSquare()" << endl;
		exit(1);
	}

	int size = plainText.size();
	keyWord = generatingKeyWord(key, size);
	cout << "Key word: " << keyWord << endl;

	alfa = generatingAlphabet();
	alfa = alfa.substr(1) + alfa.at(0); //Ensuring that the first line of the square is gonna be shifted by 1

	//Creating the square in fact and inserting it in the checker file
	for(int i=0; i<26; i++){
		for(int j=0; j<26; j++){
			m[i][j] = alfa.at((i+j)%26);
			file1 << m[i][j] << i << "|" << j << "\t";
			if(j == 25){
				file1 << "\n";
			}
		}
	}	
	file1 << "\n\n";

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
		cipherText.push_back(m[i][j]);
	}

	//Printting the square just for a better visualization
	/*cout << endl;
	  for(int i=0; i<26; i++){
	  cout << endl;
	  for(int j=0; j<26; j++){
	  cout << m[i][j] << " ";
	  }
	  }*/

	//Inserting the vectors, key word, plain text and cipher text in the checker file 
	for(auto e : v_keyWord)
		file1 << e << "\t";

	file1 << "\n";
	for(auto e : v_plainText)
		file1 << e << "\t";

	file1 << "\n\n";
	for(auto e : keyWord)
		file1 << e << "\t";

	file1 << "\n";
	for(auto e : plainText)
		file1 << e << "\t";

	/*file1 << "\n";
	//cout << endl << endl;
	for(auto e : cipherText)
		file1 << e << "\t";*/

	file1.close();
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
