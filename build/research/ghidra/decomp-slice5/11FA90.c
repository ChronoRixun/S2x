// image offset 0x11FA90 address 7ff7a32afa90

undefined8 FUN_7ff7a32afa90(longlong param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  int *piVar6;
  uint uVar7;
  float fVar8;
  
  if ((((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) != 1
       ) || (*(ulonglong *)(param_1 + 0x48) <= *(ulonglong *)(param_1 + 0x50))) ||
     (iVar2 = FUN_7ff7a3468d90(param_1), iVar2 == 0)) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  uVar7 = 0;
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar8 = (float)FUN_7ff7a3469aa0(param_1);
    iVar2 = (int)fVar8;
  }
  else {
    iVar2 = 0;
  }
  iVar3 = FUN_7ff7a3404c30(iVar2,1);
  if (iVar3 < 1) {
    FUN_7ff7a324d6e0(1,0,0,param_1);
  }
  else {
    uVar4 = FUN_7ff7a3919870(iVar2);
    lVar5 = FUN_7ff7a3404e80(uVar4);
    FUN_7ff7a324d6e0(1,iVar3,0,param_1);
    piVar6 = (int *)(lVar5 + 0x204);
    do {
      if (*piVar6 == 1) {
        puVar1 = *(undefined4 **)(param_1 + 0x48);
        *puVar1 = 3;
        puVar1[2] = (float)(int)uVar7;
        *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
        FUN_7ff7a3469640(param_1,puVar1 + -4,uVar7 + 1);
        *(longlong *)(param_1 + 0x48) = *(longlong *)(param_1 + 0x48) + -0x10;
      }
      uVar7 = uVar7 + 1;
      piVar6 = piVar6 + 0x82;
    } while (uVar7 < 3);
  }
  return 1;
}

