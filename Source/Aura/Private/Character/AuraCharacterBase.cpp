// SixCatCompany.


#include "Character/AuraCharacterBase.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Player/AuraPlayerState.h"


// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
Weapon->SetupAttachment(GetMesh(), FName("WeaponSocket"));
Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


/*
 *
 * 初始化一些数据类似AbilitySystemComponent
 */
void AAuraCharacterBase::InitAbilityInfo()
{
}

int32 AAuraCharacterBase::GetPlayerLevel() const
{
	return 0;
}

void AAuraCharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority()) return;
	
	UAuraAbilitySystemComponent* ASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	
	/*
	 *
	 * AbilitySystemComponent中初始化所有初始能力
	 */
}

