function LoadExcelSheet($excel, $filepath, $sheetName) {
    # Load excel file
    $book = $excel.Workbooks.Open($filepath, 0, $true)
    $sheet = $book.Worksheets.Item($sheetName)
    Write-Host "$sheetName を読み込みました！ (path: $filepath)　わーい！"
    return $sheet
}
function FindHeaderBegin($sheet, $name, $maxHeaderSize, $maxMonsterSize) {
    for ($i = 1; $i -lt $maxMonsterSize; $i++) {
        for($j = 1; $j -lt $maxHeaderSize; $j++){
            $cell = $sheet.Cells.Item($i, $j)
            if ($cell.Text -eq $name){
                return @($i, $j)
            }
        }
    }

}
function GetHeader($sheet, [int]$headerBeginColumn, [int]$maxHeaderSize) {
    $headers = @()
    for ($i = $headerBeginColumn; $i -lt $headerBeginColumn + $maxHeaderSize; $i++) {
        $cell = $sheet.Cells.Item($headerRaw, $i)
        # 空の場合ヘッダの最後尾を過ぎたとみなす
        # 空判定はvalue2をIsNullOrEmptyすればいいらしい
        if ([string]::IsNullOrEmpty($cell.value2)) {
            break
        }
        $headers += $cell.Text
    }
    Write-Host "ヘッダー情報を読み込みました！ ($headers) わーい！"
    return $headers
}

function GetMonsterList($sheet, $headers, $dataRawBegin, $dataColumnBegin, $maxMonsterSize) {
    # ゴリ押し実装です
    $monsterList = @()
    for ($i = $dataRawBegin; $i -lt $dataRawBegin + $maxMonsterSize; $i++) {
        $map = [ordered]@{}
        $check = $sheet.Cells.Item($i, $dataColumnBegin)
        # その行のラベル列が空の場合モンスターデータの最後尾を過ぎたとみなす
        if ([string]::IsNullOrEmpty($check.value2)) {
            break
        }
        for ($j = 0; $j -lt $headers.Count; $j++) {
            $cell = $sheet.Cells.Item($i, $j + $dataColumnBegin)
            $cellInt = 0
            $tryParse = [int]::TryParse($cell.Text, [ref]$cellInt)
            if ($tryParse) {
                $map.Add($headers[$j], $cellInt)
            }
            else {
                $map.Add($headers[$j], $cell.Text)
            }
        }
        $monsterList += $map
    }
    $monsterCount = $monsterList.Count
    Write-Host "モンスター情報を読み込みました！ (データ数: $monsterCount) わーい！"
    return $monsterList
}

# 以下のデータの仕様を想定する
# - ヘッダのサイズは可変。ヘッダの名前は変更される可能性がある
# - ヘッダの行にはヘッダ以外の情報は存在しない。最後の列以降は何も情報が無い
# - モンスターのサイズは可変。最後の行以降は何も情報が無い

function Main() {
    # config
    $filepathRelative = $PSScriptRoot + "\..\resources\word_db.xlsx"
    $sheetName = "Sheet1"
    $headerLabelBegin = "id"
    # $headerBeginColumn = 2
    # $headerRaw = 3
    $maxHeaderSize = 32
    $maxMonsterSize = 1024

    # Create excel object
    $excel = New-Object -ComObject Excel.Application
    # No visualize
    $excel.Visible = $false

    # Loading excel file needs absolute path
    $filepathAbsolute = (Get-ChildItem $filepathRelative).FullName
    $filepathWithoutExt = $filepathAbsolute.Substring(0, $filepathAbsolute.LastIndexOf('.'))
    $outputFilePath = $filepathWithoutExt + ".json"
    
    try {
        $sheet = LoadExcelSheet $excel $filepathAbsolute $sheetName
        $begin = FindHeaderBegin $sheet $headerLabelBegin $maxHeaderSize $maxMonsterSize
        $headerRaw = $begin[0]
        $headerBeginColumn = $begin[1]
        $headers = GetHeader $sheet $headerBeginColumn $maxHeaderSize
        $monsterList = GetMonsterList $sheet $headers $($headerRaw + 1) $headerBeginColumn $maxMonsterSize

        $json_obj = @{
            "word_list" = $monsterList
        }

        ConvertTo-Json $json_obj | Out-File $outputFilePath
        Write-Host "データを保存しました！ (path: $outputFilePath) わーい！" 
    }
    catch {
        $errorMessage = $_.Exception.Message
        $errorMessage
    }
    finally {
        $excel.Quit()
    }
    
}

Main
[System.GC]::Collect()
