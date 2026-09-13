// image offset 0x2766F0 address 7ff7a34066f0

ulonglong FUN_7ff7a34066f0(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  ulonglong uVar4;
  undefined *puVar5;
  uint *puVar6;
  
  iVar2 = FUN_7ff7a37e2250(param_2);
  puVar5 = &DAT_7ff7ab0f6de0;
  if (iVar2 != 0) {
    puVar5 = &DAT_7ff7ab0f6bc0;
  }
  uVar4 = 0;
  puVar6 = (uint *)(puVar5 + (longlong)param_1 * 0x110);
  uVar1 = *puVar6;
  if (uVar1 != 0) {
    do {
      if ((puVar6[uVar4 * 2 + 2] == 1) && (puVar6[uVar4 * 2 + 1] == param_2)) goto LAB_7ff7a340675e;
      uVar3 = (int)uVar4 + 1;
      uVar4 = (ulonglong)uVar3;
    } while (uVar3 < uVar1);
  }
  if (0x1d < uVar1) {
    return uVar4 & 0xffffffffffffff00;
  }
  puVar6[(ulonglong)uVar1 * 2 + 1] = param_2;
  uVar4 = (ulonglong)*puVar6;
  puVar6[uVar4 * 2 + 2] = 1;
  *puVar6 = *puVar6 + 1;
LAB_7ff7a340675e:
  return CONCAT71((int7)(uVar4 >> 8),1);
}

