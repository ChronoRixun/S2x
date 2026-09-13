// image offset 0x139D50 address 7ff7a32c9d50

int FUN_7ff7a32c9d50(undefined8 param_1)

{
  int iVar1;
  char *_Str;
  undefined8 local_res10 [3];
  
  FUN_7ff7a38f34d0("dw/dwGameChallenges.csv",local_res10);
  _Str = (char *)FUN_7ff7a38f3560(local_res10[0],1,param_1);
  if (_Str != (char *)0x0) {
    iVar1 = FUN_7ff7a3b94f40(_Str,&DAT_7ff7a3cbd562);
    if (iVar1 != 0) {
      iVar1 = atoi(_Str);
      return iVar1;
    }
  }
  return -1;
}

