// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// http://code.google.com/p/yam2d/
//
// Copyright (c) 2013 Mikko Romppainen
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
// FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef WAYPOINT_CONRTOLLER_H_
#define WAYPOINT_CONRTOLLER_H_ 

// Include base class
#include <SpriteComponent.h>

// Forward declaration of class Player
class PlayerController;

// Use yam2d::Component as base class for our player. Use also yam2d::Updatable -interface, for update-method.
class WaypointController : public yam2d::Component, public yam2d::Updatable
{
public:
	/** Constructor of player. 
	 *
	 * @param gameObjectType Game specific game object type. Useful for for example detecting of "real game object type", like Player or Enemy.
	 * @param texture Texture for our game object.
	 */
	WaypointController(yam2d::GameObject* parent, yam2d::GameObject* player);
	virtual ~WaypointController(void);

	// This virtual method is automatically called byt map/layer, when update is called from main.cpp
	virtual void update( float deltaTime );

	/** 
	 * Sets waypoints for this enemy, where this should go. 
	 */
	void setWayoints(const std::vector<yam2d::vec2>& waypoints );

	/**
	 * Returns true, if enemy has reached its final destination.
	 */
	bool hasReachedGoal();

	yam2d::GameObject* getGameObject() { return (yam2d::GameObject*)getOwner(); }
	const yam2d::GameObject* getGameObject() const { return (const yam2d::GameObject*)getOwner(); }
private:
	std::vector<yam2d::vec2> m_waypoints;
	yam2d::GameObject* m_player;

};


#endif