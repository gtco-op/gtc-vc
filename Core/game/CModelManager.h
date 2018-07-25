#pragma once
class CModelManager
{
public:
	CModelManager();


	bool IsModelLoaded(int modelid);
	bool LoadModel(int modelid);
};