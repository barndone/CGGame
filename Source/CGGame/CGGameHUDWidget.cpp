// Fill out your copyright notice in the Description page of Project Settings.


#include "CGGameHUDWidget.h"
#include "Components/TextBlock.h"
#include "CGGamePlayer.h"

void UCGGameHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ACGGamePlayer* player = Cast<ACGGamePlayer>(GetOwningPlayerPawn());

	if (player != nullptr)
	{
		player->OnScoreChanged.AddDynamic(this, &UCGGameHUDWidget::HandleOnScoreChanged);
	}

}

void UCGGameHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UCGGameHUDWidget::HandleOnScoreChanged(int _value)
{
	ScoreText->SetText(FText::FromString(FString::FromInt(_value)));
}
