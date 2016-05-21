#include "SearchLevel.h"

namespace
{

	// R p[0] G p[1] B p[2]
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

	bool isWhite(unsigned char* p)
	{
		float v = p[0];
		v = v / 255.f;

		if (v == 1)
		{
			return true;
		}
		return false;
	}

	bool isBlack(unsigned char* p)
	{
		float v = p[0];
		v = v / 255.f;
		if (v == 0)
		{
			return true;
		}
		return false;
	}

	bool isGrey(unsigned char* p)
	{
		float v = p[0];
		v = v / 255.f;

		if (v >= 0.4f && v <= 0.6f)
		{
			return true;
		}
		return false;
	}
}

float SearchLevel::GetG(SearchNode* fromNode, const Position &toPos)
{
	// Return euclidean distance between points
	float dX = (float)(toPos.first - fromNode->pos.first);
	float dY = (float)(toPos.second - fromNode->pos.second);
	float result = sqrtf(dX*dX + dY*dY);
	return result;
}

float SearchLevel::GetH(const Position &fromPos, const Position &toPos)
{
	// Return euclidean distance between points (heuristic)
	float dX = (float)(toPos.first - fromPos.first);
	float dY = (float)(toPos.second - fromPos.second);
	return sqrtf(dX*dX + dY*dY);
}
// tänne colliderin tiedot
bool SearchLevel::isWalkable(int posX, int posY)
{
	if (posX < 0 || posY < 0 || posX >= AIlayer->getWidth() || posY >= AIlayer->getHeight())
		return false;

	unsigned char* pixel = AIlayer->getPixel(posX, posY);
	bool isNotWalkable = ::isBlack(pixel);

	return !isNotWalkable;
}

std::vector<Position> SearchLevel::GetAdjacentNodes(int posX, int posY)
{
	std::vector<Position> result;

	if (isWalkable(posX + 1, posY))
		result.push_back(Position(posX + 1, posY));

	if (isWalkable(posX - 1, posY))
		result.push_back(Position(posX - 1, posY));

	if (isWalkable(posX, posY + 1))
		result.push_back(Position(posX, posY + 1));

	if (isWalkable(posX, posY - 1))
		result.push_back(Position(posX, posY - 1));

	return result;
}