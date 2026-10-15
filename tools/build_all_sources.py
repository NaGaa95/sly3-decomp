"""Build every currently admitted EE/IOP/VU source component and save a checkpoint.

This remains a partial rebuild: unrecovered code, data, metadata and VU programs
are original preservation inputs, excluded from all source-completion totals.
The separate VU build consumes native VSM/VIF uploads into its own partial ELF;
EE C/C++ and VU instruction/protocol accounting remain distinct.
"""
from common import ROOT


def main():
    from build_source import main as build_ee
    from iop_sources import build_components
    from vu_union_sources import build_components as build_vu
    from inventory import main as inventory
    from report_progress import main as report

    build_ee()
    build_components()
    build_vu()
    inventory()
    report()
    print('PASS all currently admitted source components; full game source relinking remains incomplete.')


if __name__ == '__main__':
    main()
