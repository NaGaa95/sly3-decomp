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


def source_signature(source, compiler, assembler, flags, apply_filter, include_dirs, filter_mode="engine"):
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
    inputs[str(compiler / "bin/ee-gcc.exe")] = file_hash(compiler / "bin/ee-gcc.exe")
    for path in (compiler / "lib/gcc-lib/ee").rglob("*.exe"):
        if path.stem in ("cc1", "cc1plus", "cpp"):
            inputs[str(path)] = file_hash(path)
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
    return hashlib.sha256(json.dumps({"inputs": inputs, "flags": flags, "filter": apply_filter, "filter_mode": filter_mode}, sort_keys=True).encode()).hexdigest()


def compile_source(source, output, include_dirs=()):
    source = Path(source).resolve()
    output = Path(output).resolve()
    output.parent.mkdir(parents=True, exist_ok=True)
    target = target_config()
    header = source.read_text(encoding="utf-8", errors="replace")[:3000]
    if re.search(r"SLY3_ASM:\s*gnu-reorder", header):
        raise ValueError("The reference GNU 2.96 reorder assembler profile is not installed; adapt and verify this source explicitly")
    compiler = ROOT / os.environ.get("SLY3_CC", target["compiler"])
    override = re.search(r"SLY3_CC:\s*(\S+)", header)
    if override:
        compiler = ROOT / override[1]
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
    filter_mode = os.environ.get("SLY3_ASFIX", mode_match[1] if mode_match else "engine")
    filter_mode = {"1": "engine", "0": "off"}.get(filter_mode, filter_mode)
    if filter_mode not in ("engine", "off", "sdk-loop7", "sdk-fdlibm", "engine-const-copy", "sdk-gp64", "sdk-softdf", "sdk-literals", "engine-local-jumps", "sdk-branch-fold", "engine-exit-slots", "engine-divfix1"):
        raise ValueError("Unsupported assembler filter: " + filter_mode)
    apply_filter = filter_mode != "off"
    signature = source_signature(source, compiler, assembler, flags, apply_filter, include_dirs, filter_mode)
    manifest = output.with_suffix(".compile.json")
    if manifest.exists() and output.exists() and os.environ.get("SLY3_FORCE_COMPILE") != "1":
        cached = json.loads(manifest.read_text())
        if cached.get("signature") == signature and cached.get("object_sha256") == file_hash(output):
            return output
    cmd = [str(compiler / "bin/ee-gcc.exe"), "-S", *flags, source.as_posix(), "-o", raw.as_posix()]
    subprocess.run(cmd, cwd=ROOT, check=True, capture_output=True, text=True, timeout=120)
    text = raw.read_text(encoding="utf-8")
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
