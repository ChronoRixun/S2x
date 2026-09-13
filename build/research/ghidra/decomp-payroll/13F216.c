// image offset 0x13F216 address 7ff7a32cf216

void FUN_7ff7a32cf190(int param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  char cVar1;
  uint uVar2;
  longlong lVar3;
  int *piVar4;
  longlong lVar5;
  undefined8 local_68 [2];
  undefined1 local_58 [12];
  int local_4c;
  undefined4 local_1c;
  
  cVar1 = FUN_7ff7a340f430(param_2,param_3,"Achievements",local_68);
  if ((cVar1 != '\0') && (lVar3 = FUN_7ff7a3398270(0,param_1,0x85), lVar3 != 0)) {
    lVar3 = FUN_7ff7a39c9390(lVar3);
    cVar1 = FUN_7ff7a39c9000(lVar3 + 0xd0,param_4);
    if ((cVar1 != '\0') && (lVar3 = FUN_7ff7a340efe0(param_2,local_68[0]), lVar3 != 0)) {
      do {
        cVar1 = FUN_7ff7a32ca570(param_2,lVar3,local_58,0,0);
        if (cVar1 != '\0') {
          piVar4 = (int *)(&DAT_7ff7a923409c + (longlong)param_1 * 0x13890);
          uVar2 = 0;
          do {
            if (*piVar4 == local_4c) {
              if (((uVar2 != 0xffffffff) &&
                  (lVar5 = (longlong)(int)uVar2 * 0x40 + (longlong)param_1 * 0x13890,
                  lVar5 != -0x7ff7a9234090)) &&
                 ((*(int *)(&DAT_7ff7a9234098 + lVar5) == 4 ||
                  (*(int *)(&DAT_7ff7a9234098 + lVar5) == 0xb)))) {
                *(undefined4 *)(&DAT_7ff7a92340cc + lVar5) = local_1c;
              }
              break;
            }
            uVar2 = uVar2 + 1;
            piVar4 = piVar4 + 0x10;
          } while (uVar2 < 1000);
        }
        lVar3 = FUN_7ff7a340f240(param_2,lVar3);
      } while (lVar3 != 0);
    }
  }
  return;
}

