// image offset 0x13AA96 address 7ff7a32caa96

bool FUN_7ff7a32ca910(undefined8 param_1,undefined8 param_2,undefined1 *param_3,undefined8 *param_4,
                     undefined4 *param_5)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 uVar4;
  longlong lVar5;
  undefined8 uVar6;
  longlong lVar7;
  
  *(undefined4 *)(param_3 + 0x28) = 0;
  *(undefined4 *)(param_3 + 0xc) = 0xffffffff;
  *(undefined4 *)(param_3 + 8) = 0xffff;
  *(undefined8 *)(param_3 + 0x20) = 0;
  *(undefined4 *)(param_3 + 0x10) = 1;
  *(undefined4 *)(param_3 + 4) = 0xffffffff;
  *(undefined8 *)(param_3 + 0x18) = 0;
  if (param_4 != (undefined8 *)0x0) {
    *param_4 = 0;
    FUN_7ff7a340c970(param_4 + 1);
  }
  if (param_5 != (undefined4 *)0x0) {
    *param_5 = 0xffffffff;
  }
  lVar5 = FUN_7ff7a340efe0(param_1,param_2);
  do {
    if (lVar5 == 0) {
      return *(int *)(param_3 + 0xc) != -1;
    }
    cVar1 = FUN_7ff7a340fce0(lVar5);
    if (cVar1 == '\0') {
      uVar6 = FUN_7ff7a340f220(param_1,lVar5);
      iVar3 = FUN_7ff7a3b94f40(uVar6,&DAT_7ff7a3cd03f8);
      if (iVar3 == 0) {
        uVar4 = FUN_7ff7a340f170(param_1,lVar5);
        *(undefined4 *)(param_3 + 8) = uVar4;
      }
      else {
        iVar3 = FUN_7ff7a3b94f40(uVar6,&DAT_7ff7a3cc4b48);
        if (iVar3 == 0) {
          uVar6 = FUN_7ff7a340f710(param_1,lVar5);
          uVar4 = FUN_7ff7a32c9d50(uVar6);
          *(undefined4 *)(param_3 + 0xc) = uVar4;
        }
        else {
          iVar3 = FUN_7ff7a3b94f40(uVar6,"progressTarget");
          if ((iVar3 == 0) || (iVar3 = FUN_7ff7a3b94f40(uVar6,"globalProgressTarget"), iVar3 == 0))
          {
            iVar3 = FUN_7ff7a340f750(param_1,lVar5);
            if (iVar3 != 0) {
              *(int *)(param_3 + 0x10) = iVar3;
            }
          }
          else {
            iVar3 = FUN_7ff7a3b94f40(uVar6,"requiresClaim");
            if (iVar3 == 0) {
              uVar2 = FUN_7ff7a340efc0(lVar5);
              *param_3 = uVar2;
            }
            else {
              iVar3 = FUN_7ff7a3b94f40(uVar6,"status");
              if (iVar3 == 0) {
                lVar7 = FUN_7ff7a340f710(param_1,lVar5);
                uVar4 = 0;
                if (lVar7 == 0) {
LAB_7ff7a32cab0f:
                  *(undefined4 *)(param_3 + 0x28) = uVar4;
                }
                else {
                  iVar3 = FUN_7ff7a3b94f40(lVar7,"available");
                  if (iVar3 == 0) {
                    *(undefined4 *)(param_3 + 0x28) = 1;
                  }
                  else {
                    iVar3 = FUN_7ff7a3b94f40(lVar7,"completed");
                    if (iVar3 == 0) {
                      *(undefined4 *)(param_3 + 0x28) = 4;
                    }
                    else {
                      iVar3 = FUN_7ff7a3b94f40(lVar7,"in_progress");
                      if (iVar3 != 0) {
                        iVar3 = FUN_7ff7a3b94f40(lVar7,"claimable");
                        uVar4 = 0;
                        if (iVar3 == 0) {
                          uVar4 = 3;
                        }
                        goto LAB_7ff7a32cab0f;
                      }
                      *(undefined4 *)(param_3 + 0x28) = 2;
                    }
                  }
                }
              }
              else {
                iVar3 = FUN_7ff7a3b94f40(uVar6,"successRewards");
                if ((iVar3 == 0) && (param_4 != (undefined8 *)0x0)) {
                  FUN_7ff7a32ce610(param_1,lVar5,param_4);
                }
                else {
                  iVar3 = FUN_7ff7a3b94f40(uVar6,"usageTimeTarget");
                  if (iVar3 == 0) {
                    uVar4 = FUN_7ff7a340f170(param_1,lVar5);
                    *(undefined4 *)(param_3 + 4) = uVar4;
                  }
                  else {
                    iVar3 = FUN_7ff7a3b94f40(uVar6,"expirationTimestamp");
                    if (iVar3 == 0) {
                      uVar6 = FUN_7ff7a340f7b0(param_1,lVar5);
                      *(undefined8 *)(param_3 + 0x18) = uVar6;
                    }
                    else {
                      iVar3 = FUN_7ff7a3b94f40(uVar6,"globalCounterID");
                      if ((iVar3 == 0) && (param_5 != (undefined4 *)0x0)) {
                        uVar4 = FUN_7ff7a340f170(param_1,lVar5);
                        *param_5 = uVar4;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    lVar5 = FUN_7ff7a340f240(param_1,lVar5);
  } while( true );
}

