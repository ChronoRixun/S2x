// image offset 0x27C640 address 7ff7a340c640

undefined8
FUN_7ff7a340c640(int param_1,int param_2,undefined4 param_3,undefined4 *param_4,int param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  char cVar4;
  uint uVar5;
  longlong lVar6;
  ulonglong uVar7;
  int *piVar8;
  longlong lVar9;
  
  if ((DAT_7ff7ab0ff108 == 0) || (*(int *)(DAT_7ff7ab0ff108 + 0x10) != 0)) {
    lVar6 = FUN_7ff7a33981b0(5,param_1);
    cVar4 = FUN_7ff7a39c9650(lVar6);
    if ((cVar4 != '\0') && (cVar4 = FUN_7ff7a39c9710(lVar6), cVar4 != '\0')) {
      if (param_5 == 0x96) {
LAB_7ff7a340c706:
        lVar9 = (longlong)param_1 * 0x2360;
        FUN_7ff7a339d510(&DAT_7ff7ab320d90 + lVar9);
        *(int *)(&DAT_7ff7ab320da0 + lVar9) = param_2;
        *(undefined4 *)(&DAT_7ff7ab320da4 + lVar9) = param_3;
        *(undefined4 *)(&DAT_7ff7ab320ff8 + lVar9) = 1;
        uVar1 = param_4[1];
        uVar2 = param_4[2];
        uVar3 = param_4[3];
        *(undefined4 *)(&DAT_7ff7ab320ffc + lVar9) = *param_4;
        *(undefined4 *)(lVar9 + 0x7ff7ab321000) = uVar1;
        *(undefined4 *)(lVar9 + 0x7ff7ab321004) = uVar2;
        *(undefined4 *)(lVar9 + 0x7ff7ab321008) = uVar3;
        *(undefined8 *)(&DAT_7ff7ab32100c + lVar9) = *(undefined8 *)(param_4 + 4);
        (&DAT_7ff7ab321014)[lVar9] = *(undefined1 *)(param_4 + 6);
        FUN_7ff7a39c9700(lVar6,&DAT_7ff7ab320d90 + lVar9);
        *(code **)(lVar6 + 0x30) = thunk_FUN_7ff7a3394ba0;
        *(code **)(lVar6 + 0x40) = FUN_7ff7a340ba20;
        *(code **)(lVar6 + 0x38) = FUN_7ff7a340ba60;
        FUN_7ff7a39c97e0(lVar6);
        return 1;
      }
      uVar7 = 0;
      piVar8 = &DAT_7ff7ab2938b0;
      do {
        if (param_2 == *piVar8) {
          if (uVar7 * 0x2e8 == -0x7ff7ab2938b0) {
            return 0;
          }
          if ((&DAT_7ff7ab293af0)[uVar7 * 0xba] == 0) {
            return 0;
          }
          goto LAB_7ff7a340c706;
        }
        uVar5 = (int)uVar7 + 1;
        uVar7 = (ulonglong)uVar5;
        piVar8 = piVar8 + 0xba;
      } while (uVar5 < 400);
    }
  }
  return 0;
}

