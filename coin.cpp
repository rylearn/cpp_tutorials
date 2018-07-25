#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
using namespace std;

enum coin_value {tails = 0, heads};

class Coin {
public:
	int value;
	double proba;

	Coin() {
		srand(time(NULL));
		if ((double) rand() / RAND_MAX > 0.5) {
			this->value = static_cast<int>(heads);
		} else {
			this->value = static_cast<int>(tails);
		}
	}

	Coin(coin_value curr_value) {
		this->value = static_cast<int>(curr_value);
	}

	Coin(double proba) {
		this->proba = proba;
		srand(time(NULL));
		if ((double) rand() / RAND_MAX > proba) {
			this->value = static_cast<int>(heads);
		} else {
			this->value = static_cast<int>(tails);
		}
	}
};

struct Coins {
	vector<Coin> vec_coins;
	double proba;
	int num_heads;
	int num_tails;

	Coins(int size, int num_heads) {
		this->proba = (double) num_heads / size;
		this->num_heads = num_heads;
		this->num_tails = size - num_heads;
		for (int i = 0; i < num_heads; ++i)
			vec_coins.push_back(Coin(heads));
		for (int i = num_heads; i < size; ++i)
			vec_coins.push_back(Coin(tails));
	}

	int size() {
		return vec_coins.size();
	}

	bool contains(vector<int> index_vec, int index) {
		for (const int& ind : index_vec)
			if (ind == index) {
				return true;
			}
		return false;
	}

	void split(vector<Coin>& pileA, vector<Coin>& pileB) {
		int expected_tails = 0;
		int i = 0;
		vector<int> used_indices;
		while (expected_tails < (num_tails / 2)) {
			if (((double) rand() / RAND_MAX) > proba) {
				pileA.push_back(vec_coins[i]);
				expected_tails += 1;
				used_indices.push_back(i);
			}
			i += 1;
			if (i >= this->size()) {
				break;
			}
		}
		for (int j = 0; j < vec_coins.size(); ++j) {
			if (!contains(used_indices, j)) {
				pileA.push_back(vec_coins[j]);
				used_indices.push_back(j);
			}
			if (pileA.size() == (this->size() / 2)) {
				break;
			}
		}
		for (int j = 0; j < vec_coins.size(); ++j) {
			if (!contains(used_indices, j)) {
				pileB.push_back(vec_coins[j]);
				used_indices.push_back(j);
			}
			if (pileB.size() == (this->size() / 2)) {
				break;
			}
		}
	}

};

int main() {
	Coins coin_pile = Coins(100, 90);
	vector<Coin> pile_a;
	vector<Coin> pile_b;
	coin_pile.split(pile_a, pile_b);

	int tails_cnt = 0;
	for (Coin x : pile_a) {
		cout << x.value << ' ';
		if (x.value == 0) {
			tails_cnt++;
		}
	}
	cout << endl;
	cout << tails_cnt << endl;

	tails_cnt = 0;
	for (Coin x : pile_b) {
		cout << x.value << ' ';
		if (x.value == 0) {
			tails_cnt++;
		}
	}
	cout << endl;
	cout << tails_cnt << endl;

	// vector<Coin> one_pile;
	// vector<Coin> another_pile;
	return 0;
}

