// image offset 0x27D2A0 address 7ff7a340d2a0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_7ff7a340d160(void)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  longlong lVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  uint uVar7;
  ulonglong uVar8;
  int *piVar9;
  ulonglong uVar10;
  ulonglong uVar11;
  
  if ((DAT_7ff7ab0ff108 != 0) && (*(int *)(DAT_7ff7ab0ff108 + 0x10) == 0)) {
    return;
  }
  cVar1 = FUN_7ff7a33978b0();
  if (cVar1 != '\0') {
    uVar8 = 0;
    uVar6 = uVar8;
    do {
      iVar2 = FUN_7ff7a320dfd0(uVar6);
      if ((iVar2 != 0) && (DAT_7ff7a4d636f8 == '\0')) goto LAB_7ff7a340d4eb;
      uVar7 = (int)uVar6 + 1;
      uVar6 = (ulonglong)uVar7;
    } while ((int)uVar7 < 2);
    uVar6 = uVar8;
    if ((DAT_7ff7ab0ff108 == 0) || (*(int *)(DAT_7ff7ab0ff108 + 0x10) != 0)) {
      do {
        lVar4 = FUN_7ff7a3398270(5,uVar6);
        if ((lVar4 != 0) && (iVar2 = FUN_7ff7a39c9380(lVar4), iVar2 == 1)) {
          FUN_7ff7a3408a50(uVar6);
        }
        lVar4 = FUN_7ff7a3398270(5,uVar6);
        if (((lVar4 != 0) && (iVar2 = FUN_7ff7a39c9380(lVar4), iVar2 == 1)) &&
           (DAT_7ff7ab2fa600 == '\0')) {
          FUN_7ff7a3408b30(uVar6,1);
        }
        lVar4 = FUN_7ff7a3398270(5,uVar6);
        if (((lVar4 != 0) && (iVar2 = FUN_7ff7a39c9380(lVar4), iVar2 == 1)) &&
           ((DAT_7ff7ab0ff108 == 0 || (*(int *)(DAT_7ff7ab0ff108 + 0x10) != 0)))) {
          lVar4 = FUN_7ff7a33981b0(5,uVar6);
          cVar1 = FUN_7ff7a39c9650(lVar4);
          if ((cVar1 != '\0') && (cVar1 = FUN_7ff7a39c9710(lVar4), cVar1 != '\0')) {
            FUN_7ff7a39c9700(lVar4,0);
            *(code **)(lVar4 + 0x30) = thunk_FUN_7ff7b4a47d69;
            *(undefined8 *)(lVar4 + 0x40) = 0;
            *(undefined **)(lVar4 + 0x38) = &DAT_7ff7a340b8c0;
            FUN_7ff7a39c97e0(lVar4);
          }
        }
        lVar4 = FUN_7ff7a3398270(5,uVar6);
        if ((lVar4 != 0) && (iVar2 = FUN_7ff7a39c9380(lVar4), iVar2 == 1)) {
          FUN_7ff7a340cf30(uVar6);
        }
        uVar7 = (int)uVar6 + 1;
        uVar6 = (ulonglong)uVar7;
      } while ((int)uVar7 < 2);
    }
    piVar9 = &DAT_7ff7ab32b568;
    uVar6 = uVar8;
    do {
      if (0 < *piVar9) {
        FUN_7ff7a340d6b0(uVar6);
      }
      uVar7 = (int)uVar6 + 1;
      uVar6 = (ulonglong)uVar7;
      piVar9 = piVar9 + 1;
    } while ((int)uVar7 < 2);
    uVar6 = uVar8;
    if ((DAT_7ff7ab0ff108 == 0) || (*(int *)(DAT_7ff7ab0ff108 + 0x10) != 0)) {
      do {
        cVar1 = FUN_7ff7a3398650(5,uVar6);
        if (cVar1 != '\0') goto LAB_7ff7a340d4eb;
        uVar7 = (int)uVar6 + 1;
        uVar6 = (ulonglong)uVar7;
      } while ((int)uVar7 < 2);
      cVar1 = FUN_7ff7a36309b0();
      if ((cVar1 == '\0') &&
         (((DAT_7ff7ab0ff108 == 0 || (*(int *)(DAT_7ff7ab0ff108 + 0x10) != 0)) &&
          (cVar1 = FUN_7ff7a33978b0(), uVar6 = uVar8, cVar1 != '\0')))) {
        do {
          iVar2 = FUN_7ff7a320dfd0(uVar6);
          if ((iVar2 != 0) && (DAT_7ff7a4d636f8 == '\0')) goto LAB_7ff7a340d4eb;
          uVar7 = (int)uVar6 + 1;
          uVar6 = (ulonglong)uVar7;
        } while ((int)uVar7 < 2);
        if (DAT_7ff7ab2938a8 != '\0') {
          piVar9 = &DAT_7ff7ab293af0;
          uVar6 = uVar8;
          uVar10 = uVar8;
          uVar11 = uVar8;
          do {
            iVar2 = piVar9[-0x8e];
            if ((iVar2 != 0) && (*piVar9 == 0)) {
              uVar5 = uVar8;
              if (0 < (longlong)uVar6) {
                do {
                  if ((&DAT_7ff7ab3306a0)[uVar5] == iVar2) goto LAB_7ff7a340d405;
                  uVar5 = uVar5 + 1;
                } while ((longlong)uVar5 < (longlong)uVar6);
              }
              uVar10 = (ulonglong)((int)uVar10 + 1);
              (&DAT_7ff7ab3306a0)[uVar6] = iVar2;
              uVar6 = uVar6 + 1;
LAB_7ff7a340d405:
              iVar2 = (int)uVar10;
              if (uVar6 == 100) break;
            }
            iVar2 = (int)uVar10;
            uVar7 = (int)uVar11 + 1;
            uVar11 = (ulonglong)uVar7;
            piVar9 = piVar9 + 0xba;
          } while (uVar7 < 400);
          if ((0 < iVar2) &&
             ((uVar3 = FUN_7ff7a3631500(), DAT_7ff7ab0ff108 == 0 ||
              (*(int *)(DAT_7ff7ab0ff108 + 0x10) != 0)))) {
            lVar4 = FUN_7ff7a33981b0(5,uVar3);
            cVar1 = FUN_7ff7a39c9650(lVar4);
            if ((cVar1 != '\0') && (cVar1 = FUN_7ff7a39c9710(lVar4), cVar1 != '\0')) {
              FUN_7ff7a339cf90(&DAT_7ff7ab2fa6e0);
              DAT_7ff7ab30b214 = 1;
              _DAT_7ff7ab30b210 = iVar2;
              if (0 < iVar2) {
                memcpy(&DAT_7ff7ab30b080,&DAT_7ff7ab3306a0,(longlong)iVar2 << 2);
              }
              FUN_7ff7a39c9700(lVar4,&DAT_7ff7ab2fa6e0);
              *(code **)(lVar4 + 0x30) = thunk_FUN_7ff7b51146a3;
              *(undefined **)(lVar4 + 0x40) = &DAT_7ff7a340b4c0;
              *(code **)(lVar4 + 0x38) = FUN_7ff7a340b4d0;
              FUN_7ff7a39c97e0(lVar4);
            }
          }
        }
      }
    }
  }
LAB_7ff7a340d4eb:
  FUN_7ff7a3398790(5);
  FUN_7ff7a3406c20();
  return;
}

