// image offset 0x20B1B0 address 7ff7a339b1b0

longlong FUN_7ff7a339b1b0(longlong param_1,longlong param_2,longlong param_3)

{
  longlong *plVar1;
  longlong lVar2;
  longlong lVar3;
  
  if (param_2 != 0) {
    lVar3 = (param_3 - param_1) + -8;
    do {
      FUN_7ff7a3c04d20((longlong)*(int *)(*(longlong *)(param_1 + 8) + 4) + 8 + param_1,
                       param_3 + 8 + (longlong)*(int *)(*(longlong *)(param_3 + 8) + 4));
      plVar1 = (longlong *)(param_1 + 0x80);
      *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_3 + 0x10);
      lVar2 = 10;
      *(undefined2 *)(param_1 + 0x14) = *(undefined2 *)(param_3 + 0x14);
      *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_3 + 0x18);
      *(undefined1 *)(param_1 + 0x1c) = *(undefined1 *)(param_3 + 0x1c);
      *(undefined1 *)(param_1 + 0x1d) = *(undefined1 *)(param_3 + 0x1d);
      *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_3 + 0x20);
      *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_3 + 0x24);
      *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_3 + 0x28);
      *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(param_3 + 0x2c);
      *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_3 + 0x30);
      *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_3 + 0x34);
      *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_3 + 0x38);
      *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_3 + 0x3c);
      *(undefined1 *)(param_1 + 0x40) = *(undefined1 *)(param_3 + 0x40);
      *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_3 + 0x44);
      *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_3 + 0x48);
      *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(param_3 + 0x4c);
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_3 + 0x50);
      *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(param_3 + 0x54);
      *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_3 + 0x58);
      *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_3 + 0x5c);
      *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_3 + 0x60);
      do {
        FUN_7ff7a3c04d20((longlong)*(int *)(plVar1[-2] + 4) + -0x10 + (longlong)plVar1,
                         (longlong)*(int *)(*(longlong *)(lVar3 + -8 + (longlong)plVar1) + 4) + -8 +
                         lVar3 + (longlong)plVar1);
        FUN_7ff7a3c04d20((longlong)*(int *)(*plVar1 + 4) + (longlong)plVar1,
                         (longlong)*(int *)(*(longlong *)(lVar3 + 8 + (longlong)plVar1) + 4) + 8 +
                         lVar3 + (longlong)plVar1);
        *(undefined4 *)(plVar1 + 1) = *(undefined4 *)(lVar3 + 0x10 + (longlong)plVar1);
        *(undefined4 *)((longlong)plVar1 + 0xc) = *(undefined4 *)(lVar3 + 0x14 + (longlong)plVar1);
        plVar1 = plVar1 + 7;
        lVar2 = lVar2 + -1;
      } while (lVar2 != 0);
      param_1 = param_1 + 0x2a8;
      lVar3 = lVar3 + -0x2a8;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  return param_1;
}

