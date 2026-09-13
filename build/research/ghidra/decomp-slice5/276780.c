// image offset 0x276780 address 7ff7a3406780

uint FUN_7ff7a3406780(undefined4 param_1,undefined4 param_2,undefined8 param_3)

{
  undefined8 uVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  char *_Str;
  undefined8 local_res20;
  
  FUN_7ff7a38f34d0("mp/itemsCollections.csv",&local_res20);
  uVar1 = FUN_7ff7a38fa3d0(&DAT_7ff7a3cc32b4,param_2);
  uVar3 = FUN_7ff7a38f3700(local_res20,0,uVar1);
  uVar7 = uVar3;
  if ((int)uVar3 < 0) {
LAB_7ff7a3406893:
    return uVar7 & 0xffffff00;
  }
  uVar1 = FUN_7ff7a38f3510(local_res20,uVar3,1);
  iVar4 = FUN_7ff7a37e23d0(uVar1);
  if ((iVar4 == 0) || (cVar2 = FUN_7ff7a340a310(param_1,iVar4), cVar2 == '\0')) {
    _Str = (char *)FUN_7ff7a38f3510(local_res20,uVar3,2);
    uVar7 = (uint)_Str;
    if ((_Str == (char *)0x0) ||
       ((*_Str == '\0' || (uVar5 = strtol(_Str,(char **)0x0,10), uVar7 = uVar5, 0xe < uVar5 - 1))))
    goto LAB_7ff7a3406893;
    iVar4 = 0;
    if (0 < (int)uVar5) {
      do {
        uVar1 = FUN_7ff7a38f3510(local_res20,uVar3,iVar4 + 3);
        iVar6 = FUN_7ff7a37e23d0(uVar1);
        uVar7 = 0;
        if ((iVar6 == 0) || (uVar7 = FUN_7ff7a340a310(param_1,iVar6), (char)uVar7 == '\0'))
        goto LAB_7ff7a3406893;
        iVar4 = iVar4 + 1;
      } while (iVar4 < (int)uVar5);
    }
  }
  uVar1 = FUN_7ff7a38fa3d0("Collection_%u",param_2);
  uVar7 = FUN_7ff7a3408180(param_1,uVar1,param_3,1);
  return uVar7;
}

