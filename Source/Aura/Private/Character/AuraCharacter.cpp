// SixCatCompany.


#include "Character/AuraCharacter.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Player/AuraPlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate=FRotator(0.f,400.f,0.f);
	//限制角色在二维平面上移动
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	/*
	 * 限定角色控制器转动方向
	 */
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}
void AAuraCharacter::InitAbilityInfo()
{
	AAuraPlayerState* AuraPlayerState=GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	/*
	 *
	 * 从PlayerState获取到ASC组件（ASC组件创建在PlayerState时不会销毁，ASC组件在角色的肉体上也创建了一个ASC组件方便调用）
	 */
	AbilitySystemComponent=AuraPlayerState->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	
	/**在角色中初始化
	 * 在应用游戏效果时触发的委托
	 * 主要为覆层OverlayWidget提供信息主要有，PlayerController，PlayerState，AbilitySystemComponent，AttributeSet
	 */
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->InitAbilityActorInfoSet();
	AttributeSet=AuraPlayerState->GetAttributeSet();
	if (AAuraPlayerController* PlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		if (AAuraHUD* HUD=Cast<AAuraHUD>(PlayerController->GetHUD()))
		{
			HUD->InitOverlay(PlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);
		}
		
	}
	
	/*
	 * 初始化角色默认游戏属性（使用Effect赋予角色属性）
	 */
	ApplyEffectToSelf(DefaultPrimaryEffect,1.f);
	ApplyEffectToSelf(DefaultSecondaryEffect,1.f);
	ApplyEffectToSelf(DefaultVitalEffect,1.f);
}

/*
 *
 * 将属性游戏效果应用到角色（一般是一些属性类型）
 */
void AAuraCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass, float Level) const
{
	if (!IsValid(EffectClass) || !AbilitySystemComponent) return;
		FGameplayEffectContextHandle Handle = AbilitySystemComponent->MakeEffectContext();
		const FGameplayEffectSpecHandle EffectHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass,Level,Handle);
		Handle.AddSourceObject(this);
	if (!EffectHandle.Data.Get())
    {
	    UE_LOG(LogTemp,Warning,TEXT("AuraCharacter:EffectHandle Are not valid!"));
    	return;  
    }
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectHandle.Data.Get());
}

/*
 * 获取到玩家等级（默认为零级）
 */
int32 AAuraCharacter::GetPlayerLevel() const
{
	const AAuraPlayerState* AuraPlayerState=GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetPlayerLevel();
}

/*
 *
 * 在不同的时间段触发角色的初始化
 * 
 */
void AAuraCharacter::PossessedBy(AController* PlayerController)
{
	Super::PossessedBy(PlayerController);
	//Init ability actor info in server
	InitAbilityInfo();
}


/*
 *玩家等级在服务器端变化出发函数（可能存在预测）
 */
void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//Init ability actor info in client
	InitAbilityInfo();
}
