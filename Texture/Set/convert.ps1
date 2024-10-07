
$files = Get-Item *.jpg
foreach($f in $files){
    Start-Process -FilePath TL2TextureConverter.exe -ArgumentList $f -Wait
}

