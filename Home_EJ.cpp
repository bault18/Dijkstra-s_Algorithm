#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <set>

using std::cin;
using std::cout;
using std::endl;

int goal_state = 13;

struct node {
	node() {};
	node(int s, double c, std::list<int> p)
	{
		state = s;
		cost = c;
		path = p;
	}

	int state;
	double cost;
	std::list<int> path;
};

bool operator<(const node& a, const node& b)
{
	if (a.cost < b.cost)
		return false;
	if (a.cost > b.cost)
		return true;
	if (a.cost == b.cost)
	{
		if (a.path.size() > b.path.size())
			return false;
		if (a.path.size() < b.path.size())
			return true;
	}
	return (a.state < b.state);
}

bool isGoalState(int curr_state)
{
	return curr_state == goal_state;
}

std::vector<int> getChildren(int parent, std::vector<std::vector<double> > matrix)
{
	std::vector<int> children;
	for (int i = 0; i < matrix.size(); i++)
	{
		if (matrix[parent][i] != 0)
			children.push_back(i);
	}
	return children;
}

int main()
{
	//Import map into matrix
	int nnode, edge;
	cin >> nnode >> edge;
	std::vector<std::vector<double> > matrix;
	for (int i = 0; i < nnode; i++)
	{
		std::vector<double> temp;
		for (int j = 0; j < nnode; j++)
			temp.push_back(0);

		matrix.push_back(temp);
	}

	int from, to;
	double dist;
	for (int i = 0; i < edge; i++)
	{
		cin >> from >> to >> dist;
		matrix[from][to] = dist;
		matrix[to][from] = dist;
	}

	//Begin algorithm
	std::priority_queue<node> paths;
	std::set<int> visited_nodes;

	//initial state
	node initial(0, 0, std::list<int>{ 0 });
	while (true)
	{
		if (paths.empty()) {
			cout << "Failed" << endl;
			break;
		}

		node current = paths.top();
		paths.pop();

		if (isGoalState(current.state)) {
			cout << "The route is: ";
			for (std::list<int>::iterator it = current.path.begin(); it != current.path.end(); it++)
				cout << *it << " ";
			cout << endl;
			break;
		}

		if (visited_nodes.find(current.state) != visited_nodes.end()) {
			visited_nodes.insert(current.state);

			std::vector<int> children = getChildren(current.state, matrix);
			for (int i = 0; i < children.size(); i++) {
				node child;
				child.state = children[i];

				child.path = current.path;
				child.path.push_back(child.state);

				child.cost = current.cost + matrix[current.state][children[i]];

				paths.push(child);
			}
		}
	}
}
