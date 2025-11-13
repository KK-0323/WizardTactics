#include "Stage.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), pFbx_(nullptr)
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	pFbx_ = new Fbx;
	pFbx_->Load("Road.fbx");
	transform_.position_ = { 0.0f, 0.0f, 0.0f };
}

void Stage::Update()
{
	//transform_.rotate_.y += 0.5f;
}

void Stage::Draw()
{
	if (pFbx_)
	{
		pFbx_->Draw(transform_);
	}
}

void Stage::Release()
{
	if (pFbx_)
	{
		pFbx_->Release();
		delete pFbx_;
		pFbx_ = nullptr;
	}
}

void Stage::LoadMapData(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		return;
	}

	std::string line;
	int y = 0;
	while (std::getline(file, line) && y < STAGE_HEIGHT)
	{
		std::stringstream ss(line);
		std::string token;
		int x = 0;

		while (std::getline(ss, token, ',') && x < STAGE_WIDTH)
		{
			try
			{
				mapData_[y][x] = std::stoi(token);
			}
			catch (...)
			{
				mapData_[y][x] = 0;
			}
			x++;
		}
		y++;
	}
}
