// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTankPalyerController.h"
#include "Tank.h"


ATank* AMyTankPalyerController::GetTank() const{
	return Cast<ATank>(GetPawn());

}

// Called when the game starts or when spawned
void AMyTankPalyerController::BeginPlay()
{
	Super::BeginPlay();
	auto controlledTank = GetTank();
	UE_LOG(LogTemp, Warning, TEXT("Tank being used by Player controller: %s"), *controlledTank->GetName());
}

// Called every frame
void AMyTankPalyerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshair();
}


void AMyTankPalyerController::AimAtCrosshair() {

	if (!GetTank()) { return; }
	FVector HitLocation;

	GetSightRayHitLocation(HitLocation);

	/*UE_LOG(LogTemp, Warning, TEXT("hitLocation: %s"), *HitLocation.ToString());*/

}

bool AMyTankPalyerController::GetSightRayHitLocation(FVector& outHitLocation) const{
	
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	auto ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXScreenLocation, ViewPortSizeY * CrossHairYScreenLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		GetLookVectorHitLocation(LookDirection, outHitLocation);
		GetTank()->AimAt(outHitLocation);
	}	

	return false;
}

bool AMyTankPalyerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const{
	
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	)) {
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false;
}

bool AMyTankPalyerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutWorldDirection) const{
	
	FVector CameraWorldLocation;	
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		OutWorldDirection);
}





