#ifndef NODE_H
#define NODE_H

#include <vector>
#include "state.hpp"
#include "point.hpp"

class Node {
	public:
		State state;
		char direction;
		Node *parent;

		bool hasBoxIn(Point);
		bool hasWallIn(Point);
		bool hasGoalIn(Point);
		virtual bool isFreePoint(Point);
		Node* getChild(char, bool);
		//bool identifyDeadBox(Node*, Point);
		bool isBoxStuck(Point, bool);
		bool isBoxStuck(Point);
		//bool identifyDeadBox(Point);
		bool identifyDeadGroup(std::vector<Point>, Point);
		std::vector<Point> getAdjacentBoxGroup(Point);

		Node():direction(' '),parent(NULL){};
		Node(State s, char d, Node* p):state(s), direction(d), parent(p){};
		virtual ~Node(){};

		virtual std::vector<Node*> getNextSteps(std::vector<std::string> map);
		std::vector<Point> getMovableSides(Point box, std::vector<std::string> map);
		std::vector<Node*> findPaths(std::vector<Point> goals, std::vector<std::string> map);
		bool isSearchTarget(std::vector<Point> &goals);

};

int heuristic(State);

struct NodeCompare
{
	bool operator()(const Node* a, const Node* b) const
	{
		return heuristic(a->state) > heuristic(b->state);
	}
};

class BackNode: public Node
{
public:
	BackNode():Node(){};
	BackNode(State s, char d, Node* p):Node(s, d, p){};
	virtual ~BackNode(){};
	bool isFreePoint(Point);
	std::vector<Node*> getNextSteps(std::vector<std::string> map);
};
#endif
