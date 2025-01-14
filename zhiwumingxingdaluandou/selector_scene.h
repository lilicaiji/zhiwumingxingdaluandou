#pragma once

#include "scene.h"
#include "scene_manager.h"
#include "animation.h"
#include "peashooter_player.h"
#include "sunflower_player.h"
#include "gloomshroom_player.h"
#include "nut_player.h"
#include "player_id.h"

extern Player* player_1;
extern Player* player_2;

extern IMAGE img_VS;                                                  //vs 艺术字图片
extern IMAGE img_1P;                                                  //1p 文本图片
extern IMAGE img_2P;                                                  //2p 文本图片
extern IMAGE img_1P_desc;                                             //1p 键位描述图片
extern IMAGE img_2P_desc;                                             //2p 键位描述图片
extern IMAGE img_gravestone_left;                                     //朝向左的墓碑图片
extern IMAGE img_gravestone_right;                                    //朝向右的墓碑图片
extern IMAGE img_selector_tip;                                        //选角界面提示信息文本图片
extern IMAGE img_selector_background;                                 //选角界面背景图
extern IMAGE img_1P_selector_btn_idle_left;                           //1p 向左选择按钮默认状态图片
extern IMAGE img_1P_selector_btn_idle_right;                          //1p 向右选择按钮默认状态图片
extern IMAGE img_1P_selector_btn_down_left;                           //1p 向左选择按钮按下状态图片
extern IMAGE img_1P_selector_btn_down_right;                          //1p 向右选择按钮按下状态图片
extern IMAGE img_2P_selector_btn_idle_left;                           //2p 向左选择按钮默认状态图片
extern IMAGE img_2P_selector_btn_idle_right;                          //2p 向右选择按钮默认状态图片
extern IMAGE img_2P_selector_btn_down_left;                           //2p 向左选择按钮按下状态图片
extern IMAGE img_2P_selector_btn_down_right;                          //2p 向右选择按钮按下状态图片

extern IMAGE img_peashooter_selector_background_left;                 //选角界面朝向左的豌豆射手背景图片
extern IMAGE img_peashooter_selector_background_right;                //选角界面朝向右的豌豆射手背景图片
extern IMAGE img_sunflower_selector_background_left;                  //选角界面朝向左的向日葵背景图片
extern IMAGE img_sunflower_selector_background_right;                 //选角界面朝向右的向日葵背景图片
extern IMAGE img_gloomshroom_selector_background_left;                //选角界面朝向左的开朗姑背景图片
extern IMAGE img_gloomshroom_selector_background_right;               //选角界面朝向右的开朗姑背景图片
extern IMAGE img_nut_selector_background_left;                        //选角界面朝向左的奸果背景图片
extern IMAGE img_nut_selector_background_right;                       //选角界面朝向右的奸果背景图片

extern Atlas atlas_peashooter_idle_right;                             //豌豆射手角色图片
extern Atlas atlas_sunflower_idle_right;                              //向日葵角色图片
extern Atlas atlas_gloomshroom_idle_right;                            //开朗姑角色图片
extern Atlas atlas_nut_idle_right;                                    //奸果角色图片

extern IMAGE img_avatar_peashooter;									  //豌豆射手头像图片
extern IMAGE img_avatar_sunflower;									  //向日葵头像图片
extern IMAGE img_avatar_gloomshroom;								  //开朗姑头像图片
extern IMAGE img_avatar_nut;									      //奸果头像图片

extern IMAGE* img_player_1_avatar;                                    //玩家1头像
extern IMAGE* img_player_2_avatar;                                    //玩家2头像

extern SceneManager scene_manager;


class SelectorScene : public Scene
{
public:
	SelectorScene() = default;
	~SelectorScene() = default;

	void on_enter()
	{
		animation_peashooter.set_atlas(&atlas_peashooter_idle_right);
		animation_sunflower.set_atlas(&atlas_sunflower_idle_right);
		animation_gloomshroom.set_atlas(&atlas_gloomshroom_idle_right);
		animation_nut.set_atlas(&atlas_nut_idle_right);
		animation_peashooter.set_interval(100);
		animation_sunflower.set_interval(100);
		animation_gloomshroom.set_interval(100);
		animation_nut.set_interval(100);

		static const int OFFSET_X = 50;

		
		pos_img_VS.x = (getwidth() - img_VS.getwidth()) / 2;
		pos_img_VS.y = (getheight() - img_VS.getheight()) / 2;
		//std::cout << pos_img_VS.x<<" 1" << std::endl;
		pos_img_tip.x = (getwidth() - img_selector_tip.getwidth()) / 2;
		pos_img_tip.y = getheight() - 125;
		pos_img_1P.x = (getwidth() / 2 - img_1P.getwidth()) / 2 - OFFSET_X;
		pos_img_1P.y = 35;
		pos_img_2P.x = getwidth() / 2 + (getwidth() / 2 - img_2P.getwidth()) / 2 + OFFSET_X;
		pos_img_2P.y = pos_img_1P.y;
		pos_img_1P_desc.x = (getwidth() / 2 - img_1P_desc.getwidth()) / 2 - OFFSET_X;
		pos_img_1P_desc.y = getheight() - 150;
		pos_img_2P_desc.x = getwidth() / 2 + (getwidth() / 2 - img_2P_desc.getwidth()) / 2 + OFFSET_X;
		pos_img_2P_desc.y = pos_img_1P_desc.y;
		pos_img_1P_gravestone.x = (getwidth() / 2 - img_gravestone_right.getwidth()) / 2 - OFFSET_X;
		pos_img_1P_gravestone.y = pos_img_1P.y + img_1P.getheight() + 35;
		pos_img_2P_gravestone.x = getwidth() / 2 + (getwidth() / 2 - img_gravestone_left.getwidth()) / 2 + OFFSET_X;
		pos_img_2P_gravestone.y = pos_img_1P_gravestone.y;
		pos_animation_1P.x = (getwidth() / 2 - atlas_peashooter_idle_right.get_image(0)->getwidth()) / 2 - OFFSET_X;
		pos_animation_1P.y = pos_img_1P_gravestone.y + 80;
		pos_animation_2P.x = getwidth() / 2 + (getwidth() / 2 - atlas_peashooter_idle_right.get_image(0)->getwidth()) / 2 + OFFSET_X;
		pos_animation_2P.y = pos_animation_1P.y;
		pos_img_1P_name.y = pos_animation_1P.y + 155;
		pos_img_2P_name.y = pos_img_1P_name.y;
		pos_1P_selector_btn_left.x = pos_img_1P_gravestone.x - img_1P_selector_btn_idle_left.getwidth();
		pos_1P_selector_btn_left.y = pos_img_1P_gravestone.y + (img_gravestone_right.getheight() - img_1P_selector_btn_idle_left.getheight()) / 2;
		pos_1P_selector_btn_right.x = pos_img_1P_gravestone.x + img_gravestone_right.getwidth();
		pos_1P_selector_btn_right.y = pos_1P_selector_btn_left.y;
		pos_2P_selector_btn_left.x = pos_img_2P_gravestone.x - img_2P_selector_btn_idle_left.getwidth();
		pos_2P_selector_btn_left.y = pos_1P_selector_btn_left.y;
		pos_2P_selector_btn_right.x = pos_img_2P_gravestone.x + img_gravestone_left.getwidth();
		pos_2P_selector_btn_right.y = pos_1P_selector_btn_left.y;

	}

	void on_update(int delta)
	{
		animation_peashooter.on_update(delta);
		animation_sunflower.on_update(delta);
		animation_gloomshroom.on_update(delta);
		animation_nut.on_update(delta);

		selector_background_scorll_offset_x += 5;
		if (selector_background_scorll_offset_x >= img_peashooter_selector_background_left.getwidth())
			selector_background_scorll_offset_x = 0; 
	}

	void on_draw(const Camera& camera)
	{
		IMAGE* img_p1_selector_background = nullptr;
		IMAGE* img_p2_selector_background = nullptr;

		switch (player_type_2)
		{
		case SelectorScene::PlayerType::Peashooter:
			img_p1_selector_background = &img_peashooter_selector_background_right;
			break;
		case SelectorScene::PlayerType::Sunflower:
			img_p1_selector_background = &img_sunflower_selector_background_right;
			break;
		case SelectorScene::PlayerType::Gloomshroom:
			img_p1_selector_background = &img_gloomshroom_selector_background_right;
			break;
		case SelectorScene::PlayerType::Nut:
			img_p1_selector_background = &img_nut_selector_background_right;
			break;
		default:
			img_p1_selector_background = &img_peashooter_selector_background_right;
			break;
		}

		switch (player_type_1)
		{
		case SelectorScene::PlayerType::Peashooter:
			img_p2_selector_background = &img_peashooter_selector_background_left;
			break;
		case SelectorScene::PlayerType::Sunflower:
			img_p2_selector_background = &img_sunflower_selector_background_left;
			break;
		case SelectorScene::PlayerType::Gloomshroom:
			img_p2_selector_background = &img_gloomshroom_selector_background_left;
			break;
		case SelectorScene::PlayerType::Nut:
			img_p2_selector_background = &img_nut_selector_background_left;
			break;
		default:
			img_p2_selector_background = &img_sunflower_selector_background_left;
			break;
		}

		putimage(0, 0, &img_selector_background);

		putimage_alpha(selector_background_scorll_offset_x - img_p1_selector_background->getwidth(), 0, img_p1_selector_background);
		putimage_alpha(selector_background_scorll_offset_x, 0,
			img_p1_selector_background->getwidth() - selector_background_scorll_offset_x, 0, img_p1_selector_background, 0, 0);
		putimage_alpha(getwidth() - img_p2_selector_background->getwidth(), 0, img_p2_selector_background->getwidth() -
			selector_background_scorll_offset_x, 0, img_p2_selector_background, selector_background_scorll_offset_x, 0);
		putimage_alpha(getwidth() - selector_background_scorll_offset_x, 0, img_p2_selector_background);

		putimage_alpha(pos_img_VS.x, pos_img_VS.y, &img_VS);

		putimage_alpha(pos_img_1P.x, pos_img_1P.y, &img_1P);
		putimage_alpha(pos_img_2P.x, pos_img_2P.y, &img_2P);
		putimage_alpha(pos_img_1P_gravestone.x, pos_img_1P_gravestone.y, &img_gravestone_right);
		putimage_alpha(pos_img_2P_gravestone.x, pos_img_2P_gravestone.y, &img_gravestone_left);

		switch (player_type_1)
		{
		case SelectorScene::PlayerType::Peashooter:
			animation_peashooter.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);
			pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_peashooter_name)) / 2;
			outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_peashooter_name);
			break;
		case SelectorScene::PlayerType::Sunflower:
			animation_sunflower.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);
			pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_sunflower_name)) / 2;
			outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_sunflower_name);
			break;
		case SelectorScene::PlayerType::Gloomshroom:
			animation_gloomshroom.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);
			pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_sunflower_name)) / 2;
			outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_gloomshroom_name);
			break;
		case SelectorScene::PlayerType::Nut:
			animation_nut.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);
			pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_sunflower_name)) / 2;
			outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_nut_name);
			break;
		}

		switch (player_type_2)
		{
		case SelectorScene::PlayerType::Peashooter:
			animation_peashooter.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);
			pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_peashooter_name)) / 2;
			outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_peashooter_name);
			break;
		case SelectorScene::PlayerType::Sunflower:
			animation_sunflower.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);
			pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_sunflower_name)) / 2;
			outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_sunflower_name);
			break;
		case SelectorScene::PlayerType::Gloomshroom:
			animation_gloomshroom.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);
			pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_sunflower_name)) / 2;
			outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_gloomshroom_name);
			break;
		case SelectorScene::PlayerType::Nut:
			animation_nut.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);
			pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_sunflower_name)) / 2;
			outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_nut_name);
			break;
		}

		putimage_alpha(pos_1P_selector_btn_left.x, pos_1P_selector_btn_left.y,
			is_btn_1P_left_down ? &img_1P_selector_btn_down_left : &img_1P_selector_btn_idle_left);
		putimage_alpha(pos_1P_selector_btn_right.x, pos_1P_selector_btn_right.y,
			is_btn_1P_right_down ? &img_1P_selector_btn_down_right : &img_1P_selector_btn_idle_right);
		putimage_alpha(pos_2P_selector_btn_left.x, pos_2P_selector_btn_left.y,
			is_btn_2P_left_down ? &img_2P_selector_btn_down_left : &img_2P_selector_btn_idle_left);
		putimage_alpha(pos_2P_selector_btn_right.x, pos_2P_selector_btn_right.y,
			is_btn_2P_right_down ? &img_2P_selector_btn_down_right : &img_2P_selector_btn_idle_right);

		putimage_alpha(pos_img_1P_desc.x, pos_img_1P_desc.y, &img_1P_desc);
		putimage_alpha(pos_img_2P_desc.x, pos_img_2P_desc.y, &img_2P_desc);
		
		putimage_alpha(pos_img_tip.x, pos_img_tip.y, &img_selector_tip);
	}

	void on_input(const ExMessage& msg)
	{
		switch (msg.message)
		{
		case WM_KEYDOWN:
			switch (msg.vkcode)
			{
				// "A"
			case 0x41:
				is_btn_1P_left_down = true;
				break;
				// "D"
			case 0x44:
				is_btn_1P_right_down = true;
				break;
				// "<-"
			case VK_LEFT:
				is_btn_2P_left_down = true;
				break;
				// "->"
			case VK_RIGHT:
				is_btn_2P_right_down = true;
				break;
			}
			break;
		case WM_KEYUP:
			switch (msg.vkcode)
			{
				// "A"
			case 0x41:
				is_btn_1P_left_down = false;
				player_type_1 = (PlayerType)(((int)PlayerType::Invaild + (int)player_type_1 - 1) % (int)PlayerType::Invaild);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
				// "D"
			case 0x44:
				is_btn_1P_right_down = false;
				player_type_1 = (PlayerType)(((int)player_type_1 + 1) % (int)PlayerType::Invaild);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
				// "<-"
			case VK_LEFT:
				is_btn_2P_left_down = false;
				player_type_2 = (PlayerType)(((int)PlayerType::Invaild + (int)player_type_2 - 1) % (int)PlayerType::Invaild);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
				// "->"
			case VK_RIGHT:
				is_btn_2P_right_down = false;
				player_type_2 = (PlayerType)(((int)player_type_2 + 1) % (int)PlayerType::Invaild);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
			case VK_RETURN:
				scene_manager.switch_to(SceneManager::SceneType::Game);
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
				break;
			}
		
		}
	}

	void on_exit()
	{
		switch (player_type_1)
		{
		case SelectorScene::PlayerType::Peashooter: 
			player_1 = new PeashooterPlayer();
			img_player_1_avatar = &img_avatar_peashooter;
			break;
		case SelectorScene::PlayerType::Sunflower: 
			player_1 = new SunflowerPlayer();
			img_player_1_avatar = &img_avatar_sunflower;
			break;
		case SelectorScene::PlayerType::Gloomshroom:
			player_1 = new GloomshroomPlayer();
			std::cout << (int)(1111) << std::endl;
			img_player_1_avatar = &img_avatar_gloomshroom;
			break;
		case SelectorScene::PlayerType::Nut:
			player_1 = new NutPlayer();
			img_player_1_avatar = &img_avatar_nut;
			break;
		}
		//std::cout << (int)(player_type_1) << std::endl;
		player_1->set_id(PlayerID::P1);

		switch (player_type_2)
		{
		case SelectorScene::PlayerType::Peashooter: 
			player_2 = new PeashooterPlayer(false);
			img_player_2_avatar = &img_avatar_peashooter;
			break;
		case SelectorScene::PlayerType::Sunflower:
			player_2 = new SunflowerPlayer(false);
			img_player_2_avatar = &img_avatar_sunflower;
			break;
		case SelectorScene::PlayerType::Gloomshroom:
			player_2 = new GloomshroomPlayer(false);
			img_player_2_avatar = &img_avatar_gloomshroom;
			break;
		case SelectorScene::PlayerType::Nut:
			player_2 = new NutPlayer(false);
			img_player_2_avatar = &img_avatar_nut;
			break;
		}
		player_2->set_id(PlayerID::P2);

		mciSendString(_T("stop bgm_menu"), NULL, 0, NULL);
	}

private:
	enum class PlayerType
	{
		Peashooter = 0,
		Sunflower,
		Gloomshroom,
		Nut,
		Invaild 
	};

private:
	POINT pos_img_VS = { 0 };                        //vs艺术字图片位置
	POINT pos_img_tip = { 0 };                       //提示信息文本图片位置
	POINT pos_img_1P = { 0 };                        //1p文本图片位置
	POINT pos_img_2P = { 0 };                        //2p文本图片位置
	POINT pos_img_1P_desc = { 0 };                   //1p键位描述图片位置
	POINT pos_img_2P_desc = { 0 };                   //2p键位描述图片位置
	POINT pos_img_1P_name = { 0 };                   //1p角色姓名文本位置
	POINT pos_img_2P_name = { 0 };                   //2p角色姓名文本位置
	POINT pos_animation_1P = { 0 };                  //1p角色动画位置
	POINT pos_animation_2P = { 0 };                  //2p角色动画位置
	POINT pos_img_1P_gravestone = { 0 };             //1p墓碑图片位置
	POINT pos_img_2P_gravestone = { 0 };             //2p墓碑图片位置
	POINT pos_1P_selector_btn_left = { 0 };          //1p向左切换按钮
	POINT pos_1P_selector_btn_right = { 0 };         //1p向右切换按钮
	POINT pos_2P_selector_btn_left = { 0 };          //2p向左切换按钮
	POINT pos_2P_selector_btn_right = { 0 };         //2p向右切换按钮

	Animation animation_peashooter;                  //豌豆射手动画
	Animation animation_sunflower;                   //向日葵动画
	Animation animation_gloomshroom;                 //开朗姑动画
	Animation animation_nut;                         //奸果动画

	PlayerType player_type_1 = PlayerType::Peashooter; //1p角色类型
	PlayerType player_type_2 = PlayerType::Sunflower;  //2p角色类型

	LPCTSTR str_peashooter_name = _T("逗逼射手");      //豌豆射手角色名
	LPCTSTR str_sunflower_name = _T("向月葵");         //向日葵角色名
	LPCTSTR str_gloomshroom_name = _T("开朗姑");       //开朗姑角色名
	LPCTSTR str_nut_name = _T("奸果");                 //奸果角色名

	int selector_background_scorll_offset_x = 0;       //背景板滚动的距离

	bool is_btn_1P_left_down = false;                  //1p向左切换按钮是否按下
	bool is_btn_1P_right_down = false;                 //1p向右切换按钮是否按下
	bool is_btn_2P_left_down = false;                  //2p向左切换按钮是否按下
	bool is_btn_2P_right_down = false;                 //2p向右切换按钮是否按下


private:
	void outtextxy_shaded(int x, int y, LPCTSTR str)
	{
		settextcolor(RGB(45, 45, 45));
		outtextxy(x + 3, y + 3, str);
		settextcolor(RGB(255, 255, 255));
		outtextxy(x, y, str);
	}
};

