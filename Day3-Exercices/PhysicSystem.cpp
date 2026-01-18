#include "PhysicSystem.h"
#include "Engine.h"
#include "RigidBody.h"
#include "ACollider.h"
#include "TransformComponent.h"
#include "ICollisionEvent.h"

const float PhysicSystem::worldScale = 128.f;

PhysicSystem::PhysicSystem() {
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = {0.f, 9.8f};
	gravity = { 0.f, 9.8f };
	b2WorldId worldId = b2CreateWorld(&worldDef);
	world = worldId;
}

void PhysicSystem::update(float _deltaTime) {
	SceneManager* sm = SceneManager::instance();
	
	for (Entity* entity : *sm->getCurrentScene()->getEntities()) {
		if (RigidBody* rb = entity->getComponent<RigidBody>()) {
			TransformComponent* transformComp = entity->getComponent<TransformComponent>();
			b2Body_SetTransform(rb->getBody(), { transformComp->getPosition().x / worldScale, transformComp->getPosition().y / worldScale }, b2MakeRot(transformComp->getRotation().asRadians()));
		}
	}

	b2World_Step(world, _deltaTime, 4);

	for (Entity* entity : *sm->getCurrentScene()->getEntities()) {
		if (RigidBody* rb = entity->getComponent<RigidBody>()) {
			TransformComponent* transformComp = entity->getComponent<TransformComponent>();
			b2Vec2 position = b2Body_GetPosition(rb->getBody());
			b2Rot rotation = b2Body_GetRotation(rb->getBody());

			transformComp->setPosition({position.x * worldScale, position.y * worldScale });
			transformComp->setRotation(sf::radians(b2Rot_GetAngle(rotation)));
		}
	}

	b2ContactEvents contactEvents = b2World_GetContactEvents(world);

	for (int i = 0; i < contactEvents.beginCount; i++) {
		auto event = contactEvents.beginEvents[i];
		ACollider* colliderA = nullptr;
		ACollider* colliderB = nullptr;
		for (Entity* entity : *sm->getCurrentScene()->getEntities()) {
			if (ACollider* c = entity->getComponent<ACollider>()) {
				if (B2_ID_EQUALS(c->shapeId, event.shapeIdA)) {
					colliderA = c;
				}
				if (B2_ID_EQUALS(c->shapeId, event.shapeIdB)) {
					colliderB = c;
				}
			}
		}
		if (colliderA != nullptr && colliderB != nullptr) {
			if (ICollisionEvent* t = colliderA->getParent()->getComponent<ICollisionEvent>()) {
				t->beginCollision(colliderA, colliderB);
			}
			if (ICollisionEvent* t = colliderB->getParent()->getComponent<ICollisionEvent>()) {
				t->beginCollision(colliderB, colliderA);
			}
		}
	}

	for (int i = 0; i < contactEvents.endCount; i++) {
		auto event = contactEvents.endEvents[i];
		ACollider* colliderA = nullptr;
		ACollider* colliderB = nullptr;
		for (Entity* entity : *sm->getCurrentScene()->getEntities()) {
			if (ACollider* c = entity->getComponent<ACollider>()) {
				if (B2_ID_EQUALS(c->shapeId, event.shapeIdA)) {
					colliderA = c;
				}
				if (B2_ID_EQUALS(c->shapeId, event.shapeIdB)) {
					colliderB = c;
				}
			}
		}
		if (colliderA != nullptr && colliderB != nullptr) {
			if (ICollisionEvent* t = colliderA->getParent()->getComponent<ICollisionEvent>()) {
				t->endCollision(colliderA, colliderB);
			}
			if (ICollisionEvent* t = colliderB->getParent()->getComponent<ICollisionEvent>()) {
				t->endCollision(colliderB, colliderA);
			}
		}
	}
}

b2WorldId* PhysicSystem::getWorld() {
	return &world;
}