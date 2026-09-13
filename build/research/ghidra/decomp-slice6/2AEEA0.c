// image offset 0x2AEEA0 address 7ff7a343eea0

undefined8 FUN_7ff7a343eea0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined8 uVar2;
  char *_Str;
  undefined8 local_res18 [2];
  
  if ((DAT_7ff7a466bda8 == 0) || (*(char *)(DAT_7ff7a466bda8 + 0x10) == '\0')) {
    FUN_7ff7a38f34d0("mp/supplyDropTypes.csv",local_res18);
    uVar2 = FUN_7ff7a38fa3d0(&DAT_7ff7a3cc2f5c,param_2);
    _Str = (char *)FUN_7ff7a38f3560(local_res18[0],1,uVar2);
    if ((_Str != (char *)0x0) && (*_Str != '\0')) {
      iVar1 = atoi(_Str);
      if (iVar1 != 0) {
        uVar2 = FUN_7ff7a3409480(param_1,iVar1);
        return uVar2;
      }
    }
  }
  return 0;
}

