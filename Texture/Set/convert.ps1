
$files = Get-Item *.png, *jpg
$mlValue = Read-Host "ミップレベルの設定をしてください :"

foreach($f in $files){
    Start-Process -FilePath TL2TextureConverter.exe -ArgumentList "$f -ml $mlValue" -Wait
}


