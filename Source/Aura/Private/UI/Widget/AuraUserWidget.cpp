// SixCatCompany.


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* WidgetControllerObject)
{
	WidgetController = WidgetControllerObject;
	WidgetControllerSet();
}
