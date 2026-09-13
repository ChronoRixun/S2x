// image offset 0x370070 address 7ff7a3500070

undefined8 FUN_7ff7a3500070(longlong param_1)

{
  undefined4 *puVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  int iVar7;
  float fVar8;
  undefined1 local_58 [4];
  undefined4 local_54;
  undefined4 local_50;
  undefined8 local_48;
  undefined8 uStack_40;
  undefined1 local_38 [48];
  
  local_58[0] = 0;
  iVar7 = 0;
  local_50 = 0xffffffff;
  local_54 = 0;
  local_48 = 0;
  uStack_40 = 0;
  bVar3 = 1;
  cVar2 = FUN_7ff7a3401760();
  if ((cVar2 != '\0') && (cVar2 = FUN_7ff7a36309b0(), cVar2 == '\0')) {
    uVar5 = *(ulonglong *)(param_1 + 0x48);
    uVar6 = *(ulonglong *)(param_1 + 0x50);
    if ((int)((longlong)(uVar5 - uVar6) >> 4) != 2) {
      FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
      uVar6 = *(ulonglong *)(param_1 + 0x50);
      uVar5 = *(ulonglong *)(param_1 + 0x48);
    }
    if ((uVar5 <= uVar6) || (iVar4 = FUN_7ff7a3468d90(param_1), iVar4 == 0)) {
      FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    }
    if ((*(ulonglong *)(param_1 + 0x48) <= *(longlong *)(param_1 + 0x50) + 0x10U) ||
       (iVar4 = FUN_7ff7a3468d90(param_1), iVar4 == 0)) {
      FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    }
    uVar5 = *(ulonglong *)(param_1 + 0x50);
    uVar6 = *(ulonglong *)(param_1 + 0x48);
    if (uVar5 < uVar6) {
      fVar8 = (float)FUN_7ff7a3469aa0(param_1,uVar5);
      uVar5 = *(ulonglong *)(param_1 + 0x50);
      uVar6 = *(ulonglong *)(param_1 + 0x48);
    }
    else {
      fVar8 = 0.0;
    }
    iVar4 = (int)fVar8;
    if (uVar5 + 0x10 < uVar6) {
      fVar8 = (float)FUN_7ff7a3469aa0(param_1);
      iVar7 = (int)fVar8;
    }
    cVar2 = FUN_7ff7a3401c90(iVar4);
    if ((cVar2 != '\0') && (cVar2 = FUN_7ff7a34017e0(iVar4,local_58,local_38,0), cVar2 != '\0')) {
      bVar3 = FUN_7ff7a34019f0(iVar4,iVar7,local_58,local_38);
    }
  }
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)bVar3;
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

