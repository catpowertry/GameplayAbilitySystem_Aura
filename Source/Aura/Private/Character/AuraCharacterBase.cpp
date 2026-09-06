// SixCatCompany.


#include "Character/AuraCharacterBase.h"

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
