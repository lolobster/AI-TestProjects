#include "SearchLevel.h"

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

bool SearchLevel::isWalkable(int posX, int posY)
{
	if (posX < 0 || posY < 0 || posX >= inputTexture->getWidth() || posY >= inputTexture->getHeight())
		return false;
	unsigned char* pixel = inputTexture->getPixel(posX, posY);
	bool isNotWalkable = isGreen(pixel);
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