// image offset 0x337400 address 7ff7a34c7400

undefined8 FUN_7ff7a34c7400(longlong param_1)

{
  int iVar1;
  ulonglong uVar2;
  uint *puVar3;
  uint *puVar4;
  ulonglong uVar5;
  float fVar6;
  
  if ((((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 2
       ) && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) &&
     (iVar1 = FUN_7ff7a3468d90(param_1), iVar1 != 0)) {
    puVar4 = *(uint **)(param_1 + 0x50);
    puVar3 = *(uint **)(param_1 + 0x48);
    if ((puVar4 + 4 < puVar3) && ((puVar4[4] & 0xf) - 3 < 2)) goto LAB_7ff7a34c7466;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  puVar3 = *(uint **)(param_1 + 0x48);
  puVar4 = *(uint **)(param_1 + 0x50);
LAB_7ff7a34c7466:
  if ((((int)((longlong)puVar3 - (longlong)puVar4 >> 4) == 2) && (puVar4 < puVar3)) &&
     (iVar1 = FUN_7ff7a3468d90(param_1), iVar1 != 0)) {
    puVar4 = *(uint **)(param_1 + 0x50);
    puVar3 = *(uint **)(param_1 + 0x48);
    if ((puVar4 + 4 < puVar3) && ((puVar4[4] & 0xf) - 3 < 2)) {
      uVar2 = 0;
      uVar5 = uVar2;
      if (puVar4 < puVar3) {
        fVar6 = (float)FUN_7ff7a3469aa0(param_1,puVar4);
        puVar4 = *(uint **)(param_1 + 0x50);
        puVar3 = *(uint **)(param_1 + 0x48);
        uVar5 = (ulonglong)(uint)(int)fVar6;
      }
      if (puVar4 + 4 < puVar3) {
        uVar2 = FUN_7ff7a3469740(param_1,puVar4 + 4,0);
      }
      FUN_7ff7a38ddf30(uVar5,uVar2);
    }
  }
  return 0;
}

