"""Native Windows compiler runner, with the Sly 2 assembly filter as a hypothesis."""
import os
import re
import subprocess
import hashlib
import json
from pathlib import Path
from common import ROOT, target_config

_file_hashes = {}


def file_hash(path):
    path = Path(path)
    stat = path.stat()
    key = (str(path), stat.st_size, stat.st_mtime_ns)
    if key not in _file_hashes:
        _file_hashes[key] = hashlib.sha256(path.read_bytes()).hexdigest()
    return _file_hashes[key]


SDK_ASM_MODES = ("gnu-reorder-db", "gnu-reorder", "gnu-reorg")


def resolve_compiler(value):
    """A SLY3_CC value: a compiler directory relative to the project root (as always), or - only when no such
    directory exists - a short name of a compiler under tools/third_party (e.g. `991111` -> ee-gcc2.9-991111,
    `2.96` -> ee-gcc2.96, `3.2-040921` -> ee-gcc3.2-040921, `114` -> ee-gcc2.95.3-114)."""
    path = ROOT / value
    if path.is_dir():
        return path
    third = ROOT / "tools/third_party"
    for name in (value, "ee-gcc" + value, "ee-gcc2.9-" + value, "ee-gcc2.95.3-" + value):
        if (third / name).is_dir():
            return third / name
    return path


def is_native(compiler):
    """Native 32-bit Linux toolchains (the ee-gcc 2.9/2.96/3.2 builds from decomp.me) ship bin/ee-gcc, no .exe."""
    return not (compiler / "bin/ee-gcc.exe").exists() and (compiler / "bin/ee-gcc").is_file()


def source_signature(source, compiler, assembler, flags, apply_filter, include_dirs, filter_mode="engine", sdk=None):
    directories = [source.parent, ROOT / "include", *(Path(p).resolve() for p in include_dirs)]
    macros = next((ROOT / "tools/third_party/m2c").glob("*/m2c_macros.h"), None)
    if macros:
        directories.append(macros.parent)
    inputs, pending = {}, [source]
    while pending:
        path = pending.pop()
        if str(path) in inputs:
            continue
        inputs[str(path)] = file_hash(path)
        for name in re.findall(r'^\s*#\s*include\s*[<"]([^">]+)[">]', path.read_text(encoding="utf-8", errors="replace"), re.M):
            for directory in [path.parent, *directories]:
                dependency = (directory / name).resolve()
                if dependency.is_file():
                    pending.append(dependency)
                    break
    inputs[str(assembler)] = file_hash(assembler)
    if is_native(compiler):
        inputs[str(compiler / "bin/ee-gcc")] = file_hash(compiler / "bin/ee-gcc")
        for path in (compiler / "lib/gcc-lib/ee").rglob("*"):
            if path.name in ("cc1", "cc1plus", "cpp"):
                inputs[str(path)] = file_hash(path)
        if (compiler / "ee/bin/as").is_file():
            inputs[str(compiler / "ee/bin/as")] = file_hash(compiler / "ee/bin/as")
    else:
        inputs[str(compiler / "bin/ee-gcc.exe")] = file_hash(compiler / "bin/ee-gcc.exe")
        for path in (compiler / "lib/gcc-lib/ee").rglob("*.exe"):
            if path.stem in ("cc1", "cc1plus", "cpp"):
                inputs[str(path)] = file_hash(path)
    if sdk:
        for name in ("tools/gnu_reorder.py", "tools/asfix_sly2.py", "tools/third_party/ee-gcc2.96/ee/bin/as"):
            inputs[str(ROOT / name)] = file_hash(ROOT / name)
    if apply_filter:
        inputs[str(ROOT / "tools/asfix_sly2.py")] = file_hash(ROOT / "tools/asfix_sly2.py")
        if filter_mode == "sdk-loop7":
            inputs[str(ROOT / "tools/asfix_sdk.py")] = file_hash(ROOT / "tools/asfix_sdk.py")
        if filter_mode == "sdk-fdlibm":
            inputs[str(ROOT / "tools/asfix_fdlibm.py")] = file_hash(ROOT / "tools/asfix_fdlibm.py")
        if filter_mode == "engine-const-copy":
            inputs[str(ROOT / "tools/asfix_constcopy.py")] = file_hash(ROOT / "tools/asfix_constcopy.py")
        if filter_mode in ("sdk-gp64", "sdk-softdf", "sdk-literals"):
            for name in ("asfix_sdk_gp64.py", "asfix_fdlibm.py"):
                inputs[str(ROOT / "tools" / name)] = file_hash(ROOT / "tools" / name)
        if filter_mode in ("sdk-softdf", "sdk-literals"):
            inputs[str(ROOT / "tools/asfix_sdk_softdf.py")] = file_hash(ROOT / "tools/asfix_sdk_softdf.py")
        if filter_mode == "sdk-literals":
            inputs[str(ROOT / "tools/asfix_sdk_literals.py")] = file_hash(ROOT / "tools/asfix_sdk_literals.py")
        if filter_mode == "engine-exit-slots":
            inputs[str(ROOT / "tools/asfix_engine_exit_slots.py")] = file_hash(ROOT / "tools/asfix_engine_exit_slots.py")
        if filter_mode == "engine-local-jumps":
            inputs[str(ROOT / "tools/asfix_backward_b.py")] = file_hash(ROOT / "tools/asfix_backward_b.py")
        if filter_mode == "sdk-branch-fold":
            inputs[str(ROOT / "tools/asfix_branch_fold.py")] = file_hash(ROOT / "tools/asfix_branch_fold.py")
        if filter_mode == "engine-divfix1":
            inputs[str(ROOT / "tools/asfix_divfix1.py")] = file_hash(ROOT / "tools/asfix_divfix1.py")
    inputs[str(Path(__file__).resolve())] = file_hash(Path(__file__).resolve())
    key = {"inputs": inputs, "flags": flags, "filter": apply_filter, "filter_mode": filter_mode}
    if sdk:
        key["sdk"] = sdk
    return hashlib.sha256(json.dumps(key, sort_keys=True).encode()).hexdigest()


def compile_source(source, output, include_dirs=()):
    source = Path(source).resolve()
    output = Path(output).resolve()
    output.parent.mkdir(parents=True, exist_ok=True)
    target = target_config()
    header = source.read_text(encoding="utf-8", errors="replace")[:3000]
    # Sony SDK path (opt-in per file, see docs in tools/gnu_reorder.py and the README):
    #   // SLY3_ASM: gnu-reorder | gnu-reorder-db | gnu-reorg   GNU as 2.96 reorder-mode assembly instead of ps2eeas
    #   // SLY3_SAVES: sd     64-bit sd/ld register saves (Sony's SDK compiler) instead of sq/lq
    #   // SLY3_DIVNOP, // SLY3_NOLOOPFIX                        extra gnu_reorder rules (libm / libmpeg)
    asm_match = re.search(r"SLY3_ASM:\s*(\S+)", header)
    asm_mode = None
    if asm_match:
        asm_mode = asm_match[1]
        if asm_mode not in SDK_ASM_MODES:
            raise ValueError("Unsupported SLY3_ASM mode: " + asm_mode)
    compiler = ROOT / os.environ.get("SLY3_CC", target["compiler"])
    override = re.search(r"SLY3_CC:\s*(\S+)", header)
    if override:
        compiler = resolve_compiler(override[1])
    native = is_native(compiler)
    flags = os.environ.get("SLY3_CFLAGS", " ".join(target["cflags"])).split()
    override = re.search(r"SLY3_CFLAGS:\s*([^\r\n]+)", header)
    if override:
        flags = override[1].split()
    language = "c" if source.suffix == ".c" else "c++"
    libdir = next((compiler / "lib/gcc-lib/ee").iterdir())
    flags = ["-x", language, *flags, "-B" + libdir.as_posix() + "/", "-I" + (ROOT / "include").as_posix()]
    macros = next((ROOT / "tools/third_party/m2c").glob("*/m2c_macros.h"), None)
    if macros:
        flags.append("-I" + macros.parent.as_posix())
    flags += ["-I" + Path(p).resolve().as_posix() for p in include_dirs]
    if native:
        # the old native compilers predate -mvu0-use-vf0-vf31; let their driver find their own GNU as
        flags = [x for x in flags if x != "-mvu0-use-vf0-vf31"] + ["-B" + (compiler / "ee/bin").as_posix() + "/"]
    if asm_mode == "gnu-reorder":
        flags.append("-fno-delayed-branch")
    raw = output.with_suffix(".raw.s")
    fixed = output.with_suffix(".s")
    assembler = ROOT / os.environ.get("SLY3_AS", target["assembler"])
    assembler_override = re.search(r"SLY3_AS:\s*(\S+)", header)
    if assembler_override:
        profiles = {"gnu-2.9": "tools/third_party/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3/as.exe"}
        if assembler_override[1] not in profiles:
            raise ValueError("Unsupported assembler profile: " + assembler_override[1])
        assembler = ROOT / profiles[assembler_override[1]]
    mode_match = re.search(r"SLY3_ASFIX:\s*(\S+)", header)
    if (asm_mode or native) and mode_match:
        raise ValueError("SLY3_ASFIX filters are for ps2eeas output; they cannot be combined with SLY3_ASM or a native SDK compiler")
    filter_mode = os.environ.get("SLY3_ASFIX", mode_match[1] if mode_match else "engine")
    if asm_mode or native:
        filter_mode = "off"
    filter_mode = {"1": "engine", "0": "off"}.get(filter_mode, filter_mode)
    if filter_mode not in ("engine", "off", "sdk-loop7", "sdk-fdlibm", "engine-const-copy", "sdk-gp64", "sdk-softdf", "sdk-literals", "engine-local-jumps", "sdk-branch-fold", "engine-exit-slots", "engine-divfix1"):
        raise ValueError("Unsupported assembler filter: " + filter_mode)
    apply_filter = filter_mode != "off"
    sdk = None
    if asm_mode or native:
        sdk = {"asm": asm_mode or "driver", "saves": bool(re.search(r"SLY3_SAVES:\s*sd\b", header)),
               "divnop": bool(re.search(r"SLY3_DIVNOP", header)), "noloopfix": bool(re.search(r"SLY3_NOLOOPFIX", header))}
    signature = source_signature(source, compiler, assembler, flags, apply_filter, include_dirs, filter_mode, sdk)
    manifest = output.with_suffix(".compile.json")
    if manifest.exists() and output.exists() and os.environ.get("SLY3_FORCE_COMPILE") != "1":
        cached = json.loads(manifest.read_text())
        if cached.get("signature") == signature and cached.get("object_sha256") == file_hash(output):
            return output
    driver = str(compiler / ("bin/ee-gcc" if native else "bin/ee-gcc.exe"))
    cmd = [driver, "-S", *flags, source.as_posix(), "-o", raw.as_posix()]
    subprocess.run(cmd, cwd=ROOT, check=True, capture_output=True, text=True, timeout=120)
    text = raw.read_text(encoding="utf-8")
    if sdk:
        if sdk["saves"]:
            # Sony's SDK compiler saved/restored registers with 64-bit sd/ld (in 16-byte slots); emulate it on
            # $sp-based sq/lq only (SDK C code has no other 128-bit stack accesses; a wrong rewrite cannot match)
            text = re.sub(r"^(\s+)sq(\s+\$\w+\s*,\s*-?\w*\(\$sp\))", r"\1sd\2", text, flags=re.M)
            text = re.sub(r"^(\s+)lq(\s+\$\w+\s*,\s*-?\w*\(\$sp\))", r"\1ld\2", text, flags=re.M)
        if asm_mode:
            import gnu_reorder
            text = gnu_reorder.rewrite(text, asm_mode, sdk["divnop"], sdk["noloopfix"])
            fixed.write_text(text, encoding="utf-8")
            subprocess.run([str(ROOT / gnu_reorder.GNU_AS), "-G0", "-EL", "-mabi=eabi", "-o", output.as_posix(), fixed.as_posix()], cwd=ROOT, check=True, capture_output=True, text=True, timeout=120)
        else:
            # native compiler without SLY3_ASM: its own driver + GNU as, like `ee-gcc -c`
            fixed.write_text(text, encoding="utf-8")
            subprocess.run([driver, "-c", *[x for x in flags if x not in ("-x", "c", "c++")], "-x", "assembler", fixed.as_posix(), "-o", output.as_posix()], cwd=ROOT, check=True, capture_output=True, text=True, timeout=120)
        manifest.write_text(json.dumps({"source": source.as_posix(), "signature": signature, "object_sha256": file_hash(output)}, indent=2) + "\n", encoding="utf-8")
        return output
    if apply_filter:
        if filter_mode == "sdk-loop7":
            from asfix_sdk import fix
        elif filter_mode == "sdk-fdlibm":
            from asfix_fdlibm import fix
        elif filter_mode == "engine-const-copy":
            from asfix_constcopy import fix
        elif filter_mode == "sdk-gp64":
            from asfix_sdk_gp64 import fix
        elif filter_mode == "sdk-softdf":
            from asfix_sdk_softdf import fix
        elif filter_mode == "sdk-literals":
            from asfix_sdk_literals import fix
        elif filter_mode == "engine-exit-slots":
            from asfix_engine_exit_slots import fix
        elif filter_mode == "engine-local-jumps":
            from asfix_backward_b import fix
        elif filter_mode == "sdk-branch-fold":
            from asfix_branch_fold import fix
        elif filter_mode == "engine-divfix1":
            from asfix_divfix1 import fix
        else:
            from asfix_sly2 import fix
        text, _ = fix(text)
    fixed.write_text(text, encoding="utf-8")
    subprocess.run([str(assembler), "-G0", "-O2", "-mabi=eabi", "-o", output.as_posix(), fixed.as_posix()], cwd=ROOT, check=True, capture_output=True, text=True, timeout=120)
    manifest.write_text(json.dumps({"source": source.as_posix(), "signature": signature, "object_sha256": file_hash(output)}, indent=2) + "\n", encoding="utf-8")
    return output
