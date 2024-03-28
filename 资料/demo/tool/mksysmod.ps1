# Powershell Script

foreach ($header in $args) {
    g++ -std=c++23 -fmodules-ts -xc++-system-header $header
}
