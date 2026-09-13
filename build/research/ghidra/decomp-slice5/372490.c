// image offset 0x372490 address 7ff7a3502490

undefined8 FUN_7ff7a3502490(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  longlong lVar3;
  
  cVar1 = FUN_7ff7a3919d60(param_1);
  if (cVar1 != '\0') {
    cVar1 = FUN_7ff7a3919d20(param_1);
    if (cVar1 != '\0') {
      cVar1 = FUN_7ff7a39c4640(param_1);
      if (cVar1 != '\0') {
        cVar1 = FUN_7ff7a39e3250(param_1);
        if (cVar1 != '\0') {
          lVar3 = FUN_7ff7a33981b0(4,param_1);
          cVar1 = FUN_7ff7a39c9650(lVar3);
          if (cVar1 != '\0') {
            cVar1 = FUN_7ff7a39c9710(lVar3);
            if (cVar1 != '\0') {
              uVar2 = FUN_7ff7a3941290();
              *(undefined4 *)(&DAT_7ff7abba4f8c + (longlong)param_1 * 0x110) = uVar2;
              FUN_7ff7a39c9700(lVar3,&DAT_7ff7abba4f90 + (longlong)param_1 * 0x110);
              *(undefined1 *)(lVar3 + 1) = 0;
              *(code **)(lVar3 + 0x30) = thunk_FUN_7ff7b509fd31;
              *(code **)(lVar3 + 0x40) = FUN_7ff7a3502680;
              *(code **)(lVar3 + 0x38) = FUN_7ff7a35026a0;
              FUN_7ff7a39c97e0(lVar3);
              return 1;
            }
          }
        }
      }
    }
  }
  return 0;
}

