// image offset 0x4A0D90 address 7ff7a3630d90

undefined8 FUN_7ff7a3630d90(int param_1,int *param_2)

{
  char cVar1;
  int iVar2;
  
  if (DAT_7ff7a4119a44 == 0) {
    if (param_1 == DAT_7ff7ac24b230) {
LAB_7ff7a3630df0:
      *param_2 = 0;
      return 1;
    }
  }
  else {
    iVar2 = (&DAT_7ff7ac24b238)[param_1];
    if (-1 < iVar2) {
      if ((DAT_7ff7a4d636f8 != '\0') && (*(char *)(DAT_7ff7a466b580 + 0x10) != '\0')) {
        if (param_1 == DAT_7ff7a466b588) goto LAB_7ff7a3630df0;
        if (iVar2 == 0) {
          *param_2 = 1;
          return 1;
        }
      }
      *param_2 = iVar2;
      return 1;
    }
    if (param_1 < 2) {
      cVar1 = FUN_7ff7a39e6280();
      if (cVar1 == '\0') {
        cVar1 = FUN_7ff7a39e6750();
        if (cVar1 == '\0') {
          iVar2 = FUN_7ff7a39e6fa0();
          if (iVar2 == 0) {
            cVar1 = FUN_7ff7a39e65f0();
            if (cVar1 == '\0') {
              *param_2 = param_1;
              return 1;
            }
          }
        }
      }
    }
  }
  *param_2 = -1;
  return 0;
}

