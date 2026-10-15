"""Download isolated local tools from their upstream releases with checksums."""
import argparse
import hashlib
import json
import shutil
import tarfile
import urllib.request
import zipfile
from pathlib import Path, PurePosixPath
from common import ROOT, save_json, sha256_file


def fetch_json(url):
    req = urllib.request.Request(url, headers={"User-Agent": "sly3-decomp-setup"})
    with urllib.request.urlopen(req, timeout=60) as response:
        return json.load(response)


def safe_extract(path, destination):
    destination.mkdir(parents=True, exist_ok=True)
    if zipfile.is_zipfile(path):
        with zipfile.ZipFile(path) as archive:
            for info in archive.infolist():
                name = PurePosixPath(info.filename.replace("\\", "/"))
                if name.is_absolute() or ".." in name.parts or ":" in str(name):
                    raise ValueError("Unsafe ZIP member")
            archive.extractall(destination)
    else:
        with tarfile.open(path) as archive:
            archive.extractall(destination, filter="data")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--jdk", action="store_true", help="Also install a portable x64 JDK 21 for Ghidra")
    args = parser.parse_args()
    lock_path = ROOT / "config/toolchain.lock.json"
    lock = json.loads(lock_path.read_text()) if lock_path.exists() else {"tools": {}}
    wanted = {
        "ee-gcc2.95.3-136": ("decompme/compilers", "compilers", "ee-gcc2.95.3-136.tar.gz"),
        "ee-gcc2.95.3-114": ("decompme/compilers", "compilers", "ee-gcc2.95.3-114.tar.gz"),
        "slytools": ("VelocityRa/SlyTools", "v1.2", "slytools-v1.2-x64.zip"),
        "ghidra-emotionengine": ("chaoticgd/ghidra-emotionengine-reloaded", "v2.1.38", "ghidra_12.1.4_PUBLIC_20261004_ghidra-emotionengine-reloaded.zip"),
    }
    releases = {}
    for name, (repo, tag, filename) in wanted.items():
        if name in lock["tools"]:
            continue
        key = (repo, tag)
        if key not in releases:
            releases[key] = fetch_json(f"https://api.github.com/repos/{repo}/releases/tags/{tag}")
        asset = next(a for a in releases[key]["assets"] if a["name"] == filename)
        lock["tools"][name] = {"url": asset["browser_download_url"], "filename": filename, "sha256": (asset.get("digest") or "").removeprefix("sha256:"), "upstream": f"https://github.com/{repo}", "version": tag}
    for name, repo in (("m2c", "matt-kempster/m2c"), ("slytools-source", "VelocityRa/SlyTools")):
        if name not in lock["tools"]:
            commit = fetch_json(f"https://api.github.com/repos/{repo}/commits/HEAD")["sha"]
            lock["tools"][name] = {"url": f"https://api.github.com/repos/{repo}/zipball/{commit}", "filename": name + ".zip", "commit": commit, "upstream": f"https://github.com/{repo}"}
    if args.jdk and "jdk" not in lock["tools"]:
        assets = fetch_json("https://api.adoptium.net/v3/assets/latest/21/hotspot?architecture=x64&image_type=jdk&os=windows&vendor=eclipse")
        package = assets[0]["binary"]["package"]
        lock["tools"]["jdk"] = {"url": package["link"], "filename": package["name"], "sha256": package["checksum"], "version": assets[0]["version"]["semver"], "upstream": "https://adoptium.net/"}
    save_json(lock_path, lock)
    for name, item in lock["tools"].items():
        destination = ROOT / "tools/third_party" / name
        marker = destination / ".installed.json"
        if marker.exists():
            print(f"Already installed: {name}", flush=True)
            continue
        archive = ROOT / "tools/downloads" / item["filename"]
        archive.parent.mkdir(parents=True, exist_ok=True)
        if not archive.exists():
            print(f"Downloading {name}", flush=True)
            req = urllib.request.Request(item["url"], headers={"User-Agent": "sly3-decomp-setup"})
            with urllib.request.urlopen(req, timeout=90) as response, archive.with_suffix(archive.suffix + ".part").open("wb") as output:
                shutil.copyfileobj(response, output, 1024 * 1024)
            archive.with_suffix(archive.suffix + ".part").replace(archive)
        checksum = sha256_file(archive)
        if item.get("sha256") and item["sha256"] != checksum:
            raise ValueError("Checksum mismatch: " + str(archive))
        item["sha256"] = checksum
        print(f"Extracting {name}", flush=True)
        safe_extract(archive, destination)
        save_json(marker, item)
        save_json(lock_path, lock)
    print("Local tool installation complete")


if __name__ == "__main__":
    main()
