```PYTHON

```

```C++
# include<string>
#include<iostream>
#include<cstdio>
#include<iomanip>
using namespace std;

struct ArrayBoard
{
	bool left_array = false;
	bool diagonal_array = false;
	bool up_array = false;
};

class GobalAlignment {
public:
	int best_alignment_score;
	int s_match, s_ts, s_tv, s_indel;// s_ts = AG, CT
									 // s_tv = AC, CG, GT, AT
	string str_s, str_r;
	int len_s, len_r;

	ArrayBoard** arrayBoard;
	int** scoreBoard;

public:
	void initialize() {
		/*cin >> s_match;
		cin >> s_ts;
		cin >> s_tv;
		cin >> s_indel;
		cin >> str_r;
		cin >> str_s;*/
		int i;
		best_alignment_score = 0;
		s_match = 2;				//initialize
		s_ts = -1;
		s_tv = -1;
		s_indel = -2;
		str_r = "CTAGA";
		str_s = "ACAGGA";
		len_r = str_r.length();
		len_s = str_s.length();

		arrayBoard = new ArrayBoard * [len_r + 1];
		for (i = 0; i < len_r + 1; i++) {
			arrayBoard[i] = new ArrayBoard[len_s + 1];
		}

		scoreBoard = new int* [len_r + 1];
		for (i = 0; i < len_r + 1; i++) {
			scoreBoard[i] = new int[len_s + 1];
			memset(scoreBoard[i], 0, sizeof(int) * (len_s));
		}


		//initialize end
	}

	int checkMatch(int r_entry, int s_entry) {                           //scoreBoard[r][s]
																	   // s_ts = AG, CT
		int score = 0;															// s_tv = AC, CG, GT, AT

		if (str_r[r_entry] == str_s[s_entry]) {
			score = s_match;
		}
		else if ((str_r[r_entry] == 'A' && str_s[s_entry] == 'G') || (str_r[r_entry] == 'G' && str_s[s_entry] == 'A')
			|| (str_r[r_entry] == 'C' && str_s[s_entry] == 'T') || (str_r[r_entry] == 'T' && str_s[s_entry] == 'C')) {

			score = s_ts;
		}
		else {
			score = s_tv;
		}

		return score;
	}

	int maxScore(int s_diagonal, int s_horizontal, int s_vertical) {
		int score = s_diagonal;
		if (score < s_horizontal)
		{
			score = s_horizontal;
		}
		if (score < s_vertical)
		{
			score = s_vertical;
		}
		return score;
	}
	void optimal() {
		int r_entry, s_entry;
		int s_diagonal, s_horizontal, s_vertical;
		for (r_entry = len_r - 1; r_entry >= 0; r_entry--) {
			for (s_entry = len_s - 1; s_entry >= 0; s_entry--) {
				if ((r_entry == len_r - 1) && (s_entry == len_s - 1)) {  //case: right corner
					s_diagonal = checkMatch(r_entry, s_entry);
					s_horizontal = s_indel * (s_entry - len_s + 1);
					s_vertical = s_indel * (r_entry - len_r + 1);
					scoreBoard[r_entry][s_entry] = maxScore(s_diagonal, s_horizontal, s_vertical);

				}
				else if (r_entry == len_r - 1) {                          //case: last row(botton)
					s_diagonal = checkMatch(r_entry, s_entry) + s_indel * (len_s - s_entry-1);
					s_horizontal = scoreBoard[r_entry][s_entry + 1] + s_indel;
					s_vertical = s_indel * (len_s - s_entry+1);
					scoreBoard[r_entry][s_entry] = maxScore(s_diagonal, s_horizontal, s_vertical);
					cout << s_entry << " : " << s_diagonal << " " << s_horizontal << " " << s_vertical << endl;
				}
				else if (s_entry == len_s - 1) {                          // case: last column(right)
					
					s_diagonal = checkMatch(r_entry, s_entry) + s_indel * (len_r - r_entry - 1);
					s_horizontal = s_indel * (len_r - r_entry + 1);
					s_vertical = scoreBoard[r_entry + 1][s_entry] + s_indel; 
					scoreBoard[r_entry][s_entry] = maxScore(s_diagonal, s_horizontal, s_vertical);
					cout << r_entry << " : " << s_diagonal << " " << s_horizontal << " " << s_vertical << endl;
				}
				else {
					s_diagonal = checkMatch(r_entry, s_entry) + scoreBoard[r_entry + 1][s_entry+1];
					s_horizontal = scoreBoard[r_entry][s_entry + 1] + s_indel;
					s_vertical = scoreBoard[r_entry + 1][s_entry] + s_indel;
					scoreBoard[r_entry][s_entry] = maxScore(s_diagonal, s_horizontal, s_vertical);

				}
				//scoreBoard[r_entry][s_entry] = checkMatch(r_entry, s_entry);
			}
		}
	}



	void traceBack() {
	}

	void print_scoreBoard() {
		int i;
		int j;


		for (i = 0; i < len_s; i++) {
			cout << setw(3);
			cout << str_s[i];
		}
		cout << endl;
		for (i = 0; i < len_r; i++) {
			cout << str_r[i];
			for (j = 0; j < len_s; j++) {
				cout << setw(3);
				cout << scoreBoard[i][j];
			}
			cout << endl << endl;
		}
		cout << endl;

		if (scoreBoard[0][0]) {
			cout << "valuw" << endl;
		}
		else {
			cout << "NULL" << endl;
		}
	}

};

int main() {
	GobalAlignment gobalAlignment;
	gobalAlignment.initialize();
	gobalAlignment.optimal();
	gobalAlignment.print_scoreBoard();


	return 0;
}
```

