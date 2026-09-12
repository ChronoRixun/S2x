// image offset 0x2AF080 address 7ff7a343f080

int FUN_7ff7a343f080(undefined4 param_1)

{
  int iVar1;
  undefined8 uVar2;
  char *_Str;
  int iVar3;
  int iVar4;
  undefined8 local_res10;
  
  iVar4 = 0;
  iVar3 = 0;
  do {
    if ((DAT_7ff7a466bda8 == 0) || (*(char *)(DAT_7ff7a466bda8 + 0x10) == '\0')) {
      FUN_7ff7a38f34d0("mp/supplyDropTypes.csv",&local_res10);
      uVar2 = FUN_7ff7a38fa3d0(&DAT_7ff7a3cc2f5c,iVar3);
      _Str = (char *)FUN_7ff7a38f3560(local_res10,1,uVar2);
      if ((_Str == (char *)0x0) || (*_Str == '\0')) goto LAB_7ff7a343f10a;
      iVar1 = atoi(_Str);
      if (iVar1 == 0) goto LAB_7ff7a343f10a;
      iVar1 = FUN_7ff7a3409480(param_1,iVar1);
    }
    else {
LAB_7ff7a343f10a:
      iVar1 = 0;
    }
    iVar4 = iVar4 + iVar1;
    iVar3 = iVar3 + 1;
    if (0xff < iVar3) {
      return iVar4;
    }
  } while( true );
}

