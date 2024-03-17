// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}



void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TriggerComponent BeginPlay"));
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UE_LOG(LogTemp, Warning, TEXT("TriggerComponent TickComponent"));
	AActor* AcceptableActor = GetAcceptableActor();
	if (AcceptableActor != nullptr) {
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(AcceptableActor->GetRootComponent());
		if (Component != nullptr) {
			Component->SetSimulatePhysics(false);
			UE_LOG(LogTemp, Warning, TEXT("Uprimitive component was casted"));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Uprimitive component was unable to be casted"));
		}
		AcceptableActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		Mover->SetShouldMove(true);
	}
	else {
		Mover->SetShouldMove(false);
	}
	
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors_Array;
	GetOverlappingActors(Actors_Array);
	if (Actors_Array.Num() != 0) {
		for (int32 i = 0; i < Actors_Array.Num(); i++) {
			FString Actor_Names = Actors_Array[i]->GetActorNameOrLabel();
			if ( (Actors_Array[i]->ActorHasTag(AcceptableKey)) && !(Actors_Array[i]->ActorHasTag("Grabbed")) ) {
				return Actors_Array[i];
			}
		}
	}
	return nullptr;
}
