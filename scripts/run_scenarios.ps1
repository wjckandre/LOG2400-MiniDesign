# Run scenarios for MiniDesign and save outputs
# Usage: run from repository root by PowerShell

Set-Location -Path (Split-Path -Parent $MyInvocation.MyCommand.Definition)
# move to project root
Set-Location ..

Write-Output "Compiling..."
g++ -std=c++11 -I src src/*.cpp -O2 -Wall -Wextra -o MiniDesign.exe

# Scenario 1
Write-Output "Running scenario 1..." | Out-File -FilePath scripts/output_scenario1.txt -Encoding utf8
# Commands: a (list), o1 (texture grid), o2 (id grid), f (make a nuage), then c1, c2, q
@("a","o1","o2","f","0 1","c1","c2","q") -join "`n" | .\MiniDesign.exe "(5,0) (14,16) (23,0) (0,8) (0,0) (28,8)" | Out-File -FilePath scripts/output_scenario1.txt -Append -Encoding utf8

# Scenario 2
Write-Output "Running scenario 2..." | Out-File -FilePath scripts/output_scenario2.txt -Encoding utf8
@("a","o1","o2","f","0 1 2","c1","c2","q") -join "`n" | .\MiniDesign.exe "(2,0) (28,8) (28,0) (2,8) (15,16)" | Out-File -FilePath scripts/output_scenario2.txt -Append -Encoding utf8

Write-Output "Done. Outputs written to scripts/output_scenario1.txt and scripts/output_scenario2.txt"
