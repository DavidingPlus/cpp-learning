# Powershell Script

# 生成系统头文件的模块
# 启用的C++标准必须和应用构建启用的标准一样

echo "Generating system modules..."

del gcm.cache\D- /y

$headers = Get-Content -Path .\tool\syshdrs.txt

foreach ($header in $headers) {
    echo "--- $header"
    $args = "-std=c++23 -fmodules-ts -xc++-system-header $header"
    $gxx = Start-Process -FilePath "g++" -ArgumentList $args -PassThru -NoNewWindow -Wait
    $gxx.WaitForExit()
}

echo "Done. Please use 'tree gcm.cache' to check these modules."