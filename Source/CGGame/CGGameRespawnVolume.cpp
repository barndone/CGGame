// Fill out your copyright notice in the Description page of Project Settings.


#include "CGGameRespawnVolume.h"
#include "Components/BoxComponent.h"
#include "GameFramework/GameModeBase.h"
#include "CGGamePlayer.h"

// Sets default values
ACGGameRespawnVolume::ACGGameRespawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RespawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("RespawnVolume"));
	RootComponent = RespawnVolume;
}

// Called when the game starts or when spawned
void ACGGameRespawnVolume::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ACGGameRespawnVolume::HandleOverlap);
}

// Called every frame
void ACGGameRespawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACGGameRespawnVolume::HandleOverlap(AActor* _OverlappedActor, AActor* _OtherActor)
{
	ACGGamePlayer* player = Cast<ACGGamePlayer>(_OtherActor);
	if (player == nullptr)
	{
		return;
	}
	else
	{
		player->Destroy();
		GetWorld()->GetAuthGameMode()->RestartPlayer(GetWorld()->GetFirstPlayerController());
	}
}

