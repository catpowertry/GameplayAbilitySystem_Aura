// SixCatCompany.


#include "Aura/Data/AuraDataAsset.h"

FAuraAttributeInfo UAuraDataAsset::FindAttributeInfo(FGameplayTag TargetTag, bool bLogNotFound)
{
for (auto &Info: AuraAttributesList)
 	{
 		if (Info.AttributeTag == TargetTag)
 		{
 			return Info;	
 		}
 		
 		if (bLogNotFound)
         		{
         		UE_LOG(LogTemp,Warning,TEXT("Can't find Info [%s] in the data asset [%s]"),*Info.AttributeTag.ToString(),*Info.AttributeName.ToString())
         		return FAuraAttributeInfo();
         		}
 	} 
 	
 	return FAuraAttributeInfo();
}
