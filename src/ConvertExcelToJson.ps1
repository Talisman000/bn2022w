function LoadExcelSheet($filepath, $sheetName) {
    # Create excel object
    $excel = New-Object -ComObject Excel.Application
    # No visualize
    $excel.Visible = $false
    # Load excel file
    $book = $excel.Workbooks.Open($filepath, 0, $true)
    $sheet = $book.Worksheets.Item($sheetName)
    Write-Host "$sheetName を読み込みました！ (path: $filepath)　わーい！"
    return $sheet
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
            $map.Add($headers[$j], $cell.Text)
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
    $filepathRelative = $PSScriptRoot + "\..\MonsterData\MonsterData.xlsx"
    $sheetName = "Sheet1"
    $headerBeginColumn = 2
    $headerRaw = 3
    $maxHeaderSize = 32
    $maxMonsterSize = 1024

    # Loading excel file needs absolute path
    $filepathAbsolute = (Get-ChildItem $filepathRelative).FullName
    $filepathWithoutExt = $filepathAbsolute.Substring(0, $filepathAbsolute.LastIndexOf('.'))
    $outputFilePath = $filepathWithoutExt + ".json"
    
    try {
        $sheet = LoadExcelSheet $filepathAbsolute $sheetName
        $headers = GetHeader $sheet $headerBeginColumn $maxHeaderSize
        $monsterList = GetMonsterList $sheet $headers $($headerRaw + 1) $headerBeginColumn $maxMonsterSize

        # データを取得して連想配列にする

        $json_obj = @{
            "monster_list" = $monsterList
        }

        ConvertTo-Json $json_obj | Out-File $outputFilePath
        Write-Host "データを保存しました！ (path: $outputFilePath) わーい！" 
    }
    catch {
        $errorMessage = $_.Exception.Message
        $errorMessage
    }
    
}

Main
