// image offset 0x126970 address 7ff7a32b6970

undefined8 FUN_7ff7a32b6970(longlong param_1)

{
  uint *puVar1;
  undefined4 *puVar2;
  bool bVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  undefined8 uVar7;
  longlong lVar8;
  uint *puVar9;
  undefined4 uVar10;
  
  puVar9 = *(uint **)(param_1 + 0x48);
  puVar1 = *(uint **)(param_1 + 0x50);
  uVar10 = 0;
  if (((((int)((longlong)puVar9 - (longlong)puVar1 >> 4) != 2) || (puVar9 <= puVar1)) ||
      (1 < (*puVar1 & 0xf) - 3)) || ((puVar9 <= puVar1 + 4 || (((byte)puVar1[4] & 0xf) != 1)))) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  puVar9 = *(uint **)(param_1 + 0x48);
  puVar1 = *(uint **)(param_1 + 0x50);
  if ((((int)((longlong)puVar9 - (longlong)puVar1 >> 4) == 2) && (puVar1 < puVar9)) &&
     (((*puVar1 & 0xf) == 3 || (*puVar1 & 0xf) == 4 &&
      ((puVar1 + 4 < puVar9 && (bVar3 = true, ((byte)puVar1[4] & 0xf) == 1)))))) {
    pcVar6 = (char *)FUN_7ff7a3469740(param_1,puVar1,0);
    puVar9 = (uint *)(*(longlong *)(param_1 + 0x50) + 0x10);
    if ((*(uint **)(param_1 + 0x48) <= puVar9) ||
       ((uVar4 = *puVar9 & 0xf, uVar4 == 0 ||
        ((uVar4 == 1 && (*(int *)(*(longlong *)(param_1 + 0x50) + 0x18) == 0)))))) {
      bVar3 = false;
    }
    if (((pcVar6 != (char *)0x0) && (*pcVar6 != '\0')) &&
       (iVar5 = FUN_7ff7a38f6400(pcVar6), 0 < iVar5)) {
      uVar7 = FUN_7ff7a38f6510(iVar5);
      lVar8 = FUN_7ff7a3402560(uVar7);
      if (lVar8 == 0) {
        lVar8 = FUN_7ff7a3402560("seasonpass");
        if ((bVar3) && (lVar8 != 0)) {
          uVar10 = 1;
        }
      }
      else {
        uVar10 = 1;
      }
    }
  }
  puVar2 = *(undefined4 **)(param_1 + 0x48);
  puVar2[2] = uVar10;
  *puVar2 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar2 + 4;
  return 1;
}

