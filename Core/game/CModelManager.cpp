/*
    Grand Theft CO-OP: Vice City
    -----------------------------
    FILE: CModelManager.cpp
    DESCRIPTION: Manages the models in game.
    AUTHOR(S): Vektor

    License: GPL v2
    Copyrights (c) 2017-2018 GTC Team
*/
#include "main.h"

CModelManager::CModelManager() {
	printf("[CMODELMANAGER] Started.\n");   
}

bool CModelManager::IsModelLoaded(int modelid)
{
	return CStreaming::ms_aInfoForModel[modelid].m_nLoadState == LOADSTATE_LOADED;
}

bool CModelManager::LoadModel(int modelid)
{
	bool loaded = this->IsModelLoaded(modelid);
	if (!loaded)
	{
		unsigned char oldFlags = CStreaming::ms_aInfoForModel[modelid].m_nFlags;
		CStreaming::RequestModel(modelid, 0);
		CStreaming::LoadAllRequestedModels(false);

		loaded = this->IsModelLoaded(modelid);
		if (loaded)
		{
            if (!(oldFlags & 1))
            {
                CStreaming::SetModelIsDeletable(modelid);
            }
		}
	}
	return loaded;
}