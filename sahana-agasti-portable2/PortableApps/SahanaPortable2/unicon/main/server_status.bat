mode con:cols=61 lines=35
TITLE UNIFORM SERVER - Server Status 5.3-Nano
COLOR B0
@echo off
cls
rem ###################################################
rem # Name: server_status.bat
rem # Created By: The Uniform Server Development Team
rem # Edited Last By: Mike Gleaves (ric)
rem # V 1.0 6-10-2009
rem ##################################################

rem ### working directory current folder 
pushd %~dp0

..\..\usr\local\php\php.exe server_status.php

pause

rem ### restore original working directory
popd
EXIT