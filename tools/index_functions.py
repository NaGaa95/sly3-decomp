"""Combine independent function-start discoveries; boundaries remain provisional."""
import csv
import re
from collections import defaultdict
from common import ROOT, target_config


def main():
    target = target_config()["text"]
    begin, limit = target["addr"], target["addr"] + target["size"]
    starts = defaultdict(set)
    names = {}
    with (ROOT / "build/reports/spim_functions.csv").open(newline="") as stream:
        for row in csv.DictReader(stream):
            address = int(row["address"], 16)
            if begin <= address < limit and row["file"].endswith("974"):
                starts[address].add("spimdisasm")
                names[address] = row["name"]
    path = ROOT / "build/reports/ghidra_functions.csv"
    if path.exists():
        with path.open(newline="") as stream:
            for row in csv.DictReader(stream):
                address = int(row["Start"], 16)
                if begin <= address < limit and address % 4 == 0:
                    starts[address].add("ghidra")
    names[target_config()["entry"]] = "_start"
    exclusions = []
    exclusion_path = ROOT / "config/function_exclusions.csv"
    if exclusion_path.exists():
        with exclusion_path.open(newline="") as stream:
            reader = csv.DictReader(stream)
            if reader.fieldnames != ["Start", "End", "Reason"]:
                raise ValueError("Invalid non-function exclusion columns")
            for row in reader:
                if None in row or any(value is None for value in row.values()):
                    raise ValueError("Invalid non-function exclusion row")
                start, end = int(row["Start"], 16), int(row["End"], 16)
                if not begin <= start < end <= limit or start % 4 or end % 4 or not row["Reason"].strip():
                    raise ValueError("Invalid non-function exclusion")
                exclusions.append((start, end))
        exclusions.sort()
        if any(left[1] > right[0] for left, right in zip(exclusions, exclusions[1:])):
            raise ValueError("Overlapping non-function exclusions")
        if any(start <= target_config()["entry"] < end for start, end in exclusions):
            raise ValueError("The executable entry cannot be excluded")
        matched_path = ROOT / "config/matched.csv"
        if matched_path.exists():
            with matched_path.open(newline="") as stream:
                for row in csv.DictReader(stream):
                    address = int(row["address"], 0)
                    end = address + int(row["instructions"]) * 4
                    if any(max(address, start) < min(end, stop) for start, stop in exclusions):
                        raise ValueError("Non-function exclusion overlaps maintained source")
        for address in list(starts):
            if any(start <= address < end for start, end in exclusions):
                del starts[address]
                names.pop(address, None)
    overrides = {}
    override_path = ROOT / "config/function_overrides.csv"
    if override_path.exists():
        for row in csv.DictReader(override_path.open(newline="")):
            address = int(row["Start"], 16)
            end = int(row["End"], 16)
            if not begin <= address < end <= limit or address % 4 or end % 4:
                raise ValueError("Invalid function boundary override")
            if any(max(address, start) < min(end, stop) for start, stop in exclusions):
                raise ValueError("Function override overlaps a non-function exclusion")
            overrides[address] = row
            starts[address].add("manual")
            names[address] = row["Name"]
    addresses = sorted(starts)
    with (ROOT / "config/functions.csv").open("w", newline="", encoding="utf-8") as stream:
        writer = csv.writer(stream)
        writer.writerow(("Name", "Start", "End", "Size", "BoundarySource"))
        for i, address in enumerate(addresses):
            inferred_end = addresses[i + 1] if i + 1 < len(addresses) else limit
            end = int(overrides[address]["End"], 16) if address in overrides else inferred_end
            if end > inferred_end:
                raise ValueError("Override overlaps the next candidate function")
            boundary = overrides[address]["BoundarySource"] if address in overrides else "+".join(sorted(starts[address])) + "-provisional"
            writer.writerow((names.get(address, f"func_{address:08X}"), f"0x{address:08X}", f"0x{end:08X}", end - address, boundary))
    print(f"Indexed {len(addresses):,} main EE function candidates; verify boundaries before claiming matches")


if __name__ == "__main__":
    main()
