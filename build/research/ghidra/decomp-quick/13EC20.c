// image offset 0x13EC20 address 7ff7a32cec20

void FUN_7ff7a32cec20(int param_1,undefined8 param_2,undefined8 param_3)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  longlong lVar7;
  undefined8 uVar8;
  undefined8 auStack_28 [2];

  lVar6 = FUN_7ff7a3398270(0,param_1,0x72);
  if ((lVar6 != 0) &&
     (cVar3 = FUN_7ff7a340f430(param_2,param_3,&UNK_7ff7a3cd1388,auStack_28), cVar3 != '\0')) {
    for (lVar6 = FUN_7ff7a340efe0(param_2,auStack_28[0]); lVar6 != 0;
        lVar6 = FUN_7ff7a340f240(param_2,lVar6)) {
      iVar5 = -1;
      lVar7 = FUN_7ff7a340efe0(param_2,lVar6);
      if (lVar7 != 0) {
        do {
          cVar3 = func_0x7ff7a340fce0(lVar7);
          if (cVar3 == '\0') {
            uVar8 = func_0x7ff7a340f220(param_2,lVar7);
            iVar4 = func_0x7ff7a3b94f40(uVar8,&UNK_7ff7a3cd03f8);
            if (iVar4 == 0) {
code_r0x7ff7a32cee9a:
              FUN_7ff7a340f170(param_2,lVar7);
            }
            else {
              iVar4 = func_0x7ff7a3b94f40(uVar8,&UNK_7ff7a3cc4b48);
              if (iVar4 == 0) {
                uVar8 = func_0x7ff7a340f710(param_2,lVar7);
                iVar5 = FUN_7ff7a32c9d50(uVar8);
              }
              else {
                iVar4 = func_0x7ff7a3b94f40(uVar8,&UNK_7ff7a3cd11e0);
                if (iVar4 == 0) {
                  func_0x7ff7a340efc0(lVar7);
                }
                else {
                  iVar4 = func_0x7ff7a3b94f40(uVar8,&UNK_7ff7a3cd07e8);
                  if ((((iVar4 == 0) ||
                       (iVar4 = func_0x7ff7a3b94f40(uVar8,&UNK_7ff7a3cd1570), iVar4 == 0)) ||
                      (iVar4 = func_0x7ff7a3b94f40(uVar8,&UNK_7ff7a3cd1580), iVar4 == 0)) ||
                     (iVar4 = func_0x7ff7a3b94f40(uVar8,&UNK_7ff7a3cd1590), iVar4 == 0)) {
code_r0x7ff7a32cee8d:
                    FUN_7ff7a340f750(param_2,lVar7);
                  }
                  else {
                    iVar4 = func_0x7ff7a3b94f40(uVar8,&UNK_7ff7a3cd15a0);
                    if ((iVar4 == 0) ||
                       (iVar4 = func_0x7ff7a3b94f40(uVar8,&UNK_7ff7a3cd15c0), iVar4 == 0)) {
code_r0x7ff7a32cee80:
                      func_0x7ff7a340f7b0(param_2,lVar7);
                    }
                    else {
                      iVar4 = func_0x7ff7a3b94f40(uVar8,&UNK_7ff7a3cd11b8);
                      if ((iVar4 == 0) ||
                         (iVar4 = func_0x7ff7a3b94f40(uVar8,&UNK_7ff7a3cd11c8), iVar4 == 0))
                      goto code_r0x7ff7a32cee8d;
                      iVar4 = func_0x7ff7a3b94f40(uVar8,&UNK_7ff7a3cd0400);
                      if (iVar4 == 0) {
                        uVar8 = func_0x7ff7a340f710(param_2,lVar7);
                        FUN_7ff7a32c9c10(uVar8);
                      }
                      else {
                        func_0x7ff7a3b94f40(uVar8,&UNK_7ff7a3cd11f0);
                        iVar4 = func_0x7ff7a3b94f40(uVar8,&UNK_7ff7a3cd1200);
                        if ((iVar4 == 0) ||
                           (iVar4 = func_0x7ff7a3b94f40(uVar8,&UNK_7ff7a3cd15d8), iVar4 == 0))
                        goto code_r0x7ff7a32cee9a;
                        iVar4 = func_0x7ff7a3b94f40(uVar8,&UNK_7ff7a3cd15f0);
                        if ((iVar4 != 0) &&
                           (iVar4 = func_0x7ff7a3b94f40(uVar8,&UNK_7ff7a3cd0408), iVar4 == 0))
                        goto code_r0x7ff7a32cee80;
                      }
                    }
                  }
                }
              }
            }
          }
          lVar7 = FUN_7ff7a340f240(param_2,lVar7);
        } while (lVar7 != 0);
        if (iVar5 != -1) {
          lVar7 = (longlong)param_1 * 0x1a0;
          uVar2 = *(uint *)(lVar7 + 0x7ff7a8e28200);
          if (99 < uVar2) {
            return;
          }
          *(int *)(((longlong)param_1 * 0x68 + (ulonglong)uVar2) * 4 + 0x7ff7a8e28070) = iVar5;
          piVar1 = (int *)(lVar7 + 0x7ff7a8e28200);
          *piVar1 = *piVar1 + 1;
        }
      }
    }
  }
  return;
}
