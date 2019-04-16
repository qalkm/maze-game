@echo off

IF "%PROCESSOR_ARCHITECTURE%"=="x86" (
    start ./ansicon/x86/ansicon.exe a.exe
) ELSE (
    start ./ansicon/x64/ansicon.exe a.exe
)

