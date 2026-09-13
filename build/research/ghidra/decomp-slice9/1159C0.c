// image offset 0x1159C0 address 7ff7a32a59c0

undefined8 FUN_7ff7a32a59c0(longlong param_1)

{
  undefined4 *puVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  longlong lVar6;
  float fVar7;

  bVar2 = 1;
  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 2)
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar3 = FUN_7ff7a3468d90(param_1);
    if (iVar3 != 0) {
      iVar3 = thunk_FUN_7ff7a3294bb0(param_1,2);
      if (iVar3 != 0) goto LAB_7ff7a32a5a22;
    }
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32a5a22:
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar7 = (float)FUN_7ff7a3469aa0(param_1);
    iVar3 = (int)fVar7;
  }
  else {
    iVar3 = 0;
  }
  uVar4 = FUN_7ff7a36321d0(iVar3);
  uVar5 = FUN_7ff7a325cb30(param_1,2);
  lVar6 = FUN_7ff7a325e780(uVar5);
  if (lVar6 != 0) {
    bVar2 = FUN_7ff7a38cf9f0(uVar4,lVar6,uVar5);
  }
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)bVar2;
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}
