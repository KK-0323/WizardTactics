#include "Model.h"
#include "Direct3D.h"

namespace Model
{
    std::vector<ModelData*> modelList;
}

int Model::Load(std::string fileName)
{
	for (int i = 0; i < (int)modelList.size(); i++)
	{
		if (modelList[i]->filename_ == fileName)
		{
			return i;
		}
	}

	ModelData* pModelData = new ModelData;
	pModelData->filename_ = fileName;
	pModelData->pfbx_ = new Fbx;
	pModelData->pfbx_->Load(fileName.c_str());

	modelList.push_back(pModelData);
	return((int)modelList.size() - 1);
}

void Model::SetTransform(int hModel, Transform transform)
{
    modelList[hModel]->transform_ = transform;
}

void Model::Draw(int hModel)
{
    modelList[hModel]->pfbx_->Draw(modelList[hModel]->transform_);
}

void Model::Release()
{
	bool isReffered = false; // 参照されているかどうか
	for (int i = 0; i < modelList.size(); i++)
    {
		isReffered = false;
		for (int j = i + 1; j < modelList.size(); j++)
		{
			if (modelList[i]->pfbx_ == modelList[j]->pfbx_)
			{
				isReffered = true;
				break;
			}
		}
        if (isReffered == false)
        {
            SAFE_DELETE(modelList[i]->pfbx_);
        }
		SAFE_DELETE(modelList[i]);
	}
	modelList.clear(); // 配列を空にする（念のため）
}
