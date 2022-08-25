#include <Game.hpp>
#include <Objects/Global/Player.hpp>
#include <Objects/Helpers/CompetitionSession.h>

using namespace RSDK;

ManiaGlobalVariables* maniaGlobals = nullptr;
const char* modid;

struct Player : EntityPlayer {

	struct Static : ObjectPlayer {
	};

	struct ModStatic {};

	static void StageLoad(){
		if(maniaGlobals->gameMode == MODE_COMPETITION) {
			// we in competition mode! don't break it
			modTable->Super(sVars->classID, SUPER_STAGELOAD, nullptr);
			return;
		}

		// hack the competition mode
		auto session = (EntityCompetitionSession*) maniaGlobals->competitionSession;
		session->playerCount = 4;
		maniaGlobals->playerID &= 0xFF;

		// give 3 random partners
		maniaGlobals->playerID |= (1 << Math::Rand(0, 5)) << 8;
		maniaGlobals->playerID |= (1 << Math::Rand(0, 5)) << 16;
		maniaGlobals->playerID |= (1 << Math::Rand(0, 5)) << 24;

		auto mode = maniaGlobals->gameMode;
		maniaGlobals->gameMode = MODE_COMPETITION;
		modTable->Super(sVars->classID, SUPER_STAGELOAD, nullptr);
		maniaGlobals->gameMode = mode;
	}

	MOD_DECLARE(Player);
};

MOD_REGISTER_OBJECT(Player);

#if RETRO_USE_MOD_LOADER
extern "C" {
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
}
#endif

void InitModAPI(void) {
	Mod::Settings::Settings();
}

#if RETRO_USE_MOD_LOADER
#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))

void InitModAPI(void);

bool32 LinkModLogic(EngineInfo *info, const char *id) {
#if !RETRO_REV01
    LinkGameLogicDLL(info);
#else
    LinkGameLogicDLL(*info);
#endif

	modid = id;
    maniaGlobals = (ManiaGlobalVariables*) Mod::GetGlobals();
    InitModAPI();
    return true;
}
#endif
