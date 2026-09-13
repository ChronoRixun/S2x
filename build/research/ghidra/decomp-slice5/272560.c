// image offset 0x272560 address 7ff7a3402560

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong FUN_7ff7a3402560(undefined8 param_1)

{
  longlong lVar1;
  int iVar2;
  undefined8 uVar3;
  int iVar4;
  int *piVar5;
  longlong *plVar6;
  int iVar7;
  
  iVar7 = 0;
  if (0 < (int)_DAT_7ff7ab0eec08) {
    piVar5 = &DAT_7ff7ab0eddf0;
    uVar3 = _DAT_7ff7ab0eec08;
    do {
      iVar4 = 0;
      if (0 < *piVar5) {
        plVar6 = (longlong *)(piVar5 + -0x40);
        do {
          lVar1 = *plVar6;
          iVar2 = FUN_7ff7a3b94f90(lVar1 + 0x90,param_1);
          if (iVar2 == 0) {
            return lVar1;
          }
          iVar4 = iVar4 + 1;
          plVar6 = plVar6 + 1;
          uVar3 = _DAT_7ff7ab0eec08;
        } while (iVar4 < *piVar5);
      }
      iVar7 = iVar7 + 1;
      piVar5 = piVar5 + 100;
    } while (iVar7 < (int)uVar3);
  }
  return 0;
}

