// image offset 0x370500 address 7ff7a3500500

void FUN_7ff7a3500500(longlong param_1)

{
  char cVar1;
  int iVar2;
  
  cVar1 = FUN_7ff7a34a89f0();
  if (cVar1 != '\0') {
    FUN_7ff7a34737b0(param_1,"Store",&PTR_s_GetCategoryInfo_7ff7a3cf55f0);
    iVar2 = (int)(*(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4);
    if (0 < iVar2) {
      iVar2 = 1;
    }
    *(longlong *)(param_1 + 0x48) = *(longlong *)(param_1 + 0x48) + (longlong)iVar2 * -0x10;
  }
  return;
}

