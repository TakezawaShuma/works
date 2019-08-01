#include "../../../stdafx.h"
#include "LobbyScene.h"

using namespace std;

Lobby::Lobby()
{
}

Lobby::~Lobby()
{
}

int Lobby::SceneFlag(Player  _p1)
{
	return _p1.changeSceneFlag;
}

list<Player> Lobby::Execution()
{
	return list<Player>();
}
