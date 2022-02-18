param ($cppversion="14")
$BuildPath = "build"
if (-not (Test-Path -Path $BuildPath))
{
    New-Item $BuildPath -ItemType Directory
}
Start-Process -NoNewWindow -Wait -FilePath "cmake.exe" -WorkingDirectory $BuildPath -ArgumentList "..","-DCMAKE_CXX_FLAGS=/std:c++$cppversion"
Start-Process -NoNewWindow -Wait -FilePath "cmake.exe" -WorkingDirectory $BuildPath -ArgumentList "--build",".","--config","Release"
Write-Host "==========="
Write-Host " Executing"
Write-Host "==========="
Start-Process -NoNewWindow -Wait -FilePath ".\bin\run.exe"