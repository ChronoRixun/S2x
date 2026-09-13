// image offset 0x20C1A0 address 7ff7a339c1a0

void FUN_7ff7a339c1a0(longlong param_1,longlong param_2)

{
  longlong *plVar1;
  uint uVar2;
  
  plVar1 = (longlong *)(param_1 + 0x70);
  *(undefined4 *)(param_2 + 0x230) = *(undefined4 *)(param_1 + 0x10);
  uVar2 = 0;
  *(undefined1 *)(param_2 + 0x234) = *(undefined1 *)(param_1 + 0x1c);
  param_2 = param_2 - param_1;
  do {
    FUN_7ff7a3c04d20((longlong)*(int *)(*(longlong *)(param_2 + -0x68 + (longlong)plVar1) + 4) +
                     -0x68 + param_2 + (longlong)plVar1,
                     (longlong)*(int *)(*plVar1 + 4) + (longlong)plVar1);
    FUN_7ff7a3c04d20((longlong)*(int *)(*(longlong *)(param_2 + -0x58 + (longlong)plVar1) + 4) +
                     -0x58 + param_2 + (longlong)plVar1,
                     (longlong)*(int *)(plVar1[2] + 4) + 0x10 + (longlong)plVar1);
    uVar2 = uVar2 + 1;
    *(int *)(param_2 + -0x50 + (longlong)plVar1) = (int)plVar1[3];
    *(undefined4 *)(param_2 + -0x4c + (longlong)plVar1) = *(undefined4 *)((longlong)plVar1 + 0x1c);
    plVar1 = plVar1 + 7;
  } while (uVar2 < 10);
  return;
}

