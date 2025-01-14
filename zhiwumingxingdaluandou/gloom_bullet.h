#pragma once

#include "bullet.h"
#include "animation.h"

extern Atlas atlas_bubbles;								          //向四周喷射图集


extern Camera main_camera;

class GloomBullet :public Bullet
{
public:
	GloomBullet()
	{
		size.x = 192, size.y = 192;

		damage = 30;

		animation_idle.set_atlas(&atlas_bubbles);
		//animation_idle.add_atlas(&atlas_bubbles);
		animation_idle.set_interval(50);
		animation_idle.set_loop(false);
		animation_idle.set_callback(
			[&]()
			{
				can_remove = true;
			}
		);
	}
	~GloomBullet()
	{
		animation_idle.clear();
	}

	void on_collide()
	{
		Bullet::on_collide();

		main_camera.shake(5, 200);

		
	}

	bool check_collision(const Vector2& position, const Vector2& size)
	{
		return ((position.x - ((this->position.x + this->size.x / 2))) * (position.x - ((this->position.x + this->size.x / 2)))
			+ (position.y - ((this->position.y + this->size.y / 2))) * (position.y - ((this->position.y + this->size.y / 2)))
			<= (this->size.y / 2 - 10) * (this->size.y / 2 - 10) ? true : false) ||  (((position.x + size.x - ((this->position.x + this->size.x / 2))) * (position.x + size.x - ((this->position.x + this->size.x / 2)))
				+ (position.y + size.y- ((this->position.y + this->size.y / 2))) * (position.y + size.y- ((this->position.y + this->size.y / 2)))
				<= (this->size.y / 2 - 10) * (this->size.y / 2 - 10) ? true : false));
	}

	void on_update(int delta)
	{
	
		animation_idle.on_update(delta);

		if (check_can_remove()) can_remove = true;
	}

	void on_draw(const Camera& camera) const
	{
		if (is_debug)
		{
			setlinecolor(RGB(255, 255, 255));
			circle((int)(position.x + size.x / 2), (int)(position.y + size.y / 2), (this->size.y / 2 - 10));
		}
		animation_idle.on_draw(camera, (int)position.x, (int)position.y);
	}

	


private:
	Animation animation_idle;          //喷射子弹默认状态
	
};