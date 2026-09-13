// image offset 0x275110 address 7ff7a3405110

undefined1 FUN_7ff7a3405110(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  int iVar5;
  undefined8 uVar6;
  char *_Str;
  undefined1 uVar7;
  undefined8 local_res18 [2];
  
  uVar7 = 0;
  FUN_7ff7a38f34d0("mp/itemsCollections.csv",local_res18);
  uVar6 = FUN_7ff7a38fa3d0(&DAT_7ff7a3cc32b4,param_2);
  iVar2 = FUN_7ff7a38f3700(local_res18[0],0,uVar6);
  if (-1 < iVar2) {
    uVar6 = FUN_7ff7a38f3510(local_res18[0],iVar2,1);
    iVar3 = FUN_7ff7a37e23d0(uVar6);
    if ((iVar3 != 0) && (cVar1 = FUN_7ff7a340a310(param_1,iVar3), cVar1 != '\0')) {
      return 1;
    }
    _Str = (char *)FUN_7ff7a38f3510(local_res18[0],iVar2,2);
    if (((_Str != (char *)0x0) && (*_Str != '\0')) &&
       (lVar4 = strtol(_Str,(char **)0x0,10), lVar4 - 1U < 0xf)) {
      iVar3 = 0;
      uVar7 = 1;
      if (0 < lVar4) {
        do {
          uVar6 = FUN_7ff7a38f3510(local_res18[0],iVar2,iVar3 + 3);
          iVar5 = FUN_7ff7a37e23d0(uVar6);
          if ((iVar5 == 0) || (cVar1 = FUN_7ff7a340a310(param_1,iVar5), cVar1 == '\0')) {
            return 0;
          }
          iVar3 = iVar3 + 1;
        } while (iVar3 < lVar4);
      }
    }
  }
  return uVar7;
}

