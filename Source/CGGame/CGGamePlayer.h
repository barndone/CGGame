// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CGGamePlayer.generated.h"

UCLASS()
class CGGAME_API ACGGamePlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	//	DO NOT SUBSCRIBE TO EVENTS HERE
	ACGGamePlayer();

protected:
	// Called when the game starts or when spawned
	//	 SUBSCRIBE TO EVENTS HERE
	//		START() in unity
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//		Update()
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Player")
	class UStaticMeshComponent* PlayerMesh;

	UFUNCTION()
	void Handle_MoveForward(float _axisValue);
	UFUNCTION()
	void Handle_MoveRight(float _axisValue);
	UFUNCTION()
	void Handle_Jump();
	UFUNCTION()
	void HandleOverlap(AActor* _OverlappedActor, AActor* _OtherActor);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (AllowPrivateAccess=true))
		float PushForce = 10000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (AllowPrivateAccess = true))
		float JumpForce = 10000.0f;

	UPROPERTY(VisibleAnywhere, Category = "Player", meta = (AllowPrivateAccess = true))
		int Score = 0;
};
