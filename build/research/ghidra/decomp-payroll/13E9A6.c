// image offset 0x13E9A6 address 7ff7a32ce9a6

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_7ff7a32ce960(int param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  longlong lVar1;
  char cVar2;
  uint uVar3;
  longlong lVar4;
  int iVar5;
  int *piVar6;
  longlong lVar7;
  int *piVar8;
  undefined1 *puVar9;
  longlong lVar10;
  longlong lVar11;
  undefined1 auStack_c8 [32];
  undefined4 *local_a8;
  undefined8 local_98;
  undefined8 local_90;
  undefined8 local_88;
  undefined4 uStack_80;
  int iStack_7c;
  undefined8 local_78;
  undefined8 uStack_70;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  int iStack_5c;
  undefined8 local_58;
  int iStack_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  ulonglong local_38;
  
  local_38 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_c8;
  lVar4 = FUN_7ff7a3398270(0,param_1,0x84);
  if (lVar4 != 0) {
    lVar4 = FUN_7ff7a39c9390(lVar4);
    cVar2 = FUN_7ff7a39c9000(lVar4 + 0xd0,param_4);
    if ((cVar2 != '\0') &&
       (cVar2 = FUN_7ff7a340f430(param_2,param_3,"Achievements",&local_90), cVar2 != '\0')) {
      puVar9 = *(undefined1 **)(lVar4 + 0xf0);
      cVar2 = FUN_7ff7a340f430(param_2,param_3,"NextPageToken");
      if ((cVar2 != '\0') &&
         ((cVar2 = FUN_7ff7a340fce0(local_98), cVar2 == '\0' &&
          (cVar2 = FUN_7ff7a340f570(param_2,param_3,"NextPageToken"), cVar2 != '\0')))) {
        iVar5 = 0x20;
        if (*(char *)CONCAT44(uStack_44,local_48) != '\0') {
          lVar4 = (longlong)CONCAT44(uStack_44,local_48) - (longlong)puVar9;
          do {
            if (iVar5 < 2) break;
            iVar5 = iVar5 + -1;
            *puVar9 = puVar9[lVar4];
            puVar9 = puVar9 + 1;
          } while (puVar9[lVar4] != '\0');
        }
        *puVar9 = 0;
      }
      for (lVar4 = FUN_7ff7a340efe0(param_2,local_90); lVar4 != 0;
          lVar4 = FUN_7ff7a340f240(param_2,lVar4)) {
        local_a8 = &local_48;
        cVar2 = FUN_7ff7a32ca570(param_2,lVar4,&local_88);
        if ((cVar2 != '\0') && ((iStack_5c != 0 || (iStack_50 != 1)))) {
          lVar11 = (longlong)param_1 * 0x13890;
          uVar3 = 0;
          piVar6 = (int *)(&DAT_7ff7a923409c + lVar11);
          piVar8 = piVar6;
          do {
            if (*piVar8 == iStack_7c) {
              if (uVar3 != 0xffffffff) {
                lVar10 = (longlong)(int)uVar3 * 0x40 + lVar11;
                if ((undefined8 *)(&DAT_7ff7a9234090 + lVar10) != (undefined8 *)0x0) {
                  *(undefined8 *)(&DAT_7ff7a9234090 + lVar10) = local_88;
                  *(ulonglong *)(&DAT_7ff7a9234098 + lVar10) = CONCAT44(iStack_7c,uStack_80);
                  *(undefined8 *)(&DAT_7ff7a92340a0 + lVar10) = local_78;
                  *(undefined8 *)(&DAT_7ff7a92340a8 + lVar10) = uStack_70;
                  *(undefined4 *)(&DAT_7ff7a92340b0 + lVar10) = local_68;
                  *(undefined4 *)(lVar10 + 0x7ff7a92340b4) = uStack_64;
                  *(undefined4 *)(&DAT_7ff7a92340b8 + lVar10) = uStack_60;
                  *(int *)(&DAT_7ff7a92340bc + lVar10) = iStack_5c;
                  *(undefined8 *)(&DAT_7ff7a92340c0 + lVar10) = local_58;
                  *(ulonglong *)(&DAT_7ff7a92340c8 + lVar10) = CONCAT44(uStack_4c,iStack_50);
                  goto LAB_7ff7a32cebde;
                }
              }
              break;
            }
            uVar3 = uVar3 + 1;
            piVar8 = piVar8 + 0x10;
          } while (uVar3 < 1000);
          uVar3 = 0;
          lVar10 = 0;
          while (*piVar6 != -1) {
            uVar3 = uVar3 + 1;
            lVar10 = lVar10 + 1;
            piVar6 = piVar6 + 0x10;
            if (999 < uVar3) {
              return;
            }
          }
          if (uVar3 == 0xffffffff) {
            return;
          }
          lVar7 = (longlong)param_1 * 0x1389;
          lVar1 = lVar11 + lVar10 * 0x40;
          *(undefined8 *)(&DAT_7ff7a9234090 + lVar1) = local_88;
          *(ulonglong *)(&DAT_7ff7a9234098 + lVar1) = CONCAT44(iStack_7c,uStack_80);
          *(undefined8 *)(&DAT_7ff7a92340a0 + lVar1) = local_78;
          *(undefined8 *)(&DAT_7ff7a92340a8 + lVar1) = uStack_70;
          *(ulonglong *)(&DAT_7ff7a92340b0 + lVar1) = CONCAT44(uStack_64,local_68);
          *(ulonglong *)(&DAT_7ff7a92340b8 + lVar1) = CONCAT44(iStack_5c,uStack_60);
          *(undefined8 *)(&DAT_7ff7a92340c0 + lVar1) = local_58;
          *(ulonglong *)(&DAT_7ff7a92340c8 + lVar1) = CONCAT44(uStack_4c,iStack_50);
          lVar1 = (lVar7 + lVar10) * 0x10;
          *(undefined4 *)(&DAT_7ff7a9243a90 + lVar1) = local_48;
          *(undefined4 *)(lVar1 + 0x7ff7a9243a94) = uStack_44;
          *(undefined4 *)(lVar1 + 0x7ff7a9243a98) = uStack_40;
          *(undefined4 *)(lVar1 + 0x7ff7a9243a9c) = uStack_3c;
          *(undefined **)(&DAT_7ff7a92340b0 + lVar10 * 0x40 + lVar11) =
               &DAT_7ff7a9243a90 + ((int)uVar3 + lVar7) * 0x10;
        }
LAB_7ff7a32cebde:
      }
    }
  }
  return;
}

