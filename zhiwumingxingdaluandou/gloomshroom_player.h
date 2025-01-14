#pragma once

#include "player.h"
#include "gloom_bullet.h"
#include "gloom_bullet_ex.h"

#include<iostream>

extern Atlas atlas_gloomshroom_idle_left;                            //���ʹó������Ĭ�϶���ͼ��
extern Atlas atlas_gloomshroom_idle_right;                           //���ʹó����ҵ�Ĭ�϶���ͼ��
extern Atlas atlas_gloomshroom_run_left;                             //���ʹó�����ı��ܶ���ͼ��
extern Atlas atlas_gloomshroom_run_right;                            //���ʹó����ҵı��ܶ���ͼ��
extern Atlas atlas_gloomshroom_attack_ex_left;                       //���ʹó���������⹥������ͼ��
extern Atlas atlas_gloomshroom_attack_ex_right;                      //���ʹó����ҵ����⹥������ͼ��
extern Atlas atlas_gloomshroom_die_left;                             //���ʹó��������������ͼ��
extern Atlas atlas_gloomshroom_die_right;                            //���ʹó����ҵ���������ͼ��



class GloomshroomPlayer : public Player
{
public:
	GloomshroomPlayer(bool facing_right = true) : Player(facing_right)
	{
		animation_idle_left.set_atlas(&atlas_gloomshroom_idle_left);
		animation_idle_right.set_atlas(&atlas_gloomshroom_idle_right);
		animation_run_left.set_atlas(&atlas_gloomshroom_run_left);
		animation_run_right.set_atlas(&atlas_gloomshroom_run_right);
		animation_attack_ex_left.set_atlas(&atlas_gloomshroom_attack_ex_left);
		animation_attack_ex_right.set_atlas(&atlas_gloomshroom_attack_ex_right);
		animation_die_left.set_atlas(&atlas_gloomshroom_die_left);
		animation_die_right.set_atlas(&atlas_gloomshroom_die_right);

		animation_idle_left.set_interval(75);
		animation_idle_right.set_interval(75);
		animation_run_left.set_interval(75);
		animation_run_right.set_interval(75);
		animation_attack_ex_left.set_interval(75);
		animation_attack_ex_right.set_interval(75);
		animation_die_left.set_interval(150);
		animation_die_right.set_interval(150);

		animation_die_left.set_loop(false);
		animation_die_right.set_loop(false);

		size.x = 96, size.y = 96;

		timer_attack_ex.set_wait_time(attack_ex_duration);
		timer_attack_ex.set_one_shot(true);
		timer_attack_ex.set_callback(
			[&]()
			{
				is_attacking_ex = false;
				
			}
		);


		attack_cd = 100;
	}
	~GloomshroomPlayer() = default;

	void on_update(int delta)
	{
		//std::cout << "���ʹ����ڸ���" << std::endl;
		Player::on_update(delta);

		if (is_attacking_ex)
		{
			main_camera.shake(5, 100);
			timer_attack_ex.on_update(delta);
		}
		
	}

	void on_attack()
	{
		mciSendString(_T("play bubbles_shot from 0"), NULL, 0, NULL);
		
		Bullet* bullet = new GloomBullet();

		Vector2 bullet_positon;
		const Vector2& bullet_size = bullet->get_size();
		float offent = bullet_size.x / 2 - size.x / 2;
		bullet_positon.x = position.x - offent;
		bullet_positon.y = position.y - offent;

		bullet->set_position(bullet_positon.x, bullet_positon.y);

		bullet->set_collide_target(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);

		bullet->set_callback([&]() { mp += 40; });

		bullet_list.push_back(bullet);

		
	}

	void on_attack_ex()
	{
		mciSendString(_T("play bubbles_shot_ex from 0"), NULL, 0, NULL);

		timer_attack_ex.restart();

		is_attacking_ex = true;

		is_facing_right ? animation_attack_ex_right.reset() : animation_attack_ex_left.reset();

		Bullet* bullet = new GlooomBulletEx();

		Vector2 bullet_positon;
		const Vector2& bullet_size = bullet->get_size();
		float offent = bullet_size.x / 2 - size.x / 2;
		bullet_positon.x = position.x - offent;
		bullet_positon.y = position.y - offent;

		bullet->set_position(bullet_positon.x, bullet_positon.y);

		bullet->set_collide_target(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);

		bullet->set_callback([&]() { mp += 40; });

		bullet_list.push_back(bullet);
	}

	void move_and_collode(int delta)
	{
		Player::move_and_collode(delta);
	}

private:
	int attack_ex_duration = 2500;                    //���⹥��״̬����ʱ��

private:
	Timer timer_attack_ex;                                  //���⹥��״̬��ʱ��
};

