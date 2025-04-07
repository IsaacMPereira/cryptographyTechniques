#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[2]){
	if(argc != 2){
		cout << "Error! Run: $ alphabet.x shift" << endl;
		exit(1);	
	}

	int shift = atoi(argv[1]), controller=0;
	char begin = 'a';
	string alfa, alfaShifted;

	//shift = 26 - shift;
	//cout << shift << endl;

	if(shift > 26){
		cout << "Shift must be smaller then 26" << endl;
		exit(1);
	}

	for(int i=begin; i<='z'; i++){
		alfa.push_back(i);
	}

	while(controller != 26){
		if(shift == 26){
			shift = 0;
		}
		alfaShifted.push_back(alfa.at(shift));
		//cout << "shift:" << shift << " controller:" << controller << endl;

		shift++;
		controller++;
	}

	//int z=0;
	for(auto e : alfa){
		cout << e << " ";
		//cout << e << "|" << z << " ";
		//z++;
	}

	cout << endl;
	//z=0;
	for(auto e : alfaShifted){
		cout << e << " ";
		//cout << e << "|" << z << " ";
		//z++;
	}

	cout << endl;
	return 0;
}
