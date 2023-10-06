// Fill out your copyright notice in the Description page of Project Settings.


#include "CGGameProceduralCubeActor.h"
#include <ProceduralMeshComponent.h>

// Sets default values
ACGGameProceduralCubeActor::ACGGameProceduralCubeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	RootComponent = ProceduralMesh;
}

// Called when the game starts or when spawned
void ACGGameProceduralCubeActor::BeginPlay()
{
	Super::BeginPlay();
	
	Positions.Add(FVector(0, 50, 50));			//	1st vert
	Positions.Add(FVector(0, -50, -50));		//	2nd vert
	Positions.Add(FVector(0, -50, 50));			//	3rd vert
	Positions.Add(FVector(0, 50, -50));

	UVs.Add(FVector2D(1, 0));
	UVs.Add(FVector2D(0, 1));
	UVs.Add(FVector2D(0, 0));
	UVs.Add(FVector2D(1, 1));

	TriangleIndices.Add(0);
	TriangleIndices.Add(1);
	TriangleIndices.Add(2);
	TriangleIndices.Add(2);
	TriangleIndices.Add(3);
	TriangleIndices.Add(1);

	//TrisToRender = (TriangleIndices.Num() / 2) - 1;

	ProceduralMesh->CreateMeshSection(
		0, 
		Positions, 
		TriangleIndices, 
		TArray<FVector>(), 
		UVs, 
		TArray<FColor>(), 
		TArray<FProcMeshTangent>(), 
		false);
}

// Called every frame
void ACGGameProceduralCubeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	for (int i = 0; i < UVs.Num(); i++)
	{
		if (PositivePanning)
		{
			UVs[i].X += PanningSpeed * DeltaTime;
		}
		else
		{
			UVs[i].X -= PanningSpeed * DeltaTime;
		}
	}

	ProceduralMesh->CreateMeshSection(
		0,
		Positions,
		TriangleIndices,
		TArray<FVector>(),
		UVs,
		TArray<FColor>(),
		TArray<FProcMeshTangent>(),
		false);
}


