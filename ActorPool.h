// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolableActor.h"
#include "Delegates/Delegate.h"
#include "ActorPool.generated.h"

UCLASS()
class SANDBOX_API AActorPool : public AActor
{
	GENERATED_BODY()


public:


	// Sets default values for this actor's properties
	AActorPool();

//Poolable actor to be spawned
	UPROPERTY(EditAnywhere, Category = "Actor")
		TSubclassOf<APoolableActor> PooledActor;

	UPROPERTY(EditAnywhere, Category = "Actor")
		int32 SpawnCount = 5;

	UPROPERTY(EditAnywhere, Category = "Actor")
		float LifeSpan = 3.0f;

//Time between allowed spawns if on a timer
	float cooldown = 0.0f;
  
	UPROPERTY(EditAnywhere, Category = "Actor")
		bool ActorShouldSimulatePhysics;

	UPROPERTY()
		UPrimitiveComponent* Root;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

//Array to hold actors
	UPROPERTY()
		TArray<APoolableActor*> Pool;
	//TQueue<APoolableActor*> Pool;

	int32 NumElements;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PushActor(APoolableActor* NewActor);
	virtual APoolableActor* PopActor(FVector Location, FRotator Rotation);
	void SetActorPhysics(APoolableActor* NewActor, bool bSimulate);
	bool IsEmpty();
	int32 ActorCount();
	void Activate();
	TArray<APoolableActor*>& GetPool();
	void DeActivate();

};
