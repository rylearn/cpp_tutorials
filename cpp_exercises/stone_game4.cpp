
// struct Greater_than {
//     bool operator()(int x, int y) {
//         return x > y;
//     }
// };

// struct Lesser_than {
//     bool operator()(int x, int y) {
//         return x < y;
//     }
// };
#include <iostream>
#include <vector>
#include <functional>
using namespace std;


void choose_max(vector<int>& piles, 
    int& start, int& end,
    int &sum, int &other_sum, bool &first_move)
{
	if (first_move) {
		if (start < 0) {
			return;
		}
		if (end > piles.size() - 1) {
			return;
		}
		if (piles[start] > piles[end]) {
	        sum += piles[end];
	        end++;
	    } 
	    else if (piles[start] < piles[end]) {
	        sum += piles[start];
	        start--;
	    }
	    else {
	        while (piles[start] == piles[end]) {
	            sum += piles[start];
	            other_sum += piles[end];
	            start--;
	            end++;
	        }
	        choose_max(piles, start, end, sum, 
	            other_sum, first_move);
	    }
	    return;
	}
    if (start < 0) {
        sum += piles[end];
        end++;
        return;
    }
    if (end > (piles.size() - 1)) {
        sum += piles[start];
        start--;
        return;
    }
    if (piles[start] > piles[end]) {
        sum += piles[start];
        start--;
    } 
    else if (piles[start] < piles[end]) {
        sum += piles[end];
        end++;
    }
    else {
        while (piles[start] == piles[end]) {
            sum += piles[start];
            other_sum += piles[end];
            start--;
            end++;
        }
        choose_max(piles, start, end, sum, 
            other_sum, first_move);
    }
}

bool helper(vector<int>& piles, int& start, int& end, 
	int& alex_sum, int& lee_sum) {

	bool alex_turn = false;
	bool first_move = true;
	while (true) {
        if (alex_turn) {
            choose_max(piles, start, end, alex_sum, 
                lee_sum, first_move);
        }
        else {
            choose_max(piles, start, end, lee_sum, 
                alex_sum, first_move);
        }
        first_move = false;
        alex_turn = !alex_turn;
        if (start < 0 && end > piles.size() - 1) {
            break;
        }
    }
    return alex_sum > lee_sum;
}

bool stoneGame(vector<int>& piles) {
    vector<bool> visited;

    const int half = piles.size() / 2;

    bool victory = false;
    int start = -1;
	int end = 0;
    for (int i = 0; i < piles.size() - 1; ++i) {
    	start += 1;
	    end += 1;

	    int lee_sum = 0;
	    int alex_sum = 0;

	    victory = helper(piles, start, end, alex_sum, lee_sum);
	    if (victory)
	    	break;
    }
    // cout << alex_sum << endl;
    // cout << lee_sum << endl;

    return victory;
}

int main() {
    vector<int> x = {7,7,12,16,41,48,41,48,11,9,34,2,
    	44,30,27,12,11,39,31,8,23,11,47,25,15,
    	23,4,17,11,50,16,50,38,34,48,27,16,24,
    	22,48,50,10,26,27,9,43,13,42,46,24};
    cout << x.size() << endl;
    cout << stoneGame(x) << endl;
    return 0;
}
