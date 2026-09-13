// image offset 0x274CF0 address 7ff7a3404cf0

undefined8 FUN_7ff7a3404cf0(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  undefined8 uVar6;
  undefined8 local_res10;
  undefined4 local_res18;
  int iStackX_1c;
  
  FUN_7ff7a339d430(&local_res18);
  pcVar5 = (char *)FUN_7ff7a3261ba0(param_1,0x1e);
  if ((pcVar5 == (char *)0x0) || (iVar1 = atoi(pcVar5), iVar1 < 1)) goto LAB_7ff7a3404e70;
  iVar1 = FUN_7ff7a37e2360(param_1);
  if (iVar1 == 0) {
    iVar2 = FUN_7ff7a37e22d0(param_1);
LAB_7ff7a3404d7f:
    if (iVar2 == -1) goto LAB_7ff7a3404e70;
  }
  else {
    if (iVar1 != 1) {
      if (iVar1 == 2) {
        iVar2 = FUN_7ff7a37e22f0(param_1);
      }
      else if (iVar1 == 6) {
        iVar2 = FUN_7ff7a37e2250(param_1);
      }
      else {
        if (iVar1 != 7) goto LAB_7ff7a3404e70;
        iVar2 = FUN_7ff7a37e2080(param_1);
      }
      goto LAB_7ff7a3404d7f;
    }
    iVar2 = 0;
  }
  FUN_7ff7a38f34d0("mp/pawnValues.csv",&local_res10);
  uVar6 = FUN_7ff7a38fa3d0(&DAT_7ff7a3cc2f5c,iVar1);
  for (iVar3 = FUN_7ff7a38f3700(local_res10,0,uVar6); -1 < iVar3;
      iVar3 = FUN_7ff7a38f3910(local_res10,0,uVar6,iVar3 + -1)) {
    pcVar5 = (char *)FUN_7ff7a38f3510(local_res10,iVar3,1);
    if (((pcVar5 != (char *)0x0) && (*pcVar5 != '\0')) && (iVar4 = atoi(pcVar5), iVar4 == iVar2)) {
      iVar1 = FUN_7ff7a37e2330(param_1);
      if (((iVar1 != -1) &&
          (pcVar5 = (char *)FUN_7ff7a38f3510(local_res10,iVar3,iVar1 + 2), pcVar5 != (char *)0x0))
         && ((*pcVar5 != '\0' && (iVar1 = atoi(pcVar5), -1 < iVar1)))) {
        local_res18 = 6;
        iStackX_1c = iVar1;
      }
      break;
    }
    uVar6 = FUN_7ff7a38fa3d0(&DAT_7ff7a3cc2f5c,iVar1);
  }
LAB_7ff7a3404e70:
  return CONCAT44(iStackX_1c,local_res18);
}

