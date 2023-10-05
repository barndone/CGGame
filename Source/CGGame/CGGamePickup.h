// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CGGamePickup.generated.h"

UCLASS()
class CGGAME_API ACGGamePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACGGamePickup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		int ScoreValue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	class UStaticMeshComponent* PickupMesh;
};
