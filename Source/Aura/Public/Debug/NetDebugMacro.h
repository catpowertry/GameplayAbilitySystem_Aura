#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


/*
 *
 * do while(0)的作用是将宏定义包装在一个do while循环中，这样可以确保宏在使用时表现得像一个单独的语句块。它有几个主要的作用：
 * 1. 语法安全性：使用do while(0)可以确保宏在使用时不会引起语法错误。即使宏中包含多条语句，也可以将它们包装在一个单独的语句块中，避免了潜在的语法问题。
 * 2. 控制流一致性：使用do while(0)可以确保宏在使用时的控制流一致性。无论宏在何处被调用，它都会被视为一个单独的语句块，从而避免了潜在的控制流问题。
 * 3. 可读性和可维护性：使用do while(0)可以提高代码的可读性和可维护性。它明确地表明宏的作用范围，并且使代码结构更加清晰，便于理解和维护。
 */
#define NET_LOG(Fmt,...)  do{\
	UE_LOG(LogTemp,Warning,TEXT("[%s] NetMode:%d,Authority:%d,Role:%d,LocalController:%d |", Fmt),\
	*GetName(),(int32)GetNetMode(),(int32)HasAuthority(),(int32)GetLocalRole(),(int32)IsLocalController(),##__VA_ARGS__);\
	}\
while(0)