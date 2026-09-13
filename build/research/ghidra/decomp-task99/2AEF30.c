// image offset 0x2AEF30 address 7ff7a343ef30

void FUN_7ff7a343ef30(int param_1,undefined8 param_2,longlong param_3,uint param_4,uint *param_5,
                     longlong param_6,uint param_7,undefined4 *param_8)

{
  undefined4 uVar1;
  char cVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  uint uVar5;
  uint uVar7;
  longlong lVar8;
  ulonglong uVar6;
  
  uVar4 = 0;
  lVar8 = (longlong)param_1 * 0x154;
  uVar5 = 0;
  *param_5 = 0;
  *param_8 = 0;
  cVar2 = FUN_7ff7a39c9000(param_2,&DAT_7ff7ab973b30 + lVar8);
  if (cVar2 != '\0') {
    if (*(int *)(&DAT_7ff7ab973c14 + lVar8) != 0) {
      uVar3 = uVar4;
      do {
        uVar1 = *(undefined4 *)(&DAT_7ff7ab973b4c + (uVar4 + (longlong)param_1 * 0x55) * 4);
        cVar2 = FUN_7ff7a3405230(uVar1);
        uVar6 = uVar3;
        if ((cVar2 == '\0') && (cVar2 = FUN_7ff7a3406bc0(uVar1), cVar2 == '\0')) {
          uVar5 = (int)uVar3 + 1;
          uVar6 = (ulonglong)uVar5;
          *(undefined4 *)(param_3 + 4 + uVar3 * 8) = 1;
          *(undefined4 *)(param_3 + uVar3 * 8) = uVar1;
          if (param_4 <= uVar5) break;
        }
        uVar5 = (uint)uVar6;
        uVar7 = (int)uVar4 + 1;
        uVar4 = (ulonglong)uVar7;
        uVar3 = uVar6;
      } while (uVar7 < *(uint *)(&DAT_7ff7ab973c14 + lVar8));
    }
    uVar3 = 0;
    *param_5 = uVar5;
    uVar4 = uVar3;
    if (*(int *)(&DAT_7ff7ab973c80 + lVar8) != 0) {
      do {
        *(undefined8 *)(param_6 + uVar4 * 8) =
             *(undefined8 *)(&DAT_7ff7ab973c18 + lVar8 + uVar3 * 8);
        uVar5 = (int)uVar4 + 1;
        uVar4 = (ulonglong)uVar5;
        if (param_7 <= uVar5) break;
        uVar5 = (int)uVar3 + 1;
        uVar3 = (ulonglong)uVar5;
      } while (uVar5 < *(uint *)(&DAT_7ff7ab973c80 + lVar8));
    }
    *param_8 = (int)uVar4;
  }
  return;
}

