// image offset 0x3723B0 address 7ff7a35023b0

int FUN_7ff7a35023b0(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  longlong local_res18;
  
  iVar6 = 0;
  FUN_7ff7a38f34d0("mp/marketingcomms.csv",&local_res18);
  if (local_res18 == 0) {
    return 0;
  }
  iVar1 = FUN_7ff7a38f3550();
  iVar5 = iVar6;
  if (0 < iVar1) {
    do {
      pcVar4 = (char *)FUN_7ff7a38f3510(local_res18,iVar6,0);
      iVar2 = atoi(pcVar4);
      pcVar4 = (char *)FUN_7ff7a38f3510(local_res18,iVar6);
      iVar3 = atoi(pcVar4);
      if (param_1 == iVar2) {
        if ((-1 < param_2) && (param_2 < iVar3)) {
          return param_2 + iVar5;
        }
        return -1;
      }
      iVar5 = iVar5 + iVar3;
      iVar6 = iVar6 + 1;
    } while (iVar6 < iVar1);
  }
  return iVar5;
}

