// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CGGamePlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int, scoreValue);

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

	UFUNCTION(BlueprintCallable)
	void AddScore(int _scoreToAdd);
	UFUNCTION(BlueprintCallable)
	int GetScore() const;
	UFUNCTION(BlueprintCallable)
	void ApplyImpulse(FVector _force, bool _resetYVelocity);
	UPROPERTY(BlueprintAssignable)
	FOnScoreChanged OnScoreChanged;

private:
	UPROPERTY(VisibleAnywhere, Category = "Player")
	class UStaticMeshComponent* PlayerMesh;

	UFUNCTION()
	void Handle_MoveForward(float _axisValue);
	UFUNCTION()
	void Handle_MoveRight(float _axisValue);
	UFUNCTION()
	void Handle_Jump();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (AllowPrivateAccess=true))
	float PushForce = 10000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (AllowPrivateAccess = true))
	float JumpForce = 10000.0f;

	UPROPERTY(VisibleAnywhere, Category = "Player", meta = (AllowPrivateAccess = true))
	int Score = 0;

	UPROPERTY(VisibleAnywhere, Category = "Player", meta = (AllowPrivateAccess = true))
	bool IsGrounded = 0;
};
