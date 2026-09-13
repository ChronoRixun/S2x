// image offset 0x27F430 address 7ff7a340f430

undefined8 FUN_7ff7a340f430(longlong param_1,uint *param_2,byte *param_3,undefined8 *param_4)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  ulonglong uVar4;
  longlong lVar5;
  longlong lVar6;
  int iVar7;
  byte *pbVar8;
  uint *puVar9;
  
  uVar4 = (ulonglong)*param_3;
  puVar9 = (uint *)0x0;
  if (*param_3 != 0) {
    do {
      bVar1 = (byte)uVar4;
      pbVar8 = param_3;
      while ((bVar1 != 0x2e && ((char)uVar4 != '\0'))) {
        bVar1 = pbVar8[1];
        pbVar8 = pbVar8 + 1;
        uVar4 = (ulonglong)bVar1;
      }
      iVar7 = (int)pbVar8 - (int)param_3;
      uVar2 = *param_2 & 0xe0000000;
      uVar4 = (ulonglong)uVar2;
      if ((0x20000000 < uVar2) || (uVar2 = *param_2 & 0x1fffffff, uVar2 == 0x1fffffff)) {
LAB_7ff7a340f53a:
        puVar9 = (uint *)0x0;
        goto LAB_7ff7a340f546;
      }
      param_2 = (uint *)(*(ulonglong *)(param_1 + 0x118) + (ulonglong)uVar2 * 0xc);
      uVar4 = *(ulonglong *)(param_1 + 0x118);
      while( true ) {
        puVar9 = param_2;
        if (param_2 == (uint *)0x0) goto LAB_7ff7a340f546;
        if (param_2[1] == 0xffffffff) {
          lVar6 = 0;
        }
        else {
          lVar6 = (ulonglong)param_2[1] + *(longlong *)(param_1 + 0x100);
        }
        lVar5 = -1;
        do {
          lVar5 = lVar5 + 1;
        } while (*(char *)(lVar6 + lVar5) != '\0');
        if ((iVar7 == (int)lVar5) && (iVar3 = FUN_7ff7a3b95000(param_3,lVar6,iVar7), iVar3 == 0))
        break;
        uVar4 = (ulonglong)param_2[2];
        if (param_2[2] == 0xffffffff) goto LAB_7ff7a340f53a;
        param_2 = (uint *)(*(ulonglong *)(param_1 + 0x118) + uVar4 * 0xc);
        uVar4 = *(ulonglong *)(param_1 + 0x118);
      }
      bVar1 = *pbVar8;
      param_3 = pbVar8;
      while (bVar1 == 0x2e) {
        param_3 = param_3 + 1;
        bVar1 = *param_3;
      }
      uVar4 = (ulonglong)*param_3;
    } while (*param_3 != 0);
    uVar4 = 0;
  }
LAB_7ff7a340f546:
  if (param_4 != (undefined8 *)0x0) {
    *param_4 = puVar9;
  }
  return CONCAT71((int7)(uVar4 >> 8),puVar9 != (uint *)0x0);
}

