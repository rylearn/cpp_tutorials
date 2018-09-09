
#include <set>
#include <vector>
#include <iostream>
using namespace std;

/* Generate all subsets given a set */
vector<vector<int>> subsets;
void getSubsets(vector<int>& set, int index) {
	if (set.size() == index) {
		vector<int> empty_set;
		subsets.push_back(empty_set);
	}
	else {
		getSubsets(set, index + 1);
		int item = set[index];

		vector<vector<int>> more_subsets;
		for (vector<int> subset : subsets) {
			vector<int> new_subset = subset;
			new_subset.push_back(item);
			more_subsets.push_back(new_subset);
		}
		for (auto subset : more_subsets) {
			subsets.push_back(subset);
		}
	}
}

int main() {
	std::vector<int> v = {1, 2, 3};
	getSubsets(v, 0);
	cout << subsets.size() << endl;
	for (int i = 0; i < subsets.size(); ++i) {
		for (int j = 0; j < subsets[i].size(); ++j) {
			cout << subsets[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}
