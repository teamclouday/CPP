param ($cppversion="20")
$BuildPath = "build"
if (-not (Test-Path -Path $BuildPath))
{
    New-Item $BuildPath -ItemType Directory
}
Set-Location $BuildPath
& "cmake.exe" ".." "-DCMAKE_CXX_FLAGS=/std:c++$cppversion"
& "cmake.exe" "--build" "." "--config" "Release"
Set-Location ..
Write-Host "==========="
Write-Host " Executing"
Write-Host "==========="
& ".\bin\run.exe"