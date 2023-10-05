// Fill out your copyright notice in the Description page of Project Settings.


#include "CGGameHUD.h"
#include "Blueprint/UserWidget.h"

void ACGGameHUD::BeginPlay()
{
	//	1st, create root widget
	UUserWidget* rootWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetHUDClass);

	//	2nd, assign owning player
	rootWidget->SetOwningPlayer(GetOwningPlayerController());
	//	3rd, add to screen
	rootWidget->AddToPlayerScreen();

	//	4th, assign the root
	RootWidget = rootWidget;
}
