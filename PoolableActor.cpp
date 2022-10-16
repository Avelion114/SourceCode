
#include "PoolableActor.h"
#include "ActorPool.h"

// Sets default values
APoolableActor::APoolableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void APoolableActor::BeginPlay()
{
	Super::BeginPlay();
  
  //Set this actor's lifespan to the set lifespan defined by the owning Actor Pool
	AActorPool* OwningPool = Cast<AActorPool>(GetOwner());
	if (OwningPool)
	{
		MaxLifeSpan = OwningPool->LifeSpan;
	}


}

// Called every frame
void APoolableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

  //Check whether this actor has been alive longer than it's defined lifespan
	if (Active && MaxLifeSpan > 0.0f)
	{
		CurrentLifeSpan += DeltaTime;
	}
	if (CurrentLifeSpan > MaxLifeSpan)
	{
		Kill();
	}
}

void APoolableActor::Kill()
{
	AActorPool* OwningPool = Cast<AActorPool>(GetOwner());
	if (OwningPool)
	{
		CurrentLifeSpan = 0;
		OwningPool->PushActor(this);
	}
}

