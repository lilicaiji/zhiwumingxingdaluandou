#pragma once

#include "util.h"

extern IMAGE buff_icon_hurry;                                        //buff加速标志
extern IMAGE buff_icon_invisible;                                    //buff隐身标志
extern IMAGE buff_icon_recover;                                      //buff回复标志
extern IMAGE buff_icon_silence;                                      //buff沉默标志

extern Player* player_1;
extern Player* player_2;

class StatusBar
{
public:
	StatusBar()
	{
		transparently_image(&buff_icon_hurry, &img_transparently);

		timer_buff_blue_imminent_disappearance_blink.set_wait_time(75);
		timer_buff_blue_imminent_disappearance_blink.set_callback(
			[&]()
			{
				is_buff_blue_showing_transparently_frame = !is_buff_blue_showing_transparently_frame;
			}
		);
		timer_buff_pink_imminent_disappearance_blink.set_wait_time(75);
		timer_buff_pink_imminent_disappearance_blink.set_callback(
			[&]()
			{
				is_buff_pink_showing_transparently_frame = !is_buff_pink_showing_transparently_frame;
			}
		);

	}
	~StatusBar() = default;

	void set_avatar(IMAGE* img)
	{
		img_avatar = img;
	}

	void set_position(int x, int y)
	{
		position.x = x, position.y = y;
	}

	void set_hp(int val)
	{
		hp = val;
	}

	void add_hp(int val)
	{
		hp += val;
	}

	void set_mp(int val)
	{
		mp = val;
	}

	void set_id(PlayerID id)
	{
		this->id = id;
	}

	void on_update(int delta)
	{
		timer_buff_blue_imminent_disappearance_blink.on_update(delta);
		timer_buff_pink_imminent_disappearance_blink.on_update(delta);
		
	}

	void on_draw()
	{
		putimage_alpha(position.x, position.y, img_avatar);

		//状态栏
		setfillcolor(RGB(5, 5, 5));
		solidroundrect(position.x + 100, position.y + 10, position.x + 100 + width + 3 * 2, position.y + 36, 8, 8);
		solidroundrect(position.x + 100, position.y + 45, position.x + 100 + width + 3 * 2, position.y + 71, 8, 8);
		setfillcolor(RGB(67, 47, 47));
		solidroundrect(position.x + 100, position.y + 10, position.x + 100 + width + 3, position.y + 33, 8, 8);
		solidroundrect(position.x + 100, position.y + 45, position.x + 100 + width + 3, position.y + 68, 8, 8);

		//画血量和能量条
		float hp_bar_width = width * max(0, hp) / 100.0f;
		float mp_bar_width = width * min(100, mp) / 100.0f;
		setfillcolor(RGB(197, 61, 67));
		solidroundrect(position.x + 100, position.y + 10, position.x + 100 + (int)hp_bar_width + 3, position.y + 33, 8, 8);
		setfillcolor(RGB(83, 131, 195));
		solidroundrect(position.x + 100, position.y + 45, position.x + 100 + (int)mp_bar_width + 3, position.y + 68, 8, 8);
	
		//画buff
		//玩家1
		if (id == PlayerID::P1)
		{
			//疾行buff
			if (player_1->get_is_buff_blue())
			{
				if (player_1->get_is_buff_blue_imminent_disappearance())
				{
					is_buff_blue_showing_transparently_frame == true ? putimage_alpha(position.x + 100, position.y - 55, &img_transparently) :
						putimage_alpha(position.x + 100, position.y - 55, &buff_icon_hurry);
				}
				else
				{
					putimage_alpha(position.x + 100, position.y - 55, &buff_icon_hurry);
				}
			}
			if (player_1->get_is_buff_pink())
			{
				//隐身buff
				if (player_1->get_is_buff_pink_imminent_disappearance())
				{
					is_buff_pink_showing_transparently_frame == true ? putimage_alpha(position.x + 100 + 80, position.y - 55, &img_transparently) :
						putimage_alpha(position.x + 100 + 80, position.y - 55, &buff_icon_invisible);
				}
				else
				{
					putimage_alpha(position.x + 100 + 80, position.y - 55, &buff_icon_invisible);
				}
			}
		}
		



		//玩家2
		if (id == PlayerID::P2)
		{
			//疾行buff
			if (player_2->get_is_buff_blue())
			{
				if (player_2->get_is_buff_blue_imminent_disappearance())
				{
					is_buff_blue_showing_transparently_frame == true ? putimage_alpha(position.x + 100, position.y - 55, &img_transparently) :
						putimage_alpha(position.x + 100, position.y - 55, &buff_icon_hurry);
				}
				else
				{
					putimage_alpha(position.x + 100, position.y - 55, &buff_icon_hurry);
				}
			}
			if (player_2->get_is_buff_pink())
			{
				//隐身buff
				if (player_2->get_is_buff_pink_imminent_disappearance())
				{
					is_buff_pink_showing_transparently_frame == true ? putimage_alpha(position.x + 100 + 80, position.y - 55, &img_transparently) :
						putimage_alpha(position.x + 100 + 80, position.y - 55, &buff_icon_invisible);
				}
				else
				{
					putimage_alpha(position.x + 100 + 80, position.y - 55, &buff_icon_invisible);
				}
			}
		}
	}

	

private:
	const int width = 275;       //状态条宽度

private:
	int hp = 0;                  //需要显示的生命值
	int mp = 0;                  //需要显示的能量值
	POINT position = { 0 };      //在窗口显示的位置
	IMAGE* img_avatar = nullptr; //角色头像图片
	PlayerID id = PlayerID::P1;  //玩家状态栏

	IMAGE img_transparently;                              //动画帧透明图片 
	bool is_buff_blue_showing_transparently_frame = false;//蓝色buff当前帧是否应该显示剪影
	Timer timer_buff_blue_imminent_disappearance_blink;   //蓝色buff即将消失状态闪烁定时器
	bool is_buff_pink_showing_transparently_frame = false;//粉色buff当前帧是否应该显示剪影
	Timer timer_buff_pink_imminent_disappearance_blink;   //粉色buff即将消失状态闪烁定时器
};
