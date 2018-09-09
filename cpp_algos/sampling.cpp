#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
using namespace std;

class Sample {
public:
	Sample(int state, int action, int reward, int next_state) {
		this->state = state;
		this->action = action;
		this->reward = reward;
		this->next_state = next_state;
	}

	int state;
	int action;
	int reward;
	int next_state;
};

int find_index_max_elem(const vector<int>& current_Q_vector) {
	int max = -1;
	int max_ind = -1;
	for (int i = 0; i < current_Q_vector.size(); ++i) {
		if (current_Q_vector[i] > max) {
			max = current_Q_vector[i];
			max_ind = i;
		}
	}
	return max_ind;
}

int main() {
	ifstream file("large.csv");
	int state;
	int action; 
	int reward;
	int next_state;
	vector<Sample> total_samp_vector;
	int i = 0;
	while (file)
	{
		if (i == 0) {
			string s;
			if (!getline(file, s)) break;

			cout << s << endl;
			i += 1;
			continue;
		}
		
		string s;
		if (!getline(file, s)) break;
		istringstream tokenStream(s);

		vector<int> list_values(4);
		int ind = 0;
		int num;
		while (tokenStream >> num) {
			list_values[ind] = num;
			ind += 1;
			if (tokenStream.peek() == ',')
				tokenStream.ignore();
		}

		auto newSamp = Sample(list_values[0], list_values[1], list_values[2], list_values[3]);
		total_samp_vector.push_back(newSamp);
	}
	cout << total_samp_vector[10].action << endl;
	cout << total_samp_vector.size() << endl;

	int num_states = 10101010;
	int num_acts = 125;

	vector<int> state_space(num_states);
	for (int i = 1; i < num_states + 1; ++i) {
		state_space[i - 1] = i;
	}
	vector<int> action_space(num_acts);
	for (int i = 1; i < num_acts + 1; ++i) {
		action_space[i - 1] = i;
	}
	map <tuple<int, int>, double> Q_dict;

	for (size_t i = 1; i < num_states + 1; ++i) {
		for (int j = 1; j < num_acts + 1; ++j) {
			auto key = make_tuple(state_space[i - 1], action_space[j - 1]);
			Q_dict[key] = 0;
		}
	}

	double alpha = 0.001;
	double gamma = 0.95;
	for (size_t i = 0; i < total_samp_vector.size() - 1; ++i) {
		auto samp = total_samp_vector[i];
		int s_t = samp.state;
		int a_t = samp.action;
		int r_t = samp.reward;

		auto next_sample = total_samp_vector[i + 1];
		int s_t_next = next_sample.state;
		int a_t_next = next_sample.action;

		auto key = make_tuple(s_t, a_t);
		auto key_next = make_tuple(s_t_next, a_t_next);
		Q_dict[key] += alpha * (r_t + gamma * Q_dict[key_next] - Q_dict[key]);
	}

	vector<int> policy_vector(num_states);
	for (size_t i = 0; i < state_space.size(); ++i) {
		int state = state_space[i];

		vector<int> current_Q_vector;
		vector<int> possible_actions;
		for (int j = 0; j < action_space.size(); ++j) {
			int curr_action = action_space[j];
			auto key = make_tuple(state, curr_action);
			current_Q_vector.push_back(Q_dict[key]);
			possible_actions.push_back(curr_action);
		}

		int index = find_index_max_elem(current_Q_vector);
		policy_vector[i] = possible_actions[index];
	}

	ofstream myfile;
	myfile.open("large.policy");
	for (size_t i = 0; i < policy_vector.size(); ++i) {
		myfile << policy_vector[i] << endl;
	}
	myfile.close();

	cout << "done" << endl;
	cin.ignore();
	cin.ignore();
	return 0;
}