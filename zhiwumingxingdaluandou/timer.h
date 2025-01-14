#pragma once

#include <functional>

class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	void restart()
	{
		pass_time = 0;
		shotted = false;
	}

	void set_wait_time(float val)
	{
		wait_time = val;
	}

	void add_wait_time(float val)
	{
		wait_time += val;
	}

	//是否单次触发
	void set_one_shot(bool flag)
	{
		one_shot = flag;
	}

	void set_callback(std::function<void()> callback)
	{
		this->callback = callback;
	}

	void pause()
	{
		paused = true;
	}

	void resume()
	{
		paused = false;
	}

	int get_sparetime()
	{
		return wait_time - pass_time;
	}

	void on_update(int delta)
	{
		if (paused) return;
		pass_time += delta;
		if (pass_time >= wait_time)
		{
			if ((!one_shot || (one_shot && !shotted)) && callback) callback();
			//标记已经触发过
			shotted = true;
			pass_time = 0; 
		}
	}


private:
	//已过时间
	int pass_time = 0;
	//等待时间
	int wait_time = 0;
	//是否暂停
	bool paused = false;
	//是否触发过
	bool shotted = false;
	//单次触发
	bool one_shot = false;
	//触发回调 
	std::function<void()> callback;
};
