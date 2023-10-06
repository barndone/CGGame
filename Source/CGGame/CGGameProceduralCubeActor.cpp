// Fill out your copyright notice in the Description page of Project Settings.


#include "CGGameProceduralCubeActor.h"
#include <ProceduralMeshComponent.h>
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"

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
	
	//	QUAD Generation
	//	Positions.Add(FVector(0, 50, 50));			//	1st vert
	//	Positions.Add(FVector(0, -50, -50));		//	2nd vert
	//	Positions.Add(FVector(0, -50, 50));			//	3rd vert
	//	Positions.Add(FVector(0, 50, -50));
	//	UVs.Add(FVector2D(1, 0));
	//	UVs.Add(FVector2D(0, 1));
	//	UVs.Add(FVector2D(0, 0));
	//	UVs.Add(FVector2D(1, 1));
	//	verts need to be arranged in a counter clockwise fashion for them to be rendered correctly
	//	TriangleIndices.Add(0);
	//	TriangleIndices.Add(1);
	//	TriangleIndices.Add(2);
	//	TriangleIndices.Add(0);
	//	TriangleIndices.Add(3);
	//	TriangleIndices.Add(1);

	//	//	PENTAGON Generation
	//	Positions.Add(FVector(0, 0, 0));
	//	Positions.Add(FVector(0, 0, 50));
	//	Positions.Add(FVector(0, 50, 0));
	//	Positions.Add(FVector(0, 30, -50));
	//	Positions.Add(FVector(0, -30, -50));
	//	Positions.Add(FVector(0, -50, 0));
	//	
	//	//	CounterClockWise Per Tri:
	//	//	Tri 1:
	//	TriangleIndices.Add(0);
	//	TriangleIndices.Add(2);
	//	TriangleIndices.Add(1);
	//	//	Tri 2:
	//	TriangleIndices.Add(0);
	//	TriangleIndices.Add(3);
	//	TriangleIndices.Add(2);
	//	//	Tri 3:
	//	TriangleIndices.Add(0);
	//	TriangleIndices.Add(4);
	//	TriangleIndices.Add(3);
	//	//	Tri 4:
	//	TriangleIndices.Add(0);
	//	TriangleIndices.Add(5);
	//	TriangleIndices.Add(4);
	//	//	Tri 5:
	//	TriangleIndices.Add(0);
	//	TriangleIndices.Add(1);
	//	TriangleIndices.Add(5);


	switch (type)
	{
		case MeshType::QUAD:
			GenerateQuadFromExtents();
			break;
		case MeshType::NGON:
			GenerateNGon();
			break;
		case MeshType::CUBE:
			GenerateCube();
			break;
	}

	ProceduralMesh->CreateMeshSection(
		0, 
		Positions, 
		TriangleIndices, 
		Normals, 
		UVs, 
		TArray<FColor>(), 
		TArray<FProcMeshTangent>(), 
		false);

	//	iterate through each vert
	//	draw a debug visual for the position of that vert
	for (int i = 0; i < Positions.Num(); i++)
	{
		DrawDebugSphere(
			GetWorld(),
			ProceduralMesh->GetComponentLocation() + Positions[i],
			1.0f,
			4,
			FColor::Blue,
			true,
			-1.0f,
			0,
			1.0f
		);
	}
}

// Called every frame
void ACGGameProceduralCubeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (UVPanning)
	{
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
}

void ACGGameProceduralCubeActor::GenerateQuadFromExtents()
{
	//	add vertex positions:
	//	half extents used for offset from center position of mesh
	float halfExtentHeight = Height / 2;
	float halfExtentWidth = Width / 2;
	Positions.Add(FVector(0, halfExtentWidth, halfExtentHeight));
	Positions.Add(FVector(0, -halfExtentWidth, halfExtentHeight));
	Positions.Add(FVector(0, halfExtentWidth, -halfExtentHeight));
	Positions.Add(FVector(0, -halfExtentWidth, -halfExtentHeight));

	//	tri 1:
	TriangleIndices.Add(0);
	TriangleIndices.Add(1);
	TriangleIndices.Add(2);
	//	tri 2:
	TriangleIndices.Add(1);
	TriangleIndices.Add(3);
	TriangleIndices.Add(2);
}

void ACGGameProceduralCubeActor::GenerateNGon()
{
	float angleStep = 360.0 / numSides;
	//	center point
	Positions.Add(FVector(0, 0, 0));

	for (int i = 0; i < numSides; i++)
	{
		Positions.Add(FVector(0, 
			Radius * cosf(FMath::DegreesToRadians((angleStep * i) - StartingDegreeOffset)),
			Radius * sinf(FMath::DegreesToRadians((angleStep * i) - StartingDegreeOffset))));

		//	for each side add the origin point
		TriangleIndices.Add(0);

		int temp = i + 2;
		if (temp > numSides)
		{
			temp = 1;
		}
		TriangleIndices.Add(temp);
		TriangleIndices.Add(i+1);
	}
}

void ACGGameProceduralCubeActor::GenerateCube()
{

	FVector xNormal = { 1, 0, 0 };
	FVector yNormal = { 0, 1, 0 };
	FVector zNormal = { 0, 0, 1 };

	float halfX = CubeDepth / 2;
	float halfY = CubeWidth / 2;
	float halfZ = CubeHeight / 2;

	//	Face in positive X direction
	//	Build triangles ClockWise
	Positions.Add(FVector(halfX,	halfY,		halfZ));
	Positions.Add(FVector(halfX,	-halfY,		halfZ));
	Positions.Add(FVector(halfX,	halfY,		-halfZ));
	Positions.Add(FVector(halfX,	-halfY,		-halfZ));

	Normals.Add(xNormal);
	Normals.Add(xNormal);
	Normals.Add(xNormal);
	Normals.Add(xNormal);


	//	tri 1:
	TriangleIndices.Add(0);
	TriangleIndices.Add(2);
	TriangleIndices.Add(1);
	//	tri 2:
	TriangleIndices.Add(1);
	TriangleIndices.Add(2);
	TriangleIndices.Add(3);

	//	Face in negative X direction
	//	Built triangles CounterClockWise
	Positions.Add(FVector(-halfX,	halfY,		halfZ));
	Positions.Add(FVector(-halfX,	-halfY,		halfZ));
	Positions.Add(FVector(-halfX,	halfY,		-halfZ));
	Positions.Add(FVector(-halfX,	-halfY,		-halfZ));

	Normals.Add(-xNormal);
	Normals.Add(-xNormal);
	Normals.Add(-xNormal);
	Normals.Add(-xNormal);

	//	tri 3:
	TriangleIndices.Add(4);
	TriangleIndices.Add(5);
	TriangleIndices.Add(6);
	//	tri 4:
	TriangleIndices.Add(5);
	TriangleIndices.Add(7);
	TriangleIndices.Add(6);

	//	Face in positive Y direction
	//	Build triangles ClockWise
	Positions.Add(FVector(halfX,	halfY,		halfZ));
	Positions.Add(FVector(halfX,	halfY,		-halfZ));
	Positions.Add(FVector(-halfX,	halfY,		halfZ));
	Positions.Add(FVector(-halfX,	halfY,		-halfZ));

	Normals.Add(yNormal);
	Normals.Add(yNormal);
	Normals.Add(yNormal);
	Normals.Add(yNormal);

	//	tri 5:
	TriangleIndices.Add(8);
	TriangleIndices.Add(10);
	TriangleIndices.Add(9);
	//	tri 6:
	TriangleIndices.Add(9);
	TriangleIndices.Add(10);
	TriangleIndices.Add(11);

	//	Face in negative Y direction
	//	Built triangles CounterClockWise
	Positions.Add(FVector(-halfX,	-halfY,		-halfZ));
	Positions.Add(FVector(-halfX,	-halfY,		halfZ));
	Positions.Add(FVector(halfX,	-halfY,		-halfZ));
	Positions.Add(FVector(halfX,	-halfY,		halfZ));

	Normals.Add(-yNormal);
	Normals.Add(-yNormal);
	Normals.Add(-yNormal);
	Normals.Add(-yNormal);

	//	tri 7:
	TriangleIndices.Add(12);
	TriangleIndices.Add(13);
	TriangleIndices.Add(14);
	//	tri 8:
	TriangleIndices.Add(13);
	TriangleIndices.Add(15);
	TriangleIndices.Add(14);

	//	Face in positive Z direction
	//	Built triangles CounterClockWise
	Positions.Add(FVector(halfX,	halfY,		halfZ));
	Positions.Add(FVector(halfX,	-halfY,		halfZ));
	Positions.Add(FVector(-halfX,	halfY,		halfZ));
	Positions.Add(FVector(-halfX,	-halfY,		halfZ));

	Normals.Add(zNormal);
	Normals.Add(zNormal);
	Normals.Add(zNormal);
	Normals.Add(zNormal);

	//	tri 9:
	TriangleIndices.Add(16);
	TriangleIndices.Add(17);
	TriangleIndices.Add(18);
	//	tri 10:
	TriangleIndices.Add(17);
	TriangleIndices.Add(19);
	TriangleIndices.Add(18);

	//	Face in negative Z direction
	//	Build triangles ClockWise
	Positions.Add(FVector(halfX,	halfY,		-halfZ));
	Positions.Add(FVector(halfX,	-halfY,		-halfZ));
	Positions.Add(FVector(-halfX,	halfY,		-halfZ));
	Positions.Add(FVector(-halfX,	-halfY,		-halfZ));

	Normals.Add(-zNormal);
	Normals.Add(-zNormal);
	Normals.Add(-zNormal);
	Normals.Add(-zNormal);

	//	tri 11:
	TriangleIndices.Add(20);
	TriangleIndices.Add(22);
	TriangleIndices.Add(21);
	//	tri 12:
	TriangleIndices.Add(21);
	TriangleIndices.Add(22);
	TriangleIndices.Add(23);

}


