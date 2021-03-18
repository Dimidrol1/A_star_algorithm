#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <queue>
#include <tuple>
#include <stack>
#include <functional>

typedef std::tuple<int, int, int> Tuple;
typedef std::pair<int, int> Pair;
typedef  bool(*func_p)(const Tuple&, const Tuple&);

struct Node
{
	Pair prevNode;
	int f,g,h;
	bool cheked;
	Node() :f(-1), g(-1), h(-1), cheked(false)
	{
	}
};

int manhattan_distance(const Pair &p, const Pair &pf);
void a_star(std::string pathfile);
void build_path(const Pair &dim ,const Pair &start, const Pair &finish, Node **map, char **maze);
bool compare(const Tuple &t1, const Tuple &t2);
bool valid_node(const Pair &dim, const Pair &curr, char** maze);


int main()
{
	std::string pathfile = "maze.txt";

	a_star(pathfile);

	std::system("pause");
	return 0;
}

void a_star(std::string pathfile)
{
	char **maze;
	Node **map;

	std::string s;
	Pair start;
	Pair finish;
	Pair dimension;
	std::fstream Fread(pathfile);
	if (!Fread.is_open())
	{
		std::cout << "file opening error";
		return;
	}
	else
	{

		Fread >> dimension.first;
		Fread >> dimension.second;
		Fread >> start.first;
		start.first--;
		Fread >> start.second;
		start.second--;
		Fread >> finish.first;
		finish.first--;
		Fread >> finish.second;
		finish.second--;

		maze = new char*[dimension.first];
		map = new Node*[dimension.first];
		for (int i = 0; i < dimension.first; i++)
		{
			map[i] = new Node[dimension.second];
			maze[i] = new char[dimension.second];
		}

		for (int i = 0; i < dimension.first; i++)
		{
			for (int j = 0; j < dimension.second; j++)
			{
				Fread >> maze[i][j];
			}
		}
	}


	Fread.close();

	func_p myCompare = compare;
	std::priority_queue<Tuple, std::vector<Tuple>, std::function<bool(Tuple, Tuple)>> openlist(std::ref(myCompare));

	int i = start.first, j = start.second;
	int newf, newh, newg;

	map[i][j].prevNode = { i, j };
	map[i][j].f = 0;
	map[i][j].g = 0;
	map[i][j].h = 0;
	openlist.emplace(i, j, 0);

	Pair neigbours;


	if (valid_node(dimension, start, maze) && valid_node(dimension, finish, maze))
	{
		while (!openlist.empty())
		{
			 Tuple curr = openlist.top();

			openlist.pop();
			i = std::get<0>(curr);
			j = std::get<1>(curr);
			
			if (i == finish.first && j == finish.second)
			{
				build_path(dimension,start, finish, map, maze);

				for (int i = 0; i < dimension.first; i++)
				{
					delete[] map[i];
					delete[] maze[i];
				}

				delete[] map;
				delete[] maze;
				return;
			}

			map[i][j].cheked = true;

			neigbours.first = i - 1;
			neigbours.second = j;

			if (valid_node(dimension, neigbours, maze) &&
				map[neigbours.first][neigbours.second].cheked == false)
			{
				newh = manhattan_distance(neigbours, finish);
				newg = map[i][j].g + 1;
				newf = newg + newh;

				if (map[neigbours.first][neigbours.second].f == -1
					|| map[neigbours.first][neigbours.second].f > newf) {

					openlist.emplace(neigbours.first, neigbours.second, newf);
					map[neigbours.first][neigbours.second].g = newg;
					map[neigbours.first][neigbours.second].h = newh;
					map[neigbours.first][neigbours.second].f = newf;
					map[neigbours.first][neigbours.second].prevNode = { i,j };
					
				}
			}

			neigbours.first += 2;
			if (valid_node(dimension, neigbours, maze) &&
				map[neigbours.first][neigbours.second].cheked == false)
			{
				newh = manhattan_distance(neigbours, finish);
				newg = map[i][j].g + 1;
				newf = newg + newh;

				if (map[neigbours.first][neigbours.second].f == -1
					|| map[neigbours.first][neigbours.second].f > newf) {

					openlist.emplace(neigbours.first, neigbours.second, newf);
					map[neigbours.first][neigbours.second].g = newg;
					map[neigbours.first][neigbours.second].h = newh;
					map[neigbours.first][neigbours.second].f = newf;
					map[neigbours.first][neigbours.second].prevNode = { i,j };
				}
			}

			neigbours.first = i;
			neigbours.second = j - 1;

			if (valid_node(dimension, neigbours, maze) &&
				map[neigbours.first][neigbours.second].cheked == false)
			{
				newh = manhattan_distance(neigbours, finish);
				newg = map[i][j].g + 1;
				newf = newg + newh;

				if (map[neigbours.first][neigbours.second].f == -1
					|| map[neigbours.first][neigbours.second].f > newf) {

					openlist.emplace(neigbours.first, neigbours.second, newf);
					map[neigbours.first][neigbours.second].g = newg;
					map[neigbours.first][neigbours.second].h = newh;
					map[neigbours.first][neigbours.second].f = newf;
					map[neigbours.first][neigbours.second].prevNode = { i,j };
				}
			}

			neigbours.second += 2;
			if (valid_node(dimension, neigbours, maze) &&
				map[neigbours.first][neigbours.second].cheked == false)
			{
				newh = manhattan_distance(neigbours, finish);
				newg = map[i][j].g + 1;
				newf = newg + newh;

				if (map[neigbours.first][neigbours.second].f == -1
					|| map[neigbours.first][neigbours.second].f > newf) {

					openlist.emplace(neigbours.first, neigbours.second, newf);
					map[neigbours.first][neigbours.second].g = newg;
					map[neigbours.first][neigbours.second].h = newh;
					map[neigbours.first][neigbours.second].f = newf;
					map[neigbours.first][neigbours.second].prevNode = { i,j };
				}
			}
		}
		std::cout << "there is no path" << std::endl;
	}
	else
	{
		std::cout << "start or end point not valid" << std::endl;
	}
	

	for (int i = 0; i < dimension.first; i++)
	{
		delete[] map[i];
		delete[] maze[i];
	}

	delete[] map;
	delete[] maze;

}

void build_path(const Pair &dim,const Pair &start, const Pair &finish, Node **map, char **maze)
{
	int i = finish.first;
	int j = finish.second;
	std::stack<char> s;
	s.push('F');
	maze[start.first][start.second] = 'S';
	maze[finish.first][finish.second] = 'F';

	while (map[i][j].prevNode != start)
	{

		auto tempPrev = map[i][j].prevNode;

		if (i > tempPrev.first)
		{
			maze[tempPrev.first][tempPrev.second] = 'D';
			s.push('D');
		}
		else if (i < tempPrev.first)
		{ 
			maze[tempPrev.first][tempPrev.second] = 'U';
			s.push('U');
		}

		if (j < tempPrev.second)
		{ 
			maze[tempPrev.first][tempPrev.second] = 'L';
			s.push('L');
		}
		else if (j > tempPrev.second)
		{ 
			maze[tempPrev.first][tempPrev.second] = 'R';
			s.push('R');
		}
		i = tempPrev.first;
		j = tempPrev.second;
	}
	s.push('S');
	std::cout << map[finish.first][finish.second].g << " steps" << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < dim.first; i++)
	{
		for (int j = 0; j < dim.second; j++)
		{
			std::cout << maze[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	while (!s.empty())
	{
		std::cout << s.top()<<" ";
		s.pop();
	}
	std::cout <<std::endl;
}


int manhattan_distance(const Pair &p, const Pair &pf)
{
	return abs(p.first - pf.first) + abs(p.second - pf.second);
}

bool compare(const Tuple &t1, const Tuple &t2)
{
	int a, b;
	a = std::get<2>(t1);
	b = std::get<2>(t2);
	return a > b;
}

bool valid_node(const Pair &dim, const Pair &curr, char** maze)
{
	if (curr.first >= 0 && curr.first < dim.first && curr.second >= 0 && curr.second < dim.second)
	{
		if (maze[curr.first][curr.second] != '1')
			return true;
	}
	return false;
}