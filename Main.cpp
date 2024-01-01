#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "catch_reporter_github.hpp"
// Some Windows BS I guess included by Catch?
#ifdef far
#undef far
#endif
#ifdef near
#undef near
#endif
#include "Actor.h"
#include "CollisionComponent.h"

// This is janky but doing it this way to account for weird include
// dependencies people may have introduced into CollisionComponent.cpp
#include <algorithm>
#include <vector>
// Create dummy implementations for a few SDL functions/macros
#ifdef SDL_assert
#undef SDL_assert
#endif
#define SDL_assert(condition) REQUIRE(condition)

#ifdef SDL_assert_release
#undef SDL_assert_release
#endif
#define SDL_assert_release(condition) REQUIRE(condition)

// Skip over SDL logs completely
static void SDL_Log(...)
{
}

#include "CollisionComponent.cpp"

TEST_CASE("GetMinOverlap() - They don't intersect")
{
	SECTION("GetMinOverlap() - They don't intersect - Square dimensions - Below")
	{
		Actor a1(Vector3(50.0f, 70.0f, 0.0f), 1.0f);
		Actor a2(Vector3(50.0f, 70.0f, -30.0f), 1.0f);
		CollisionComponent c1(&a1);
		c1.SetSize(25.0f, 25.0f, 25.0f);
		CollisionComponent c2(&a2);
		c2.SetSize(25.0f, 25.0f, 25.0f);
		Vector3 offset;
		REQUIRE(c1.GetMinOverlap(&c2, offset) == CollSide::None);
	}
	SECTION("GetMinOverlap() - They don't intersect - Square dimensions - Above")
	{
		Actor a1(Vector3(50.0f, 70.0f, 0.0f), 1.0f);
		Actor a2(Vector3(50.0f, 70.0f, 30.0f), 1.0f);
		CollisionComponent c1(&a1);
		c1.SetSize(25.0f, 25.0f, 25.0f);
		CollisionComponent c2(&a2);
		c2.SetSize(25.0f, 25.0f, 25.0f);
		Vector3 offset;
		REQUIRE(c1.GetMinOverlap(&c2, offset) == CollSide::None);
	}
	SECTION("GetMinOverlap() - They don't intersect - Square dimensions - Right")
	{
		Actor a1(Vector3(50.0f, 70.0f, 25.0f), 1.0f);
		Actor a2(Vector3(50.0f, 100.0f, 25.0f), 1.0f);
		CollisionComponent c1(&a1);
		c1.SetSize(25.0f, 25.0f, 25.0f);
		CollisionComponent c2(&a2);
		c2.SetSize(25.0f, 25.0f, 25.0f);
		Vector3 offset;
		REQUIRE(c1.GetMinOverlap(&c2, offset) == CollSide::None);
	}
	SECTION("GetMinOverlap() - They don't intersect - Square dimensions - Left")
	{
		Actor a1(Vector3(50.0f, 70.0f, 25.0f), 1.0f);
		Actor a2(Vector3(50.0f, 44.0f, 25.0f), 1.0f);
		CollisionComponent c1(&a1);
		c1.SetSize(25.0f, 25.0f, 25.0f);
		CollisionComponent c2(&a2);
		c2.SetSize(25.0f, 25.0f, 25.0f);
		Vector3 offset;
		REQUIRE(c1.GetMinOverlap(&c2, offset) == CollSide::None);
	}
	SECTION("GetMinOverlap() - They don't intersect - Square dimensions - Front")
	{
		Actor a1(Vector3(50.0f, 70.0f, 25.0f), 1.0f);
		Actor a2(Vector3(76.0f, 70.0f, 25.0f), 1.0f);
		CollisionComponent c1(&a1);
		c1.SetSize(25.0f, 25.0f, 25.0f);
		CollisionComponent c2(&a2);
		c2.SetSize(25.0f, 25.0f, 25.0f);
		Vector3 offset;
		REQUIRE(c1.GetMinOverlap(&c2, offset) == CollSide::None);
	}
	SECTION("GetMinOverlap() - They don't intersect - Square dimensions - Back")
	{
		Actor a1(Vector3(50.0f, 70.0f, 25.0f), 1.0f);
		Actor a2(Vector3(24.0f, 70.0f, 25.0f), 1.0f);
		CollisionComponent c1(&a1);
		c1.SetSize(25.0f, 25.0f, 25.0f);
		CollisionComponent c2(&a2);
		c2.SetSize(25.0f, 25.0f, 25.0f);
		Vector3 offset;
		REQUIRE(c1.GetMinOverlap(&c2, offset) == CollSide::None);
	}
	SECTION("GetMinOverlap() - They don't intersect - Non-uniform dimensions - Below")
	{
		Actor a1(Vector3(50.0f, 70.0f, 0.0f), 1.0f);
		Actor a2(Vector3(50.0f, 70.0f, -30.0f), 1.0f);
		CollisionComponent c1(&a1);
		c1.SetSize(50.0f, 25.0f, 75.0f);
		CollisionComponent c2(&a2);
		c2.SetSize(50.0f, 25.0f, 75.0f);
		Vector3 offset;
		REQUIRE(c1.GetMinOverlap(&c2, offset) == CollSide::None);
	}
	SECTION("GetMinOverlap() - They don't intersect - Non-uniform dimensions - Above")
	{
		Actor a1(Vector3(50.0f, 70.0f, 0.0f), 1.0f);
		Actor a2(Vector3(50.0f, 70.0f, 30.0f), 1.0f);
		CollisionComponent c1(&a1);
		c1.SetSize(50.0f, 25.0f, 75.0f);
		CollisionComponent c2(&a2);
		c2.SetSize(50.0f, 25.0f, 75.0f);
		Vector3 offset;
		REQUIRE(c1.GetMinOverlap(&c2, offset) == CollSide::None);
	}
	SECTION("GetMinOverlap() - They don't intersect - Non-uniform dimensions - Right")
	{
		Actor a1(Vector3(50.0f, 70.0f, 25.0f), 1.0f);
		Actor a2(Vector3(50.0f, 100.0f, 25.0f), 1.0f);
		CollisionComponent c1(&a1);
		c1.SetSize(25.0f, 50.0f, 75.0f);
		CollisionComponent c2(&a2);
		c2.SetSize(25.0f, 50.0f, 75.0f);
		Vector3 offset;
		REQUIRE(c1.GetMinOverlap(&c2, offset) == CollSide::None);
	}
	SECTION("GetMinOverlap() - They don't intersect - Non-uniform dimensions - Left")
	{
		Actor a1(Vector3(50.0f, 70.0f, 25.0f), 1.0f);
		Actor a2(Vector3(50.0f, 44.0f, 25.0f), 1.0f);
		CollisionComponent c1(&a1);
		c1.SetSize(25.0f, 50.0f, 75.0f);
		CollisionComponent c2(&a2);
		c2.SetSize(25.0f, 50.0f, 75.0f);
		Vector3 offset;
		REQUIRE(c1.GetMinOverlap(&c2, offset) == CollSide::None);
	}
	SECTION("GetMinOverlap() - They don't intersect - Non-uniform dimensions - Front")
	{
		Actor a1(Vector3(50.0f, 70.0f, 25.0f), 1.0f);
		Actor a2(Vector3(76.0f, 70.0f, 25.0f), 1.0f);
		CollisionComponent c1(&a1);
		c1.SetSize(50.0f, 75.0f, 25.0f);
		CollisionComponent c2(&a2);
		c2.SetSize(50.0f, 75.0f, 25.0f);
		Vector3 offset;
		REQUIRE(c1.GetMinOverlap(&c2, offset) == CollSide::None);
	}
	SECTION("GetMinOverlap() - They don't intersect - Non-uniform dimensions - Back")
	{
		Actor a1(Vector3(50.0f, 70.0f, 25.0f), 1.0f);
		Actor a2(Vector3(24.0f, 70.0f, 25.0f), 1.0f);
		CollisionComponent c1(&a1);
		c1.SetSize(50.0f, 75.0f, 25.0f);
		CollisionComponent c2(&a2);
		c2.SetSize(50.0f, 75.0f, 25.0f);
		Vector3 offset;
		REQUIRE(c1.GetMinOverlap(&c2, offset) == CollSide::None);
	}
}

TEST_CASE("GetMinOverlap() - Single overlap side")
{
	SECTION("GetMinOverlap() - Single overlap side - Non-uniform dimensions - Top")
	{
		Actor thisActor(Vector3(50.0f, 85.0f, 28.0f), 1.0f);
		Actor otherActor(Vector3(50.0f, 85.0f, 0.0f), 1.0f);
		CollisionComponent thisCC(&thisActor);
		thisCC.SetSize(100.0f, 32.0f, 64.0f);
		CollisionComponent otherCC(&otherActor);
		otherCC.SetSize(100.0f, 32.0f, 64.0f);
		Vector3 offset;
		REQUIRE(thisCC.GetMinOverlap(&otherCC, offset) == CollSide::Top);
		REQUIRE(offset.x == Approx(0.0f));
		REQUIRE(offset.y == Approx(0.0f));
		REQUIRE(offset.z == Approx(4.0f));
	}
	SECTION("GetMinOverlap() - Single overlap side - Non-uniform dimensions - Bottom")
	{
		Actor thisActor(Vector3(50.0f, 85.0f, 0.0f), 1.0f);
		Actor otherActor(Vector3(50.0f, 85.0f, 27.0f), 1.0f);
		CollisionComponent thisCC(&thisActor);
		thisCC.SetSize(100.0f, 32.0f, 64.0f);
		CollisionComponent otherCC(&otherActor);
		otherCC.SetSize(100.0f, 32.0f, 64.0f);
		Vector3 offset;
		REQUIRE(thisCC.GetMinOverlap(&otherCC, offset) == CollSide::Bottom);
		REQUIRE(offset.x == Approx(0.0f));
		REQUIRE(offset.y == Approx(0.0f));
		REQUIRE(offset.z == Approx(-5.0f));
	}
	SECTION("GetMinOverlap() - Single overlap side - Non-uniform dimensions - Left")
	{
		Actor thisActor(Vector3(50.0f, 85.0f, 30.0f), 1.0f);
		Actor otherActor(Vector3(50.0f, 115.0f, 30.0f), 1.0f);
		CollisionComponent thisCC(&thisActor);
		thisCC.SetSize(32.0f, 64.0f, 100.0f);
		CollisionComponent otherCC(&otherActor);
		otherCC.SetSize(32.0f, 64.0f, 100.0f);
		Vector3 offset;
		REQUIRE(thisCC.GetMinOverlap(&otherCC, offset) == CollSide::Left);
		REQUIRE(offset.x == Approx(0.0f));
		REQUIRE(offset.y == Approx(-2.0f));
		REQUIRE(offset.z == Approx(0.0f));
	}
	SECTION("GetMinOverlap() - Single overlap side - Non-uniform dimensions - Right")
	{
		Actor thisActor(Vector3(50.0f, 85.0f, 20.0f), 1.0f);
		Actor otherActor(Vector3(50.0f, 54.0f, 20.0f), 1.0f);
		CollisionComponent thisCC(&thisActor);
		thisCC.SetSize(32.0f, 64.0f, 100.0f);
		CollisionComponent otherCC(&otherActor);
		otherCC.SetSize(32.0f, 64.0f, 100.0f);
		Vector3 offset;
		REQUIRE(thisCC.GetMinOverlap(&otherCC, offset) == CollSide::Right);
		REQUIRE(offset.x == Approx(0.0f));
		REQUIRE(offset.y == Approx(1.0f));
		REQUIRE(offset.z == Approx(0.0f));
	}
	SECTION("GetMinOverlap() - Single overlap side - Non-uniform dimensions - Front")
	{
		Actor thisActor(Vector3(79.0f, 85.0f, 10.0f), 1.0f);
		Actor otherActor(Vector3(50.0f, 85.0f, 10.0f), 1.0f);
		CollisionComponent thisCC(&thisActor);
		thisCC.SetSize(64.0f, 100.0f, 32.0f);
		CollisionComponent otherCC(&otherActor);
		otherCC.SetSize(64.0f, 100.0f, 32.0f);
		Vector3 offset;
		REQUIRE(thisCC.GetMinOverlap(&otherCC, offset) == CollSide::Front);
		REQUIRE(offset.x == Approx(3.0f));
		REQUIRE(offset.y == Approx(0.0f));
		REQUIRE(offset.z == Approx(0.0f));
	}
	SECTION("GetMinOverlap() - Single overlap side - Non-uniform dimensions - Back")
	{
		Actor thisActor(Vector3(50.0f, 85.0f, 10.0f), 1.0f);
		Actor otherActor(Vector3(79.0f, 85.0f, 10.0f), 1.0f);
		CollisionComponent thisCC(&thisActor);
		thisCC.SetSize(64.0f, 100.0f, 32.0f);
		CollisionComponent otherCC(&otherActor);
		otherCC.SetSize(64.0f, 100.0f, 32.0f);
		Vector3 offset;
		REQUIRE(thisCC.GetMinOverlap(&otherCC, offset) == CollSide::Back);
		REQUIRE(offset.x == Approx(-3.0f));
		REQUIRE(offset.y == Approx(0.0f));
		REQUIRE(offset.z == Approx(0.0f));
	}
}

TEST_CASE("GetMinOverlap() - Tie")
{
	SECTION("GetMinOverlap() - Tie - Top or Left")
	{
		Actor thisActor(Vector3(32.0f, 32.0f, 64.0f), 1.0f);
		Actor otherActor(Vector3(32.0f, 64.0f, 32.0f), 1.0f);
		CollisionComponent thisCC(&thisActor);
		thisCC.SetSize(32.0f, 32.0f, 32.0f);
		CollisionComponent otherCC(&otherActor);
		otherCC.SetSize(32.0f, 32.0f, 32.0f);
		Vector3 offset;
		CollSide side = thisCC.GetMinOverlap(&otherCC, offset);
		REQUIRE((side == CollSide::Top || side == CollSide::Left));
		REQUIRE(offset.x == Approx(0.0f));
		REQUIRE(offset.y == Approx(0.0f));
		REQUIRE(offset.z == Approx(0.0f));
	}
	SECTION("GetMinOverlap() - Tie - Top or Right")
	{
		Actor thisActor(Vector3(32.0f, 96.0f, 64.0f), 1.0f);
		Actor otherActor(Vector3(32.0f, 64.0f, 32.0f), 1.0f);
		CollisionComponent thisCC(&thisActor);
		thisCC.SetSize(32.0f, 32.0f, 32.0f);
		CollisionComponent otherCC(&otherActor);
		otherCC.SetSize(32.0f, 32.0f, 32.0f);
		Vector3 offset;
		CollSide side = thisCC.GetMinOverlap(&otherCC, offset);
		REQUIRE((side == CollSide::Top || side == CollSide::Right));
		REQUIRE(offset.x == Approx(0.0f));
		REQUIRE(offset.y == Approx(0.0f));
		REQUIRE(offset.z == Approx(0.0f));
	}
	SECTION("GetMinOverlap() - Tie - Back or Left")
	{
		Actor thisActor(Vector3(32.0f, 32.0f, 0.0f), 1.0f);
		Actor otherActor(Vector3(64.0f, 64.0f, 0.0f), 1.0f);
		CollisionComponent thisCC(&thisActor);
		thisCC.SetSize(32.0f, 32.0f, 32.0f);
		CollisionComponent otherCC(&otherActor);
		otherCC.SetSize(32.0f, 32.0f, 32.0f);
		Vector3 offset;
		CollSide side = thisCC.GetMinOverlap(&otherCC, offset);
		REQUIRE((side == CollSide::Back || side == CollSide::Left));
		REQUIRE(offset.x == Approx(0.0f));
		REQUIRE(offset.y == Approx(0.0f));
		REQUIRE(offset.z == Approx(0.0f));
	}
	SECTION("GetMinOverlap() - Tie - Front or Right")
	{
		Actor thisActor(Vector3(64.0f, 64.0f, 0.0f), 1.0f);
		Actor otherActor(Vector3(32.0f, 32.0f, 0.0f), 1.0f);
		CollisionComponent thisCC(&thisActor);
		thisCC.SetSize(32.0f, 32.0f, 32.0f);
		CollisionComponent otherCC(&otherActor);
		otherCC.SetSize(32.0f, 32.0f, 32.0f);
		Vector3 offset;
		CollSide side = thisCC.GetMinOverlap(&otherCC, offset);
		REQUIRE((side == CollSide::Front || side == CollSide::Right));
		REQUIRE(offset.x == Approx(0.0f));
		REQUIRE(offset.y == Approx(0.0f));
		REQUIRE(offset.z == Approx(0.0f));
	}
}
