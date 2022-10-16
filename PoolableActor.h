// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolableActor.generated.h"

UCLASS()
class SANDBOX_API APoolableActor : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APoolableActor();

//This actor should be visible and active in the environment
	bool Active = false;
  
//Used for tracking lifespan of actor. Set by owning ActorPool
	float MaxLifeSpan = 3.0f;
	float CurrentLifeSpan = 0.0f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//Destroy proxy
	virtual void Kill();

};
