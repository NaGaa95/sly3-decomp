"""Write the whole-executable component scope (main EE, IOP modules, VU programs)."""
import csv
import json
from common import ROOT, Elf32, target_config, save_json


def main():
    matched_path = ROOT / "config/matched.csv"
    matched = {int(row["address"], 16): row for row in csv.DictReader(matched_path.open())} if matched_path.exists() else {}
    remaining = []
    for row in csv.DictReader((ROOT / "config/functions.csv").open()):
        if int(row["Start"], 16) not in matched:
            remaining.append(row)
    target = target_config()
    elf = Elf32((ROOT / "disc" / target["serial"]).read_bytes())
    from iop_sources import current_modules
    iop_proofs = {module['module']: module for module in current_modules()}
    iop = []
    for entry in json.loads((ROOT / "disc/irx/manifest.json").read_text()):
        module = Elf32((ROOT / "disc/irx" / entry["file"]).read_bytes())
        component = {**entry, "entry": module.entry, "elf_type": module.type, "code_sections": [{"name": s["name"], "address": s["addr"], "size": s["size"]} for s in module.sections if s["flags"] & 4 and s["size"]], "decompilation_status": "preserved-not-decompiled", "verified_source_functions": 0, "verified_source_code_bytes": 0, "verified_source_initialized_data_bytes": 0}
        proof = iop_proofs.get('disc/irx/' + entry['file'])
        if proof:
            iop_proof = proof
            component.update(iop_proof['progress'])
            component.update(decompilation_status='partial-C-source-build',
                             source_evidence=iop_proof['source_evidence'],
                             source_claims=iop_proof['source_claims'],
                             source_data_objects=iop_proof.get('data_objects', []),
                             source_evidence_freshness=iop_proof['freshness'],
                             original_metadata_imports_exports_relocations_and_bss='preserved-not-rebuilt-from-source',
                             historical_compiler_and_general_o32_abi='unconfirmed',
                             full_module_source_relink_complete=False)
        iop.append(component)
    vu = [{"name": s["name"], "address": s["addr"], "size": s["size"], "offset": s["offset"], "decompilation_status": "preserved-not-decompiled"} for s in elf.sections if "vu" in s["name"].lower() or s["name"].lower().startswith(".dvp")]
    from vu_union_sources import summarize as vu_summary, current_programs as vu_programs
    vu_totals = vu_summary()
    vu_program_inventory = vu_programs()
    iop_totals = {key: sum(item[key] for item in iop) for key in ('verified_source_functions', 'verified_source_code_bytes', 'verified_source_initialized_data_bytes')}
    save_json(ROOT / "build/reports/component_inventory.json", {"target": target["serial"], "main_ee": {"text_bytes": target["text"]["size"], "verified_function_count": len(matched), "remaining_function_candidates": len(remaining), "boundaries_provisional_except_overrides": True}, "embedded_iop_modules": iop, "iop_source_totals": iop_totals, "vu_sections": vu, "vu_source_totals": vu_totals, "vu_programs": vu_program_inventory, "vu_nonallocated_zero_shadows_excluded_from_source": 29, "VU_address_domain_is_separate_from_EE": True, "full_cpp_relink_complete": False, "disc_archive": {"path": "disc/SLY3.WAD", "size": (ROOT / "disc/SLY3.WAD").stat().st_size, "extracted_intact": True, "individual_asset_catalogue_recovered": True, "named_nonempty_worlds":39, "verified_module_boundaries":7151, "verified_top_factory_headers":46221, "catalogue_proof":"build/reports/asset_catalog_named_worlds_control_scope.json", "nested_runtime_alias_domains_complete":False, "extracted_assets_count_as_source_code":False}})
    print(f"Remaining: {len(remaining):,} main EE candidates; {vu_totals['original_unique_program_count']-vu_totals['verified_source_programs']} VU programs / {vu_totals['unrecovered_VU_code_bytes']:,} instruction bytes. Verified source covers {len(iop_proofs)} of {len(iop)} IOP module identities.")


if __name__ == "__main__":
    main()

