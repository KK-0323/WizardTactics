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
	CsvReader csv("Assets\\Map\\Tutorial.csv");

	const float BLOCK_SIZE = 2.0f;
	const float START_X = 4.0f;
	int rowCount = csv.GetLines();

	for (int y = 0; y < rowCount; y++)
	{
		int colCount = csv.GetColumns(y);

		for (int x = 0; x < colCount; x++)
		{
			int type = csv.GetInt(y, x);

			if (type == 0)
			{
				continue;
			}

			std::string modelPath;
			switch (type)
			{
			case 1:
				modelPath = "BoxGrass.fbx";
				break;
			case 2:
				modelPath = "BoxSand.fbx";
				break;
			case 3:
				modelPath = "BoxWater.fbx";
				break;
			case 4:
				modelPath = "BoxBrick.fbx";
				break;
			default:
				continue;
			}

			Stage* pModel = Instantiate<Stage>(this, modelPath);

			float posX = x * BLOCK_SIZE - START_X;
			float posY = (rowCount - 1 - y) * BLOCK_SIZE;

			pModel->SetPosition({ posX, posY, 0.0f });
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
