```PYTHON
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

	//ArrayBoard** arrayBoard;
	int** scoreBoard;

public:
	void initialize() {
		/*cin >> s_match;
		cin >> s_ts;
		cin >> s_tv;
		cin >> s_indel;
		cin >> str_r;
		cin >> str_s;*/
		
		int i, j;
		best_alignment_score = 0;

		s_match = 8;				//initialize
		s_ts = -1;
		s_tv = -4;
		s_indel = -4;
		str_r = "GATGA";
		str_s = "GATTG";

		len_r = str_r.length();
		len_s = str_s.length();

		//arrayBoard = new ArrayBoard * [len_r + 1];
		for (i = 0; i < len_r + 1; i++) {
			//arrayBoard[i] = new ArrayBoard[len_s + 1];
		}

		scoreBoard = new int* [len_r + 1];
		for (i = 0; i < len_r + 1; i++) {
			scoreBoard[i] = new int[len_s + 1];
			
		}
		for (i = 0; i < len_r+1; i++) {
			for (j = 0; j < len_s+1; j++) {
				//arrayBoard[i][j].diagonal_array = false;
				//arrayBoard[i][j].left_array = false;
				//arrayBoard[i][j].up_array = false;
				if (i == len_r && j == len_s) {
					scoreBoard[i][j] = 0;
					//arrayBoard[i][j].diagonal_array = false;
					//arrayBoard[i][j].left_array = false;
					//arrayBoard[i][j].up_array = false;
				}
				else if (i == len_r) {
					scoreBoard[i][j] = s_indel*(len_s - j) ;
					//arrayBoard[i][j].left_array = true;
				}
				else if (j == len_s) {
					scoreBoard[i][j] = s_indel * (len_r - i);
					//arrayBoard[i][j].up_array = true;
				}
				else {
					scoreBoard[i][j] = 0;
				}
				
				
			}
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

	void checkSameScore(int r_entry, int s_entry, int s_diagonal, int s_horizontal, int s_vertical) {
		int score = scoreBoard[r_entry][s_entry];
		if (score == s_diagonal) {
			//arrayBoard[r_entry][s_entry].diagonal_array = true;
		}
		if (score == s_horizontal) {
			//arrayBoard[r_entry][s_entry].left_array = true;
		}
		if (score == s_vertical) {
			//arrayBoard[r_entry][s_entry].up_array = true;
		}

	}

	void optimal() {
		int r_entry, s_entry;
		int s_diagonal, s_horizontal, s_vertical;
		for (r_entry = len_r - 1; r_entry >= 0; r_entry--) {
			for (s_entry = len_s - 1; s_entry >= 0; s_entry--) {
				
				s_diagonal = checkMatch(r_entry, s_entry) + scoreBoard[r_entry + 1][s_entry + 1];
				s_horizontal = scoreBoard[r_entry][s_entry + 1] + s_indel;
				s_vertical = scoreBoard[r_entry + 1][s_entry] + s_indel;
				scoreBoard[r_entry][s_entry] = maxScore(s_diagonal, s_horizontal, s_vertical);
				//checkSameScore( r_entry,  s_entry,  s_diagonal,  s_horizontal,  s_vertical);
				
			}
		}
	}


	/*void traceBack(string str_r_final, string str_s_final, int r_entry, int s_entry) {
		string print_str_r = "";
		string print_str_s = "";

		if (!arrayBoard[r_entry][s_entry].diagonal_array && !arrayBoard[r_entry][s_entry].left_array && !arrayBoard[r_entry][s_entry].up_array) {
			cout << str_r_final << endl;
			cout << str_s_final <<endl<<endl;
			
			

			return;
		}
		if (arrayBoard[r_entry][s_entry].up_array) {

			print_str_r = str_r_final + str_r[r_entry];
			print_str_s = str_s_final + "_";


			traceBack(print_str_r, print_str_s, r_entry + 1, s_entry);
		}
		
		if (arrayBoard[r_entry][s_entry].diagonal_array) {

			print_str_r = str_r_final + str_r[r_entry];
			print_str_s = str_s_final + str_s[s_entry];


			traceBack(print_str_r, print_str_s, r_entry + 1, s_entry + 1);
		}

		if (arrayBoard[r_entry][s_entry].left_array) {

			print_str_r = str_r_final + "_";
			print_str_s = str_s_final + str_s[s_entry];


			traceBack(print_str_r, print_str_s, r_entry, s_entry + 1);
		}
		
		

		

		
	}*/

	void printTraceBack(string test, string test2) {
		
		cout << scoreBoard[0][0] << endl<<endl;
		//traceBack(test, test2, 0, 0);
	}

	void print_scoreBoard() {
		int i;
		int j;


		for (i = 0; i < len_s; i++) {
			cout << setw(3);
			cout << str_s[i];
		}
		cout << endl;
		for (i = 0; i < len_r +1; i++) {
			cout << str_r[i];
			for (j = 0; j < len_s+1; j++) {
				cout << setw(3);
				cout << scoreBoard[i][j];
			}
			cout << endl << endl;
		}
		cout << endl;


	}

};

int main() {
	GobalAlignment gobalAlignment;
	gobalAlignment.initialize();
	gobalAlignment.optimal();
	//gobalAlignment.print_scoreBoard();
	gobalAlignment.printTraceBack("", "");


	return 0;
}
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
		cin >> s_match;
		cin >> s_ts;
		cin >> s_tv;
		cin >> s_indel;
		cin >> str_r;
		cin >> str_s;
		int i, j;
		best_alignment_score = 0;

		//s_match = 8;				//initialize
		//s_ts = -1;
		//s_tv = -4;
		//s_indel = -4;
		//str_r = "GATGA";
		//str_s = "GATTG";

		len_r = str_r.length();
		len_s = str_s.length();

		arrayBoard = new ArrayBoard * [len_r + 1];
		for (i = 0; i < len_r + 1; i++) {
			arrayBoard[i] = new ArrayBoard[len_s + 1];
		}

		scoreBoard = new int* [len_r + 1];
		for (i = 0; i < len_r + 1; i++) {
			scoreBoard[i] = new int[len_s + 1];
			
		}
		for (i = 0; i < len_r+1; i++) {
			for (j = 0; j < len_s+1; j++) {
				arrayBoard[i][j].diagonal_array = false;
				arrayBoard[i][j].left_array = false;
				arrayBoard[i][j].up_array = false;
				if (i == len_r && j == len_s) {
					scoreBoard[i][j] = 0;
					arrayBoard[i][j].diagonal_array = false;
					arrayBoard[i][j].left_array = false;
					arrayBoard[i][j].up_array = false;
				}
				else if (i == len_r) {
					scoreBoard[i][j] = s_indel*(len_s - j) ;
					arrayBoard[i][j].left_array = true;
				}
				else if (j == len_s) {
					scoreBoard[i][j] = s_indel * (len_r - i);
					arrayBoard[i][j].up_array = true;
				}
				else {
					scoreBoard[i][j] = 0;
				}
				
				
			}
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

	void checkSameScore(int r_entry, int s_entry, int s_diagonal, int s_horizontal, int s_vertical) {
		int score = scoreBoard[r_entry][s_entry];
		if (score == s_diagonal) {
			arrayBoard[r_entry][s_entry].diagonal_array = true;
		}
		if (score == s_horizontal) {
			arrayBoard[r_entry][s_entry].left_array = true;
		}
		if (score == s_vertical) {
			arrayBoard[r_entry][s_entry].up_array = true;
		}

	}

	void optimal() {
		int r_entry, s_entry;
		int s_diagonal, s_horizontal, s_vertical;
		for (r_entry = len_r - 1; r_entry >= 0; r_entry--) {
			for (s_entry = len_s - 1; s_entry >= 0; s_entry--) {
				
				s_diagonal = checkMatch(r_entry, s_entry) + scoreBoard[r_entry + 1][s_entry + 1];
				s_horizontal = scoreBoard[r_entry][s_entry + 1] + s_indel;
				s_vertical = scoreBoard[r_entry + 1][s_entry] + s_indel;
				scoreBoard[r_entry][s_entry] = maxScore(s_diagonal, s_horizontal, s_vertical);
				checkSameScore( r_entry,  s_entry,  s_diagonal,  s_horizontal,  s_vertical);
				
			}
		}
	}


	void traceBack(string str_r_final, string str_s_final, int r_entry, int s_entry) {
		string print_str_r = "";
		string print_str_s = "";

		if (!arrayBoard[r_entry][s_entry].diagonal_array && !arrayBoard[r_entry][s_entry].left_array && !arrayBoard[r_entry][s_entry].up_array) {
			cout << str_r_final << endl;
			cout << str_s_final <<endl<<endl;
			
			

			return;
		}
		if (arrayBoard[r_entry][s_entry].up_array) {

			print_str_r = str_r_final + str_r[r_entry];
			print_str_s = str_s_final + "_";


			traceBack(print_str_r, print_str_s, r_entry + 1, s_entry);
		}
		
		if (arrayBoard[r_entry][s_entry].diagonal_array) {

			print_str_r = str_r_final + str_r[r_entry];
			print_str_s = str_s_final + str_s[s_entry];


			traceBack(print_str_r, print_str_s, r_entry + 1, s_entry + 1);
		}

		if (arrayBoard[r_entry][s_entry].left_array) {

			print_str_r = str_r_final + "_";
			print_str_s = str_s_final + str_s[s_entry];


			traceBack(print_str_r, print_str_s, r_entry, s_entry + 1);
		}
		
		

		

		
	}

	void printTraceBack(string test, string test2) {
		
		cout << scoreBoard[0][0] << endl<<endl;
		traceBack(test, test2, 0, 0);
	}

	void print_scoreBoard() {
		int i;
		int j;


		for (i = 0; i < len_s; i++) {
			cout << setw(3);
			cout << str_s[i];
		}
		cout << endl;
		for (i = 0; i < len_r +1; i++) {
			cout << str_r[i];
			for (j = 0; j < len_s+1; j++) {
				cout << setw(3);
				cout << scoreBoard[i][j];
			}
			cout << endl << endl;
		}
		cout << endl;


	}

};

int main() {
	GobalAlignment gobalAlignment;
	gobalAlignment.initialize();
	gobalAlignment.optimal();
	//gobalAlignment.print_scoreBoard();
	gobalAlignment.printTraceBack("", "");


	return 0;
}
```

