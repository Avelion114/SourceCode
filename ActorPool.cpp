// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorPool.h"


// Sets default values
AActorPool::AActorPool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

}

// Called when the game starts or when spawned
void AActorPool::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

  //USE WHEN SETTING SPAWN ON TIMER
	/*cooldown += DeltaTime;

	if (cooldown >= 2.0f)
	{
		cooldown = 0.0f;
		PopActor(GetActorLocation(), GetActorRotation());
	*/}

}

void AActorPool::PushActor(APoolableActor* NewActor)
{

  //Deactivate actor and remove physics
	NewActor->Active = false;
	NewActor->SetActorEnableCollision(false);
	NewActor->SetActorLocation(GetActorLocation());
	NewActor->SetActorScale3D({ 0.0f,0.0f,0.0f });
	SetActorPhysics(NewActor, false);
  
  //Insert actor into pool
	Pool.Push(NewActor);
}

APoolableActor* AActorPool::PopActor(FVector Location, FRotator Rotation)
{
	if (!(Pool.Num() <= 0))
	{
		auto IT = Pool.begin();

		APoolableActor* NewActor;
		NewActor = *IT;
		Pool.RemoveAt(0);
    
    //Enable phyiscs and activate actor
		NewActor->SetActorScale3D({ 1.0f,1.0f,1.0f });
		NewActor->SetActorEnableCollision(true);
		NewActor->SetActorLocation(Location);
		NewActor->SetActorRotation(Rotation);
		SetActorPhysics(NewActor, true);
		NewActor->Active = true;
    
		return NewActor;
	}
	else
	{
		return nullptr;
	}
}

void AActorPool::SetActorPhysics(APoolableActor* NewActor, bool bSimulate)
{
  //Determine if we need to set physics for the actor or not
	if (ActorShouldSimulatePhysics)
	{
		Root = Cast<UPrimitiveComponent>(NewActor->GetRootComponent());
		if (Root)
		{
			Root->SetSimulatePhysics(bSimulate);
		}
	}
}

bool AActorPool::IsEmpty()
{
	return Pool.Num() <= 0;
}

int32 AActorPool::ActorCount()
{
	return Pool.Num();
}

//Activate the new pool based on the assigned actor to store. This is used so actors are only spawned when needed and the pool is activated.
void AActorPool::Activate()
{
	if (PooledActor)
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		Params.Owner = this;
		for (int i = 0; i < SpawnCount; i++)
		{
			APoolableActor* NewActor = GetWorld()->SpawnActor<APoolableActor>(PooledActor, GetActorLocation(), GetActorRotation(), Params);
			if (NewActor)
			{
				PushActor(NewActor);
			}
		}
	}
}

TArray<APoolableActor*>& AActorPool::GetPool()
{
	return Pool;
}


//Destroy all actors assigned to this pool
void AActorPool::DeActivate()
{
	for (auto i : Children)
	{
		i->Destroy();
	}
}




