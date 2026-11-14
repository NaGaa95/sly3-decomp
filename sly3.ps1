param(
    [Parameter(Position = 0)]
    [ValidateSet('doctor','extract','configure','disassemble','split','index','target','check','draft','reference','progress','verify','build','build-all','iop-build','iop-selftest','iop-libsd-build','iop-libsd-selftest','iop-nosplit-build','iop-nosplit-selftest','baseline','selftest','ghidra')]
    [string]$Command = 'doctor',
    [Parameter(Position = 1, ValueFromRemainingArguments = $true)]
    [string[]]$CommandArgs
)
$ErrorActionPreference = 'Stop'
$taskPython = Join-Path $PSScriptRoot '.venv\Scripts\python.exe'
if (-not (Test-Path -LiteralPath $taskPython)) {
    throw 'Create .venv first (see "Build" in README.md).'
}
Push-Location $PSScriptRoot
try {
    $taskScripts = @{
        doctor = 'doctor.py'; extract = 'extract_disc.py'; configure = 'configure.py'
        disassemble = 'disassemble.py'; split = 'split.py'; index = 'index_functions.py'
        target = 'matchtool.py'; check = 'matchtool.py'
        draft = 'draft.py'; reference = 'reference_sly2.py'; progress = 'source_progress.py'
        verify = 'verify.py'; build = 'build_source.py'; baseline = 'build_baseline.py'; selftest = 'selftest.py'
        'build-all' = 'build_all_sources.py'; 'iop-build' = 'iop_build.py'; 'iop-selftest' = 'test_iop_build.py'
        'iop-libsd-build' = 'iop_libsd_build.py'; 'iop-libsd-selftest' = 'test_iop_libsd_build.py'
        'iop-nosplit-build' = 'iop_nosplit_build.py'; 'iop-nosplit-selftest' = 'test_iop_nosplit_build.py'
        ghidra = 'ghidra_project.py'
    }
    $taskArguments = @()
    if ($Command -in @('target','check')) { $taskArguments += $Command }
    if ($Command -eq 'split') { $taskArguments += @('split','config/sly3.yaml') }
    $taskArguments += $CommandArgs
    & $taskPython (Join-Path $PSScriptRoot ('tools\' + $taskScripts[$Command])) @taskArguments
    exit $LASTEXITCODE
} finally {
    Pop-Location
}
