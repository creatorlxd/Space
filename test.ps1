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
	$result = cmd /c .\Source\UnitTest\UnitTest\UnitTest%CONFIGURATION%x64.exe -all
	if($result.HasSuccessed)
	{
		exit 0
	}
	else
	{
		exit -1	
	}
}
else 
{
	cmd /c copy .\%CONFIGURATION%\UnitTest.exe .\Source\UnitTest\UnitTest\UnitTest%CONFIGURATION%.exe
	$result = cmd /c .\Source\UnitTest\UnitTest\UnitTest%CONFIGURATION%.exe -all
	if($result.HasSuccessed)
	{
		exit 0
	}
	else
	{
		exit -1	
	}
}