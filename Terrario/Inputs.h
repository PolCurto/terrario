#pragma once


struct Inputs
{
	bool Create();
	bool Update();
	bool Destroy();

	const bool* keyboard = nullptr;
};