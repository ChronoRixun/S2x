// image offset 0x126AE0 address 7ff7a32b6ae0

undefined8 FUN_7ff7a32b6ae0(longlong param_1)

{
  undefined4 *puVar1;
  byte bVar2;
  undefined8 uVar3;
  uint *puVar4;
  uint *puVar5;
  
  bVar2 = 0;
  puVar4 = *(uint **)(param_1 + 0x48);
  puVar5 = *(uint **)(param_1 + 0x50);
  if ((((int)((longlong)puVar4 - (longlong)puVar5 >> 4) != 1) || (puVar4 <= puVar5)) ||
     (1 < (*puVar5 & 0xf) - 3)) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    puVar4 = *(uint **)(param_1 + 0x48);
    puVar5 = *(uint **)(param_1 + 0x50);
  }
  if ((((int)((longlong)puVar4 - (longlong)puVar5 >> 4) == 1) && (puVar5 < puVar4)) &&
     ((*puVar5 & 0xf) - 3 < 2)) {
    uVar3 = FUN_7ff7a3469740(param_1,puVar5,0);
    uVar3 = FUN_7ff7a3402560(uVar3);
    bVar2 = FUN_7ff7a34028c0(uVar3);
  }
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)bVar2;
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

