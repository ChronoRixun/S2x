// image offset 0x278D30 address 7ff7a3408d30

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
FUN_7ff7a3408d30(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined8 param_4,
                undefined8 param_5)

{
  char cVar1;
  longlong lVar2;
  
  if ((DAT_7ff7ab0ff108 == 0) || (*(int *)(DAT_7ff7ab0ff108 + 0x10) != 0)) {
    lVar2 = FUN_7ff7a33981b0(5,param_1);
    cVar1 = FUN_7ff7a39c9650(lVar2);
    if ((cVar1 != '\0') &&
       ((cVar1 = FUN_7ff7a39c9710(lVar2), cVar1 != '\0' && (DAT_7ff7ab320b7c == '\0')))) {
      FUN_7ff7a339d0e0(&DAT_7ff7ab30b218);
      _DAT_7ff7ab320b74 = 100;
      _DAT_7ff7ab320b6c = 0;
      DAT_7ff7ab320b7c = 1;
      _DAT_7ff7ab320b70 = param_2;
      _DAT_7ff7ab320b78 = param_3;
      FUN_7ff7a39c9700(lVar2,&DAT_7ff7ab30b218);
      *(undefined8 *)(lVar2 + 0x38) = param_4;
      *(code **)(lVar2 + 0x30) = thunk_FUN_7ff7a334c1af;
      *(undefined8 *)(lVar2 + 0x40) = param_5;
      FUN_7ff7a39c97e0(lVar2);
      return 1;
    }
  }
  return 0;
}

