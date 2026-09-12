// image offset 0x118174FD address 7ff7b49a74fd

undefined8 FUN_7ff7b49a74fd(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  char cVar2;
  undefined8 uVar3;
  longlong unaff_RBP;
  undefined8 uVar4;
  undefined7 uVar5;

  uVar3 = CONCAT71((int7)((ulonglong)param_3 >> 8),0x6f);
  FUN_7ff7a3bfb930(unaff_RBP + -0x49,0x50,uVar3,0x400,0x1ffff);
  FUN_7ff7a3bfbb50(unaff_RBP + -0x49,*(longlong *)(unaff_RBP + 0x37) + 8);
  uVar4 = CONCAT71((int7)((ulonglong)uVar3 >> 8),1);
  uVar3 = (**(code **)(*(longlong *)(unaff_RBP + -0x49) + 8))(unaff_RBP + -0x49,4,uVar4);
  if ((char)uVar3 != '\0') {
    if (*(char *)(unaff_RBP + -0x29) != '\0') {
      *(int *)(unaff_RBP + -0x25) = *(int *)(unaff_RBP + -0x25) + -1;
    }
    LOCK();
    UNLOCK();
    return uVar3;
  }
  uVar5 = (undefined7)((ulonglong)uVar4 >> 8);
  uVar3 = (**(code **)(*(longlong *)(unaff_RBP + -0x49) + 8))(unaff_RBP + -0x49);
  if ((char)uVar3 != '\0') {
    LOCK();
    UNLOCK();
    return uVar3;
  }
  uVar3 = (**(code **)(*(longlong *)(unaff_RBP + -0x49) + 8))(unaff_RBP + -0x49,1,CONCAT71(uVar5,1))
  ;
  if ((char)uVar3 != '\0') {
    return uVar3;
  }
  cVar2 = (**(code **)(*(longlong *)(unaff_RBP + -0x49) + 8))(unaff_RBP + -0x49,4,1);
  iVar1 = *(int *)(unaff_RBP + 0x6f);
  if (cVar2 != '\0') {
    if (*(char *)(unaff_RBP + -0x29) != '\0') {
      *(int *)(unaff_RBP + -0x25) = *(int *)(unaff_RBP + -0x25) + -1;
    }
    if (*(char *)(unaff_RBP + -0x39) != '\0') {
      cVar2 = FUN_7ff7a3c07870(*(undefined8 *)(unaff_RBP + -0x31),iVar1);
      *(undefined1 *)(unaff_RBP + -0x39) = 1;
      if (cVar2 != '\0') goto LAB_7ff7a3361025;
    }
    *(undefined1 *)(unaff_RBP + -0x39) = 0;
  }
LAB_7ff7a3361025:
  if (iVar1 == 0) {
    uVar3 = (**(code **)(*(longlong *)(unaff_RBP + -0x49) + 8))(unaff_RBP + -0x49,4,1);
    return uVar3;
  }
  uVar3 = (**(code **)(*(longlong *)(unaff_RBP + -0x49) + 8))(unaff_RBP + -0x49,4,1);
  if ((char)uVar3 != '\0') {
    LOCK();
    UNLOCK();
    return uVar3;
  }
  return uVar3;
}
