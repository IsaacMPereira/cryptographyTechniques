#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
	char begin = 'a';
	string alfa; //The alphabet
	string alfaShifted; //The shifted alphabet
	string cipherText, criptedText;
	int shift;
	vector<int> relations;
	
	cout << "Cipher text: ";
	getline(cin, cipherText);
	cout << "Shift: ";
	cin >> shift;
	if(shift > 26){
	    cout << "Shift must be smaller then 26" << endl;
	    exit(1);
	}else if(shift <= 0){
	    cout << "Shift must be begger then 0" << endl;
	    exit(1);
	}
	shift--;
	
	//Generating the alphabet
	for(int i=begin; i<='z'; i++){
	    alfa.push_back(i);
	}
	
	//Generating the shifted alphabet
	int controller = 0;
	while(controller != 26){
	     if(shift == 26){
	         shift = 0;
	     }
	     alfaShifted.push_back(alfa.at(shift));
	    
	     shift++;
	     controller++;
	 }
	 
	 //Relating the cipher text characteres positions with it's corresponding positions in the alphabet
	 for(size_t i=0; i<cipherText.size(); i++){
	     for(size_t j=0; j<alfa.size(); j++){
	          if(cipherText.at(i) == alfa.at(j))
	              relations.push_back(j);
	              
	      }
	 }
	 
	 cout << endl << "Cripted text: ";
	 for(auto e : relations)
	     cout << alfaShifted.at(e);
	     
	 /*cout << endl;
	 for(auto e : alfa)
	     cout << e << " ";
	     
	 cout << endl;
	 for(auto e : alfaShifted)
	     cout << e << " ";*/
	 
	 cout << endl;
	 return 0;
}