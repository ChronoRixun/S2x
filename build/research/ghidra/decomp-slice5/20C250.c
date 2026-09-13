// image offset 0x20C250 address 7ff7a339c250

void FUN_7ff7a339c250(longlong param_1,undefined4 *param_2)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  ulonglong uVar6;
  char cVar7;
  
  cVar7 = '\0';
  *param_2 = *(undefined4 *)(param_1 + 0x20);
  uVar6 = 0;
  param_2[2] = *(undefined4 *)(param_1 + 0x24);
  param_2[1] = (uint)*(byte *)(param_1 + 0x350);
  param_2[3] = *(undefined4 *)(param_1 + 0x358);
  *(undefined1 *)(param_2 + 0xb8) = *(undefined1 *)(param_1 + 0x35c);
  if (*(char *)(param_1 + 0x118) != '\0') {
    do {
      if (1 < (uint)uVar6) break;
      cVar7 = cVar7 + '\x01';
      param_2[uVar6 * 2 + 0x93] = (uint)*(byte *)(uVar6 * 0x38 + 0x140 + param_1);
      param_2[uVar6 * 2 + 0x94] = *(undefined4 *)(uVar6 * 0x38 + 0x144 + param_1);
      uVar5 = (uint)uVar6 + 1;
      uVar6 = (ulonglong)uVar5;
    } while (uVar5 < *(byte *)(param_1 + 0x118));
  }
  *(char *)((longlong)param_2 + 0x2e1) = cVar7;
  iVar4 = 0x40;
  param_2[0xb7] = *(undefined4 *)(param_1 + 0x70);
  iVar3 = 0x40;
  cVar7 = *(char *)(param_1 + 0x80);
  pcVar1 = (char *)(param_2 + 0x97);
  pcVar2 = pcVar1;
  if (cVar7 != '\0') {
    do {
      if (iVar3 < 2) break;
      *pcVar2 = cVar7;
      iVar3 = iVar3 + -1;
      cVar7 = pcVar2[(longlong)((char *)(param_1 + 0x80) + (1 - (longlong)pcVar1))];
      pcVar2 = pcVar2 + 1;
    } while (cVar7 != '\0');
  }
  *pcVar2 = '\0';
  pcVar1 = (char *)(param_2 + 0xa7);
  cVar7 = *(char *)(param_1 + 0x29);
  pcVar2 = pcVar1;
  if (cVar7 != '\0') {
    do {
      if (iVar4 < 2) break;
      *pcVar2 = cVar7;
      iVar4 = iVar4 + -1;
      cVar7 = pcVar2[(longlong)((char *)(param_1 + 0x29) + (1 - (longlong)pcVar1))];
      pcVar2 = pcVar2 + 1;
    } while (cVar7 != '\0');
  }
  *pcVar2 = '\0';
  return;
}

