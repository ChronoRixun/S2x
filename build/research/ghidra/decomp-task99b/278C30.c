// image offset 0x278C30 address 7ff7a3408c30

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_7ff7a3408c30(undefined4 param_1,longlong param_2,int param_3,undefined1 param_4)

{
  char cVar1;
  longlong lVar2;
  longlong lVar3;
  
  if ((DAT_7ff7ab0ff108 == 0) || (*(int *)(DAT_7ff7ab0ff108 + 0x10) != 0)) {
    lVar2 = FUN_7ff7a33981b0(5,param_1);
    cVar1 = FUN_7ff7a39c9650(lVar2);
    if ((cVar1 != '\0') && (cVar1 = FUN_7ff7a39c9710(lVar2), cVar1 != '\0')) {
      FUN_7ff7a339cf90();
      _DAT_7ff7ab30b210 = param_3;
      DAT_7ff7ab30b214 = param_4;
      if (0 < param_3) {
        lVar3 = 0;
        do {
          (&DAT_7ff7ab30b080)[lVar3] = *(undefined4 *)(param_2 + lVar3 * 4);
          lVar3 = lVar3 + 1;
        } while (lVar3 < param_3);
      }
      FUN_7ff7a39c9700(lVar2,&DAT_7ff7ab2fa6e0);
      *(code **)(lVar2 + 0x30) = thunk_FUN_7ff7b51146a3;
      *(undefined **)(lVar2 + 0x40) = &DAT_7ff7a340b4c0;
      *(code **)(lVar2 + 0x38) = FUN_7ff7a340b4d0;
      FUN_7ff7a39c97e0(lVar2);
      return 1;
    }
  }
  return 0;
}

