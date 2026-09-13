// image offset 0x372CF0 address 7ff7a3502cf0

void FUN_7ff7a3502cd0(int param_1)

{
  undefined8 *puVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined8 uVar8;
  char *pcVar9;
  void *_Dst;
  ulonglong uVar10;
  ulonglong uVar11;
  longlong lVar12;
  longlong lVar13;
  uint uVar14;
  int iVar15;
  longlong local_res10;
  undefined8 local_58;
  undefined8 uStack_50;
  int local_48;
  uint uStack_44;
  int iStack_40;
  int iStack_3c;
  undefined8 local_38;
  
  lVar13 = (longlong)param_1 * 0x110;
  FUN_7ff7a38f34d0("mp/marketingcomms.csv",&local_res10);
  FUN_7ff7a3be04a0(lVar13 + 0x7ff7abba4fa8);
  FUN_7ff7a3be0be0(lVar13 + 0x7ff7abba5000);
  *(undefined8 *)(&DAT_7ff7abba4f60 + lVar13) = 0;
  (&DAT_7ff7abba4f84)[(longlong)param_1 * 0x44] = 0;
  uVar8 = FUN_7ff7a38bd380();
  FUN_7ff7a38fc8e0(lVar13 + 0x7ff7abba4fc8,uVar8,0x14);
  *(longlong *)(&DAT_7ff7abba4f90 + lVar13) = lVar13 + 0x7ff7abba4fa8;
  *(longlong *)(&DAT_7ff7abba4f98 + lVar13) = lVar13 + 0x7ff7abba5000;
  if (local_res10 != 0) {
    iVar5 = FUN_7ff7a38f3550();
    iVar15 = 0;
    if (0 < iVar5) {
      lVar12 = 0;
      do {
        FUN_7ff7a3be0200(&local_58,1);
        pcVar9 = (char *)FUN_7ff7a38f3510(local_res10,iVar15,0);
        iVar6 = atoi(pcVar9);
        pcVar9 = (char *)FUN_7ff7a38f3510(local_res10,iVar15);
        uVar7 = atoi(pcVar9);
        uVar11 = (ulonglong)uVar7;
        iVar3 = *(int *)(&DAT_7ff7abba4fe8 + lVar13);
        local_48 = iVar6;
        uStack_44 = uVar7;
        if (*(int *)(&DAT_7ff7abba4fec + lVar13) == iVar3) {
          iVar6 = iVar3;
          if (iVar3 == 0) {
            iVar6 = 1;
          }
          _Dst = (void *)0x0;
          uVar14 = iVar6 + iVar3;
          if (uVar14 != 0) {
            _Dst = (void *)FUN_7ff7a3c05210((ulonglong)uVar14 * 0x28);
            if (*(uint *)(&DAT_7ff7abba4fec + lVar13) != 0) {
              memcpy(_Dst,*(void **)(&DAT_7ff7abba4fe0 + lVar13),
                     (ulonglong)*(uint *)(&DAT_7ff7abba4fec + lVar13) * 0x28);
            }
          }
          FUN_7ff7a3c05240(*(undefined8 *)(&DAT_7ff7abba4fe0 + lVar13));
          *(void **)(&DAT_7ff7abba4fe0 + lVar13) = _Dst;
          *(uint *)(&DAT_7ff7abba4fe8 + lVar13) = uVar14;
        }
        uVar10 = (ulonglong)*(uint *)(&DAT_7ff7abba4fec + lVar13);
        lVar4 = *(longlong *)(&DAT_7ff7abba4fe0 + lVar13);
        puVar1 = (undefined8 *)(lVar4 + uVar10 * 0x28);
        *puVar1 = local_58;
        puVar1[1] = uStack_50;
        piVar2 = (int *)(lVar4 + 0x10 + uVar10 * 0x28);
        *piVar2 = local_48;
        piVar2[1] = uStack_44;
        piVar2[2] = iStack_40;
        piVar2[3] = iStack_3c;
        *(undefined8 *)(lVar4 + 0x20 + uVar10 * 0x28) = local_38;
        *(int *)(&DAT_7ff7abba4fec + lVar13) = *(int *)(&DAT_7ff7abba4fec + lVar13) + 1;
        if (0 < (int)uVar7) {
          do {
            if (lVar12 < 0x19) {
              (&DAT_7ff7abba4f68)[lVar12 + lVar13] = 0;
              lVar12 = lVar12 + 1;
            }
            uVar11 = uVar11 - 1;
          } while (uVar11 != 0);
        }
        FUN_7ff7a3bcb470(&local_48);
        FUN_7ff7a3c04d10(&iStack_40);
        iVar15 = iVar15 + 1;
      } while (iVar15 < iVar5);
    }
  }
  return;
}

