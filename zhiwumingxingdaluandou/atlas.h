#pragma once

#include<vector>
#include<graphics.h>

class Atlas
{
public:
	Atlas() = default;
	~Atlas() = default;

	void load_from_file(LPCTSTR path_template, int num)
	{
		//清空列表
		img_list.clear();
		//设定列表长度
		img_list.resize(num);

		TCHAR path_file[256];
		for (int i = 0; i < num; i++)
		{
			_stprintf_s(path_file, path_template, i + 1);
			loadimage(&img_list[i], path_file);
		}
	}

	//清空图集中已经加载的对象
	void clear()
	{
		img_list.clear();
	}

	//获取图集中图片的数量
	int get_size()
	{
		return (int)img_list.size(); 
	}

	IMAGE* get_image(int idx)
	{
		//检查索引是否越界
		if (idx < 0 || idx >= img_list.size())
		{
			return nullptr;
		}
		//返回对应索引图片对象的地址
		return &img_list[idx];
	}

	//向图集中添加已有的图片对象，处理水平镜像
	void add_image(const IMAGE& img)
	{
		img_list.push_back(img);
	}

	std::vector<IMAGE>  get_img_list()
	{
		return img_list;
	}

private: 
	std::vector<IMAGE> img_list; 
};

