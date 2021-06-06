// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "MyTankPalyerController.h"


// Called when the game starts or when spawned
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto controlledTank = GetTank();
	UE_LOG(LogTemp, Warning, TEXT("Tank being used by AI controller: %s"), *controlledTank->GetName());

	auto playerTank = GetPlayerTank();
	UE_LOG(LogTemp, Warning, TEXT("AI controller following player Tank: %s"), *playerTank->GetName());
}


// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank()) {
		GetTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}

}

ATank* ATankAIController::GetTank() const {
	return Cast<ATank>(GetPawn());

}

ATank* ATankAIController::GetPlayerTank() const {
	auto firstPlayerController = GetWorld()->GetFirstPlayerController();	
	auto tankPlayerController = Cast<AMyTankPalyerController>(firstPlayerController);

	if (!tankPlayerController) {
		return nullptr;
	}

	if (tankPlayerController) {
		return tankPlayerController->GetTank();
	}
	else {
		return nullptr;
	}
}