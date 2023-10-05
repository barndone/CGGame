// Copyright Epic Games, Inc. All Rights Reserved.


#include "CGGameGameModeBase.h"
#include "CGGamePlayer.h"

#include "CGGameHUD.h"

ACGGameGameModeBase::ACGGameGameModeBase()
{
	//	returns a U-class object
	//	refer to the type of an object (same as system.type in c#)
	DefaultPawnClass = ACGGamePlayer::StaticClass();
	HUDClass = ACGGameHUD::StaticClass();
}
