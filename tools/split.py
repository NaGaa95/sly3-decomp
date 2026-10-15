"""Run splat for PS2 without eagerly loading unused N64 native modules.

splat 0.50.1 imports every platform's segments at startup. On Windows ARM64
this otherwise requires building pygfxd, although a PS2 split never uses it.
Only the N64 package initializer is bypassed; PS2 analysis runs unchanged.
"""
import importlib.util
import sys
import types
from pathlib import Path


def main():
    spec = importlib.util.find_spec("splat")
    if spec is None:
        raise RuntimeError("Install requirements.txt in the project environment first")
    package = types.ModuleType("splat.segtypes.n64")
    package.__path__ = [str(Path(spec.origin).parent / "segtypes/n64")]
    sys.modules[package.__name__] = package
    from splat.__main__ import splat_main
    splat_main()


if __name__ == "__main__":
    main()
