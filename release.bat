@echo off

set pwd=%~dp0

:copy /y %pwd%\src\tables\*h %pwd%\debug\win64\sdk\gorm_tables\codes
:copy /y %pwd%\src\tables\*cc %pwd%\debug\win64\sdk\gorm_tables\codes

copy /y %pwd%\src\common\*h %pwd%\..\gorm_lib\src\include
copy /y %pwd%\src\client\*h %pwd%\..\gorm_lib\src\include

copy /y %pwd%\src\common\*cc %pwd%\..\gorm_lib\src\client
copy /y %pwd%\src\client\*cc %pwd%\..\gorm_lib\src\client

:copy /y %pwd%\src\common\*cc %pwd%\debug\win64\sdk\src
:copy /y %pwd%\src\client\*cc %pwd%\debug\win64\sdk\src

:copy /y  %pwd%\win64\gorm_client\Debug\gorm_client.lib %pwd%\debug\win64\sdk\lib
:copy /y  %pwd%\win64\gorm_client\Debug\gorm_client.pdb %pwd%\debug\win64\sdk\lib