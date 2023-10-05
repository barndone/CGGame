// Fill out your copyright notice in the Description page of Project Settings.


#include "CGGamePickup.h"

// Sets default values
ACGGamePickup::ACGGamePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	RootComponent = PickupMesh;

}

// Called when the game starts or when spawned
void ACGGamePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACGGamePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

