#pragma once


namespace Weapon
{
	enum WeaponType
	{
		NONE,
		SWORD,
		FIST,
		STAFF,
		MAX
	};

	bool equippedWeapons[WeaponType::MAX] = { false, true, false, true };
};

