// image offset 0x276580 address 7ff7a3406580

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_7ff7a3406580(undefined4 param_1,undefined8 param_2,undefined8 param_3,undefined8 *param_4,
                     int param_5)

{
  undefined8 uVar1;
  char cVar2;
  
  *param_4 = 0;
  param_4[1] = 0;
  param_4[2] = 0;
  *(undefined1 *)(param_4 + 3) = 0;
  if ((DAT_7ff7ab0f487c == 0) &&
     (cVar2 = FUN_7ff7a3404570(0,param_2,param_3,param_5), cVar2 != '\0')) {
    DAT_7ff7ab0f4850 = (undefined4)param_2;
    _DAT_7ff7ab0f4854 = CONCAT44(param_5,(int)param_3);
    DAT_7ff7ab0f4878 = param_1;
    FUN_7ff7a39c90a0(&DAT_7ff7ab0f485c);
    if (param_5 == 0x96) {
      DAT_7ff7ab0f487c = 2;
      cVar2 = FUN_7ff7a340c640(DAT_7ff7ab0f4878,DAT_7ff7ab0f4850,_DAT_7ff7ab0f4854 & 0xffffffff,
                               &DAT_7ff7ab0f485c,DAT_7ff7ab0f4858);
      if (cVar2 == '\0') {
        DAT_7ff7ab0f4850 = 0;
        _DAT_7ff7ab0f4854 = 0;
        _DAT_7ff7ab0f485c = 0;
        uRam00007ff7ab0f4864 = 0;
        DAT_7ff7ab0f486c = 0;
        DAT_7ff7ab0f4874 = 0;
        DAT_7ff7ab0f4878 = 0xffffffff;
        DAT_7ff7ab0f487c = 0;
        return;
      }
    }
    else {
      DAT_7ff7ab0f487c = 1;
    }
    uVar1 = uRam00007ff7ab0f4864;
    *param_4 = _DAT_7ff7ab0f485c;
    param_4[1] = uVar1;
    param_4[2] = DAT_7ff7ab0f486c;
    *(undefined1 *)(param_4 + 3) = DAT_7ff7ab0f4874;
  }
  return;
}

