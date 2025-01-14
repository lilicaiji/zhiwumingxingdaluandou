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
		//����б�
		img_list.clear();
		//�趨�б���
		img_list.resize(num);

		TCHAR path_file[256];
		for (int i = 0; i < num; i++)
		{
			_stprintf_s(path_file, path_template, i + 1);
			loadimage(&img_list[i], path_file);
		}
	}

	//���ͼ�����Ѿ����صĶ���
	void clear()
	{
		img_list.clear();
	}

	//��ȡͼ����ͼƬ������
	int get_size()
	{
		return (int)img_list.size(); 
	}

	IMAGE* get_image(int idx)
	{
		//��������Ƿ�Խ��
		if (idx < 0 || idx >= img_list.size())
		{
			return nullptr;
		}
		//���ض�Ӧ����ͼƬ����ĵ�ַ
		return &img_list[idx];
	}

	//��ͼ����������е�ͼƬ���󣬴���ˮƽ����
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

