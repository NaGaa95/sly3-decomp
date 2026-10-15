"""Import/analyze the verified executable with the local JDK and PS2 extension."""
import argparse
import shutil
import subprocess
from common import ROOT, target_config


def paths():
    ghidra = next(ROOT.glob("ghidra_*/ghidra_*"))
    jdk = next((ROOT / "tools/third_party/jdk").glob("jdk-*"))
    return ghidra, jdk


def java_command():
    ghidra, jdk = paths()
    user = ROOT / "build/ghidra-user"
    user.mkdir(parents=True, exist_ok=True)
    for directory in ("settings", "cache", "temp"):
        (user / directory).mkdir(exist_ok=True)
    return [str(jdk / "bin/java.exe"), "-Xmx3G", "-Djava.system.class.loader=ghidra.GhidraClassLoader", "-Dfile.encoding=UTF-8", "-Duser.country=US", "-Duser.language=en", "-Duser.home=" + str(user), "-Dapplication.settingsdir=" + str(user / "settings"), "-Dapplication.cachedir=" + str(user / "cache"), "-Dapplication.tempdir=" + str(user / "temp"), "-cp", str(ghidra / "Ghidra/Framework/Utility/lib/Utility.jar"), "ghidra.GhidraLauncher"]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--open", action="store_true", help="Open the prepared project in Ghidra")
    parser.add_argument("--no-analysis", action="store_true")
    parser.add_argument("--reimport", action="store_true")
    args = parser.parse_args()
    ghidra, _ = paths()
    source = ROOT / "tools/third_party/ghidra-emotionengine/ghidra-emotionengine-reloaded"
    extension = ghidra / "Ghidra/Extensions/ghidra-emotionengine-reloaded"
    if not extension.exists():
        shutil.copytree(source, extension)
    project_dir = ROOT / "build/ghidra"
    project_dir.mkdir(parents=True, exist_ok=True)
    target = target_config()
    if args.open:
        subprocess.Popen(java_command() + ["ghidra.GhidraRun", str(project_dir / "Sly3.gpr")])
        return
    cmd = java_command() + ["ghidra.app.util.headless.AnalyzeHeadless", str(project_dir), "Sly3"]
    if (project_dir / "Sly3.gpr").exists() and not args.reimport:
        cmd += ["-process", target["serial"]]
    else:
        cmd += ["-import", str(ROOT / "disc" / target["serial"]), "-processor", target["ghidra_language"], "-cspec", "default"]
        if args.reimport:
            cmd += ["-overwrite"]
    cmd += ["-scriptPath", str(ROOT / "tools/ghidra"), "-postScript", "Sly3Export.java", str(ROOT / "build/reports/ghidra_functions.csv"), "-analysisTimeoutPerFile", "600", "-max-cpu", "4", "-log", str(ROOT / "build/reports/ghidra.log")]
    if args.no_analysis:
        cmd += ["-noanalysis"]
    subprocess.run(cmd, cwd=ROOT, check=True)


if __name__ == "__main__":
    main()
