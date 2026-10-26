
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _Z24gml_Object_ob_car_Step_2P9CInstanceS0_(undefined4 param_1,undefined4 param_2)

{
  int *piVar1;
  uint uVar2;
  undefined *puVar3;
  double *pdVar4;
  longdouble lVar5;
  double dVar6;
  undefined4 uStack_34;
  undefined4 uStack_30;
  int iStack_28;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined4 uStack_1c;
  undefined *puStack_18;
  double dStack_14;
  
  puVar3 = PTR__ZN13SYYStackTrace8s_pStartE_013c3e4c;
  puStack_20 = &UNK_00f85c4f;
  uStack_1c = 0;
  uStack_24 = *(undefined4 *)PTR__ZN13SYYStackTrace8s_pStartE_013c3e4c;
  *(undefined4 **)PTR__ZN13SYYStackTrace8s_pStartE_013c3e4c = &uStack_24;
  piVar1 = *(int **)PTR_g_pGlobal_013bf30c;
  if (piVar1[1] == 0) {
    pdVar4 = (double *)(**(code **)(*piVar1 + 8))(piVar1,0xaa);
  }
  else {
    pdVar4 = (double *)(piVar1[1] + 0xaa0);
  }
  iStack_28 = 0;
  uStack_30 = 0;
  uStack_34 = 0;
  uStack_1c = 3;
  uVar2 = *(uint *)((int)pdVar4 + 0xc);
  if ((uVar2 < 0xe) && ((0x2481U >> (uVar2 & 0x1f) & 1) != 0)) {
    if ((uVar2 & 0xffffff) == 0) {
      dVar6 = *pdVar4;
    }
    else {
      lVar5 = (longdouble)func_0x001785e0(pdVar4);
      dVar6 = (double)lVar5;
      dStack_14 = dVar6;
    }
    dVar6 = dVar6 + _UNK_00f75e90;
    if ((double)(-(ulonglong)(dVar6 < 0.0) & (_UNK_00f75960 ^ (ulonglong)dVar6) |
                ~-(ulonglong)(dVar6 < 0.0) & (ulonglong)dVar6) <=
        *(double *)PTR_g_GMLMathEpsilon_013c3408) {
      uStack_1c = 5;
      puStack_18 = PTR_gs_constArg0_5A1C4DBE_013bad8c;
      func_0x001818b0(param_1,param_2,&uStack_34,1,&puStack_18);
      if ((iStack_28 + 0xffffffU & 0xfffffc) == 0) {
        func_0x0017e680(&uStack_34);
      }
    }
    else if ((iStack_28 + 0xffffffU & 0xfffffc) == 0) {
      func_0x0017e680(&uStack_34);
    }
  }
  *(undefined4 *)puVar3 = uStack_24;
  return;
}

