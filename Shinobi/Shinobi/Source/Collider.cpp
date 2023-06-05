#include "Collider.h"
#include "BossScene.h"
#include "Application.h"
#include <iostream>
Collider::Collider(SDL_Rect rectangle, Type type, Module* listener): rect(rectangle), type(type), listener(listener)
{
	
}

void Collider::SetPos(int x, int y)
{
	if (App->sceneboss->IsEnabled() && type == Collider::Type::ENEMY_SHOT)
	{
		rect.x = x;
		rect.y = y+20;
	}
	else
	{
		rect.x = x;
		rect.y = y;
	}
	
}

bool Collider::Intersects(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);
}