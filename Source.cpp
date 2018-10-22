
#include <iostream>
#include<conio.h>
#include<cstring>
#include<cstdlib>
using namespace std; 
#define MACHINE_PLAYER 1
#define MAX_DEPTH 5
#define DIM_MIN 3
#define DIM_MAX 9


int table[DIM_MIN][DIM_MAX];//�������
int dimensions;// ������� ����

int best_row;//������ ��� ��� ����������		
int best_col;//

//���������
void Draw();
void clear();
void init();
int parse_command_line(int argc, char *argv[]);
int check_for_winner(int b[DIM_MAX][DIM_MAX]);//��������� ���� �� ����������, ���� - ��, �� ���������� ��� �����, ���� ��� �� ���������� 0 
int minimax(int hypothetical_board[DIM_MAX][DIM_MAX], int player, bool mymove, int depth);//minmax �������� ��� ������ https://www.neverstopbuilding.com/blog/minimax
int read_player_input(int *r, int *c, int player);//��������� ��� ������ � �������



int main(int argc, char*argv[])
{
	setlocale(LC_ALL, "Russian");
	int current_player = -1; // X(�������) ����� ������
	int winner, row, col, score;
	int total_moves = 0;
	if (parse_command_line(argc, argv) != 0)//����������� ��������� ������
		return 1;
	init();//�������������� ������� (��. ������� init)
	while(true)
	{
		clear();;//������� ����� ��� ������ ����
		Draw();//������ ������������ �������, ������� ����������� � � �
		winner = check_for_winner(table);//��������� ���� �� ����������
		if (winner != 0)//���� ���� ���������� �������, ��� �������
		{
			cout << "����������: ";
			winner == -1 ? cout << "X" : cout << "O";
			break;
		}
		if (total_moves == (dimensions*dimensions))
		{
			cout<<"�����!!!";
			break;
		}
		if (current_player == MACHINE_PLAYER)
		{
			//��� ������ �� ��������� �������(������ ����)
			score = minimax(table, current_player, true, 0);

			if (score != -1000)
			{
				row = best_row;
				col = best_col;
			}
		}
		else
		{
			// ����������� ��� ��������           
			if (read_player_input(&row, &col, current_player) != 0)
			{
				continue;
			}
		}
		// ��������� �������
		if ((row >= 0 && row<dimensions) && (col >= 0 && col<dimensions))
		{
			// ��������� ������� �� �� ����� �� ��� ��� ���
			if (table[row][col] == 0)
			{
				table[row][col] = current_player;

				// ������ ������ �� �� ��� ��������
				current_player = current_player * -1;

				// �������������� ���
				total_moves++;
			}
		}

	}
	
	
		
	_getch();
	return 0;
}
int read_player_input(int *r, int *c, int player)
{
	
	printf("������� ������� %s (��������, b2):", player == -1 ? "X" : "O");

	char loc[2];
	cin >> loc[0];
	cin >> loc[1];
	// ��������� � int
	*r = tolower(loc[0]) - 'a';
	*c = loc[1] - '0';

	return 0;
}
void Draw()
{
	int i, j;

	

	printf("   ");
	for (j = 0; j < dimensions; j++)
	{
		printf(" %d  ", j);
	}
	printf("\n");
	for (i = 0; i <dimensions; i++)
	{
		printf(" %c ", (char)'a' + i);
		for (j = 0; j < dimensions; j++)
		{
			if (table[i][j] != 0)
			{
				if (table[i][j] == 1)
				{
					printf(" O ");
				}
				else
				{
					printf(" X ");
				}
			}
			else
			{
				printf("   ");
			}
			if (j<(dimensions - 1))
				printf("|");
		}
		if (i<(dimensions - 1))
		{
			printf("\n   ");
			for (j = 0; j < dimensions - 1; j++)
			{
				printf("---+");
			}
			printf("---");
		}
		printf("\n");
	}
	printf("\n");
}
void clear()
{
	system("CLS");
}

int parse_command_line(int argc, char *argv[])
{
	if (argc != 2)
	{
		// ���� �������� �� �������, �� ����������� ��� ������� 3�3
		dimensions =  3;
	}
	else
	{
		dimensions = atoi(argv[1]);
		if (dimensions < DIM_MIN || dimensions > DIM_MAX)
		{
			cout << "������� ������ ���� ���. " << DIM_MIN << " x " << DIM_MIN << " ����. " << DIM_MAX << " x " << DIM_MAX << " ������������.\n";
			return 1;
		}
	}
	return 0;
}

int minimax(int hypothetical_board[DIM_MAX][DIM_MAX], int player, bool mymove, int depth)
{
	int i, j, score;

	// ���� �� ������ ������� ������, �� ������� �� �������
	if (depth > MAX_DEPTH)
		return 0;

	//�������� �� ����������
	int winner = check_for_winner(hypothetical_board);
	if (winner != 0)
	{
		return winner;
	}

	int move_row = -1;
	int move_col = -1;
	if (mymove)
		score = -2; 
	else
		score = 2;

	for (i = 0; i<dimensions; i++)
	{
		for (j = 0; j<dimensions; j++)
		{
			if (hypothetical_board[i][j] == 0)
			{
				// ���� ��� ��������
				hypothetical_board[i][j] = player; //������� ����
				int thisScore = minimax(hypothetical_board, -1 * player, !mymove, depth + 1);

				if (mymove)
				{
					// ��� ��� ��� ���������� score        
					if (thisScore > score) {
						score = thisScore;
						move_row = i;
						move_col = j;
					}
				}
				else
				{
					// �� ��� ��� ������������� ���������� score
					if (thisScore < score) {
						score = thisScore;
						move_row = i;
						move_col = j;
					}
				}
				hypothetical_board[i][j] = 0;//�������������� �������
			}
		}
	}
	if (move_row == -1) return 0;  // ��� ��������� �����-�����
	best_row = move_row;
	best_col = move_col;
	return score;
}

void init()
{
	int i, j;

	// �������������� ������ �������
	for (i = 0; i<dimensions; i++)
	{
		for (j = 0; j<dimensions; j++)
		{
			table[i][j] = 0;
		}
	}

	best_row = -1000;
	best_col = -1000;
}
int check_for_winner(int b[DIM_MAX][DIM_MAX])
{
	// �������� �� ����������� ������� � �������
	int i, j;
	int prev, winner;

	for (i = 0; i<dimensions; i++)
	{
		// ��������� ������ ���
		prev = b[i][0];
		winner = prev;
		for (j = 1; j<dimensions; j++)
		{
			if (prev != b[i][j])
			{
				winner = 0;
			}
		}
		if (winner != 0) return(winner);

		// ��������� ������ �������
		prev = b[0][i];
		winner = prev;
		for (j = 1; j<dimensions; j++)
		{
			if (prev != b[j][i])
			{
				winner = 0;
			}
		}
		if (winner != 0) return(winner);
	}

	// ���� dimensions �������, ����� ��������� ���������
	if ((dimensions % 2) == 1)
	{
		prev = b[0][0];
		winner = prev;
		for (j = 1; j<dimensions; j++)
		{
			if (prev != b[j][j])
			{
				winner = 0;
			}
		}
		if (winner != 0) return(winner);

		prev = b[0][dimensions - 1];
		winner = prev;
		for (j = 1; j<dimensions; j++)
		{
			if (prev != b[j][dimensions - 1 - j])
			{
				winner = 0;
			}
		}
		if (winner != 0) return(winner);
	}
	return(0);
}