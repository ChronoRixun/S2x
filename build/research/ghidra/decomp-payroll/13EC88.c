// image offset 0x13EC88 address 7ff7a32cec88

void FUN_7ff7a32cec20(int param_1,undefined8 param_2,undefined8 param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 local_28 [2];
  
  lVar4 = FUN_7ff7a3398270(0,param_1,0x72);
  if ((lVar4 != 0) &&
     (cVar1 = FUN_7ff7a340f430(param_2,param_3,"Achievements",local_28), cVar1 != '\0')) {
    for (lVar4 = FUN_7ff7a340efe0(param_2,local_28[0]); lVar4 != 0;
        lVar4 = FUN_7ff7a340f240(param_2,lVar4)) {
      iVar3 = -1;
      lVar5 = FUN_7ff7a340efe0(param_2,lVar4);
      if (lVar5 != 0) {
        do {
          cVar1 = FUN_7ff7a340fce0(lVar5);
          if (cVar1 == '\0') {
            uVar6 = FUN_7ff7a340f220(param_2,lVar5);
            iVar2 = FUN_7ff7a3b94f40(uVar6,&DAT_7ff7a3cd03f8);
            if (iVar2 == 0) {
LAB_7ff7a32cee9a:
              FUN_7ff7a340f170(param_2,lVar5);
            }
            else {
              iVar2 = FUN_7ff7a3b94f40(uVar6,&DAT_7ff7a3cc4b48);
              if (iVar2 == 0) {
                uVar6 = FUN_7ff7a340f710(param_2,lVar5);
                iVar3 = FUN_7ff7a32c9d50(uVar6);
              }
              else {
                iVar2 = FUN_7ff7a3b94f40(uVar6,"requiresClaim");
                if (iVar2 == 0) {
                  FUN_7ff7a340efc0(lVar5);
                }
                else {
                  iVar2 = FUN_7ff7a3b94f40(uVar6,"progress");
                  if ((((iVar2 == 0) ||
                       (iVar2 = FUN_7ff7a3b94f40(uVar6,"fulfilledTimes"), iVar2 == 0)) ||
                      (iVar2 = FUN_7ff7a3b94f40(uVar6,"num_times"), iVar2 == 0)) ||
                     (iVar2 = FUN_7ff7a3b94f40(uVar6,"completionCount"), iVar2 == 0)) {
LAB_7ff7a32cee8d:
                    FUN_7ff7a340f750(param_2,lVar5);
                  }
                  else {
                    iVar2 = FUN_7ff7a3b94f40(uVar6,"eventEndTimestamp");
                    if ((iVar2 == 0) ||
                       (iVar2 = FUN_7ff7a3b94f40(uVar6,"completionTimestamp"), iVar2 == 0)) {
LAB_7ff7a32cee80:
                      FUN_7ff7a340f7b0(param_2,lVar5);
                    }
                    else {
                      iVar2 = FUN_7ff7a3b94f40(uVar6,"progressTarget");
                      if ((iVar2 == 0) ||
                         (iVar2 = FUN_7ff7a3b94f40(uVar6,"globalProgressTarget"), iVar2 == 0))
                      goto LAB_7ff7a32cee8d;
                      iVar2 = FUN_7ff7a3b94f40(uVar6,"status");
                      if (iVar2 == 0) {
                        uVar6 = FUN_7ff7a340f710(param_2,lVar5);
                        FUN_7ff7a32c9c10(uVar6);
                      }
                      else {
                        FUN_7ff7a3b94f40(uVar6,"successRewards");
                        iVar2 = FUN_7ff7a3b94f40(uVar6,"usageTimeTarget");
                        if ((iVar2 == 0) ||
                           (iVar2 = FUN_7ff7a3b94f40(uVar6,"usageTimeRemaining"), iVar2 == 0))
                        goto LAB_7ff7a32cee9a;
                        iVar2 = FUN_7ff7a3b94f40(uVar6,"activationTimestamp");
                        if ((iVar2 != 0) &&
                           (iVar2 = FUN_7ff7a3b94f40(uVar6,"expirationTimestamp"), iVar2 == 0))
                        goto LAB_7ff7a32cee80;
                      }
                    }
                  }
                }
              }
            }
          }
          lVar5 = FUN_7ff7a340f240(param_2,lVar5);
        } while (lVar5 != 0);
        if (iVar3 != -1) {
          lVar5 = (longlong)param_1 * 0x1a0;
          if (99 < *(uint *)(&DAT_7ff7a8e28200 + lVar5)) {
            return;
          }
          *(int *)(&DAT_7ff7a8e28070 +
                  ((longlong)param_1 * 0x68 + (ulonglong)*(uint *)(&DAT_7ff7a8e28200 + lVar5)) * 4)
               = iVar3;
          *(int *)(&DAT_7ff7a8e28200 + lVar5) = *(int *)(&DAT_7ff7a8e28200 + lVar5) + 1;
        }
      }
    }
  }
  return;
}

