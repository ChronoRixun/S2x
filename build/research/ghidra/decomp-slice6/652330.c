// image offset 0x652330 address 7ff7a37e2330

int FUN_7ff7a37e2330(undefined8 param_1)

{
  int iVar1;
  char *_Str;
  
  _Str = (char *)FUN_7ff7a3261ba0(param_1,0x1d);
  if (_Str != (char *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x7ff7a37e234a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = atoi(_Str);
    return iVar1;
  }
  return -1;
}

