"""Meaningful negative native ownership/freshness tests; frozen receipts are never overwritten."""
import argparse
import copy
import json
import struct
import tempfile
from pathlib import Path
from vu_build import DEFAULT_BUNDLE, DEFAULT_OUTPUT, EXPECTED, PROJECT, Elf32, checked_manifest, current_report, inspect_native, original_mapping, sha, source_totals, file_receipt, REPORT_NAME, validate_program, validate_upload

def guards(program,upload,original_program,original_upload):
 tests=[]
 def mutate(data,label,fields):
  b=bytearray(data)
  for pos,val in fields:struct.pack_into('<I',b,pos,val)
  return label,bytes(b)
 def shpos(e,index,field):return struct.unpack_from('<I',e.data,32)[0]+struct.unpack_from('<H',e.data,46)[0]*index+field
 pe=Elf32(program);pt=next(s for s in pe.sections if s['name']=='.vutext');psym=next(s for s in pe.sections if s['name']=='.symtab')
 ptests=[]
 for name,off,size in EXPECTED:
  ptests.append(mutate(program,'different complete '+name,[(pt['offset']+off,struct.unpack_from('<I',program,pt['offset']+off)[0]^1)]))
  f=next(s for s in pe.symbols() if s['name']==name)
  ptests.append(mutate(program,'partial declared '+name,[(psym['offset']+16*f['index']+8,size-8)]))
 ptests.extend([mutate(program,'truncated native text',[(shpos(pe,pt['index'],20),2232)]),mutate(program,'branch displacement differs',[(pt['offset']+0x170,0x52016803)]),mutate(program,'floating immediate depth differs',[(pt['offset']+0x300,0x40800001)]),mutate(program,'missing final delay',[(pt['offset']+0x8b8,0x10030001)])])
 for name in ['.vudata','.vubss']:
  s=next(s for s in pe.sections if s['name']==name);ptests.append(mutate(program,'extra '+name,[(shpos(pe,s['index'],20),16)]))
 ue=Elf32(upload);ut=next(s for s in ue.sections if s['name']=='.vutext');tab=next(s for s in ue.sections if s['name']=='.DVP.ovlytab');rel=next(s for s in ue.sections if s['name']=='.rel.DVP.ovlytab')
 utests=[mutate(upload,'wrong first MPG count',[(ut['offset']+4,0x4aff0000)]),mutate(upload,'wrong second MPG PC',[(ut['offset']+2060,0x4a180101)]),mutate(upload,'missing metadata relocation',[(shpos(ue,rel['index'],20),24)]),mutate(upload,'wrong metadata relocation kind',[(rel['offset']+4,struct.unpack_from('<I',upload,rel['offset']+4)[0]&~255|5)]),mutate(upload,'wrong second payload mapping',[(tab['offset']+16,2060)]),mutate(upload,'wrong second virtual mapping',[(tab['offset']+20,2056)]),mutate(upload,'allocated metadata table',[(shpos(ue,tab['index'],8),3)])]
 for s in ue.sections:
  if s['name'].startswith('.DVP.overlay.'):
   utests.extend([mutate(upload,'nonzero shadow '+s['name'],[(s['offset'],1)]),mutate(upload,'allocated shadow '+s['name'],[(shpos(ue,s['index'],8),7)])])
 for profile,candidates,validator,expected in [('program',ptests,validate_program,original_program),('upload',utests,validate_upload,original_upload)]:
  for label,b in candidates:
   try:validator(b,expected)
   except (ValueError,AssertionError,IndexError,struct.error,StopIteration) as ex:tests.append({'profile':profile,'mutation':label,'rejected':True,'reason':str(ex)})
   else:raise AssertionError('false native admission '+label)
 return tests

def execute_lane_bits(code,memory,vf,vi):
 # Interpreter only covers these actual bit-move/kick operations. Tokens are
 # allowed as lane values, so no accidental host float interpretation occurs.
 memory={a:list(v) for a,v in memory.items()};vf={a:list(v) for a,v in vf.items()};vi=dict(vi);kicks=[];end=None
 for index,(lo,hi) in enumerate(struct.iter_unpack('<II',code)):
  assert hi&~0x40000000==0x2ff and vi[0]==0
  if end is not None:assert index==end+1
  op=lo>>25;mask=(lo>>21)&15
  if op==0:
   base=vi[(lo>>11)&31];reg=(lo>>16)&31;offset=lo&2047;offset=offset-2048 if offset&1024 else offset
   for lane in range(4):
    if mask&(8>>lane):vf[reg][lane]=memory[base+offset][lane]
  elif op==1:
   base=vi[(lo>>16)&31];reg=(lo>>11)&31;offset=lo&2047;offset=offset-2048 if offset&1024 else offset
   for lane in range(4):
    if mask&(8>>lane):memory[base+offset][lane]=vf[reg][lane]
  elif op==8:
   imm=((lo>>21)&15)*2048+(lo&2047);vi[(lo>>16)&31]=(vi[(lo>>11)&31]+imm)&65535
  elif lo==0x80001efc:kicks.append((vi[3],[list(x) for x in [memory[vi[3]],memory[vi[3]+1]]]))
  elif lo!=0x8000033c:raise ValueError('unsupported instruction in selected routine')
  if hi&0x40000000:end=index
  if end is not None and index==end+1:break
 assert end==6 and index==7
 return memory,vf,vi,kicks

def verify_bit_semantics(original):
 trials=0
 for entry,packet in [(192,23),(256,25)]:
  # Arbitrary symbolic tokens prove all32 bits transported unchanged, while
  # all other data/register lanes are distinct and therefore testable.
  states=[{'parameter':f'input_bit_word_{entry}','seed':'symbolic'}]
  states.extend({'parameter':(x*0x9e3779b1)&0xffffffff,'seed':x} for x in range(65536))
  for state in states:
   seed=state['seed'];memory={a:[f'mem{a}:{lane}:{seed}' for lane in range(4)] for a in [12,23,24,25,26]};memory[12][0]=state['parameter'];vf={1:[f'vf1:{lane}:{seed}' for lane in range(4)]};vi={0:0,3:0xabcd}
   actual=execute_lane_bits(original[entry:entry+64],memory,vf,vi)
   expected_memory={a:list(v) for a,v in memory.items()};expected_memory[packet+1][0]=memory[12][0]
   expected_vf={1:list(vf[1])};expected_vf[1][0]=memory[12][0];expected_vi={0:0,3:packet}
   expected_kicks=[(packet,[list(expected_memory[packet]),list(expected_memory[packet+1])])]
   assert actual==(expected_memory,expected_vf,expected_vi,expected_kicks)
   trials+=1
 return {'bit_lane_states':trials,'symbolic_bit_word_transfer_proved':True,'numerical_float_interpretation':False,'preserved_other_VF1_lanes_and_all_other_memory_words':True,'flags_Q_P_and_other_registers_unaccessed_by_original_operations':True,'hardware_stalls_and_GIF_bus_execution_not_simulated':True}

def copy_component_dependencies(bundle, destination):
    """Copy exactly the verified VU files, never an enclosing project tree.

    The default PUBLIC bundle is the project root. Its disc, reference, EE,
    IOP, environment and build trees must remain outside temporary rejection
    fixtures even when the destination happens to be under that same root.
    """
    bundle=Path(bundle).resolve();destination=Path(destination).resolve()
    _,_,_,_,_,freshness,_=checked_manifest(bundle)
    rows=[row for row in freshness if 'path'in row]
    if len(rows)!=21 or len({r['path']for r in rows})!=21:
        raise ValueError('Exact complete VU component dependency set required')
    copied=[]
    for row in rows:
        source=(bundle/row['path']).resolve();target=(destination/row['path']).resolve()
        if not source.is_relative_to(bundle)or not target.is_relative_to(destination):
            raise ValueError('Fixture copy escapes its exact VU dependency ownership')
        data=source.read_bytes()
        if len(data)!=row['bytes']or sha(data)!=row['sha256']:
            raise ValueError('Source/tool dependency changed before fixture copy')
        target.parent.mkdir(parents=True,exist_ok=True)
        with target.open('xb')as stream:stream.write(data)
        copied.append(row['path'])
    actual={p.relative_to(destination).as_posix()for p in destination.rglob('*')if p.is_file()}
    if actual!=set(copied):raise ValueError('Unexpected project content copied into rejection fixture')
    return {'files':len(copied),'bytes':sum(r['bytes']for r in rows),'only_checked_component_dependencies':True,'project_disc_build_references_IOP_and_environment_not_copied':True}

def copy_native_fixture(output,destination):
    """Copy only five exact native receipt files, never an output directory."""
    output=Path(output).resolve();destination=Path(destination).resolve()
    names=['program.o','upload.o','renderer_upload.bin','SCUS_974.64.vu-source.elf',REPORT_NAME]
    destination.mkdir(parents=True,exist_ok=False)
    for name in names:
        source=(output/name).resolve();target=(destination/name).resolve()
        if not source.is_relative_to(output)or not target.is_relative_to(destination):
            raise ValueError('Native fixture path escapes output ownership')
        with target.open('xb')as stream:stream.write(source.read_bytes())

def verify_rejections(program_object,upload_object,bundle=DEFAULT_BUNDLE,output=None,temp_root=None):
    _,program,upload,_=original_mapping()
    tests=guards(program_object,upload_object,program,upload)
    bitstates=verify_bit_semantics(program)
    if len(tests)!=33 or bitstates['bit_lane_states']!=131074:raise ValueError('Incomplete meaningful native rejection/lane test suite')
    # Independently exercise malformed ABI/domain labels, empty-section schemas,
    # extra control ownership, unexpected source includes, and real metadata fields.
    pe=Elf32(program_object);ue=Elf32(upload_object);ps=pe.section('.symtab');us=ue.section('.symtab');tab=ue.section('.DVP.ovlytab');rel=ue.section('.rel.DVP.ovlytab')
    extra=[]
    def mutation(raw,label,pos,fmt,value,validator,target):
        data=bytearray(raw);struct.pack_into(fmt,data,pos,value)
        try:validator(bytes(data),target)
        except (ValueError,AssertionError,IndexError,KeyError,StopIteration,struct.error):extra.append({'mutation':label,'rejected':True})
        else:raise ValueError('False source/native ownership admission: '+label)
    for name,begin,size in EXPECTED:
        symbol=next(s for s in pe.symbols()if s['name']==name)
        mutation(program_object,'EE alias used for VU '+name,ps['offset']+16*symbol['index']+4,'I',0x2c1420+begin,validate_program,program)
        mutation(program_object,'wrong VU st_other '+name,ps['offset']+16*symbol['index']+13,'B',0,validate_program,program)
        alias=next(s for s in ue.symbols()if s['name']=='_$'+name)
        mutation(upload_object,'wrong upload stored alias '+name,us['offset']+16*alias['index']+4,'I',begin,validate_upload,upload)
    for name in ['.vudata','.vubss']:
        s=pe.section(name);mutation(program_object,'unsupported empty allocated kind '+name,pe.shoff+pe.shentsize*s['index']+4,'I',0x7fffffff,validate_program,program)
    mutation(upload_object,'metadata duplicate relocation',rel['offset']+24,'I',12,validate_upload,upload)
    mutation(upload_object,'wrong metadata string reference',tab['offset'],'I',0xffffff,validate_upload,upload)
    mutation(program_object,'hidden native load segment',44,'H',1,validate_program,program)
    # Manifest and report mutations use private temporary bundles/output copies.
    # Each throws before assembler execution, and no live report is altered.
    checks=[]
    temp_root=Path(temp_root or(PROJECT/'build/vu/testing')).resolve()
    if not temp_root.is_relative_to(PROJECT/'build/vu')and not temp_root.is_relative_to(PROJECT/'build/vu_matches'):raise ValueError('Test temporary output escapes VU lane')
    temp_root.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='negative_',dir=temp_root)as temp:
        temp=Path(temp)
        import shutil
        component_copy=copy_component_dependencies(bundle,temp/'bundle');clone=temp/'bundle'
        cases=[('source raw instruction copy','src/vu/renderer_program.vsm',lambda b:b+b'\n.word 0\n'),('foreign source include','src/vu/renderer_upload.vif',lambda b:b.replace(b'renderer_program.vsm',b'foreign_program.vsm')),('duplicate old128 source owner','config/vu_sources.json',lambda b:_duplicate(b)),('preserved zero shadow source count','config/vu_sources.json',lambda b:_count(b)),('false historical compiler claim','config/vu_sources.json',lambda b:_compiler(b)),('changed portable assembler','tools/third_party/dvp/bin/dvp-as.exe',lambda b:b[:-1]+bytes([b[-1]^1])),('changed required runtime','tools/third_party/dvp/bin/libzstd.dll',lambda b:b[:-1]+bytes([b[-1]^1])),('missing original CPU entry proof','docs/evidence/vu_renderer_input_review.json',lambda b:b+b' '),('changed independent parent review','docs/evidence/vu_renderer_parent_review.json',lambda b:b+b' '),('wrong original VU inventory','config/vu_original_programs.json',lambda b:b+b' ')]
        for label,relative,fn in cases:
            p=clone/relative;old=p.read_bytes();p.write_bytes(fn(old))
            try:checked_manifest(clone)
            except (ValueError,AssertionError,KeyError,IndexError):checks.append({'mutation':label,'rejected':True})
            else:raise ValueError('False source/provenance admission: '+label)
            finally:p.write_bytes(old)
    if output is not None:
        current=current_report(bundle,output)
        if current['native_proof']!=inspect_native(program_object,upload_object,program,upload):raise ValueError('Current native proof mismatch')
        with tempfile.TemporaryDirectory(prefix='receipt_negative_',dir=temp_root)as temp:
            clone=Path(temp)/'output';copy_native_fixture(output,clone)
            base=json.loads((clone/REPORT_NAME).read_text());base['objects']={mode:file_receipt(clone/(mode+'.o'),PROJECT)for mode in ['program','upload']};base['partial_source_elf']=file_receipt(clone/'SCUS_974.64.vu-source.elf',PROJECT);base['source_derived_upload_binary']=file_receipt(clone/'renderer_upload.bin',PROJECT)
            (clone/REPORT_NAME).write_text(json.dumps(base),encoding='utf-8');current_report(bundle,clone)
            receipt_cases=[('stale source/verifier receipt',lambda d:d['freshness_inputs'].pop()),('wrong dependency hash',lambda d:d['dependency_hashes'].__setitem__('disc/SCUS_974.64','0'*64)),('duplicate source/code count',lambda d:d['progress'].__setitem__('verified_source_code_bytes',4480)),('VIF protocol wrongly counted as code',lambda d:d['progress'].__setitem__('verified_source_VU_code_bytes',2256)),('missing entire upload proof',lambda d:d['objects'].pop('upload')),('false full source relink',lambda d:d.__setitem__('full_source_relink_complete',True)),('missing native overlay relocation',lambda d:d['native_proof']['all_actual_nonallocated_overlay_relocations'].pop()),('missing original CPU protocol body',lambda d:d.__setitem__('complete_original_CPU_protocol_body_count',33))]
            for label,fn in receipt_cases:
                altered=copy.deepcopy(base);fn(altered);(clone/REPORT_NAME).write_text(json.dumps(altered),encoding='utf-8')
                try:current_report(bundle,clone)
                except (ValueError,AssertionError,KeyError,IndexError):checks.append({'mutation':label,'rejected':True})
                else:raise ValueError('False aggregate source/native report admission: '+label)
            (clone/REPORT_NAME).write_text(json.dumps(base),encoding='utf-8')
            obj=clone/'program.o';old=obj.read_bytes();obj.write_bytes(old[:-1]+bytes([old[-1]^1]))
            try:current_report(bundle,clone)
            except (ValueError,AssertionError,KeyError,IndexError):checks.append({'mutation':'changed current whole native object','rejected':True})
            else:raise ValueError('Changed current whole native object was admitted')
    return {'native_object_guards':tests,'additional_native_guards':extra,'source_and_provenance_guards':checks,'frame_raw_lane_semantics':bitstates,'temporary_component_copy':component_copy,'native_guard_count':len(tests)+len(extra),'source_guard_count':len(checks),'full_NATIVE_instruction_streams_and_initialized_data_checked':True}

def _duplicate(data):
    d=json.loads(data);d['components'].append(copy.deepcopy(d['components'][0]));return json.dumps(d).encode()
def _count(data):
    d=json.loads(data);d['components'][0]['whole_program_code_bytes']+=2240;return json.dumps(d).encode()
def _compiler(data):
    d=json.loads(data);d['historical_original_compiler_identity_confirmed']=True;return json.dumps(d).encode()

def main():
    p=argparse.ArgumentParser();p.add_argument('--bundle-root',type=Path,default=DEFAULT_BUNDLE);p.add_argument('--output',type=Path,default=DEFAULT_OUTPUT);p.add_argument('--report',type=Path);p.add_argument('--temp-root',type=Path)
    a=p.parse_args();r=verify_rejections((a.output/'program.o').read_bytes(),(a.output/'upload.o').read_bytes(),a.bundle_root,a.output,a.temp_root)
    if a.report:
        out=a.report.resolve()
        if not out.is_relative_to(PROJECT/'build/vu')and not out.is_relative_to(PROJECT/'build/vu_matches'):raise ValueError('Test report escapes VU ownership')
        if out.exists():raise ValueError('Test report cannot overwrite an existing/frozen receipt')
        out.write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'status':'PASS','native_guards':r['native_guard_count'],'source_guards':r['source_guard_count'],'raw_lane_states':r['frame_raw_lane_semantics']['bit_lane_states']}))
if __name__=='__main__':main()
