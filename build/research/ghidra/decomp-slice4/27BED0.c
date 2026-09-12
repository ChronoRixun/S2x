// image offset 0x27BED0 address 7ff7a340bed0

void FUN_7ff7a340bed0(void)

{
  short sVar1;
  int iVar2;
  longlong lVar3;
  int iVar4;
  longlong lVar5;
  undefined4 *puVar6;
  
  iVar2 = FUN_7ff7a39c9370();
  lVar5 = (longlong)iVar2 * 0x16a0;
  iVar4 = 0;
  if (0 < *(int *)(&DAT_7ff7ab2dd9cc + lVar5)) {
    puVar6 = (undefined4 *)(&DAT_7ff7ab2dc398 + lVar5);
    do {
      sVar1 = FUN_7ff7a3409300(iVar2,*puVar6,0);
      if (sVar1 != -1) {
        lVar3 = (longlong)iVar2 * 0xc8438 + (longlong)sVar1;
        if (((&DAT_7ff7ab1c6858)[lVar3] & 8) != 0) {
          (&DAT_7ff7ab1c6858)[lVar3] = (&DAT_7ff7ab1c6858)[lVar3] & 0xf7;
        }
      }
      iVar4 = iVar4 + 1;
      puVar6 = puVar6 + 0x30;
    } while (iVar4 < *(int *)(&DAT_7ff7ab2dd9cc + lVar5));
  }
  FUN_7ff7a34052e0(iVar2,2);
  return;
}

