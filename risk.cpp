#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>

using namespace std;

#define MAX_A 3
#define MAX_D 2

int DICE = 6;

struct Army{
	int attacker;
	int defender;
};

void print_army(int a[], const int SIZE){
	cout << "{";
	for(int i = 0; i < SIZE; i++){
		cout << a[i];
		if(i+1 < SIZE)
			cout << ",";
	}
	cout << "}\n";
}

void input(Army &armies, int &AMOUNT){
	cout << "Attacker: ";
	cin >> armies.attacker;
	cout << "Defender: ";
	cin >> armies.defender;

	cout << "Simulate so many times: ";
	cin >> AMOUNT;
	if(AMOUNT < 1)
		AMOUNT = 1;
}

void fight(Army &armies, bool print){
	const int ATT_SIZE = (armies.attacker >= MAX_A)? MAX_A : armies.attacker;
	const int DEF_SIZE = (armies.defender >= MAX_D)? MAX_D : armies.defender;
	int att[ATT_SIZE];
	int def[DEF_SIZE];

	for(int i = 0; i < ATT_SIZE; i++)
		att[i] = rand() % DICE + 1;
	for(int j = 0; j < DEF_SIZE; j++)
		def[j] = rand() % DICE + 1;

	sort(att, att+ATT_SIZE, greater<int>());
	sort(def, def+DEF_SIZE, greater<int>());

	if(print){
		cout << " FIGHT!\n";
		cout << "   Att: ";
		print_army(att, ATT_SIZE);
		cout << "   Def: ";
		print_army(def, DEF_SIZE);
	}

	for(int count = 0; count < ATT_SIZE && count < DEF_SIZE; count++){
		if(att[count] > def[count])
			armies.defender -= 1;
		else
			armies.attacker -= 1;
	}
}

void calculate(Army &armies, bool print){
	if(armies.attacker == 0 || armies.defender == 0){
		return;
	}else{
		fight(armies, print);
		calculate(armies, print);
	}
}

void simulate_once(Army &armies){
	calculate(armies, true);
	string result = (armies.attacker == 0)? "defender" : "attacker";
	cout << "The " << result << " won!" << endl;
}

void simulate_multi(Army &armies, const int &AMOUNT){
	Army copy_armies = armies;
	int att_wins = 0, def_wins = 0;

	for(int i = 0; i < AMOUNT; i++){
		calculate(armies, false);
		if(armies.attacker == 0)
			def_wins++;
		else
			att_wins++;
		armies = copy_armies;
	}

	cout << "  The attacker won " << att_wins << " time(s).\n";
	cout << "  The defender won " << def_wins << " time(s).\n";
	cout << "So the succes rate of the attackers is " << (int)(((double)att_wins / AMOUNT) * 100) << "%.\n";
}

void simulate(Army &armies, const int &AMOUNT){
	if(AMOUNT == 1)
		simulate_once(armies);
	else
		simulate_multi(armies, AMOUNT);
}

int main(int argc, char *argv[]){
	if(argc > 1)
		DICE = strtol(argv[1], nullptr, 0);

	srand(time(0));
	Army armies;
	int AMOUNT;

	input(armies, AMOUNT);
	simulate(armies, AMOUNT);

	return 0;
}
