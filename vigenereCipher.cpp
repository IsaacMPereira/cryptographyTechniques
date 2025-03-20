/*
 * Vigenère Cipher implementation in C++
 * Reference: Simon Singh, The Code Book, 1999, pg. 66.
 *
 * Compile: $ g++ -Wall vigenereCipher.cpp -o vigenereCipher.x
 * Run: $ vigenereCipher.x 
 * */

#include <iostream>
#include <string>

using namespace std;

//Assignments for all the functions
void vigenereSquare();
string generatingAlphabet();

int main(){
	vigenereSquare();

	cout << endl;
	return 0;
}

void vigenereSquare(){
	char m[26][26] = {};
	//int shift = 0;

	string alfa = generatingAlphabet();
	alfa = alfa.substr(1) + alfa[0];
	cout << alfa << endl;
	int count=0;
	for(auto e : alfa){
		cout << e << "|" << count << " ";
		count++;
	}
	cout << endl;

	//cout << shift << endl;
	for(int i=0; i<26; i++){
		for(int j=0; j<26; j++){
			m[i][j] = alfa.at((j+i)%26);
		}
	}	

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
