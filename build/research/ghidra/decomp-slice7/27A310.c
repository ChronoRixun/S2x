// image offset 0x27A310 address 7ff7a340a310

undefined1 FUN_7ff7a340a310(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined2 uVar2;
  undefined1 uVar3;
  longlong alStackX_18 [2];
  
  cVar1 = FUN_7ff7a3260980(param_2);
  if (cVar1 != '\0') {
    return 1;
  }
  alStackX_18[0] = 0;
  uVar2 = FUN_7ff7a3409300(param_1,param_2,alStackX_18);
  uVar3 = 0;
  if ((alStackX_18[0] != 0) && (*(int *)(alStackX_18[0] + 4) != 0)) {
    cVar1 = FUN_7ff7a340a260(param_1,uVar2);
    uVar3 = 0;
    if (cVar1 == '\0') {
      uVar3 = 1;
    }
  }
  return uVar3;
}

