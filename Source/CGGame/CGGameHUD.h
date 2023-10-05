// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CGGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class CGGAME_API ACGGameHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> WidgetHUDClass;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true));
	UUserWidget* RootWidget;
};
