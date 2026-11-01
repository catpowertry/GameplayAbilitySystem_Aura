// SixCatCompany.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"
class UAuraAbilitySystemComponent;
class UInputMappingContext;
class UInputAction;
class IEnemyInterface;
class UAuraInputConfig;
class USplineComponent;
struct FGameplayTag;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	AAuraPlayerController();
	
	UAuraAbilitySystemComponent* GetAuraAbilityComponent()  ;
	
protected:
	
	virtual void BeginPlay() override;
	virtual void PlayerTick( float DeltaTime ) override;
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditAnywhere,Category="MappingContext")
    TObjectPtr<UInputMappingContext> AuraMappingContext;
	
	UPROPERTY(EditAnywhere,Category="MoveAction|InputAction")
	TObjectPtr<UInputAction> MoveAction;
	
	void Move(const FInputActionValue& InputActionValue);
	
	void CursorTrace();
	
	FHitResult CursorHit;
	
	IEnemyInterface* LastActor;
	IEnemyInterface* CurrentActor;
	
	void AbilityInputPressed(FGameplayTag Tag);
	
	void AbilityInputReleased(FGameplayTag Tag);
	
	void AbilityInputHeld(FGameplayTag Tag);
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UAuraInputConfig> InputConfig;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAuraAbilitySystemComponent> ASC;
	
	
	/*
	 * CurserMove
	 */
public:
	FVector CachedLocation = FVector::ZeroVector;
	
	float FollowTime = 0.f;
	
	bool bIsAutoRunning = false;
	
	float ShortPressedTime = 0.5f;
	
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadios = 20.f;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;
};
