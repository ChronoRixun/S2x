// image offset 0x13A330 address 7ff7a32ca330

void FUN_7ff7a32ca330(undefined4 param_1,undefined8 param_2,undefined8 param_3)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  int iVar5;
  longlong lVar6;
  longlong lVar7;
  undefined8 uVar8;
  uint uVar9;
  ulonglong uVar10;
  uint uVar11;
  undefined4 auStack_28 [2];
  undefined8 uStack_20;

  cVar4 = FUN_7ff7a340f430(param_2,param_3,&UNK_7ff7a3cd1220,&uStack_20);
  if (cVar4 != '\0') {
    bVar3 = false;
    bVar2 = false;
    lVar6 = FUN_7ff7a340efe0(param_2,uStack_20);
    if (lVar6 != 0) {
      do {
        cVar4 = func_0x7ff7a340fce0(lVar6);
        if ((cVar4 == '\0') && (lVar7 = func_0x7ff7a340f220(param_2,lVar6), lVar7 != 0)) {
          iVar5 = atoi(lVar7);
          uVar8 = func_0x7ff7a340f1e0(param_2,lVar6);
          bVar1 = false;
          uVar10 = 0;
          uVar11 = uRam00007ff7a8e28684;
          if (uRam00007ff7a8e28684 != 0) {
            do {
              if (*(int *)(uVar10 * 0x40 + 0x7ff7a8e28418) == iVar5) {
                *(undefined8 *)(uVar10 * 0x40 + 0x7ff7a8e28420) = uVar8;
                bVar1 = true;
                *(undefined1 *)(uVar10 + 0x7ff7a8e28678) = 1;
                uVar11 = uRam00007ff7a8e28684;
              }
              uVar9 = (int)uVar10 + 1;
              uVar10 = (ulonglong)uVar9;
            } while (uVar9 < uVar11);
            bVar2 = bVar3;
            if (bVar1) {
              bVar3 = true;
              bVar2 = true;
            }
          }
        }
        lVar6 = FUN_7ff7a340f240(param_2,lVar6);
      } while (lVar6 != 0);
      if (((bVar2) && (cVar4 = FUN_7ff7a3630d90(param_1,auStack_28), cVar4 != '\0')) &&
         (cVar4 = FUN_7ff7a324d020(auStack_28[0],&UNK_7ff7a3cd06a8,uRam00007ff7a4d63d08),
         cVar4 != '\0')) {
        FUN_7ff7a325c620(&UNK_7ff7a3cd06c0,10,uRam00007ff7a4d63d08);
        FUN_7ff7a325c3e0(&UNK_7ff7a3cc50e0,1,uRam00007ff7a4d63d08);
        FUN_7ff7a324e7e0(uRam00007ff7a4d63d08);
      }
    }
  }
  return;
}
