#ifndef SEARCHLEVEL_H
#define SEARCHLEVEL_H
#include "Searchnode.h"
#include <vector>
#include "Texture.h"
#include <StreamTexture.h>

namespace
{
	void setPathColor(yam2d::StreamTexture* t, int x, int y)
	{
		t->getPixel(x, y)[0] = 0xff;
		t->getPixel(x, y)[1] = 0x00;
		t->getPixel(x, y)[2] = 0xff;
	}

	bool isRed(unsigned char* p)
	{
		return p[0] > 200;
	}

	bool isGreen(unsigned char* p)
	{
		return p[1] > 200;
	}

	bool isBlue(unsigned char* p)
	{
		return p[2] > 200;
	}
}

class SearchLevel
{
public:
	SearchLevel(yam2d::Texture* input)
		: inputTexture(input){}
	~SearchLevel(){};

	float GetG(SearchNode* fromNode, const Position& toPos);
	float GetH(const Position& fromPos, const Position& toPos);
	bool isWalkable(int x, int y);
	
	std::vector<Position> GetAdjacentNodes(int posX, int posY);

private:
	yam2d::Texture* inputTexture;
};

#endif