#pragma once
#include "ACollider.h"
#include "box2d/box2d.h"

class BoxCollider : public ACollider
{
protected:
	b2Polygon shape;
	b2Vec2 size;

public:

	void setShape(b2BodyId _body) override;
	void setSize(b2Vec2 _size);
};

