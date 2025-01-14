#pragma once

#include "atlas.h"
#include "util.h"
#include "camera.h"

#include<functional>
#include <graphics.h>

using namespace std;

class Animation
{
public:
	Animation() = default;
	~Animation() = default;

	void reset()
	{
		timer = 0;
		idx_frame = 0;
	}

	//设置动画所使用的图集
	void set_atlas(Atlas* new_atlas)
	{
		reset();
		atlas = new_atlas;
	}

	void add_atlas(Atlas* new_atlas)
	{
		std::vector<IMAGE> img_list = new_atlas->get_img_list();
		for (const IMAGE& img : img_list)
		{
			atlas->add_image(img);
		}
	}

	void set_loop(bool flag)
	{
		is_loop = flag;
	}

	void set_interval(int ms)
	{
		interval = ms;
	}

	//获取当前帧索引
	int get_idx_frame()
	{
		return idx_frame;
	}

	//获取当前帧图片
	IMAGE* get_frame()
	{
		return atlas->get_image(idx_frame);
	}

	bool check_finised()
	{
		if (is_loop) return false;

		return (idx_frame == atlas->get_size() - 1);
	}

	void on_update(int delta)
	{
		timer += delta;
		if (timer >= interval)
		{
			timer = 0;
			idx_frame++;
			if (idx_frame >= atlas->get_size())
			{
				idx_frame = is_loop ? 0 : atlas->get_size() - 1;
				if (!is_loop && callback)
				{
					callback();
				}
			}
		}
	}

	void on_draw(const Camera& camera, int x,int y) const
	{
		putimage_alpha(camera, x, y, atlas->get_image(idx_frame));
	}

	void set_callback(std::function<void()> callback)
	{
		this->callback = callback;
	}

	void clear()
	{
		atlas->clear();
	}

	Atlas* get_atlas()
	{
		return atlas;
	}

private:
	//计时器
	int timer = 0;
	//帧间隔
	int interval = 0;
	//帧索引
	int idx_frame = 0;
	//是否循环
	bool is_loop = true;
	 
	Atlas* atlas = nullptr;

	std::function<void()> callback;
};

