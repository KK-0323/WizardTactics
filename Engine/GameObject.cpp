#include "GameObject.h"

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent), objectName_(name)
{
}

GameObject::~GameObject()
{
}

void GameObject::DrawSub()
{
	//Ž©•ª‚ð•`‰æ
	this->Draw();
	for (auto child : this->childList_)
	{
		child->DrawSub();
	}
}

void GameObject::UpdateSub()
{
	this->Update();
	for (auto child : this->childList_)
	{
		child->UpdateSub();
	}
}

void GameObject::ReleaseSub()
{
	this->Release();
	for (auto child : this->childList_)
	{
		child->ReleaseSub();
	}
}

void GameObject::SetPosition(XMFLOAT3 position)
{
	transform_.position_ = position;
}

void GameObject::SetPosition(float x, float y, float z)
{
	transform_.position_ = { x,y,z };
}

void GameObject::KillMe()
{
	isDead_ = true;
}
