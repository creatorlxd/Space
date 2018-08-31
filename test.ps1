if ($PLATFORM == "x64") {
	cmd /c copy .\x64\%CONFIGURATION%\UnitTest.exe .\Source\UnitTest\UnitTest\UnitTest%CONFIGURATION%x64.exe 
	cmd /c .\Source\UnitTest\UnitTest\UnitTest%CONFIGURATION%x64.exe -all
}
else {
	cmd /c copy .\%CONFIGURATION%\UnitTest.exe .\Source\UnitTest\UnitTest\UnitTest%CONFIGURATION%.exe
	cmd /c .\Source\UnitTest\UnitTest\UnitTest%CONFIGURATION%.exe -all
}