// image offset 0x274A70 address 7ff7a3404a70

void FUN_7ff7a3404a70(undefined4 param_1,undefined4 param_2,int *param_3,long *param_4)

{
  undefined8 uVar1;
  char cVar2;
  int iVar3;
  long lVar4;
  int iVar5;
  char *_Str;
  int iVar6;
  undefined8 local_28 [2];
  
  FUN_7ff7a38f34d0("mp/itemsCollections.csv",local_28);
  uVar1 = FUN_7ff7a38fa3d0(&DAT_7ff7a3cc32b4,param_2);
  iVar3 = FUN_7ff7a38f3700(local_28[0],0,uVar1);
  if (((iVar3 < 0) || (_Str = (char *)FUN_7ff7a38f3510(local_28[0],iVar3,2), _Str == (char *)0x0))
     || (*_Str == '\0')) {
    *param_3 = 0;
    *param_4 = 0;
  }
  else {
    lVar4 = strtol(_Str,(char **)0x0,10);
    iVar6 = 0;
    if (lVar4 - 1U < 0xf) {
      *param_4 = lVar4;
      *param_3 = 0;
      if (0 < lVar4) {
        do {
          uVar1 = FUN_7ff7a38f3510(local_28[0],iVar3,iVar6 + 3);
          iVar5 = FUN_7ff7a37e23d0(uVar1);
          if (iVar5 == 0) {
            *param_3 = 0;
            *param_4 = 0;
            return;
          }
          cVar2 = FUN_7ff7a340a310(param_1,iVar5);
          if (cVar2 != '\0') {
            *param_3 = *param_3 + 1;
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < lVar4);
      }
    }
    else {
      *param_3 = 0;
      *param_4 = 0;
    }
  }
  return;
}

