// SixCatCompany.


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTag.h"
#include "Aura/Public/Debug/NetDebugMacro.h"
#include "EnhancedInputComponent.h"
#include "Aura/Public/Interaction/EnemyInterface.h"
#include "GameplayTagContainer.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Input/AuraInputComponent.h"
#include "Components/SplineComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetAuraAbilityComponent() 
{
	if (ASC == nullptr)
	{
		ASC = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	};
	
	return ASC;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraMappingContext);
	//获取增强输入本地玩家子系统用于绑定输入映射情景在BeginPlay设置的原因是LocalPlayer还没有准备好无法获取到LocalPlayer
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem && AuraMappingContext)
	{
		Subsystem->AddMappingContext(AuraMappingContext, 0);
	}
	//因为是上帝视角所以需要默认显示鼠标并设置鼠标的样式
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	//设置输入模式
	FInputModeGameAndUI  InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	
	if (bIsAutoRunning == true)
	{
		if (APawn* ControllerPawn = GetPawn())
		{
			if (!Spline) return;
            const FVector Location = Spline->FindLocationClosestToWorldLocation(ControllerPawn->GetActorLocation(),ESplineCoordinateSpace::World);
            const FVector Direction = Spline->FindDirectionClosestToWorldLocation(Location,ESplineCoordinateSpace::World);
            NET_LOG(TEXT(""));
            ControllerPawn->AddMovementInput(Direction);
			NET_LOG(TEXT(""));
            const float DistanceToLocation = (Location-CachedLocation).Length();
            if (DistanceToLocation <= AutoRunAcceptanceRadios)
            {
            	bIsAutoRunning = false;
            }
		}
		
	}
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UAuraInputComponent* EnhancedInputComponent = Cast<UAuraInputComponent>(InputComponent);
	
	/*
	 *一个IA有三种状态按下，持续，松开分别触发
	 * 从InputActionConfig中拉出资产实现按键绑定
	 * 可使用而不是一直使用，类似Move 这种要一直使用的就需要专门绑定，而像技能释放这种释放次数不多所以就需要用这种资产方式绑定
	 */
	EnhancedInputComponent->BindAbilityActions(InputConfig , this ,&AAuraPlayerController::AbilityInputPressed,&ThisClass::AbilityInputReleased,&ThisClass::AbilityInputHeld);
	
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector=InputActionValue.Get<FVector2D>();
	const FRotator Rotation=GetControlRotation();
	const FRotator YawRotation(Rotation.Pitch,Rotation.Yaw,Rotation.Roll);
	
	const FVector ForwardDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	if (APawn* ControllerPawn=GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
	
}

/*
 *
 * 光标指向角色的光标指示修改
 * 高亮光改变
 */
void AAuraPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility,false ,CursorHit);
	if (!CursorHit.bBlockingHit)return;
	
	LastActor=CurrentActor;
	CurrentActor=Cast<IEnemyInterface>(CursorHit.GetActor());
	
	if (CurrentActor == LastActor)
	{
		return;
	}
	if (CurrentActor != LastActor)
	{
		if (CurrentActor) CurrentActor->HighLightActor();
		if (LastActor) LastActor->UnhighLightActor();
	}
}

void AAuraPlayerController::AbilityInputPressed(
FGameplayTag Tag)
{
	if (Tag != FAuraGameplayTags::Get().InputTag_LMB)
	{
		if (GetAuraAbilityComponent())
		{ 
			ASC->AbilityInputTagPressed(Tag);
		}
		return;
	}
	if (CurrentActor)
	{
		if (GetAuraAbilityComponent())
		{ 
			ASC->AbilityInputTagPressed(Tag);
		}
	}
	else
	{
		/*
		 *
		 * 从左键开始按下之后就开始执行，一直执行到松开按键，第一次开始获取到的为0
		 */
		FollowTime  += GetWorld()->GetDeltaSeconds();
		GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
		CachedLocation = CursorHit.ImpactPoint;
	}
}

void AAuraPlayerController::AbilityInputReleased(
FGameplayTag Tag)
{
	if (Tag != FAuraGameplayTags::Get().InputTag_LMB)
	{
		if (GetAuraAbilityComponent())
		{
        ASC->AbilityInputTagReleased(Tag);
        }
	}
	if (CurrentActor)
	{
		if (GetAuraAbilityComponent())
		{
			ASC->AbilityInputTagReleased(Tag);
		}
	}
	else
	{
		APawn* ControllerPawn = GetPawn();
		if (FollowTime <= ShortPressedTime && ControllerPawn)
		{
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this,ControllerPawn->GetActorLocation(),CachedLocation))
			{
				Spline->ClearSplinePoints();
				for (const FVector& PathPoint : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PathPoint,ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(),PathPoint,20.f,12,FColor::Red,true,5.f);
				}
				CachedLocation = NavPath->PathPoints[NavPath->PathPoints.Num()-1];
				bIsAutoRunning = true;
			}
			FollowTime = 0.f;
		}
		
	}
	
	
}

void AAuraPlayerController::AbilityInputHeld(
FGameplayTag Tag)
{
	if (Tag != FAuraGameplayTags::Get().InputTag_LMB)
	{
		if (GetAuraAbilityComponent())
		{ 
			ASC->AbilityInputTagHeld(Tag);
		}
		return;
	}
	if (CurrentActor)
	{
		if (GetAuraAbilityComponent())
        { 
        	ASC->AbilityInputTagHeld(Tag);
        }
	}
	else
	{
        GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
        CachedLocation = CursorHit.ImpactPoint;
        if (APawn* SelfPawn = GetPawn())
        {
        	const FVector WorldVector = (CachedLocation - SelfPawn->GetActorLocation()).GetSafeNormal();
	        SelfPawn->AddMovementInput(WorldVector);
        }
	}
}
