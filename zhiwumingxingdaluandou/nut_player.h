#pragma once

#include "player.h"
#include "animation.h"
#include "nut_bullet.h"

extern Atlas atlas_nut_idle_left;                                    //奸果朝向左的默认动画图集
extern Atlas atlas_nut_idle_right;                                   //奸果朝向右的默认动画图集
extern Atlas atlas_nut_run_left;                                     //奸果朝向左的奔跑动画图集
extern Atlas atlas_nut_run_right;                                    //奸果朝向右的奔跑动画图集
extern Atlas atlas_nut_attack_ex_left;                               //奸果朝向左的特殊攻击动画图集
extern Atlas atlas_nut_attack_ex_right;                              //奸果朝向右的特殊攻击动画图集
extern Atlas atlas_nut_die_left;                                     //奸果朝向左的死亡动画图集
extern Atlas atlas_nut_die_right;                                    //奸果朝向右的死亡动画图集


class NutPlayer : public Player
{
public:
	NutPlayer(bool facing_right = true) : Player(facing_right)
	{
		animation_idle_left.set_atlas(&atlas_nut_idle_left);
		animation_idle_right.set_atlas(&atlas_nut_idle_right);
		animation_run_left.set_atlas(&atlas_nut_run_left);
		animation_run_right.set_atlas(&atlas_nut_run_right);
		animation_attack_ex_left.set_atlas(&atlas_nut_attack_ex_left);
		animation_attack_ex_right.set_atlas(&atlas_nut_attack_ex_right);
		animation_die_left.set_atlas(&atlas_nut_die_left);
		animation_die_right.set_atlas(&atlas_nut_die_right);
	

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
		animation_attack_ex_left.set_loop(false);
		animation_attack_ex_right.set_loop(false);
	

		animation_attack_ex_left.set_callback(
			[&]()
			{
				is_attacking_ex = false;
			}
		);
		animation_attack_ex_right.set_callback(
			[&]()
			{
				is_attacking_ex = false;
			}
		);

		size.x = 96, size.y = 96;

		hp = 200;

		attack_cd = 250;


	}
	~NutPlayer() = default;
	
	void on_update(int delta)
	{
		//std::cout << "奸果正在更新" << std::endl;
		Player::on_update(delta);
	
	}

	void on_draw(const Camera& camera)
	{
		Player::on_draw(camera);
		
		
		

	}

	void on_attack()
	{
		hp += 50;

	}

	void on_attack_ex()
	{
		is_attacking_ex = true;

		is_facing_right ? animation_attack_ex_right.reset() : animation_attack_ex_left.reset();

		Bullet* bullet = new NutBullet();
		Player* target_player = (id == PlayerID::P1 ? player_2 : player_1);

		Vector2 bullet_velocity;
		if(is_facing_right) bullet_velocity.x = speed_nut;
		else bullet_velocity.x = -speed_nut;
		
		bullet_velocity.y = 0;

		bullet->set_position(position.x,position.y);
		bullet->set_velocity(bullet_velocity.x, bullet_velocity.y);

		bullet->set_collide_target(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);

		bullet->set_callback([&]() { mp += 20; });

		bullet_list.push_back(bullet);

		mciSendString(_T("play nut_dash from 0"), NULL, 0, NULL);
	}

	void move_and_collode(int delta)
	{
		//buff
		for (Bullet* bullet : bullet_list)
		{
			if (!bullet->get_valid() || bullet->get_collide_target() != PlayerID::P0) continue;

			if (bullet->check_collision(position, size))
			{
				switch (bullet->get_buff_id())
				{
				case BuffID::Blue:
					run_velocity += 0.2f;
					timer_buff_blue.restart();
					is_buff_blue = true;
					break;
				case BuffID::Pink:
					timer_buff_pink.restart();
					is_buff_pink = true;
					break;
				case BuffID::Yellow:

				default:
					break;
				}
				bullet->on_collide();

				bullet->set_valid(false);
			}
		}

		if (is_attacking_ex) return;
		float last_velocity_y = velocity.y;

		velocity.y += gravity * delta;
		position += velocity * (float)delta;

		if (hp <= 0) return;

		//平台
		if (velocity.y > 0)
		{
			for (const Platform& platform : platform_list)
			{
				const Platform::CollisionShape& shape = platform.shape;
				bool is_collide_x = (max(position.x + size.x, shape.right) - min(position.x, shape.left)
					<= size.x + (shape.right - shape.left));
				bool is_collide_y = (shape.y >= position.y && shape.y <= position.y + size.y);

				if (is_collide_x && is_collide_y)
				{
					float delta_pos_y = velocity.y * delta;
					//上一帧脚底的位置
					float last_tick_foot_pos_y = position.y + size.y - delta_pos_y;
					if (last_tick_foot_pos_y <= shape.y)
					{
						position.y = shape.y - size.y;
						velocity.y = 0;
						if (last_velocity_y) on_land();
						break;
					}
				}
			}
		}

		//伤害
		if (!is_invulnerable)
		{
			for (Bullet* bullet : bullet_list)
			{
				if (!bullet->get_valid() || bullet->get_collide_target() != id) continue;

				if (bullet->check_collision(position, size))
				{
					make_invulnerable();
					bullet->on_collide();
					bullet->set_valid(false);
					hp -= bullet->get_damage();
					mp += 50;
					last_hurt_direction = bullet->get_postion() - position;
					if (hp <= 0)
					{
						velocity.x = last_hurt_direction.x < 0 ? 0.35f : -0.35f;
						velocity.y = -1.0f;
					}
				}
			}
		}
	}

private:
	const float speed_nut = 0.5f;

private:
	bool is_explode = false;               //是否在播放爆炸动画
	Animation animation_nut_explode;       //坚果爆炸动画
	Vector2 offset;                        //偏移量
};

