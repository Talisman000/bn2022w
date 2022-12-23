Param(
    [parameter(mandatory)][string]$name = "WordData"
)
function Main {
    flatc -o $PSScriptRoot/../resources/ --binary $PSScriptRoot/WordData.fbs $PSScriptRoot/../resources/$name.json 
    flatc -o $PSScriptRoot/../include/ --cpp $PSScriptRoot/WordData.fbs
}

Main