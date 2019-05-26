#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>

using namespace std;

#define MAX_A 3
#define MAX_D 2

struct army{
	int attacker;
	int defender;
};

void print(int a[], const int SIZE){
	cout << "{";
	for(int i = 0; i < SIZE; i++){
		cout << a[i];
		if(i+1 < SIZE)
			cout << ",";
	}
	cout << "}\n";
}

void input(army &armies){
	cout << "Attacker: ";
	cin >> armies.attacker;
	cout << "Defender: ";
	cin >> armies.defender;
}

void fight(army &armies){
	const int ATT_SIZE = (armies.attacker >= MAX_A)? MAX_A : armies.attacker;
	const int DEF_SIZE = (armies.defender >= MAX_D)? MAX_D : armies.defender;
	int att[ATT_SIZE];
	int def[DEF_SIZE];

	for(int i = 0; i < ATT_SIZE; i++)
		att[i] = rand() % 6 + 1;
	for(int j = 0; j < DEF_SIZE; j++)
		def[j] = rand() % 6 + 1;

	sort(att, att+ATT_SIZE, greater<int>());
	sort(def, def+DEF_SIZE, greater<int>());

	cout << " FIGHT!\n";
	cout << "   Att: ";
	print(att, ATT_SIZE);
	cout << "   Def: ";
	print(def, DEF_SIZE);

	for(int count = 0; count < ATT_SIZE && count < DEF_SIZE; count++){
		if(att[count] > def[count])
			armies.defender -= 1;
		else
			armies.attacker -= 1;
	}	
}

void calculate(army &armies){
	if(armies.attacker == 0 || armies.defender == 0){
		return;
	}else{
		fight(armies);
		calculate(armies);	
	}
}

int main(){
	srand(time(0));
	army armies;

	input(armies);
	calculate(armies);

	string result = (armies.attacker == 0)? "defender(s)" : "attacker(s)";
	cout << "The " << result << " won!" << endl;
	return 0;
}
