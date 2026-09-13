// image offset 0x277300 address 7ff7a3407300

undefined4 FUN_7ff7a3407300(longlong param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  longlong lVar6;
  int iVar7;
  
  iVar7 = 0;
  uVar4 = 0;
  lVar6 = 0;
  iVar5 = -1;
  while ((((iVar1 = FUN_7ff7a37e2360(*(undefined4 *)(param_1 + lVar6 * 4)), iVar1 == 1 &&
           ((((iVar2 = FUN_7ff7a37e2210(*(undefined4 *)(param_1 + lVar6 * 4)), iVar1 = iVar2,
              iVar7 == 0 || (iVar1 = iVar7, iVar7 == iVar2)) && (iVar7 = iVar1, iVar2 != 0)) &&
            ((iVar2 = FUN_7ff7a37e23a0(*(undefined4 *)(param_1 + lVar6 * 4)), iVar1 = iVar2,
             iVar5 == -1 || (iVar1 = iVar5, iVar5 == iVar2)))))) && (iVar5 = iVar1, iVar2 != -1)) &&
         ((uVar3 = FUN_7ff7a37e2370(*(undefined4 *)(param_1 + lVar6 * 4)), 1 < uVar3 + 1 &&
          ((uVar4 >> (uVar3 & 0x1f) & 1) == 0))))) {
    uVar4 = uVar4 | 1 << (uVar3 & 0x1f);
    lVar6 = lVar6 + 1;
    if (2 < lVar6) {
      return 1;
    }
  }
  return 0;
}

