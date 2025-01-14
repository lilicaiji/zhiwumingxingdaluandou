#pragma once

#include "bullet.h"
#include "animation.h"
#include "util.h"

#include <graphics.h>

extern Atlas atlas_nut_attack_ex_left;                               //�������������⹥������ͼ��
extern Atlas atlas_nut_attack_ex_right;                              //��������ҵ����⹥������ͼ��
extern Atlas atlas_nut_explode;                                     //�����ը����ͼ��


extern Camera main_camera;

class NutBullet :public Bullet
{
public:
	NutBullet()
	{
		size.x = 96, size.y = 96;

		damage = 30;

		animation_idle.set_atlas(&atlas_nut_attack_ex_left);
		animation_idle_right.set_atlas(&atlas_nut_attack_ex_right);
		animation_explode.set_atlas(&atlas_nut_explode);

		animation_idle.set_interval(50);
		animation_idle_right.set_interval(50);
		animation_explode.set_interval(50);

		animation_idle.set_loop(false);
		animation_idle_right.set_loop(false);
		animation_explode.set_loop(false);

		animation_explode.set_callback([&]() { can_remove = true; });

		IMAGE* img1 = atlas_nut_explode.get_image(0);
		IMAGE* img2 = atlas_nut_attack_ex_left.get_image(0);
		offset.x = (img2->getwidth() - img1->getwidth()) / 2;
		offset.y = (img2->getheight() - img1->getheight()) / 2;
		
	}
	~NutBullet()
	{

	}

	void on_collide()
	{
		Bullet::on_collide();

		main_camera.shake(5, 200);
	}



	void on_update(int delta)
	{
		if (valid)
		{
			position += velocity * (float)delta;
			
			rotateimage(&img_rotation, animation_idle.get_frame(), angle, size.x / 2, size.y / 2, true);
			//putimage_alpha((int)position.x, (int)position.y, (animation_idle.get_frame()));
			angle += rotation_speed;
			if (angle >= 360.0) angle -= 360.0;
		}

		if (!valid) animation_explode.on_update(delta);
		else animation_idle.on_update(delta);
		

		if (check_can_remove()) can_remove = true;
	}

	void on_draw(const Camera& camera) const
	{
		Bullet::on_draw(camera);
		if (valid)
		{
			animation_idle.on_draw(camera, (int)position.x, (int)position.y);
			
			//putimage_alpha(camera, (int)position.x, (int)position.y, const_cast<IMAGE*>(&img_rotation));
		}
		else
		{
			animation_explode.on_draw(camera, (int)(position.x + offset.x), (int)(position.y + offset.y));
		}
		
	}

private:
	float angle = 0;
	float rotation_speed = 5.0f;

private:
	Animation animation_idle;            //�������������⹥������ͼ��
	Animation animation_idle_right;      //��������ҵ����⹥������ͼ��
	Animation animation_explode;         //��������ҵ����⹥������ͼ��
	Vector2 offset;                      //ͼ��֮��Ĳ�
	IMAGE img_rotation;                  //��ת���ͼƬ
};