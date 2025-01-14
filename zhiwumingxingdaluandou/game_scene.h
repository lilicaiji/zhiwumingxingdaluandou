#pragma once

#include "scene.h"
#include "scene_manager.h"
#include "util.h"
#include "platform.h"
#include "player.h"
#include "status_bar.h"
#include "buff_blue_bullet.h"

#include<iostream>

extern IMAGE img_sky;												   //天空图片
extern IMAGE img_hills;											       //山脉图片
extern IMAGE img_platform_large;									   //大型平台图片
extern IMAGE img_platform_small;									   //小型平台图片

extern IMAGE img_1P_winnner;									      //1p 获胜文本图片
extern IMAGE img_2P_winnner;									      //2p 获胜文本图片
extern IMAGE img_winnner_bar;									      //获胜玩家文本背景图片

extern Camera main_camera;
extern std::vector<Platform> platform_list;

extern SceneManager scene_manager;

extern Player* player_1;
extern Player* player_2;

extern IMAGE* img_player_1_avatar;                                    //玩家1头像
extern IMAGE* img_player_2_avatar;                                    //玩家2头像 


class GameScene : public Scene
{
public:
	GameScene() = default;
	~GameScene() = default;

	void on_enter()
	{
		//std::cout << "进入游戏局内场景" << std::endl;
		is_game_over = false;
		is_slide_out_started = false;

		pos_img_winner_bar.x = -img_winnner_bar.getwidth();
		pos_img_winner_bar.y = (getheight() - img_winnner_bar.getheight()) / 2;
		pos_x_img_winner_bar_dst = (getwidth() - img_winnner_bar.getwidth()) / 2;

		pos_img_winner_text.x = pos_img_winner_bar.x;
		pos_img_winner_text.y = (getheight() - img_1P_winnner.getheight()) / 2;
		pos_x_img_winner_text_dst = (getwidth() - img_1P_winnner.getwidth()) / 2;

		timer_winnner_slide_in.restart();
		timer_winnner_slide_in.set_wait_time(2500);
		timer_winnner_slide_in.set_one_shot(true);
		timer_winnner_slide_in.set_callback(
			[&]()
			{
				is_slide_out_started = true;
			}
		);

		timer_winnner_slide_out.restart();
		timer_winnner_slide_out.set_wait_time(1000);
		timer_winnner_slide_out.set_one_shot(true);
		timer_winnner_slide_out.set_callback(
			[&]()
			{
				scene_manager.switch_to(SceneManager::SceneType::Menu);
			}
		);

		player_1->set_position(200, 50);
		player_2->set_position(975, 50);

		status_bar_1P.set_avatar(img_player_1_avatar);
		status_bar_2P.set_avatar(img_player_2_avatar);

		status_bar_1P.set_position(235, 625);
		status_bar_2P.set_position(675, 625);
		status_bar_1P.set_id(PlayerID::P1);
		status_bar_2P.set_id(PlayerID::P2);

		pos_img_sky.x = (getwidth() - img_sky.getwidth()) / 2;
		pos_img_sky.y = (getheight() - img_sky.getheight()) / 2;

		pos_img_hills.x = (getwidth() - img_hills.getwidth()) / 2;
		pos_img_hills.y = (getheight() - img_hills.getheight()) / 2;

		platform_list.resize(4);

		Platform& large_platform = platform_list[0];
		large_platform.img = &img_platform_large;
		large_platform.render_position.x = 122;
		large_platform.render_position.y = 455;
		large_platform.shape.left = (float)large_platform.render_position.x + 30;
		large_platform.shape.right = (float)large_platform.render_position.x + img_platform_large.getwidth() - 30;
		large_platform.shape.y = (float)large_platform.render_position.y + 60;

		Platform& small_platform_1 = platform_list[1];
		small_platform_1.img = &img_platform_small;
		small_platform_1.render_position.x = 175;
		small_platform_1.render_position.y = 360;
		small_platform_1.shape.left = (float)small_platform_1.render_position.x + 40;
		small_platform_1.shape.right = (float)small_platform_1.render_position.x + img_platform_small.getwidth() - 40;
		small_platform_1.shape.y = (float)small_platform_1.render_position.y + img_platform_small.getheight() / 2;
	
		Platform& small_platform_2 = platform_list[2];
		small_platform_2.img = &img_platform_small;
		small_platform_2.render_position.x = 855;
		small_platform_2.render_position.y = 360;
		small_platform_2.shape.left = (float)small_platform_2.render_position.x + 40;
		small_platform_2.shape.right = (float)small_platform_2.render_position.x + img_platform_small.getwidth() - 40;
		small_platform_2.shape.y = (float)small_platform_2.render_position.y + img_platform_small.getheight() / 2;
	
		Platform& small_platform_3 = platform_list[3];
		small_platform_3.img = &img_platform_small;
		small_platform_3.render_position.x = 515;
		small_platform_3.render_position.y = 225;
		small_platform_3.shape.left = (float)small_platform_3.render_position.x + 40;
		small_platform_3.shape.right = (float)small_platform_3.render_position.x + img_platform_small.getwidth() - 40;
		small_platform_3.shape.y = (float)small_platform_3.render_position.y + img_platform_small.getheight() / 2;
	
		mciSendString(_T("play bgm_game repeat from 0"), NULL, 0, NULL);
	}

	void on_update(int delta)
	{
		//std::cout << "游戏正在运行。。。" << std::endl;
		player_1->on_update(delta);
		player_2->on_update(delta);

		main_camera.on_update(delta);

		//删除子弹
		bullet_list.erase(std::remove_if(
			bullet_list.begin(), bullet_list.end(),
			[](const Bullet* bullet)
			{
				bool deletable = bullet->check_can_remove();
				if (deletable) delete bullet;
				return deletable;
			}),
			bullet_list.end());

		//更新子弹
		for (Bullet* bullet : bullet_list) bullet->on_update(delta);

		const Vector2 position_player_1 = player_1->get_position();
		const Vector2 position_player_2 = player_2->get_position();
		if (position_player_1.y >= getheight()) player_1->set_hp(0);
		if (position_player_2.y >= getheight()) player_2->set_hp(0);
		if (player_1->get_hp() <= 0 || player_2->get_hp() <= 0)
		{
			if (!is_game_over)
			{
				mciSendString(_T("stop bgm_game"), NULL, 0, NULL);
				mciSendString(_T("play ui_win from 0"), NULL, 0, NULL);
			}
			is_game_over = true;
		}

		status_bar_1P.set_hp(player_1->get_hp());
		status_bar_2P.set_hp(player_2->get_hp());
		status_bar_1P.set_mp(player_1->get_mp());
		status_bar_2P.set_mp(player_2->get_mp());
		status_bar_1P.on_update(delta);
		status_bar_2P.on_update(delta);

		if (is_game_over)
		{
			pos_img_winner_bar.x += (int)(speed_winnner_bar * delta);
			pos_img_winner_text.x += (int)(speed_winnner_text * delta);

			if (!is_slide_out_started)
			{
				timer_winnner_slide_in.on_update(delta);
				if (pos_img_winner_bar.x > pos_x_img_winner_bar_dst) pos_img_winner_bar.x = pos_x_img_winner_bar_dst;
				if (pos_img_winner_text.x > pos_x_img_winner_text_dst) pos_img_winner_text.x = pos_x_img_winner_text_dst;
			}
			else
			{
				timer_winnner_slide_out.on_update(delta);
			}
		}


	}

	void on_draw(const Camera& camera)
	{
		//outtextxy(10, 10, _T("游戏绘图内容"));
		putimage_alpha(camera, pos_img_sky.x, pos_img_sky.y, &img_sky);
		putimage_alpha(camera, pos_img_hills.x, pos_img_hills.y, &img_hills);

		for (const Platform& platform : platform_list)
		{
			platform.on_draw(camera);
		}

		if (is_debug)
		{
			settextcolor(RGB(255, 0, 0));
			outtextxy(15, 15, _T("已开启调试模式，按'Q'键关闭"));
		}

		player_1->on_draw(camera);
		player_2->on_draw(camera);

		for (Bullet* bullet : bullet_list) bullet->on_draw(camera);

		if (is_game_over)
		{
			putimage_alpha(pos_img_winner_bar.x, pos_img_winner_bar.y, &img_winnner_bar);
			putimage_alpha(pos_img_winner_text.x, pos_img_winner_text.y, 
			 player_1->get_hp() > 0 ? &img_1P_winnner : &img_2P_winnner);
		}
		else
		{
			status_bar_1P.on_draw();
			status_bar_2P.on_draw();
		}
	}

	void on_input(const ExMessage& msg)
	{
		player_1->on_input(msg);
		player_2->on_input(msg);
		switch (msg.message)
		{
		case WM_KEYUP: 
			// "Q"
			if (msg.vkcode == 0x51) is_debug = !is_debug;
			break;
		default:
			break;
		}
	}

	void on_exit()
	{
		std::cout << "游戏局内退出" << std::endl;
		delete player_1;
		player_1 = nullptr;
		delete player_2;
		player_2 = nullptr;

		is_debug = false;
		bullet_list.clear();
		main_camera.reset();
	}

private:
	const float speed_winnner_bar = 3.0f;              //结算动效背景移动速度
	const float speed_winnner_text = 1.5f;             //结算动效文本移动速度

private:
	POINT pos_img_sky = { 0 };                         //天空背景图位置
	POINT pos_img_hills = { 0 };                       //山脉背景图位置

	StatusBar status_bar_1P;                           //玩家1的状态条
	StatusBar status_bar_2P;                           //玩家2的状态条

	bool is_game_over = false;                         //游戏是否结束

	POINT pos_img_winner_bar = { 0 };                  //结算动效背景位置
	POINT pos_img_winner_text = { 0 };                 //结算动效文本位置
	int pos_x_img_winner_bar_dst = 0;                  //结算动效背景移动的目标位置
	int pos_x_img_winner_text_dst = 0;                 //结算动效文本移动的目标位置
	Timer timer_winnner_slide_in;                      //结算动效滑入定时器
	Timer timer_winnner_slide_out;                     //结算动效滑出定时器
	bool is_slide_out_started = false;                 //结算动效是否开始滑出
};

