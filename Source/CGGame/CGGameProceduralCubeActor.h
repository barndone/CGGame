// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CGGameProceduralCubeActor.generated.h"

UENUM(DisplayName = "Mesh Options")
enum class MeshType : uint8
{
	QUAD = 0,
	NGON = 1,
	CUBE = 2
};

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
		float PanningSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UV Panning")
		bool PositivePanning = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UV Panning")
		bool UVPanning = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Type")
	MeshType type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quad Options")
		float Height = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quad Options")
		float Width = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NGON Options")
		float Radius = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NGON Options")
		int numSides = 4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NGON Options")
		float StartingDegreeOffset = -90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cube Options")
		float CubeHeight = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cube Options")
		float CubeWidth = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cube Options")
		float CubeDepth = 50;


private:
	//	vert positions
	TArray<FVector> Positions;
	//	indices that make up tris
	TArray<int32> TriangleIndices;
	// normal directions per vert
	TArray<FVector> Normals;
	//	vert uvs
	TArray<FVector2D> UVs;


	UPROPERTY(VisibleAnywhere)
	class UProceduralMeshComponent* ProceduralMesh;

	UFUNCTION()
	void GenerateQuadFromExtents();
	UFUNCTION()
	void GenerateNGon();
	UFUNCTION()
	void GenerateCube();
};
