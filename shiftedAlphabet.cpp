#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Assignments for all the functions
void crypting();
string upperCase(string s);
string generatingAlphabet();
string shiftedAlphabet(int shift, string alfa);
void relatting(string text, string alfa);

int main(){
	int opt;

	cout << "Options:\n1 - Crypt text\n2 - Decrypt text\n3 - Check wether is a cipher text crypted with this method\nChoose: ";
	cin >> opt;
	getchar();
	fflush(stdin);
	switch(opt){
		case 1:
			crypting();
			break;
		case 2:
			decrypting();
			break;
		case 3:
			cout << "@" << endl;
			break;
		default:
			cout << "Invalid option!" << endl;
	}	

	cout << endl;
	return 0;
}

void crypting(){
	string plainText, cipherText;
	int shift;
	vector<int> relations;

	cout << "Plain text: ";
	getline(cin, plainText);
	string plainText_lc = upperCase(plainText); //Putting in lower case

	cout << "Shift: ";
	cin >> shift;

	if(shift > 26){
		cout << "Shift must be smaller then 26" << endl;
		exit(1);
	}else if(shift <= 0){
		cout << "Shift must be bigger then 0" << endl;
		exit(1);
	}

	string alfa = generatingAlphabet();	

	string alfaShifted = shiftedAlphabet(shift, alfa);	

	relations = relatting(plainText_lc, alfa);

	cout << endl << "Cipher text: ";
	for(auto e : relations)
		cout << alfaShifted.at(e);

	cout << endl;
	for(auto e : alfa)
		cout << e << " ";

	cout << endl;
	for(auto e : alfaShifted)
		cout << e << " ";
}

void decrypting(){
	string cipherText, cipherText_lc;
	int shift;
	vector<int>relations;

	cout << "Shift: ";
	cin >> shift;

	string alfa = generatingAlphabet();

	string alfaShifted = shiftedAlphabet(alfa, shift);  

	cout << "Cipher text: ";
	cin >> cipherText;
	
	cipherText_lc = upperCase(cipherText);

	relations = relatting(cipherText_lc, alfa);	

	cout << "Plain text: ";
	for(auto e : relations)
		cout << alfa.at(e);	
}

string upperCase(string s){
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

string generatingAlphabet(){
	char begin = 'a';
	string alfa;

	for(int i=begin; i<='z'; i++){
		alfa.push_back(i);
	}

	return alfa;
}

string shiftedAlphabet(int shift, string alfa){
	string alfaShifted;

	//shift = 26 - shift;

	int controller = 0;
	while(controller != 26){
		if(shift == 26){
			shift = 0;
		}
		alfaShifted.push_back(alfa.at(shift));

		shift++;
		controller++;
	}

	return alfaShifted;
}

//Relatting the text characteres positions with it's corresponding positions in the alphabet
void relatting(string text, string alfa){
	vector<int>relations;

	for(size_t i=0; i<text.size(); i++){
		for(size_t j=0; j<alfa.size(); j++){
			if(text.at(i) == alfa.at(j))
				relations.push_back(j);

		}
	}

	return relations;
}

