#include "Character/AuraEnemy.h"
#include "Aura/Aura.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

void AAuraEnemy::HighLightActor()
{
	check(GetMesh());
	GetMesh()->SetRenderCustomDepth(true);
	//在Aura.h中定义了CUSTOM_DEPTH_RED宏，自定义了深度模板值为250
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
}

void AAuraEnemy::UnhighLightActor()
{
	check(GetMesh());
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AAuraEnemy::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAuraEnemy,EnemyLevel);
}

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	
	AbilitySystemComponent=CreateDefaultSubobject<UAuraAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AttributeSet=CreateDefaultSubobject<UAuraAttributeSet>(TEXT("AttributeSet"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

void AAuraEnemy::InitAbilityInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->InitAbilityActorInfoSet();
}

int32 AAuraEnemy::GetPlayerLevel() const
{
	return EnemyLevel;
}


/*
 *敌人等级在服务器端变化出发函数（可能存在预测）
 */
void AAuraEnemy::OnRep_EnemyLevel(int32 OldLevel)
{
	
}
