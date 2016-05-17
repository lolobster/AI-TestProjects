// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// War Game for GameAIGameFramework.
//
// Copyright (c) 2016 Mikko Romppainen. All Rights reserved.
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef AI_MAP_LAYER_H_
#define AI_MAP_LAYER_H_

#include <Texture.h>
#include <Layer.h>
#include <stdint.h>

class AIMapLayer
{
private:
	yam2d::Layer* m_layer;
protected:
	AIMapLayer(yam2d::Layer* layer)
		: m_layer(layer)
	{
	}

	virtual ~AIMapLayer()
	{
	}

public:
	virtual void setPixel(int px, int py, float value) = 0;
	virtual void setPixel(int px, int py, uint8_t* pixelValues) = 0;
	virtual uint8_t* getPixel(int px, int py) = 0;
	virtual const uint8_t* getPixel(int px, int py) const = 0;
	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;

	/*uint8_t* getPixelFromPos(const slm::vec2& pos)
	{
		return getPixel((int)(pos.x + 0.5f), (int)(pos.y + 0.5f));
	}*/

	yam2d::Layer* getLayer() const
	{
		return m_layer;
	}

	const uint8_t* getPixelFromPos(const slm::vec2& pos) const
	{
		return getPixel((int)(pos.x + 0.5f), (int)(pos.y + 0.5f));
	}
};



#endif

