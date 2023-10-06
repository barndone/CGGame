// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CGGameProceduralCubeActor.generated.h"

UCLASS()
class CGGAME_API ACGGameProceduralCubeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACGGameProceduralCubeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UV Panning")
	float PanningSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UV Panning")
	bool PositivePanning = false;

private:
	//	vert positions
	TArray<FVector> Positions;

	//	vert uvs
	TArray<FVector2D> UVs;

	//	indices that make up tris
	TArray<int32> TriangleIndices;

	UPROPERTY(VisibleAnywhere)
	class UProceduralMeshComponent* ProceduralMesh;

};
