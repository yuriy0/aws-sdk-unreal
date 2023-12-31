﻿// Copyright Out-of-the-Box Plugins 2018-2024. All Rights Reserved.

#include "AwsLogger.h"

Aws::Utils::Logging::LogLevel FUnrealLogger::GetLogLevel() const
{
	// We want to gather as much log information as possible, we will filter it out in LogInternalMessage.
	return Aws::Utils::Logging::LogLevel::Trace;
}

void FUnrealLogger::Log(Aws::Utils::Logging::LogLevel logLevel, const char* tag, const char* formatStr, ...)
{
	// TODO: Check this is working as intended
	TAnsiStringBuilder<256> MessageBuilder;

	va_list Args;
	va_start(Args, formatStr);
	MessageBuilder.AppendV(formatStr, Args);
	va_end(Args);

	const FString MessageTag = UTF8_TO_TCHAR(tag);

	LogInternalMessage(logLevel, MessageTag, *MessageBuilder);
}

void FUnrealLogger::LogStream(Aws::Utils::Logging::LogLevel logLevel, const char* tag, const Aws::OStringStream& messageStream)
{
	const FString MessageLog = UTF8_TO_TCHAR(messageStream.str().c_str());
	const FString MessageTag = UTF8_TO_TCHAR(tag);

	LogInternalMessage(logLevel, MessageTag, MessageLog);
}

void FUnrealLogger::Flush()
{
	if (GLog)
	{
		GLog->Flush();
	}
}

void FUnrealLogger::LogInternalMessage(Aws::Utils::Logging::LogLevel Verbosity, const FString& Tag, const FString& Message)
{
	// TODO: Create our own log category
	switch (Verbosity)
	{
	case Aws::Utils::Logging::LogLevel::Fatal:
		{
			UE_LOG(LogTemp, Fatal, TEXT("[AWS-SDK] %s %s"), *Tag, *Message);
			return;
		}
	case Aws::Utils::Logging::LogLevel::Error:
		{
			UE_LOG(LogTemp, Error, TEXT("[AWS-SDK] %s %s"), *Tag, *Message);
			return;
		}
	case Aws::Utils::Logging::LogLevel::Warn:
		{
			UE_LOG(LogTemp, Warning, TEXT("[AWS-SDK] %s %s"), *Tag, *Message);
			return;
		}
	case Aws::Utils::Logging::LogLevel::Info:
		{
			UE_LOG(LogTemp, Display, TEXT("[AWS-SDK] %s %s"), *Tag, *Message);
			return;
		}
	case Aws::Utils::Logging::LogLevel::Debug:
		{
			UE_LOG(LogTemp, Verbose, TEXT("[AWS-SDK] %s %s"), *Tag, *Message);
			return;
		}
	case Aws::Utils::Logging::LogLevel::Trace:
		{
			UE_LOG(LogTemp, VeryVerbose, TEXT("[AWS-SDK] %s %s"), *Tag, *Message);
			return;
		}
	default:
		{
			checkNoEntry();
		}
	}
}
