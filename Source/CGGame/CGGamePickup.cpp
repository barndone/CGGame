// Fill out your copyright notice in the Description page of Project Settings.


#include "CGGamePickup.h"
#include "CGGamePlayer.h"

// Sets default values
ACGGamePickup::ACGGamePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	RootComponent = PickupMesh;

}

// Called when the game starts or when spawned
void ACGGamePickup::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ACGGamePickup::HandleOverlap);

}

// Called every frame
void ACGGamePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACGGamePickup::HandleOverlap(AActor* _OverlappedActor, AActor* _OtherActor)
{
	ACGGamePlayer* player = Cast<ACGGamePlayer>(_OtherActor);
	if (player == nullptr)
	{
		return;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Score was: " + FString::FromInt(player->GetScore())));
		player->AddScore(ScoreValue);
		GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Green, TEXT("Score is now: " + FString::FromInt(player->GetScore())));
		Destroy();
	}
}

