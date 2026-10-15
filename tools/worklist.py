"""List small unmatched function candidates in an optional hexadecimal address range."""
import argparse
import csv
from common import ROOT


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("low", nargs="?", default="100000")
    parser.add_argument("high", nargs="?", default="2C0250")
    parser.add_argument("max_instructions", nargs="?", type=int, default=100)
    parser.add_argument("--limit", type=int, default=40)
    args = parser.parse_args()
    low, high = int(args.low, 16), int(args.high, 16)
    matches = set()
    path = ROOT / "config/matched.csv"
    if path.exists():
        matches = {int(r["address"], 16) for r in csv.DictReader(path.open()) if r["status"] in ("EXACT_MATCH", "LINKED_MATCH")}
    rows = []
    for row in csv.DictReader((ROOT / "config/functions.csv").open()):
        address, size = int(row["Start"], 16), int(row["Size"])
        if low <= address < high and address not in matches and size // 4 <= args.max_instructions:
            rows.append((size, address, row["Name"]))
    for size, address, name in sorted(rows)[:args.limit]:
        print(f"{address:08X} {size // 4:4d} instructions  {name}")
    print(f"{len(rows):,} candidates in range; boundaries are provisional")


if __name__ == "__main__":
    main()
