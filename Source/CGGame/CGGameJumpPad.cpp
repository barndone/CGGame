// Fill out your copyright notice in the Description page of Project Settings.


#include "CGGameJumpPad.h"
#include "CGGamePlayer.h"

// Sets default values
ACGGameJumpPad::ACGGameJumpPad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	JumpPadMesh = CreateDefaultSubobject<UStaticMeshComponent>("JumpPadMesh");
	RootComponent = JumpPadMesh;
}

// Called when the game starts or when spawned
void ACGGameJumpPad::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACGGameJumpPad::HandleOverlap);

}

void ACGGameJumpPad::HandleOverlap(AActor* _OverlappedActor, AActor* _OtherActor)
{
	ACGGamePlayer* player = Cast<ACGGamePlayer>(_OtherActor);
	if (player == nullptr)
	{
		return;

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("JUMP PAD GO BRR"));
		player->ApplyImpulse(JumpForce, ResetYVelocity);
	}
}

