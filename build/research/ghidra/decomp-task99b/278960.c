// image offset 0x278960 address 7ff7a3408960

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_7ff7a34088e0(undefined4 param_1,int *param_2,uint param_3)

{
  char cVar1;
  longlong lVar2;
  int *piVar3;
  uint uVar4;
  undefined4 *puVar5;
  ulonglong uVar6;
  uint uVar7;
  int *piVar8;
  
  uVar6 = (ulonglong)param_3;
  if ((DAT_7ff7ab0ff108 == 0) || (*(int *)(DAT_7ff7ab0ff108 + 0x10) != 0)) {
    lVar2 = FUN_7ff7a33981b0(5,param_1);
    cVar1 = FUN_7ff7a39c9650(lVar2);
    if ((cVar1 != '\0') &&
       ((cVar1 = FUN_7ff7a39c9710(), cVar1 != '\0' && (DAT_7ff7ab320d8c == '\0')))) {
      uVar7 = 0;
      piVar8 = param_2;
      if (param_3 == 0) {
        FUN_7ff7a339cec0(&DAT_7ff7ab320b80);
        DAT_7ff7ab320d8c = 1;
        _DAT_7ff7ab320d88 = param_3;
      }
      else {
        do {
          uVar4 = 0;
          piVar3 = &DAT_7ff7ab2938b0;
          while (*piVar8 != *piVar3) {
            uVar4 = uVar4 + 1;
            piVar3 = piVar3 + 0xba;
            if (399 < uVar4) {
              return 0;
            }
          }
          if ((ulonglong)uVar4 * 0x2e8 == -0x7ff7ab2938b0) {
            return 0;
          }
          if (*(int *)(&DAT_7ff7ab2938bc + (ulonglong)uVar4 * 0x2e8) == -1) {
            return 0;
          }
          uVar7 = uVar7 + 1;
          piVar8 = piVar8 + 1;
        } while (uVar7 < param_3);
        FUN_7ff7a339cec0(&DAT_7ff7ab320b80);
        puVar5 = &DAT_7ff7ab320d60;
        DAT_7ff7ab320d8c = 1;
        _DAT_7ff7ab320d88 = param_3;
        do {
          *puVar5 = *(undefined4 *)((longlong)(param_2 + -0x1ffdeacc8358) + (longlong)puVar5);
          puVar5 = puVar5 + 1;
          uVar6 = uVar6 - 1;
        } while (uVar6 != 0);
      }
      FUN_7ff7a39c9700(lVar2,&DAT_7ff7ab320b80);
      *(code **)(lVar2 + 0x30) = thunk_FUN_7ff7b4987176;
      *(code **)(lVar2 + 0x40) = FUN_7ff7a340b130;
      *(code **)(lVar2 + 0x38) = FUN_7ff7a340b170;
      FUN_7ff7a39c97e0(lVar2);
      return 1;
    }
  }
  return 0;
}

