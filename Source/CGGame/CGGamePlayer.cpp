// Fill out your copyright notice in the Description page of Project Settings.


#include "CGGamePlayer.h"
#include "Components/StaticMeshComponent.h"
#include "CGGamePickup.h"
#include "CGGameJumpPad.h"

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
}

// Called every frame
void ACGGamePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//	checking grounded state:
	bool wasGrounded = IsGrounded;

	//FHitRaycast
}

// Called to bind functionality to input
void ACGGamePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACGGamePlayer::Handle_MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACGGamePlayer::Handle_MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACGGamePlayer::Handle_Jump);
}

void ACGGamePlayer::AddScore(int _scoreToAdd)
{
	Score += _scoreToAdd;
	OnScoreChanged.Broadcast(Score);
}

int ACGGamePlayer::GetScore() const
{
	return Score;
}

void ACGGamePlayer::ApplyImpulse(FVector _force, bool _resetYVelocity)
{
	if (_resetYVelocity)
	{
		FVector currentVel = PlayerMesh->GetPhysicsLinearVelocity();
		PlayerMesh->SetPhysicsLinearVelocity(FVector(currentVel.X, currentVel.Y, 0.0f));
	}

	PlayerMesh->AddImpulse(_force);
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
	ApplyImpulse(FVector(0, 0, JumpForce), false);
}

