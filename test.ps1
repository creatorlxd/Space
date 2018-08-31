if ($CONFIGURATION -eq "Debug")
{
	exit 0
}
if ($CONFIGURATION -eq "Release")
{
	exit 0
}
if ($PLATFORM -eq "x64") {
	cmd /c copy .\x64\%CONFIGURATION%\UnitTest.exe .\Source\UnitTest\UnitTest\UnitTest%CONFIGURATION%x64.exe 
	cmd /c .\Source\UnitTest\UnitTest\UnitTest%CONFIGURATION%x64.exe -all
	exit $LASTEXITCODE
}
else 
{
	cmd /c copy .\%CONFIGURATION%\UnitTest.exe .\Source\UnitTest\UnitTest\UnitTest%CONFIGURATION%.exe
	cmd /c .\Source\UnitTest\UnitTest\UnitTest%CONFIGURATION%.exe -all
	exit $LASTEXITCODE
}