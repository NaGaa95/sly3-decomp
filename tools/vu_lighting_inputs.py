"""Pure complete original incoming/upload/branch/packet review; no native/file writes.
Only consumed GP low64 lanes are replayed. No floats/OS/VU execution is claimed.
"""
import hashlib,json,struct
from pathlib import Path
def sha(data):return hashlib.sha256(data).hexdigest()
def same(a,b):return json.loads(json.dumps(a))==json.loads(json.dumps(b))
def sign(x,n):return x-(1<<n)if x&(1<<(n-1))else x
MASK=(1<<64)-1
def _need(condition,message):
    if not condition:raise ValueError(message)

class Transport:
    """Only original integer operand transport. No game callbacks/VU/floats/OS simulated."""

    def __init__(self, e):
        self.e = e
        self.r = [0] * 32
        self.m = {}
        self.calls = []
        self.steps = 0

    def rd(self, a, n):
        a &= 4294967295
        if a not in self.m:
            raise ValueError(f'Unprovided bounded memory {a:X}/{n}')
        return self.m[a] & (1 << 8 * n) - 1

    def wr(self, a, x, n):
        self.m[a & 4294967295] = x & (1 << 8 * n) - 1

    def set(self, r, x):
        if r:
            self.r[r] = x & MASK

    def one(self, pc):
        w = struct.unpack('<I', self.e.at_vram(pc, 4))[0]
        op = w >> 26
        rs = w >> 21 & 31
        rt = w >> 16 & 31
        rd = w >> 11 & 31
        sh = w >> 6 & 31
        im = w & 65535
        si = sign(im, 16)
        fn = w & 63
        self.steps += 1
        if op == 0:
            if w == 0:
                return
            if fn in (33, 45):
                self.set(rd, self.r[rs] + self.r[rt])
            elif fn == 36:
                self.set(rd, self.r[rs] & self.r[rt])
            elif fn == 37:
                self.set(rd, self.r[rs] | self.r[rt])
            elif fn == 2:
                self.set(rd, sign((self.r[rt] & 4294967295) >> sh, 32))
            elif fn == 0:
                self.set(rd, sign(self.r[rt] << sh & 4294967295, 32))
            elif fn == 3:
                self.set(rd, sign(self.r[rt] & 4294967295, 32) >> sh)
            elif fn == 35:
                self.set(rd, sign(self.r[rs] - self.r[rt] & 4294967295, 32))
            elif fn == 42:
                self.set(rd, int(sign(self.r[rs], 64) < sign(self.r[rt], 64)))
            elif fn == 11:
                if self.r[rt]:
                    self.set(rd, self.r[rs])
            elif fn == 60:
                self.set(rd, self.r[rt] << sh + 32)
            else:
                raise ValueError(f'Unsupported bounded op {pc:X}/{w:X}')
        elif op in (9, 25):
            self.set(rt, sign(self.r[rs] + si & 4294967295, 32))
        elif op == 15:
            self.set(rt, sign(im << 16, 32))
        elif op == 13:
            self.set(rt, self.r[rs] | im)
        elif op == 12:
            self.set(rt, self.r[rs] & im)
        elif op == 35:
            self.set(rt, sign(self.rd(self.r[rs] + si, 4), 32))
        elif op == 55:
            self.set(rt, self.rd(self.r[rs] + si, 8))
        elif op == 30:
            self.set(rt, self.rd(self.r[rs] + si, 16))
        elif op == 31:
            self.wr(self.r[rs] + si, self.r[rt], 16)
        elif op in (43, 63):
            self.wr(self.r[rs] + si, self.r[rt], 4 if op == 43 else 8)
        else:
            raise ValueError(f'Unsupported bounded op {pc:X}/{w:X}')

    def run(self, start, end, follow=False):
        pc = start
        initial_ra = self.r[31]
        while start <= pc < end:
            if self.steps > 400:
                raise ValueError('Bounded transport step limit')
            w = struct.unpack('<I', self.e.at_vram(pc, 4))[0]
            op = w >> 26
            rs = w >> 21 & 31
            rt = w >> 16 & 31
            si = sign(w & 65535, 16)
            if op in (4, 5, 20, 21):
                taken = self.r[rs] == self.r[rt] if op in (4, 20) else self.r[rs] != self.r[rt]
                if taken or op in (4, 5):
                    self.one(pc + 4)
                pc = pc + 4 + si * 4 if taken else pc + 8
            elif op == 3:
                target = pc + 4 & 4026531840 | (w & 67108863) << 2
                self.set(31, pc + 8)
                self.one(pc + 4)
                self.calls.append(dict(site=hex(pc), target=hex(target), A0=hex(self.r[4] & 4294967295), A1=hex(self.r[5] & 4294967295)))
                if follow:
                    sizes = {2750936: 40, 2750816: 112, 1527920: 36, 1525512: 152}
                    if target not in sizes:
                        raise ValueError('Unreviewed callee')
                    self.run(target, target + sizes[target], True)
                pc += 8
            elif op == 0 and w & 63 == 8:
                target = self.r[rs]
                self.one(pc + 4)
                if target != initial_ra:
                    raise ValueError('Unexpected original return target')
                return
            else:
                self.one(pc)
                pc += 4
        if pc != end:
            raise ValueError('Bounded slice escaped expected end')

def transport_cases(e):
    result = []
    for frame in (3588912, 3589312):
        for packet in (33619968, 37749296, 1879122752):
            for chcr in (0, 4, 15, 128):
                t = Transport(e)
                t.r[21] = t.r[19] = 3604480
                t.m.update({3588884: packet, 3588904: frame})
                t.run(1528668, 1528688)
                _need(t.m[frame + 36] == packet, 'Incomplete original input proof')
                t.r[18] = t.r[20] = 3604480
                t.m.update({3589760: frame, 3587388: 268472320})
                t.run(1585668, 1585688)
                _need(t.calls[-1]['target'] == '0x195760' and t.r[4] == 268472320 and (t.r[5] & 4294967295 == packet), 'Incomplete original input proof')
                t.r[17] = t.r[5]
                t.r[18] = t.r[4]
                t.run(1660876, 1660888)
                _need(t.calls[-1]['target'] == '0x29fd20' and t.r[4] == 268472320 and (t.r[5] & 4294967295 == packet), 'Incomplete original input proof')
                t.r[29] = 1610616832
                t.r[31] = 305419896
                t.m.update({268472320: chcr, 268472368: 0, 268472352: 99})
                t.run(2751776, 2751880, True)
                expected = packet & 268435455 | 2147483648 if packet >> 28 == 7 else packet
                _need(t.m[268472368] == expected and t.m[268472352] == 0 and (t.m[268472320] == chcr & 4294967283 | 261), 'Incomplete original input proof')
                result.append(dict(frame=hex(frame), symbolic_packet_pointer=hex(packet), old_CHCR=hex(chcr), actual_TADR=hex(t.m[268472368]), QWC=0, new_CHCR=hex(t.m[268472320]), calls=t.calls, integer_steps=t.steps))
    return dict(status='PASS_ORIGINAL_INTEGER_PACKET_TRANSPORT', cases=result, count=len(result), scope='Actual original opcode execution in listed slices and whole29FD20/29F9D8/29F960 with old DMA idle and writable TADR; pointer cases are finite symbolic inputs, not observed runtime buffers.', no_OS_or_floating_or_VU_execution_claim=True)

def dispatcher_upload_launch_operands(e):
    result = []
    for renderer_id in (0, -1):
        t = Transport(e)
        t.r[4] = renderer_id & MASK
        t.r[29] = 1610616832
        t.r[31] = 305419896
        t.run(1527816, 1527920, True)
        state = sign(t.r[2] & 4294967295, 32)
        _need(state == -1, 'Incomplete original input proof')
        t.r[4] = state & MASK
        t.run(1528040, 1528076)
        _need(t.r[2] == 0, 'Incomplete original input proof')
        result.append(dict(renderer_ID=renderer_id, original_state=state, state_callback_record_pointer=0, steps=t.steps))
    t = Transport(e)
    t.r[4] = 0
    t.r[31] = 305419896
    t.run(1528384, 1528420)
    _need(t.r[2] == 3281472, 'Incomplete original input proof')
    _need(struct.unpack('<2I', e.at_vram(t.r[2], 8)) == (1629896, 0), 'Incomplete original input proof')
    t = Transport(e)
    t.r[4] = 3588872
    t.r[5] = 2901504
    t.r[6] = 2903000
    t.r[29] = 1610616832
    t.r[31] = 305419896
    t.m.update({3588880: 0, 3588884: 34603008})
    t.run(1584480, 1584520, True)
    _need(t.m[34603008] == 2901504 << 32 | 1073741918 and t.m[34603016] == 0 and (t.m[3588884] == 34603024), 'Incomplete original input proof')
    refs = dict(whole_original_rounding_and_REFS_helpers_executed=True, requested_bytes=1496, QWC=94, whole_transfer_bytes=1504, generated_DMA_REFS_low64=hex(t.m[34603008]), entire_upper64_zero=hex(t.m[34603016]), original_program_payload_source_credit=0)
    t = Transport(e)
    t.r[4] = 3588872
    t.r[5] = 16
    t.r[31] = 305419896
    t.m[3588884] = 34668544
    t.run(2613856, 2613904)
    _need(t.m[34668544] == 335544322 and t.m[3588884] == 34668548, 'Incomplete original input proof')
    mscal = dict(whole_original_builder_executed=True, VU_byte_input=16, VIF_immediate=2, exact_written_VIF_word=hex(t.m[34668544]))
    t = Transport(e)
    record = 52428800
    part = 54525952
    matrix = 55574528
    geometry = 56623104
    t.r[2] = record
    t.r[16] = matrix
    t.r[20] = part
    t.m[part + 8] = geometry
    t.run(1631048, 1631068)
    _need(t.m[record] == 0 and t.m[record + 4] == 0 and (t.m[record + 8] == matrix) and (t.m[record + 12] == geometry), 'Incomplete original input proof')
    t.r[20] = record
    t.m[3588884] = 34603264
    t.run(1529140, 1529236)
    _need(t.m[34603264] == matrix << 32 | 1342177280 and t.m[34603280] == geometry << 32 | 1342177280, 'Incomplete original input proof')
    return dict(status='PASS_ORIGINAL_ID0_STATE_REFS_MSCAL_AND_REAL_RECORD_CALL_OPERANDS', ID_cases=result, actual_kind0_record=hex(3281472), actual_kind0_setup=hex(1629896), upload_refs=refs, launch=mscal, original_render_record_fields=dict(ID=0, word1=0, matrix_chain=hex(matrix), geometry_from_part8=hex(geometry)), DMA_CALLs=[hex(t.m[34603264]), hex(t.m[34603280])], scope='Only original integer transport with explicitly provided memory; 128-bit save/load instructions track consumed low64 lanes only, unsampled high save lanes and hardware execution are not simulated.')

class Gate(Transport):

    def one(self, pc):
        w = struct.unpack('<I', self.e.at_vram(pc, 4))[0]
        op = w >> 26
        if op in (32, 36):
            rs = w >> 21 & 31
            rt = w >> 16 & 31
            a = self.r[rs] + sign(w & 65535, 16) & 4294967295
            x = self.rd(a, 1)
            self.set(rt, sign(x, 8) if op == 32 else x)
            self.steps += 1
        else:
            super().one(pc)

    def trace_gate(self):
        pc = 1644120
        path = []
        while pc not in (1644164, 1644520, 1645352, 1645356):
            _need(len(path) < 32, 'Bounded actual gate loop')
            path.append(hex(pc))
            w = struct.unpack('<I', self.e.at_vram(pc, 4))[0]
            op = w >> 26
            rs = w >> 21 & 31
            rt = w >> 16 & 31
            si = sign(w & 65535, 16)
            if op in (4, 5, 20, 21, 6):
                if op == 6:
                    taken = sign(self.r[rs], 64) <= 0
                else:
                    taken = self.r[rs] == self.r[rt] if op in (4, 20) else self.r[rs] != self.r[rt]
                if taken or op in (4, 5, 6):
                    self.one(pc + 4)
                pc = pc + 4 + si * 4 if taken else pc + 8
            else:
                self.one(pc)
                pc += 4
        return dict(path=path, stop=hex(pc), enters_lighting=pc == 1644520, nonlighting_color_path=pc == 1644164, explicit_skip=pc in (1645352, 1645356))

def gate_case(e, piece_flags, surface_type, seg_flags, count, global_gate):
    t = Gate(e)
    t.r[23] = 50348032
    t.r[18] = 50352128
    t.m.update({50348034: piece_flags, 50352132: 50356224, 50356228: surface_type, 50352136: seg_flags, 50352128: count & 4294967295, 3428416: global_gate})
    trace = t.trace_gate()
    expected = piece_flags & 3 == 0 and surface_type in (1, 7) and (global_gate != 0 or not seg_flags & 32) and (count > 0)
    _need(trace['enters_lighting'] == expected, 'Actual original gate disagrees with declared condition')
    return dict(piece_flags=piece_flags, surface_type=surface_type, segment_flags=seg_flags, actual_palette_count=count, live_gate=global_gate, trace=trace)


def _int(x):return int(x,0)if isinstance(x,str)else x

def checked_inputs(elf,bundle,manifest):
    """Re-read all consumed full bodies/tables/stock bytes and real gate/transport paths."""
    bundle=Path(bundle).resolve()
    load=lambda rel:json.loads((bundle/rel).read_text())
    runtime=load('docs/evidence/vu_lighting_runtime_binding_review.json')
    peer=load('docs/evidence/vu_lighting_runtime_parent_review.json')
    submission=load('docs/evidence/vu_lighting_frame_submission_review.json')
    _need(runtime['status']=='ADDITIVE_ORIGINAL_SURFACE_BRANCH_CORRECTION_AND_REPLACEMENT_MODE0_TYPE1_WITNESS_PASS_PARENT_REVIEW_REQUIRED','Incomplete corrected runtime evidence')
    _need(peer['status']=='PASS_ADDITIVE_ALARM_TYPE1_RUNTIME_ENTRY_WITH_EXPLICIT_LIVE_PRECONDITIONS','Missing independent actual type1 entry review')
    _need(runtime['old_type0_entry_claim_valid']is False and not submission['old_type0_stock_entry_claim_valid'],'Historical type0 claim cannot authorize source')
    _need(runtime['historical_claim_withdrawal']['negative_Bentley_chain_population']['positive_part8_population_claim_withdrawn'],'Historical type0 part8 was not withdrawn')
    _need(runtime['branch_entry_contract_closed_for_replacement_captured_path']is True and runtime['live_runtime_execution_observed']is False and runtime['universal_class_or_material_domain_claim']is False,'False launch scope/hardware claim')
    records=submission['complete_original_EE_input_support']+runtime['complete_new_original_input_support']+peer['additional_input_only_support']
    unique={};full=[]
    for row in records:
        address=_int(row['address']);size=row.get('complete_original_bytes',row.get('bytes',row.get('complete_bytes')))
        raw=elf.at_vram(address,size);expected=row.get('original_bytes_hex',row.get('original_hex'))
        want=row.get('original_sha256',row.get('sha256'))
        _need(raw.hex()==expected and sha(raw)==want,'Complete original incoming/control body changed')
        key=(address,size);_need(key not in unique or unique[key]==want,'Contradictory original boundary/input owner')
        unique[key]=want;full.append({'address':address,'size':size,'sha256':want})
    for row in submission['tables']+runtime['actual_bounded_factory_and_PMF_metadata']:
        raw=elf.at_vram(_int(row['address']),row['bytes']);expected=row.get('raw_hex',row.get('original_hex'))
        _need(raw.hex()==expected and sha(raw)==row['sha256'],'Whole bounded original table changed')
    witness=runtime['replacement_actual_stock_witness'];body=bytes.fromhex(witness['whole_body_original_hex']);factory=witness['actual_factory_record']
    decoded=bundle/'build/asset_catalog/level_tag_05.decoded.bin';raw=decoded.read_bytes()
    _need(sha(raw)=='4b8beaf0de21ccf5a3694b9feced105a6dd0a970bcd09be5f1adeccb05f3f017','Extracted original world identity changed')
    a,z=factory['body_range'];_need([a,z]==[533283,540038]and raw[a:z]==body and len(body)==6755 and sha(body)=='da2bfc8bb088faf1c3964be984fb707bf6ee67f6d899d0054d2fddafcfe8d675','Entire genuine6755 baseALO body changed')
    _need(factory['mode']==0 and factory['cid']==47 and factory['identity']==148210 and factory['parent']==-1 and not factory['masks']and not factory['choices'],'Unsupported stock factory/runtime choice')
    module_a,module_z=witness['module_range'];_need(sha(raw[module_a:module_z])==witness['module_sha256'],'Whole original module boundaries changed')
    node=witness['selected_node'];g=node['geometry'];segment=g['segments'][0]
    _need(node['kind']==node['disabled']==node['sub_count']==node['additional_count']==node['frame']==0 and g['flags']==8 and g['material']==g['packed_selector']==-1 and not g['shaders']['groups'],'Actual native geometry overrides/counts changed')
    _need(segment['palettes']==[[16,1,3],[14,1,3]]and segment['vertex_count']==18 and segment['packing']==0,'Serialized vertices are not lighting palette counts')
    surface=witness['surface1'];sa,sz=surface['stream_range'];header=bytes.fromhex(surface['header_hex'])
    _need(raw[sa:sa+24]==header and header[4]==1 and surface['shader']==-1 and body[g['stream_range'][0]]==8,'Actual copied surface type1 or piece flags changed')
    _need(sha(body[g['stream_range'][0]:g['stream_range'][1]])==g['original_sha256'],'Whole original geometry payload changed')
    _need(max(witness['raw_indices'])<18 and len(witness['raw_indices'])==30 and witness['actual_original_light_batch_counter']==2,'False original positive palette/lighting counter')
    word=lambda a:struct.unpack('<I',elf.at_vram(a,4))[0]
    branch=lambda a:a+4+sign(word(a)&65535,16)*4
    _need(branch(0x191674)==branch(0x19167c)==0x1917bc and branch(0x1917b4)==0x191b2c,'Reversed actual surface gate')
    _need(word(0x1904b0)==0xafa011c4 and word(0x1918f8)==0xafa811c4 and word(0x192598)==0x18a00013 and branch(0x192598)==0x1925e8,'Actual original lighting counter/copy gate changed')
    gates=[]
    for flags in range(256):
        for typ in (0,1,7,255):
            for sf in (1,3,0x20):
                for count in (-1,0,1,38):
                    for live in (0,1):gates.append(gate_case(elf,flags,typ,sf,count,live)['trace']['enters_lighting'])
    _need(len(gates)==24576 and sum(gates)==1280 and sha(bytes(gates))=='3ce69d29b6d94287fe427dcdfda319ee44c9abace0089da5822de82771c70816','Actual complete original branch domain changed')
    positive=[gate_case(elf,8,1,3,n,0)for n in(16,14)];negative=[gate_case(elf,12,0,1,n,0)for n in(16,15)]
    _need(all(c['trace']['enters_lighting']for c in positive)and not any(c['trace']['enters_lighting']for c in negative),'Type0 historical negative or actual type1 positive changed')
    transport=transport_cases(elf);upload=dispatcher_upload_launch_operands(elf)
    _need(same(transport,submission['original_integer_transport'])and same(upload,submission['original_upload_launch_operand_replay']),'Current actual entire upload/MSCAL/DMA operands changed')
    _need(word(0x17536c)==0xaca20024 and word(0x183214)==0x8c450024,'Current frame+24 start/consumer changed')
    _need(elf.at_vram(0x21dd28,8)==elf.at_vram(0x1746a8,8)==struct.pack('<2I',0x03e00008,0),'Mandatory interlude callback is not the true no-op')
    _need(word(0x1cb2ac)==0x10800003 and branch(0x1cb2ac)==0x1cb2bc,'Restricted real null-client branch changed')
    _need(struct.unpack('<2I',elf.at_vram(0x3659d8,8))==(0,0x23c0b8)and struct.unpack('<2I',elf.at_vram(0x365b20,8))==(0,0x28c310),'Actual CID2F body/frame PMF domain changed')
    return {'status':'CURRENT_COMPLETE_ORIGINAL_TYPE1_INPUT_BRANCH_UPLOAD_AND_SUBMISSION_REVERIFIED','unique_complete_original_body_count':len(unique),'captured_body_records':len(records),'original_body_fingerprints':sorted(full,key=lambda x:(x['address'],x['size'])),'full_actual_body_bytes':6755,'body_sha256':sha(body),'actual_gate_states':24576,'actual_palette_counts':[16,14],'shared_serialized_vertices':18,'actual_positive_light_batches':2,'actual_MSCAL_immediate':2,'actual_VU_byte_entry':16,'original_integer_transport_cases':24,'old_type0_entry_and_positive_part8_claims_withdrawn':True,'source_progress_from_input_bodies':0,'live_runtime_observed':False,'universal_class_claim':False,'required_native_live_preconditions':runtime['explicit_runtime_preconditions']}
