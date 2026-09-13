// image offset 0x27F020 address 7ff7a340f020

float FUN_7ff7a340f020(longlong param_1,uint *param_2)

{
  int *piVar1;
  char *_Str;
  uint uVar2;
  double dVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  char *local_res10 [3];
  
  if (1 < (*param_2 >> 0x1d) - 3) {
    return 0.0;
  }
  uVar2 = *param_2 & 0x1fffffff;
  if (uVar2 == 0x1fffffff) {
    _Str = (char *)0x0;
  }
  else {
    _Str = (char *)((ulonglong)uVar2 + *(longlong *)(param_1 + 0x100));
  }
  piVar1 = _errno();
  *piVar1 = 0;
  dVar3 = strtod(_Str,local_res10);
  piVar1 = _errno();
  if ((*piVar1 == 0) && (*local_res10[0] == '\0')) {
    if ((dVar3 < -3.4028234663852886e+38) ||
       (uVar4 = SUB84(dVar3,0), uVar5 = (int)((ulonglong)dVar3 >> 0x20),
       3.4028234663852886e+38 < dVar3)) {
      return 0.0;
    }
  }
  else {
    uVar4 = 0;
    uVar5 = 0;
  }
  return (float)(double)CONCAT44(uVar5,uVar4);
}

