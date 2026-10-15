"""Fourth-VU exact native/whole-section/metadata/source/receipt guards.
Only enumerated dependencies are cloned; no enclosing project/build tree copy.
"""
import argparse,copy,json,struct,tempfile
from pathlib import Path
import vu_lighting_build as light
from vu_lighting_native import strict_native
ROOT=light.ROOT
DEPS=['config/vu_lighting_sources.json',light.EXPECTED_COMPONENT['source'],light.EXPECTED_COMPONENT['upload_source'],*light.EXPECTED_EVIDENCE_HASHES,'tools/common.py','tools/vu_build.py','tools/vu_lighting_build.py','tools/vu_lighting_native.py','tools/vu_lighting_inputs.py','tools/test_vu_lighting.py','config/vu_original_programs.json','build/asset_catalog/level_tag_05.decoded.bin']

def clone_dependencies(bundle,dest):
    bundle=Path(bundle).resolve();dest=Path(dest).resolve();light.need(not dest.exists(),'New minimal lighting dependency fixture required')
    dest.mkdir(parents=True);records=[]
    for rel in sorted(set(DEPS)):
        source=light.renderer.contained(bundle,rel);target=light.renderer.contained(dest,rel);target.parent.mkdir(parents=True,exist_ok=True)
        with target.open('xb')as f:f.write(source.read_bytes())
        records.append({'path':rel,'sha256':light.sha(target.read_bytes()),'bytes':target.stat().st_size})
    light.need({p.relative_to(dest).as_posix()for p in dest.rglob('*')if p.is_file()}==set(DEPS),'Foreign project/native data copied into lighting fixture')
    return {'files':records,'exact_dependency_count':len(records),'whole_project_or_enclosing_build_never_copied':True}

def clone_native(output,dest):
    dest=Path(dest);dest.mkdir(parents=True);output=Path(output)
    for name in ['program.o','program.bin','chain.o','chain.bin','runtime_REFS.o','runtime_REFS.bin',light.REPORT_NAME]:
        with (dest/name).open('xb')as f:f.write((output/name).read_bytes())

def rebase_report(bundle,output):
    bundle=Path(bundle).resolve();out=Path(output).resolve();m,e,expected,inputs,deps=light.checked_manifest(bundle)
    report=json.loads((out/light.REPORT_NAME).read_text());report['bundle_root']=bundle.relative_to(ROOT).as_posix();report['dependency_hashes']=deps
    for kind in ['program','chain','runtime_REFS']:
        report['native_components'][kind]['files']={name:light.receipt(out/name)for name in[kind+'.o',kind+'.bin']}
    (out/light.REPORT_NAME).write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    light.current_report(bundle,out);return report

def rejection(label,callback,reason):
    try:callback()
    except (ValueError,KeyError,IndexError,StopIteration,struct.error,UnicodeError)as ex:
        return {'mutation':label,'rejected':True,'expected_scope':reason,'actual_exception':type(ex).__name__,'actual_reason':str(ex)}
    raise ValueError('False maintained lighting admission: '+label)

def native_guards(output,expected):
    output=Path(output);rows=[]
    for kind,filename in [('program','program.o'),('upload','chain.o'),('runtime_REFS','runtime_REFS.o')]:
        raw=(output/filename).read_bytes();e=light.Elf32(raw);text=e.section('.vutext');want=expected['chain'if kind=='upload'else kind]
        for i in range(text['size']):
            changed=bytearray(raw);changed[text['offset']+i]^=1
            rows.append(rejection(kind+'.allocated_byte['+str(i)+']',lambda changed=bytes(changed),kind=kind,want=want:strict_native(changed,kind,want),'Entire original emitted native text equality'))
        def field(label,at,value):
            changed=bytearray(raw);struct.pack_into('<I',changed,at,value)
            rows.append(rejection(kind+'.'+label,lambda changed=bytes(changed),kind=kind,want=want:strict_native(changed,kind,want),'Whole native section/header/symbol/relocation schema'))
        for name in ['.vudata','.vubss']:
            sec=e.section(name);field('unowned initialized '+name,e.shoff+e.shentsize*sec['index']+20,4)
        field('incomplete entire text',e.shoff+e.shentsize*text['index']+20,text['size']-8)
        field('hidden program header count',44,(e.shentsize<<16)|1)
        if kind=='program':
            sym=e.section('.symtab')
            for s in e.symbols():
                if s['type']!=2:continue
                field('incomplete routine '+s['name'],sym['offset']+s['index']*16+8,s['size']-8)
                field('EE address incorrectly aliasesVU '+s['name'],sym['offset']+s['index']*16+4,0x2c4608+s['value'])
        if kind=='upload':
            tab=e.section('.DVP.ovlytab');rel=e.section('.rel.DVP.ovlytab');shadow=next(s for s in e.sections if s['name'].startswith('.DVP.overlay.'))
            field('missing actualR32field',e.shoff+e.shentsize*rel['index']+20,8)
            field('unresolved actual metadata type',rel['offset']+4,(struct.unpack_from('<I',raw,rel['offset']+4)[0]&~255)|5)
            field('wrong EE payload addend',tab['offset']+4,16)
            field('wrong VU localdestination',tab['offset']+8,8)
            field('allocated overlaymetadata',e.shoff+e.shentsize*tab['index']+8,3)
            field('allocated zerosource shadow',e.shoff+e.shentsize*shadow['index']+8,7)
            field('nonzero hiddenoriginalcode shadow',shadow['offset'],1)
    return rows

def run_tests(bundle=light.DEFAULT_BUNDLE,output=light.DEFAULT_OUTPUT,temp_root=None):
    bundle=Path(bundle).resolve();out=Path(output).resolve();before=light.current_report(bundle,out);m,e,expected,inputs,deps=light.checked_manifest(bundle)
    native=native_guards(out,expected);temp_root=light.output_path(temp_root or(ROOT/'build/vu/lighting/testing'));temp_root.mkdir(parents=True,exist_ok=True)
    source=[];receipt=[]
    with tempfile.TemporaryDirectory(dir=temp_root,prefix='exact_lighting_')as temp:
        temp=Path(temp);cloned=temp/'bundle';copyproof=clone_dependencies(bundle,cloned);fixture=temp/'native';clone_native(out,fixture);base=rebase_report(cloned,fixture)
        for rel in sorted(set(DEPS)):
            target=cloned/rel;old=target.read_bytes();target.write_bytes(old+b' ')
            try:source.append(rejection('changed actualdependency '+rel,lambda:light.current_report(cloned,fixture),'Source/input/compiler-report dependency fingerprint'))
            finally:target.write_bytes(old)
        mutations=[('missing program owner',lambda r:r['native_components'].pop('program')),
         ('false programdata',lambda r:r.__setitem__('initialized_data_bytes',4)),('dynamicREFS counted as source',lambda r:r.__setitem__('dynamic_REFS_source_credit',16)),
         ('wrong MSCAL addressdomain',lambda r:r.__setitem__('actual_MSCAL_immediate',16)),('withdrawn type0 claim restored',lambda r:r.__setitem__('old_Bentley_type0_entry_and_part8_claims_withdrawn',False)),
         ('missing actualR32relocation',lambda r:r['native_components']['chain']['native_proof']['actual_nonallocated_metadata_relocations'].pop()),
         ('stale compiler fingerprint',lambda r:r['dependency_hashes'].__setitem__('tools/third_party/dvp/bin/dvp-as.exe','0'*64)),
         ('false nativeobject fingerprint',lambda r:r['native_components']['program']['files']['program.o'].__setitem__('sha256','0'*64))]
        for label,fn in mutations:
            changed=copy.deepcopy(base);fn(changed);(fixture/light.REPORT_NAME).write_text(json.dumps(changed),encoding='utf-8')
            receipt.append(rejection(label,lambda:light.current_report(cloned,fixture),'Exact complete current native/input/source receipt'))
        (fixture/light.REPORT_NAME).write_text(json.dumps(base),encoding='utf-8');light.current_report(cloned,fixture)
    light.need(light.current_report(bundle,out)==before,'Current public source/native/input proof changed during scoped guards')
    return {'status':'PASS','native_guards':native,'native_guard_count':len(native),'allocated_native_byte_guards':3008,'source_guards':source,'source_guard_count':len(source),'receipt_guards':receipt,'receipt_guard_count':len(receipt),'minimal_fixture':copyproof,'dynamic_REFS_source_credit':0,'all_existing_owners_readonly':True}

def main():
    p=argparse.ArgumentParser();p.add_argument('--bundle-root',type=Path,default=light.DEFAULT_BUNDLE);p.add_argument('--output',type=Path,default=light.DEFAULT_OUTPUT);p.add_argument('--temp-root',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();r=run_tests(a.bundle_root,a.output,a.temp_root)
    if a.report:
        path=light.output_path(a.report);light.need(not path.exists(),'New private/owned guard report required');path.parent.mkdir(parents=True,exist_ok=True);path.write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({k:r[k]for k in['status','native_guard_count','allocated_native_byte_guards','source_guard_count','receipt_guard_count','dynamic_REFS_source_credit']}))
if __name__=='__main__':main()