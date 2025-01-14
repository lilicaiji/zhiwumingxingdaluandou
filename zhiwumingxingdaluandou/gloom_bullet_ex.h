#pragma once

#include "bullet.h"
#include "animation.h"

extern Atlas atlas_bubbles_ex;								          //�����ܴ�Χ����ͼ��

extern Camera main_camera;

class GlooomBulletEx : public Bullet
{
public:
	GlooomBulletEx()
	{

		size.x = 384, size.y = 384;

		damage = 30;

		animation_idle.set_atlas(&atlas_bubbles_ex);
		animation_idle.set_interval(60);

		timer.set_wait_time(duration);
		timer.set_one_shot(true);
		timer.set_callback(
			[&]()
			{
				can_remove = true;

			}
		);
	}
	~GlooomBulletEx() = default;

	void on_collide()
	{
		Bullet::on_collide();

		main_camera.shake(20, 350);

	}

	bool check_collision(const Vector2& position, const Vector2& size)
	{
		return (position.x - ((this->position.x + this->size.x / 2))) * (position.x - ((this->position.x + this->size.x / 2)))
			+ (position.y - ((this->position.y + this->size.y / 2))) * (position.y - ((this->position.y + this->size.y / 2)))
			<= (this->size.y / 2 - 10) * (this->size.y / 2 - 10) ? true : false;
	}

	void on_update(int delta)
	{

		animation_idle.on_update(delta);
		timer.on_update(delta);

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
	const int duration = 2500;  //���ܳ���ʱ��

private:
	Animation animation_idle;   //�����ܴ�Χ����Ĭ�϶���
	Timer timer;                 //���ܶ�ʱ��

};

