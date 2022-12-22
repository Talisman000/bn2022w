flatc -o $PSScriptRoot/../resources/ --binary $PSScriptRoot/WordData.fbs $PSScriptRoot/../resources/WordData.json 
flatc -o $PSScriptRoot/../include/ --cpp $PSScriptRoot/WordData.fbs