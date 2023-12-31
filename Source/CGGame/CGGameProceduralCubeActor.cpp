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
		case MeshType::SPHERE:
			GenerateSphere();
			break;
	}

	ProceduralMesh->CreateMeshSection(
		0, 
		Positions, 
		TriangleIndices, 
		/*Normals*/TArray<FVector>(),
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
	//	Build triangles ClockWise so the rear faces are not visible 
	Positions.Add(FVector(halfX,	halfY,		halfZ));
	Positions.Add(FVector(halfX,	-halfY,		halfZ));
	Positions.Add(FVector(halfX,	halfY,		-halfZ));
	Positions.Add(FVector(halfX,	-halfY,		-halfZ));

	Normals.Add(-xNormal);
	Normals.Add(-xNormal);
	Normals.Add(-xNormal);
	Normals.Add(-xNormal);


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
	//	Build triangles ClockWise so the rear faces are not visible 
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
	//	Build triangles ClockWise so the rear faces are not visible 
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

void ACGGameProceduralCubeActor::GenerateSphere()
{
	//	calculate angle steps for horizontal and vertical slices
	float angleStepHorizontalDegrees = 360.0f / HorizontalSlices;
	float angleStepVerticalDegrees = 360.0f / VerticalSlices;

	//	convert to radians
	float horizontalAngleStepRad = FMath::DegreesToRadians(angleStepHorizontalDegrees);
	float verticalAngleStepRad = FMath::DegreesToRadians(angleStepVerticalDegrees);

	//	place the verts
	//	Vertically
	for (int i = 0; i < VerticalSlices / 2 + 1; i++)
	{
		//	horizontally
		for (int j = 0; j < HorizontalSlices / 2 + 1; j++)
		{
			//	 add the x, y, and z positions
			Positions.Add(
			FVector(
				SphereRadius * cos(j * horizontalAngleStepRad) * sin(i * verticalAngleStepRad),
				SphereRadius * sin(j * horizontalAngleStepRad) * sin(i * verticalAngleStepRad),
				SphereRadius * cos(i * verticalAngleStepRad)
			));
		}
	}


	//	generate tris
	//		TODO: helper method to generate tris given a bool for clockwise or counterclockwise
	GenerateTris();

}

void ACGGameProceduralCubeActor::GenerateTris()
{
	//
	/*
	  temp2 -- temp4
		|  \	|
		|   \   |
		|    \	|
	  temp3 -- temp

	*/

	for(int i = 0; i < Positions.Num(); i++)
	{
		int temp = i;
		int temp2 = temp + (HorizontalSlices / 2);
		int temp3 = temp + (HorizontalSlices / 2 + 1);
		auto temp4 = temp * HorizontalSlices * 2;
		
		TriangleIndices.Add(temp);
		TriangleIndices.Add(temp3);
		TriangleIndices.Add(temp2);

		TriangleIndices.Add(temp);
		TriangleIndices.Add(temp4);
		TriangleIndices.Add(temp2);

	}
}

