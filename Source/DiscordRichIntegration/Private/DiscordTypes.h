// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Misc/Paths.h"
#include "Containers/UnrealString.h"

// Easy access function to get the plugins settings file
inline FString GetIniName() { return FString::Printf(TEXT("%sDefaultPlugins.ini"), *FPaths::SourceConfigDir()); }
