// image offset 0x27B170 address 7ff7a340b170

void FUN_7ff7a340b170(void)

{
  undefined4 uVar1;
  longlong lVar2;
  int *piVar3;
  uint uVar4;
  ulonglong uVar5;
  longlong lVar6;
  longlong lVar7;
  ulonglong uVar8;
  
  uVar1 = FUN_7ff7a39c9370();
  lVar2 = FUN_7ff7a39c9390();
  uVar8 = 0;
  *(undefined1 *)(lVar2 + 0x20c) = 0;
  if (*(int *)(lVar2 + 0x208) != 0) {
    do {
      piVar3 = &DAT_7ff7ab2938b0;
      lVar7 = uVar8 * 0x30 + lVar2;
      uVar5 = 0;
      do {
        if (*(int *)(lVar7 + 0x10) == *piVar3) {
          lVar6 = uVar5 * 0x2e8;
          if (lVar6 != -0x7ff7ab2938b0) {
            *(undefined4 *)(&DAT_7ff7ab2938bc + lVar6) = *(undefined4 *)(lVar7 + 0x14);
            *(undefined4 *)(&DAT_7ff7ab293af8 + lVar6) = *(undefined4 *)(lVar7 + 0x18);
            (&DAT_7ff7ab293b90)[lVar6] = *(undefined1 *)(lVar7 + 0x1c);
          }
          break;
        }
        uVar4 = (int)uVar5 + 1;
        uVar5 = (ulonglong)uVar4;
        piVar3 = piVar3 + 0xba;
      } while (uVar4 < 400);
      uVar4 = (int)uVar8 + 1;
      uVar8 = (ulonglong)uVar4;
    } while (uVar4 < *(uint *)(lVar2 + 0x208));
  }
  FUN_7ff7a3405360(uVar1,5,1);
  return;
}

