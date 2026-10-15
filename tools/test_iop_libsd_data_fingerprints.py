"""Private primary/original/native fingerprint rejection tests, with no writes
to protected dependencies. The current data receipt must be fresh before each
simulated mismatch; original allocated-domain fixtures remain in memory.
"""
import json,struct,sys,time
from pathlib import Path
from unittest.mock import patch
ROOT=Path(__file__).resolve().parents[1];STAGE=ROOT/'build/iop/module_04_data'
sys.path.insert(0,str(STAGE));sys.path.insert(0,str(ROOT/'tools'))
import iop_libsd_data_build as v
from common import Elf32,sha256_file

def main():
 start=time.time();guards=[];manifest=json.loads(v.DEFAULT_MANIFEST.read_text());v.current_report()
 protected=[ROOT/p for p in(v.PRIMARY,v.REGISTERS,v.PROVENANCE,v.PROOF,v.TABLE_PROOF,v.FLOW_PROOF,v.MODULE)];before={str(p):sha256_file(p)for p in protected}
 def rejected(name,fn):
  try:fn()
  except (ValueError,FileNotFoundError,KeyError,StopIteration,struct.error)as e:guards.append({'name':name,'status':'REJECTED','reason':str(e)});return
  raise AssertionError('Guard accepted: '+name)
 real_sha=v.sha256_file
 for relative in(v.PRIMARY,v.REGISTERS,v.PROVENANCE,v.PROOF,v.TABLE_PROOF,v.FLOW_PROOF):
  changed=(ROOT/relative).resolve()
  def stale_sha(path,changed=changed):return '0'*64 if Path(path).resolve()==changed else real_sha(path)
  with patch.object(v,'sha256_file',stale_sha):rejected('stale_primary_or_proof:'+relative,lambda:v.validate_manifest(manifest))
 real_read=Path.read_bytes;module=(ROOT/v.MODULE).resolve()
 def stale_module(path):
  raw=real_read(path)
  if path.resolve()==module:raw=raw[:-1]+bytes([raw[-1]^1])
  return raw
 with patch.object(Path,'read_bytes',stale_module):rejected('stale_complete_original_module',v.load_original)
 # Every actual compiler-stage/assembler fingerprint is a separate required
 # input. These simulations never alter installed binaries or original files.
 real_inputs=v.native_inputs
 for revision in(114,136):
  for dependency in real_inputs(revision):
   def stale_inputs(asked,revision=revision,dependency=dependency):
    result=real_inputs(asked)
    if asked==revision:result[dependency]='0'*64
    return result
   with patch.object(v,'native_inputs',stale_inputs):rejected('native_'+str(revision)+':'+dependency,v.current_report)
 raw,original=v.load_original()
 def section_fixture(name,key,value):
  section=original.section(name);out=bytearray(raw);keys=['name_offset','type','flags','addr','offset','size','link','info','alignment','entsize'];struct.pack_into('<I',out,original.shoff+section['index']*original.shentsize+4*keys.index(key),value);return Elf32(bytes(out))
 for name,key,value in[('.data','flags',1),('.data','type',8),('.data','addr',0x4AC0),('.data','offset',0),('.data','size',680)]:
  rejected('original_allocated_domain:'+name+':'+key,lambda name=name,key=key,value=value:v.validate_original(section_fixture(name,key,value)))
 # A nonallocated overlapping .iopmod must not become a second readable owner.
 meta=original.section('.iopmod');out=bytearray(raw)
 for key,value in[('flags',2),('addr',v.START),('size',v.SIZE)]:
  keys=['name_offset','type','flags','addr','offset','size','link','info','alignment','entsize'];struct.pack_into('<I',out,original.shoff+meta['index']*original.shentsize+4*keys.index(key),value)
 rejected('original_allocated_domain:overlapping_metadata',lambda:v.validate_original(Elf32(bytes(out))))
 after={str(p):sha256_file(p)for p in protected};assert before==after,'Protected dependencies changed'
 current=v.current_report();assert current['progress']['verified_source_initialized_data_bytes']==680
 report={'status':'PASS_MAINTAINED_PRIMARY_ORIGINAL_AND_NATIVE_FINGERPRINT_GUARDS','guard_count':len(guards),'guards':guards,'protected_hashes_unchanged':True,'protected_hashes':{str(Path(p).relative_to(ROOT)):h for p,h in before.items()},'whole_current_data_report':current['freshness'],'test_sha256':sha256_file(Path(__file__)),'elapsed_seconds':time.time()-start,'public_mutations':False}
 (STAGE/'fingerprint_guard_results.json').write_text(json.dumps(report,indent=2)+'\n');print('PASS',len(guards),'primary/original/native guards;no protected file writes',flush=True)

if __name__=='__main__':main()
