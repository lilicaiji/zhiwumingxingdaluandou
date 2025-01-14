#pragma once

#include "timer.h"
#include "vector2.h"
#include "camera.h"
#include "util.h"

#include <graphics.h>

class BuffIcon
{
public:
	BuffIcon()
	{
		timer_imminent_disappearance_blink.set_wait_time(75);
		timer_imminent_disappearance_blink.set_callback(
			[&]()
			{
				is_showing_transparently_frame = !is_showing_transparently_frame;
			}
		);
	}
	~BuffIcon();

	void set_positon(int x, int y)
	{
		position.x = x;
		position.y = y;
	}
	
	void set_img(IMAGE img)
	{
		this->img = img;
	}

	void on_update(int delta)
	{
		timer_imminent_disappearance_blink.on_update(delta);
		if (is_showing_transparently_frame) transparently_image(&img, &img_transparently);
	}

	void on_draw(const Camera& camera)
	{

	}


private:
	IMAGE img_transparently;                      //动画帧透明图片 
	bool is_showing_transparently_frame = false;  //当前帧是否应该显示剪影
	Timer timer_imminent_disappearance_blink;     //即将消失状态闪烁定时器
	Vector2 position;                             //图片位置
	IMAGE img;
};
