#include "ContactListener.h"
#include "Framework/Actor.h"
#include "Components/CollisionComponent.h"
#include <iostream>

namespace neu
{

	void neu::ContactListener::BeginContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer)
		{
			Actor* actorA = (Actor*)(fixtureA->GetUserData().pointer);
			Actor* actorB = (Actor*)(fixtureB->GetUserData().pointer);

			std::cout << actorA->GetName() << std::endl;
			std::cout << actorB->GetName() << std::endl;

			if (actorA->GetComponent<CollisionComponent>())
			{
				actorA->GetComponent <CollisionComponent>()->OnCollisionEnter(actorA);
			}
			
			if (actorB->GetComponent<CollisionComponent>())
			{
				actorB->GetComponent <CollisionComponent>()->OnCollisionEnter(actorA);
			}
		}
	}


	void neu::ContactListener::EndContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer)
		{
			Actor* actorA = (Actor*)(fixtureA->GetUserData().pointer);
			Actor* actorB = (Actor*)(fixtureB->GetUserData().pointer);

			std::cout << actorA->GetName() << std::endl;
			std::cout << actorB->GetName() << std::endl;

			if (actorA->GetComponent<CollisionComponent>())
			{
				actorA->GetComponent <CollisionComponent>()->OnCollisionExit(actorA);
			}

			if (actorB->GetComponent<CollisionComponent>())
			{
				actorB->GetComponent <CollisionComponent>()->OnCollisionExit(actorA);
			}
		}
	}

}