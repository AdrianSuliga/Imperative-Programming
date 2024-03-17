#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NUMBER_OF_CARDS 52
#define NUMBER_OF_COLORS 4

int pA = 0, pB = 0;
int eA = 25, eB = 25;

int random_from_interval(int a, int b) {
	if (a > b)
		return INT_MIN;
	if (b - a > RAND_MAX)
		return INT_MAX;
	if (a == b)
		return a;
	else
		return rand() % (b - a + 1) + a;
}

void swap(int array[], int i, int k)
{
	int buffor = array[k];
	array[k] = array[i];
	array[i] = buffor;
}

void shuffle(int t[], int size) {
	if (size >= 0)
	{
		for (int i = 0; i < size; i++)
		{
			t[i] = i;
		}
		for (int i = 0; i < size - 1; i++)
		{
			int k = random_from_interval(i, size - 1);
			swap(t, i, k);
		}
	}
}

void one_takes_cards(int winner[], int* size1, int loser[], int* size2, int flag) 
{																			
	if (flag == 0)
	{
		*size1 += pB;
		for (int i = 0; i < pA; i++)
		{
			int buffor = winner[0];
			for (int i = 1; i < eA + 1; i++)
			{
				winner[i - 1] = winner[i];
			}
			winner[eA] = buffor;
		}
		int ind = 0;
		for (int i = eA + 1; i < eA + pB + 1; i++)
		{
			winner[i] = loser[ind];
			ind++;
		}
		for (int i = 0; i < pB; i++)
		{
			loser[i] = -1;
		}
		for (int i = pB; i < *size2; i++)
		{
			loser[i - pB] = loser[i];
		}
		*size2 -= pB;
		eB -= pB;
		eA += pB;
		pB = 0;
		pA = 0;
	}
	else
	{
		*size1 += pA;
		for (int i = 0; i < pA; i++)
		{
			int buffor = winner[0];
			for (int i = 1; i < eB + 1; i++)
			{
				winner[i - 1] = winner[i];
			}
			winner[eB] = buffor;
		}
		int ind = 0;
		for (int i = eB + 1; i < eB + pA + 1; i++)
		{
			winner[i] = loser[ind];
			ind++;
		}
		for (int i = 0; i < pA; i++)
		{
			loser[i] = -1;
		}
		for (int i = pA; i < *size2; i++)
		{
			loser[i - pA] = loser[i];
		}
		*size2 -= pA;
		eB += pA;
		eA -= pA;
		pA = 0;
		pB = 0;
	}
}

void both_take_cards(int playerA[], int playerB[], int sizeA, int sizeB)
{
	for (int i = 0; i < pA; i++)
	{
		int buffor = playerA[0];
		for (int i = 1; i < sizeA; i++)
		{
			playerA[i - 1] = playerA[i];
		}
		playerA[eA] = buffor;
	}
	for (int i = 0; i < pB; i++)
	{
		int buffor = playerB[0];
		for (int i = 1; i < sizeB; i++)
		{
			playerB[i - 1] = playerB[i];
		}
		playerB[eB] = buffor;
	}
	pA = 0;
	pB = 0;
}

int who_wins(int deck1[], int deck2[], int size1, int size2, int *conflict_count, int conflict_max)
{
	int card1 = deck1[pA];
	int card2 = deck2[pB];
	
	pA++;
	pB++;

	(*conflict_count)++;
	card1 >>= 2;
	card2 >>= 2;

	if (*conflict_count >= conflict_max)
		return 0;

	if (card1 > card2)
		return 1;
	else if (card1 < card2)
		return 2;
	else
		return 0;
}

void print_arr(int player[], int size)
{
	for (int i = 0; i < size; i++)
		printf("%d ", player[i]);
	printf("\n");
}

void game(int n, int player_A[], int player_B[], int max_conflicts, int simplified_mode) {
	int player_A_deck_size = NUMBER_OF_CARDS / 2, player_B_deck_size = n - player_A_deck_size;
	int confilct_count = 0, winner = 0;
 
	while (confilct_count < max_conflicts && player_A_deck_size > 0 && player_B_deck_size > 0)
	{
		winner = who_wins(player_A, player_B, player_A_deck_size, player_B_deck_size, &confilct_count, max_conflicts);
		if (winner == 0 && simplified_mode == 1)
		{
			both_take_cards(player_A, player_B, player_A_deck_size, player_B_deck_size);
			continue;
		}
		if (winner == 0)
		{
			pA = 0;
			pB = 0;
		}
		while (winner == 0 && confilct_count <= max_conflicts && pA < eA && pB < eB)
		{
			if (pA + 2 > eA || pB + 2 > eB)
			{
				printf("%d %d %d", 1, player_A_deck_size, player_B_deck_size);
				return;
			}
			pA+=2;
			pB+=2;
			winner = who_wins(player_A, player_B, player_A_deck_size, player_B_deck_size, &confilct_count, max_conflicts);
		}
	
		switch (winner)
		{
			case 0:
				both_take_cards(player_A, player_B, player_A_deck_size, player_B_deck_size);
				if (confilct_count > max_conflicts)
				{
					printf("%d %d %d", 0, player_A_deck_size, player_B_deck_size);
					return;
				}
				else
				{
					printf("%d %d %d", 1, player_A_deck_size, player_B_deck_size);
					return;
				}
			case 1:
				one_takes_cards(player_A, &player_A_deck_size, player_B, &player_B_deck_size, 0);
				break;
			case 2:
				one_takes_cards(player_B, &player_B_deck_size, player_A, &player_A_deck_size, 1);
				break;
			default:
				break;
		}
	}
	if (confilct_count >= max_conflicts && (player_A_deck_size > 0 || player_B_deck_size > 0))
	{
		printf("%d %d %d\n", 0, player_A_deck_size, player_B_deck_size);
		return;
	}
	if (winner == 1)
	{
		printf("%d %d", winner + 1, confilct_count);
		return;
	}
	else if (winner == 2)
	{
		printf("%d\n", winner + 1);
		print_arr(player_B, player_B_deck_size);
		return;
	}
}

int main(void) {
	int player_A[NUMBER_OF_CARDS], player_B[NUMBER_OF_CARDS];
	int deck[NUMBER_OF_CARDS];
	int max_conflicts;
	int simplified_mode;
	int seed;
	scanf("%d", &seed);
	scanf("%d", &simplified_mode);
	scanf("%d", &max_conflicts);
	for(int i = 0; i < NUMBER_OF_CARDS; i++) deck[i] = i;
	srand((unsigned) seed);
	shuffle(deck, NUMBER_OF_CARDS);
	for(int i = 0; i < NUMBER_OF_CARDS / 2; i++) {
		player_A[i] = deck[i];
		player_B[i] = deck[i + NUMBER_OF_CARDS / 2];
	}
	game(NUMBER_OF_CARDS, player_A, player_B, max_conflicts, simplified_mode);
	return 0;
}

