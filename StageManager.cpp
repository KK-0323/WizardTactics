#include "StageManager.h"
#include "Stage.h"
#include "BattleStage.h"
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
	string parentName = pParent_->GetName();

	string fileName;

	if (parentName == "PlayScene")
	{
		fileName = "Assets\\Map\\Stage.csv";
	}
	else
	{
		fileName = "Assets\\Map\\Battle.csv";
	}
	CsvReader csv(fileName);

	const float BLOCK_SIZE = 2.0f;
	const float START_X = 5.0f;
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

			GameObject* pModel = nullptr;
			if (parentName == "BattleScene")
			{
				pModel = Instantiate<BattleStage>(this, modelPath);
			}
			else
			{
				pModel = Instantiate<Stage>(this, modelPath);
			}
			if (pModel)
			{
				stageList_.push_back(pModel);

				float posX = x * BLOCK_SIZE - START_X;
				float posY = (rowCount - 1 - y) * BLOCK_SIZE;

				pModel->SetPosition({ posX, posY, 0.0f });
			}
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
