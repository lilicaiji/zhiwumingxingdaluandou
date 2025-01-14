#pragma once

#pragma once

#include "bullet.h"
#include "animation.h"

extern Atlas atlas_buff_box_pink;								      //蓝色buff动画图集

class BuffPinkBullet : public Bullet
{
public:
	BuffPinkBullet()
	{
		size.x = 80, size.y = 80;

		damage = 0;

		animation_idle.set_atlas(&atlas_buff_box_pink);
		animation_idle.set_interval(60);

		velocity.y = speed_drop;
	}
	~BuffPinkBullet() = default;

	void on_collide()
	{
		Bullet::on_collide();

		can_remove = true;

	}

	bool check_collision(const Vector2& position, const Vector2& size)
	{

		bool is_collide_x = (max(this->position.x + this->size.x, position.x + size.x)
			- min(this->position.x, position.x) <= this->size.x + size.x);
		bool is_collide_y = (max(this->position.y + this->size.y, position.y + size.y)
			- min(this->position.y, position.y) <= this->size.y + size.y);
		return is_collide_x && is_collide_y;
	}

	void on_update(int delta)
	{
		if (valid)
		{
			position += velocity * (float)delta;
		}

		animation_idle.on_update(delta);

		if (check_can_remove()) can_remove = true;
	}

	void on_draw(const Camera& camera) const
	{
		Bullet::on_draw(camera);
		animation_idle.on_draw(camera, (int)position.x, (int)position.y);
	}

private:
	const float speed_drop = 0.15f;          //buff下落速度

private:
	Animation animation_idle;                //buff默认动画
};
