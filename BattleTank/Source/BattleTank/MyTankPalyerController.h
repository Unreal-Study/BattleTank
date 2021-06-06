// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "MyTankPalyerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API AMyTankPalyerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATank* GetTank() const;

	void AimAtCrosshair();

	bool GetSightRayHitLocation(FVector& outHitLocation) const;

private:

	UPROPERTY(EditAnywhere)
	float CrossHairXScreenLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYScreenLocation = 0.33333333333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000; //10 kilometers in cm
	
	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutWorldDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
