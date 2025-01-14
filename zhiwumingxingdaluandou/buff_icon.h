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
	IMAGE img_transparently;                      //����֡͸��ͼƬ 
	bool is_showing_transparently_frame = false;  //��ǰ֡�Ƿ�Ӧ����ʾ��Ӱ
	Timer timer_imminent_disappearance_blink;     //������ʧ״̬��˸��ʱ��
	Vector2 position;                             //ͼƬλ��
	IMAGE img;
};
