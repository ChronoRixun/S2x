// image offset 0x275270 address 7ff7a3405270

bool FUN_7ff7a3405270(undefined8 param_1)

{
  int iVar1;
  char *_Str;
  
  _Str = (char *)FUN_7ff7a3261ba0(param_1,0x1e);
  if (_Str != (char *)0x0) {
    iVar1 = atoi(_Str);
    return 0 < iVar1;
  }
  return false;
}

