# Slice 8 relay and predicate evidence (2026-09-13)

Read-only inspection; no game process launched.

Table: 1234 rows; 416 nonempty predicates; 133 distinct expressions.
Operators: `:` (selector test), `&&`, `||`; grouping: `(`, `)`. No other operators or whitespace occur.
Selectors used: [1, 2, 3, 5, 6, 7, 8, 9, 128, 129, 130].
Selectors 128..130 have only power-of-two masks. `(130:4)&&(130:128)` requires two bits of the same word; equality cannot satisfy it. Low selectors use enum/scalar equality.
The table has six columns (ID, name, kind, event ID, predicate, season), no increment/count selector.

## Captured task-11 requests

Directory (read only): `D:/Program Files/Steam/steamapps/common/Call of Duty WWII/s2x/dump/dw`.

- `hq_reward_11_1220_52.bin` (104 bytes): enter_hub: parameters=1, max_selector=1
- `hq_reward_11_35824_113.bin` (104 bytes): enter_hub: parameters=1, max_selector=1
- `hq_reward_11_35824_150.bin` (104 bytes): enter_hub: parameters=1, max_selector=1
- `hq_reward_11_35824_210.bin` (104 bytes): enter_hub: parameters=1, max_selector=1
- `hq_reward_11_35824_247.bin` (104 bytes): enter_hub: parameters=1, max_selector=1
- `hq_reward_11_35824_52.bin` (104 bytes): enter_hub: parameters=1, max_selector=1
- `hq_reward_11_56280_52.bin` (104 bytes): enter_hub: parameters=1, max_selector=1
- `hq_reward_11_65416_52.bin` (104 bytes): enter_hub: parameters=1, max_selector=1

All available requests above are hub events; no dedicated kill request was captured. The real kill maximum is unmeasured. Use the requested fallback of 256 parameters/selectors 0..255 and log first task-11 event per name on the server for the next operator run.

## Reliable command slot evidence

Image: `build/research/ghidra/s2_mp64_ship_unpacked.exe` (RVA addresses).

```text
006E0BB7: mov edx, 0x20000
006E0BBC: lea rcx, [rsp + 0x30]
006E0BC1: call 0x287110
006E0BEC: mov r9, qword ptr [rsp + 0x80]
006E0BF4: mov r8d, 0x20000
006E0BFA: mov rdx, rsi
006E0BFD: call qword ptr [rip + 0x10b8c215]
006E0C08: mov r8, rsi
006E0C0B: mov edx, ebp
006E0C0D: mov rcx, rbx
006E0C10: call 0x6ddfe0
006DE17C: mov eax, ecx
006DE17E: mov r8d, 0x400
006DE184: and eax, 0x7f
006DE187: mov rcx, rdi
006DE18A: imul rax, rax, 0x408
006DE191: add rbx, rax
006DE194: lea rdx, [rbx + 0xd64]
006DE19B: call 0x6745a0
006745A0: push rbx
006745A2: xor r11d, r11d
006745A5: mov qword ptr [rsp + 0x18], rdi
006745AA: movsxd rbx, r8d
006745AD: mov rdi, rcx
006745B0: mov r9, rdx
006745B3: test r8d, r8d
006745B6: jle 0x6745fb
006745B8: mov r10, rdx
006745BB: mov qword ptr [rsp + 0x10], rsi
006745C0: neg r10
006745C3: lea esi, [r11 + 0x2e]
006745C7: nop word ptr [rax + rax]
006745D0: lea rax, [r10 + r9]
006745D4: movzx ecx, byte ptr [rax + rdi]
006745D8: test cl, cl
006745DA: je 0x6745f6
006745DC: cmp cl, 0x25
006745DF: mov eax, ecx
006745E1: cmove eax, esi
006745E4: inc r11d
006745E7: mov byte ptr [r9], al
006745EA: inc r9
006745ED: lea rax, [r10 + r9]
006745F1: cmp rax, rbx
006745F4: jl 0x6745d0
006745F6: mov rsi, qword ptr [rsp + 0x10]
006745FB: mov rdi, qword ptr [rsp + 0x18]
00674600: cmp r11d, r8d
00674603: jge 0x67460e
00674605: movsxd rax, r11d
00674608: mov byte ptr [rax + rdx], 0
0067460C: pop rbx
0067460D: ret
0067460E: mov byte ptr [rbx + rdx - 1], 0
00674613: pop rbx
00674614: ret
00674615: nop
```

`SV_SendServerCommand` (0x6E0BA0) formats with capacity 0x20000, but calls 0x6DDFE0, whose ring has 128 entries of stride 0x408 (8 bytes metadata + 0x400 text). At 0x6DE17E it passes 0x400 to copy helper 0x6745A0. Thus strings must fit 1023 bytes plus NUL. Slice 8 uses <=800 hex payload characters plus six bounded header tokens, always below this limit.
