// image offset 0x278A50 address 7ff7a3408a50

undefined8 FUN_7ff7a3408a50(int param_1)

{
  char cVar1;
  longlong lVar2;
  longlong lVar3;
  
  if ((DAT_7ff7ab0ff108 == 0) || (*(int *)(DAT_7ff7ab0ff108 + 0x10) != 0)) {
    lVar2 = FUN_7ff7a33981b0(5,param_1);
    cVar1 = FUN_7ff7a39c9650(lVar2);
    if (cVar1 != '\0') {
      cVar1 = FUN_7ff7a39c9710(lVar2);
      if (cVar1 != '\0') {
        lVar3 = (longlong)param_1 * 0x2e0;
        FUN_7ff7a339cba0(&DAT_7ff7ab0ffbb8 + lVar3);
        *(undefined4 *)(&DAT_7ff7ab0ffe90 + lVar3) = 0xd;
        FUN_7ff7a39c9700(lVar2,&DAT_7ff7ab0ffbb8 + lVar3);
        *(undefined8 *)(lVar2 + 0x40) = 0;
        *(code **)(lVar2 + 0x30) = thunk_FUN_7ff7b48629c2;
        *(code **)(lVar2 + 0x38) = FUN_7ff7a340b230;
        FUN_7ff7a39c97e0(lVar2);
        return 1;
      }
    }
  }
  return 0;
}

