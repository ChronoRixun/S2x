// image offset 0xD3720 address 7ff7a3263720

void FUN_7ff7a3263720(int param_1)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  char *pcVar7;
  undefined8 uVar8;
  longlong lVar9;
  int iVar10;
  undefined8 local_res10;
  undefined1 local_58 [48];

  FUN_7ff7a38f34d0("mp/statstable.csv",&local_res10);
  iVar3 = FUN_7ff7a38f3550(local_res10);
  iVar10 = 0;
  if (0 < iVar3) {
    do {
      pcVar7 = (char *)FUN_7ff7a38f3510(local_res10,iVar10,6);
      if ((pcVar7 != (char *)0x0) && (*pcVar7 != '\0')) {
        uVar8 = FUN_7ff7a38f3510(local_res10,iVar10,0x12);
        iVar4 = FUN_7ff7a37e23d0(uVar8);
        if ((iVar4 != 0) &&
           (iVar5 = FUN_7ff7a325f390(param_1),
           (&DAT_7ff7a4cc2868)[(longlong)iVar5 * 0x15d70 + (longlong)param_1 * 0x41920] != '\0')) {
          uVar6 = FUN_7ff7a325f390(param_1);
          FUN_7ff7a331dcf0(local_58,param_1,uVar6,0,1);
          lVar9 = FUN_7ff7a3409220(param_1,iVar4);
          pcVar7 = (char *)FUN_7ff7a3404960(iVar4);
          iVar4 = 0;
          if (pcVar7 != (char *)0x0) {
            cVar2 = *pcVar7;
            pcVar1 = pcVar7;
            while (cVar2 != '\0') {
              pcVar1 = pcVar1 + 1;
              iVar4 = iVar4 * 0x1f + (int)cVar2;
              cVar2 = *pcVar1;
            }
          }
          cVar2 = FUN_7ff7a37e4000(iVar4,local_58,0);
          if ((bool)cVar2 != 0 < lVar9) {
            iVar4 = 0;
            if (pcVar7 != (char *)0x0) {
              cVar2 = *pcVar7;
              while (cVar2 != '\0') {
                pcVar7 = pcVar7 + 1;
                iVar4 = iVar4 * 0x1f + (int)cVar2;
                cVar2 = *pcVar7;
              }
            }
            FUN_7ff7a37e4480(iVar4,0 < lVar9,local_58,0,0);
          }
        }
      }
      iVar10 = iVar10 + 1;
    } while (iVar10 < iVar3);
  }
  return;
}
