if exist .\..\OUTPUT\*.hex (.\..\Binary\hex2bin.exe  .\..\OUTPUT\*.hex )
if exist .\..\OUTPUT\*.hex (.\..\Binary\hex2dfu.exe -t  .\..\OUTPUT\*.hex )
pause