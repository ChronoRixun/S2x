// image offset 0x312F30 address 7ff7a34a2f30

undefined8 FUN_7ff7a34a2f30(longlong param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  longlong lVar5;
  uint *puVar6;
  float fVar7;
  undefined8 local_res8;
  
  if ((((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 2
       ) && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) &&
     (iVar2 = FUN_7ff7a3468d90(param_1), iVar2 != 0)) {
    lVar5 = *(longlong *)(param_1 + 0x50);
    puVar6 = *(uint **)(param_1 + 0x48);
    if (((uint *)(lVar5 + 0x10U) < puVar6) && ((*(uint *)(lVar5 + 0x10U) & 0xf) - 3 < 2))
    goto LAB_7ff7a34a2fa2;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  lVar5 = *(longlong *)(param_1 + 0x50);
  puVar6 = *(uint **)(param_1 + 0x48);
LAB_7ff7a34a2fa2:
  uVar4 = 0;
  uVar3 = 0;
  if ((uint *)(lVar5 + 0x10) < puVar6) {
    uVar4 = FUN_7ff7a3469740(param_1,(uint *)(lVar5 + 0x10),0);
  }
  FUN_7ff7a38f34d0("mp/unlocktable.csv",&local_res8);
  iVar2 = FUN_7ff7a38f3700(local_res8,0,uVar4);
  if (iVar2 != -1) {
    if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
      fVar7 = (float)FUN_7ff7a3469aa0(param_1);
    }
    else {
      fVar7 = 0.0;
    }
    uVar3 = FUN_7ff7a36321d0((int)fVar7);
    iVar2 = thunk_EXT_FUN_7ff7a3180513(uVar3,local_res8,iVar2,0);
    uVar3 = 0;
    if (iVar2 == 0) {
      uVar3 = 1;
    }
  }
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = uVar3;
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

