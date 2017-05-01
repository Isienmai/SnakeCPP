#ifndef INCLUDED_PATH
#define INCLUDED_PATH

//The entirety of path.h and path.cpp are an implementation of a linked list of coordinates.

struct Coord
{
	int x, y;
	Coord() : x(0), y(0) {}
	Coord(int _x, int _y) : x(_x), y(_y) {}
	Coord operator+ (const Coord &other) const;
	Coord operator- (const Coord &other) const;
	bool operator== (const Coord &other) const;
	bool operator!= (const Coord &other) const;
};

struct PathNode
{
	Coord point;
	PathNode *next;
	PathNode() : next(nullptr), point(0, 0) {}
	PathNode(Coord content, PathNode *top) : point(content), next(top) {}
};

class Path
{
	PathNode* start;

public:
	Path() : start(nullptr) {}
	~Path();

	void AddLast(Coord toAdd);
	void AddFirst(Coord toAdd);
	//The function returns the last member of the list and removes said member from the list.
	Coord CutLast();
	void RemoveFirst();
	bool IsEmpty();
	bool ContainsDuplicate();

	PathNode* Start(){ return start; }
};

#endif

