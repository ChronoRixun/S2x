// image offset 0x278F30 address 7ff7a3408f30

void FUN_7ff7a3408f30(int param_1,longlong param_2,uint param_3)

{
  int iVar1;
  ulonglong uVar2;
  longlong lVar3;
  short sVar4;
  longlong lVar5;
  
  lVar5 = (longlong)param_1 * 0xc8438;
  uVar2 = 0;
  if ((&DAT_7ff7ab1c85a8)[lVar5] != '\0') {
    iVar1 = *(int *)(&DAT_7ff7ab1c85a4 + lVar5);
    sVar4 = 0;
    if (0 < iVar1) {
      do {
        lVar3 = (longlong)sVar4 * 0x68 + lVar5;
        if (((&DAT_7ff7ab108198)[lVar3] & 2) == 0) {
          if (param_3 <= (uint)uVar2) {
            return;
          }
          *(undefined4 *)(param_2 + uVar2 * 4) = *(undefined4 *)(&DAT_7ff7ab108178 + lVar3);
          uVar2 = (ulonglong)((uint)uVar2 + 1);
        }
        sVar4 = sVar4 + 1;
      } while (sVar4 < iVar1);
    }
  }
  return;
}

