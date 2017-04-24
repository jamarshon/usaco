@echo off

SETLOCAL

SET sourceFile=%~1
SET inputFile=%~2
SET outputFile=%~3

ECHO "g++ " %sourceFile% " < " %inputFile% " > " %outputFile%
g++ %sourceFile% -std=c++11 -o test

IF "%outputFile%"=="" ( 
	GOTO Run
) ELSE (
	GOTO RunWrite
)

:Run
	echo "Result"
	test < %inputFile% 
GOTO:EOF

:RunWrite
	echo "Wrote to File!"
	test < %inputFile% > %outputFile%
GOTO:EOF
