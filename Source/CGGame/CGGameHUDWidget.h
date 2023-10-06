// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CGGameHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class CGGAME_API UCGGameHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true, BindWidget))
	class UTextBlock* ScoreText;

	UFUNCTION()
	void HandleOnScoreChanged(int _value);
};
