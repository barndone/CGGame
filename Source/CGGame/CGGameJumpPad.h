// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CGGameJumpPad.generated.h"

UCLASS()
class CGGAME_API ACGGameJumpPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACGGameJumpPad();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Pad")
		FVector JumpForce = {0.0f, 0.0f, 2.0f};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Jump Pad")
	class UStaticMeshComponent* JumpPadMesh;
	UPROPERTY(VisibleAnywhere, Category = "Jump Pad")
	bool ResetYVelocity = true;

	UFUNCTION()
	void HandleOverlap(AActor* _OverlappedActor, AActor* _OtherActor);

};
