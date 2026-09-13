// image offset 0x20CBA0 address 7ff7a339cba0

void FUN_7ff7a339cba0(longlong param_1)

{
  longlong lVar1;
  longlong *plVar2;
  longlong lVar3;
  undefined1 local_48 [16];
  undefined1 local_38 [16];
  undefined1 local_28 [8];
  undefined1 local_20 [24];
  
  *(undefined4 *)(param_1 + 0x2d8) = 0;
  *(undefined1 *)(param_1 + 0x2dc) = 0;
  lVar1 = FUN_7ff7a3bd97f0(local_48,1);
  lVar3 = 0xd;
  plVar2 = (longlong *)(param_1 + 8);
  do {
    FUN_7ff7a3c04d20((longlong)*(int *)(*plVar2 + 4) + (longlong)plVar2,
                     (longlong)*(int *)(*(longlong *)(lVar1 + 8) + 4) + 8 + lVar1);
    FUN_7ff7a3c04d20((longlong)*(int *)(plVar2[2] + 4) + 0x10 + (longlong)plVar2,
                     (longlong)*(int *)(*(longlong *)(lVar1 + 0x18) + 4) + 0x18 + lVar1);
    *(undefined1 *)(plVar2 + 3) = *(undefined1 *)(lVar1 + 0x20);
    *(undefined4 *)((longlong)plVar2 + 0x1c) = *(undefined4 *)(lVar1 + 0x24);
    plVar2 = plVar2 + 7;
    lVar3 = lVar3 + -1;
  } while (lVar3 != 0);
  FUN_7ff7a3bcb570(local_28);
  FUN_7ff7a3bbc060(local_38);
  FUN_7ff7a3c04d10(local_20);
  return;
}

