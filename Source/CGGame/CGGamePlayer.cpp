// Fill out your copyright notice in the Description page of Project Settings.


#include "CGGamePlayer.h"
#include "Components/StaticMeshComponent.h"
#include "CGGamePickup.h"

// Sets default values
ACGGamePlayer::ACGGamePlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//	set up a default for the PlayerMesh
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>("PlayerMesh");
	//	Simulate physics
	PlayerMesh->SetSimulatePhysics(true);
	//	assign a root component to the Actor
	RootComponent = PlayerMesh;
}

// Called when the game starts or when spawned
void ACGGamePlayer::BeginPlay()
{
	//	super refers to base time (NOT a c++ keyword)
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACGGamePlayer::HandleOverlap);

	
}

// Called every frame
void ACGGamePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACGGamePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACGGamePlayer::Handle_MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACGGamePlayer::Handle_MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACGGamePlayer::Handle_Jump);
}

void ACGGamePlayer::Handle_MoveForward(float _axisValue)
{
	//GEngine->AddOnScreenDebugMessage(0, 0.0f, FColor::Red, TEXT("MOVE FWD"));
	PlayerMesh->AddForce(FVector(PushForce * _axisValue, 0, 0));
}

void ACGGamePlayer::Handle_MoveRight(float _axisValue)
{
	PlayerMesh->AddForce(FVector(0, PushForce * _axisValue, 0));
}

void ACGGamePlayer::Handle_Jump()
{
	PlayerMesh->AddImpulse(FVector(0, 0, JumpForce));
}

void ACGGamePlayer::HandleOverlap(AActor* _OverlappedActor, AActor* _OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Purple, TEXT("Overlap Occured"));

	//	cast to player
	ACGGamePlayer* overlappedActor = Cast<ACGGamePlayer>(_OverlappedActor);

	ACGGamePickup* overlappedPickup = Cast<ACGGamePickup>(_OtherActor);

	if (overlappedPickup != nullptr)
	{
		overlappedActor->Score += overlappedPickup->ScoreValue;
	}

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Score is now: " + FString::FromInt(overlappedActor->Score)));
}

