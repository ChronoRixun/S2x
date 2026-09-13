// image offset 0x700D00 address 7ff7a3890d00

undefined8 FUN_7ff7a3890d00(int param_1,undefined4 param_2)

{
  char cVar1;
  longlong lVar2;
  longlong lVar3;
  
  cVar1 = FUN_7ff7a37eb520(param_1);
  if (cVar1 != '\0') {
    lVar2 = FUN_7ff7a33981b0(9,param_1,0x8b);
    cVar1 = FUN_7ff7a39c9650(lVar2);
    if (cVar1 != '\0') {
      cVar1 = FUN_7ff7a39c9710(lVar2);
      if (cVar1 != '\0') {
        lVar3 = (longlong)param_1 * 0x3848;
        FUN_7ff7a339dbd0(&DAT_7ff7affaa010 + lVar3);
        *(undefined4 *)(&DAT_7ff7affad854 + lVar3) = 200;
        *(undefined4 *)(&DAT_7ff7affad850 + lVar3) = param_2;
        FUN_7ff7a39c9700(lVar2,&DAT_7ff7affaa010 + lVar3);
        *(code **)(lVar2 + 0x30) = thunk_FUN_7ff7b5069cb2;
        *(undefined **)(lVar2 + 0x40) = &DAT_7ff7a3891140;
        *(code **)(lVar2 + 0x38) = FUN_7ff7a3890fd0;
        FUN_7ff7a39c97e0(lVar2);
        return 1;
      }
    }
  }
  return 0;
}

