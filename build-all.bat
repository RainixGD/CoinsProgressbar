@echo off
echo Starting ALL builds...

call build-windows.bat
call build-android32.bat
call build-android64.bat

echo Creating merge folder...
mkdir merge

echo Copying files into merge...
copy .\build\rainixdev.coinsprogressbar.geode .\merge\rainixdev.coinsprogressbar.geode
copy .\build-android32\rainixdev.coinsprogressbar.geode .\merge\android32.geode
copy .\build-android64\rainixdev.coinsprogressbar.geode .\merge\android64.geode

echo Running geode package...
geode package merge .\merge\rainixdev.coinsprogressbar.geode .\merge\android32.geode .\merge\android64.geode

del .\merge\android32.geode
del .\merge\android64.geode

echo All done!
pause