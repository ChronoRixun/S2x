// image offset 0x274C30 address 7ff7a3404c30

int FUN_7ff7a3404c30(undefined8 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  uint uVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  longlong *plVar8;
  
  lVar3 = FUN_7ff7a3919870();
  iVar6 = 0;
  if (lVar3 != 0) {
    uVar4 = 0;
    plVar8 = &DAT_7ff7ab0f41b8;
    while (*plVar8 != lVar3) {
      uVar4 = uVar4 + 1;
      plVar8 = plVar8 + 0xc4;
      if (1 < uVar4) {
        return 0;
      }
    }
    iVar6 = 0;
    if ((longlong)(int)uVar4 * 0x620 != -0x7ff7ab0f3ba0) {
      uVar7 = 0;
      piVar5 = (int *)(&DAT_7ff7ab0f3fac + (longlong)(int)uVar4 * 0x620);
      iVar6 = 0;
      do {
        iVar2 = iVar6 + 1;
        if (piVar5[-0x82] != param_2) {
          iVar2 = iVar6;
        }
        iVar1 = iVar2 + 1;
        if (*piVar5 != param_2) {
          iVar1 = iVar2;
        }
        iVar6 = iVar1 + 1;
        if (piVar5[0x82] != param_2) {
          iVar6 = iVar1;
        }
        uVar7 = uVar7 + 3;
        piVar5 = piVar5 + 0x186;
      } while (uVar7 < 3);
    }
  }
  return iVar6;
}

