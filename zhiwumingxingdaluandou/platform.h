#pragma once

#include "camera.h"
#include "util.h"

extern bool is_debug;

class Platform
{
public:
	struct CollisionShape
	{
		float y;
		float left, right;
	};
public :
	CollisionShape shape;
	//ƽ̨ͼƬ
	IMAGE* img = nullptr;
	//ƽ̨λ��
	POINT render_position = { 0 };

public:
	Platform() = default;
	~Platform() = default;

	void on_draw(const Camera& camera) const 
	{
		putimage_alpha(camera, render_position.x, render_position.y, img);

		if (is_debug)
		{
			setlinecolor(RGB(255, 0, 0));
			line(camera, (int)shape.left, (int)shape.y, (int)shape.right, (int)shape.y);
		}
	}

private:

};

