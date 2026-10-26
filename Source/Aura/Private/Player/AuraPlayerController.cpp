// SixCatCompany.


#include "Player/AuraPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Aura/Public/Interaction/EnemyInterface.h"
#include "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
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
	InputModeData.SetHideCursorDuringCapture(true);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(InputComponent);
	
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
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false ,CursorHit);
	if (!CursorHit.bBlockingHit)return;
	
	LastActor=CurrentActor;
	CurrentActor=Cast<IEnemyInterface>(CursorHit.GetActor());
	/**
	 * A:CurrentActor==Null && LastActor==Null
	 * -Doing Nothing
	 * B:CurrentActor is Valid && LastActor is Null
	 * -HighLight CurrentActor
	 * C:CurrentActor is Null && LastActor is Valid
	 * -UnhighLight LastActor
	 * D:CurrentActor is Valid && LastActor is Valid
	 * -If CurrentActor != LastActor
	 * -UnhighLight LastActor
	 * -HighLight CurrentActor
	 * -If CurrentActor==LastActor
	 * -Doing Nothing
	 */
	if (CurrentActor==nullptr)
	{
		if (LastActor==nullptr)
		{
			return;
		}
		else
		{
			LastActor->UnhighLightActor();
		}
	}
	else //CurrentActor is Valid
	{
		if (LastActor==nullptr)
		{
			CurrentActor->HighLightActor();
		}
		else
		{
			if (CurrentActor!=LastActor)
			{
				LastActor->UnhighLightActor();
				CurrentActor->HighLightActor();
			}
			else
			{
				return;
			}
		}
	}
}
