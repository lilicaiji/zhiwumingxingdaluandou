#pragma once

#include "camera.h"

#include<graphics.h>

class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	//��������ʱ�ĳ�ʼ���߼�
	virtual void on_enter() {}
	//�������ݵ���
	virtual void on_update(int delta) {}
	//��������Ⱦ
	virtual void on_draw(const Camera& camera) {}
	//�����������
	virtual void on_input(const ExMessage& msg) {}
	//�����˳�ʱ��ж���߼�
	virtual void on_exit() {}



private:

};
