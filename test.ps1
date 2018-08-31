# use for appveyor test
if ($CONFIGURATION -eq "Debug")
{
	Write-Output("debug")
	exit 0
}
if ($CONFIGURATION -eq "Release")
{
	Write-Output("release")
	exit 0
}
if ($PLATFORM -eq "x64") {
	Write-Output(%APPVEYOR_BUILD_FOLDER%\x64\%CONFIGURATION%\UnitTest.exe)
	cmd /c copy %APPVEYOR_BUILD_FOLDER%\x64\%CONFIGURATION%\UnitTest.exe %APPVEYOR_BUILD_FOLDER%\Source\UnitTest\UnitTest\UnitTest%CONFIGURATION%.exe 
	cmd /c %APPVEYOR_BUILD_FOLDER%\Source\UnitTest\UnitTest\UnitTest%CONFIGURATION%.exe -all
	exit $LASTEXITCODE
}
else 
{
	Write-Output(%APPVEYOR_BUILD_FOLDER%\%CONFIGURATION%\UnitTest.exe)
	cmd /c copy %APPVEYOR_BUILD_FOLDER%\%CONFIGURATION%\UnitTest.exe .%APPVEYOR_BUILD_FOLDER%\Source\UnitTest\UnitTest\UnitTest%CONFIGURATION%.exe
	cmd /c %APPVEYOR_BUILD_FOLDER%\Source\UnitTest\UnitTest\UnitTest%CONFIGURATION%.exe -all
	exit $LASTEXITCODE
}