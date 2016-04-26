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
#ifndef TEXT_H_
#define TEXT_H_

#include <vector>
#include <string>
#include <GameObject.h>
#include <Ref.h>

namespace yam2d
{
class Sprite;
class SpriteSheet;

/**
 * Class for Text.
 *
 * @ingroup yam2d
 * @author Mikko Romppainen (mikko@kajakbros.com) 
 */
class Text : public Component
{
public:
	enum Pivot
	{
		CENTER_CENTER,
		LEFT_CENTER,
		RIGHT_CENTER,
		CENTER_TOP,
		CENTER_BOTTOM
	};

	Text(GameObject* owner, SpriteSheet* font);

	virtual ~Text() {}

	void setText( const std::string& str );
	void setText( const char* str );
	void setPivot(Pivot newPivot) { m_pivot = newPivot; }

	void getVertexData( std::vector<float>& verts, std::vector<float>& texCoords, std::vector<float>& colors ) const;

	/**
	 *  Sets depth value of this sprite.
	 */
	void setDepth( float depth );

	const std::string& getText() const { return m_text; }
	/**
	 * Sets color of this sprite.
	 */
	void setColor( float r, float g, float b, float a = 1.0f );
	void setOpacity( float a );
	SpriteSheet* getFont() const;
	int getWidth();
	Pivot getPivot();

	GameObject* getGameObject() { return (GameObject*)getOwner(); }
private:
	Ref<SpriteSheet> m_font;
	Ref<Sprite> m_sprite;
	int m_totalWidth;
	Pivot m_pivot;
	std::string m_text;
};


}


#endif

