#!/usr/bin/env python3
"""Draw docs/progress.svg (shown in README) and log config/progress_history.csv.

Needs only files that are committed to the repo (config/functions.csv, config/matched.csv and the
VU/IOP config JSONs), so it runs on GitHub without the game disc: .github/workflows/progress.yml
calls it on every push and commits the refreshed graph. Run it locally after tools/source_progress.py
to preview:  python tools/progress_graph.py
If progress.svg or progress_history.csv conflicts on a pull, take either side and re-run this script."""
import csv
import datetime
import glob
import json
import os
import re
from html import escape

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
HIST = os.path.join(ROOT, 'config', 'progress_history.csv')
SVG = os.path.join(ROOT, 'docs', 'progress.svg')
MATCH = ('LINKED_MATCH', 'EXACT_MATCH')

# Range owners, from ASSIGNMENTS.md (everything below 0x1B0000 is Dimitri + Claude)
OWNERS = {'naga': [(0x1B0000, 0x240000)], 'lilly': [(0x240000, 0x1_0000_0000)]}
C_DONE, C_DONE2, C_LEFT = '#2f9e6e', '#4c7fd1', '#e4e7ec'
C_TEXT, C_MUTED, C_GRID = '#1f2328', '#656d76', '#d0d7de'
C_ME, C_COLLAB, C_LILLY = '#d97706', '#7c3aed', '#db2777'
WHO = [('me', 'Dimitri + Claude', C_ME), ('naga', 'NaGa + Claude + ChatGPT', C_COLLAB), ('lilly', 'Lilly + Claude', C_LILLY)]


def owner(addr):
    for who, ranges in OWNERS.items():
        if any(a <= addr < b for a, b in ranges):
            return who
    return 'me'


def load_functions():
    """{addr: (name, size_bytes)} for every EE function in config/functions.csv"""
    real = {}
    with open(os.path.join(ROOT, 'config', 'functions.csv'), newline='') as f:
        for r in csv.DictReader(f):
            a, e = int(r['Start'], 16), int(r['End'], 16)
            if e > a:
                real.setdefault(a, (r['Name'], e - a))
    return real


def load_matched():
    with open(os.path.join(ROOT, 'config', 'matched.csv'), newline='') as f:
        return {int(r['address'], 16) for r in csv.DictReader(f) if r['status'].strip() in MATCH}


def side_stats():
    """VU programs and IOP functions recorded by NaGa's VU/IOP pipelines (None when unavailable)."""
    vu = iop_f = iop_b = None
    try:
        v = json.load(open(os.path.join(ROOT, 'config', 'vu_original_programs.json')))
        progs = v.get('programs')
        vu = len(progs) if isinstance(progs, list) else None
    except (OSError, ValueError, AttributeError):
        pass
    seen = set()
    for path in glob.glob(os.path.join(ROOT, 'config', 'iop_*partial.json')):
        try:
            d = json.load(open(path))
        except (OSError, ValueError):
            continue
        for fn in d.get('functions', []) if isinstance(d, dict) else []:
            if isinstance(fn, dict) and fn.get('source'):
                key = (d.get('module'), fn.get('name'), fn.get('module_offset'))
                if key not in seen:
                    seen.add(key)
                    iop_f = (iop_f or 0) + 1
                    iop_b = (iop_b or 0) + int(fn.get('size') or 0)
    return vu, iop_f, iop_b


def load_history():
    if not os.path.exists(HIST):
        return []
    with open(HIST, newline='') as f:
        return list(csv.DictReader(f))


def log(mf, mi, total_f, total_i, note=''):
    rows = load_history()
    if rows and int(rows[-1]['functions']) == mf and int(rows[-1]['instructions']) == mi:
        return rows
    rows.append({'date': datetime.date.today().isoformat(), 'functions': str(mf), 'instructions': str(mi),
                 'total_functions': str(total_f), 'total_instructions': str(total_i), 'note': note})
    with open(HIST, 'w', newline='') as f:
        w = csv.DictWriter(f, fieldnames=['date', 'functions', 'instructions', 'total_functions', 'total_instructions', 'note'])
        w.writeheader()
        w.writerows(rows)
    return rows



def pretty(parts):
    """One SVG element per line (indented two spaces), blank line + comment before each section."""
    lines = []
    for part in parts:
        if part.startswith('<!--'):
            lines += ['', part]
            continue
        for el in re.split(r'(?<=>)(?=<)', part):
            lines.append(el.replace('"/>', '" />'))
    return '\n'.join('  ' + l if l else '' for l in lines)


def t(x, y, s, size=13, color=C_TEXT, anchor='start', weight='normal'):
    return (f'<text x="{x:.1f}" y="{y:.1f}" font-size="{size}" fill="{color}" text-anchor="{anchor}" '
            f'font-weight="{weight}">{escape(str(s), quote=False)}</text>')


def bar(x, y, w, h, frac, color, r=4):
    return (f'<rect x="{x}" y="{y}" width="{w}" height="{h}" rx="{r}" fill="{C_LEFT}"/>'
            f'<rect x="{x}" y="{y}" width="{max(0, w * frac):.1f}" height="{h}" rx="{r}" fill="{color}"/>')


def render(real, matched_addrs):
    """real: {addr: (name, size_bytes)}; matched_addrs: set of verified function addresses."""
    total_f = len(real)
    total_i = sum(s // 4 for _, s in real.values())
    mf = sum(1 for a in real if a in matched_addrs)
    mi = sum(s // 4 for a, (_, s) in real.items() if a in matched_addrs)
    hist = log(mf, mi, total_f, total_i)
    today = datetime.date.today().isoformat()
    W = 960
    out = []
    y = 0

    # ---- header
    out.append('<!-- Header -->')
    y += 40
    out.append(t(32, y, 'Sly 3: Honor Among Thieves — matching decompilation progress', 22, weight='bold'))
    y += 22
    out.append(t(32, y, f'SCUS_974.64 (NTSC-U) · only byte-identical, relocation-checked functions count · updated {today}', 13, C_MUTED))

    def headline(y, label, sub, done, total, color, unit):
        frac = done / total if total else 1
        out.append(f'<!-- {label} Section -->')
        out.append(t(32, y, label, 15, weight='bold'))
        out.append(t(W - 32, y, f'{frac:.1%}', 22, color, 'end', 'bold'))
        out.append(t(32, y + 18, sub, 12, C_MUTED))
        out.append(bar(32, y + 28, W - 64, 22, frac, color, 6))
        out.append(t(32, y + 68, f'{done:,} of {total:,} {unit} matched', 12))
        out.append(t(W - 32, y + 68, f'{total - done:,} {unit} left to 100%', 12, C_MUTED, 'end'))
        return y + 96
    y += 44
    y = headline(y, 'Functions', 'How many of the game\'s functions have source code that compiles to the exact original bytes',
                 mf, total_f, C_DONE, 'functions')
    y = headline(y, 'Code size (instructions)', 'The same, weighted by size — the honest "how much of the game is decompiled" number',
                 mi, total_i, C_DONE2, 'instructions')

    # ---- VU / IOP side line
    out.append('<!-- VU and IOP -->')
    vu, iop_f, iop_b = side_stats()
    parts = []
    if vu:
        parts.append(f'VU microcode: {vu} of {vu} programs matched')
    if iop_f:
        parts.append(f'IOP modules: {iop_f:,} functions matched ({iop_b:,} code bytes)')
    if parts:
        out.append(t(32, y, '   ·   '.join(parts), 12, C_MUTED))
        y += 18

    # ---- history line chart
    out.append('<!-- Progress Over Time Section -->')
    y += 16
    out.append(t(32, y, 'Progress over time', 16, weight='bold'))
    out.append(t(W - 32, y, 'each point = one recorded checkpoint', 12, C_MUTED, 'end'))
    cx, cy, cw, ch = 72, y + 20, W - 72 - 40, 200
    for p in range(0, 101, 25):
        gy = cy + ch - ch * p / 100
        out.append(f'<line x1="{cx}" y1="{gy:.1f}" x2="{cx + cw}" y2="{gy:.1f}" stroke="{C_GRID}" stroke-width="1"/>')
        out.append(t(cx - 8, gy + 4, f'{p}%', 11, C_MUTED, 'end'))
    n = len(hist)
    xs = [cx + (cw * i / (n - 1) if n > 1 else cw / 2) for i in range(n)]
    for key, color in (('functions', C_DONE), ('instructions', C_DONE2)):
        pts = []
        for i, r in enumerate(hist):
            tot = int(r['total_' + key]) or 1
            pts.append((xs[i], cy + ch - ch * int(r[key]) / tot))
        if len(pts) > 1:
            out.append(f'<polyline fill="none" stroke="{color}" stroke-width="2.5" stroke-linejoin="round" points="'
                       + ' '.join(f'{a:.1f},{b:.1f}' for a, b in pts) + '"/>')
        for a, b in pts:
            out.append(f'<circle cx="{a:.1f}" cy="{b:.1f}" r="3.5" fill="{color}"/>')
    first = {}
    for i, r in enumerate(hist):
        first.setdefault(r['date'][5:], i)
    keep = []
    for lab, i in sorted(first.items(), key=lambda kv: kv[1]):
        while keep and xs[i] - xs[keep[-1][1]] < 42:
            keep.pop()
        keep.append((lab, i))
    for lab, i in keep:
        anchor = 'end' if xs[i] > cx + cw - 20 else ('start' if xs[i] < cx + 20 else 'middle')
        out.append(t(xs[i], cy + ch + 16, lab, 10, C_MUTED, anchor))
    ly = cy + ch + 36
    out.append(f'<rect x="{cx}" y="{ly - 9}" width="12" height="4" fill="{C_DONE}"/>' + t(cx + 18, ly - 4, 'Functions', 12))
    out.append(f'<rect x="{cx + 100}" y="{ly - 9}" width="12" height="4" fill="{C_DONE2}"/>' + t(cx + 118, ly - 4, 'Code size (instructions)', 12))
    y = ly + 24

    # ---- per-person progress
    out.append('<!-- Progress By Person Section -->')
    y += 16
    out.append(t(32, y, 'Progress by person (assigned ranges, see ASSIGNMENTS.md)', 16, weight='bold'))
    y += 8
    for key, label, color in WHO:
        fs = [a for a in real if owner(a) == key]
        if not fs:
            continue
        ti = sum(real[a][1] // 4 for a in fs)
        di = sum(real[a][1] // 4 for a in fs if a in matched_addrs)
        df = sum(1 for a in fs if a in matched_addrs)
        frac = di / ti if ti else 1
        y += 26
        out.append(f'<rect x="32" y="{y - 11}" width="10" height="12" rx="2" fill="{color}"/>' + t(48, y, label, 12, weight='bold'))
        out.append(bar(240, y - 12, 270, 14, frac, color, 3))
        out.append(t(630, y, f'{frac:.1%} of code', 12, anchor='end'))
        out.append(t(W - 32, y, f'{df:,} of {len(fs):,} functions matched · {len(fs) - df:,} left', 12, C_MUTED, 'end'))
    y += 20

    # ---- per-range table
    out.append('<!-- By Address Range Section -->')
    y += 16
    out.append(t(32, y, 'Where the remaining work is (by address range)', 16, weight='bold'))
    y += 18
    out.append(f'<rect x="32" y="{y - 9}" width="10" height="10" rx="2" fill="{C_ME}"/>' + t(48, y, 'Dimitri + Claude', 12))
    out.append(f'<rect x="170" y="{y - 9}" width="10" height="10" rx="2" fill="{C_COLLAB}"/>' + t(186, y, 'NaGa', 12))
    out.append(f'<rect x="240" y="{y - 9}" width="10" height="10" rx="2" fill="{C_LILLY}"/>' + t(256, y, 'Lilly', 12))
    out.append(t(W - 32, y, 'bar = share of the range\'s code matched', 12, C_MUTED, 'end'))
    y += 22
    out.append(t(52, y, 'Range', 11, C_MUTED) + t(560, y, 'Code done', 11, C_MUTED, 'end')
               + t(650, y, 'Funcs left', 11, C_MUTED, 'end') + t(760, y, 'Instr. left', 11, C_MUTED, 'end')
               + t(W - 32, y, 'Biggest left', 11, C_MUTED, 'end'))
    y += 8
    buckets = {}
    for a, (name, s) in real.items():
        b = buckets.setdefault(a >> 16, {'fi': 0, 'ti': 0, 'fl': 0, 'il': 0, 'big': 0, 'own': {}})
        b['own'][owner(a)] = b['own'].get(owner(a), 0) + s // 4
        b['ti'] += s // 4
        if a in matched_addrs:
            b['fi'] += s // 4
        else:
            b['fl'] += 1
            b['il'] += s // 4
            b['big'] = max(b['big'], s // 4)
    for k in sorted(buckets):
        b = buckets[k]
        lo = k << 16
        frac = b['fi'] / b['ti'] if b['ti'] else 1
        y += 22
        oc = {'me': C_ME, 'naga': C_COLLAB, 'lilly': C_LILLY}[max(b['own'], key=b['own'].get)]
        out.append(f'<rect x="32" y="{y - 11}" width="10" height="12" rx="2" fill="{oc}"/>')
        out.append(t(52, y, f'0x{lo:06X}–0x{lo + 0x10000:06X}', 12, weight='bold' if frac == 1 else 'normal'))
        out.append(bar(250, y - 11, 250, 12, frac, C_DONE2 if frac < 1 else C_DONE, 3))
        out.append(t(560, y, f'{frac:.0%}', 12, anchor='end'))
        out.append(t(650, y, f'{b["fl"]:,}' if b['fl'] else 'done', 12, C_MUTED if not b['fl'] else C_TEXT, 'end'))
        out.append(t(760, y, f'{b["il"]:,}' if b['il'] else '—', 12, anchor='end'))
        out.append(t(W - 32, y, f'{b["big"]:,} instr.' if b['big'] else '—', 12, C_MUTED, 'end'))
    y += 20

    # ---- remaining by function size
    out.append('<!-- By Function Size Section -->')
    y += 24
    out.append(t(32, y, 'What\'s left, by function size', 16, weight='bold'))
    sizes = [(1, 20, 'Tiny (≤20 instr.)'), (21, 100, 'Small (21–100)'), (101, 300, 'Medium (101–300)'),
             (301, 1000, 'Large (301–1,000)'), (1001, 10 ** 9, 'Huge (1,000+)')]
    y += 10
    for lo, hi, lab in sizes:
        tot = [s // 4 for a, (_, s) in real.items() if lo <= s // 4 <= hi]
        left = [s // 4 for a, (_, s) in real.items() if lo <= s // 4 <= hi and a not in matched_addrs]
        if not tot:
            continue
        frac = 1 - len(left) / len(tot)
        y += 26
        out.append(t(32, y, lab, 12))
        out.append(bar(190, y - 12, 350, 14, frac, C_DONE, 3))
        out.append(t(630, y, f'{frac:.0%} done', 12, anchor='end'))
        out.append(t(W - 32, y, f'{len(left):,} of {len(tot):,} functions left · {sum(left):,} instr.', 12, C_MUTED, 'end'))
    y += 30
    out.append(t(32, y, 'Generated by tools/progress_graph.py from config/matched.csv (refreshed automatically on every push).', 11, C_MUTED))
    H = y + 24
    svg = (f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{H}" viewBox="0 0 {W} {H}" '
           f'font-family="-apple-system,BlinkMacSystemFont,Segoe UI,Helvetica,Arial,sans-serif">'
           '\n' + pretty([f'<rect width="{W}" height="{H}" rx="12" fill="#ffffff" stroke="{C_GRID}"/>'] + out) + '\n</svg>\n')
    os.makedirs(os.path.dirname(SVG), exist_ok=True)
    with open(SVG, 'w', encoding='utf-8', newline='\n') as f:
        f.write(svg)
    return mf, total_f, mi, total_i


if __name__ == '__main__':
    mf, tf, mi, ti = render(load_functions(), load_matched())
    print(f'docs/progress.svg: {mf:,}/{tf:,} functions ({mf / tf:.2%}), {mi:,}/{ti:,} instructions ({mi / ti:.2%})')
