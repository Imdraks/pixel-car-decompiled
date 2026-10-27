  5b9796:	8b 44 24 18          	mov    0x18(%esp),%eax
  5b979a:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5b979e:	66 0f 28 93 60 09 bb 	movapd -0x44f6a0(%ebx),%xmm2
  5b97a5:	ff 
  5b97a6:	66 0f 57 d0          	xorpd  %xmm0,%xmm2
  5b97aa:	66 0f 2e d1          	ucomisd %xmm1,%xmm2
  5b97ae:	76 1d                	jbe    5b97cd <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x823d>
  5b97b0:	c7 44 24 30 8f 01 00 	movl   $0x18f,0x30(%esp)
  5b97b7:	00 
  5b97b8:	8b 06                	mov    (%esi),%eax
  5b97ba:	85 c0                	test   %eax,%eax
  5b97bc:	0f 84 21 01 00 00    	je     5b98e3 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8353>
  5b97c2:	8d 88 10 6e 00 00    	lea    0x6e10(%eax),%ecx
  5b97c8:	e9 41 01 00 00       	jmp    5b990e <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x837e>
  5b97cd:	c7 44 24 30 9f 01 00 	movl   $0x19f,0x30(%esp)
  5b97d4:	00 
  5b97d5:	8b 36                	mov    (%esi),%esi
  5b97d7:	85 f6                	test   %esi,%esi
  5b97d9:	74 08                	je     5b97e3 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8253>
  5b97db:	81 c6 10 6e 00 00    	add    $0x6e10,%esi
  5b97e1:	eb 1d                	jmp    5b9800 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8270>
  5b97e3:	8b 45 00             	mov    0x0(%ebp),%eax
  5b97e6:	8b 40 08             	mov    0x8(%eax),%eax
  5b97e9:	89 2c 24             	mov    %ebp,(%esp)
  5b97ec:	c7 44 24 04 e1 06 00 	movl   $0x6e1,0x4(%esp) # verified field ID: tire_heat
  5b97f3:	00 
  5b97f4:	ff d0                	call   *%eax
  5b97f6:	89 c6                	mov    %eax,%esi
  5b97f8:	8b 44 24 18          	mov    0x18(%esp),%eax
  5b97fc:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5b9800:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
  5b9806:	8d ac 24 48 04 00 00 	lea    0x448(%esp),%ebp
  5b980d:	89 6c 24 04          	mov    %ebp,0x4(%esp)
  5b9811:	89 34 24             	mov    %esi,(%esp)
  5b9814:	e8 37 b3 ba ff       	call   164b50 <YYCompareVal(RValue const&, RValue const&, double)@plt>
  5b9819:	85 c0                	test   %eax,%eax
  5b981b:	8b 7c 24 38          	mov    0x38(%esp),%edi
  5b981f:	0f 8e ab 02 00 00    	jle    5b9ad0 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8540>
  5b9825:	c7 44 24 30 a1 01 00 	movl   $0x1a1,0x30(%esp)
  5b982c:	00 
  5b982d:	8b 3f                	mov    (%edi),%edi
  5b982f:	85 ff                	test   %edi,%edi
  5b9831:	74 08                	je     5b983b <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x82ab>
  5b9833:	81 c7 10 6e 00 00    	add    $0x6e10,%edi
  5b9839:	eb 18                	jmp    5b9853 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x82c3>
  5b983b:	8b 4c 24 24          	mov    0x24(%esp),%ecx
  5b983f:	8b 01                	mov    (%ecx),%eax
  5b9841:	8b 40 08             	mov    0x8(%eax),%eax
  5b9844:	89 0c 24             	mov    %ecx,(%esp)
  5b9847:	c7 44 24 04 e1 06 00 	movl   $0x6e1,0x4(%esp) # verified field ID: tire_heat
  5b984e:	00 
  5b984f:	ff d0                	call   *%eax
  5b9851:	89 c7                	mov    %eax,%edi
  5b9853:	c7 84 24 cc 07 00 00 	movl   $0x0,0x7cc(%esp)
  5b985a:	00 00 00 00 
  5b985e:	c7 84 24 c4 07 00 00 	movl   $0x3fd00000,0x7c4(%esp)
  5b9865:	00 00 d0 3f 
  5b9869:	c7 84 24 c0 07 00 00 	movl   $0x0,0x7c0(%esp)
  5b9870:	00 00 00 00 
  5b9874:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5b9879:	23 47 0c             	and    0xc(%edi),%eax
  5b987c:	83 f8 0d             	cmp    $0xd,%eax
  5b987f:	0f 87 08 02 00 00    	ja     5b9a8d <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x84fd>
  5b9885:	8b 84 83 d4 0f bc ff 	mov    -0x43f02c(%ebx,%eax,4),%eax
  5b988c:	01 d8                	add    %ebx,%eax
  5b988e:	ff e0                	jmp    *%eax
  5b9890:	f2 0f 10 07          	movsd  (%edi),%xmm0
  5b9894:	f2 0f 58 83 e8 0c bc 	addsd  -0x43f318(%ebx),%xmm0
  5b989b:	ff 
  5b989c:	f2 0f 11 07          	movsd  %xmm0,(%edi)
  5b98a0:	e9 05 02 00 00       	jmp    5b9aaa <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x851a>
  5b98a5:	8b 07                	mov    (%edi),%eax
  5b98a7:	8b 40 08             	mov    0x8(%eax),%eax
  5b98aa:	89 3c 24             	mov    %edi,(%esp)
  5b98ad:	c7 44 24 04 b4 05 00 	movl   $0x5b4,0x4(%esp)
  5b98b4:	00 
  5b98b5:	ff d0                	call   *%eax
  5b98b7:	89 84 24 40 02 00 00 	mov    %eax,0x240(%esp)
  5b98be:	8b 44 24 38          	mov    0x38(%esp),%eax
  5b98c2:	8b 00                	mov    (%eax),%eax
  5b98c4:	85 c0                	test   %eax,%eax
  5b98c6:	0f 85 96 e7 ff ff    	jne    5b8062 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x6ad2>
  5b98cc:	8b 07                	mov    (%edi),%eax
  5b98ce:	8b 40 08             	mov    0x8(%eax),%eax
  5b98d1:	89 3c 24             	mov    %edi,(%esp)
  5b98d4:	c7 44 24 04 d5 04 00 	movl   $0x4d5,0x4(%esp)
  5b98db:	00 
  5b98dc:	ff d0                	call   *%eax
  5b98de:	e9 84 e7 ff ff       	jmp    5b8067 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x6ad7>
  5b98e3:	8b 45 00             	mov    0x0(%ebp),%eax
  5b98e6:	8b 40 08             	mov    0x8(%eax),%eax
  5b98e9:	89 2c 24             	mov    %ebp,(%esp)
  5b98ec:	c7 44 24 04 e1 06 00 	movl   $0x6e1,0x4(%esp) # verified field ID: tire_heat
  5b98f3:	00 
  5b98f4:	ff d0                	call   *%eax
  5b98f6:	89 84 24 80 02 00 00 	mov    %eax,0x280(%esp)
  5b98fd:	8b 06                	mov    (%esi),%eax
  5b98ff:	85 c0                	test   %eax,%eax
  5b9901:	0f 84 bd 02 00 00    	je     5b9bc4 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8634>
  5b9907:	8b 8c 24 80 02 00 00 	mov    0x280(%esp),%ecx
  5b990e:	89 8c 24 80 02 00 00 	mov    %ecx,0x280(%esp)
  5b9915:	05 90 5d 00 00       	add    $0x5d90,%eax
  5b991a:	89 44 24 04          	mov    %eax,0x4(%esp)
  5b991e:	8d b4 24 68 22 00 00 	lea    0x2268(%esp),%esi
  5b9925:	89 34 24             	mov    %esi,(%esp)
  5b9928:	c7 44 24 0c 85 eb 91 	movl   $0x3f91eb85,0xc(%esp)
  5b992f:	3f 
  5b9930:	c7 44 24 08 ec 51 b8 	movl   $0x1eb851ec,0x8(%esp)
  5b9937:	1e 
  5b9938:	e8 f3 ec bb ff       	call   178630 <operator*(YYRValue const&, double)@plt>
  5b993d:	83 ec 04             	sub    $0x4,%esp
  5b9940:	89 b4 24 e8 17 00 00 	mov    %esi,0x17e8(%esp)
  5b9947:	8b 84 24 30 01 00 00 	mov    0x130(%esp),%eax
  5b994e:	89 84 24 ec 17 00 00 	mov    %eax,0x17ec(%esp)
  5b9955:	8b ab d8 71 ff ff    	mov    -0x8e28(%ebx),%ebp
  5b995b:	89 ac 24 f0 17 00 00 	mov    %ebp,0x17f0(%esp)
  5b9962:	8b 84 24 c8 00 00 00 	mov    0xc8(%esp),%eax
  5b9969:	8b 40 04             	mov    0x4(%eax),%eax
  5b996c:	8d 8c 24 e8 17 00 00 	lea    0x17e8(%esp),%ecx
  5b9973:	89 4c 24 14          	mov    %ecx,0x14(%esp)
  5b9977:	89 44 24 10          	mov    %eax,0x10(%esp)
  5b997b:	8d 44 24 60          	lea    0x60(%esp),%eax
  5b997f:	89 44 24 08          	mov    %eax,0x8(%esp)
  5b9983:	8b 84 24 44 6a 00 00 	mov    0x6a44(%esp),%eax
  5b998a:	89 44 24 04          	mov    %eax,0x4(%esp)
  5b998e:	8b 44 24 24          	mov    0x24(%esp),%eax
  5b9992:	89 04 24             	mov    %eax,(%esp)
  5b9995:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
  5b999c:	00 
  5b999d:	e8 1e a9 bb ff       	call   1742c0 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
  5b99a2:	89 44 24 08          	mov    %eax,0x8(%esp)
  5b99a6:	8d b4 24 98 68 00 00 	lea    0x6898(%esp),%esi
  5b99ad:	89 34 24             	mov    %esi,(%esp)
  5b99b0:	c7 44 24 04 64 00 00 	movl   $0x64,0x4(%esp)
  5b99b7:	00 
  5b99b8:	e8 63 07 bb ff       	call   16a120 <operator+(int, YYRValue const&)@plt>
  5b99bd:	83 ec 04             	sub    $0x4,%esp
  5b99c0:	8b 44 24 18          	mov    0x18(%esp),%eax
  5b99c4:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5b99c8:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
  5b99ce:	89 74 24 04          	mov    %esi,0x4(%esp)
  5b99d2:	8b 84 24 80 02 00 00 	mov    0x280(%esp),%eax
  5b99d9:	89 04 24             	mov    %eax,(%esp)
  5b99dc:	e8 6f b1 ba ff       	call   164b50 <YYCompareVal(RValue const&, RValue const&, double)@plt>
  5b99e1:	89 c7                	mov    %eax,%edi
  5b99e3:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5b99e8:	03 84 24 a4 68 00 00 	add    0x68a4(%esp),%eax
  5b99ef:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5b99f4:	75 08                	jne    5b99fe <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x846e>
  5b99f6:	89 34 24             	mov    %esi,(%esp)
  5b99f9:	e8 82 4c bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5b99fe:	85 ff                	test   %edi,%edi
  5b9a00:	0f 88 73 01 00 00    	js     5b9b79 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x85e9>
  5b9a06:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5b9a0b:	03 44 24 6c          	add    0x6c(%esp),%eax
  5b9a0f:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5b9a14:	8b 74 24 38          	mov    0x38(%esp),%esi
  5b9a18:	75 0c                	jne    5b9a26 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8496>
  5b9a1a:	8d 44 24 60          	lea    0x60(%esp),%eax
  5b9a1e:	89 04 24             	mov    %eax,(%esp)
  5b9a21:	e8 5a 4c bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5b9a26:	c7 44 24 68 00 00 00 	movl   $0x0,0x68(%esp)
  5b9a2d:	00 
  5b9a2e:	c7 44 24 6c 05 00 00 	movl   $0x5,0x6c(%esp)
  5b9a35:	00 
  5b9a36:	c7 44 24 60 00 00 00 	movl   $0x0,0x60(%esp)
  5b9a3d:	00 
  5b9a3e:	c7 44 24 30 95 01 00 	movl   $0x195,0x30(%esp)
  5b9a45:	00 
  5b9a46:	8b 06                	mov    (%esi),%eax
  5b9a48:	85 c0                	test   %eax,%eax
  5b9a4a:	0f 84 4b 01 00 00    	je     5b9b9b <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x860b>
  5b9a50:	8d b8 10 6e 00 00    	lea    0x6e10(%eax),%edi
  5b9a56:	05 90 5d 00 00       	add    $0x5d90,%eax
  5b9a5b:	e9 c2 01 00 00       	jmp    5b9c22 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8692>
  5b9a60:	8d 84 24 c0 07 00 00 	lea    0x7c0(%esp),%eax
  5b9a67:	89 04 24             	mov    %eax,(%esp)
  5b9b42:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5b9b47:	8b b4 24 d0 00 00 00 	mov    0xd0(%esp),%esi
  5b9b4e:	03 46 0c             	add    0xc(%esi),%eax
  5b9b51:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5b9b56:	75 08                	jne    5b9b60 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x85d0>
  5b9b58:	89 34 24             	mov    %esi,(%esp)
  5b9b5b:	e8 20 4b bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5b9b60:	c7 46 08 00 00 00 00 	movl   $0x0,0x8(%esi)
  5b9b67:	c7 46 0c 05 00 00 00 	movl   $0x5,0xc(%esi)
  5b9b6e:	c7 06 00 00 00 00    	movl   $0x0,(%esi)
  5b9b74:	e9 b3 04 00 00       	jmp    5ba02c <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8a9c>
  5b9b79:	c7 44 24 30 91 01 00 	movl   $0x191,0x30(%esp)
  5b9b80:	00 
  5b9b81:	8b 44 24 38          	mov    0x38(%esp),%eax
  5b9b85:	8b 00                	mov    (%eax),%eax
  5b9b87:	85 c0                	test   %eax,%eax
  5b9b89:	74 51                	je     5b9bdc <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x864c>
  5b9b8b:	8d b8 10 6e 00 00    	lea    0x6e10(%eax),%edi
  5b9b91:	05 90 5d 00 00       	add    $0x5d90,%eax
  5b9b96:	e9 c3 02 00 00       	jmp    5b9e5e <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x88ce>
  5b9b9b:	8b 4c 24 24          	mov    0x24(%esp),%ecx
  5b9b9f:	8b 01                	mov    (%ecx),%eax
  5b9ba1:	8b 40 08             	mov    0x8(%eax),%eax
  5b9ba4:	89 0c 24             	mov    %ecx,(%esp)
  5b9ba7:	c7 44 24 04 e1 06 00 	movl   $0x6e1,0x4(%esp) # verified field ID: tire_heat
  5b9bae:	00 
  5b9baf:	ff d0                	call   *%eax
  5b9bb1:	89 c7                	mov    %eax,%edi
  5b9bb3:	8b 44 24 38          	mov    0x38(%esp),%eax
  5b9bb7:	8b 00                	mov    (%eax),%eax
  5b9bb9:	85 c0                	test   %eax,%eax
  5b9bbb:	74 4f                	je     5b9c0c <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x867c>
  5b9bbd:	05 90 5d 00 00       	add    $0x5d90,%eax
  5b9bc2:	eb 5e                	jmp    5b9c22 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8692>
  5b9bc4:	8b 45 00             	mov    0x0(%ebp),%eax
  5b9bc7:	8b 40 08             	mov    0x8(%eax),%eax
  5b9bca:	89 2c 24             	mov    %ebp,(%esp)
  5b9bcd:	c7 44 24 04 d9 05 00 	movl   $0x5d9,0x4(%esp) # verified field ID: RPM
  5b9bd4:	00 
  5b9bd5:	ff d0                	call   *%eax
  5b9bd7:	e9 3e fd ff ff       	jmp    5b991a <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x838a>
  5b9bdc:	8b 4c 24 24          	mov    0x24(%esp),%ecx
  5b9be0:	8b 01                	mov    (%ecx),%eax
  5b9be2:	8b 40 08             	mov    0x8(%eax),%eax
  5b9be5:	89 0c 24             	mov    %ecx,(%esp)
  5b9be8:	c7 44 24 04 e1 06 00 	movl   $0x6e1,0x4(%esp) # verified field ID: tire_heat
  5b9bef:	00 
  5b9bf0:	ff d0                	call   *%eax
  5b9bf2:	89 c7                	mov    %eax,%edi
  5b9bf4:	8b 44 24 38          	mov    0x38(%esp),%eax
  5b9bf8:	8b 00                	mov    (%eax),%eax
  5b9bfa:	85 c0                	test   %eax,%eax
  5b9bfc:	0f 84 46 02 00 00    	je     5b9e48 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x88b8>
  5b9c02:	05 90 5d 00 00       	add    $0x5d90,%eax
  5b9c07:	e9 52 02 00 00       	jmp    5b9e5e <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x88ce>
  5b9c0c:	8b 4c 24 24          	mov    0x24(%esp),%ecx
  5b9c10:	8b 01                	mov    (%ecx),%eax
  5b9c12:	8b 40 08             	mov    0x8(%eax),%eax
  5b9c15:	89 0c 24             	mov    %ecx,(%esp)
  5b9c18:	c7 44 24 04 d9 05 00 	movl   $0x5d9,0x4(%esp) # verified field ID: RPM
  5b9c1f:	00 
  5b9c20:	ff d0                	call   *%eax
  5b9c22:	89 44 24 04          	mov    %eax,0x4(%esp)
  5b9c26:	8d b4 24 58 22 00 00 	lea    0x2258(%esp),%esi
  5b9c2d:	89 34 24             	mov    %esi,(%esp)
  5b9c30:	c7 44 24 0c 85 eb 91 	movl   $0x3f91eb85,0xc(%esp)
  5b9c37:	3f 
  5b9c38:	c7 44 24 08 ec 51 b8 	movl   $0x1eb851ec,0x8(%esp)
  5b9c3f:	1e 
  5b9c40:	e8 eb e9 bb ff       	call   178630 <operator*(YYRValue const&, double)@plt>
  5b9c45:	83 ec 04             	sub    $0x4,%esp
  5b9c48:	89 b4 24 dc 17 00 00 	mov    %esi,0x17dc(%esp)
  5b9c4f:	8b 84 24 80 00 00 00 	mov    0x80(%esp),%eax
  5b9c56:	89 84 24 e0 17 00 00 	mov    %eax,0x17e0(%esp)
  5b9c5d:	89 ac 24 e4 17 00 00 	mov    %ebp,0x17e4(%esp)
  5b9c64:	8b 84 24 c8 00 00 00 	mov    0xc8(%esp),%eax
  5b9c6b:	8b 40 04             	mov    0x4(%eax),%eax
  5b9c6e:	8d 8c 24 dc 17 00 00 	lea    0x17dc(%esp),%ecx
  5b9c75:	89 4c 24 14          	mov    %ecx,0x14(%esp)
  5b9c79:	89 44 24 10          	mov    %eax,0x10(%esp)
  5b9c7d:	8d 44 24 60          	lea    0x60(%esp),%eax
  5b9c81:	89 44 24 08          	mov    %eax,0x8(%esp)
  5b9c85:	8b 84 24 44 6a 00 00 	mov    0x6a44(%esp),%eax
  5b9c8c:	89 44 24 04          	mov    %eax,0x4(%esp)
  5b9c90:	8b 6c 24 24          	mov    0x24(%esp),%ebp
  5b9c94:	89 2c 24             	mov    %ebp,(%esp)
  5b9c97:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
  5b9c9e:	00 
  5b9c9f:	e8 1c a6 bb ff       	call   1742c0 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
  5b9ca4:	89 44 24 08          	mov    %eax,0x8(%esp)
  5b9ca8:	8d b4 24 78 68 00 00 	lea    0x6878(%esp),%esi
  5b9caf:	89 34 24             	mov    %esi,(%esp)
  5b9cb2:	c7 44 24 04 64 00 00 	movl   $0x64,0x4(%esp)
  5b9cb9:	00 
  5b9cba:	e8 61 04 bb ff       	call   16a120 <operator+(int, YYRValue const&)@plt>
  5b9cbf:	83 ec 04             	sub    $0x4,%esp
  5b9cc2:	8b 44 24 18          	mov    0x18(%esp),%eax
  5b9cc6:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5b9cca:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
  5b9cd0:	89 74 24 04          	mov    %esi,0x4(%esp)
  5b9cd4:	89 3c 24             	mov    %edi,(%esp)
  5b9cd7:	e8 74 ae ba ff       	call   164b50 <YYCompareVal(RValue const&, RValue const&, double)@plt>
  5b9cdc:	89 c7                	mov    %eax,%edi
  5b9cde:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5b9ce3:	03 84 24 84 68 00 00 	add    0x6884(%esp),%eax
  5b9cea:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5b9cef:	75 08                	jne    5b9cf9 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8769>
  5b9cf1:	89 34 24             	mov    %esi,(%esp)
  5b9cf4:	e8 87 49 bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5b9cf9:	85 ff                	test   %edi,%edi
  5b9cfb:	8b 7c 24 38          	mov    0x38(%esp),%edi
  5b9cff:	0f 8e e6 00 00 00    	jle    5b9deb <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x885b>
  5b9d05:	c7 44 24 30 97 01 00 	movl   $0x197,0x30(%esp)
  5b9d0c:	00 
  5b9d0d:	8b 3f                	mov    (%edi),%edi
  5b9d0f:	85 ff                	test   %edi,%edi
  5b9d11:	74 08                	je     5b9d1b <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x878b>
  5b9d13:	81 c7 10 6e 00 00    	add    $0x6e10,%edi
  5b9d19:	eb 15                	jmp    5b9d30 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x87a0>
  5b9d1b:	8b 45 00             	mov    0x0(%ebp),%eax
  5b9d1e:	8b 40 08             	mov    0x8(%eax),%eax
  5b9d21:	89 2c 24             	mov    %ebp,(%esp)
  5b9d24:	c7 44 24 04 e1 06 00 	movl   $0x6e1,0x4(%esp) # verified field ID: tire_heat
  5b9d2b:	00 
  5b9d2c:	ff d0                	call   *%eax
  5b9d2e:	89 c7                	mov    %eax,%edi
  5b9d30:	c7 84 24 dc 07 00 00 	movl   $0x0,0x7dc(%esp)
  5b9d37:	00 00 00 00 
  5b9d3b:	c7 84 24 d4 07 00 00 	movl   $0x3fc99999,0x7d4(%esp)
  5b9d42:	99 99 c9 3f 
  5b9d46:	c7 84 24 d0 07 00 00 	movl   $0x9999999a,0x7d0(%esp)
  5b9d4d:	9a 99 99 99 
  5b9d51:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5b9d56:	23 47 0c             	and    0xc(%edi),%eax
  5b9d59:	83 f8 0d             	cmp    $0xd,%eax
  5b9d5c:	77 4a                	ja     5b9da8 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8818>
  5b9d5e:	8b 84 83 0c 10 bc ff 	mov    -0x43eff4(%ebx,%eax,4),%eax
  5b9d65:	01 d8                	add    %ebx,%eax
  5b9d67:	ff e0                	jmp    *%eax
  5b9d69:	f2 0f 10 07          	movsd  (%edi),%xmm0
  5b9d6d:	f2 0f 58 83 f0 0c bc 	addsd  -0x43f310(%ebx),%xmm0
  5b9d74:	ff 
  5b9d75:	f2 0f 11 07          	movsd  %xmm0,(%edi)
  5b9d79:	eb 4a                	jmp    5b9dc5 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8835>
  5b9d7b:	8d 84 24 d0 07 00 00 	lea    0x7d0(%esp),%eax
  5b9d82:	89 04 24             	mov    %eax,(%esp)
  5b9d85:	e8 16 de bb ff       	call   177ba0 <INT64_RValue(RValue const*)@plt>
  5b9d8a:	8b 0f                	mov    (%edi),%ecx
  5b9d8c:	29 c1                	sub    %eax,%ecx
  5b9d8e:	19 57 04             	sbb    %edx,0x4(%edi)
  5b9d91:	89 0f                	mov    %ecx,(%edi)
  5b9d93:	eb 30                	jmp    5b9dc5 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8835>
  5b9d95:	8d 84 24 d0 07 00 00 	lea    0x7d0(%esp),%eax
  5b9d9c:	89 04 24             	mov    %eax,(%esp)
  5b9d9f:	e8 1c a9 bb ff       	call   1746c0 <INT32_RValue(RValue const*)@plt>
  5b9da4:	29 07                	sub    %eax,(%edi)
  5b9da6:	eb 1d                	jmp    5b9dc5 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8835>
  5b9da8:	8d 84 24 d0 07 00 00 	lea    0x7d0(%esp),%eax
  5b9daf:	89 44 24 08          	mov    %eax,0x8(%esp)
  5b9db3:	89 7c 24 04          	mov    %edi,0x4(%esp)
  5b9db7:	8d 83 cc 14 bb ff    	lea    -0x44eb34(%ebx),%eax
  5b9dbd:	89 04 24             	mov    %eax,(%esp)
  5b9dc0:	e8 bb f8 ba ff       	call   169680 <YYOpError(char const*, YYRValue const*, YYRValue const*)@plt>
  5b9dc5:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5b9dca:	03 84 24 dc 07 00 00 	add    0x7dc(%esp),%eax
  5b9dd1:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5b9dd6:	75 0f                	jne    5b9de7 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8857>
  5b9dd8:	8d 84 24 d0 07 00 00 	lea    0x7d0(%esp),%eax
  5b9ddf:	89 04 24             	mov    %eax,(%esp)
  5b9de2:	e8 99 48 bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5b9de7:	8b 7c 24 38          	mov    0x38(%esp),%edi
  5b9deb:	be ff ff ff 00       	mov    $0xffffff,%esi
  5b9df0:	8b 44 24 6c          	mov    0x6c(%esp),%eax
  5b9df4:	01 f0                	add    %esi,%eax
  5b9df6:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5b9dfb:	75 0c                	jne    5b9e09 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8879>
  5b9dfd:	8d 44 24 60          	lea    0x60(%esp),%eax
  5b9e01:	89 04 24             	mov    %eax,(%esp)
  5b9e04:	e8 77 48 bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5b9e09:	c7 44 24 68 00 00 00 	movl   $0x0,0x68(%esp)
  5b9e10:	00 
  5b9e11:	c7 44 24 6c 05 00 00 	movl   $0x5,0x6c(%esp)
  5b9e18:	00 
  5b9e19:	c7 44 24 60 00 00 00 	movl   $0x0,0x60(%esp)
  5b9e20:	00 
  5b9e21:	03 b4 24 64 22 00 00 	add    0x2264(%esp),%esi
  5b9e28:	f7 c6 fc ff ff 00    	test   $0xfffffc,%esi
  5b9e2e:	0f 85 25 01 00 00    	jne    5b9f59 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x89c9>
  5b9e34:	8d 84 24 58 22 00 00 	lea    0x2258(%esp),%eax
  5b9e3b:	89 04 24             	mov    %eax,(%esp)
  5b9e3e:	e8 3d 48 bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5b9e43:	e9 11 01 00 00       	jmp    5b9f59 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x89c9>
  5b9e48:	8b 4c 24 24          	mov    0x24(%esp),%ecx
  5b9e4c:	8b 01                	mov    (%ecx),%eax
  5b9e4e:	8b 40 08             	mov    0x8(%eax),%eax
  5b9e51:	89 0c 24             	mov    %ecx,(%esp)
  5b9e54:	c7 44 24 04 d9 05 00 	movl   $0x5d9,0x4(%esp) # verified field ID: RPM
  5b9e5b:	00 
  5b9e5c:	ff d0                	call   *%eax
  5b9e5e:	89 44 24 04          	mov    %eax,0x4(%esp)
  5b9e62:	8d ac 24 88 68 00 00 	lea    0x6888(%esp),%ebp
  5b9e69:	89 2c 24             	mov    %ebp,(%esp)
  5b9e6c:	c7 44 24 0c e2 36 1a 	movl   $0x3f1a36e2,0xc(%esp)
  5b9e73:	3f 
  5b9e74:	c7 44 24 08 2d 43 1c 	movl   $0xeb1c432d,0x8(%esp)
  5b9e7b:	eb 
  5b9e7c:	e8 af e7 bb ff       	call   178630 <operator*(YYRValue const&, double)@plt>
  5baed5:	89 0c 24             	mov    %ecx,(%esp)
  5baed8:	c7 44 24 04 0a 08 00 	movl   $0x80a,0x4(%esp) # verified field ID: xspeed
  5baedf:	00 
  5baee0:	ff d0                	call   *%eax
  5baee2:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5baee9:	74 db                	je     5baec6 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x9936>
  5baeeb:	89 04 24             	mov    %eax,(%esp)
  5baeee:	e8 ed d6 ba ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5baef3:	dd 9c 24 48 4a 00 00 	fstpl  0x4a48(%esp)
  5baefa:	f2 0f 10 84 24 48 4a 	movsd  0x4a48(%esp),%xmm0
  5baf01:	00 00 
  5baf03:	8b 44 24 18          	mov    0x18(%esp),%eax
  5baf07:	66 0f 2e 00          	ucomisd (%eax),%xmm0
  5baf0b:	0f 86 2d 02 00 00    	jbe    5bb13e <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x9bae>
  5baf11:	c7 44 24 30 c2 01 00 	movl   $0x1c2,0x30(%esp)
  5baf18:	00 
  5baf19:	8b 37                	mov    (%edi),%esi
  5baf1b:	85 f6                	test   %esi,%esi
  5baf1d:	74 4f                	je     5baf6e <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x99de>
  5baf1f:	81 c6 b0 5d 00 00    	add    $0x5db0,%esi
  5baf25:	eb 5f                	jmp    5baf86 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x99f6>
  5baf27:	8b 07                	mov    (%edi),%eax
  5baf29:	8b 40 08             	mov    0x8(%eax),%eax
  5baf2c:	89 3c 24             	mov    %edi,(%esp)
  5baf2f:	c7 44 24 04 ca 04 00 	movl   $0x4ca,0x4(%esp) # verified field ID: no_traction
  5baf36:	00 
  5baf37:	ff d0                	call   *%eax
  5baf39:	89 84 24 e8 02 00 00 	mov    %eax,0x2e8(%esp)
  5baf40:	8b 44 24 38          	mov    0x38(%esp),%eax
  5baf44:	8b 30                	mov    (%eax),%esi
  5baf46:	85 f6                	test   %esi,%esi
  5baf48:	0f 85 b7 f3 ff ff    	jne    5ba305 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8d75>
  5baf4e:	8b 07                	mov    (%edi),%eax
  5baf50:	8b 40 08             	mov    0x8(%eax),%eax
  5baf53:	89 3c 24             	mov    %edi,(%esp)
  5baf56:	c7 44 24 04 35 02 00 	movl   $0x235,0x4(%esp)
  5baf5d:	00 
  5baf5e:	ff d0                	call   *%eax
  5baf60:	89 c6                	mov    %eax,%esi
  5baf62:	8b 84 24 7c 01 00 00 	mov    0x17c(%esp),%eax
  5baf69:	e9 a4 f3 ff ff       	jmp    5ba312 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8d82>
  5baf6e:	8b 4c 24 24          	mov    0x24(%esp),%ecx
  5baf72:	8b 01                	mov    (%ecx),%eax
  5baf74:	8b 40 08             	mov    0x8(%eax),%eax
  5baf77:	89 0c 24             	mov    %ecx,(%esp)
  5baf7a:	c7 44 24 04 db 05 00 	movl   $0x5db,0x4(%esp) # verified field ID: run_acc
  5baf81:	00 
  5baf82:	ff d0                	call   *%eax
  5baf84:	89 c6                	mov    %eax,%esi
  5baf86:	8b 6c 24 24          	mov    0x24(%esp),%ebp
  5baf8a:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5baf8f:	03 46 0c             	add    0xc(%esi),%eax
  5baf92:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5baf97:	75 08                	jne    5bafa1 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x9a11>
  5baf99:	89 34 24             	mov    %esi,(%esp)
  5baf9c:	e8 df 36 bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5bafa1:	c7 46 0c 00 00 00 00 	movl   $0x0,0xc(%esi)
  5bafa8:	c7 46 04 00 00 00 00 	movl   $0x0,0x4(%esi)
  5bafaf:	c7 06 00 00 00 00    	movl   $0x0,(%esi)
  5bafb5:	c7 44 24 30 c3 01 00 	movl   $0x1c3,0x30(%esp)
  5bafbc:	00 
  5bafbd:	8b 3f                	mov    (%edi),%edi
  5bafbf:	85 ff                	test   %edi,%edi
  5bafc1:	74 08                	je     5bafcb <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x9a3b>
  5bafc3:	8d b7 a0 80 00 00    	lea    0x80a0(%edi),%esi
  5bafc9:	eb 1f                	jmp    5bafea <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x9a5a>
  5bafcb:	8b 45 00             	mov    0x0(%ebp),%eax
  5bafce:	8b 40 08             	mov    0x8(%eax),%eax
  5bafd1:	89 2c 24             	mov    %ebp,(%esp)
  5bafd4:	c7 44 24 04 0a 08 00 	movl   $0x80a,0x4(%esp) # verified field ID: xspeed
  5bafdb:	00 
  5bafdc:	ff d0                	call   *%eax
  5bafde:	89 c6                	mov    %eax,%esi
  5bafe0:	8b 44 24 38          	mov    0x38(%esp),%eax
  5bafe4:	8b 38                	mov    (%eax),%edi
  5bafe6:	85 ff                	test   %edi,%edi
  5bafe8:	74 1c                	je     5bb006 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x9a76>
  5bafea:	8d af 10 39 00 00    	lea    0x3910(%edi),%ebp
  5baff0:	81 c7 a0 3a 00 00    	add    $0x3aa0,%edi
  5baff6:	f7 45 0c ff ff ff 00 	testl  $0xffffff,0xc(%ebp)
  5baffd:	75 47                	jne    5bb046 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x9ab6>
  5bafff:	f2 0f 10 45 00       	movsd  0x0(%ebp),%xmm0
  5bb004:	eb 58                	jmp    5bb05e <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x9ace>
  5bb006:	8b 45 00             	mov    0x0(%ebp),%eax
  5bb009:	8b 40 08             	mov    0x8(%eax),%eax
  5bb00c:	89 2c 24             	mov    %ebp,(%esp)
  5bb00f:	c7 44 24 04 91 03 00 	movl   $0x391,0x4(%esp)
  5bb016:	00 
  5bb017:	ff d0                	call   *%eax
  5bb019:	89 c5                	mov    %eax,%ebp
  5bb01b:	8b 44 24 38          	mov    0x38(%esp),%eax
  5bb01f:	8b 38                	mov    (%eax),%edi
  5bb021:	85 ff                	test   %edi,%edi
  5bb023:	75 cb                	jne    5baff0 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x9a60>
  5bb025:	8b 4c 24 24          	mov    0x24(%esp),%ecx
  5bb029:	8b 01                	mov    (%ecx),%eax
  5bb02b:	8b 40 08             	mov    0x8(%eax),%eax
  5bb02e:	89 0c 24             	mov    %ecx,(%esp)
  5bb031:	c7 44 24 04 aa 03 00 	movl   $0x3aa,0x4(%esp)
  5bb038:	00 
  5bb039:	ff d0                	call   *%eax
  5bb03b:	89 c7                	mov    %eax,%edi
  5bb03d:	f7 45 0c ff ff ff 00 	testl  $0xffffff,0xc(%ebp)
  5bb044:	74 b9                	je     5bafff <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x9a6f>
  5bb046:	89 2c 24             	mov    %ebp,(%esp)
  5bb049:	e8 92 d5 ba ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5bb04e:	dd 9c 24 40 4a 00 00 	fstpl  0x4a40(%esp)
  5bb055:	f2 0f 10 84 24 40 4a 	movsd  0x4a40(%esp),%xmm0
  5bb05c:	00 00 
  5bbbe5:	74 de                	je     5bbbc5 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa635>
  5bbbe7:	89 04 24             	mov    %eax,(%esp)
  5bbbea:	e8 f1 c9 ba ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5bbbef:	dd 9c 24 d0 49 00 00 	fstpl  0x49d0(%esp)
  5bbbf6:	f2 0f 10 84 24 d0 49 	movsd  0x49d0(%esp),%xmm0
  5bbbfd:	00 00 
  5bbbff:	f2 0f 58 83 90 0e bb 	addsd  -0x44f170(%ebx),%xmm0
  5bbc06:	ff 
  5bbc07:	8b 44 24 18          	mov    0x18(%esp),%eax
  5bbc0b:	f2 0f 10 08          	movsd  (%eax),%xmm1
  5bbc0f:	66 0f 57 8b 60 09 bb 	xorpd  -0x44f6a0(%ebx),%xmm1
  5bbc16:	ff 
  5bbc17:	66 0f 2e c1          	ucomisd %xmm1,%xmm0
  5bbc1b:	0f 83 e4 01 00 00    	jae    5bbe05 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa875>
  5bbc21:	c7 44 24 30 ed 01 00 	movl   $0x1ed,0x30(%esp)
  5bbc28:	00 
  5bbc29:	8b 37                	mov    (%edi),%esi
  5bbc2b:	85 f6                	test   %esi,%esi
  5bbc2d:	74 08                	je     5bbc37 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa6a7>
  5bbc2f:	81 c6 30 80 00 00    	add    $0x8030,%esi
  5bbc35:	eb 15                	jmp    5bbc4c <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa6bc>
  5bbc37:	8b 45 00             	mov    0x0(%ebp),%eax
  5bbc3a:	8b 40 08             	mov    0x8(%eax),%eax
  5bbc3d:	89 2c 24             	mov    %ebp,(%esp)
  5bbc40:	c7 44 24 04 03 08 00 	movl   $0x803,0x4(%esp) # verified field ID: wind_friction
  5bbc47:	00 
  5bbc48:	ff d0                	call   *%eax
  5bbc4a:	89 c6                	mov    %eax,%esi
  5bbc4c:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5bbc51:	03 46 0c             	add    0xc(%esi),%eax
  5bbc54:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5bbc59:	75 08                	jne    5bbc63 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa6d3>
  5bbc5b:	89 34 24             	mov    %esi,(%esp)
  5bbc5e:	e8 1d 2a bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5bbc63:	c7 46 0c 00 00 00 00 	movl   $0x0,0xc(%esi)
  5bbc6a:	c7 46 04 00 00 f0 3f 	movl   $0x3ff00000,0x4(%esi)
  5bbc71:	c7 06 00 00 00 00    	movl   $0x0,(%esi)
  5bbc77:	c7 44 24 30 ee 01 00 	movl   $0x1ee,0x30(%esp)
  5bbc7e:	00 
  5bbc7f:	8b 37                	mov    (%edi),%esi
  5bbc81:	85 f6                	test   %esi,%esi
  5bbc83:	74 08                	je     5bbc8d <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa6fd>
  5bbc85:	81 c6 20 7f 00 00    	add    $0x7f20,%esi
  5bbc8b:	eb 15                	jmp    5bbca2 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa712>
  5bbc8d:	8b 45 00             	mov    0x0(%ebp),%eax
  5bbc90:	8b 40 08             	mov    0x8(%eax),%eax
  5bbc93:	89 2c 24             	mov    %ebp,(%esp)
  5bbc96:	c7 44 24 04 f2 07 00 	movl   $0x7f2,0x4(%esp) # verified field ID: weight_to_power
  5bbc9d:	00 
  5bbc9e:	ff d0                	call   *%eax
  5bbca0:	89 c6                	mov    %eax,%esi
  5bbca2:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5bbca7:	03 46 0c             	add    0xc(%esi),%eax
  5bbcaa:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5bbcaf:	75 08                	jne    5bbcb9 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa729>
  5bbcb1:	89 34 24             	mov    %esi,(%esp)
  5bbcb4:	e8 c7 29 bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5bbcb9:	c7 46 0c 00 00 00 00 	movl   $0x0,0xc(%esi)
  5bbcc0:	c7 46 04 00 00 f0 3f 	movl   $0x3ff00000,0x4(%esi)
  5bbcc7:	c7 06 00 00 00 00    	movl   $0x0,(%esi)
  5bbccd:	c7 44 24 30 f0 01 00 	movl   $0x1f0,0x30(%esp)
  5bbcd4:	00 
  5bbcd5:	8b 07                	mov    (%edi),%eax
  5bbcd7:	85 c0                	test   %eax,%eax
  5bbcd9:	74 14                	je     5bbcef <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa75f>
  5bbcdb:	05 90 32 00 00       	add    $0x3290,%eax
  5bbce0:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5bbce7:	75 22                	jne    5bbd0b <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa77b>
  5bbce9:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5bbced:	eb 34                	jmp    5bbd23 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa793>
  5bbcef:	8b 45 00             	mov    0x0(%ebp),%eax
  5bbcf2:	8b 40 08             	mov    0x8(%eax),%eax
  5bbcf5:	89 2c 24             	mov    %ebp,(%esp)
  5bbcf8:	c7 44 24 04 29 03 00 	movl   $0x329,0x4(%esp)
  5bbcff:	00 
  5bbd00:	ff d0                	call   *%eax
  5bbd02:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5bbd09:	74 de                	je     5bbce9 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa759>
  5bbd0b:	89 04 24             	mov    %eax,(%esp)
  5bbd0e:	e8 cd c8 ba ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5bbd13:	dd 9c 24 c8 49 00 00 	fstpl  0x49c8(%esp)
  5bbd1a:	f2 0f 10 84 24 c8 49 	movsd  0x49c8(%esp),%xmm0
  5bbd21:	00 00 
  5bbd23:	8b 44 24 18          	mov    0x18(%esp),%eax
  5bbd27:	66 0f 2e 00          	ucomisd (%eax),%xmm0
  5bbd2b:	76 16                	jbe    5bbd43 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa7b3>
  5bbd2d:	c7 44 24 30 f2 01 00 	movl   $0x1f2,0x30(%esp)
  5bbd34:	00 
  5bbd35:	8b 37                	mov    (%edi),%esi
  5bbd37:	85 f6                	test   %esi,%esi
  5bbd39:	74 1e                	je     5bbd59 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa7c9>
  5bbd3b:	81 c6 90 32 00 00    	add    $0x3290,%esi
  5bbd41:	eb 2b                	jmp    5bbd6e <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa7de>
  5bbd43:	c7 44 24 30 f6 01 00 	movl   $0x1f6,0x30(%esp)
  5bbd4a:	00 
  5bbd4b:	8b 37                	mov    (%edi),%esi
  5bbd4d:	85 f6                	test   %esi,%esi
  5bbd4f:	74 6f                	je     5bbdc0 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa830>
  5bbd51:	81 c6 90 32 00 00    	add    $0x3290,%esi
  5bbd57:	eb 7c                	jmp    5bbdd5 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa845>
  5bbd59:	8b 45 00             	mov    0x0(%ebp),%eax
  5bbd5c:	8b 40 08             	mov    0x8(%eax),%eax
  5bbd5f:	89 2c 24             	mov    %ebp,(%esp)
  5bbd62:	c7 44 24 04 29 03 00 	movl   $0x329,0x4(%esp)
  5bbd69:	00 
  5bbd6a:	ff d0                	call   *%eax
  5bbd6c:	89 c6                	mov    %eax,%esi
  5bbd6e:	c7 84 24 bc 07 00 00 	movl   $0x0,0x7bc(%esp)
  5bbd75:	00 00 00 00 
  5bbf04:	89 44 24 04          	mov    %eax,0x4(%esp)
  5bbf08:	8b 84 24 7c 01 00 00 	mov    0x17c(%esp),%eax
  5bbf0f:	89 04 24             	mov    %eax,(%esp)
  5bbf12:	e8 09 ac ba ff       	call   166b20 <YYRValue::operator=(YYRValue const&)@plt>
  5bbf17:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5bbf1c:	8b b4 24 d0 00 00 00 	mov    0xd0(%esp),%esi
  5bbf23:	03 46 0c             	add    0xc(%esi),%eax
  5bbf26:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5bbf2b:	75 08                	jne    5bbf35 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa9a5>
  5bbf2d:	89 34 24             	mov    %esi,(%esp)
  5bbf30:	e8 4b 27 bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5bbf35:	c7 46 08 00 00 00 00 	movl   $0x0,0x8(%esi)
  5bbf3c:	c7 46 0c 05 00 00 00 	movl   $0x5,0xc(%esi)
  5bbf43:	c7 06 00 00 00 00    	movl   $0x0,(%esi)
  5bbf49:	c7 44 24 30 fb 01 00 	movl   $0x1fb,0x30(%esp)
  5bbf50:	00 
  5bbf51:	8b 3f                	mov    (%edi),%edi
  5bbf53:	85 ff                	test   %edi,%edi
  5bbf55:	74 08                	je     5bbf5f <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa9cf>
  5bbf57:	8d b7 30 80 00 00    	lea    0x8030(%edi),%esi
  5bbf5d:	eb 23                	jmp    5bbf82 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa9f2>
  5bbf5f:	8b 45 00             	mov    0x0(%ebp),%eax
  5bbf62:	8b 40 08             	mov    0x8(%eax),%eax
  5bbf65:	89 2c 24             	mov    %ebp,(%esp)
  5bbf68:	c7 44 24 04 03 08 00 	movl   $0x803,0x4(%esp) # verified field ID: wind_friction
  5bbf6f:	00 
  5bbf70:	ff d0                	call   *%eax
  5bbf72:	89 c6                	mov    %eax,%esi
  5bbf74:	8b 44 24 38          	mov    0x38(%esp),%eax
  5bbf78:	8b 38                	mov    (%eax),%edi
  5bbf7a:	85 ff                	test   %edi,%edi
  5bbf7c:	0f 84 19 02 00 00    	je     5bc19b <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xac0b>
  5bbf82:	8d 87 20 7f 00 00    	lea    0x7f20(%edi),%eax
  5bbf88:	89 84 24 78 01 00 00 	mov    %eax,0x178(%esp)
  5bbf8f:	89 f5                	mov    %esi,%ebp
  5bbf91:	81 c7 b0 5d 00 00    	add    $0x5db0,%edi
  5bbf97:	8b 84 24 e8 00 00 00 	mov    0xe8(%esp),%eax
  5bbf9e:	89 44 24 0c          	mov    %eax,0xc(%esp)
  5bbfa2:	8d b4 24 68 21 00 00 	lea    0x2168(%esp),%esi
  5bbfa9:	89 34 24             	mov    %esi,(%esp)
  5bbfac:	c7 44 24 08 99 99 b9 	movl   $0x3fb99999,0x8(%esp)
  5bbfb3:	3f 
  5bbfb4:	c7 44 24 04 9a 99 99 	movl   $0x9999999a,0x4(%esp)
  5bbfbb:	99 
  5bbfbc:	e8 ff eb ba ff       	call   16abc0 <operator+(double, YYRValue const&)@plt>
  5bbfc1:	83 ec 04             	sub    $0x4,%esp
  5bbfc4:	89 6c 24 08          	mov    %ebp,0x8(%esp)
  5bbfc8:	89 74 24 04          	mov    %esi,0x4(%esp)
  5bbfcc:	8d b4 24 d8 67 00 00 	lea    0x67d8(%esp),%esi
  5bbfd3:	89 34 24             	mov    %esi,(%esp)
  5bbfd6:	e8 c5 91 ba ff       	call   1651a0 <operator*(YYRValue const&, YYRValue const&)@plt>
  5bbfdb:	83 ec 04             	sub    $0x4,%esp
  5bbfde:	8b 84 24 78 01 00 00 	mov    0x178(%esp),%eax
  5bbfe5:	89 44 24 08          	mov    %eax,0x8(%esp)
  5bbfe9:	89 74 24 04          	mov    %esi,0x4(%esp)
  5bbfed:	8d ac 24 e8 67 00 00 	lea    0x67e8(%esp),%ebp
  5bbff4:	89 2c 24             	mov    %ebp,(%esp)
  5bbff7:	e8 a4 91 ba ff       	call   1651a0 <operator*(YYRValue const&, YYRValue const&)@plt>
  5bbffc:	83 ec 04             	sub    $0x4,%esp
  5bbfff:	89 6c 24 04          	mov    %ebp,0x4(%esp)
  5bc003:	89 3c 24             	mov    %edi,(%esp)
  5bc006:	e8 15 ab ba ff       	call   166b20 <YYRValue::operator=(YYRValue const&)@plt>
  5bc00b:	bf ff ff ff 00       	mov    $0xffffff,%edi
  5bc010:	8b 84 24 f4 67 00 00 	mov    0x67f4(%esp),%eax
  5bc017:	01 f8                	add    %edi,%eax
  5bc019:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5bc01e:	75 08                	jne    5bc028 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xaa98>
  5bc020:	89 2c 24             	mov    %ebp,(%esp)
  5bc023:	e8 58 26 bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5bc028:	03 bc 24 e4 67 00 00 	add    0x67e4(%esp),%edi
  5bc02f:	f7 c7 fc ff ff 00    	test   $0xfffffc,%edi
  5bc035:	75 08                	jne    5bc03f <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xaaaf>
  5bc037:	89 34 24             	mov    %esi,(%esp)
  5bc03a:	e8 41 26 bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5bc03f:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5bc044:	03 84 24 74 21 00 00 	add    0x2174(%esp),%eax
  5bc04b:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5bc050:	8d 84 24 68 21 00 00 	lea    0x2168(%esp),%eax
  5bc057:	75 08                	jne    5bc061 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xaad1>
  5bc059:	89 04 24             	mov    %eax,(%esp)
  5bc05c:	e8 1f 26 bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5bc061:	c7 44 24 30 fc 01 00 	movl   $0x1fc,0x30(%esp)
  5bc068:	00 
  5bc069:	8b 84 24 e0 01 00 00 	mov    0x1e0(%esp),%eax
  5bc070:	8b 40 0c             	mov    0xc(%eax),%eax
  5bc073:	83 f8 0d             	cmp    $0xd,%eax
  5bc076:	8b 6c 24 24          	mov    0x24(%esp),%ebp
  5bc07a:	8b 7c 24 38          	mov    0x38(%esp),%edi
  5bc07e:	0f 87 80 00 00 00    	ja     5bc104 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xab74>
  5bc084:	b9 81 24 00 00       	mov    $0x2481,%ecx
  5bc089:	0f a3 c1             	bt     %eax,%ecx
  5bc08c:	73 76                	jae    5bc104 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xab74>
  5bc08e:	a9 ff ff ff 00       	test   $0xffffff,%eax
  5bc093:	74 21                	je     5bc0b6 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xab26>
  5bc095:	8b 84 24 e0 01 00 00 	mov    0x1e0(%esp),%eax
  5bc09c:	89 04 24             	mov    %eax,(%esp)
  5bc09f:	e8 3c c5 ba ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5bc0a4:	dd 9c 24 c0 49 00 00 	fstpl  0x49c0(%esp)
  5bc0ab:	f2 0f 10 84 24 c0 49 	movsd  0x49c0(%esp),%xmm0
  5bc0b2:	00 00 
  5bc0b4:	eb 0b                	jmp    5bc0c1 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xab31>
  5bc0b6:	8b 84 24 e0 01 00 00 	mov    0x1e0(%esp),%eax
  5bc0bd:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5bc0c1:	f2 0f 58 83 90 0e bb 	addsd  -0x44f170(%ebx),%xmm0
  5bc0c8:	ff 
  5bc0c9:	66 0f 28 8b 60 09 bb 	movapd -0x44f6a0(%ebx),%xmm1
  5bc0d0:	ff 
  5bc0d1:	66 0f 57 c8          	xorpd  %xmm0,%xmm1
  5bc0d5:	66 0f 57 d2          	xorpd  %xmm2,%xmm2
  5bc53d:	89 2c 24             	mov    %ebp,(%esp)
  5bc540:	e8 3b 21 bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5bc545:	c7 45 08 00 00 00 00 	movl   $0x0,0x8(%ebp)
  5bc54c:	c7 45 0c 05 00 00 00 	movl   $0x5,0xc(%ebp)
  5bc553:	c7 45 00 00 00 00 00 	movl   $0x0,0x0(%ebp)
  5bc55a:	03 b4 24 1c 12 00 00 	add    0x121c(%esp),%esi
  5bc561:	f7 c6 fc ff ff 00    	test   $0xfffffc,%esi
  5bc567:	75 0f                	jne    5bc578 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xafe8>
  5bc569:	8d 84 24 10 12 00 00 	lea    0x1210(%esp),%eax
  5bc570:	89 04 24             	mov    %eax,(%esp)
  5bc573:	e8 08 21 bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5bc578:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5bc57d:	03 84 24 2c 12 00 00 	add    0x122c(%esp),%eax
  5bc584:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5bc589:	8b 6c 24 24          	mov    0x24(%esp),%ebp
  5bc58d:	0f 85 3a f7 ff ff    	jne    5bbccd <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa73d>
  5bc593:	8d 84 24 20 12 00 00 	lea    0x1220(%esp),%eax
  5bc59a:	89 04 24             	mov    %eax,(%esp)
  5bc59d:	e8 de 20 bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5bc5a2:	e9 26 f7 ff ff       	jmp    5bbccd <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa73d>
  5bc5a7:	89 84 24 78 01 00 00 	mov    %eax,0x178(%esp)
  5bc5ae:	8b 45 00             	mov    0x0(%ebp),%eax
  5bc5b1:	8b 40 08             	mov    0x8(%eax),%eax
  5bc5b4:	89 2c 24             	mov    %ebp,(%esp)
  5bc5b7:	c7 44 24 04 03 08 00 	movl   $0x803,0x4(%esp) # verified field ID: wind_friction
  5bc5be:	00 
  5bc5bf:	ff d0                	call   *%eax
  5bc5c1:	89 c5                	mov    %eax,%ebp
  5bc5c3:	8b 37                	mov    (%edi),%esi
  5bc5c5:	85 f6                	test   %esi,%esi
  5bc5c7:	8b 84 24 78 01 00 00 	mov    0x178(%esp),%eax
  5bc5ce:	0f 84 c3 18 00 00    	je     5bde97 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xc907>
  5bc5d4:	8d 8e 20 7f 00 00    	lea    0x7f20(%esi),%ecx
  5bc5da:	89 8c 24 e8 00 00 00 	mov    %ecx,0xe8(%esp)
  5bc5e1:	89 ef                	mov    %ebp,%edi
  5bc5e3:	81 c6 b0 5d 00 00    	add    $0x5db0,%esi
  5bc5e9:	89 44 24 0c          	mov    %eax,0xc(%esp)
  5bc5ed:	8d ac 24 48 21 00 00 	lea    0x2148(%esp),%ebp
  5bc5f4:	89 2c 24             	mov    %ebp,(%esp)
  5bc5f7:	c7 44 24 08 99 99 b9 	movl   $0x3fb99999,0x8(%esp)
  5bc5fe:	3f 
  5bc5ff:	c7 44 24 04 9a 99 99 	movl   $0x9999999a,0x4(%esp)
  5bc606:	99 
  5bc607:	e8 b4 e5 ba ff       	call   16abc0 <operator+(double, YYRValue const&)@plt>
  5bc60c:	83 ec 04             	sub    $0x4,%esp
  5bc60f:	89 6c 24 04          	mov    %ebp,0x4(%esp)
  5bc613:	8d ac 24 58 21 00 00 	lea    0x2158(%esp),%ebp
  5bc61a:	89 2c 24             	mov    %ebp,(%esp)
  5bc61d:	c7 44 24 0c 33 33 e3 	movl   $0x3fe33333,0xc(%esp)
  5bc624:	3f 
  5bc625:	c7 44 24 08 33 33 33 	movl   $0x33333333,0x8(%esp)
  5bc62c:	33 
  5bc62d:	e8 fe bf bb ff       	call   178630 <operator*(YYRValue const&, double)@plt>
  5bc632:	83 ec 04             	sub    $0x4,%esp
  5bc635:	89 7c 24 08          	mov    %edi,0x8(%esp)
  5bc639:	89 6c 24 04          	mov    %ebp,0x4(%esp)
  5bc63d:	8d ac 24 b8 67 00 00 	lea    0x67b8(%esp),%ebp
  5bc644:	89 2c 24             	mov    %ebp,(%esp)
  5bc647:	e8 54 8b ba ff       	call   1651a0 <operator*(YYRValue const&, YYRValue const&)@plt>
  5bc64c:	83 ec 04             	sub    $0x4,%esp
  5bc64f:	8b 84 24 e8 00 00 00 	mov    0xe8(%esp),%eax
  5bc656:	89 44 24 08          	mov    %eax,0x8(%esp)
  5bc65a:	89 6c 24 04          	mov    %ebp,0x4(%esp)
  5bc65e:	8d bc 24 c8 67 00 00 	lea    0x67c8(%esp),%edi
  5bc665:	89 3c 24             	mov    %edi,(%esp)
  5bc668:	e8 33 8b ba ff       	call   1651a0 <operator*(YYRValue const&, YYRValue const&)@plt>
  5bc66d:	83 ec 04             	sub    $0x4,%esp
  5bc670:	89 7c 24 04          	mov    %edi,0x4(%esp)
  5bc674:	89 34 24             	mov    %esi,(%esp)
  5bc677:	e8 a4 a4 ba ff       	call   166b20 <YYRValue::operator=(YYRValue const&)@plt>
  5bc67c:	be ff ff ff 00       	mov    $0xffffff,%esi
  5bc681:	8b 84 24 d4 67 00 00 	mov    0x67d4(%esp),%eax
  5bc688:	01 f0                	add    %esi,%eax
  5bc68a:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5bc68f:	75 08                	jne    5bc699 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb109>
  5bc691:	89 3c 24             	mov    %edi,(%esp)
  5bc694:	e8 e7 1f bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5bc699:	03 b4 24 c4 67 00 00 	add    0x67c4(%esp),%esi
  5bc6a0:	f7 c6 fc ff ff 00    	test   $0xfffffc,%esi
  5bc6a6:	75 08                	jne    5bc6b0 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb120>
  5bc6a8:	89 2c 24             	mov    %ebp,(%esp)
  5bc6ab:	e8 d0 1f bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5bc6b0:	be ff ff ff 00       	mov    $0xffffff,%esi
  5bc6b5:	8b 84 24 64 21 00 00 	mov    0x2164(%esp),%eax
  5bc6bc:	01 f0                	add    %esi,%eax
  5bc6be:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5bc6c3:	8d 84 24 58 21 00 00 	lea    0x2158(%esp),%eax
  5bc6ca:	75 08                	jne    5bc6d4 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb144>
  5bc6cc:	89 04 24             	mov    %eax,(%esp)
  5bc6cf:	e8 ac 1f bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5bc6d4:	03 b4 24 54 21 00 00 	add    0x2154(%esp),%esi
  5bc6db:	f7 c6 fc ff ff 00    	test   $0xfffffc,%esi
  5bc6e1:	8d 84 24 48 21 00 00 	lea    0x2148(%esp),%eax
  5bc6e8:	75 08                	jne    5bc6f2 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb162>
  5bc6ea:	89 04 24             	mov    %eax,(%esp)
  5bc6ed:	e8 8e 1f bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5bc6f2:	8b 6c 24 24          	mov    0x24(%esp),%ebp
  5bc6f6:	8b 7c 24 38          	mov    0x38(%esp),%edi
  5bc6fa:	c7 44 24 30 03 02 00 	movl   $0x203,0x30(%esp)
  5bc701:	00 
  5bc702:	8b 84 24 d8 01 00 00 	mov    0x1d8(%esp),%eax
  5bc709:	8b 40 0c             	mov    0xc(%eax),%eax
  5bc70c:	83 f8 0d             	cmp    $0xd,%eax
  5bc70f:	0f 87 48 05 00 00    	ja     5bcc5d <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb6cd>
  5bc715:	b9 81 24 00 00       	mov    $0x2481,%ecx
  5bc71a:	0f a3 c1             	bt     %eax,%ecx
  5bc71d:	0f 83 3a 05 00 00    	jae    5bcc5d <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb6cd>
  5bc723:	a9 ff ff ff 00       	test   $0xffffff,%eax
  5bc728:	74 21                	je     5bc74b <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb1bb>
  5bc9be:	8b 44 24 38          	mov    0x38(%esp),%eax
  5bc9c2:	8b 30                	mov    (%eax),%esi
  5bc9c4:	85 f6                	test   %esi,%esi
  5bc9c6:	74 0e                	je     5bc9d6 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb446>
  5bc9c8:	8d 8e 00 3e 00 00    	lea    0x3e00(%esi),%ecx
  5bc9ce:	8d be 30 80 00 00    	lea    0x8030(%esi),%edi
  5bc9d4:	eb 56                	jmp    5bca2c <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb49c>
  5bc9d6:	8b 07                	mov    (%edi),%eax
  5bc9d8:	8b 40 08             	mov    0x8(%eax),%eax
  5bc9db:	89 3c 24             	mov    %edi,(%esp)
  5bc9de:	c7 44 24 04 e0 03 00 	movl   $0x3e0,0x4(%esp)
  5bc9e5:	00 
  5bc9e6:	ff d0                	call   *%eax
  5bc9e8:	89 c1                	mov    %eax,%ecx
  5bc9ea:	8b 44 24 38          	mov    0x38(%esp),%eax
  5bc9ee:	8b 30                	mov    (%eax),%esi
  5bc9f0:	85 f6                	test   %esi,%esi
  5bc9f2:	74 08                	je     5bc9fc <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb46c>
  5bc9f4:	8d be 30 80 00 00    	lea    0x8030(%esi),%edi
  5bc9fa:	eb 30                	jmp    5bca2c <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb49c>
  5bc9fc:	89 8c 24 20 02 00 00 	mov    %ecx,0x220(%esp)
  5bca03:	8b 07                	mov    (%edi),%eax
  5bca05:	8b 40 08             	mov    0x8(%eax),%eax
  5bca08:	89 3c 24             	mov    %edi,(%esp)
  5bca0b:	c7 44 24 04 03 08 00 	movl   $0x803,0x4(%esp) # verified field ID: wind_friction
  5bca12:	00 
  5bca13:	ff d0                	call   *%eax
  5bca15:	89 c7                	mov    %eax,%edi
  5bca17:	8b 44 24 38          	mov    0x38(%esp),%eax
  5bca1b:	8b 30                	mov    (%eax),%esi
  5bca1d:	85 f6                	test   %esi,%esi
  5bca1f:	8b 8c 24 20 02 00 00 	mov    0x220(%esp),%ecx
  5bca26:	0f 84 a9 13 00 00    	je     5bddd5 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xc845>
  5bca2c:	89 bc 24 e8 00 00 00 	mov    %edi,0xe8(%esp)
  5bca33:	8d 86 20 7f 00 00    	lea    0x7f20(%esi),%eax
  5bca39:	89 84 24 78 01 00 00 	mov    %eax,0x178(%esp)
  5bca40:	89 ef                	mov    %ebp,%edi
  5bca42:	81 c6 b0 5d 00 00    	add    $0x5db0,%esi
  5bca48:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
  5bca4c:	8d ac 24 18 21 00 00 	lea    0x2118(%esp),%ebp
  5bca53:	89 2c 24             	mov    %ebp,(%esp)
  5bca56:	c7 44 24 08 99 99 b9 	movl   $0x3fb99999,0x8(%esp)
  5bca5d:	3f 
  5bca5e:	c7 44 24 04 9a 99 99 	movl   $0x9999999a,0x4(%esp)
  5bca65:	99 
  5bca66:	e8 55 e1 ba ff       	call   16abc0 <operator+(double, YYRValue const&)@plt>
  5bca6b:	83 ec 04             	sub    $0x4,%esp
  5bca6e:	89 7c 24 08          	mov    %edi,0x8(%esp)
  5bca72:	89 6c 24 04          	mov    %ebp,0x4(%esp)
  5bca76:	8d bc 24 28 21 00 00 	lea    0x2128(%esp),%edi
  5bca7d:	89 3c 24             	mov    %edi,(%esp)
  5bca80:	e8 1b 87 ba ff       	call   1651a0 <operator*(YYRValue const&, YYRValue const&)@plt>
  5bca85:	83 ec 04             	sub    $0x4,%esp
  5bca88:	8b 84 24 e8 00 00 00 	mov    0xe8(%esp),%eax
  5bca8f:	89 44 24 08          	mov    %eax,0x8(%esp)
  5bca93:	89 7c 24 04          	mov    %edi,0x4(%esp)
  5bca97:	8d ac 24 78 67 00 00 	lea    0x6778(%esp),%ebp
  5bca9e:	89 2c 24             	mov    %ebp,(%esp)
  5bcaa1:	e8 fa 86 ba ff       	call   1651a0 <operator*(YYRValue const&, YYRValue const&)@plt>
  5bcaa6:	83 ec 04             	sub    $0x4,%esp
  5bcaa9:	8b 84 24 78 01 00 00 	mov    0x178(%esp),%eax
  5bcab0:	89 44 24 08          	mov    %eax,0x8(%esp)
  5bcab4:	89 6c 24 04          	mov    %ebp,0x4(%esp)
  5bcab8:	8d bc 24 88 67 00 00 	lea    0x6788(%esp),%edi
  5bcabf:	89 3c 24             	mov    %edi,(%esp)
  5bcac2:	e8 d9 86 ba ff       	call   1651a0 <operator*(YYRValue const&, YYRValue const&)@plt>
  5bcac7:	83 ec 04             	sub    $0x4,%esp
  5bcaca:	89 7c 24 04          	mov    %edi,0x4(%esp)
  5bcace:	89 34 24             	mov    %esi,(%esp)
  5bcad1:	e8 4a a0 ba ff       	call   166b20 <YYRValue::operator=(YYRValue const&)@plt>
  5bcad6:	be ff ff ff 00       	mov    $0xffffff,%esi
  5bcadb:	8b 84 24 94 67 00 00 	mov    0x6794(%esp),%eax
  5bcae2:	01 f0                	add    %esi,%eax
  5bcae4:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5bcae9:	75 08                	jne    5bcaf3 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb563>
  5bcaeb:	89 3c 24             	mov    %edi,(%esp)
  5bcaee:	e8 8d 1b bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5bcaf3:	03 b4 24 84 67 00 00 	add    0x6784(%esp),%esi
  5bcafa:	f7 c6 fc ff ff 00    	test   $0xfffffc,%esi
  5bcb00:	75 08                	jne    5bcb0a <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb57a>
  5bcb02:	89 2c 24             	mov    %ebp,(%esp)
  5bcb05:	e8 76 1b bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5bcb0a:	be ff ff ff 00       	mov    $0xffffff,%esi
  5bcb0f:	8b 84 24 34 21 00 00 	mov    0x2134(%esp),%eax
  5bcb16:	01 f0                	add    %esi,%eax
  5bcb18:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5bcb1d:	8d 84 24 28 21 00 00 	lea    0x2128(%esp),%eax
  5bcb24:	75 08                	jne    5bcb2e <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb59e>
  5bcb26:	89 04 24             	mov    %eax,(%esp)
  5bcb29:	e8 52 1b bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5bcb2e:	03 b4 24 24 21 00 00 	add    0x2124(%esp),%esi
  5bcb35:	f7 c6 fc ff ff 00    	test   $0xfffffc,%esi
  5bcb3b:	8d 84 24 18 21 00 00 	lea    0x2118(%esp),%eax
  5bcb42:	75 08                	jne    5bcb4c <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb5bc>
  5bcb44:	89 04 24             	mov    %eax,(%esp)
  5bcb47:	e8 34 1b bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5bcb4c:	c7 44 24 30 07 02 00 	movl   $0x207,0x30(%esp)
  5bcb53:	00 
  5bcb54:	8b 7c 24 38          	mov    0x38(%esp),%edi
  5bcb58:	8b 07                	mov    (%edi),%eax
  5bcb5a:	85 c0                	test   %eax,%eax
  5bcb5c:	74 25                	je     5bcb83 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb5f3>
  5bcb5e:	05 10 1d 00 00       	add    $0x1d10,%eax
  5bcb63:	8b 6c 24 24          	mov    0x24(%esp),%ebp
  5bcb67:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5bcb6e:	75 33                	jne    5bcba3 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb613>
  5bcb70:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5bcb74:	66 0f 2e 83 c0 18 bb 	ucomisd -0x44e740(%ebx),%xmm0
  5bcb7b:	ff 
  5bdf39:	c7 44 24 04 db 05 00 	movl   $0x5db,0x4(%esp) # verified field ID: run_acc
  5bdf40:	00 
  5bdf41:	ff d0                	call   *%eax
  5bdf43:	89 c6                	mov    %eax,%esi
  5bdf45:	89 ef                	mov    %ebp,%edi
  5bdf47:	8b 84 24 78 01 00 00 	mov    0x178(%esp),%eax
  5bdf4e:	e9 96 e6 ff ff       	jmp    5bc5e9 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb059>
  5bdf53:	8b 45 00             	mov    0x0(%ebp),%eax
  5bdf56:	8b 40 08             	mov    0x8(%eax),%eax
  5bdf59:	89 2c 24             	mov    %ebp,(%esp)
  5bdf5c:	c7 44 24 04 bb 01 00 	movl   $0x1bb,0x4(%esp)
  5bdf63:	00 
  5bdf64:	ff d0                	call   *%eax
  5bdf66:	89 c7                	mov    %eax,%edi
  5bdf68:	8b 44 24 38          	mov    0x38(%esp),%eax
  5bdf6c:	8b 00                	mov    (%eax),%eax
  5bdf6e:	85 c0                	test   %eax,%eax
  5bdf70:	74 24                	je     5bdf96 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xca06>
  5bdf72:	05 c0 1b 00 00       	add    $0x1bc0,%eax
  5bdf77:	eb 30                	jmp    5bdfa9 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xca19>
  5bdf79:	8b 4c 24 24          	mov    0x24(%esp),%ecx
  5bdf7d:	8b 01                	mov    (%ecx),%eax
  5bdf7f:	8b 40 08             	mov    0x8(%eax),%eax
  5bdf82:	89 0c 24             	mov    %ecx,(%esp)
  5bdf85:	c7 44 24 04 03 08 00 	movl   $0x803,0x4(%esp) # verified field ID: wind_friction
  5bdf8c:	00 
  5bdf8d:	ff d0                	call   *%eax
  5bdf8f:	89 c6                	mov    %eax,%esi
  5bdf91:	e9 ac e2 ff ff       	jmp    5bc242 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xacb2>
  5bdf96:	8b 45 00             	mov    0x0(%ebp),%eax
  5bdf99:	8b 40 08             	mov    0x8(%eax),%eax
  5bdf9c:	89 2c 24             	mov    %ebp,(%esp)
  5bdf9f:	c7 44 24 04 bc 01 00 	movl   $0x1bc,0x4(%esp)
  5bdfa6:	00 
  5bdfa7:	ff d0                	call   *%eax
  5bdfa9:	89 44 24 04          	mov    %eax,0x4(%esp)
  5bdfad:	8d ac 24 58 67 00 00 	lea    0x6758(%esp),%ebp
  5bdfb4:	89 2c 24             	mov    %ebp,(%esp)
  5bdfb7:	c7 44 24 08 02 00 00 	movl   $0x2,0x8(%esp)
  5bdfbe:	00 
  5bdfbf:	e8 8c cd ba ff       	call   16ad50 <operator-(YYRValue const&, int)@plt>
  5bdfc4:	83 ec 04             	sub    $0x4,%esp
  5bdfc7:	8b 44 24 18          	mov    0x18(%esp),%eax
  5bdfcb:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5bdfcf:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
  5bdfd5:	89 6c 24 04          	mov    %ebp,0x4(%esp)
  5bdfd9:	89 3c 24             	mov    %edi,(%esp)
  5bdfdc:	e8 6f 6b ba ff       	call   164b50 <YYCompareVal(RValue const&, RValue const&, double)@plt>
  5bdfe1:	89 c7                	mov    %eax,%edi
  5bdfe3:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5bdfe8:	03 84 24 64 67 00 00 	add    0x6764(%esp),%eax
  5bdfef:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5bdff4:	75 08                	jne    5bdffe <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xca6e>
  5bdff6:	89 2c 24             	mov    %ebp,(%esp)
  5bdff9:	e8 82 06 bb ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5bdffe:	85 ff                	test   %edi,%edi
  5be000:	8b 6c 24 24          	mov    0x24(%esp),%ebp
  5be004:	8b 7c 24 38          	mov    0x38(%esp),%edi
  5be008:	0f 88 38 04 00 00    	js     5be446 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xceb6>
  5be00e:	8b 07                	mov    (%edi),%eax
  5be010:	85 c0                	test   %eax,%eax
  5be012:	74 14                	je     5be028 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xca98>
  5be014:	05 b0 1b 00 00       	add    $0x1bb0,%eax
  5be019:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5be020:	75 22                	jne    5be044 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xcab4>
  5be022:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5be026:	eb 34                	jmp    5be05c <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xcacc>
  5be028:	8b 45 00             	mov    0x0(%ebp),%eax
  5be02b:	8b 40 08             	mov    0x8(%eax),%eax
  5be02e:	89 2c 24             	mov    %ebp,(%esp)
  5be031:	c7 44 24 04 bb 01 00 	movl   $0x1bb,0x4(%esp)
  5be038:	00 
  5be039:	ff d0                	call   *%eax
  5be03b:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5be042:	74 de                	je     5be022 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xca92>
  5be044:	89 04 24             	mov    %eax,(%esp)
  5be047:	e8 94 a5 ba ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5be04c:	dd 9c 24 18 49 00 00 	fstpl  0x4918(%esp)
  5be053:	f2 0f 10 84 24 18 49 	movsd  0x4918(%esp),%xmm0
  5be05a:	00 00 
  5be05c:	f2 0f 58 83 70 0e bb 	addsd  -0x44f190(%ebx),%xmm0
  5be063:	ff 
  5be064:	8b 44 24 18          	mov    0x18(%esp),%eax
  5be068:	f2 0f 10 08          	movsd  (%eax),%xmm1
  5be06c:	66 0f 57 8b 60 09 bb 	xorpd  -0x44f6a0(%ebx),%xmm1
  5be073:	ff 
  5be074:	66 0f 2e c1          	ucomisd %xmm1,%xmm0
  5be078:	0f 82 c8 03 00 00    	jb     5be446 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xceb6>
  5be07e:	8b 84 24 8c 00 00 00 	mov    0x8c(%esp),%eax
  5be085:	8b 40 04             	mov    0x4(%eax),%eax
  5be088:	8d 8c 24 b8 00 00 00 	lea    0xb8(%esp),%ecx
  5be08f:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
  5be093:	89 44 24 04          	mov    %eax,0x4(%esp)
  5be097:	89 2c 24             	mov    %ebp,(%esp)
  5be09a:	c7 44 24 08 00 00 00 	movl   $0x80000000,0x8(%esp)
  5be0a1:	80 
  5be0a2:	e8 39 15 bb ff       	call   16f5e0 <Variable_GetValue_Direct(YYObjectBase*, int, int, RValue*)@plt>
  5be0a7:	8b 84 24 88 00 00 00 	mov    0x88(%esp),%eax
  5be0ae:	8b 00                	mov    (%eax),%eax
  5be0b0:	83 f8 0d             	cmp    $0xd,%eax
  5be0b3:	77 7e                	ja     5be133 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xcba3>
  5be0b5:	b9 81 24 00 00       	mov    $0x2481,%ecx
  5be0ba:	0f a3 c1             	bt     %eax,%ecx
  5be0bd:	73 74                	jae    5be133 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xcba3>
  5be0bf:	a9 ff ff ff 00       	test   $0xffffff,%eax
  5be0c4:	74 21                	je     5be0e7 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xcb57>
  5be0c6:	8d 84 24 b8 00 00 00 	lea    0xb8(%esp),%eax
  5be0cd:	89 04 24             	mov    %eax,(%esp)
  5be0d0:	e8 0b a5 ba ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5bf527:	ff d0                	call   *%eax
  5bf529:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5bf530:	74 de                	je     5bf510 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xdf80>
  5bf532:	89 04 24             	mov    %eax,(%esp)
  5bf535:	e8 a6 90 ba ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5bf53a:	dd 9c 24 a8 46 00 00 	fstpl  0x46a8(%esp)
  5bf541:	f2 0f 10 84 24 a8 46 	movsd  0x46a8(%esp),%xmm0
  5bf548:	00 00 
  5bf54a:	f2 0f 58 83 90 0e bb 	addsd  -0x44f170(%ebx),%xmm0
  5bf551:	ff 
  5bf552:	8b 44 24 18          	mov    0x18(%esp),%eax
  5bf556:	66 0f 2e 00          	ucomisd (%eax),%xmm0
  5bf55a:	0f 86 53 08 00 00    	jbe    5bfdb3 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe823>
  5bf560:	8b 07                	mov    (%edi),%eax
  5bf562:	85 c0                	test   %eax,%eax
  5bf564:	74 14                	je     5bf57a <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xdfea>
  5bf566:	05 a0 4c 00 00       	add    $0x4ca0,%eax
  5bf56b:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5bf572:	75 22                	jne    5bf596 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe006>
  5bf574:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5bf578:	eb 34                	jmp    5bf5ae <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe01e>
  5bf57a:	8b 45 00             	mov    0x0(%ebp),%eax
  5bf57d:	8b 40 08             	mov    0x8(%eax),%eax
  5bf580:	89 2c 24             	mov    %ebp,(%esp)
  5bf583:	c7 44 24 04 ca 04 00 	movl   $0x4ca,0x4(%esp) # verified field ID: no_traction
  5bf58a:	00 
  5bf58b:	ff d0                	call   *%eax
  5bf58d:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5bf594:	74 de                	je     5bf574 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xdfe4>
  5bf596:	89 04 24             	mov    %eax,(%esp)
  5bf599:	e8 42 90 ba ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5bf59e:	dd 9c 24 a0 46 00 00 	fstpl  0x46a0(%esp)
  5bf5a5:	f2 0f 10 84 24 a0 46 	movsd  0x46a0(%esp),%xmm0
  5bf5ac:	00 00 
  5bf5ae:	f2 0f 58 83 90 0e bb 	addsd  -0x44f170(%ebx),%xmm0
  5bf5b5:	ff 
  5bf5b6:	8b 44 24 18          	mov    0x18(%esp),%eax
  5bf5ba:	f2 0f 10 08          	movsd  (%eax),%xmm1
  5bf5be:	66 0f 57 8b 60 09 bb 	xorpd  -0x44f6a0(%ebx),%xmm1
  5bf5c5:	ff 
  5bf5c6:	66 0f 2e c8          	ucomisd %xmm0,%xmm1
  5bf5ca:	0f 86 e3 07 00 00    	jbe    5bfdb3 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe823>
  5bf5d0:	8b 07                	mov    (%edi),%eax
  5bf5d2:	85 c0                	test   %eax,%eax
  5bf5d4:	74 14                	je     5bf5ea <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe05a>
  5bf5d6:	05 a0 4c 00 00       	add    $0x4ca0,%eax
  5bf5db:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5bf5e2:	75 22                	jne    5bf606 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe076>
  5bf5e4:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5bf5e8:	eb 34                	jmp    5bf61e <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe08e>
  5bf5ea:	8b 45 00             	mov    0x0(%ebp),%eax
  5bf5ed:	8b 40 08             	mov    0x8(%eax),%eax
  5bf5f0:	89 2c 24             	mov    %ebp,(%esp)
  5bf5f3:	c7 44 24 04 ca 04 00 	movl   $0x4ca,0x4(%esp) # verified field ID: no_traction
  5bf5fa:	00 
  5bf5fb:	ff d0                	call   *%eax
  5bf5fd:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5bf604:	74 de                	je     5bf5e4 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe054>
  5bf606:	89 04 24             	mov    %eax,(%esp)
  5bf609:	e8 d2 8f ba ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5bf60e:	dd 9c 24 98 46 00 00 	fstpl  0x4698(%esp)
  5bf615:	f2 0f 10 84 24 98 46 	movsd  0x4698(%esp),%xmm0
  5bf61c:	00 00 
  5bf61e:	8b 44 24 18          	mov    0x18(%esp),%eax
  5bf622:	66 0f 2e 00          	ucomisd (%eax),%xmm0
  5bf626:	0f 86 87 07 00 00    	jbe    5bfdb3 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe823>
  5bf62c:	8b 07                	mov    (%edi),%eax
  5bf62e:	85 c0                	test   %eax,%eax
  5bf630:	74 07                	je     5bf639 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe0a9>
  5bf632:	05 10 39 00 00       	add    $0x3910,%eax
  5bf637:	eb 13                	jmp    5bf64c <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe0bc>
  5bf639:	8b 45 00             	mov    0x0(%ebp),%eax
  5bf63c:	8b 40 08             	mov    0x8(%eax),%eax
  5bf63f:	89 2c 24             	mov    %ebp,(%esp)
  5bf642:	c7 44 24 04 91 03 00 	movl   $0x391,0x4(%esp)
  5bf649:	00 
  5bf64a:	ff d0                	call   *%eax
  5bf64c:	8b 48 0c             	mov    0xc(%eax),%ecx
  5bf64f:	83 f9 0d             	cmp    $0xd,%ecx
  5bf652:	0f 87 5b 07 00 00    	ja     5bfdb3 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe823>
  5bf658:	ba 81 24 00 00       	mov    $0x2481,%edx
  5bf65d:	0f a3 ca             	bt     %ecx,%edx
  5bf660:	0f 83 4d 07 00 00    	jae    5bfdb3 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe823>
  5bf666:	f7 c1 ff ff ff 00    	test   $0xffffff,%ecx
  5bf66c:	74 1a                	je     5bf688 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe0f8>
  5bf66e:	89 04 24             	mov    %eax,(%esp)
  5bf671:	e8 6a 8f ba ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5bf676:	dd 9c 24 90 46 00 00 	fstpl  0x4690(%esp)
  5bf67d:	f2 0f 10 84 24 90 46 	movsd  0x4690(%esp),%xmm0
  5bf684:	00 00 
  5bf686:	eb 04                	jmp    5bf68c <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe0fc>
  5bf688:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5bf68c:	f2 0f 58 83 90 0e bb 	addsd  -0x44f170(%ebx),%xmm0
  5bf693:	ff 
  5bf694:	66 0f 28 8b 60 09 bb 	movapd -0x44f6a0(%ebx),%xmm1
  5bf69b:	ff 
  5bf69c:	66 0f 57 c8          	xorpd  %xmm0,%xmm1
  5bf6a0:	66 0f 57 d2          	xorpd  %xmm2,%xmm2
  5bf6a4:	66 0f 28 d8          	movapd %xmm0,%xmm3
  5bf6a8:	f2 0f c2 da 01       	cmpltsd %xmm2,%xmm3
  5bf6ad:	66 0f 28 d3          	movapd %xmm3,%xmm2
  5bf6b1:	66 0f 55 d0          	andnpd %xmm0,%xmm2
  5bf6b5:	66 0f 54 d9          	andpd  %xmm1,%xmm3
  5bf6b9:	66 0f 56 da          	orpd   %xmm2,%xmm3
  5bf6bd:	8b 44 24 18          	mov    0x18(%esp),%eax
  5bf6c1:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5bf6c5:	66 0f 2e c3          	ucomisd %xmm3,%xmm0
  5bf6c9:	0f 82 e4 06 00 00    	jb     5bfdb3 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe823>
  5bf6cf:	8b 84 24 8c 00 00 00 	mov    0x8c(%esp),%eax
  5bf6d6:	8b 40 04             	mov    0x4(%eax),%eax
  5bf6d9:	8d 8c 24 b8 00 00 00 	lea    0xb8(%esp),%ecx
  5bf6e0:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
  5bf6e4:	89 44 24 04          	mov    %eax,0x4(%esp)
  5bf6e8:	89 2c 24             	mov    %ebp,(%esp)
  5bf6eb:	c7 44 24 08 00 00 00 	movl   $0x80000000,0x8(%esp)
  5bf6f2:	80 
  5bf6f3:	e8 e8 fe ba ff       	call   16f5e0 <Variable_GetValue_Direct(YYObjectBase*, int, int, RValue*)@plt>
  5bf6f8:	8b 84 24 88 00 00 00 	mov    0x88(%esp),%eax
  5bf6ff:	8b 00                	mov    (%eax),%eax
  5bf701:	83 f8 0d             	cmp    $0xd,%eax
  5bf704:	77 76                	ja     5bf77c <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe1ec>
  5bf706:	b9 81 24 00 00       	mov    $0x2481,%ecx
  5bf70b:	0f a3 c1             	bt     %eax,%ecx
  5bf70e:	73 6c                	jae    5bf77c <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe1ec>
  5bf710:	a9 ff ff ff 00       	test   $0xffffff,%eax
  5bf715:	74 21                	je     5bf738 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe1a8>
  5bf717:	8d 84 24 b8 00 00 00 	lea    0xb8(%esp),%eax
  5bf71e:	89 04 24             	mov    %eax,(%esp)
  5bf721:	e8 ba 8e ba ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5bf726:	dd 9c 24 88 46 00 00 	fstpl  0x4688(%esp)
  5bf72d:	f2 0f 10 84 24 88 46 	movsd  0x4688(%esp),%xmm0
  5bf734:	00 00 
  5bf736:	eb 09                	jmp    5bf741 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe1b1>
  5bf738:	f2 0f 10 84 24 b8 00 	movsd  0xb8(%esp),%xmm0
  5bf73f:	00 00 
  5bf741:	66 0f 28 8b 60 09 bb 	movapd -0x44f6a0(%ebx),%xmm1
  5bf748:	ff 
  5bf749:	66 0f 57 c8          	xorpd  %xmm0,%xmm1
  5c119e:	81 c7 c0 5d 00 00    	add    $0x5dc0,%edi
  5c11a4:	f7 46 0c ff ff ff 00 	testl  $0xffffff,0xc(%esi)
  5c11ab:	0f 85 1d 01 00 00    	jne    5c12ce <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xfd3e>
  5c11b1:	f2 0f 10 06          	movsd  (%esi),%xmm0
  5c11b5:	e9 2c 01 00 00       	jmp    5c12e6 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xfd56>
  5c11ba:	8b 45 00             	mov    0x0(%ebp),%eax
  5c11bd:	8b 40 08             	mov    0x8(%eax),%eax
  5c11c0:	89 2c 24             	mov    %ebp,(%esp)
  5c11c3:	c7 44 24 04 0a 08 00 	movl   $0x80a,0x4(%esp) # verified field ID: xspeed
  5c11ca:	00 
  5c11cb:	ff d0                	call   *%eax
  5c11cd:	89 c6                	mov    %eax,%esi
  5c11cf:	8b 44 24 38          	mov    0x38(%esp),%eax
  5c11d3:	8b 38                	mov    (%eax),%edi
  5c11d5:	85 ff                	test   %edi,%edi
  5c11d7:	0f 84 53 02 00 00    	je     5c1430 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xfea0>
  5c11dd:	81 c7 c0 5d 00 00    	add    $0x5dc0,%edi
  5c11e3:	f7 46 0c ff ff ff 00 	testl  $0xffffff,0xc(%esi)
  5c11ea:	0f 85 62 02 00 00    	jne    5c1452 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xfec2>
  5c11f0:	f2 0f 10 06          	movsd  (%esi),%xmm0
  5c11f4:	e9 71 02 00 00       	jmp    5c146a <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xfeda>
  5c11f9:	8b 45 00             	mov    0x0(%ebp),%eax
  5c11fc:	8b 40 08             	mov    0x8(%eax),%eax
  5c11ff:	89 2c 24             	mov    %ebp,(%esp)
  5c1202:	c7 44 24 04 ca 04 00 	movl   $0x4ca,0x4(%esp) # verified field ID: no_traction
  5c1209:	00 
  5c120a:	ff d0                	call   *%eax
  5c120c:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5c1213:	0f 84 c5 fe ff ff    	je     5c10de <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xfb4e>
  5c1219:	89 04 24             	mov    %eax,(%esp)
  5c121c:	e8 bf 73 ba ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5c1221:	dd 9c 24 a8 45 00 00 	fstpl  0x45a8(%esp)
  5c1228:	f2 0f 10 84 24 a8 45 	movsd  0x45a8(%esp),%xmm0
  5c122f:	00 00 
  5c1231:	f2 0f 58 83 90 0e bb 	addsd  -0x44f170(%ebx),%xmm0
  5c1238:	ff 
  5c1239:	8b 44 24 18          	mov    0x18(%esp),%eax
  5c123d:	f2 0f 10 08          	movsd  (%eax),%xmm1
  5c1241:	66 0f 57 8b 60 09 bb 	xorpd  -0x44f6a0(%ebx),%xmm1
  5c1248:	ff 
  5c1249:	66 0f 2e c8          	ucomisd %xmm0,%xmm1
  5c124d:	0f 86 a8 0d 00 00    	jbe    5c1ffb <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x10a6b>
  5c1253:	c7 44 24 30 36 03 00 	movl   $0x336,0x30(%esp)
  5c125a:	00 
  5c125b:	8b 37                	mov    (%edi),%esi
  5c125d:	85 f6                	test   %esi,%esi
  5c125f:	74 08                	je     5c1269 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xfcd9>
  5c1261:	81 c6 a0 4c 00 00    	add    $0x4ca0,%esi
  5c1267:	eb 15                	jmp    5c127e <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xfcee>
  5c1269:	8b 45 00             	mov    0x0(%ebp),%eax
  5c126c:	8b 40 08             	mov    0x8(%eax),%eax
  5c126f:	89 2c 24             	mov    %ebp,(%esp)
  5c1272:	c7 44 24 04 ca 04 00 	movl   $0x4ca,0x4(%esp) # verified field ID: no_traction
  5c1279:	00 
  5c127a:	ff d0                	call   *%eax
  5c127c:	89 c6                	mov    %eax,%esi
  5c127e:	8b 46 0c             	mov    0xc(%esi),%eax
  5c1281:	83 f8 0d             	cmp    $0xd,%eax
  5c1284:	74 11                	je     5c1297 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xfd07>
  5c1286:	83 f8 01             	cmp    $0x1,%eax
  5c1289:	0f 84 b6 0c 00 00    	je     5c1f45 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x109b5>
  5c128f:	85 c0                	test   %eax,%eax
  5c1291:	0f 85 bc 0c 00 00    	jne    5c1f53 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x109c3>
  5c1297:	f2 0f 10 06          	movsd  (%esi),%xmm0
  5c129b:	f2 0f 58 83 30 0d bc 	addsd  -0x43f2d0(%ebx),%xmm0
  5c12a2:	ff 
  5c12a3:	f2 0f 11 06          	movsd  %xmm0,(%esi)
  5c12a7:	e9 a7 0c 00 00       	jmp    5c1f53 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x109c3>
  5c12ac:	8b 45 00             	mov    0x0(%ebp),%eax
  5c12af:	8b 40 08             	mov    0x8(%eax),%eax
  5c12b2:	89 2c 24             	mov    %ebp,(%esp)
  5c12b5:	c7 44 24 04 dc 05 00 	movl   $0x5dc,0x4(%esp)
  5c12bc:	00 
  5c12bd:	ff d0                	call   *%eax
  5c12bf:	89 c7                	mov    %eax,%edi
  5c12c1:	f7 46 0c ff ff ff 00 	testl  $0xffffff,0xc(%esi)
  5c12c8:	0f 84 e3 fe ff ff    	je     5c11b1 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xfc21>
  5c12ce:	89 34 24             	mov    %esi,(%esp)
  5c12d1:	e8 0a 73 ba ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5c12d6:	dd 9c 24 68 45 00 00 	fstpl  0x4568(%esp)
  5c12dd:	f2 0f 10 84 24 68 45 	movsd  0x4568(%esp),%xmm0
  5c12e4:	00 00 
  5c12e6:	f2 0f 11 04 24       	movsd  %xmm0,(%esp)
  5c12eb:	e8 20 56 bb ff       	call   176910 <YYGML_abs(double)@plt>
  5c12f0:	dd 9c 24 60 45 00 00 	fstpl  0x4560(%esp)
  5c12f7:	f2 0f 10 84 24 60 45 	movsd  0x4560(%esp),%xmm0
  5c12fe:	00 00 
  5c1300:	89 7c 24 0c          	mov    %edi,0xc(%esp)
  5c1304:	f2 0f 11 44 24 04    	movsd  %xmm0,0x4(%esp)
  5c130a:	8d ac 24 08 65 00 00 	lea    0x6508(%esp),%ebp
  5c1311:	89 2c 24             	mov    %ebp,(%esp)
  5c1314:	e8 37 9d ba ff       	call   16b050 <operator-(double, YYRValue const&)@plt>
  5c1319:	83 ec 04             	sub    $0x4,%esp
  5c131c:	8b 84 24 80 00 00 00 	mov    0x80(%esp),%eax
  5c1323:	89 84 24 20 13 00 00 	mov    %eax,0x1320(%esp)
  5c132a:	89 ac 24 24 13 00 00 	mov    %ebp,0x1324(%esp)
  5c1331:	8d 84 24 20 13 00 00 	lea    0x1320(%esp),%eax
  5c1338:	89 44 24 08          	mov    %eax,0x8(%esp)
  5c133c:	8d 44 24 60          	lea    0x60(%esp),%eax
  5c1340:	89 04 24             	mov    %eax,(%esp)
  5c1343:	c7 44 24 04 02 00 00 	movl   $0x2,0x4(%esp)
  5c134a:	00 
  5c134b:	e8 60 38 ba ff       	call   164bb0 <YYGML_max(YYRValue&, int, YYRValue**)@plt>
  5c1350:	89 c7                	mov    %eax,%edi
  5c1352:	f7 46 0c ff ff ff 00 	testl  $0xffffff,0xc(%esi)
  5c1359:	74 1a                	je     5c1375 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xfde5>
  5c135b:	89 34 24             	mov    %esi,(%esp)
  5c135e:	e8 7d 72 ba ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5c1363:	dd 9c 24 58 45 00 00 	fstpl  0x4558(%esp)
  5c136a:	f2 0f 10 84 24 58 45 	movsd  0x4558(%esp),%xmm0
  5c1371:	00 00 
  5c1373:	eb 04                	jmp    5c1379 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xfde9>
  5c1375:	f2 0f 10 06          	movsd  (%esi),%xmm0
  5c1379:	f2 0f 11 04 24       	movsd  %xmm0,(%esp)
  5c137e:	e8 ed 4c ba ff       	call   166070 <YYGML_sign(double)@plt>
  5c1383:	dd 9c 24 50 45 00 00 	fstpl  0x4550(%esp)
  5c138a:	f2 0f 10 84 24 50 45 	movsd  0x4550(%esp),%xmm0
  5c1391:	00 00 
  5c1393:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
  5c1399:	89 7c 24 04          	mov    %edi,0x4(%esp)
  5c139d:	8d bc 24 f8 64 00 00 	lea    0x64f8(%esp),%edi
  5c13a4:	89 3c 24             	mov    %edi,(%esp)
  5c13a7:	e8 84 72 bb ff       	call   178630 <operator*(YYRValue const&, double)@plt>
  5c13ac:	83 ec 04             	sub    $0x4,%esp
  5c13af:	89 7c 24 04          	mov    %edi,0x4(%esp)
  5c13b3:	89 34 24             	mov    %esi,(%esp)
  5c13b6:	e8 65 57 ba ff       	call   166b20 <YYRValue::operator=(YYRValue const&)@plt>
  5c13bb:	be ff ff ff 00       	mov    $0xffffff,%esi
  5c13c0:	8b 84 24 04 65 00 00 	mov    0x6504(%esp),%eax
  5c13c7:	01 f0                	add    %esi,%eax
  5c13c9:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5c13ce:	75 08                	jne    5c13d8 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xfe48>
  5c13d0:	89 3c 24             	mov    %edi,(%esp)
  5c13d3:	e8 a8 d2 ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5c13d8:	03 74 24 6c          	add    0x6c(%esp),%esi
  5c13dc:	f7 c6 fc ff ff 00    	test   $0xfffffc,%esi
  5c13e2:	75 0c                	jne    5c13f0 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xfe60>
  5c2475:	66 0f 54 d9          	andpd  %xmm1,%xmm3
  5c2479:	66 0f 56 da          	orpd   %xmm2,%xmm3
  5c247d:	8b 44 24 18          	mov    0x18(%esp),%eax
  5c2481:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5c2485:	66 0f 2e c3          	ucomisd %xmm3,%xmm0
  5c2489:	73 22                	jae    5c24ad <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x10f1d>
  5c248b:	c7 44 24 30 fa 02 00 	movl   $0x2fa,0x30(%esp)
  5c2492:	00 
  5c2493:	8b 07                	mov    (%edi),%eax
  5c2495:	85 c0                	test   %eax,%eax
  5c2497:	0f 84 76 24 00 00    	je     5c4913 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x13383>
  5c249d:	8d b0 a0 4c 00 00    	lea    0x4ca0(%eax),%esi
  5c24a3:	05 90 5d 00 00       	add    $0x5d90,%eax
  5c24a8:	e9 2a 4f 00 00       	jmp    5c73d7 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x15e47>
  5c24ad:	c7 44 24 30 ff 02 00 	movl   $0x2ff,0x30(%esp)
  5c24b4:	00 
  5c24b5:	8b 37                	mov    (%edi),%esi
  5c24b7:	85 f6                	test   %esi,%esi
  5c24b9:	74 08                	je     5c24c3 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x10f33>
  5c24bb:	81 c6 a0 4c 00 00    	add    $0x4ca0,%esi
  5c24c1:	eb 15                	jmp    5c24d8 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x10f48>
  5c24c3:	8b 45 00             	mov    0x0(%ebp),%eax
  5c24c6:	8b 40 08             	mov    0x8(%eax),%eax
  5c24c9:	89 2c 24             	mov    %ebp,(%esp)
  5c24cc:	c7 44 24 04 ca 04 00 	movl   $0x4ca,0x4(%esp) # verified field ID: no_traction
  5c24d3:	00 
  5c24d4:	ff d0                	call   *%eax
  5c24d6:	89 c6                	mov    %eax,%esi
  5c24d8:	8b 46 0c             	mov    0xc(%esi),%eax
  5c24db:	83 f8 0d             	cmp    $0xd,%eax
  5c24de:	74 09                	je     5c24e9 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x10f59>
  5c24e0:	83 f8 01             	cmp    $0x1,%eax
  5c24e3:	74 16                	je     5c24fb <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x10f6b>
  5c24e5:	85 c0                	test   %eax,%eax
  5c24e7:	75 20                	jne    5c2509 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x10f79>
  5c24e9:	f2 0f 10 06          	movsd  (%esi),%xmm0
  5c24ed:	f2 0f 58 83 88 2e bb 	addsd  -0x44d178(%ebx),%xmm0
  5c24f4:	ff 
  5c24f5:	f2 0f 11 06          	movsd  %xmm0,(%esi)
  5c24f9:	eb 0e                	jmp    5c2509 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x10f79>
  5c24fb:	8d 83 dc 17 bb ff    	lea    -0x44e824(%ebx),%eax
  5c2501:	89 04 24             	mov    %eax,(%esp)
  5c2504:	e8 e7 f1 ba ff       	call   1716f0 <YYError(char const*, ...)@plt>
  5c2509:	c7 44 24 30 00 03 00 	movl   $0x300,0x30(%esp)
  5c2510:	00 
  5c2511:	89 b4 24 08 01 00 00 	mov    %esi,0x108(%esp)
  5c2518:	8b 84 24 80 00 00 00 	mov    0x80(%esp),%eax
  5c251f:	89 84 24 0c 01 00 00 	mov    %eax,0x10c(%esp)
  5c2526:	8b 84 24 30 01 00 00 	mov    0x130(%esp),%eax
  5c252d:	89 84 24 10 01 00 00 	mov    %eax,0x110(%esp)
  5c2534:	8b 84 24 c8 00 00 00 	mov    0xc8(%esp),%eax
  5c253b:	8b 40 04             	mov    0x4(%eax),%eax
  5c253e:	8d 8c 24 08 01 00 00 	lea    0x108(%esp),%ecx
  5c2545:	89 4c 24 14          	mov    %ecx,0x14(%esp)
  5c2549:	89 44 24 10          	mov    %eax,0x10(%esp)
  5c254d:	8b 84 24 d0 00 00 00 	mov    0xd0(%esp),%eax
  5c2554:	89 44 24 08          	mov    %eax,0x8(%esp)
  5c2558:	8b 84 24 44 6a 00 00 	mov    0x6a44(%esp),%eax
  5c255f:	89 44 24 04          	mov    %eax,0x4(%esp)
  5c2563:	89 2c 24             	mov    %ebp,(%esp)
  5c2566:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
  5c256d:	00 
  5c256e:	e8 4d 1d bb ff       	call   1742c0 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
  5c2573:	89 44 24 04          	mov    %eax,0x4(%esp)
  5c2577:	89 34 24             	mov    %esi,(%esp)
  5c257a:	e8 a1 45 ba ff       	call   166b20 <YYRValue::operator=(YYRValue const&)@plt>
  5c257f:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5c2584:	8b b4 24 d0 00 00 00 	mov    0xd0(%esp),%esi
  5c258b:	03 46 0c             	add    0xc(%esi),%eax
  5c258e:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5c2593:	75 08                	jne    5c259d <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1100d>
  5c2595:	89 34 24             	mov    %esi,(%esp)
  5c2598:	e8 e3 c0 ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5c259d:	c7 46 08 00 00 00 00 	movl   $0x0,0x8(%esi)
  5c25a4:	c7 46 0c 05 00 00 00 	movl   $0x5,0xc(%esi)
  5c25ab:	c7 06 00 00 00 00    	movl   $0x0,(%esi)
  5c25b1:	c7 44 24 30 02 03 00 	movl   $0x302,0x30(%esp)
  5c25b8:	00 
  5c25b9:	8b 07                	mov    (%edi),%eax
  5c25bb:	85 c0                	test   %eax,%eax
  5c25bd:	74 14                	je     5c25d3 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x11043>
  5c25bf:	05 a0 4c 00 00       	add    $0x4ca0,%eax
  5c25c4:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5c25cb:	75 22                	jne    5c25ef <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1105f>
  5c25cd:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5c25d1:	eb 34                	jmp    5c2607 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x11077>
  5c25d3:	8b 45 00             	mov    0x0(%ebp),%eax
  5c25d6:	8b 40 08             	mov    0x8(%eax),%eax
  5c25d9:	89 2c 24             	mov    %ebp,(%esp)
  5c25dc:	c7 44 24 04 ca 04 00 	movl   $0x4ca,0x4(%esp) # verified field ID: no_traction
  5c25e3:	00 
  5c25e4:	ff d0                	call   *%eax
  5c25e6:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5c25ed:	74 de                	je     5c25cd <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1103d>
  5c25ef:	89 04 24             	mov    %eax,(%esp)
  5c25f2:	e8 e9 5f ba ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5c25f7:	dd 9c 24 e8 44 00 00 	fstpl  0x44e8(%esp)
  5c25fe:	f2 0f 10 84 24 e8 44 	movsd  0x44e8(%esp),%xmm0
  5c2605:	00 00 
  5c2607:	f2 0f 58 83 48 ae bb 	addsd  -0x4451b8(%ebx),%xmm0
  5c260e:	ff 
  5c260f:	8b 44 24 18          	mov    0x18(%esp),%eax
  5c2613:	f2 0f 10 08          	movsd  (%eax),%xmm1
  5c2617:	66 0f 57 8b 60 09 bb 	xorpd  -0x44f6a0(%ebx),%xmm1
  5c261e:	ff 
  5c261f:	66 0f 2e c8          	ucomisd %xmm0,%xmm1
  5c2623:	0f 86 e5 00 00 00    	jbe    5c270e <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1117e>
  5c2629:	8b 07                	mov    (%edi),%eax
  5c262b:	85 c0                	test   %eax,%eax
  5c262d:	74 07                	je     5c2636 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x110a6>
  5c262f:	05 10 39 00 00       	add    $0x3910,%eax
  5c2634:	eb 13                	jmp    5c2649 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x110b9>
  5c2636:	8b 45 00             	mov    0x0(%ebp),%eax
  5c2639:	8b 40 08             	mov    0x8(%eax),%eax
  5c263c:	89 2c 24             	mov    %ebp,(%esp)
  5c263f:	c7 44 24 04 91 03 00 	movl   $0x391,0x4(%esp)
  5c2646:	00 
  5c2647:	ff d0                	call   *%eax
  5c2649:	8b 48 0c             	mov    0xc(%eax),%ecx
  5c264c:	83 f9 0d             	cmp    $0xd,%ecx
  5c264f:	77 67                	ja     5c26b8 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x11128>
  5c2651:	ba 81 24 00 00       	mov    $0x2481,%edx
  5c2656:	0f a3 ca             	bt     %ecx,%edx
  5c2659:	73 5d                	jae    5c26b8 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x11128>
  5c265b:	f7 c1 ff ff ff 00    	test   $0xffffff,%ecx
  5c2661:	74 1a                	je     5c267d <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x110ed>
  5c2663:	89 04 24             	mov    %eax,(%esp)
  5c2666:	e8 75 5f ba ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5c266b:	dd 9c 24 e0 44 00 00 	fstpl  0x44e0(%esp)
  5c2672:	f2 0f 10 84 24 e0 44 	movsd  0x44e0(%esp),%xmm0
  5c2679:	00 00 
  5c267b:	eb 04                	jmp    5c2681 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x110f1>
  5c267d:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5c2681:	66 0f 28 8b 60 09 bb 	movapd -0x44f6a0(%ebx),%xmm1
  5c2688:	ff 
  5c2689:	66 0f 57 c8          	xorpd  %xmm0,%xmm1
  5c268d:	66 0f 57 d2          	xorpd  %xmm2,%xmm2
  5c2691:	66 0f 28 d8          	movapd %xmm0,%xmm3
  5c2695:	f2 0f c2 da 01       	cmpltsd %xmm2,%xmm3
  5c269a:	66 0f 28 d3          	movapd %xmm3,%xmm2
  5c269e:	66 0f 55 d0          	andnpd %xmm0,%xmm2
  5c26a2:	66 0f 54 d9          	andpd  %xmm1,%xmm3
  5c26a6:	66 0f 56 da          	orpd   %xmm2,%xmm3
  5c26aa:	8b 44 24 18          	mov    0x18(%esp),%eax
  5c26ae:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5c26b2:	66 0f 2e c3          	ucomisd %xmm3,%xmm0
  5c26b6:	73 56                	jae    5c270e <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1117e>
  5c26b8:	c7 44 24 30 04 03 00 	movl   $0x304,0x30(%esp)
  5c26bf:	00 
  5c26c0:	8b 37                	mov    (%edi),%esi
  5c26c2:	85 f6                	test   %esi,%esi
  5c26c4:	74 08                	je     5c26ce <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1113e>
  5c26c6:	81 c6 70 7f 00 00    	add    $0x7f70,%esi
  5c26cc:	eb 15                	jmp    5c26e3 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x11153>
  5c26ce:	8b 45 00             	mov    0x0(%ebp),%eax
  5c26d1:	8b 40 08             	mov    0x8(%eax),%eax
  5c26d4:	89 2c 24             	mov    %ebp,(%esp)
  5c26d7:	c7 44 24 04 f7 07 00 	movl   $0x7f7,0x4(%esp) # verified field ID: wheel_spin
  5c26de:	00 
  5c26df:	ff d0                	call   *%eax
  5c26e1:	89 c6                	mov    %eax,%esi
  5c26e3:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5c26e8:	03 46 0c             	add    0xc(%esi),%eax
  5c26eb:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5c26f0:	75 08                	jne    5c26fa <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1116a>
  5c26f2:	89 34 24             	mov    %esi,(%esp)
  5c26f5:	e8 86 bf ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5c26fa:	c7 46 0c 00 00 00 00 	movl   $0x0,0xc(%esi)
  5c2701:	c7 46 04 00 00 e0 3f 	movl   $0x3fe00000,0x4(%esi)
  5c2708:	c7 06 00 00 00 00    	movl   $0x0,(%esi)
  5c270e:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5c2713:	03 84 24 6c 11 00 00 	add    0x116c(%esp),%eax
  5c271a:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5c271f:	75 0f                	jne    5c2730 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x111a0>
  5c2c9d:	c7 44 24 04 0a 08 00 	movl   $0x80a,0x4(%esp) # verified field ID: xspeed
  5c2ca4:	00 
  5c2ca5:	ff d0                	call   *%eax
  5c2ca7:	89 c6                	mov    %eax,%esi
  5c2ca9:	8b 07                	mov    (%edi),%eax
  5c2cab:	85 c0                	test   %eax,%eax
  5c2cad:	74 30                	je     5c2cdf <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1174f>
  5c2caf:	05 a0 4c 00 00       	add    $0x4ca0,%eax
  5c2cb4:	eb 3c                	jmp    5c2cf2 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x11762>
  5c2cb6:	8b 45 00             	mov    0x0(%ebp),%eax
  5c2cb9:	8b 40 08             	mov    0x8(%eax),%eax
  5c2cbc:	89 2c 24             	mov    %ebp,(%esp)
  5c2cbf:	c7 44 24 04 0a 08 00 	movl   $0x80a,0x4(%esp) # verified field ID: xspeed
  5c2cc6:	00 
  5c2cc7:	ff d0                	call   *%eax
  5c2cc9:	89 c6                	mov    %eax,%esi
  5c2ccb:	8b 07                	mov    (%edi),%eax
  5c2ccd:	85 c0                	test   %eax,%eax
  5c2ccf:	0f 84 82 04 00 00    	je     5c3157 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x11bc7>
  5c2cd5:	05 10 2d 00 00       	add    $0x2d10,%eax
  5c2cda:	e9 8b 04 00 00       	jmp    5c316a <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x11bda>
  5c2cdf:	8b 45 00             	mov    0x0(%ebp),%eax
  5c2ce2:	8b 40 08             	mov    0x8(%eax),%eax
  5c2ce5:	89 2c 24             	mov    %ebp,(%esp)
  5c2ce8:	c7 44 24 04 ca 04 00 	movl   $0x4ca,0x4(%esp) # verified field ID: no_traction
  5c2cef:	00 
  5c2cf0:	ff d0                	call   *%eax
  5c2cf2:	89 84 24 a4 16 00 00 	mov    %eax,0x16a4(%esp)
  5c2cf9:	8b 84 24 80 00 00 00 	mov    0x80(%esp),%eax
  5c2d00:	89 84 24 a8 16 00 00 	mov    %eax,0x16a8(%esp)
  5c2d07:	8b 84 24 30 01 00 00 	mov    0x130(%esp),%eax
  5c2d0e:	89 84 24 ac 16 00 00 	mov    %eax,0x16ac(%esp)
  5c2d15:	8b 84 24 c8 00 00 00 	mov    0xc8(%esp),%eax
  5c2d1c:	8b 40 04             	mov    0x4(%eax),%eax
  5c2d1f:	8d 8c 24 a4 16 00 00 	lea    0x16a4(%esp),%ecx
  5c2d26:	89 4c 24 14          	mov    %ecx,0x14(%esp)
  5c2d2a:	89 44 24 10          	mov    %eax,0x10(%esp)
  5c2d2e:	8d 44 24 60          	lea    0x60(%esp),%eax
  5c2d32:	89 44 24 08          	mov    %eax,0x8(%esp)
  5c2d36:	8b 84 24 44 6a 00 00 	mov    0x6a44(%esp),%eax
  5c2d3d:	89 44 24 04          	mov    %eax,0x4(%esp)
  5c2d41:	89 2c 24             	mov    %ebp,(%esp)
  5c2d44:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
  5c2d4b:	00 
  5c2d4c:	e8 6f 15 bb ff       	call   1742c0 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
  5c2d51:	89 44 24 08          	mov    %eax,0x8(%esp)
  5c2d55:	89 74 24 04          	mov    %esi,0x4(%esp)
  5c2d59:	8d b4 24 28 20 00 00 	lea    0x2028(%esp),%esi
  5c2d60:	89 34 24             	mov    %esi,(%esp)
  5c2d63:	e8 38 24 ba ff       	call   1651a0 <operator*(YYRValue const&, YYRValue const&)@plt>
  5c2d68:	83 ec 04             	sub    $0x4,%esp
  5c2d6b:	8b 84 24 34 20 00 00 	mov    0x2034(%esp),%eax
  5c2d72:	a9 ff ff ff 00       	test   $0xffffff,%eax
  5c2d77:	74 21                	je     5c2d9a <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1180a>
  5c2d79:	89 34 24             	mov    %esi,(%esp)
  5c2d7c:	e8 5f 58 ba ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5c2d81:	dd 9c 24 88 44 00 00 	fstpl  0x4488(%esp)
  5c2d88:	f2 0f 10 84 24 88 44 	movsd  0x4488(%esp),%xmm0
  5c2d8f:	00 00 
  5c2d91:	8b 84 24 34 20 00 00 	mov    0x2034(%esp),%eax
  5c2d98:	eb 09                	jmp    5c2da3 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x11813>
  5c2d9a:	f2 0f 10 84 24 28 20 	movsd  0x2028(%esp),%xmm0
  5c2da1:	00 00 
  5c2da3:	8b 4c 24 18          	mov    0x18(%esp),%ecx
  5c2da7:	f2 0f 10 09          	movsd  (%ecx),%xmm1
  5c2dab:	05 ff ff ff 00       	add    $0xffffff,%eax
  5c2db0:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5c2db5:	75 2c                	jne    5c2de3 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x11853>
  5c2db7:	89 34 24             	mov    %esi,(%esp)
  5c2dba:	f2 0f 11 84 24 e8 00 	movsd  %xmm0,0xe8(%esp)
  5c2dc1:	00 00 
  5c2dc3:	f2 0f 11 8c 24 80 01 	movsd  %xmm1,0x180(%esp)
  5c2dca:	00 00 
  5c2dcc:	e8 af b8 ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5c2dd1:	f2 0f 10 8c 24 80 01 	movsd  0x180(%esp),%xmm1
  5c2dd8:	00 00 
  5c2dda:	f2 0f 10 84 24 e8 00 	movsd  0xe8(%esp),%xmm0
  5c2de1:	00 00 
  5c2de3:	f2 0f 58 83 50 0e bb 	addsd  -0x44f1b0(%ebx),%xmm0
  5c2dea:	ff 
  5c2deb:	66 0f 2e c1          	ucomisd %xmm1,%xmm0
  5c2def:	0f 86 88 00 00 00    	jbe    5c2e7d <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x118ed>
  5c2df5:	8b 07                	mov    (%edi),%eax
  5c2df7:	85 c0                	test   %eax,%eax
  5c2df9:	74 14                	je     5c2e0f <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1187f>
  5c2dfb:	05 d0 1c 00 00       	add    $0x1cd0,%eax
  5c2e00:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5c2e07:	75 22                	jne    5c2e2b <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1189b>
  5c2e09:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5c2e0d:	eb 34                	jmp    5c2e43 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x118b3>
  5c2e0f:	8b 45 00             	mov    0x0(%ebp),%eax
  5c2e12:	8b 40 08             	mov    0x8(%eax),%eax
  5c2e15:	89 2c 24             	mov    %ebp,(%esp)
  5c2e18:	c7 44 24 04 cd 01 00 	movl   $0x1cd,0x4(%esp)
  5c2e1f:	00 
  5c2e20:	ff d0                	call   *%eax
  5c2e22:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5c2e29:	74 de                	je     5c2e09 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x11879>
  5c2e2b:	89 04 24             	mov    %eax,(%esp)
  5c2e2e:	e8 ad 57 ba ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5c2e33:	dd 9c 24 80 44 00 00 	fstpl  0x4480(%esp)
  5c2e3a:	f2 0f 10 84 24 80 44 	movsd  0x4480(%esp),%xmm0
  5c2e41:	00 00 
  5c2e43:	f2 0f 58 83 40 0d bc 	addsd  -0x43f2c0(%ebx),%xmm0
  5c2e4a:	ff 
  5c2e4b:	8b 44 24 18          	mov    0x18(%esp),%eax
  5c2e4f:	f2 0f 10 08          	movsd  (%eax),%xmm1
  5c2e53:	66 0f 57 8b 60 09 bb 	xorpd  -0x44f6a0(%ebx),%xmm1
  5c2e5a:	ff 
  5c2eb0:	00 
  5c2eb1:	c7 44 24 30 2b 03 00 	movl   $0x32b,0x30(%esp)
  5c2eb8:	00 
  5c2eb9:	8b 07                	mov    (%edi),%eax
  5c2ebb:	85 c0                	test   %eax,%eax
  5c2ebd:	74 0d                	je     5c2ecc <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1193c>
  5c2ebf:	8d b0 a0 80 00 00    	lea    0x80a0(%eax),%esi
  5c2ec5:	05 a0 4c 00 00       	add    $0x4ca0,%eax
  5c2eca:	eb 35                	jmp    5c2f01 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x11971>
  5c2ecc:	8b 45 00             	mov    0x0(%ebp),%eax
  5c2ecf:	8b 40 08             	mov    0x8(%eax),%eax
  5c2ed2:	89 2c 24             	mov    %ebp,(%esp)
  5c2ed5:	c7 44 24 04 0a 08 00 	movl   $0x80a,0x4(%esp) # verified field ID: xspeed
  5c2edc:	00 
  5c2edd:	ff d0                	call   *%eax
  5c2edf:	89 c6                	mov    %eax,%esi
  5c2ee1:	8b 07                	mov    (%edi),%eax
  5c2ee3:	85 c0                	test   %eax,%eax
  5c2ee5:	74 07                	je     5c2eee <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1195e>
  5c2ee7:	05 a0 4c 00 00       	add    $0x4ca0,%eax
  5c2eec:	eb 13                	jmp    5c2f01 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x11971>
  5c2eee:	8b 45 00             	mov    0x0(%ebp),%eax
  5c2ef1:	8b 40 08             	mov    0x8(%eax),%eax
  5c2ef4:	89 2c 24             	mov    %ebp,(%esp)
  5c2ef7:	c7 44 24 04 ca 04 00 	movl   $0x4ca,0x4(%esp) # verified field ID: no_traction
  5c2efe:	00 
  5c2eff:	ff d0                	call   *%eax
  5c2f01:	89 84 24 98 16 00 00 	mov    %eax,0x1698(%esp)
  5c2f08:	8b 84 24 80 00 00 00 	mov    0x80(%esp),%eax
  5c2f0f:	89 84 24 9c 16 00 00 	mov    %eax,0x169c(%esp)
  5c2f16:	8b 84 24 30 01 00 00 	mov    0x130(%esp),%eax
  5c2f1d:	89 84 24 a0 16 00 00 	mov    %eax,0x16a0(%esp)
  5c2f24:	8b 84 24 c8 00 00 00 	mov    0xc8(%esp),%eax
  5c2f2b:	8b 40 04             	mov    0x4(%eax),%eax
  5c2f2e:	8d 8c 24 98 16 00 00 	lea    0x1698(%esp),%ecx
  5c2f35:	89 4c 24 14          	mov    %ecx,0x14(%esp)
  5c2f39:	89 44 24 10          	mov    %eax,0x10(%esp)
  5c2f3d:	8d 44 24 60          	lea    0x60(%esp),%eax
  5c2f41:	89 44 24 08          	mov    %eax,0x8(%esp)
  5c2f45:	8b 84 24 44 6a 00 00 	mov    0x6a44(%esp),%eax
  5c2f4c:	89 44 24 04          	mov    %eax,0x4(%esp)
  5c2f50:	89 2c 24             	mov    %ebp,(%esp)
  5c2f53:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
  5c2f5a:	00 
  5c2f5b:	e8 60 13 bb ff       	call   1742c0 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
  5c2f60:	89 44 24 08          	mov    %eax,0x8(%esp)
  5c2f64:	89 74 24 04          	mov    %esi,0x4(%esp)
  5c2f68:	8d b4 24 18 20 00 00 	lea    0x2018(%esp),%esi
  5c2f6f:	89 34 24             	mov    %esi,(%esp)
  5c2f72:	e8 29 22 ba ff       	call   1651a0 <operator*(YYRValue const&, YYRValue const&)@plt>
  5c2f77:	83 ec 04             	sub    $0x4,%esp
  5c2f7a:	8b 84 24 24 20 00 00 	mov    0x2024(%esp),%eax
  5c2f81:	a9 ff ff ff 00       	test   $0xffffff,%eax
  5c2f86:	74 21                	je     5c2fa9 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x11a19>
  5c2f88:	89 34 24             	mov    %esi,(%esp)
  5c2f8b:	e8 50 56 ba ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5c2f90:	dd 9c 24 78 44 00 00 	fstpl  0x4478(%esp)
  5c2f97:	f2 0f 10 84 24 78 44 	movsd  0x4478(%esp),%xmm0
  5c2f9e:	00 00 
  5c2fa0:	8b 84 24 24 20 00 00 	mov    0x2024(%esp),%eax
  5c2fa7:	eb 09                	jmp    5c2fb2 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x11a22>
  5c2fa9:	f2 0f 10 84 24 18 20 	movsd  0x2018(%esp),%xmm0
  5c2fb0:	00 00 
  5c2fb2:	8b 4c 24 18          	mov    0x18(%esp),%ecx
  5c2fb6:	f2 0f 10 09          	movsd  (%ecx),%xmm1
  5c2fba:	05 ff ff ff 00       	add    $0xffffff,%eax
  5c2fbf:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5c2fc4:	75 2c                	jne    5c2ff2 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x11a62>
  5c2fc6:	89 34 24             	mov    %esi,(%esp)
  5c2fc9:	f2 0f 11 84 24 e8 00 	movsd  %xmm0,0xe8(%esp)
  5c2fd0:	00 00 
  5c2fd2:	66 0f 29 8c 24 80 01 	movapd %xmm1,0x180(%esp)
  5c2fd9:	00 00 
  5c2fdb:	e8 a0 b6 ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5c2fe0:	66 0f 28 8c 24 80 01 	movapd 0x180(%esp),%xmm1
  5c2fe7:	00 00 
  5c2fe9:	f2 0f 10 84 24 e8 00 	movsd  0xe8(%esp),%xmm0
  5c2ff0:	00 00 
  5c2ff2:	f2 0f 58 83 50 0e bb 	addsd  -0x44f1b0(%ebx),%xmm0
  5c2ff9:	ff 
  5c2ffa:	66 0f 57 8b 60 09 bb 	xorpd  -0x44f6a0(%ebx),%xmm1
  5c3001:	ff 
  5c3002:	66 0f 2e c8          	ucomisd %xmm0,%xmm1
  5c3006:	0f 86 26 01 00 00    	jbe    5c3132 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x11ba2>
  5c300c:	c7 44 24 30 2d 03 00 	movl   $0x32d,0x30(%esp)
  5c3013:	00 
  5c3014:	8b 37                	mov    (%edi),%esi
  5c3016:	85 f6                	test   %esi,%esi
  5c3018:	74 08                	je     5c3022 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x11a92>
  5c301a:	81 c6 d0 1c 00 00    	add    $0x1cd0,%esi
  5c3020:	eb 15                	jmp    5c3037 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x11aa7>
  5c3022:	8b 45 00             	mov    0x0(%ebp),%eax
  5c3025:	8b 40 08             	mov    0x8(%eax),%eax
  5c3028:	89 2c 24             	mov    %ebp,(%esp)
  5c302b:	c7 44 24 04 cd 01 00 	movl   $0x1cd,0x4(%esp)
  5c3032:	00 
  5c3033:	ff d0                	call   *%eax
  5c3035:	89 c6                	mov    %eax,%esi
  5c3037:	c7 84 24 6c 07 00 00 	movl   $0x0,0x76c(%esp)
  5c303e:	00 00 00 00 
  5c3042:	c7 84 24 64 07 00 00 	movl   $0x3ff00000,0x764(%esp)
  5c3049:	00 00 f0 3f 
  5c304d:	c7 84 24 60 07 00 00 	movl   $0x0,0x760(%esp)
  5c3054:	00 00 00 00 
  5c3058:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5c305d:	23 46 0c             	and    0xc(%esi),%eax
  5c3060:	83 f8 0d             	cmp    $0xd,%eax
  5c3063:	0f 87 8a 00 00 00    	ja     5c30f3 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x11b63>
  5c3069:	8b 84 83 8c 13 bc ff 	mov    -0x43ec74(%ebx,%eax,4),%eax
  5c48b0:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
  5c48b4:	89 44 24 04          	mov    %eax,0x4(%esp)
  5c48b8:	89 2c 24             	mov    %ebp,(%esp)
  5c48bb:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
  5c48c2:	00 
  5c48c3:	e8 e8 57 ba ff       	call   16a0b0 <Variable_SetValue_Direct(YYObjectBase*, int, int, RValue*)@plt>
  5c48c8:	be ff ff ff 00       	mov    $0xffffff,%esi
  5c48cd:	8b 84 24 5c 11 00 00 	mov    0x115c(%esp),%eax
  5c48d4:	01 f0                	add    %esi,%eax
  5c48d6:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5c48db:	75 0f                	jne    5c48ec <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1335c>
  5c48dd:	8d 84 24 50 11 00 00 	lea    0x1150(%esp),%eax
  5c48e4:	89 04 24             	mov    %eax,(%esp)
  5c48e7:	e8 94 9d ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5c48ec:	03 b4 24 04 04 00 00 	add    0x404(%esp),%esi
  5c48f3:	f7 c6 fc ff ff 00    	test   $0xfffffc,%esi
  5c48f9:	0f 85 a0 05 00 00    	jne    5c4e9f <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1390f>
  5c48ff:	8d 84 24 f8 03 00 00 	lea    0x3f8(%esp),%eax
  5c4906:	89 04 24             	mov    %eax,(%esp)
  5c4909:	e8 72 9d ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5c490e:	e9 8c 05 00 00       	jmp    5c4e9f <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1390f>
  5c4913:	8b 45 00             	mov    0x0(%ebp),%eax
  5c4916:	8b 40 08             	mov    0x8(%eax),%eax
  5c4919:	89 2c 24             	mov    %ebp,(%esp)
  5c491c:	c7 44 24 04 ca 04 00 	movl   $0x4ca,0x4(%esp) # verified field ID: no_traction
  5c4923:	00 
  5c4924:	ff d0                	call   *%eax
  5c4926:	89 c6                	mov    %eax,%esi
  5c4928:	8b 07                	mov    (%edi),%eax
  5c492a:	85 c0                	test   %eax,%eax
  5c492c:	0f 84 92 2a 00 00    	je     5c73c4 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x15e34>
  5c4932:	05 90 5d 00 00       	add    $0x5d90,%eax
  5c4937:	e9 9b 2a 00 00       	jmp    5c73d7 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x15e47>
  5c493c:	8b 45 00             	mov    0x0(%ebp),%eax
  5c493f:	8b 40 08             	mov    0x8(%eax),%eax
  5c4942:	89 2c 24             	mov    %ebp,(%esp)
  5c4945:	c7 44 24 04 0a 08 00 	movl   $0x80a,0x4(%esp) # verified field ID: xspeed
  5c494c:	00 
  5c494d:	ff d0                	call   *%eax
  5c494f:	89 c6                	mov    %eax,%esi
  5c4951:	8b bb 88 e3 ff ff    	mov    -0x1c78(%ebx),%edi
  5c4957:	8b 47 04             	mov    0x4(%edi),%eax
  5c495a:	8d 8c 24 10 02 00 00 	lea    0x210(%esp),%ecx
  5c4961:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
  5c4965:	89 44 24 04          	mov    %eax,0x4(%esp)
  5c4969:	89 2c 24             	mov    %ebp,(%esp)
  5c496c:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
  5c4973:	00 
  5c4974:	e8 67 ac ba ff       	call   16f5e0 <Variable_GetValue_Direct(YYObjectBase*, int, int, RValue*)@plt>
  5c4979:	89 b4 24 9c 0a 00 00 	mov    %esi,0xa9c(%esp)
  5c4980:	8b 83 e4 65 ff ff    	mov    -0x9a1c(%ebx),%eax
  5c4986:	8b 40 04             	mov    0x4(%eax),%eax
  5c4989:	8d 8c 24 9c 0a 00 00 	lea    0xa9c(%esp),%ecx
  5c4990:	89 4c 24 14          	mov    %ecx,0x14(%esp)
  5c4994:	89 44 24 10          	mov    %eax,0x10(%esp)
  5c4998:	8d 44 24 60          	lea    0x60(%esp),%eax
  5c499c:	89 44 24 08          	mov    %eax,0x8(%esp)
  5c49a0:	8b 84 24 44 6a 00 00 	mov    0x6a44(%esp),%eax
  5c49a7:	89 44 24 04          	mov    %eax,0x4(%esp)
  5c49ab:	89 2c 24             	mov    %ebp,(%esp)
  5c49ae:	c7 44 24 0c 01 00 00 	movl   $0x1,0xc(%esp)
  5c49b5:	00 
  5c49b6:	e8 05 f9 ba ff       	call   1742c0 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
  5c49bb:	89 44 24 08          	mov    %eax,0x8(%esp)
  5c49bf:	8d b4 24 f8 63 00 00 	lea    0x63f8(%esp),%esi
  5c49c6:	89 34 24             	mov    %esi,(%esp)
  5c49c9:	c7 44 24 04 0a 00 00 	movl   $0xa,0x4(%esp)
  5c49d0:	00 
  5c49d1:	e8 4a 57 ba ff       	call   16a120 <operator+(int, YYRValue const&)@plt>
  5c49d6:	83 ec 04             	sub    $0x4,%esp
  5c49d9:	89 74 24 04          	mov    %esi,0x4(%esp)
  5c49dd:	8d 84 24 10 02 00 00 	lea    0x210(%esp),%eax
  5c49e4:	89 04 24             	mov    %eax,(%esp)
  5c49e7:	e8 04 33 bb ff       	call   177cf0 <YYRValue::operator+=(YYRValue const&)@plt>
  5c49ec:	bd ff ff ff 00       	mov    $0xffffff,%ebp
  5c49f1:	8b 84 24 04 64 00 00 	mov    0x6404(%esp),%eax
  5c49f8:	01 e8                	add    %ebp,%eax
  5c49fa:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5c49ff:	75 08                	jne    5c4a09 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x13479>
  5c4a01:	89 34 24             	mov    %esi,(%esp)
  5c4a04:	e8 77 9c ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5c4a09:	03 6c 24 6c          	add    0x6c(%esp),%ebp
  5c4a0d:	f7 c5 fc ff ff 00    	test   $0xfffffc,%ebp
  5c4a13:	75 0c                	jne    5c4a21 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x13491>
  5c4a15:	8d 44 24 60          	lea    0x60(%esp),%eax
  5c4a19:	89 04 24             	mov    %eax,(%esp)
  5c4a1c:	e8 5f 9c ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5c4a21:	c7 44 24 68 00 00 00 	movl   $0x0,0x68(%esp)
  5c4a28:	00 
  5c4a29:	c7 44 24 6c 05 00 00 	movl   $0x5,0x6c(%esp)
  5c4a30:	00 
  5c4a31:	c7 44 24 60 00 00 00 	movl   $0x0,0x60(%esp)
  5c4a38:	00 
  5c4a39:	8b 47 04             	mov    0x4(%edi),%eax
  5c4a3c:	8d 8c 24 10 02 00 00 	lea    0x210(%esp),%ecx
  5c4a43:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
  5c4a47:	89 44 24 04          	mov    %eax,0x4(%esp)
  5c4a4b:	8b 6c 24 24          	mov    0x24(%esp),%ebp
  5c4a4f:	89 2c 24             	mov    %ebp,(%esp)
  5c4a52:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
  5c4a59:	00 
  5c4a5a:	e8 51 56 ba ff       	call   16a0b0 <Variable_SetValue_Direct(YYObjectBase*, int, int, RValue*)@plt>
  5c4a5f:	e9 3b 04 00 00       	jmp    5c4e9f <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1390f>
  5c4a64:	89 8c 24 2c 02 00 00 	mov    %ecx,0x22c(%esp)
  5c4a6b:	8b 45 00             	mov    0x0(%ebp),%eax
  5c4a6e:	8b 40 08             	mov    0x8(%eax),%eax
  5c4a71:	89 2c 24             	mov    %ebp,(%esp)
  5c4a74:	c7 44 24 04 eb 02 00 	movl   $0x2eb,0x4(%esp)
  5c4a7b:	00 
  5c9ee7:	75 08                	jne    5c9ef1 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18961>
  5c9ee9:	89 34 24             	mov    %esi,(%esp)
  5c9eec:	e8 8f 47 ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5c9ef1:	c7 46 08 00 00 00 00 	movl   $0x0,0x8(%esi)
  5c9ef8:	c7 46 0c 05 00 00 00 	movl   $0x5,0xc(%esi)
  5c9eff:	c7 06 00 00 00 00    	movl   $0x0,(%esi)
  5c9f05:	c7 44 24 30 8d 02 00 	movl   $0x28d,0x30(%esp)
  5c9f0c:	00 
  5c9f0d:	8b 7c 24 38          	mov    0x38(%esp),%edi
  5c9f11:	8b 07                	mov    (%edi),%eax
  5c9f13:	85 c0                	test   %eax,%eax
  5c9f15:	74 28                	je     5c9f3f <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x189af>
  5c9f17:	05 a0 4c 00 00       	add    $0x4ca0,%eax
  5c9f1c:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5c9f23:	74 3a                	je     5c9f5f <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x189cf>
  5c9f25:	89 04 24             	mov    %eax,(%esp)
  5c9f28:	e8 b3 e6 b9 ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5c9f2d:	dd 9c 24 40 47 00 00 	fstpl  0x4740(%esp)
  5c9f34:	f2 0f 10 84 24 40 47 	movsd  0x4740(%esp),%xmm0
  5c9f3b:	00 00 
  5c9f3d:	eb 24                	jmp    5c9f63 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x189d3>
  5c9f3f:	8b 45 00             	mov    0x0(%ebp),%eax
  5c9f42:	8b 40 08             	mov    0x8(%eax),%eax
  5c9f45:	89 2c 24             	mov    %ebp,(%esp)
  5c9f48:	c7 44 24 04 ca 04 00 	movl   $0x4ca,0x4(%esp) # verified field ID: no_traction
  5c9f4f:	00 
  5c9f50:	ff d0                	call   *%eax
  5c9f52:	8b 7c 24 38          	mov    0x38(%esp),%edi
  5c9f56:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5c9f5d:	75 c6                	jne    5c9f25 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18995>
  5c9f5f:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5c9f63:	f2 0f 58 83 90 0e bb 	addsd  -0x44f170(%ebx),%xmm0
  5c9f6a:	ff 
  5c9f6b:	8b 44 24 18          	mov    0x18(%esp),%eax
  5c9f6f:	f2 0f 10 08          	movsd  (%eax),%xmm1
  5c9f73:	66 0f 57 8b 60 09 bb 	xorpd  -0x44f6a0(%ebx),%xmm1
  5c9f7a:	ff 
  5c9f7b:	66 0f 2e c8          	ucomisd %xmm0,%xmm1
  5c9f7f:	76 59                	jbe    5c9fda <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18a4a>
  5c9f81:	c7 44 24 30 8f 02 00 	movl   $0x28f,0x30(%esp)
  5c9f88:	00 
  5c9f89:	8b 07                	mov    (%edi),%eax
  5c9f8b:	85 c0                	test   %eax,%eax
  5c9f8d:	74 07                	je     5c9f96 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18a06>
  5c9f8f:	05 a0 4c 00 00       	add    $0x4ca0,%eax
  5c9f94:	eb 13                	jmp    5c9fa9 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18a19>
  5c9f96:	8b 45 00             	mov    0x0(%ebp),%eax
  5c9f99:	8b 40 08             	mov    0x8(%eax),%eax
  5c9f9c:	89 2c 24             	mov    %ebp,(%esp)
  5c9f9f:	c7 44 24 04 ca 04 00 	movl   $0x4ca,0x4(%esp) # verified field ID: no_traction
  5c9fa6:	00 
  5c9fa7:	ff d0                	call   *%eax
  5c9fa9:	8b 48 0c             	mov    0xc(%eax),%ecx
  5c9fac:	83 f9 0d             	cmp    $0xd,%ecx
  5c9faf:	74 09                	je     5c9fba <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18a2a>
  5c9fb1:	83 f9 01             	cmp    $0x1,%ecx
  5c9fb4:	74 16                	je     5c9fcc <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18a3c>
  5c9fb6:	85 c9                	test   %ecx,%ecx
  5c9fb8:	75 20                	jne    5c9fda <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18a4a>
  5c9fba:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5c9fbe:	f2 0f 58 83 08 0d bc 	addsd  -0x43f2f8(%ebx),%xmm0
  5c9fc5:	ff 
  5c9fc6:	f2 0f 11 00          	movsd  %xmm0,(%eax)
  5c9fca:	eb 0e                	jmp    5c9fda <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18a4a>
  5c9fcc:	8d 83 dc 17 bb ff    	lea    -0x44e824(%ebx),%eax
  5c9fd2:	89 04 24             	mov    %eax,(%esp)
  5c9fd5:	e8 16 77 ba ff       	call   1716f0 <YYError(char const*, ...)@plt>
  5c9fda:	c7 44 24 30 91 02 00 	movl   $0x291,0x30(%esp)
  5c9fe1:	00 
  5c9fe2:	8b 07                	mov    (%edi),%eax
  5c9fe4:	85 c0                	test   %eax,%eax
  5c9fe6:	74 14                	je     5c9ffc <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18a6c>
  5c9fe8:	05 10 2d 00 00       	add    $0x2d10,%eax
  5c9fed:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5c9ff4:	75 22                	jne    5ca018 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18a88>
  5c9ff6:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5c9ffa:	eb 34                	jmp    5ca030 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18aa0>
  5c9ffc:	8b 45 00             	mov    0x0(%ebp),%eax
  5c9fff:	8b 40 08             	mov    0x8(%eax),%eax
  5ca002:	89 2c 24             	mov    %ebp,(%esp)
  5ca005:	c7 44 24 04 d1 02 00 	movl   $0x2d1,0x4(%esp)
  5ca00c:	00 
  5ca00d:	ff d0                	call   *%eax
  5ca00f:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5ca016:	74 de                	je     5c9ff6 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18a66>
  5ca018:	89 04 24             	mov    %eax,(%esp)
  5ca01b:	e8 c0 e5 b9 ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5ca020:	dd 9c 24 38 47 00 00 	fstpl  0x4738(%esp)
  5ca027:	f2 0f 10 84 24 38 47 	movsd  0x4738(%esp),%xmm0
  5ca02e:	00 00 
  5ca030:	f2 0f 58 83 90 0e bb 	addsd  -0x44f170(%ebx),%xmm0
  5ca037:	ff 
  5ca038:	8b 44 24 18          	mov    0x18(%esp),%eax
  5ca03c:	f2 0f 10 08          	movsd  (%eax),%xmm1
  5ca040:	66 0f 57 8b 60 09 bb 	xorpd  -0x44f6a0(%ebx),%xmm1
  5ca047:	ff 
  5ca048:	66 0f 2e c8          	ucomisd %xmm0,%xmm1
  5ca04c:	0f 86 82 02 00 00    	jbe    5ca2d4 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18d44>
  5ca052:	c7 44 24 30 93 02 00 	movl   $0x293,0x30(%esp)
  5ca059:	00 
  5ca05a:	8b 07                	mov    (%edi),%eax
  5ca05c:	85 c0                	test   %eax,%eax
  5ca05e:	74 07                	je     5ca067 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18ad7>
  5ca060:	05 10 2d 00 00       	add    $0x2d10,%eax
  5ca065:	eb 13                	jmp    5ca07a <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18aea>
  5ca067:	8b 45 00             	mov    0x0(%ebp),%eax
  5ca06a:	8b 40 08             	mov    0x8(%eax),%eax
  5ca06d:	89 2c 24             	mov    %ebp,(%esp)
  5ca070:	c7 44 24 04 d1 02 00 	movl   $0x2d1,0x4(%esp)
  5ca077:	00 
  5ca078:	ff d0                	call   *%eax
  5ca07a:	8b 48 0c             	mov    0xc(%eax),%ecx
  5ca07d:	83 f9 0d             	cmp    $0xd,%ecx
  5ca080:	74 09                	je     5ca08b <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18afb>
  5ca082:	83 f9 01             	cmp    $0x1,%ecx
  5ca085:	74 16                	je     5ca09d <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18b0d>
  5ca087:	85 c9                	test   %ecx,%ecx
  5ca089:	75 20                	jne    5ca0ab <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18b1b>
  5ca08b:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5ca08f:	f2 0f 58 83 30 07 bc 	addsd  -0x43f8d0(%ebx),%xmm0
  5ca096:	ff 
  5ca097:	f2 0f 11 00          	movsd  %xmm0,(%eax)
  5ca09b:	eb 0e                	jmp    5ca0ab <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18b1b>
  5ca09d:	8d 83 dc 17 bb ff    	lea    -0x44e824(%ebx),%eax
  5ca0a3:	89 04 24             	mov    %eax,(%esp)
  5ca0a6:	e8 45 76 ba ff       	call   1716f0 <YYError(char const*, ...)@plt>
  5ca0ab:	c7 44 24 30 94 02 00 	movl   $0x294,0x30(%esp)
  5ca0b2:	00 
  5ca0b3:	8b 44 24 38          	mov    0x38(%esp),%eax
  5ca0b7:	8b 28                	mov    (%eax),%ebp
  5ca0b9:	85 ed                	test   %ebp,%ebp
  5ca0bb:	74 08                	je     5ca0c5 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18b35>
  5ca0bd:	8d bd a0 80 00 00    	lea    0x80a0(%ebp),%edi
  5ca0c3:	eb 22                	jmp    5ca0e7 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18b57>
  5ca403:	75 06                	jne    5ca40b <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18e7b>
  5ca405:	8a 10                	mov    (%eax),%dl
  5ca407:	84 d2                	test   %dl,%dl
  5ca409:	74 2f                	je     5ca43a <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18eaa>
  5ca40b:	8b 09                	mov    (%ecx),%ecx
  5ca40d:	85 c9                	test   %ecx,%ecx
  5ca40f:	0f 84 b6 00 00 00    	je     5ca4cb <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18f3b>
  5ca415:	89 44 24 04          	mov    %eax,0x4(%esp)
  5ca419:	89 0c 24             	mov    %ecx,(%esp)
  5ca41c:	e8 6f ed ba ff       	call   179190 <strcmp@plt>
  5ca421:	85 c0                	test   %eax,%eax
  5ca423:	0f 85 a2 00 00 00    	jne    5ca4cb <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18f3b>
  5ca429:	eb 0f                	jmp    5ca43a <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18eaa>
  5ca42b:	8b 83 ec b7 ff ff    	mov    -0x4814(%ebx),%eax
  5ca431:	80 38 00             	cmpb   $0x0,(%eax)
  5ca434:	0f 85 91 00 00 00    	jne    5ca4cb <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18f3b>
  5ca43a:	8b 07                	mov    (%edi),%eax
  5ca43c:	85 c0                	test   %eax,%eax
  5ca43e:	74 1f                	je     5ca45f <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18ecf>
  5ca440:	05 a0 3a 00 00       	add    $0x3aa0,%eax
  5ca445:	eb 2b                	jmp    5ca472 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18ee2>
  5ca447:	8b 45 00             	mov    0x0(%ebp),%eax
  5ca44a:	8b 40 08             	mov    0x8(%eax),%eax
  5ca44d:	89 2c 24             	mov    %ebp,(%esp)
  5ca450:	c7 44 24 04 ca 04 00 	movl   $0x4ca,0x4(%esp) # verified field ID: no_traction
  5ca457:	00 
  5ca458:	ff d0                	call   *%eax
  5ca45a:	e9 5d 53 ff ff       	jmp    5bf7bc <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe22c>
  5ca45f:	8b 45 00             	mov    0x0(%ebp),%eax
  5ca462:	8b 40 08             	mov    0x8(%eax),%eax
  5ca465:	89 2c 24             	mov    %ebp,(%esp)
  5ca468:	c7 44 24 04 aa 03 00 	movl   $0x3aa,0x4(%esp)
  5ca46f:	00 
  5ca470:	ff d0                	call   *%eax
  5ca472:	89 04 24             	mov    %eax,(%esp)
  5ca475:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
  5ca47c:	00 
  5ca47d:	e8 ae 8b ba ff       	call   173030 <YYRValue::operator[](int)@plt>
  5ca482:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5ca489:	74 1a                	je     5ca4a5 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18f15>
  5ca48b:	89 04 24             	mov    %eax,(%esp)
  5ca48e:	e8 4d e1 b9 ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5ca493:	dd 9c 24 00 47 00 00 	fstpl  0x4700(%esp)
  5ca49a:	f2 0f 10 84 24 00 47 	movsd  0x4700(%esp),%xmm0
  5ca4a1:	00 00 
  5ca4a3:	eb 04                	jmp    5ca4a9 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18f19>
  5ca4a5:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5ca4a9:	f2 0f 58 83 28 0d bc 	addsd  -0x43f2d8(%ebx),%xmm0
  5ca4b0:	ff 
  5ca4b1:	8b 44 24 18          	mov    0x18(%esp),%eax
  5ca4b5:	f2 0f 10 08          	movsd  (%eax),%xmm1
  5ca4b9:	66 0f 57 8b 60 09 bb 	xorpd  -0x44f6a0(%ebx),%xmm1
  5ca4c0:	ff 
  5ca4c1:	66 0f 2e c1          	ucomisd %xmm1,%xmm0
  5ca4c5:	0f 82 9b 3a 00 00    	jb     5cdf66 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1c9d6>
  5ca4cb:	c7 44 24 30 99 02 00 	movl   $0x299,0x30(%esp)
  5ca4d2:	00 
  5ca4d3:	8b 07                	mov    (%edi),%eax
  5ca4d5:	85 c0                	test   %eax,%eax
  5ca4d7:	74 0d                	je     5ca4e6 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18f56>
  5ca4d9:	8d b0 70 7f 00 00    	lea    0x7f70(%eax),%esi
  5ca4df:	05 90 5d 00 00       	add    $0x5d90,%eax
  5ca4e4:	eb 35                	jmp    5ca51b <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18f8b>
  5ca4e6:	8b 45 00             	mov    0x0(%ebp),%eax
  5ca4e9:	8b 40 08             	mov    0x8(%eax),%eax
  5ca4ec:	89 2c 24             	mov    %ebp,(%esp)
  5ca4ef:	c7 44 24 04 f7 07 00 	movl   $0x7f7,0x4(%esp) # verified field ID: wheel_spin
  5ca4f6:	00 
  5ca4f7:	ff d0                	call   *%eax
  5ca4f9:	89 c6                	mov    %eax,%esi
  5ca4fb:	8b 07                	mov    (%edi),%eax
  5ca4fd:	85 c0                	test   %eax,%eax
  5ca4ff:	74 07                	je     5ca508 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18f78>
  5ca501:	05 90 5d 00 00       	add    $0x5d90,%eax
  5ca506:	eb 13                	jmp    5ca51b <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x18f8b>
  5ca508:	8b 45 00             	mov    0x0(%ebp),%eax
  5ca50b:	8b 40 08             	mov    0x8(%eax),%eax
  5ca50e:	89 2c 24             	mov    %ebp,(%esp)
  5ca511:	c7 44 24 04 d9 05 00 	movl   $0x5d9,0x4(%esp) # verified field ID: RPM
  5ca518:	00 
  5ca519:	ff d0                	call   *%eax
  5ca51b:	89 44 24 04          	mov    %eax,0x4(%esp)
  5ca51f:	8d bc 24 c8 20 00 00 	lea    0x20c8(%esp),%edi
  5ca526:	89 3c 24             	mov    %edi,(%esp)
  5ca529:	c7 44 24 0c 00 18 c5 	movl   $0x40c51800,0xc(%esp)
  5ca530:	40 
  5ca531:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
  5ca538:	00 
  5ca539:	e8 72 fd b9 ff       	call   16a2b0 <operator/(YYRValue const&, double)@plt>
  5ca53e:	83 ec 04             	sub    $0x4,%esp
  5ca541:	89 bc 24 10 17 00 00 	mov    %edi,0x1710(%esp)
  5ca548:	8b 83 20 7b ff ff    	mov    -0x84e0(%ebx),%eax
  5ca54e:	89 84 24 14 17 00 00 	mov    %eax,0x1714(%esp)
  5ca555:	8b 84 24 30 01 00 00 	mov    0x130(%esp),%eax
  5ca55c:	89 84 24 18 17 00 00 	mov    %eax,0x1718(%esp)
  5ca563:	8b 84 24 c8 00 00 00 	mov    0xc8(%esp),%eax
  5ca56a:	8b 40 04             	mov    0x4(%eax),%eax
  5ca56d:	8d 8c 24 10 17 00 00 	lea    0x1710(%esp),%ecx
  5ca574:	89 4c 24 14          	mov    %ecx,0x14(%esp)
  5ca578:	89 44 24 10          	mov    %eax,0x10(%esp)
  5ca57c:	8d 44 24 60          	lea    0x60(%esp),%eax
  5ca580:	89 44 24 08          	mov    %eax,0x8(%esp)
  5ca584:	8b 84 24 44 6a 00 00 	mov    0x6a44(%esp),%eax
  5ca58b:	89 44 24 04          	mov    %eax,0x4(%esp)
  5ca58f:	89 2c 24             	mov    %ebp,(%esp)
  5ca592:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
  5ca599:	00 
  5ca59a:	e8 21 9d ba ff       	call   1742c0 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
  5ca59f:	89 44 24 08          	mov    %eax,0x8(%esp)
  5ca6d7:	e8 44 c4 b9 ff       	call   166b20 <YYRValue::operator=(YYRValue const&)@plt>
  5ca6dc:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5ca6e1:	8b b4 24 d0 00 00 00 	mov    0xd0(%esp),%esi
  5ca6e8:	03 46 0c             	add    0xc(%esi),%eax
  5ca6eb:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5ca6f0:	75 08                	jne    5ca6fa <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1916a>
  5ca6f2:	89 34 24             	mov    %esi,(%esp)
  5ca6f5:	e8 86 3f ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5ca6fa:	c7 46 08 00 00 00 00 	movl   $0x0,0x8(%esi)
  5ca701:	c7 46 0c 05 00 00 00 	movl   $0x5,0xc(%esi)
  5ca708:	c7 06 00 00 00 00    	movl   $0x0,(%esi)
  5ca70e:	c7 44 24 30 9d 02 00 	movl   $0x29d,0x30(%esp)
  5ca715:	00 
  5ca716:	8b 07                	mov    (%edi),%eax
  5ca718:	85 c0                	test   %eax,%eax
  5ca71a:	74 14                	je     5ca730 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x191a0>
  5ca71c:	05 a0 4c 00 00       	add    $0x4ca0,%eax
  5ca721:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5ca728:	75 22                	jne    5ca74c <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x191bc>
  5ca72a:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5ca72e:	eb 34                	jmp    5ca764 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x191d4>
  5ca730:	8b 45 00             	mov    0x0(%ebp),%eax
  5ca733:	8b 40 08             	mov    0x8(%eax),%eax
  5ca736:	89 2c 24             	mov    %ebp,(%esp)
  5ca739:	c7 44 24 04 ca 04 00 	movl   $0x4ca,0x4(%esp) # verified field ID: no_traction
  5ca740:	00 
  5ca741:	ff d0                	call   *%eax
  5ca743:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5ca74a:	74 de                	je     5ca72a <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1919a>
  5ca74c:	89 04 24             	mov    %eax,(%esp)
  5ca74f:	e8 8c de b9 ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5ca754:	dd 9c 24 f8 46 00 00 	fstpl  0x46f8(%esp)
  5ca75b:	f2 0f 10 84 24 f8 46 	movsd  0x46f8(%esp),%xmm0
  5ca762:	00 00 
  5ca764:	f2 0f 58 83 f0 0c bc 	addsd  -0x43f310(%ebx),%xmm0
  5ca76b:	ff 
  5ca76c:	8b 44 24 18          	mov    0x18(%esp),%eax
  5ca770:	f2 0f 10 08          	movsd  (%eax),%xmm1
  5ca774:	66 0f 57 8b 60 09 bb 	xorpd  -0x44f6a0(%ebx),%xmm1
  5ca77b:	ff 
  5ca77c:	66 0f 2e c8          	ucomisd %xmm0,%xmm1
  5ca780:	0f 86 be 37 00 00    	jbe    5cdf44 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1c9b4>
  5ca786:	8b 07                	mov    (%edi),%eax
  5ca788:	85 c0                	test   %eax,%eax
  5ca78a:	74 14                	je     5ca7a0 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x19210>
  5ca78c:	05 10 2d 00 00       	add    $0x2d10,%eax
  5ca791:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5ca798:	75 22                	jne    5ca7bc <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1922c>
  5ca79a:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5ca79e:	eb 34                	jmp    5ca7d4 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x19244>
  5ca7a0:	8b 45 00             	mov    0x0(%ebp),%eax
  5ca7a3:	8b 40 08             	mov    0x8(%eax),%eax
  5ca7a6:	89 2c 24             	mov    %ebp,(%esp)
  5ca7a9:	c7 44 24 04 d1 02 00 	movl   $0x2d1,0x4(%esp)
  5ca7b0:	00 
  5ca7b1:	ff d0                	call   *%eax
  5ca7b3:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
  5ca7ba:	74 de                	je     5ca79a <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1920a>
  5ca7bc:	89 04 24             	mov    %eax,(%esp)
  5ca7bf:	e8 1c de b9 ff       	call   1685e0 <REAL_RValue_Ex(RValue const*)@plt>
  5ca7c4:	dd 9c 24 f0 46 00 00 	fstpl  0x46f0(%esp)
  5ca7cb:	f2 0f 10 84 24 f0 46 	movsd  0x46f0(%esp),%xmm0
  5ca7d2:	00 00 
  5ca7d4:	f2 0f 58 83 58 c1 bb 	addsd  -0x443ea8(%ebx),%xmm0
  5ca7db:	ff 
  5ca7dc:	8b 44 24 18          	mov    0x18(%esp),%eax
  5ca7e0:	66 0f 2e 00          	ucomisd (%eax),%xmm0
  5ca7e4:	0f 86 5a 37 00 00    	jbe    5cdf44 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1c9b4>
  5ca7ea:	c7 44 24 30 9f 02 00 	movl   $0x29f,0x30(%esp)
  5ca7f1:	00 
  5ca7f2:	8b 37                	mov    (%edi),%esi
  5ca7f4:	85 f6                	test   %esi,%esi
  5ca7f6:	74 20                	je     5ca818 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x19288>
  5ca7f8:	81 c6 10 2d 00 00    	add    $0x2d10,%esi
  5ca7fe:	eb 2d                	jmp    5ca82d <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1929d>
  5ca800:	8b 45 00             	mov    0x0(%ebp),%eax
  5ca803:	8b 40 08             	mov    0x8(%eax),%eax
  5ca806:	89 2c 24             	mov    %ebp,(%esp)
  5ca809:	c7 44 24 04 d1 02 00 	movl   $0x2d1,0x4(%esp)
  5ca810:	00 
  5ca811:	ff d0                	call   *%eax
  5ca813:	e9 b7 52 ff ff       	jmp    5bfacf <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xe53f>
  5ca818:	8b 45 00             	mov    0x0(%ebp),%eax
  5ca81b:	8b 40 08             	mov    0x8(%eax),%eax
  5ca81e:	89 2c 24             	mov    %ebp,(%esp)
  5ca821:	c7 44 24 04 d1 02 00 	movl   $0x2d1,0x4(%esp)
  5ca828:	00 
  5ca829:	ff d0                	call   *%eax
  5ca82b:	89 c6                	mov    %eax,%esi
  5ca82d:	c7 84 24 9c 07 00 00 	movl   $0x0,0x79c(%esp)
  5ca834:	00 00 00 00 
  5ca838:	c7 84 24 94 07 00 00 	movl   $0x3f747ae1,0x794(%esp)
  5ca83f:	e1 7a 74 3f 
  5ca843:	c7 84 24 90 07 00 00 	movl   $0x47ae147b,0x790(%esp)
  5ca84a:	7b 14 ae 47 
  5ca84e:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5ca853:	23 46 0c             	and    0xc(%esi),%eax
  5ca856:	83 f8 0d             	cmp    $0xd,%eax
  5ca859:	0f 87 a6 36 00 00    	ja     5cdf05 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1c975>
  5ca85f:	8b 84 83 cc 11 bc ff 	mov    -0x43ee34(%ebx,%eax,4),%eax
  5ca866:	01 d8                	add    %ebx,%eax
  5ca868:	ff e0                	jmp    *%eax
  5ca86a:	f2 0f 10 06          	movsd  (%esi),%xmm0
  5ca86e:	f2 0f 58 83 38 07 bc 	addsd  -0x43f8c8(%ebx),%xmm0
  5ca875:	ff 
  5ca876:	f2 0f 11 06          	movsd  %xmm0,(%esi)
  5ca87a:	e9 a3 36 00 00       	jmp    5cdf22 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1c992>
  5ca87f:	8b 45 00             	mov    0x0(%ebp),%eax
  5ca882:	8b 40 08             	mov    0x8(%eax),%eax
  5cb278:	66 0f 28 8b 60 09 bb 	movapd -0x44f6a0(%ebx),%xmm1
  5cb27f:	ff 
  5cb280:	66 0f 57 c8          	xorpd  %xmm0,%xmm1
  5cb284:	66 0f 57 d2          	xorpd  %xmm2,%xmm2
  5cb288:	66 0f 28 d8          	movapd %xmm0,%xmm3
  5cb28c:	f2 0f c2 da 01       	cmpltsd %xmm2,%xmm3
  5cb291:	66 0f 28 d3          	movapd %xmm3,%xmm2
  5cb295:	66 0f 55 d0          	andnpd %xmm0,%xmm2
  5cb299:	66 0f 54 d9          	andpd  %xmm1,%xmm3
  5cb29d:	66 0f 56 da          	orpd   %xmm2,%xmm3
  5cb2a1:	8b 44 24 18          	mov    0x18(%esp),%eax
  5cb2a5:	f2 0f 10 00          	movsd  (%eax),%xmm0
  5cb2a9:	66 0f 2e c3          	ucomisd %xmm3,%xmm0
  5cb2ad:	0f 82 db 30 00 00    	jb     5ce38e <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1cdfe>
  5cb2b3:	c7 44 24 30 d4 03 00 	movl   $0x3d4,0x30(%esp)
  5cb2ba:	00 
  5cb2bb:	8b 37                	mov    (%edi),%esi
  5cb2bd:	85 f6                	test   %esi,%esi
  5cb2bf:	74 08                	je     5cb2c9 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x19d39>
  5cb2c1:	81 c6 10 6e 00 00    	add    $0x6e10,%esi
  5cb2c7:	eb 15                	jmp    5cb2de <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x19d4e>
  5cb2c9:	8b 45 00             	mov    0x0(%ebp),%eax
  5cb2cc:	8b 40 08             	mov    0x8(%eax),%eax
  5cb2cf:	89 2c 24             	mov    %ebp,(%esp)
  5cb2d2:	c7 44 24 04 e1 06 00 	movl   $0x6e1,0x4(%esp) # verified field ID: tire_heat
  5cb2d9:	00 
  5cb2da:	ff d0                	call   *%eax
  5cb2dc:	89 c6                	mov    %eax,%esi
  5cb2de:	89 74 24 04          	mov    %esi,0x4(%esp)
  5cb2e2:	8d bc 24 58 1f 00 00 	lea    0x1f58(%esp),%edi
  5cb2e9:	89 3c 24             	mov    %edi,(%esp)
  5cb2ec:	c7 44 24 0c 00 80 66 	movl   $0x40668000,0xc(%esp)
  5cb2f3:	40 
  5cb2f4:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
  5cb2fb:	00 
  5cb2fc:	e8 af ef b9 ff       	call   16a2b0 <operator/(YYRValue const&, double)@plt>
  5cb301:	83 ec 04             	sub    $0x4,%esp
  5cb304:	89 bc 24 70 0a 00 00 	mov    %edi,0xa70(%esp)
  5cb30b:	8b 83 0c fb ff ff    	mov    -0x4f4(%ebx),%eax
  5cb311:	89 84 24 f0 00 00 00 	mov    %eax,0xf0(%esp)
  5cb318:	8b 40 04             	mov    0x4(%eax),%eax
  5cb31b:	8d 8c 24 70 0a 00 00 	lea    0xa70(%esp),%ecx
  5cb322:	89 4c 24 14          	mov    %ecx,0x14(%esp)
  5cb326:	89 44 24 10          	mov    %eax,0x10(%esp)
  5cb32a:	8d 84 24 90 00 00 00 	lea    0x90(%esp),%eax
  5cb331:	89 44 24 08          	mov    %eax,0x8(%esp)
  5cb335:	8b bc 24 44 6a 00 00 	mov    0x6a44(%esp),%edi
  5cb33c:	89 7c 24 04          	mov    %edi,0x4(%esp)
  5cb340:	89 2c 24             	mov    %ebp,(%esp)
  5cb343:	c7 44 24 0c 01 00 00 	movl   $0x1,0xc(%esp)
  5cb34a:	00 
  5cb34b:	e8 70 8f ba ff       	call   1742c0 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
  5cb350:	89 ea                	mov    %ebp,%edx
  5cb352:	89 84 24 74 16 00 00 	mov    %eax,0x1674(%esp)
  5cb359:	8b 84 24 80 00 00 00 	mov    0x80(%esp),%eax
  5cb360:	89 84 24 78 16 00 00 	mov    %eax,0x1678(%esp)
  5cb367:	8b ab 34 86 ff ff    	mov    -0x79cc(%ebx),%ebp
  5cb36d:	89 ac 24 7c 16 00 00 	mov    %ebp,0x167c(%esp)
  5cb374:	8b 84 24 c8 00 00 00 	mov    0xc8(%esp),%eax
  5cb37b:	8b 40 04             	mov    0x4(%eax),%eax
  5cb37e:	8d 8c 24 74 16 00 00 	lea    0x1674(%esp),%ecx
  5cb385:	89 4c 24 14          	mov    %ecx,0x14(%esp)
  5cb389:	89 44 24 10          	mov    %eax,0x10(%esp)
  5cb38d:	8d 44 24 60          	lea    0x60(%esp),%eax
  5cb391:	89 44 24 08          	mov    %eax,0x8(%esp)
  5cb395:	89 7c 24 04          	mov    %edi,0x4(%esp)
  5cb399:	89 14 24             	mov    %edx,(%esp)
  5cb39c:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
  5cb3a3:	00 
  5cb3a4:	e8 17 8f ba ff       	call   1742c0 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
  5cb3a9:	89 44 24 04          	mov    %eax,0x4(%esp)
  5cb3ad:	8d 84 24 38 04 00 00 	lea    0x438(%esp),%eax
  5cb3b4:	89 04 24             	mov    %eax,(%esp)
  5cb3b7:	e8 64 b7 b9 ff       	call   166b20 <YYRValue::operator=(YYRValue const&)@plt>
  5cb3bc:	bf ff ff ff 00       	mov    $0xffffff,%edi
  5cb3c1:	8b 44 24 6c          	mov    0x6c(%esp),%eax
  5cb3c5:	01 f8                	add    %edi,%eax
  5cb3c7:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5cb3cc:	75 0c                	jne    5cb3da <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x19e4a>
  5cb3ce:	8d 44 24 60          	lea    0x60(%esp),%eax
  5cb3d2:	89 04 24             	mov    %eax,(%esp)
  5cb3d5:	e8 a6 32 ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5cb3da:	c7 44 24 68 00 00 00 	movl   $0x0,0x68(%esp)
  5cb3e1:	00 
  5cb3e2:	c7 44 24 6c 05 00 00 	movl   $0x5,0x6c(%esp)
  5cb3e9:	00 
  5cb3ea:	c7 44 24 60 00 00 00 	movl   $0x0,0x60(%esp)
  5cb3f1:	00 
  5cb3f2:	03 bc 24 9c 00 00 00 	add    0x9c(%esp),%edi
  5cb3f9:	f7 c7 fc ff ff 00    	test   $0xfffffc,%edi
  5cb3ff:	75 0f                	jne    5cb410 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x19e80>
  5cb401:	8d 84 24 90 00 00 00 	lea    0x90(%esp),%eax
  5cb408:	89 04 24             	mov    %eax,(%esp)
  5cb40b:	e8 70 32 ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5cb410:	c7 84 24 98 00 00 00 	movl   $0x0,0x98(%esp)
  5cb417:	00 00 00 00 
  5cb41b:	c7 84 24 9c 00 00 00 	movl   $0x5,0x9c(%esp)
  5cb422:	05 00 00 00 
  5cb426:	c7 84 24 90 00 00 00 	movl   $0x0,0x90(%esp)
  5cb42d:	00 00 00 00 
  5cb431:	c7 44 24 30 d5 03 00 	movl   $0x3d5,0x30(%esp)
  5cb438:	00 
  5cb439:	89 74 24 04          	mov    %esi,0x4(%esp)
  5cb43d:	8d b4 24 48 1f 00 00 	lea    0x1f48(%esp),%esi
  5cb444:	89 34 24             	mov    %esi,(%esp)
  5cb447:	c7 44 24 0c 00 80 66 	movl   $0x40668000,0xc(%esp)
  5cb44e:	40 
  5cb44f:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
  5cb456:	00 
  5cb4b2:	f2 0f 11 84 24 30 02 	movsd  %xmm0,0x230(%esp)
  5cb4b9:	00 00 
  5cb4bb:	f2 0f 11 8c 24 38 02 	movsd  %xmm1,0x238(%esp)
  5cb4c2:	00 00 
  5cb4c4:	e8 b7 31 ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5cb4c9:	f2 0f 10 8c 24 38 02 	movsd  0x238(%esp),%xmm1
  5cb4d0:	00 00 
  5cb4d2:	f2 0f 10 84 24 30 02 	movsd  0x230(%esp),%xmm0
  5cb4d9:	00 00 
  5cb4db:	f2 0f 58 83 90 0e bb 	addsd  -0x44f170(%ebx),%xmm0
  5cb4e2:	ff 
  5cb4e3:	66 0f 2e c1          	ucomisd %xmm1,%xmm0
  5cb4e7:	0f 86 d1 01 00 00    	jbe    5cb6be <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1a12e>
  5cb4ed:	c7 44 24 30 d7 03 00 	movl   $0x3d7,0x30(%esp)
  5cb4f4:	00 
  5cb4f5:	8b 07                	mov    (%edi),%eax
  5cb4f7:	85 c0                	test   %eax,%eax
  5cb4f9:	74 07                	je     5cb502 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x19f72>
  5cb4fb:	05 10 6e 00 00       	add    $0x6e10,%eax
  5cb500:	eb 16                	jmp    5cb518 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x19f88>
  5cb502:	8b 4c 24 24          	mov    0x24(%esp),%ecx
  5cb506:	8b 01                	mov    (%ecx),%eax
  5cb508:	8b 40 08             	mov    0x8(%eax),%eax
  5cb50b:	89 0c 24             	mov    %ecx,(%esp)
  5cb50e:	c7 44 24 04 e1 06 00 	movl   $0x6e1,0x4(%esp) # verified field ID: tire_heat
  5cb515:	00 
  5cb516:	ff d0                	call   *%eax
  5cb518:	89 44 24 04          	mov    %eax,0x4(%esp)
  5cb51c:	8d b4 24 38 1f 00 00 	lea    0x1f38(%esp),%esi
  5cb523:	89 34 24             	mov    %esi,(%esp)
  5cb526:	c7 44 24 0c 00 80 66 	movl   $0x40668000,0xc(%esp)
  5cb52d:	40 
  5cb52e:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
  5cb535:	00 
  5cb536:	e8 75 ed b9 ff       	call   16a2b0 <operator/(YYRValue const&, double)@plt>
  5cb53b:	83 ec 04             	sub    $0x4,%esp
  5cb53e:	89 b4 24 6c 0a 00 00 	mov    %esi,0xa6c(%esp)
  5cb545:	8b 84 24 f0 00 00 00 	mov    0xf0(%esp),%eax
  5cb54c:	8b 40 04             	mov    0x4(%eax),%eax
  5cb54f:	8d 8c 24 6c 0a 00 00 	lea    0xa6c(%esp),%ecx
  5cb556:	89 4c 24 14          	mov    %ecx,0x14(%esp)
  5cb55a:	89 44 24 10          	mov    %eax,0x10(%esp)
  5cb55e:	8d 84 24 90 00 00 00 	lea    0x90(%esp),%eax
  5cb565:	89 44 24 08          	mov    %eax,0x8(%esp)
  5cb569:	8b b4 24 44 6a 00 00 	mov    0x6a44(%esp),%esi
  5cb570:	89 74 24 04          	mov    %esi,0x4(%esp)
  5cb574:	8b 7c 24 24          	mov    0x24(%esp),%edi
  5cb578:	89 3c 24             	mov    %edi,(%esp)
  5cb57b:	c7 44 24 0c 01 00 00 	movl   $0x1,0xc(%esp)
  5cb582:	00 
  5cb583:	e8 38 8d ba ff       	call   1742c0 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
  5cb588:	89 84 24 68 16 00 00 	mov    %eax,0x1668(%esp)
  5cb58f:	8b 84 24 80 00 00 00 	mov    0x80(%esp),%eax
  5cb596:	89 84 24 6c 16 00 00 	mov    %eax,0x166c(%esp)
  5cb59d:	89 ac 24 70 16 00 00 	mov    %ebp,0x1670(%esp)
  5cb5a4:	8b 84 24 c8 00 00 00 	mov    0xc8(%esp),%eax
  5cb5ab:	8b 40 04             	mov    0x4(%eax),%eax
  5cb5ae:	8d 8c 24 68 16 00 00 	lea    0x1668(%esp),%ecx
  5cb5b5:	89 4c 24 14          	mov    %ecx,0x14(%esp)
  5cb5b9:	89 44 24 10          	mov    %eax,0x10(%esp)
  5cb5bd:	8d 44 24 60          	lea    0x60(%esp),%eax
  5cb5c1:	89 44 24 08          	mov    %eax,0x8(%esp)
  5cb5c5:	89 74 24 04          	mov    %esi,0x4(%esp)
  5cb5c9:	89 3c 24             	mov    %edi,(%esp)
  5cb5cc:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
  5cb5d3:	00 
  5cb5d4:	e8 e7 8c ba ff       	call   1742c0 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
  5cb5d9:	89 44 24 08          	mov    %eax,0x8(%esp)
  5cb5dd:	8d bc 24 d8 62 00 00 	lea    0x62d8(%esp),%edi
  5cb5e4:	89 3c 24             	mov    %edi,(%esp)
  5cb5e7:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
  5cb5ee:	00 
  5cb5ef:	e8 dc d3 ba ff       	call   1789d0 <operator-(int, YYRValue const&)@plt>
  5cb5f4:	83 ec 04             	sub    $0x4,%esp
  5cb5f7:	89 7c 24 04          	mov    %edi,0x4(%esp)
  5cb5fb:	8d 84 24 38 04 00 00 	lea    0x438(%esp),%eax
  5cb602:	89 04 24             	mov    %eax,(%esp)
  5cb605:	e8 16 b5 b9 ff       	call   166b20 <YYRValue::operator=(YYRValue const&)@plt>
  5cb60a:	bd ff ff ff 00       	mov    $0xffffff,%ebp
  5cb60f:	8b 84 24 e4 62 00 00 	mov    0x62e4(%esp),%eax
  5cb616:	01 e8                	add    %ebp,%eax
  5cb618:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5cb61d:	75 08                	jne    5cb627 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1a097>
  5cb61f:	89 3c 24             	mov    %edi,(%esp)
  5cb622:	e8 59 30 ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5cb627:	03 6c 24 6c          	add    0x6c(%esp),%ebp
  5cb62b:	f7 c5 fc ff ff 00    	test   $0xfffffc,%ebp
  5cb631:	75 0c                	jne    5cb63f <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1a0af>
  5cb633:	8d 44 24 60          	lea    0x60(%esp),%eax
  5cb637:	89 04 24             	mov    %eax,(%esp)
  5cb63a:	e8 41 30 ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5cb63f:	c7 44 24 68 00 00 00 	movl   $0x0,0x68(%esp)
  5cb646:	00 
  5cb647:	c7 44 24 6c 05 00 00 	movl   $0x5,0x6c(%esp)
  5cb64e:	00 
  5cb64f:	c7 44 24 60 00 00 00 	movl   $0x0,0x60(%esp)
  5cb656:	00 
  5cb657:	bf ff ff ff 00       	mov    $0xffffff,%edi
  5cb65c:	8b 84 24 9c 00 00 00 	mov    0x9c(%esp),%eax
  5cb663:	01 f8                	add    %edi,%eax
  5cb665:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5cb66a:	75 0f                	jne    5cb67b <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1a0eb>
  5cb66c:	8d 84 24 90 00 00 00 	lea    0x90(%esp),%eax
  5cb673:	89 04 24             	mov    %eax,(%esp)
  5cb676:	e8 05 30 ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5cb67b:	c7 84 24 98 00 00 00 	movl   $0x0,0x98(%esp)
  5cb682:	00 00 00 00 
  5cb686:	c7 84 24 9c 00 00 00 	movl   $0x5,0x9c(%esp)
  5cb68d:	05 00 00 00 
  5cc429:	8b 7c 24 38          	mov    0x38(%esp),%edi
  5cc42d:	89 44 24 04          	mov    %eax,0x4(%esp)
  5cc431:	89 34 24             	mov    %esi,(%esp)
  5cc434:	e8 e7 a6 b9 ff       	call   166b20 <YYRValue::operator=(YYRValue const&)@plt>
  5cc439:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5cc43e:	8b b4 24 d0 00 00 00 	mov    0xd0(%esp),%esi
  5cc445:	03 46 0c             	add    0xc(%esi),%eax
  5cc448:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5cc44d:	75 08                	jne    5cc457 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1aec7>
  5cc44f:	89 34 24             	mov    %esi,(%esp)
  5cc452:	e8 29 22 ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5cc457:	c7 46 08 00 00 00 00 	movl   $0x0,0x8(%esi)
  5cc45e:	c7 46 0c 05 00 00 00 	movl   $0x5,0xc(%esi)
  5cc465:	c7 06 00 00 00 00    	movl   $0x0,(%esi)
  5cc46b:	c7 44 24 30 e4 03 00 	movl   $0x3e4,0x30(%esp)
  5cc472:	00 
  5cc473:	8b 07                	mov    (%edi),%eax
  5cc475:	85 c0                	test   %eax,%eax
  5cc477:	74 07                	je     5cc480 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1aef0>
  5cc479:	05 a0 4c 00 00       	add    $0x4ca0,%eax
  5cc47e:	eb 13                	jmp    5cc493 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1af03>
  5cc480:	8b 45 00             	mov    0x0(%ebp),%eax
  5cc483:	8b 40 08             	mov    0x8(%eax),%eax
  5cc486:	89 2c 24             	mov    %ebp,(%esp)
  5cc489:	c7 44 24 04 ca 04 00 	movl   $0x4ca,0x4(%esp) # verified field ID: no_traction
  5cc490:	00 
  5cc491:	ff d0                	call   *%eax
  5cc493:	89 84 24 2c 02 00 00 	mov    %eax,0x22c(%esp)
  5cc49a:	8b 44 24 58          	mov    0x58(%esp),%eax
  5cc49e:	89 44 24 04          	mov    %eax,0x4(%esp)
  5cc4a2:	8d bc 24 98 62 00 00 	lea    0x6298(%esp),%edi
  5cc4a9:	89 3c 24             	mov    %edi,(%esp)
  5cc4ac:	c7 44 24 0c 00 70 97 	movl   $0x40977000,0xc(%esp)
  5cc4b3:	40 
  5cc4b4:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
  5cc4bb:	00 
  5cc4bc:	e8 ef dd b9 ff       	call   16a2b0 <operator/(YYRValue const&, double)@plt>
  5cc4c1:	83 ec 04             	sub    $0x4,%esp
  5cc4c4:	89 7c 24 04          	mov    %edi,0x4(%esp)
  5cc4c8:	8d b4 24 c8 1e 00 00 	lea    0x1ec8(%esp),%esi
  5cc4cf:	89 34 24             	mov    %esi,(%esp)
  5cc4d2:	c7 44 24 0c 00 00 e0 	movl   $0x3fe00000,0xc(%esp)
  5cc4d9:	3f 
  5cc4da:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
  5cc4e1:	00 
  5cc4e2:	e8 49 c1 ba ff       	call   178630 <operator*(YYRValue const&, double)@plt>
  5cc4e7:	83 ec 04             	sub    $0x4,%esp
  5cc4ea:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5cc4ef:	03 84 24 a4 62 00 00 	add    0x62a4(%esp),%eax
  5cc4f6:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5cc4fb:	75 08                	jne    5cc505 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1af75>
  5cc4fd:	89 3c 24             	mov    %edi,(%esp)
  5cc500:	e8 7b 21 ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5cc505:	89 b4 24 20 16 00 00 	mov    %esi,0x1620(%esp)
  5cc50c:	8b 84 24 80 00 00 00 	mov    0x80(%esp),%eax
  5cc513:	89 84 24 24 16 00 00 	mov    %eax,0x1624(%esp)
  5cc51a:	8b 84 24 34 03 00 00 	mov    0x334(%esp),%eax
  5cc521:	89 84 24 28 16 00 00 	mov    %eax,0x1628(%esp)
  5cc528:	8b 84 24 38 02 00 00 	mov    0x238(%esp),%eax
  5cc52f:	89 44 24 08          	mov    %eax,0x8(%esp)
  5cc533:	8b 84 24 30 02 00 00 	mov    0x230(%esp),%eax
  5cc53a:	89 44 24 04          	mov    %eax,0x4(%esp)
  5cc53e:	8d b4 24 a8 1e 00 00 	lea    0x1ea8(%esp),%esi
  5cc545:	89 34 24             	mov    %esi,(%esp)
  5cc548:	e8 13 8a b9 ff       	call   164f60 <operator+(YYRValue const&, YYRValue const&)@plt>
  5cc54d:	83 ec 04             	sub    $0x4,%esp
  5cc550:	89 74 24 04          	mov    %esi,0x4(%esp)
  5cc554:	8d b4 24 b8 1e 00 00 	lea    0x1eb8(%esp),%esi
  5cc55b:	89 34 24             	mov    %esi,(%esp)
  5cc55e:	c7 44 24 0c 00 00 e0 	movl   $0x3fe00000,0xc(%esp)
  5cc565:	3f 
  5cc566:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
  5cc56d:	00 
  5cc56e:	e8 bd c0 ba ff       	call   178630 <operator*(YYRValue const&, double)@plt>
  5cc573:	83 ec 04             	sub    $0x4,%esp
  5cc576:	89 74 24 04          	mov    %esi,0x4(%esp)
  5cc57a:	8d bc 24 78 62 00 00 	lea    0x6278(%esp),%edi
  5cc581:	89 3c 24             	mov    %edi,(%esp)
  5cc584:	c7 44 24 08 50 00 00 	movl   $0x50,0x8(%esp)
  5cc58b:	00 
  5cc58c:	e8 bf e7 b9 ff       	call   16ad50 <operator-(YYRValue const&, int)@plt>
  5cc591:	83 ec 04             	sub    $0x4,%esp
  5cc594:	89 7c 24 04          	mov    %edi,0x4(%esp)
  5cc598:	8d ac 24 88 62 00 00 	lea    0x6288(%esp),%ebp
  5cc59f:	89 2c 24             	mov    %ebp,(%esp)
  5cc5a2:	c7 44 24 0c 06 f0 46 	movl   $0x3f46f006,0xc(%esp)
  5cc5a9:	3f 
  5cc5aa:	c7 44 24 08 c7 ba b8 	movl   $0x8db8bac7,0x8(%esp)
  5cc5b1:	8d 
  5cc5b2:	e8 79 c0 ba ff       	call   178630 <operator*(YYRValue const&, double)@plt>
  5cc5b7:	83 ec 04             	sub    $0x4,%esp
  5cc5ba:	89 6c 24 08          	mov    %ebp,0x8(%esp)
  5cc5be:	8d 84 24 a0 10 00 00 	lea    0x10a0(%esp),%eax
  5cc5c5:	89 04 24             	mov    %eax,(%esp)
  5cc5c8:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
  5cc5cf:	00 
  5cc5d0:	e8 fb c3 ba ff       	call   1789d0 <operator-(int, YYRValue const&)@plt>
  5cc5d5:	83 ec 04             	sub    $0x4,%esp
  5cc5d8:	be ff ff ff 00       	mov    $0xffffff,%esi
  5cc5dd:	8b 84 24 94 62 00 00 	mov    0x6294(%esp),%eax
  5cc5e4:	01 f0                	add    %esi,%eax
  5cc5e6:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5cc5eb:	75 08                	jne    5cc5f5 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1b065>
  5cc5ed:	89 2c 24             	mov    %ebp,(%esp)
  5cc5f0:	e8 8b 20 ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5cc5f5:	03 b4 24 84 62 00 00 	add    0x6284(%esp),%esi
  5cc5fc:	f7 c6 fc ff ff 00    	test   $0xfffffc,%esi
  5cc602:	8b 6c 24 24          	mov    0x24(%esp),%ebp
  5cc606:	75 08                	jne    5cc610 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1b080>
  5cd27c:	e8 3f 70 ba ff       	call   1742c0 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
  5cd281:	89 44 24 04          	mov    %eax,0x4(%esp)
  5cd285:	89 34 24             	mov    %esi,(%esp)
  5cd288:	e8 93 98 b9 ff       	call   166b20 <YYRValue::operator=(YYRValue const&)@plt>
  5cd28d:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5cd292:	8b b4 24 d0 00 00 00 	mov    0xd0(%esp),%esi
  5cd299:	03 46 0c             	add    0xc(%esi),%eax
  5cd29c:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5cd2a1:	75 08                	jne    5cd2ab <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1bd1b>
  5cd2a3:	89 34 24             	mov    %esi,(%esp)
  5cd2a6:	e8 d5 13 ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5cd2ab:	c7 46 08 00 00 00 00 	movl   $0x0,0x8(%esi)
  5cd2b2:	c7 46 0c 05 00 00 00 	movl   $0x5,0xc(%esi)
  5cd2b9:	c7 06 00 00 00 00    	movl   $0x0,(%esi)
  5cd2bf:	c7 44 24 30 ef 03 00 	movl   $0x3ef,0x30(%esp)
  5cd2c6:	00 
  5cd2c7:	8b 07                	mov    (%edi),%eax
  5cd2c9:	85 c0                	test   %eax,%eax
  5cd2cb:	74 07                	je     5cd2d4 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1bd44>
  5cd2cd:	05 a0 4c 00 00       	add    $0x4ca0,%eax
  5cd2d2:	eb 13                	jmp    5cd2e7 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1bd57>
  5cd2d4:	8b 45 00             	mov    0x0(%ebp),%eax
  5cd2d7:	8b 40 08             	mov    0x8(%eax),%eax
  5cd2da:	89 2c 24             	mov    %ebp,(%esp)
  5cd2dd:	c7 44 24 04 ca 04 00 	movl   $0x4ca,0x4(%esp) # verified field ID: no_traction
  5cd2e4:	00 
  5cd2e5:	ff d0                	call   *%eax
  5cd2e7:	89 84 24 2c 02 00 00 	mov    %eax,0x22c(%esp)
  5cd2ee:	8b 44 24 58          	mov    0x58(%esp),%eax
  5cd2f2:	89 44 24 04          	mov    %eax,0x4(%esp)
  5cd2f6:	8d bc 24 08 62 00 00 	lea    0x6208(%esp),%edi
  5cd2fd:	89 3c 24             	mov    %edi,(%esp)
  5cd300:	c7 44 24 0c 00 70 97 	movl   $0x40977000,0xc(%esp)
  5cd307:	40 
  5cd308:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
  5cd30f:	00 
  5cd310:	e8 9b cf b9 ff       	call   16a2b0 <operator/(YYRValue const&, double)@plt>
  5cd315:	83 ec 04             	sub    $0x4,%esp
  5cd318:	89 7c 24 04          	mov    %edi,0x4(%esp)
  5cd31c:	8d b4 24 08 1e 00 00 	lea    0x1e08(%esp),%esi
  5cd323:	89 34 24             	mov    %esi,(%esp)
  5cd326:	c7 44 24 0c 00 00 e0 	movl   $0x3fe00000,0xc(%esp)
  5cd32d:	3f 
  5cd32e:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
  5cd335:	00 
  5cd336:	e8 f5 b2 ba ff       	call   178630 <operator*(YYRValue const&, double)@plt>
  5cd33b:	83 ec 04             	sub    $0x4,%esp
  5cd33e:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  5cd343:	03 84 24 14 62 00 00 	add    0x6214(%esp),%eax
  5cd34a:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5cd34f:	75 08                	jne    5cd359 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1bdc9>
  5cd351:	89 3c 24             	mov    %edi,(%esp)
  5cd354:	e8 27 13 ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5cd359:	89 b4 24 a8 15 00 00 	mov    %esi,0x15a8(%esp)
  5cd360:	8b 84 24 80 00 00 00 	mov    0x80(%esp),%eax
  5cd367:	89 84 24 ac 15 00 00 	mov    %eax,0x15ac(%esp)
  5cd36e:	8b 84 24 20 02 00 00 	mov    0x220(%esp),%eax
  5cd375:	89 84 24 b0 15 00 00 	mov    %eax,0x15b0(%esp)
  5cd37c:	8b 84 24 38 02 00 00 	mov    0x238(%esp),%eax
  5cd383:	89 44 24 08          	mov    %eax,0x8(%esp)
  5cd387:	8b 84 24 30 02 00 00 	mov    0x230(%esp),%eax
  5cd38e:	89 44 24 04          	mov    %eax,0x4(%esp)
  5cd392:	8d b4 24 e8 1d 00 00 	lea    0x1de8(%esp),%esi
  5cd399:	89 34 24             	mov    %esi,(%esp)
  5cd39c:	e8 bf 7b b9 ff       	call   164f60 <operator+(YYRValue const&, YYRValue const&)@plt>
  5cd3a1:	83 ec 04             	sub    $0x4,%esp
  5cd3a4:	89 74 24 04          	mov    %esi,0x4(%esp)
  5cd3a8:	8d b4 24 f8 1d 00 00 	lea    0x1df8(%esp),%esi
  5cd3af:	89 34 24             	mov    %esi,(%esp)
  5cd3b2:	c7 44 24 08 02 00 00 	movl   $0x2,0x8(%esp)
  5cd3b9:	00 
  5cd3ba:	e8 e1 36 ba ff       	call   170aa0 <operator*(YYRValue const&, int)@plt>
  5cd3bf:	83 ec 04             	sub    $0x4,%esp
  5cd3c2:	89 74 24 04          	mov    %esi,0x4(%esp)
  5cd3c6:	8d ac 24 e8 61 00 00 	lea    0x61e8(%esp),%ebp
  5cd3cd:	89 2c 24             	mov    %ebp,(%esp)
  5cd3d0:	c7 44 24 08 50 00 00 	movl   $0x50,0x8(%esp)
  5cd3d7:	00 
  5cd3d8:	e8 73 d9 b9 ff       	call   16ad50 <operator-(YYRValue const&, int)@plt>
  5cd3dd:	83 ec 04             	sub    $0x4,%esp
  5cd3e0:	89 6c 24 04          	mov    %ebp,0x4(%esp)
  5cd3e4:	8d bc 24 f8 61 00 00 	lea    0x61f8(%esp),%edi
  5cd3eb:	89 3c 24             	mov    %edi,(%esp)
  5cd3ee:	c7 44 24 0c 06 f0 46 	movl   $0x3f46f006,0xc(%esp)
  5cd3f5:	3f 
  5cd3f6:	c7 44 24 08 c7 ba b8 	movl   $0x8db8bac7,0x8(%esp)
  5cd3fd:	8d 
  5cd3fe:	e8 2d b2 ba ff       	call   178630 <operator*(YYRValue const&, double)@plt>
  5cd403:	83 ec 04             	sub    $0x4,%esp
  5cd406:	89 7c 24 08          	mov    %edi,0x8(%esp)
  5cd40a:	8d 84 24 40 10 00 00 	lea    0x1040(%esp),%eax
  5cd411:	89 04 24             	mov    %eax,(%esp)
  5cd414:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
  5cd41b:	00 
  5cd41c:	e8 af b5 ba ff       	call   1789d0 <operator-(int, YYRValue const&)@plt>
  5cd421:	83 ec 04             	sub    $0x4,%esp
  5cd424:	be ff ff ff 00       	mov    $0xffffff,%esi
  5cd429:	8b 84 24 04 62 00 00 	mov    0x6204(%esp),%eax
  5cd430:	01 f0                	add    %esi,%eax
  5cd432:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  5cd437:	75 08                	jne    5cd441 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1beb1>
  5cd439:	89 3c 24             	mov    %edi,(%esp)
  5cd43c:	e8 3f 12 ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5cd441:	03 b4 24 f4 61 00 00 	add    0x61f4(%esp),%esi
  5cd448:	f7 c6 fc ff ff 00    	test   $0xfffffc,%esi
  5cd44e:	75 08                	jne    5cd458 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1bec8>
  5cd450:	89 2c 24             	mov    %ebp,(%esp)
  5cd453:	e8 28 12 ba ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  5cd458:	be ff ff ff 00       	mov    $0xffffff,%esi
  6315c3:	c7 07 00 00 00 00    	movl   $0x0,(%edi)
  6315c9:	03 b4 24 c4 0c 00 00 	add    0xcc4(%esp),%esi
  6315d0:	f7 c6 fc ff ff 00    	test   $0xfffffc,%esi
  6315d6:	8d bc 24 48 01 00 00 	lea    0x148(%esp),%edi
  6315dd:	0f 85 b3 ed ff ff    	jne    630396 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x7ee06>
  6315e3:	8d 84 24 b8 0c 00 00 	lea    0xcb8(%esp),%eax
  6315ea:	89 04 24             	mov    %eax,(%esp)
  6315ed:	e8 8e d0 b3 ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  6315f2:	e9 9f ed ff ff       	jmp    630396 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x7ee06>
  6315f7:	8b 6c 24 24          	mov    0x24(%esp),%ebp
  6315fb:	8b 45 00             	mov    0x0(%ebp),%eax
  6315fe:	8b 40 08             	mov    0x8(%eax),%eax
  631601:	89 2c 24             	mov    %ebp,(%esp)
  631604:	c7 44 24 04 d1 02 00 	movl   $0x2d1,0x4(%esp)
  63160b:	00 
  63160c:	ff d0                	call   *%eax
  63160e:	89 c6                	mov    %eax,%esi
  631610:	8b 44 24 38          	mov    0x38(%esp),%eax
  631614:	8b 00                	mov    (%eax),%eax
  631616:	85 c0                	test   %eax,%eax
  631618:	0f 85 b1 f7 ff ff    	jne    630dcf <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x7f83f>
  63161e:	8b 45 00             	mov    0x0(%ebp),%eax
  631621:	8b 40 08             	mov    0x8(%eax),%eax
  631624:	89 2c 24             	mov    %ebp,(%esp)
  631627:	c7 44 24 04 ca 04 00 	movl   $0x4ca,0x4(%esp) # verified field ID: no_traction
  63162e:	00 
  63162f:	ff d0                	call   *%eax
  631631:	e9 9e f7 ff ff       	jmp    630dd4 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x7f844>
  631636:	8b 45 00             	mov    0x0(%ebp),%eax
  631639:	8b 40 08             	mov    0x8(%eax),%eax
  63163c:	89 2c 24             	mov    %ebp,(%esp)
  63163f:	c7 44 24 04 d9 05 00 	movl   $0x5d9,0x4(%esp) # verified field ID: RPM
  631646:	00 
  631647:	ff d0                	call   *%eax
  631649:	89 c6                	mov    %eax,%esi
  63164b:	c7 84 24 8c 05 00 00 	movl   $0x0,0x58c(%esp)
  631652:	00 00 00 00 
  631656:	c7 84 24 84 05 00 00 	movl   $0x4082c000,0x584(%esp)
  63165d:	00 c0 82 40 
  631661:	c7 84 24 80 05 00 00 	movl   $0x0,0x580(%esp)
  631668:	00 00 00 00 
  63166c:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  631671:	23 46 0c             	and    0xc(%esi),%eax
  631674:	83 f8 0d             	cmp    $0xd,%eax
  631677:	77 4a                	ja     6316c3 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x80133>
  631679:	8b 84 83 dc 1f bc ff 	mov    -0x43e024(%ebx,%eax,4),%eax
  631680:	01 d8                	add    %ebx,%eax
  631682:	ff e0                	jmp    *%eax
  631684:	f2 0f 10 06          	movsd  (%esi),%xmm0
  631688:	f2 0f 58 83 38 0e bc 	addsd  -0x43f1c8(%ebx),%xmm0
  63168f:	ff 
  631690:	f2 0f 11 06          	movsd  %xmm0,(%esi)
  631694:	eb 4a                	jmp    6316e0 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x80150>
  631696:	8d 84 24 80 05 00 00 	lea    0x580(%esp),%eax
  63169d:	89 04 24             	mov    %eax,(%esp)
  6316a0:	e8 fb 64 b4 ff       	call   177ba0 <INT64_RValue(RValue const*)@plt>
  6316a5:	8b 0e                	mov    (%esi),%ecx
  6316a7:	29 c1                	sub    %eax,%ecx
  6316a9:	19 56 04             	sbb    %edx,0x4(%esi)
  6316ac:	89 0e                	mov    %ecx,(%esi)
  6316ae:	eb 30                	jmp    6316e0 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x80150>
  6316b0:	8d 84 24 80 05 00 00 	lea    0x580(%esp),%eax
  6316b7:	89 04 24             	mov    %eax,(%esp)
  6316ba:	e8 01 30 b4 ff       	call   1746c0 <INT32_RValue(RValue const*)@plt>
  6316bf:	29 06                	sub    %eax,(%esi)
  6316c1:	eb 1d                	jmp    6316e0 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x80150>
  6316c3:	8d 84 24 80 05 00 00 	lea    0x580(%esp),%eax
  6316ca:	89 44 24 08          	mov    %eax,0x8(%esp)
  6316ce:	89 74 24 04          	mov    %esi,0x4(%esp)
  6316d2:	8d 83 cc 14 bb ff    	lea    -0x44eb34(%ebx),%eax
  6316d8:	89 04 24             	mov    %eax,(%esp)
  6316db:	e8 a0 7f b3 ff       	call   169680 <YYOpError(char const*, YYRValue const*, YYRValue const*)@plt>
  6316e0:	b8 ff ff ff 00       	mov    $0xffffff,%eax
  6316e5:	03 84 24 8c 05 00 00 	add    0x58c(%esp),%eax
  6316ec:	a9 fc ff ff 00       	test   $0xfffffc,%eax
  6316f1:	75 0f                	jne    631702 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x80172>
  6316f3:	8d 84 24 80 05 00 00 	lea    0x580(%esp),%eax
  6316fa:	89 04 24             	mov    %eax,(%esp)
  6316fd:	e8 7e cf b3 ff       	call   16e680 <FREE_RValue__Pre(RValue*)@plt>
  631702:	8b b4 24 d0 00 00 00 	mov    0xd0(%esp),%esi
  631709:	e9 4f 5e ff ff       	jmp    62755d <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x75fcd>
  63170e:	f2 0f 10 00          	movsd  (%eax),%xmm0
  631712:	66 0f 28 8b 60 09 bb 	movapd -0x44f6a0(%ebx),%xmm1
  631719:	ff 
  63171a:	66 0f 57 c8          	xorpd  %xmm0,%xmm1
  63171e:	66 0f 57 d2          	xorpd  %xmm2,%xmm2
  631722:	66 0f 28 d8          	movapd %xmm0,%xmm3
  631726:	f2 0f c2 da 01       	cmpltsd %xmm2,%xmm3
  63172b:	66 0f 28 d3          	movapd %xmm3,%xmm2
  63172f:	66 0f 55 d0          	andnpd %xmm0,%xmm2
  631733:	66 0f 54 d9          	andpd  %xmm1,%xmm3
  631737:	66 0f 56 da          	orpd   %xmm2,%xmm3
  63173b:	8b 44 24 18          	mov    0x18(%esp),%eax
  63173f:	f2 0f 10 00          	movsd  (%eax),%xmm0
  631743:	66 0f 2e c3          	ucomisd %xmm3,%xmm0
  631747:	0f 83 b0 0d 00 00    	jae    6324fd <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x80f6d>
  63174d:	c7 44 24 30 12 15 00 	movl   $0x1512,0x30(%esp)
  631754:	00 
  631755:	8b 2f                	mov    (%edi),%ebp
  631757:	85 ed                	test   %ebp,%ebp
  631759:	74 08                	je     631763 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x801d3>
  63175b:	81 c5 f0 3e 00 00    	add    $0x3ef0,%ebp
  631761:	eb 18                	jmp    63177b <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x801eb>
  631763:	8b 4c 24 24          	mov    0x24(%esp),%ecx
  631767:	8b 01                	mov    (%ecx),%eax
  631769:	8b 40 08             	mov    0x8(%eax),%eax
  63176c:	89 0c 24             	mov    %ecx,(%esp)
  63176f:	c7 44 24 04 ef 03 00 	movl   $0x3ef,0x4(%esp)
  631776:	00 
