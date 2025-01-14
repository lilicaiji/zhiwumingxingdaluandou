#pragma once

#include "player.h"
#include "sun_bullet.h"
#include "sun_bullet_ex.h"
#include "gloom_bullet.h"

#include <iostream>

extern Atlas atlas_sunflower_idle_left;                              //向日葵朝向左的默认动画图集
extern Atlas atlas_sunflower_idle_right;                             //向日葵朝向右的默认动画图集
extern Atlas atlas_sunflower_run_left;                               //向日葵朝向左的奔跑动画图集
extern Atlas atlas_sunflower_run_right;                              //向日葵朝向右的奔跑动画图集
extern Atlas atlas_sunflower_attack_ex_left;                         //向日葵朝向左的特殊攻击动画图集
extern Atlas atlas_sunflower_attack_ex_right;                        //向日葵朝向右的特殊攻击动画图集
extern Atlas atlas_sun_text;								         //日文本动画图集
extern Atlas atlas_run_effect;								         //奔跑特效动画图集
extern Atlas atlas_sunflower_die_left;                               //向日葵朝向左的死亡动画图集
extern Atlas atlas_sunflower_die_right;                              //向日葵朝向右的死亡动画图集


extern Player* player_1;
extern Player* player_2;

class SunflowerPlayer:public Player

{
public:
	SunflowerPlayer(bool facing_right = true) : Player(facing_right)
	{
		animation_idle_left.set_atlas(&atlas_sunflower_idle_left);
		animation_idle_right.set_atlas(&atlas_sunflower_idle_right);
		animation_run_left.set_atlas(&atlas_sunflower_run_left);
		animation_run_right.set_atlas(&atlas_sunflower_run_right);
		animation_attack_ex_left.set_atlas(&atlas_sunflower_attack_ex_left);
		animation_attack_ex_right.set_atlas(&atlas_sunflower_attack_ex_right);
		animation_sun_text.set_atlas(&atlas_sun_text);
		animation_die_left.set_atlas(&atlas_sunflower_die_left);
		animation_die_right.set_atlas(&atlas_sunflower_die_right);

		animation_idle_left.set_interval(75);
		animation_idle_right.set_interval(75);
		animation_run_left.set_interval(75);
		animation_run_right.set_interval(75);
		animation_attack_ex_left.set_interval(100);
		animation_attack_ex_right.set_interval(100);
		animation_sun_text.set_interval(100);
		animation_die_left.set_interval(150);
		animation_die_right.set_interval(150);

		animation_die_left.set_loop(false);
		animation_die_right.set_loop(false);
		animation_attack_ex_left.set_loop(false);
		animation_attack_ex_right.set_loop(false);
		animation_sun_text.set_loop(false);

		animation_attack_ex_left.set_callback(
			[&]()
			{
				//std::cout << 1 << std::endl;
				is_attacking_ex = false;
				is_sun_text_visible = false;
			}
		);

		animation_attack_ex_right.set_callback(
			[&]()
			{
				is_attacking_ex = false;
				is_sun_text_visible = false;
			}
		);

		size.x = 96, size.y = 96;

		attack_cd = 250;
	}
	~SunflowerPlayer() = default;

	void on_update(int delta)
	{
		//std::cout << "向日葵正在更新" << std::endl;
		Player::on_update(delta);

		if (is_sun_text_visible) animation_sun_text.on_update(delta);
	}

	void on_draw(const Camera& camera)
	{
		Player::on_draw(camera);

		if (is_sun_text_visible)
		{
			Vector2 text_positon;
			IMAGE* frame = animation_sun_text.get_frame();
			text_positon.x = position.x - (size.x - frame->getwidth()) / 2;
			text_positon.y = position.y - frame->getheight();
			animation_sun_text.on_draw(camera, (int)text_positon.x, (int)text_positon.y);

		}
	}

	void on_attack()
	{
		Bullet* bullet = new SunBullet();

		Vector2 bullet_positon;
		const Vector2& bullet_size = bullet->get_size();
		bullet_positon.x = position.x + (size.x - bullet_size.x) / 2;
		bullet_positon.y = position.y;

		bullet->set_position(bullet_positon.x, bullet_positon.y);
		bullet->set_velocity(is_facing_right ? velocity_sun.x : -velocity_sun.x, velocity_sun.y);

		bullet->set_collide_target(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);

		bullet->set_callback([&]() { mp += 35; });

		bullet_list.push_back(bullet);
	}

	void on_attack_ex()
	{
		is_attacking_ex = true;
		is_sun_text_visible = true;

		animation_sun_text.reset();
		is_facing_right ? animation_attack_ex_right.reset() : animation_attack_ex_left.reset();

		Bullet* bullet = new SunBulletEx();
		Player* target_player = (id == PlayerID::P1 ? player_2 : player_1);

		Vector2 bullet_position, bullet_velocity;
		const Vector2& bullet_size = bullet->get_size();
		const Vector2& target_size = target_player->get_size();
		const Vector2& target_position = target_player->get_position();
		bullet_position.x = target_position.x + (target_size.x - bullet_size.x) / 2;
		bullet_position.y = -size.y;
		bullet_velocity.x = 0;
		bullet_velocity.y = speed_sun_ex;

		bullet->set_position(bullet_position.x, bullet_position.y);
		bullet->set_velocity(bullet_velocity.x, bullet_velocity.y);

		bullet->set_collide_target(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);

		bullet->set_callback([&]() { mp += 50; });

		bullet_list.push_back(bullet);

		mciSendString(_T("play sun_text from 0"), NULL, 0, NULL);
	}

	void move_and_collode(int delta)
	{
		Player::move_and_collode(delta);
	}

private:
	const float speed_sun_ex = 0.15f;          //大型日光炸弹下落速度
	const Vector2 velocity_sun = { 0.25f,-0.5f }; //小型日光炸弹抛射速度

private:
	Animation animation_sun_text;              //头顶文本动画
	bool is_sun_text_visible = false;          //是否显示头顶文本
};

