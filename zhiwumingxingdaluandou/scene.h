#pragma once

#include "camera.h"

#include<graphics.h>

class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	//场景进入时的初始化逻辑
	virtual void on_enter() {}
	//处理数据调用
	virtual void on_update(int delta) {}
	//处理画面渲染
	virtual void on_draw(const Camera& camera) {}
	//处理玩家输入
	virtual void on_input(const ExMessage& msg) {}
	//场景退出时的卸载逻辑
	virtual void on_exit() {}



private:

};
