
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _Z24gml_Object_ob_car_Step_1P9CInstanceS0_(int *param_1,int *param_2)

{
  int *piVar1;
  double *pdVar2;
  uint uVar3;
  code *pcVar4;
  char cVar5;
  int iVar6;
  int *piVar7;
  int *piVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  longdouble lVar15;
  double dVar16;
  undefined8 uVar17;
  double dVar18;
  int *unaff_retaddr;
  int aiStack_168 [6];
  undefined8 uStack_150;
  int *piStack_148;
  undefined8 uStack_144;
  int **ppiStack_13c;
  int aiStack_138 [4];
  undefined *puStack_128;
  int aiStack_124 [5];
  double *apdStack_110 [2];
  int iStack_108;
  undefined *apuStack_104 [3];
  undefined8 uStack_f8;
  int aiStack_f0 [7];
  int *piStack_d4;
  int iStack_d0;
  undefined4 uStack_cc;
  double adStack_c8 [2];
  uint auStack_b4 [5];
  uint auStack_a0 [8];
  undefined8 uStack_80;
  uint uStack_74;
  double dStack_28;
  double dStack_20;
  
  puStack_128 = &UNK_00f85c70;
  aiStack_124[0] = 0;
  piStack_d4 = (int *)PTR__ZN13SYYStackTrace8s_pStartE_013c3e4c;
  aiStack_138[3] = *(int *)PTR__ZN13SYYStackTrace8s_pStartE_013c3e4c;
  *(int **)PTR__ZN13SYYStackTrace8s_pStartE_013c3e4c = aiStack_138 + 3;
  piVar8 = *(int **)PTR_g_pGlobal_013bf30c;
  if (piVar8[1] == 0) {
    piStack_148 = (int *)0xa2;
    uStack_150 = (double)CONCAT44(piVar8,0x5c00d7);
    aiStack_f0[1] = (**(code **)(*piVar8 + 8))();
  }
  else {
    aiStack_f0[1] = piVar8[1] + 0xa20;
  }
  apdStack_110[0] = (double *)0x0;
  aiStack_124[3] = 0;
  aiStack_124[2] = 0;
  aiStack_f0[6] = 0;
  aiStack_f0[4] = 0;
  aiStack_f0[3] = 0;
  aiStack_124[0] = 3;
  iVar6 = param_1[1];
  if (iVar6 == 0) {
    piStack_148 = (int *)0x2d1;
    uStack_150 = (double)CONCAT44(param_1,0x5c0143);
    iVar10 = (**(code **)(*param_1 + 8))();
    if (param_1[1] == 0) {
      piStack_148 = (int *)0x7f7;
      uStack_150 = (double)CONCAT44(param_1,0x5c0166);
      piStack_148 = (int *)(**(code **)(*param_1 + 8))();
    }
    else {
      piStack_148 = (int *)(param_1[1] + 0x7f70);
    }
  }
  else {
    iVar10 = iVar6 + 0x2d10;
    piStack_148 = (int *)(iVar6 + 0x7f70);
  }
  apdStack_110[1] = (double *)PTR_g_GMLMathEpsilon_013c3408;
  uStack_144 = *(undefined8 *)PTR_g_GMLMathEpsilon_013c3408;
  uStack_150._0_4_ = (int *)0x5c0186;
  uStack_150._4_4_ = iVar10;
  iVar6 = func_0x00174b50();
  piVar7 = (int *)((int)&uStack_150 + 4);
  piVar8 = param_1;
  if (iVar6 != 0) {
    aiStack_124[0] = 5;
    iVar6 = param_1[1];
    if (iVar6 == 0) {
      piStack_148 = (int *)0x2d1;
      uStack_150 = (double)CONCAT44(param_1,0x5c01c4);
      piVar7 = (int *)(**(code **)(*param_1 + 8))();
      if (param_1[1] == 0) {
        piStack_148 = (int *)0x7f7;
        uStack_150 = (double)CONCAT44(param_1,0x5c01e7);
        iVar6 = (**(code **)(*param_1 + 8))();
      }
      else {
        iVar6 = param_1[1] + 0x7f70;
      }
    }
    else {
      piVar7 = (int *)(iVar6 + 0x2d10);
      iVar6 = iVar6 + 0x7f70;
    }
    uStack_144 = CONCAT44(uStack_144._4_4_,iVar6);
    iVar6 = (int)&uStack_80 + 4;
    uStack_150._0_4_ = (int *)0x5c01fe;
    piStack_148 = piVar7;
    uStack_150._4_4_ = iVar6;
    func_0x0017d460();
    piVar7 = (int *)&uStack_150;
    if ((uStack_74 & 0xffffff) != 0) {
      uStack_150 = (double)CONCAT44(uStack_150._4_4_,iVar6);
      lVar15 = (longdouble)func_0x001785e0();
      uStack_80 = (double)lVar15;
      dStack_20 = uStack_80;
    }
    uStack_150 = uStack_80;
    lVar15 = (longdouble)func_0x00186910();
    dStack_28 = (double)lVar15;
    dVar16 = dStack_28;
    dVar18 = *apdStack_110[0];
    if ((uStack_74 + 0xffffff & 0xfffffc) == 0) {
      uStack_150 = (double)CONCAT44(uStack_150._4_4_,iVar6);
      uStack_f8 = dStack_28;
      adStack_c8[0] = *apdStack_110[0];
      func_0x0017e680();
      dVar16 = uStack_f8;
      dVar18 = adStack_c8[0];
    }
    if (dVar16 + _UNK_00f85c68 <= dVar18) {
      puStack_128 = (undefined *)0xb;
      iVar6 = param_1[1];
      if (iVar6 == 0) {
        uStack_150 = (double)CONCAT44(0x7f7,param_1);
        iVar10 = (**(code **)(*param_1 + 8))();
        if (param_1[1] == 0) {
          uStack_150 = (double)CONCAT44(0x2d1,param_1);
          uStack_150._0_4_ = (int *)(**(code **)(*param_1 + 8))();
        }
        else {
          uStack_150._0_4_ = (int *)(param_1[1] + 0x2d10);
        }
      }
      else {
        iVar10 = iVar6 + 0x7f70;
        uStack_150._0_4_ = (int *)(iVar6 + 0x2d10);
      }
      uStack_150._4_4_ = iVar10;
      func_0x00176b20();
    }
    else {
      puStack_128 = (undefined *)0x7;
      iStack_108 = param_1[1];
      if (iStack_108 == 0) {
        uStack_150 = (double)CONCAT44(0x2d1,param_1);
        piVar8 = (int *)(**(code **)(*param_1 + 8))();
        iStack_108 = param_1[1];
        if (iStack_108 != 0) goto LAB_005c02f4;
        uStack_150 = (double)CONCAT44(0x7f7,param_1);
        iStack_d0 = (**(code **)(*param_1 + 8))();
        if (param_1[1] == 0) {
          uStack_150 = (double)CONCAT44(0x706,param_1);
          iStack_108 = (**(code **)(*param_1 + 8))();
        }
        else {
          iStack_108 = param_1[1] + 0x7060;
        }
      }
      else {
        piVar8 = (int *)(iStack_108 + 0x2d10);
LAB_005c02f4:
        iStack_d0 = iStack_108 + 0x7f70;
        iStack_108 = iStack_108 + 0x7060;
      }
      apuStack_104[0] = PTR_gs_constArg0_336D7683_013c49f0;
      apuStack_104[1] = PTR_gs_constArg1_336D7683_013bc910;
      ppiStack_13c = (int **)&iStack_108;
      piStack_148 = aiStack_f0 + 2;
      uStack_150 = (double)CONCAT44(param_1,unaff_retaddr);
      uStack_144 = CONCAT44(*(undefined4 *)(PTR_g_FUNC_clamp_013bcce4 + 4),3);
      piStack_d4 = piVar8;
      uStack_cc = func_0x001842c0();
      ppiStack_13c = &piStack_d4;
      piStack_148 = aiStack_138 + 6;
      uStack_150 = (double)CONCAT44(param_1,unaff_retaddr);
      uStack_144 = CONCAT44(*(undefined4 *)(PTR_g_FUNC_lerp_013c35bc + 4),3);
      uStack_150._4_4_ = func_0x001842c0();
      uStack_150._0_4_ = piVar8;
      func_0x00176b20();
      if ((aiStack_124[4] + 0xffffffU & 0xfffffc) == 0) {
        uStack_150._0_4_ = aiStack_138 + 6;
        func_0x0017e680();
      }
      aiStack_124[3] = 0;
      aiStack_124[4] = 5;
      aiStack_124[1] = 0;
      if ((aiStack_f0[5] + 0xffffffU & 0xfffffc) == 0) {
        uStack_150._0_4_ = aiStack_f0 + 2;
        func_0x0017e680();
      }
      aiStack_f0[4] = 0;
      aiStack_f0[5] = 5;
      aiStack_f0[2] = 0;
      piVar7 = (int *)&uStack_150;
      piVar8 = unaff_retaddr;
      param_2 = param_1;
    }
  }
  piVar7[10] = 0x22;
  iVar6 = piVar8[1];
  if (iVar6 == 0) {
    pcVar4 = *(code **)(*piVar8 + 8);
    *piVar7 = (int)piVar8;
    piVar7[1] = 0x2eb;
    piVar7[-1] = 0x5c04ba;
    iVar10 = (*pcVar4)();
    if (piVar8[1] == 0) {
      pcVar4 = *(code **)(*piVar8 + 8);
      *piVar7 = (int)piVar8;
      piVar7[1] = 0x580;
      piVar7[-1] = 0x5c04dd;
      iVar6 = (*pcVar4)();
    }
    else {
      iVar6 = piVar8[1] + 0x5800;
    }
  }
  else {
    iVar10 = iVar6 + 0x2eb0;
    iVar6 = iVar6 + 0x5800;
  }
  *(undefined8 *)(piVar7 + 2) = *(undefined8 *)piVar7[0x10];
  piVar7[1] = iVar6;
  *piVar7 = iVar10;
  piVar7[-1] = 0x5c04f7;
  iVar6 = func_0x00174b50();
  piVar12 = piVar7;
  if (iVar6 != 0) {
    piVar7[10] = 0x24;
    iVar6 = piVar8[1];
    if (iVar6 == 0) {
      pcVar4 = *(code **)(*piVar8 + 8);
      *piVar7 = (int)piVar8;
      piVar7[1] = 0x2eb;
      piVar7[-1] = 0x5c052e;
      iVar10 = (*pcVar4)();
      if (piVar8[1] == 0) {
        pcVar4 = *(code **)(*piVar8 + 8);
        *piVar7 = (int)piVar8;
        piVar7[1] = 0x580;
        piVar7[-1] = 0x5c0551;
        iVar6 = (*pcVar4)();
      }
      else {
        iVar6 = piVar8[1] + 0x5800;
      }
    }
    else {
      iVar10 = iVar6 + 0x2eb0;
      iVar6 = iVar6 + 0x5800;
    }
    piVar7[2] = iVar6;
    piVar7[1] = iVar10;
    piVar1 = piVar7 + 0x30;
    *piVar7 = (int)piVar1;
    piVar7[-1] = 0x5c0568;
    func_0x0017d460();
    piVar12 = piVar7 + -1;
    if ((piVar7[0x32] & 0xffffffU) == 0) {
      uVar17 = *(undefined8 *)(piVar7 + 0x2f);
    }
    else {
      piVar7[-1] = (int)piVar1;
      piVar7[-2] = 0x5c0580;
      lVar15 = (longdouble)func_0x001785e0();
      *(double *)(piVar7 + 0x47) = (double)lVar15;
      uVar17 = *(undefined8 *)(piVar7 + 0x47);
    }
    *(undefined8 *)(piVar7 + -1) = uVar17;
    piVar7[-2] = 0x5c05a5;
    lVar15 = (longdouble)func_0x00186910();
    *(double *)(piVar7 + 0x45) = (double)lVar15;
    dVar16 = *(double *)(piVar7 + 0x45);
    dVar18 = *(double *)piVar7[0xf];
    if ((piVar7[0x32] + 0xffffffU & 0xfffffc) == 0) {
      piVar7[-1] = (int)piVar1;
      *(double *)(piVar7 + 0x15) = dVar16;
      *(double *)(piVar7 + 0x21) = dVar18;
      piVar7[-2] = 0x5c05e7;
      func_0x0017e680();
      dVar18 = *(double *)(piVar7 + 0x21);
      dVar16 = *(double *)(piVar7 + 0x15);
    }
    if (dVar16 + _UNK_00f85c68 <= dVar18) {
      piVar7[9] = 0x2a;
      iVar6 = piVar8[1];
      if (iVar6 == 0) {
        pcVar4 = *(code **)(*piVar8 + 8);
        piVar7[-1] = (int)piVar8;
        *piVar7 = 0x580;
        piVar7[-2] = 0x5c0705;
        iVar10 = (*pcVar4)();
        if (piVar8[1] == 0) {
          pcVar4 = *(code **)(*piVar8 + 8);
          piVar7[-1] = (int)piVar8;
          *piVar7 = 0x2eb;
          piVar7[-2] = 0x5c0754;
          iVar6 = (*pcVar4)();
        }
        else {
          iVar6 = piVar8[1] + 0x2eb0;
        }
      }
      else {
        iVar10 = iVar6 + 0x5800;
        iVar6 = iVar6 + 0x2eb0;
      }
      *piVar7 = iVar10;
      piVar7[-1] = iVar6;
      piVar7[-2] = 0x5c0760;
      func_0x00176b20();
    }
    else {
      piVar7[9] = 0x26;
      iVar6 = piVar8[1];
      if (iVar6 == 0) {
        pcVar4 = *(code **)(*piVar8 + 8);
        piVar7[-1] = (int)piVar8;
        *piVar7 = 0x2eb;
        piVar7[-2] = 0x5c0651;
        iVar10 = (*pcVar4)();
        iVar6 = piVar8[1];
        if (iVar6 != 0) goto LAB_005c065e;
        pcVar4 = *(code **)(*piVar8 + 8);
        piVar7[-1] = (int)piVar8;
        *piVar7 = 0x580;
        piVar7[-2] = 0x5c0728;
        iVar11 = (*pcVar4)();
        if (piVar8[1] == 0) {
          pcVar4 = *(code **)(*piVar8 + 8);
          piVar7[-1] = (int)piVar8;
          *piVar7 = 0x719;
          piVar7[-2] = 0x5c1305;
          iVar6 = (*pcVar4)();
        }
        else {
          iVar6 = piVar8[1] + 0x7190;
        }
      }
      else {
        iVar10 = iVar6 + 0x2eb0;
LAB_005c065e:
        iVar11 = iVar6 + 0x5800;
        iVar6 = iVar6 + 0x7190;
      }
      piVar7[0x11] = iVar10;
      piVar7[0x12] = iVar11;
      piVar7[0x13] = iVar6;
      iVar6 = *(int *)(PTR_g_FUNC_lerp_013c35bc + 4);
      piVar7[4] = (int)(piVar7 + 0x11);
      piVar7[3] = iVar6;
      piVar7[1] = (int)(piVar7 + 0xb);
      *piVar7 = (int)param_2;
      piVar7[-1] = piVar7[0x53];
      piVar7[2] = 3;
      piVar7[-2] = 0x5c06ad;
      uVar9 = func_0x001842c0();
      *piVar7 = uVar9;
      piVar7[-1] = iVar10;
      piVar7[-2] = 0x5c06b9;
      func_0x00176b20();
      if ((piVar7[0xe] + 0xffffffU & 0xfffffc) == 0) {
        piVar7[-1] = (int)(piVar7 + 0xb);
        piVar7[-2] = 0x5c06d1;
        func_0x0017e680();
      }
      piVar7[0xd] = 0;
      piVar7[0xe] = 5;
      piVar7[0xb] = 0;
      piVar8 = (int *)piVar7[0x53];
      piVar12 = piVar7 + -1;
    }
  }
  piVar12[10] = 0x2e;
  *piVar12 = 0x27;
  piVar12[-1] = 0x5c0774;
  cVar5 = func_0x00175340();
  pdVar2 = (double *)piVar12[0x18];
  if (cVar5 == '\0') {
    uVar3 = *(uint *)((int)pdVar2 + 0xc);
    if ((uVar3 < 0xe) && ((0x2481U >> (uVar3 & 0x1f) & 1) != 0)) {
      if ((uVar3 & 0xffffff) == 0) {
        dVar16 = *pdVar2;
      }
      else {
        *piVar12 = (int)pdVar2;
        piVar12[-1] = 0x5c07a1;
        lVar15 = (longdouble)func_0x001785e0();
        *(double *)(piVar12 + 0x44) = (double)lVar15;
        dVar16 = *(double *)(piVar12 + 0x44);
      }
      dVar16 = dVar16 + _UNK_00f75e90;
      if ((double)(-(ulonglong)(dVar16 < 0.0) & (_UNK_00f75960 ^ (ulonglong)dVar16) |
                  ~-(ulonglong)(dVar16 < 0.0) & (ulonglong)dVar16) <= *(double *)piVar12[0x10])
      goto LAB_005c080d;
    }
    piVar12[10] = 0x35;
    if (piVar8[1] == 0) {
      pcVar4 = *(code **)(*piVar8 + 8);
      *piVar12 = (int)piVar8;
      piVar12[1] = 0x3a8;
      piVar12[-1] = 0x5c086b;
      puVar13 = (undefined4 *)(*pcVar4)();
    }
    else {
      puVar13 = (undefined4 *)(piVar8[1] + 0x3a80);
    }
    if ((puVar13[3] + 0xffffff & 0xfffffc) == 0) {
      *piVar12 = (int)puVar13;
      piVar12[-1] = 0x5c0884;
      func_0x0017e680();
    }
    puVar13[3] = 0;
    puVar13[1] = 0;
    *puVar13 = 0;
    piVar12[10] = 0x36;
    if (piVar8[1] == 0) {
      pcVar4 = *(code **)(*piVar8 + 8);
      *piVar12 = (int)piVar8;
      piVar12[1] = 0x71a;
      piVar12[-1] = 0x5c08c2;
      puVar13 = (undefined4 *)(*pcVar4)();
    }
    else {
      puVar13 = (undefined4 *)(piVar8[1] + 0x71a0);
    }
    if ((puVar13[3] + 0xffffff & 0xfffffc) == 0) {
      *piVar12 = (int)puVar13;
      piVar12[-1] = 0x5c08db;
      func_0x0017e680();
    }
    puVar13[3] = 0;
    puVar13[1] = 0x3fb99999;
    *puVar13 = 0x9999999a;
    piVar7 = piVar12;
  }
  else {
LAB_005c080d:
    piVar12[10] = 0x30;
    iVar6 = piVar8[1];
    if (iVar6 == 0) {
      pcVar4 = *(code **)(*piVar8 + 8);
      *piVar12 = (int)piVar8;
      piVar12[1] = 0x22e;
      piVar12[-1] = 0x5c0840;
      iVar10 = (*pcVar4)();
      if (piVar8[1] == 0) {
        pcVar4 = *(code **)(*piVar8 + 8);
        *piVar12 = (int)piVar8;
        piVar12[1] = 0x71a;
        piVar12[-1] = 0x5c0907;
        iVar6 = (*pcVar4)();
      }
      else {
        iVar6 = piVar8[1] + 0x71a0;
      }
    }
    else {
      iVar10 = iVar6 + 0x22e0;
      iVar6 = iVar6 + 0x71a0;
    }
    piVar12[1] = iVar10;
    puVar13 = piVar12 + 0x12;
    *piVar12 = (int)puVar13;
    piVar12[3] = 0x3f46f006;
    piVar12[2] = 0x8db8bac7;
    piVar12[-1] = 0x5c0929;
    func_0x00188630();
    piVar7 = piVar12 + -1;
    piVar12[0x1e] = (int)puVar13;
    piVar12[0x1f] = (int)PTR_gs_constArg2_336D7683_013ba97c;
    piVar12[0x20] = (int)PTR_gs_constArg3_336D7683_013bedd8;
    uVar9 = *(undefined4 *)(PTR_g_FUNC_clamp_013bcce4 + 4);
    piVar12[4] = (int)(piVar12 + 0x1e);
    piVar12[3] = uVar9;
    piVar12[1] = (int)(piVar12 + 0xb);
    *piVar12 = piVar12[0x54];
    piVar12[-1] = piVar12[0x53];
    piVar12[2] = 3;
    piVar12[-2] = 0x5c0989;
    uVar9 = func_0x001842c0();
    *piVar12 = uVar9;
    piVar12[-1] = iVar6;
    piVar12[-2] = 0x5c0995;
    func_0x00176b20();
    if ((piVar12[0xe] + 0xffffffU & 0xfffffc) == 0) {
      piVar12[-1] = (int)(piVar12 + 0xb);
      piVar12[-2] = 0x5c09ad;
      func_0x0017e680();
    }
    piVar12[0xd] = 0;
    piVar12[0xe] = 5;
    piVar12[0xb] = 0;
    piVar12[9] = 0x31;
    piVar8 = (int *)piVar12[0x53];
    if (piVar8[1] == 0) {
      pcVar4 = *(code **)(*piVar8 + 8);
      piVar12[-1] = (int)piVar8;
      *piVar12 = 0x3a8;
      piVar12[-2] = 0x5c09f5;
      puVar14 = (undefined4 *)(*pcVar4)();
    }
    else {
      puVar14 = (undefined4 *)(piVar8[1] + 0x3a80);
    }
    if ((puVar14[3] + 0xffffff & 0xfffffc) == 0) {
      piVar12[-1] = (int)puVar14;
      piVar12[-2] = 0x5c0a10;
      func_0x0017e680();
    }
    puVar14[3] = 0;
    puVar14[1] = 0x407f4000;
    *puVar14 = 0;
    if ((piVar12[0x14] + 0xffffffU & 0xfffffc) == 0) {
      piVar12[-1] = (int)puVar13;
      piVar12[-2] = 0x5c0a38;
      func_0x0017e680();
    }
    piVar8 = (int *)piVar12[0x53];
  }
  piVar7[10] = 0x38;
  iVar6 = piVar8[1];
  if (iVar6 == 0) {
    pcVar4 = *(code **)(*piVar8 + 8);
    *piVar7 = (int)piVar8;
    piVar7[1] = 0x2d5;
    piVar7[-1] = 0x5c0a6e;
    iVar10 = (*pcVar4)();
    if (piVar8[1] == 0) {
      pcVar4 = *(code **)(*piVar8 + 8);
      *piVar7 = (int)piVar8;
      piVar7[1] = 0x3a8;
      piVar7[-1] = 0x5c0a91;
      iVar6 = (*pcVar4)();
    }
    else {
      iVar6 = piVar8[1] + 0x3a80;
    }
  }
  else {
    iVar10 = iVar6 + 0x2d50;
    iVar6 = iVar6 + 0x3a80;
  }
  *(undefined8 *)(piVar7 + 2) = *(undefined8 *)piVar7[0x10];
  piVar7[1] = iVar6;
  *piVar7 = iVar10;
  piVar7[-1] = 0x5c0aab;
  iVar6 = func_0x00174b50();
  piVar12 = piVar7;
  if (iVar6 != 0) {
    piVar7[10] = 0x3a;
    iVar6 = piVar8[1];
    if (iVar6 == 0) {
      pcVar4 = *(code **)(*piVar8 + 8);
      *piVar7 = (int)piVar8;
      piVar7[1] = 0x2d5;
      piVar7[-1] = 0x5c0ae2;
      iVar10 = (*pcVar4)();
      if (piVar8[1] == 0) {
        pcVar4 = *(code **)(*piVar8 + 8);
        *piVar7 = (int)piVar8;
        piVar7[1] = 0x3a8;
        piVar7[-1] = 0x5c0b05;
        iVar6 = (*pcVar4)();
      }
      else {
        iVar6 = piVar8[1] + 0x3a80;
      }
    }
    else {
      iVar10 = iVar6 + 0x2d50;
      iVar6 = iVar6 + 0x3a80;
    }
    piVar7[2] = iVar6;
    piVar7[1] = iVar10;
    piVar1 = piVar7 + 0x2c;
    *piVar7 = (int)piVar1;
    piVar7[-1] = 0x5c0b1c;
    func_0x0017d460();
    piVar12 = piVar7 + -1;
    if ((piVar7[0x2e] & 0xffffffU) == 0) {
      uVar17 = *(undefined8 *)(piVar7 + 0x2b);
    }
    else {
      piVar7[-1] = (int)piVar1;
      piVar7[-2] = 0x5c0b34;
      lVar15 = (longdouble)func_0x001785e0();
      *(double *)(piVar7 + 0x41) = (double)lVar15;
      uVar17 = *(undefined8 *)(piVar7 + 0x41);
    }
    *(undefined8 *)(piVar7 + -1) = uVar17;
    piVar7[-2] = 0x5c0b59;
    lVar15 = (longdouble)func_0x00186910();
    *(double *)(piVar7 + 0x3f) = (double)lVar15;
    dVar16 = *(double *)(piVar7 + 0x3f);
    dVar18 = *(double *)piVar7[0xf];
    if ((piVar7[0x2e] + 0xffffffU & 0xfffffc) == 0) {
      piVar7[-1] = (int)piVar1;
      *(double *)(piVar7 + 0x17) = dVar16;
      *(double *)(piVar7 + 0x15) = dVar18;
      piVar7[-2] = 0x5c0b98;
      func_0x0017e680();
      dVar18 = *(double *)(piVar7 + 0x15);
      dVar16 = *(double *)(piVar7 + 0x17);
    }
    if (dVar16 + _UNK_00f85c68 <= dVar18) {
      piVar7[9] = 0x40;
      iVar6 = piVar8[1];
      if (iVar6 == 0) {
        pcVar4 = *(code **)(*piVar8 + 8);
        piVar7[-1] = (int)piVar8;
        *piVar7 = 0x3a8;
        piVar7[-2] = 0x5c0cac;
        iVar10 = (*pcVar4)();
        if (piVar8[1] == 0) {
          pcVar4 = *(code **)(*piVar8 + 8);
          piVar7[-1] = (int)piVar8;
          *piVar7 = 0x2d5;
          piVar7[-2] = 0x5c0cf9;
          iVar6 = (*pcVar4)();
        }
        else {
          iVar6 = piVar8[1] + 0x2d50;
        }
      }
      else {
        iVar10 = iVar6 + 0x3a80;
        iVar6 = iVar6 + 0x2d50;
      }
      *piVar7 = iVar10;
      piVar7[-1] = iVar6;
      piVar7[-2] = 0x5c0d05;
      func_0x00176b20();
    }
    else {
      piVar7[9] = 0x3c;
      iVar6 = piVar8[1];
      if (iVar6 == 0) {
        pcVar4 = *(code **)(*piVar8 + 8);
        piVar7[-1] = (int)piVar8;
        *piVar7 = 0x2d5;
        piVar7[-2] = 0x5c0bff;
        iVar10 = (*pcVar4)();
        iVar6 = piVar8[1];
        if (iVar6 != 0) goto LAB_005c0c0c;
        pcVar4 = *(code **)(*piVar8 + 8);
        piVar7[-1] = (int)piVar8;
        *piVar7 = 0x3a8;
        piVar7[-2] = 0x5c0ccf;
        iVar11 = (*pcVar4)();
        if (piVar8[1] == 0) {
          pcVar4 = *(code **)(*piVar8 + 8);
          piVar7[-1] = (int)piVar8;
          *piVar7 = 0x71a;
          piVar7[-2] = 0x5c131d;
          iVar6 = (*pcVar4)();
        }
        else {
          iVar6 = piVar8[1] + 0x71a0;
        }
      }
      else {
        iVar10 = iVar6 + 0x2d50;
LAB_005c0c0c:
        iVar11 = iVar6 + 0x3a80;
        iVar6 = iVar6 + 0x71a0;
      }
      piVar7[0x11] = iVar10;
      piVar7[0x12] = iVar11;
      piVar7[0x13] = iVar6;
      iVar6 = *(int *)(PTR_g_FUNC_lerp_013c35bc + 4);
      piVar7[4] = (int)(piVar7 + 0x11);
      piVar7[3] = iVar6;
      piVar7[1] = (int)(piVar7 + 0xb);
      *piVar7 = piVar7[0x54];
      piVar7[-1] = (int)piVar8;
      piVar7[2] = 3;
      piVar7[-2] = 0x5c0c5b;
      uVar9 = func_0x001842c0();
      *piVar7 = uVar9;
      piVar7[-1] = iVar10;
      piVar7[-2] = 0x5c0c67;
      func_0x00176b20();
      if ((piVar7[0xe] + 0xffffffU & 0xfffffc) == 0) {
        piVar7[-1] = (int)(piVar7 + 0xb);
        piVar7[-2] = 0x5c0c7f;
        func_0x0017e680();
      }
      piVar7[0xd] = 0;
      piVar7[0xe] = 5;
      piVar7[0xb] = 0;
      piVar12 = piVar7 + -1;
    }
  }
  piVar12[10] = 0x48;
  iVar6 = piVar8[1];
  if (iVar6 == 0) {
    pcVar4 = *(code **)(*piVar8 + 8);
    *piVar12 = (int)piVar8;
    piVar12[1] = 0x2c7;
    piVar12[-1] = 0x5c0d34;
    iVar10 = (*pcVar4)();
    if (piVar8[1] == 0) {
      pcVar4 = *(code **)(*piVar8 + 8);
      *piVar12 = (int)piVar8;
      piVar12[1] = 0x1bb;
      piVar12[-1] = 0x5c0d57;
      iVar6 = (*pcVar4)();
    }
    else {
      iVar6 = piVar8[1] + 0x1bb0;
    }
  }
  else {
    iVar10 = iVar6 + 0x2c70;
    iVar6 = iVar6 + 0x1bb0;
  }
  *(undefined8 *)(piVar12 + 2) = *(undefined8 *)piVar12[0x10];
  piVar12[1] = iVar6;
  *piVar12 = iVar10;
  piVar12[-1] = 0x5c0d71;
  iVar6 = func_0x00174b50();
  piVar7 = piVar12;
  if (iVar6 != 0) {
    piVar12[10] = 0x4a;
    iVar6 = piVar8[1];
    if (iVar6 == 0) {
      pcVar4 = *(code **)(*piVar8 + 8);
      *piVar12 = (int)piVar8;
      piVar12[1] = 0x2c7;
      piVar12[-1] = 0x5c0da8;
      iVar10 = (*pcVar4)();
      if (piVar8[1] == 0) {
        pcVar4 = *(code **)(*piVar8 + 8);
        *piVar12 = (int)piVar8;
        piVar12[1] = 0x1bb;
        piVar12[-1] = 0x5c0dcb;
        iVar6 = (*pcVar4)();
      }
      else {
        iVar6 = piVar8[1] + 0x1bb0;
      }
    }
    else {
      iVar10 = iVar6 + 0x2c70;
      iVar6 = iVar6 + 0x1bb0;
    }
    piVar12[2] = iVar6;
    piVar12[1] = iVar10;
    piVar1 = piVar12 + 0x28;
    *piVar12 = (int)piVar1;
    piVar12[-1] = 0x5c0de2;
    func_0x0017d460();
    piVar7 = piVar12 + -1;
    if ((piVar12[0x2a] & 0xffffffU) == 0) {
      uVar17 = *(undefined8 *)(piVar12 + 0x27);
    }
    else {
      piVar12[-1] = (int)piVar1;
      piVar12[-2] = 0x5c0dfa;
      lVar15 = (longdouble)func_0x001785e0();
      *(double *)(piVar12 + 0x3d) = (double)lVar15;
      uVar17 = *(undefined8 *)(piVar12 + 0x3d);
    }
    *(undefined8 *)(piVar12 + -1) = uVar17;
    piVar12[-2] = 0x5c0e1f;
    lVar15 = (longdouble)func_0x00186910();
    *(double *)(piVar12 + 0x3b) = (double)lVar15;
    dVar16 = *(double *)(piVar12 + 0x3b);
    dVar18 = *(double *)piVar12[0xf];
    if ((piVar12[0x2a] + 0xffffffU & 0xfffffc) == 0) {
      piVar12[-1] = (int)piVar1;
      *(double *)(piVar12 + 0x17) = dVar16;
      *(double *)(piVar12 + 0x15) = dVar18;
      piVar12[-2] = 0x5c0e5e;
      func_0x0017e680();
      dVar18 = *(double *)(piVar12 + 0x15);
      dVar16 = *(double *)(piVar12 + 0x17);
    }
    if (dVar16 + _UNK_00f85c68 <= dVar18) {
      piVar12[9] = 0x50;
      iVar6 = piVar8[1];
      if (iVar6 == 0) {
        pcVar4 = *(code **)(*piVar8 + 8);
        piVar12[-1] = (int)piVar8;
        *piVar12 = 0x1bb;
        piVar12[-2] = 0x5c0f72;
        iVar10 = (*pcVar4)();
        if (piVar8[1] == 0) {
          pcVar4 = *(code **)(*piVar8 + 8);
          piVar12[-1] = (int)piVar8;
          *piVar12 = 0x2c7;
          piVar12[-2] = 0x5c0fbf;
          iVar6 = (*pcVar4)();
        }
        else {
          iVar6 = piVar8[1] + 0x2c70;
        }
      }
      else {
        iVar10 = iVar6 + 0x1bb0;
        iVar6 = iVar6 + 0x2c70;
      }
      *piVar12 = iVar10;
      piVar12[-1] = iVar6;
      piVar12[-2] = 0x5c0fcb;
      func_0x00176b20();
    }
    else {
      piVar12[9] = 0x4c;
      iVar6 = piVar8[1];
      if (iVar6 == 0) {
        pcVar4 = *(code **)(*piVar8 + 8);
        piVar12[-1] = (int)piVar8;
        *piVar12 = 0x2c7;
        piVar12[-2] = 0x5c0ec5;
        iVar10 = (*pcVar4)();
        iVar6 = piVar8[1];
        if (iVar6 != 0) goto LAB_005c0ed2;
        pcVar4 = *(code **)(*piVar8 + 8);
        piVar12[-1] = (int)piVar8;
        *piVar12 = 0x1bb;
        piVar12[-2] = 0x5c0f95;
        iVar11 = (*pcVar4)();
        if (piVar8[1] == 0) {
          pcVar4 = *(code **)(*piVar8 + 8);
          piVar12[-1] = (int)piVar8;
          *piVar12 = 0x1be;
          piVar12[-2] = 0x5c1335;
          iVar6 = (*pcVar4)();
        }
        else {
          iVar6 = piVar8[1] + 0x1be0;
        }
      }
      else {
        iVar10 = iVar6 + 0x2c70;
LAB_005c0ed2:
        iVar11 = iVar6 + 0x1bb0;
        iVar6 = iVar6 + 0x1be0;
      }
      piVar12[0x11] = iVar10;
      piVar12[0x12] = iVar11;
      piVar12[0x13] = iVar6;
      iVar6 = *(int *)(PTR_g_FUNC_lerp_013c35bc + 4);
      piVar12[4] = (int)(piVar12 + 0x11);
      piVar12[3] = iVar6;
      piVar12[1] = (int)(piVar12 + 0xb);
      *piVar12 = piVar12[0x54];
      piVar12[-1] = (int)piVar8;
      piVar12[2] = 3;
      piVar12[-2] = 0x5c0f21;
      uVar9 = func_0x001842c0();
      *piVar12 = uVar9;
      piVar12[-1] = iVar10;
      piVar12[-2] = 0x5c0f2d;
      func_0x00176b20();
      if ((piVar12[0xe] + 0xffffffU & 0xfffffc) == 0) {
        piVar12[-1] = (int)(piVar12 + 0xb);
        piVar12[-2] = 0x5c0f45;
        func_0x0017e680();
      }
      piVar12[0xd] = 0;
      piVar12[0xe] = 5;
      piVar12[0xb] = 0;
      piVar7 = piVar12 + -1;
    }
  }
  piVar7[10] = 0x59;
  iVar6 = piVar8[1];
  if (iVar6 == 0) {
    pcVar4 = *(code **)(*piVar8 + 8);
    *piVar7 = (int)piVar8;
    piVar7[1] = 0x2d6;
    piVar7[-1] = 0x5c0ffa;
    iVar10 = (*pcVar4)();
    if (piVar8[1] == 0) {
      pcVar4 = *(code **)(*piVar8 + 8);
      *piVar7 = (int)piVar8;
      piVar7[1] = 0x3ac;
      piVar7[-1] = 0x5c101d;
      iVar6 = (*pcVar4)();
    }
    else {
      iVar6 = piVar8[1] + 0x3ac0;
    }
  }
  else {
    iVar10 = iVar6 + 0x2d60;
    iVar6 = iVar6 + 0x3ac0;
  }
  *(undefined8 *)(piVar7 + 2) = *(undefined8 *)piVar7[0x10];
  piVar7[1] = iVar6;
  *piVar7 = iVar10;
  piVar7[-1] = 0x5c1037;
  iVar6 = func_0x00174b50();
  piVar12 = piVar7;
  if (iVar6 == 0) goto LAB_005c1291;
  piVar7[10] = 0x5b;
  iVar6 = piVar8[1];
  if (iVar6 == 0) {
    pcVar4 = *(code **)(*piVar8 + 8);
    *piVar7 = (int)piVar8;
    piVar7[1] = 0x2d6;
    piVar7[-1] = 0x5c106e;
    iVar10 = (*pcVar4)();
    if (piVar8[1] == 0) {
      pcVar4 = *(code **)(*piVar8 + 8);
      *piVar7 = (int)piVar8;
      piVar7[1] = 0x3ac;
      piVar7[-1] = 0x5c1091;
      iVar6 = (*pcVar4)();
    }
    else {
      iVar6 = piVar8[1] + 0x3ac0;
    }
  }
  else {
    iVar10 = iVar6 + 0x2d60;
    iVar6 = iVar6 + 0x3ac0;
  }
  piVar7[2] = iVar6;
  piVar7[1] = iVar10;
  piVar1 = piVar7 + 0x24;
  *piVar7 = (int)piVar1;
  piVar7[-1] = 0x5c10a8;
  func_0x0017d460();
  piVar12 = piVar7 + -1;
  if ((piVar7[0x26] & 0xffffffU) == 0) {
    uVar17 = *(undefined8 *)(piVar7 + 0x23);
  }
  else {
    piVar7[-1] = (int)piVar1;
    piVar7[-2] = 0x5c10c0;
    lVar15 = (longdouble)func_0x001785e0();
    *(double *)(piVar7 + 0x39) = (double)lVar15;
    uVar17 = *(undefined8 *)(piVar7 + 0x39);
  }
  *(undefined8 *)(piVar7 + -1) = uVar17;
  piVar7[-2] = 0x5c10e5;
  lVar15 = (longdouble)func_0x00186910();
  *(double *)(piVar7 + 0x37) = (double)lVar15;
  dVar16 = *(double *)(piVar7 + 0x37);
  dVar18 = *(double *)piVar7[0xf];
  if ((piVar7[0x26] + 0xffffffU & 0xfffffc) == 0) {
    piVar7[-1] = (int)piVar1;
    *(double *)(piVar7 + 0xf) = dVar16;
    *(double *)(piVar7 + 0x17) = dVar18;
    piVar7[-2] = 0x5c1124;
    func_0x0017e680();
    dVar18 = *(double *)(piVar7 + 0x17);
    dVar16 = *(double *)(piVar7 + 0xf);
  }
  if (dVar16 + _UNK_00f85c68 <= dVar18) {
    piVar7[9] = 0x61;
    iVar6 = piVar8[1];
    if (iVar6 == 0) {
      pcVar4 = *(code **)(*piVar8 + 8);
      piVar7[-1] = (int)piVar8;
      *piVar7 = 0x3ac;
      piVar7[-2] = 0x5c1238;
      iVar10 = (*pcVar4)();
      if (piVar8[1] == 0) {
        pcVar4 = *(code **)(*piVar8 + 8);
        piVar7[-1] = (int)piVar8;
        *piVar7 = 0x2d6;
        piVar7[-2] = 0x5c1285;
        iVar6 = (*pcVar4)();
      }
      else {
        iVar6 = piVar8[1] + 0x2d60;
      }
    }
    else {
      iVar10 = iVar6 + 0x3ac0;
      iVar6 = iVar6 + 0x2d60;
    }
    *piVar7 = iVar10;
    piVar7[-1] = iVar6;
    piVar7[-2] = 0x5c1291;
    func_0x00176b20();
    goto LAB_005c1291;
  }
  piVar7[9] = 0x5d;
  iVar6 = piVar8[1];
  if (iVar6 == 0) {
    pcVar4 = *(code **)(*piVar8 + 8);
    piVar7[-1] = (int)piVar8;
    *piVar7 = 0x2d6;
    piVar7[-2] = 0x5c118b;
    iVar10 = (*pcVar4)();
    iVar6 = piVar8[1];
    if (iVar6 != 0) goto LAB_005c1198;
    pcVar4 = *(code **)(*piVar8 + 8);
    piVar7[-1] = (int)piVar8;
    *piVar7 = 0x3ac;
    piVar7[-2] = 0x5c125b;
    iVar11 = (*pcVar4)();
    if (piVar8[1] == 0) {
      pcVar4 = *(code **)(*piVar8 + 8);
      piVar7[-1] = (int)piVar8;
      *piVar7 = 0x3ad;
      piVar7[-2] = 0x5c134d;
      iVar6 = (*pcVar4)();
    }
    else {
      iVar6 = piVar8[1] + 0x3ad0;
    }
  }
  else {
    iVar10 = iVar6 + 0x2d60;
LAB_005c1198:
    iVar11 = iVar6 + 0x3ac0;
    iVar6 = iVar6 + 0x3ad0;
  }
  piVar7[0x11] = iVar10;
  piVar7[0x12] = iVar11;
  piVar7[0x13] = iVar6;
  iVar6 = *(int *)(PTR_g_FUNC_lerp_013c35bc + 4);
  piVar7[4] = (int)(piVar7 + 0x11);
  piVar7[3] = iVar6;
  piVar7[1] = (int)(piVar7 + 0xb);
  *piVar7 = piVar7[0x54];
  piVar7[-1] = (int)piVar8;
  piVar7[2] = 3;
  piVar7[-2] = 0x5c11e7;
  uVar9 = func_0x001842c0();
  *piVar7 = uVar9;
  piVar7[-1] = iVar10;
  piVar7[-2] = 0x5c11f3;
  func_0x00176b20();
  if ((piVar7[0xe] + 0xffffffU & 0xfffffc) == 0) {
    piVar7[-1] = (int)(piVar7 + 0xb);
    piVar7[-2] = 0x5c120b;
    func_0x0017e680();
  }
  piVar7[0xd] = 0;
  piVar7[0xe] = 5;
  piVar7[0xb] = 0;
  piVar12 = piVar7 + -1;
LAB_005c1291:
  if ((piVar12[0x1d] + 0xffffffU & 0xfffffc) == 0) {
    *piVar12 = (int)(piVar12 + 0x1a);
    piVar12[-1] = 0x5c12af;
    func_0x0017e680();
  }
  if ((piVar12[0xf] + 0xffffffU & 0xfffffc) == 0) {
    *piVar12 = (int)(piVar12 + 0xc);
    piVar12[-1] = 0x5c12c7;
    func_0x0017e680();
  }
  *(int *)piVar12[0x1e] = piVar12[8];
  return;
}

