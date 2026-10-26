
undefined4 *
_Z22gml_Script_ease_linearP9CInstanceS0_R8YYRValueiPPS1_
          (undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4,
          undefined4 *param_5)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 *unaff_retaddr;
  int *piStack_60;
  undefined4 uStack_5c;
  undefined *puStack_58;
  uint uStack_54;
  undefined4 uStack_50;
  undefined *puStack_44;
  undefined *puStack_40;
  undefined4 uStack_3c;
  int iStack_34;
  undefined1 auStack_30 [8];
  undefined1 auStack_28 [4];
  int iStack_24;
  
  puStack_40 = &UNK_00f81280;
  uStack_3c = 0;
  puStack_58 = PTR__ZN13SYYStackTrace8s_pStartE_013c3e4c;
  puStack_44 = *(undefined **)PTR__ZN13SYYStackTrace8s_pStartE_013c3e4c;
  *(undefined ***)PTR__ZN13SYYStackTrace8s_pStartE_013c3e4c = &puStack_44;
  if ((param_3[3] + 0xffffff & 0xfffffc) == 0) {
    func_0x0017e680(param_3);
  }
  param_3[3] = 0;
  param_3[1] = 0;
  *param_3 = 0;
  uStack_3c = 2;
  puVar1 = (undefined4 *)*param_5;
  func_0x001751a0(&iStack_34,param_5[2]);
  func_0x00180610(auStack_28,&iStack_34,param_5[3]);
  func_0x00174f60(&uStack_5c,auStack_28,param_5[1]);
  uVar2 = uStack_54;
  if (&uStack_5c == unaff_retaddr) goto LAB_004e3ca6;
  puStack_44 = puStack_58;
  uVar5 = uStack_54 & 0xffffff;
  if (uVar5 == 2) {
    iVar3 = *piStack_60 + 1;
    *piStack_60 = iVar3;
    if ((unaff_retaddr[3] + 0xffffff & 0xfffffc) == 0) {
      func_0x0017e680(unaff_retaddr);
      iVar3 = *piStack_60;
    }
    *piStack_60 = iVar3 + -1;
  }
  else if ((unaff_retaddr[3] + 0xffffff & 0xfffffc) == 0) {
    func_0x0017e680(unaff_retaddr);
  }
  unaff_retaddr[3] = uVar2;
  unaff_retaddr[2] = puStack_44;
  switch(uVar5) {
  case 0:
  case 0xd:
    unaff_retaddr[1] = uStack_5c;
  case 3:
  case 7:
  case 0xe:
code_r0x004e3ca4:
    *unaff_retaddr = piStack_60;
    break;
  case 1:
    if (piStack_60 != (int *)0x0) {
      piStack_60[1] = piStack_60[1] + 1;
    }
    goto code_r0x004e3ca4;
  case 2:
    *unaff_retaddr = piStack_60;
    if ((piStack_60 != (int *)0x0) && (*piStack_60 = *piStack_60 + 1, piStack_60[2] == 0)) {
      piStack_60[2] = (int)unaff_retaddr;
    }
    break;
  case 6:
    *unaff_retaddr = piStack_60;
    if (piStack_60 != (int *)0x0) {
      uVar4 = func_0x00186420();
      func_0x00175800(uVar4,piStack_60);
    }
    break;
  case 10:
    *unaff_retaddr = piStack_60;
    unaff_retaddr[1] = uStack_5c;
  }
LAB_004e3ca6:
  if ((uStack_54 + 0xffffff & 0xfffffc) == 0) {
    func_0x0017e680(&piStack_60);
  }
  if ((iStack_24 + 0xffffffU & 0xfffffc) == 0) {
    func_0x0017e680(auStack_30);
  }
  if ((iStack_34 + 0xffffffU & 0xfffffc) == 0) {
    func_0x0017e680(&puStack_40);
  }
  *puVar1 = uStack_50;
  return unaff_retaddr;
}

