# Nome do arquivo de origem e do executável
$SourceFile = "cli.c"
$MainFile = "main.c"
$ExecutableName = "jacule"

# Local de instalação do executável
$InstallPath = "C:/MinGW/bin"

# Verifica se o MinGW está instalado e instala se necessário
if (-not (Test-Path "C:/MinGW/bin/gcc.exe")) {
    Set-ExecutionPolicy Bypass -Scope Process -Force
    [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072
    iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))
    choco install mingw -y
}

# Adiciona o MinGW ao PATH se ainda não estiver
$env:Path = [System.Environment]::GetEnvironmentVariable("Path", "Machine")
if (-not ($env:Path -like "*C:\MinGW\bin*")) {
    [System.Environment]::SetEnvironmentVariable("Path", $env:Path + ";C:\MinGW\bin", "Machine")
}

# Compilando o programa
$gccPath = "C:/MinGW/bin/gcc.exe"
& $gccPath -o "$ExecutableName" $MainFile $SourceFile

# Verifica se a compilação foi bem-sucedida
if ($LastExitCode -eq 0) {
    Write-Host "Compilação bem-sucedida. Instalando o programa..."

    # Movendo o executável para o diretório de instalação
    Move-Item -Path ".\$ExecutableName" -Destination $InstallPath

    # Dando permissão de execução (não necessário no Windows, mas mantido por coerência)
    & icacls "$InstallPath\$ExecutableName" /grant Everyone:F

    Write-Host "Instalação concluída. Você pode agora executar o comando '$ExecutableName' de qualquer lugar no sistema."
} else {
    Write-Host "Erro: A compilação falhou. Verifique o código e tente novamente."
}
