// image offset 0x13A605 address 7ff7a32ca605

bool FUN_7ff7a32ca570(undefined8 param_1,undefined8 param_2,undefined1 *param_3,char param_4,
                     undefined8 *param_5)

{
  undefined1 auVar1 [16];
  char cVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  int iVar5;
  undefined4 uVar6;
  longlong lVar7;
  undefined8 uVar8;
  ulonglong uVar9;
  longlong lVar10;
  
  *(undefined2 *)(param_3 + 0x28) = 0;
  *(undefined4 *)(param_3 + 0x2c) = 0;
  *(undefined8 *)(param_3 + 0x30) = 0;
  *(undefined4 *)(param_3 + 0x38) = 0;
  *(undefined4 *)(param_3 + 0x3c) = 0xffffffff;
  *(undefined4 *)(param_3 + 0xc) = 0xffffffff;
  *(undefined4 *)(param_3 + 8) = 0xffff;
  *(undefined8 *)(param_3 + 0x20) = 0;
  *(undefined4 *)(param_3 + 0x10) = 1;
  *(undefined4 *)(param_3 + 4) = 0xffffffff;
  *(undefined8 *)(param_3 + 0x18) = 0;
  if (param_5 != (undefined8 *)0x0) {
    *param_5 = 0;
    FUN_7ff7a340c970(param_5 + 1);
  }
  for (lVar7 = FUN_7ff7a340efe0(param_1,param_2); lVar7 != 0;
      lVar7 = FUN_7ff7a340f240(param_1,lVar7)) {
    cVar2 = FUN_7ff7a340fce0(lVar7);
    if (cVar2 == '\0') {
      uVar8 = FUN_7ff7a340f220(param_1,lVar7);
      iVar5 = FUN_7ff7a3b94f40(uVar8,&DAT_7ff7a3cd03f8);
      if (iVar5 == 0) {
        uVar6 = FUN_7ff7a340f170(param_1,lVar7);
        *(undefined4 *)(param_3 + 8) = uVar6;
      }
      else {
        iVar5 = FUN_7ff7a3b94f40(uVar8,&DAT_7ff7a3cc4b48);
        if (iVar5 == 0) {
          uVar8 = FUN_7ff7a340f710(param_1,lVar7);
          uVar6 = FUN_7ff7a32c9d50(uVar8);
          *(undefined4 *)(param_3 + 0xc) = uVar6;
        }
        else {
          iVar5 = FUN_7ff7a3b94f40(uVar8,"requiresClaim");
          if (iVar5 == 0) {
            uVar3 = FUN_7ff7a340efc0(lVar7);
            *param_3 = uVar3;
          }
          else {
            iVar5 = FUN_7ff7a3b94f40(uVar8,"progress");
            if (iVar5 == 0) {
              uVar4 = FUN_7ff7a340f750(param_1,lVar7);
              *(undefined2 *)(param_3 + 0x28) = uVar4;
            }
            else {
              iVar5 = FUN_7ff7a3b94f40(uVar8,"fulfilledTimes");
              if (((iVar5 == 0) || (iVar5 = FUN_7ff7a3b94f40(uVar8,"num_times"), iVar5 == 0)) ||
                 (iVar5 = FUN_7ff7a3b94f40(uVar8,"completionCount"), iVar5 == 0)) {
                uVar6 = FUN_7ff7a340f750(param_1,lVar7);
                *(undefined4 *)(param_3 + 0x2c) = uVar6;
              }
              else {
                iVar5 = FUN_7ff7a3b94f40(uVar8,"eventEndTimestamp");
                if (iVar5 == 0) {
                  uVar9 = FUN_7ff7a340f7b0(param_1,lVar7);
                  auVar1._8_8_ = 0;
                  auVar1._0_8_ = uVar9;
                  lVar10 = SUB168(ZEXT816(0x624dd2f1a9fbe77) * auVar1,8);
                  *(ulonglong *)(param_3 + 0x30) = (uVar9 - lVar10 >> 1) + lVar10 >> 9;
                }
                else if ((param_4 == '\0') ||
                        (iVar5 = FUN_7ff7a3b94f40(uVar8,&DAT_7ff7a3cd15b4), iVar5 != 0)) {
                  iVar5 = FUN_7ff7a3b94f40(uVar8,"completionTimestamp");
                  if (iVar5 == 0) {
                    uVar8 = FUN_7ff7a340f7b0(param_1,lVar7);
                    *(undefined8 *)(param_3 + 0x30) = uVar8;
                  }
                  else {
                    iVar5 = FUN_7ff7a3b94f40(uVar8,"progressTarget");
                    if ((iVar5 == 0) ||
                       (iVar5 = FUN_7ff7a3b94f40(uVar8,"globalProgressTarget"), iVar5 == 0)) {
                      iVar5 = FUN_7ff7a340f750(param_1,lVar7);
                      if (iVar5 != 0) {
                        *(int *)(param_3 + 0x10) = iVar5;
                      }
                    }
                    else {
                      iVar5 = FUN_7ff7a3b94f40(uVar8,"status");
                      if (iVar5 == 0) {
                        uVar8 = FUN_7ff7a340f710(param_1,lVar7);
                        uVar6 = FUN_7ff7a32c9c10(uVar8);
                        *(undefined4 *)(param_3 + 0x38) = uVar6;
                      }
                      else {
                        iVar5 = FUN_7ff7a3b94f40(uVar8,"successRewards");
                        if ((iVar5 == 0) && (param_5 != (undefined8 *)0x0)) {
                          FUN_7ff7a32ce610(param_1,lVar7,param_5);
                        }
                        else {
                          iVar5 = FUN_7ff7a3b94f40(uVar8,"usageTimeTarget");
                          if (iVar5 == 0) {
                            uVar6 = FUN_7ff7a340f170(param_1,lVar7);
                            *(undefined4 *)(param_3 + 4) = uVar6;
                          }
                          else {
                            iVar5 = FUN_7ff7a3b94f40(uVar8,"usageTimeRemaining");
                            if (iVar5 == 0) {
                              uVar6 = FUN_7ff7a340f170(param_1,lVar7);
                              *(undefined4 *)(param_3 + 0x3c) = uVar6;
                            }
                            else {
                              iVar5 = FUN_7ff7a3b94f40(uVar8,"activationTimestamp");
                              if ((iVar5 != 0) &&
                                 (iVar5 = FUN_7ff7a3b94f40(uVar8,"expirationTimestamp"), iVar5 == 0)
                                 ) {
                                uVar8 = FUN_7ff7a340f7b0(param_1,lVar7);
                                *(undefined8 *)(param_3 + 0x18) = uVar8;
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
                else {
                  uVar8 = FUN_7ff7a340f7b0(param_1,lVar7);
                  *(undefined8 *)(param_3 + 0x30) = uVar8;
                }
              }
            }
          }
        }
      }
    }
  }
  return *(int *)(param_3 + 0xc) != -1;
}

