//C++ version tic tac toe game

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void print_board(char* group)
{
	cout << "\t\t| " << group[0] << " | " << group[1] << " | " << group[2] << " |\n";
	cout << "\t\t|-----------|" << endl;
	cout << "\t\t| " << group[3] << " | " << group[4] << " | " << group[5] << " |\n";
	cout << "\t\t|-----------|" << endl;
	cout << "\t\t| " << group[6] << " | " << group[7] << " | " << group[8] << " |\n";
}


char* check_three(char kind, char* group)
{
	char situation[9] = {};
	int index = 0;
	int all_possible[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
	for (int i = 0; i < 8; i++){
		int x = all_possible[i][0];
		int y = all_possible[i][1];
		int z = all_possible[i][2];
		if((group[x]==kind && group[y]==kind && group[z]==' ') || 
			(group[x]==kind && group[y]==' ' && group[z]==kind) || 
			(group[x]==' ' && group[y]==kind && group[z]==kind)){
			if (group[x] == ' '){
				situation[index] = '0' + x;		//convert int to char
				index++;
			}
			else if (group[y] == ' '){
				situation[index] = '0' + y;		//convert int to char
				index++;
			}
			else if (group[z] == ' '){
				situation[index] = '0' + z;		//convert int to char
				index++;
			}
		}
	}
	return situation;
}


int human_step(char* group)
{
	int posit;
	cout << "Your turn. Enter a number: ";
	cin >> posit;
	while (group[posit-1] != ' '){
		cout << "Please enter a valid cell number: ";
		cin >> posit;
	}
	return posit - 1;
}


int pc_step(int step, char* group)
{
	srand((unsigned)time(NULL)); 
	if (step == 0){
		int pro_step[5] = {0, 2, 4, 6, 8};
		int position = rand() % 4;
		return pro_step[position];
	}
	else if (step == 2){
        	if (group[4] == 'X'){
			int cor_step[4] = {0, 2, 6, 8};
            		for(int i = 0; i < 4; i++){
				if (group[cor_step[i]] == 'O'){
                    			int posit = 0;
                    			if (cor_step[i] == 0)
                        			posit = 8;
                    			else if (cor_step[i] == 8)
                        			posit = 0;
                    			else if (cor_step[i] == 2)
                        			posit = 6;
                   			else if (cor_step[i] == 6)
                        			posit = 2;
                    			return posit;
				}
			}
			int nearby[2] = {0, 0};
            		if (group[1] == 'O'){
                		nearby[0] = 0;
                		nearby[1] = 2;
			}
            		else if (group[3] == 'O'){
                		nearby[0] = 0;
                		nearby[1] = 6;
			}
            		else if (group[5] == '0'){
                		nearby[0] = 2;
                		nearby[1] = 8;
			}
            		else if (group[7] == '0'){
                		nearby[0] = 6;
                		nearby[1] = 8;
			}
            		int posit = nearby[rand() % 2];
            		return posit;
		}
        	else{
            		if (group[4] == ' ')
               	 		return 4;
            		int posit = 0;
            		if (group[0] == 'X')
                		posit = 8;
            		else if (group[8] == 'X')
                		posit = 0;
            		else if (group[2] == 'X')
                		posit = 6;
            		else if (group[6] == 'X')
                		posit = 2;
            		return posit;
		}
	}
    	else{
        	char* first_arr = check_three('X', group);
        	if (strlen(first_arr) != 0){
            		int posit = first_arr[0];
            		return posit;
		}
        	char* second_arr = check_three('O', group);
        	if (strlen(second_arr) != 0){
            		int posit = second_arr[0];
            		return posit;
		}
        	int third_posit = 0;
        	int third_max = -1;
        	for (int temp = 0; temp < 10; temp++){
            		if (group[temp] == ' '){
                		if (third_max == -1){
                    			third_posit = temp;
                    			third_max = 0;
				}
                		char* temp_group = group;
                		char* temp_arr = check_three('X', temp_group);
                		if (strlen(temp_arr) > third_max){
                    			third_max = strlen(temp_arr);
                    			third_posit = temp;
				}
			}
		}
        	return third_posit;
	}
}


int whose_turn(int step)
{
	if (step % 2 == 0)
		return 1;
	else
		return 2;
}


void result(char state)
{
	if (state == 'X')
		cout << "Aha, you lose!" << endl;
	else if (state == 'O')
		cout << "Wow, you win!" << endl;
	else if (state == ' ')
		cout << "Tie! Try again." << endl;
	else
		cout << "Error." << endl;
}


bool game_over(char* group)
{
	if (group[0] == group[1] && group [1] == group[2] && group[0] != ' '){
		result(group[0]);
		return true;
	}
	else if (group[3] == group[4] && group [4] == group[5] && group[3] != ' '){
		result(group[3]);
		return true;
	}
	else if (group[6] == group[7] && group [7] == group[8] && group[6] != ' '){
		result(group[6]);
		return true;
	}
	else if (group[0] == group[3] && group [3] == group[6] && group[0] != ' '){
		result(group[0]);
		return true;
	}
	else if (group[1] == group[4] && group [4] == group[7] && group[7] != ' '){
		result(group[1]);
		return true;
	}
	else if (group[2] == group[5] && group [5] == group[8] && group[2] != ' '){
		result(group[2]);
		return true;
	}
	else if (group[0] == group[4] && group [4] == group[8] && group[0] != ' '){
		result(group[0]);
		return true;
	}
	else if (group[2] == group[4] && group [4] == group[6] && group[2] != ' '){
		result(group[2]);
		return true;
	}
	else
	{
		bool is_tie = true;
		for (int i = 0; i < 9; i++)
			if (group[i] == ' ')
				is_tie = false;
		if (is_tie)
		{
			result(' ');
			return true;
		}
		else
			return false;
	}
}



int main()
{
	char group[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	int step = 0;
	cout << "Choss a cell numbered from 1 to 9 as below and play.\n";
	cout << "\t\t| 1 | 2 | 3 |" << endl;
	cout << "\t\t|-----------|" << endl;
	cout << "\t\t| 4 | 5 | 6 |" << endl;
	cout << "\t\t|-----------|" << endl;
	cout << "\t\t| 7 | 8 | 9 |" << endl;

	while(!game_over(group))
	{
		int turn = whose_turn(step);		// 1->computer, 2->human
		if (turn == 1)
		{
			group[pc_step(step, group)] = 'X';
			cout << "Computer has done." << endl;
		}
		else if (turn == 2)
		{
			group[human_step(group)] = 'O';
			cout << "Human has done. Computer's turn." << endl;
		}
		print_board(group);
		step++;
	}

	system("pause");
	return 0;
}
