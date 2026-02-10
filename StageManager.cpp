#include "StageManager.h"
#include "Stage.h"
#include "Engine\\CsvReader.h"

StageManager::StageManager(GameObject* parent)
	:GameObject(parent, "StageManager")
{
}

StageManager::~StageManager()
{
}

void StageManager::Initialize()
{
	CsvReader csv("Assets\\Map\\Stage.csv");

	const float BLOCK_SIZE = 1.0f;
	const float START_X = -4.0f;
	int rowCount = csv.GetLines();

	int type = csv.GetInt(y, x);
	if (type > 0 && type < (int)std::size(ModelType))
	{
		const char* path = ModelType[type];
		if (path && *path)
		{
			Stage* p = Instantiate<Stage>(this, std::string(path));
			p->SetPosition({ x * BLOCK_SIZE, (rowCount - 1 - y) * BLOCK_SIZE, 0.0f });
		}
	}
	
}

void StageManager::Update()
{
}

void StageManager::Draw()
{
}

void StageManager::Release()
{
}
