#include "BoxCollider.h"
#include "PhysicSystem.h"

void BoxCollider::setShape(b2BodyId _body) {
	shape = b2MakeBox(size.x / PhysicSystem::worldScale / 2.f, size.y / PhysicSystem::worldScale / 2.f);
	shapeId = b2CreatePolygonShape(_body, &shapeDef, &shape);
}

void BoxCollider::setSize(b2Vec2 _size) {
	size = _size;
}