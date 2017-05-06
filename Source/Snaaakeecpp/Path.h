#ifndef INCLUDED_PATH
#define INCLUDED_PATH

//path.h and path.cpp are an implementation of a linked list of the Coord struct.

//The coord struct simply stores a 2d coordinate
//It also provides constructors, simple addition/subtraction, and boolean comparison operator definitions
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

//Defines a node of the linked list.
struct PathNode
{
	Coord point;        
	PathNode* next;
        
	PathNode() : point(0, 0), next(nullptr) {}
	PathNode(Coord content, PathNode* top) : point(content), next(top) {}
};

class Path
{
	PathNode* start;

public:
	Path() : start(nullptr) {}
	~Path();

	void AddLast(Coord toAdd);
	void AddFirst(Coord toAdd);
	Coord CutLast();
	void RemoveFirst();
	bool IsEmpty();
	bool ContainsDuplicate();

	PathNode* Start(){ return start; }
};

#endif

