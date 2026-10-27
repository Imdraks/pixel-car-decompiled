 1182588:	8b 84 24 cc 06 00 00 	mov    0x6cc(%esp),%eax
 118258f:	b9 46 00 00 00       	mov    $0x46,%ecx
 1182594:	0f a3 c1             	bt     %eax,%ecx
 1182597:	73 0f                	jae    11825a8 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x7f58>
 1182599:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 11825a0:	89 04 24             	mov    %eax,(%esp)
 11825a3:	e8 18 91 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11825a8:	c7 84 24 c0 06 00 00 	movl   $0x0,0x6c0(%esp)
 11825af:	00 00 00 00 
 11825b3:	c7 84 24 c8 06 00 00 	movl   $0x0,0x6c8(%esp)
 11825ba:	00 00 00 00 
 11825be:	c7 84 24 cc 06 00 00 	movl   $0x5,0x6cc(%esp)
 11825c5:	05 00 00 00 
 11825c9:	8b 75 08             	mov    0x8(%ebp),%esi
 11825cc:	8b 06                	mov    (%esi),%eax
 11825ce:	8b 40 08             	mov    0x8(%eax),%eax
 11825d1:	89 34 24             	mov    %esi,(%esp)
 11825d4:	c7 44 24 04 ba 90 01 	movl   $0x190ba,0x4(%esp) # verified field ID: RPM
 11825db:	00 
 11825dc:	ff d0                	call   *%eax
 11825de:	89 c7                	mov    %eax,%edi
 11825e0:	8b 06                	mov    (%esi),%eax
 11825e2:	8b 40 08             	mov    0x8(%eax),%eax
 11825e5:	89 34 24             	mov    %esi,(%esp)
 11825e8:	c7 44 24 04 b4 92 01 	movl   $0x192b4,0x4(%esp) # verified field ID: tire_heat
 11825ef:	00 
 11825f0:	ff d0                	call   *%eax
 11825f2:	89 c6                	mov    %eax,%esi
 11825f4:	89 7c 24 04          	mov    %edi,0x4(%esp)
 11825f8:	8d bc 24 20 0a 00 00 	lea    0xa20(%esp),%edi
 11825ff:	89 3c 24             	mov    %edi,(%esp)
 1182602:	c7 44 24 0c 85 eb 91 	movl   $0x3f91eb85,0xc(%esp)
 1182609:	3f 
 118260a:	c7 44 24 08 ec 51 b8 	movl   $0x1eb851ec,0x8(%esp)
 1182611:	1e 
 1182612:	e8 d9 93 6a 00       	call   182b9f0 <operator*(YYRValue const&, double)@plt>
 1182617:	83 ec 04             	sub    $0x4,%esp
 118261a:	89 7c 24 04          	mov    %edi,0x4(%esp)
 118261e:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 1182625:	89 04 24             	mov    %eax,(%esp)
 1182628:	e8 33 91 6a 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 118262d:	8b 84 24 2c 0a 00 00 	mov    0xa2c(%esp),%eax
 1182634:	b9 46 00 00 00       	mov    $0x46,%ecx
 1182639:	0f a3 c1             	bt     %eax,%ecx
 118263c:	73 0f                	jae    118264d <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x7ffd>
 118263e:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 1182645:	89 04 24             	mov    %eax,(%esp)
 1182648:	e8 73 90 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118264d:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 1182654:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 118265b:	8b 84 24 a0 00 00 00 	mov    0xa0(%esp),%eax
 1182662:	89 44 24 04          	mov    %eax,0x4(%esp)
 1182666:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 118266d:	89 04 24             	mov    %eax,(%esp)
 1182670:	e8 fb 90 6a 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 1182675:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 118267c:	89 84 24 fc 0a 00 00 	mov    %eax,0xafc(%esp)
 1182683:	8b 83 14 d2 ff ff    	mov    -0x2dec(%ebx),%eax
 1182689:	89 84 24 a8 00 00 00 	mov    %eax,0xa8(%esp)
 1182690:	89 44 24 04          	mov    %eax,0x4(%esp)
 1182694:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 118269b:	89 04 24             	mov    %eax,(%esp)
 118269e:	e8 cd 90 6a 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 11826a3:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 11826aa:	89 84 24 00 0b 00 00 	mov    %eax,0xb00(%esp)
 11826b1:	8b 44 24 60          	mov    0x60(%esp),%eax
 11826b5:	8b 40 04             	mov    0x4(%eax),%eax
 11826b8:	8d 8c 24 f8 0a 00 00 	lea    0xaf8(%esp),%ecx
 11826bf:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 11826c3:	89 44 24 10          	mov    %eax,0x10(%esp)
 11826c7:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 11826ce:	89 44 24 08          	mov    %eax,0x8(%esp)
 11826d2:	8b 45 0c             	mov    0xc(%ebp),%eax
 11826d5:	89 44 24 04          	mov    %eax,0x4(%esp)
 11826d9:	8b 45 08             	mov    0x8(%ebp),%eax
 11826dc:	89 04 24             	mov    %eax,(%esp)
 11826df:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
 11826e6:	00 
 11826e7:	e8 14 91 6a 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 11826ec:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 11826f3:	00 00 00 00 
 11826f7:	c7 84 24 24 0a 00 00 	movl   $0x40590000,0xa24(%esp)
 11826fe:	00 00 59 40 
 1182702:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 1182709:	00 00 00 00 
 118270d:	89 44 24 04          	mov    %eax,0x4(%esp)
 1182711:	8d bc 24 20 0a 00 00 	lea    0xa20(%esp),%edi
 1182718:	89 3c 24             	mov    %edi,(%esp)
 118271b:	e8 00 92 6a 00       	call   182b920 <YYRValue::operator+=(YYRValue const&)@plt>
 1182720:	8b 44 24 24          	mov    0x24(%esp),%eax
 1182724:	f2 0f 10 00          	movsd  (%eax),%xmm0
 1182728:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 118272e:	89 7c 24 04          	mov    %edi,0x4(%esp)
 1182732:	89 34 24             	mov    %esi,(%esp)
 1182735:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
 118273c:	00 
 118273d:	e8 7e 90 6a 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 1182742:	83 f8 fe             	cmp    $0xfffffffe,%eax
 1182745:	0f 95 44 24 48       	setne  0x48(%esp)
 118274a:	85 c0                	test   %eax,%eax
 118274c:	0f 98 44 24 50       	sets   0x50(%esp)
 1182751:	8b 84 24 2c 0a 00 00 	mov    0xa2c(%esp),%eax
 1182758:	b9 46 00 00 00       	mov    $0x46,%ecx
 118275d:	0f a3 c1             	bt     %eax,%ecx
 1182760:	73 08                	jae    118276a <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x811a>
 1182762:	89 3c 24             	mov    %edi,(%esp)
 1182765:	e8 56 8f 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118276a:	8a 44 24 50          	mov    0x50(%esp),%al
 118276e:	20 44 24 48          	and    %al,0x48(%esp)
 1182772:	0f 84 5a 03 00 00    	je     1182ad2 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8482>
 1182778:	c7 84 24 18 0a 00 00 	movl   $0x17a,0xa18(%esp)
 118277f:	7a 01 00 00 
 1182783:	8b 84 24 bc 06 00 00 	mov    0x6bc(%esp),%eax
 118278a:	b9 46 00 00 00       	mov    $0x46,%ecx
 118278f:	0f a3 c1             	bt     %eax,%ecx
 1182792:	73 0f                	jae    11827a3 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8153>
 1182794:	8d 84 24 b0 06 00 00 	lea    0x6b0(%esp),%eax
 118279b:	89 04 24             	mov    %eax,(%esp)
 118279e:	e8 1d 8f 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11827a3:	c7 84 24 b0 06 00 00 	movl   $0x0,0x6b0(%esp)
 11827aa:	00 00 00 00 
 11827ae:	c7 84 24 b8 06 00 00 	movl   $0x0,0x6b8(%esp)
 11827b5:	00 00 00 00 
 11827b9:	c7 84 24 bc 06 00 00 	movl   $0x5,0x6bc(%esp)
 11827c0:	05 00 00 00 
 11827c4:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11827c7:	8b 01                	mov    (%ecx),%eax
 11827c9:	8b 40 0c             	mov    0xc(%eax),%eax
 11827cc:	89 0c 24             	mov    %ecx,(%esp)
 11827cf:	c7 44 24 04 b4 92 01 	movl   $0x192b4,0x4(%esp) # verified field ID: tire_heat
 11827d6:	00 
 11827d7:	ff d0                	call   *%eax
 11827d9:	89 44 24 50          	mov    %eax,0x50(%esp)
 11827dd:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11827e0:	8b 01                	mov    (%ecx),%eax
 11827e2:	8b 40 08             	mov    0x8(%eax),%eax
 11827e5:	89 0c 24             	mov    %ecx,(%esp)
 11827e8:	c7 44 24 04 ba 90 01 	movl   $0x190ba,0x4(%esp) # verified field ID: RPM
 11827ef:	00 
 11827f0:	ff d0                	call   *%eax
 11827f2:	89 44 24 48          	mov    %eax,0x48(%esp)
 11827f6:	8b 44 24 48          	mov    0x48(%esp),%eax
 11827fa:	89 44 24 04          	mov    %eax,0x4(%esp)
 11827fe:	8d b4 24 20 0a 00 00 	lea    0xa20(%esp),%esi
 1182805:	89 34 24             	mov    %esi,(%esp)
 1182808:	c7 44 24 0c e2 36 1a 	movl   $0x3f1a36e2,0xc(%esp)
 118280f:	3f 
 1182810:	c7 44 24 08 2d 43 1c 	movl   $0xeb1c432d,0x8(%esp)
 1182817:	eb 
 1182818:	e8 d3 91 6a 00       	call   182b9f0 <operator*(YYRValue const&, double)@plt>
 118281d:	83 ec 04             	sub    $0x4,%esp
 1182820:	89 74 24 04          	mov    %esi,0x4(%esp)
 1182824:	8d 84 24 68 0a 00 00 	lea    0xa68(%esp),%eax
 118282b:	89 04 24             	mov    %eax,(%esp)
 118282e:	e8 2d 8f 6a 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 1182833:	8b 84 24 2c 0a 00 00 	mov    0xa2c(%esp),%eax
 118283a:	b9 46 00 00 00       	mov    $0x46,%ecx
 118283f:	0f a3 c1             	bt     %eax,%ecx
 1182842:	73 0f                	jae    1182853 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8203>
 1182844:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 118284b:	89 04 24             	mov    %eax,(%esp)
 118284e:	e8 6d 8e 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 1182853:	8d 84 24 68 0a 00 00 	lea    0xa68(%esp),%eax
 118285a:	89 84 24 04 0b 00 00 	mov    %eax,0xb04(%esp)
 1182861:	8b 83 18 d2 ff ff    	mov    -0x2de8(%ebx),%eax
 1182867:	89 44 24 04          	mov    %eax,0x4(%esp)
 118286b:	8d 84 24 78 0a 00 00 	lea    0xa78(%esp),%eax
 1182872:	89 04 24             	mov    %eax,(%esp)
 1182875:	e8 f6 8e 6a 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 118287a:	8d 84 24 78 0a 00 00 	lea    0xa78(%esp),%eax
 1182881:	89 84 24 08 0b 00 00 	mov    %eax,0xb08(%esp)
 1182888:	8b 84 24 a0 00 00 00 	mov    0xa0(%esp),%eax
 118288f:	89 44 24 04          	mov    %eax,0x4(%esp)
 1182893:	8d 84 24 88 0a 00 00 	lea    0xa88(%esp),%eax
 118289a:	89 04 24             	mov    %eax,(%esp)
 118289d:	e8 ce 8e 6a 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 11828a2:	8d 84 24 88 0a 00 00 	lea    0xa88(%esp),%eax
 11828a9:	89 84 24 0c 0b 00 00 	mov    %eax,0xb0c(%esp)
 11828b0:	8b 44 24 60          	mov    0x60(%esp),%eax
 11828b4:	8b 40 04             	mov    0x4(%eax),%eax
 11828b7:	8d 8c 24 04 0b 00 00 	lea    0xb04(%esp),%ecx
 11828be:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 11828c2:	89 44 24 10          	mov    %eax,0x10(%esp)
 11828c6:	8d 84 24 b0 06 00 00 	lea    0x6b0(%esp),%eax
 11828cd:	89 44 24 08          	mov    %eax,0x8(%esp)
 11828d1:	8b 45 0c             	mov    0xc(%ebp),%eax
 11828d4:	89 44 24 04          	mov    %eax,0x4(%esp)
 11828d8:	8b 45 08             	mov    0x8(%ebp),%eax
 11828db:	89 04 24             	mov    %eax,(%esp)
 11828de:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
 11828e5:	00 
 11828e6:	e8 15 8f 6a 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 11828eb:	89 c7                	mov    %eax,%edi
 11828ed:	8b 45 08             	mov    0x8(%ebp),%eax
 11828f0:	89 04 24             	mov    %eax,(%esp)
 11828f3:	e8 98 8e 6a 00       	call   182b790 <PushContextStack(YYObjectBase*)@plt>
 11828f8:	89 7c 24 04          	mov    %edi,0x4(%esp)
 11828fc:	8b 44 24 50          	mov    0x50(%esp),%eax
 1182900:	89 04 24             	mov    %eax,(%esp)
 1182903:	e8 18 90 6a 00       	call   182b920 <YYRValue::operator+=(YYRValue const&)@plt>
 1182908:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 118290f:	e8 8c 8e 6a 00       	call   182b7a0 <PopContextStack(int)@plt>
 1182914:	e9 1f 04 00 00       	jmp    1182d38 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x86e8>
 1182919:	c7 84 24 18 0a 00 00 	movl   $0x188,0xa18(%esp)
 1182920:	88 01 00 00 
 1182924:	8b 4d 08             	mov    0x8(%ebp),%ecx
 1182927:	8b 01                	mov    (%ecx),%eax
 1182929:	8b 40 0c             	mov    0xc(%eax),%eax
 118292c:	89 0c 24             	mov    %ecx,(%esp)
 118292f:	c7 44 24 04 b4 92 01 	movl   $0x192b4,0x4(%esp) # verified field ID: tire_heat
 1182936:	00 
 1182937:	ff d0                	call   *%eax
 1182939:	89 c6                	mov    %eax,%esi
 118293b:	8b 44 24 24          	mov    0x24(%esp),%eax
 118293f:	f2 0f 10 00          	movsd  (%eax),%xmm0
 1182943:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 1182949:	8d bc 24 b0 08 00 00 	lea    0x8b0(%esp),%edi
 1182950:	89 7c 24 04          	mov    %edi,0x4(%esp)
 1182954:	89 34 24             	mov    %esi,(%esp)
 1182957:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
 118295e:	00 
 118295f:	e8 5c 8e 6a 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 1182964:	85 c0                	test   %eax,%eax
 1182966:	7e 76                	jle    11829de <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x838e>
 1182968:	c7 84 24 18 0a 00 00 	movl   $0x18a,0xa18(%esp)
 118296f:	8a 01 00 00 
 1182973:	8b 4d 08             	mov    0x8(%ebp),%ecx
 1182976:	8b 01                	mov    (%ecx),%eax
 1182978:	8b 40 0c             	mov    0xc(%eax),%eax
 118297b:	89 0c 24             	mov    %ecx,(%esp)
 118297e:	c7 44 24 04 b4 92 01 	movl   $0x192b4,0x4(%esp) # verified field ID: tire_heat
 1182985:	00 
 1182986:	ff d0                	call   *%eax
 1182988:	89 c6                	mov    %eax,%esi
 118298a:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 1182991:	00 00 00 00 
 1182995:	c7 84 24 24 0a 00 00 	movl   $0x3fd00000,0xa24(%esp)
 118299c:	00 00 d0 3f 
 11829a0:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 11829a7:	00 00 00 00 
 11829ab:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 11829b2:	89 44 24 04          	mov    %eax,0x4(%esp)
 11829b6:	89 34 24             	mov    %esi,(%esp)
 11829b9:	e8 72 90 6a 00       	call   182ba30 <YYRValue::operator-=(YYRValue const&)@plt>
 11829be:	8b 84 24 2c 0a 00 00 	mov    0xa2c(%esp),%eax
 11829c5:	b9 46 00 00 00       	mov    $0x46,%ecx
 11829ca:	0f a3 c1             	bt     %eax,%ecx
 11829cd:	73 0f                	jae    11829de <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x838e>
 11829cf:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 11829d6:	89 04 24             	mov    %eax,(%esp)
 11829d9:	e8 e2 8c 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11829de:	c7 84 24 18 0a 00 00 	movl   $0x18c,0xa18(%esp)
 11829e5:	8c 01 00 00 
 11829e9:	8b 84 24 cc 06 00 00 	mov    0x6cc(%esp),%eax
 11829f0:	b9 46 00 00 00       	mov    $0x46,%ecx
 11829f5:	0f a3 c1             	bt     %eax,%ecx
 11829f8:	73 0f                	jae    1182a09 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x83b9>
 11829fa:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 1182a01:	89 04 24             	mov    %eax,(%esp)
 1182a04:	e8 b7 8c 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 1182a09:	c7 84 24 c0 06 00 00 	movl   $0x0,0x6c0(%esp)
 1182a10:	00 00 00 00 
 1182a14:	c7 84 24 c8 06 00 00 	movl   $0x0,0x6c8(%esp)
 1182a1b:	00 00 00 00 
 1182a1f:	c7 84 24 cc 06 00 00 	movl   $0x5,0x6cc(%esp)
 1182a26:	05 00 00 00 
 1182a2a:	89 74 24 04          	mov    %esi,0x4(%esp)
 1182a2e:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 1182a35:	89 04 24             	mov    %eax,(%esp)
 1182a38:	e8 23 8d 6a 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 1182a3d:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 1182a44:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 1182a4b:	89 bc 24 fc 0a 00 00 	mov    %edi,0xafc(%esp)
 1182a52:	8b 83 1c d2 ff ff    	mov    -0x2de4(%ebx),%eax
 1182a58:	89 44 24 04          	mov    %eax,0x4(%esp)
 1182a5c:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 1182a63:	89 04 24             	mov    %eax,(%esp)
 1182a66:	e8 05 8d 6a 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 1182a6b:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 1182a72:	89 84 24 00 0b 00 00 	mov    %eax,0xb00(%esp)
 1182a79:	8b 44 24 60          	mov    0x60(%esp),%eax
 1182a7d:	8b 40 04             	mov    0x4(%eax),%eax
 1182a80:	8d 8c 24 f8 0a 00 00 	lea    0xaf8(%esp),%ecx
 1182a87:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 1182a8b:	89 44 24 10          	mov    %eax,0x10(%esp)
 1182a8f:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 1182a96:	89 44 24 08          	mov    %eax,0x8(%esp)
 1182a9a:	8b 45 0c             	mov    0xc(%ebp),%eax
 1182a9d:	89 44 24 04          	mov    %eax,0x4(%esp)
 1182aa1:	8b 45 08             	mov    0x8(%ebp),%eax
 1182aa4:	89 04 24             	mov    %eax,(%esp)
 1182aa7:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
 1182aae:	00 
 1182aaf:	e8 4c 8d 6a 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 1182ab4:	89 c7                	mov    %eax,%edi
 1182ab6:	8b 45 08             	mov    0x8(%ebp),%eax
 1182ab9:	89 04 24             	mov    %eax,(%esp)
 1182abc:	e8 cf 8c 6a 00       	call   182b790 <PushContextStack(YYObjectBase*)@plt>
 1182ac1:	89 7c 24 04          	mov    %edi,0x4(%esp)
 1182ac5:	89 34 24             	mov    %esi,(%esp)
 1182ac8:	e8 93 8c 6a 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 1182acd:	e9 64 03 00 00       	jmp    1182e36 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x87e6>
 1182ad2:	c7 84 24 18 0a 00 00 	movl   $0x17e,0xa18(%esp)
 1182ad9:	7e 01 00 00 
 1182add:	8b 84 24 cc 06 00 00 	mov    0x6cc(%esp),%eax
 1182ae4:	b9 46 00 00 00       	mov    $0x46,%ecx
 1182ae9:	0f a3 c1             	bt     %eax,%ecx
 1182aec:	73 0f                	jae    1182afd <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x84ad>
 1182aee:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 1182af5:	89 04 24             	mov    %eax,(%esp)
 1182af8:	e8 c3 8b 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 1182afd:	c7 84 24 c0 06 00 00 	movl   $0x0,0x6c0(%esp)
 1182b04:	00 00 00 00 
 1182b08:	c7 84 24 c8 06 00 00 	movl   $0x0,0x6c8(%esp)
 1182b0f:	00 00 00 00 
 1182b13:	c7 84 24 cc 06 00 00 	movl   $0x5,0x6cc(%esp)
 1182b1a:	05 00 00 00 
 1182b1e:	8b 4d 08             	mov    0x8(%ebp),%ecx
 1182b21:	8b 01                	mov    (%ecx),%eax
 1182b23:	8b 40 0c             	mov    0xc(%eax),%eax
 1182b26:	89 0c 24             	mov    %ecx,(%esp)
 1182b29:	c7 44 24 04 b4 92 01 	movl   $0x192b4,0x4(%esp) # verified field ID: tire_heat
 1182b30:	00 
 1182b31:	ff d0                	call   *%eax
 1182b33:	89 44 24 50          	mov    %eax,0x50(%esp)
 1182b37:	8b 4d 08             	mov    0x8(%ebp),%ecx
 1182b3a:	8b 01                	mov    (%ecx),%eax
 1182b3c:	8b 40 08             	mov    0x8(%eax),%eax
 1182b3f:	89 0c 24             	mov    %ecx,(%esp)
 1182b42:	c7 44 24 04 ba 90 01 	movl   $0x190ba,0x4(%esp) # verified field ID: RPM
 1182b49:	00 
 1182b4a:	ff d0                	call   *%eax
 1182b4c:	89 44 24 48          	mov    %eax,0x48(%esp)
 1182b50:	8b 44 24 48          	mov    0x48(%esp),%eax
 1182b54:	89 44 24 04          	mov    %eax,0x4(%esp)
 1182b58:	8d b4 24 20 0a 00 00 	lea    0xa20(%esp),%esi
 1182b5f:	89 34 24             	mov    %esi,(%esp)
 1182b62:	c7 44 24 0c 85 eb 91 	movl   $0x3f91eb85,0xc(%esp)
 1182b69:	3f 
 1182b6a:	c7 44 24 08 ec 51 b8 	movl   $0x1eb851ec,0x8(%esp)
 1182b71:	1e 
 1182b72:	e8 79 8e 6a 00       	call   182b9f0 <operator*(YYRValue const&, double)@plt>
 1182b77:	83 ec 04             	sub    $0x4,%esp
 1182b7a:	89 74 24 04          	mov    %esi,0x4(%esp)
 1182b7e:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 1182b85:	89 04 24             	mov    %eax,(%esp)
 1182b88:	e8 d3 8b 6a 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 1182b8d:	8b 84 24 2c 0a 00 00 	mov    0xa2c(%esp),%eax
 1182b94:	b9 46 00 00 00       	mov    $0x46,%ecx
 1182b99:	0f a3 c1             	bt     %eax,%ecx
 1182b9c:	73 0f                	jae    1182bad <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x855d>
 1182b9e:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 1182ba5:	89 04 24             	mov    %eax,(%esp)
 1182ba8:	e8 13 8b 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 1182bad:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 1182bb4:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 1182bbb:	8b 44 24 44          	mov    0x44(%esp),%eax
 1182bbf:	89 44 24 04          	mov    %eax,0x4(%esp)
 1182bc3:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 1182bca:	89 04 24             	mov    %eax,(%esp)
 1182bcd:	e8 9e 8b 6a 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 1182bd2:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 1182bd9:	89 84 24 fc 0a 00 00 	mov    %eax,0xafc(%esp)
 1182be0:	8b 84 24 a8 00 00 00 	mov    0xa8(%esp),%eax
 1182be7:	89 44 24 04          	mov    %eax,0x4(%esp)
 1182beb:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 1182bf2:	89 04 24             	mov    %eax,(%esp)
 1182bf5:	e8 76 8b 6a 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 1182bfa:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 1182c01:	89 84 24 00 0b 00 00 	mov    %eax,0xb00(%esp)
 1182c08:	8b 44 24 60          	mov    0x60(%esp),%eax
 1182c0c:	8b 40 04             	mov    0x4(%eax),%eax
 1182c0f:	8d 8c 24 f8 0a 00 00 	lea    0xaf8(%esp),%ecx
 1182c16:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 1182c1a:	89 44 24 10          	mov    %eax,0x10(%esp)
 1182c1e:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 1182c25:	89 44 24 08          	mov    %eax,0x8(%esp)
 1182c29:	8b 45 0c             	mov    0xc(%ebp),%eax
 1182c2c:	89 44 24 04          	mov    %eax,0x4(%esp)
 1182c30:	8b 45 08             	mov    0x8(%ebp),%eax
 1182c33:	89 04 24             	mov    %eax,(%esp)
 1182c36:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
 1182c3d:	00 
 1182c3e:	e8 bd 8b 6a 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 1182c43:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 1182c4a:	00 00 00 00 
 1182c4e:	c7 84 24 24 0a 00 00 	movl   $0x40590000,0xa24(%esp)
 1182c55:	00 00 59 40 
 1182c59:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 1182c60:	00 00 00 00 
 1182c64:	89 44 24 04          	mov    %eax,0x4(%esp)
 1182c68:	8d b4 24 20 0a 00 00 	lea    0xa20(%esp),%esi
 1182c6f:	89 34 24             	mov    %esi,(%esp)
 1182c72:	e8 a9 8c 6a 00       	call   182b920 <YYRValue::operator+=(YYRValue const&)@plt>
 1182c77:	8b 44 24 24          	mov    0x24(%esp),%eax
 1182c7b:	f2 0f 10 00          	movsd  (%eax),%xmm0
 1182c7f:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 1182c85:	89 74 24 04          	mov    %esi,0x4(%esp)
 1182c89:	8b 44 24 50          	mov    0x50(%esp),%eax
 1182c8d:	89 04 24             	mov    %eax,(%esp)
 1182c90:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
 1182c97:	00 
 1182c98:	e8 23 8b 6a 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 1182c9d:	89 c7                	mov    %eax,%edi
 1182c9f:	8b 84 24 2c 0a 00 00 	mov    0xa2c(%esp),%eax
 1182ca6:	b9 46 00 00 00       	mov    $0x46,%ecx
 1182cab:	0f a3 c1             	bt     %eax,%ecx
 1182cae:	73 08                	jae    1182cb8 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8668>
 1182cb0:	89 34 24             	mov    %esi,(%esp)
 1182cb3:	e8 08 8a 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 1182cb8:	85 ff                	test   %edi,%edi
 1182cba:	7e 7c                	jle    1182d38 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x86e8>
 1182cbc:	c7 84 24 18 0a 00 00 	movl   $0x180,0xa18(%esp)
 1182cc3:	80 01 00 00 
 1182cc7:	8b 4d 08             	mov    0x8(%ebp),%ecx
 1182cca:	8b 01                	mov    (%ecx),%eax
 1182ccc:	8b 40 0c             	mov    0xc(%eax),%eax
 1182ccf:	89 0c 24             	mov    %ecx,(%esp)
 1182cd2:	c7 44 24 04 b4 92 01 	movl   $0x192b4,0x4(%esp) # verified field ID: tire_heat
 1182cd9:	00 
 1182cda:	ff d0                	call   *%eax
 1182cdc:	89 44 24 50          	mov    %eax,0x50(%esp)
 1182ce0:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 1182ce7:	00 00 00 00 
 1182ceb:	c7 84 24 24 0a 00 00 	movl   $0x3fc99999,0xa24(%esp)
 1182cf2:	99 99 c9 3f 
 1182cf6:	c7 84 24 20 0a 00 00 	movl   $0x9999999a,0xa20(%esp)
 1182cfd:	9a 99 99 99 
 1182d01:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 1182d08:	89 44 24 04          	mov    %eax,0x4(%esp)
 1182d0c:	8b 44 24 50          	mov    0x50(%esp),%eax
 1182d10:	89 04 24             	mov    %eax,(%esp)
 1182d13:	e8 18 8d 6a 00       	call   182ba30 <YYRValue::operator-=(YYRValue const&)@plt>
 1182d18:	8b 84 24 2c 0a 00 00 	mov    0xa2c(%esp),%eax
 1182d1f:	b9 46 00 00 00       	mov    $0x46,%ecx
 1182d24:	0f a3 c1             	bt     %eax,%ecx
 1182d27:	73 0f                	jae    1182d38 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x86e8>
 1182d29:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 1182d30:	89 04 24             	mov    %eax,(%esp)
 1182d33:	e8 88 89 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 1182d38:	c7 84 24 18 0a 00 00 	movl   $0x184,0xa18(%esp)
 1182d3f:	84 01 00 00 
 1182d43:	8b 84 24 cc 06 00 00 	mov    0x6cc(%esp),%eax
 1182d4a:	b9 46 00 00 00       	mov    $0x46,%ecx
 1182d4f:	0f a3 c1             	bt     %eax,%ecx
 1182d52:	73 0f                	jae    1182d63 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8713>
 1182d54:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 1182d5b:	89 04 24             	mov    %eax,(%esp)
 1182d5e:	e8 5d 89 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 1182d63:	c7 84 24 c0 06 00 00 	movl   $0x0,0x6c0(%esp)
 1182d6a:	00 00 00 00 
 1182d6e:	c7 84 24 c8 06 00 00 	movl   $0x0,0x6c8(%esp)
 1182d75:	00 00 00 00 
 1182d79:	c7 84 24 cc 06 00 00 	movl   $0x5,0x6cc(%esp)
 1182d80:	05 00 00 00 
 1182d84:	8b 44 24 50          	mov    0x50(%esp),%eax
 1182d88:	89 44 24 04          	mov    %eax,0x4(%esp)
 1182d8c:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 1182d93:	89 04 24             	mov    %eax,(%esp)
 1182d96:	e8 c5 89 6a 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 1182d9b:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 1182da2:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 1182da9:	8d 84 24 b0 08 00 00 	lea    0x8b0(%esp),%eax
 1182db0:	89 84 24 fc 0a 00 00 	mov    %eax,0xafc(%esp)
 1182db7:	8b 83 1c d2 ff ff    	mov    -0x2de4(%ebx),%eax
 1182dbd:	89 44 24 04          	mov    %eax,0x4(%esp)
 1182dc1:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 1182dc8:	89 04 24             	mov    %eax,(%esp)
 1182dcb:	e8 a0 89 6a 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 1182dd0:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 1182dd7:	89 84 24 00 0b 00 00 	mov    %eax,0xb00(%esp)
 1182dde:	8b 44 24 60          	mov    0x60(%esp),%eax
 1182de2:	8b 40 04             	mov    0x4(%eax),%eax
 1182de5:	8d 8c 24 f8 0a 00 00 	lea    0xaf8(%esp),%ecx
 1182dec:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 1182df0:	89 44 24 10          	mov    %eax,0x10(%esp)
 1182df4:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 1182dfb:	89 44 24 08          	mov    %eax,0x8(%esp)
 1182dff:	8b 45 0c             	mov    0xc(%ebp),%eax
 1182e02:	89 44 24 04          	mov    %eax,0x4(%esp)
 1182e06:	8b 45 08             	mov    0x8(%ebp),%eax
 1182e09:	89 04 24             	mov    %eax,(%esp)
 1182e0c:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
 1182e13:	00 
 1182e14:	e8 e7 89 6a 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 1182e19:	89 c7                	mov    %eax,%edi
 1182e1b:	8b 45 08             	mov    0x8(%ebp),%eax
 1182e1e:	89 04 24             	mov    %eax,(%esp)
 1182e21:	e8 6a 89 6a 00       	call   182b790 <PushContextStack(YYObjectBase*)@plt>
 1182e26:	89 7c 24 04          	mov    %edi,0x4(%esp)
 1182e2a:	8b 44 24 50          	mov    0x50(%esp),%eax
 1182e2e:	89 04 24             	mov    %eax,(%esp)
 1182e31:	e8 2a 89 6a 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 1182e36:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 1182e3d:	e8 5e 89 6a 00       	call   182b7a0 <PopContextStack(int)@plt>
 1182e42:	c7 84 24 18 0a 00 00 	movl   $0x193,0xa18(%esp)
 1182e49:	93 01 00 00 
 1182e4d:	8b 4d 08             	mov    0x8(%ebp),%ecx
 1182e50:	8b 01                	mov    (%ecx),%eax
 1182e52:	8b 40 0c             	mov    0xc(%eax),%eax
 1182e55:	89 0c 24             	mov    %ecx,(%esp)
 1182e58:	c7 44 24 04 8a 8a 01 	movl   $0x18a8a,0x4(%esp)
 1182e5f:	00 
 11830eb:	98 01 00 00 
 11830ef:	8b 84 24 cc 06 00 00 	mov    0x6cc(%esp),%eax
 11830f6:	0f a3 c7             	bt     %eax,%edi
 11830f9:	73 0f                	jae    118310a <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8aba>
 11830fb:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 1183102:	89 04 24             	mov    %eax,(%esp)
 1183105:	e8 b6 85 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118310a:	c7 84 24 c0 06 00 00 	movl   $0x0,0x6c0(%esp)
 1183111:	00 00 00 00 
 1183115:	c7 84 24 c8 06 00 00 	movl   $0x0,0x6c8(%esp)
 118311c:	00 00 00 00 
 1183120:	c7 84 24 cc 06 00 00 	movl   $0x5,0x6cc(%esp)
 1183127:	05 00 00 00 
 118312b:	8b 75 08             	mov    0x8(%ebp),%esi
 118312e:	8b 06                	mov    (%esi),%eax
 1183130:	8b 40 08             	mov    0x8(%eax),%eax
 1183133:	89 34 24             	mov    %esi,(%esp)
 1183136:	c7 44 24 04 49 8b 01 	movl   $0x18b49,0x4(%esp)
 118313d:	00 
 118313e:	ff d0                	call   *%eax
 1183140:	89 84 24 a8 00 00 00 	mov    %eax,0xa8(%esp)
 1183147:	8b 06                	mov    (%esi),%eax
 1183149:	8b 40 08             	mov    0x8(%eax),%eax
 118314c:	89 34 24             	mov    %esi,(%esp)
 118314f:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 1183156:	00 
 1183157:	ff d0                	call   *%eax
 1183159:	89 44 24 7c          	mov    %eax,0x7c(%esp)
 118315d:	8b 06                	mov    (%esi),%eax
 118315f:	8b 40 0c             	mov    0xc(%eax),%eax
 1183162:	89 34 24             	mov    %esi,(%esp)
 1183165:	c7 44 24 04 8d 8a 01 	movl   $0x18a8d,0x4(%esp)
 118316c:	00 
 118316d:	ff d0                	call   *%eax
 118316f:	89 c6                	mov    %eax,%esi
 1183171:	8b 44 24 7c          	mov    0x7c(%esp),%eax
 1183175:	89 44 24 04          	mov    %eax,0x4(%esp)
 1183179:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 1183180:	89 04 24             	mov    %eax,(%esp)
 1183183:	e8 d8 85 6a 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 1183188:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 118318f:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 1183196:	8b 44 24 44          	mov    0x44(%esp),%eax
 118319a:	89 44 24 04          	mov    %eax,0x4(%esp)
 118319e:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 11831a5:	89 04 24             	mov    %eax,(%esp)
 11831a8:	e8 c3 85 6a 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 11831ad:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 11831b4:	89 84 24 fc 0a 00 00 	mov    %eax,0xafc(%esp)
 11831bb:	8b 84 24 a0 00 00 00 	mov    0xa0(%esp),%eax
 11831c2:	89 44 24 04          	mov    %eax,0x4(%esp)
 11831c6:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 11831cd:	89 04 24             	mov    %eax,(%esp)
 11831d0:	e8 9b 85 6a 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 11831d5:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 11831dc:	89 84 24 00 0b 00 00 	mov    %eax,0xb00(%esp)
 11831e3:	8b 44 24 38          	mov    0x38(%esp),%eax
 11831e7:	f7 40 0c ff ff ff 00 	testl  $0xffffff,0xc(%eax)
 11831ee:	74 1a                	je     118320a <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8bba>
 11831f0:	89 04 24             	mov    %eax,(%esp)
 11831f3:	e8 e8 85 6a 00       	call   182b7e0 <REAL_RValue_Ex(RValue const*)@plt>
 11831f8:	dd 9c 24 c0 04 00 00 	fstpl  0x4c0(%esp)
 11831ff:	f2 0f 10 84 24 c0 04 	movsd  0x4c0(%esp),%xmm0
 1183206:	00 00 
 1183208:	eb 04                	jmp    118320e <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x8bbe>
 118320a:	f2 0f 10 00          	movsd  (%eax),%xmm0
 118320e:	66 0f 57 83 90 62 bc 	xorpd  -0x1439d70(%ebx),%xmm0
 1183215:	fe 
 1183216:	c7 84 24 dc 05 00 00 	movl   $0x0,0x5dc(%esp)
 118321d:	00 00 00 00 
 1183221:	66 0f 13 84 24 d0 05 	movlpd %xmm0,0x5d0(%esp)
 1183228:	00 00 
 118322a:	8b 84 24 a8 00 00 00 	mov    0xa8(%esp),%eax
 1183231:	89 44 24 08          	mov    %eax,0x8(%esp)
 1183235:	8d 84 24 d0 05 00 00 	lea    0x5d0(%esp),%eax
 118323c:	89 44 24 04          	mov    %eax,0x4(%esp)
 1183240:	8d 84 24 e0 05 00 00 	lea    0x5e0(%esp),%eax
 1183247:	89 04 24             	mov    %eax,(%esp)
 118324a:	e8 d1 88 6a 00       	call   182bb20 <operator*(YYRValue const&, YYRValue const&)@plt>
 118324f:	83 ec 04             	sub    $0x4,%esp
 1183252:	8b 44 24 60          	mov    0x60(%esp),%eax
 1183256:	8b 40 04             	mov    0x4(%eax),%eax
 1183259:	8d 8c 24 f8 0a 00 00 	lea    0xaf8(%esp),%ecx
 1183260:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 1183264:	89 44 24 10          	mov    %eax,0x10(%esp)
 1183268:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 118326f:	89 44 24 08          	mov    %eax,0x8(%esp)
 1183273:	8b 45 0c             	mov    0xc(%ebp),%eax
 1183276:	89 44 24 04          	mov    %eax,0x4(%esp)
 118327a:	8b 45 08             	mov    0x8(%ebp),%eax
 118327d:	89 04 24             	mov    %eax,(%esp)
 1183280:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
 1183287:	00 
 1183288:	e8 73 85 6a 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 118328d:	8d bc 24 f0 05 00 00 	lea    0x5f0(%esp),%edi
 1183294:	89 44 24 08          	mov    %eax,0x8(%esp)
 1183298:	8d 84 24 e0 05 00 00 	lea    0x5e0(%esp),%eax
 118329f:	89 44 24 04          	mov    %eax,0x4(%esp)
 11832a3:	89 3c 24             	mov    %edi,(%esp)
 11832a6:	e8 75 88 6a 00       	call   182bb20 <operator*(YYRValue const&, YYRValue const&)@plt>
 11832ab:	83 ec 04             	sub    $0x4,%esp
 11832ae:	89 7c 24 04          	mov    %edi,0x4(%esp)
 11832b2:	8d bc 24 00 06 00 00 	lea    0x600(%esp),%edi
 11832b9:	89 3c 24             	mov    %edi,(%esp)
 11832bc:	c7 44 24 0c 00 80 76 	movl   $0x40768000,0xc(%esp)
 11832c3:	40 
 11832c4:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 11832cb:	00 
 11832cc:	e8 ff 86 6a 00       	call   182b9d0 <operator/(YYRValue const&, double)@plt>
 118388a:	89 0c 24             	mov    %ecx,(%esp)
 118388d:	c7 44 24 04 d5 95 01 	movl   $0x195d5,0x4(%esp) # verified field ID: xspeed
 1183894:	00 
 1183895:	ff d0                	call   *%eax
 1183897:	89 44 24 38          	mov    %eax,0x38(%esp)
 118389b:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118389e:	8b 01                	mov    (%ecx),%eax
 11838a0:	8b 40 0c             	mov    0xc(%eax),%eax
 11838a3:	89 0c 24             	mov    %ecx,(%esp)
 11838a6:	c7 44 24 04 8a 8a 01 	movl   $0x18a8a,0x4(%esp)
 11838ad:	00 
 11838ae:	ff d0                	call   *%eax
 11838b0:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11838b3:	8b 01                	mov    (%ecx),%eax
 11838b5:	8b 40 08             	mov    0x8(%eax),%eax
 11838b8:	89 0c 24             	mov    %ecx,(%esp)
 11838bb:	c7 44 24 04 49 8b 01 	movl   $0x18b49,0x4(%esp)
 11838c2:	00 
 11838c3:	ff d0                	call   *%eax
 11838c5:	89 84 24 a8 00 00 00 	mov    %eax,0xa8(%esp)
 11838cc:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11838cf:	8b 01                	mov    (%ecx),%eax
 11838d1:	8b 40 08             	mov    0x8(%eax),%eax
 11838d4:	89 0c 24             	mov    %ecx,(%esp)
 11838d7:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 11838de:	00 
 11838df:	ff d0                	call   *%eax
 11838e1:	89 44 24 7c          	mov    %eax,0x7c(%esp)
 11838e5:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11838e8:	8b 01                	mov    (%ecx),%eax
 11838ea:	8b 40 0c             	mov    0xc(%eax),%eax
 11838ed:	89 0c 24             	mov    %ecx,(%esp)
 11838f0:	c7 44 24 04 8e 8a 01 	movl   $0x18a8e,0x4(%esp)
 11838f7:	00 
 11838f8:	ff d0                	call   *%eax
 11838fa:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11838fd:	8b 01                	mov    (%ecx),%eax
 11838ff:	8b 40 0c             	mov    0xc(%eax),%eax
 1183902:	89 0c 24             	mov    %ecx,(%esp)
 1183905:	c7 44 24 04 8c 8a 01 	movl   $0x18a8c,0x4(%esp)
 118390c:	00 
 118390d:	ff d0                	call   *%eax
 118390f:	89 c6                	mov    %eax,%esi
 1183911:	8b 83 b0 fc fe ff    	mov    -0x10350(%ebx),%eax
 1183917:	8b 40 04             	mov    0x4(%eax),%eax
 118391a:	8d bc 24 80 09 00 00 	lea    0x980(%esp),%edi
 1183921:	89 7c 24 0c          	mov    %edi,0xc(%esp)
 1183925:	89 44 24 04          	mov    %eax,0x4(%esp)
 1183929:	8b 45 08             	mov    0x8(%ebp),%eax
 118392c:	89 04 24             	mov    %eax,(%esp)
 118392f:	c7 44 24 14 00 00 00 	movl   $0x0,0x14(%esp)
 1183936:	00 
 1183937:	c7 44 24 10 00 00 00 	movl   $0x0,0x10(%esp)
 118393e:	00 
 118393f:	c7 44 24 08 00 00 00 	movl   $0x80000000,0x8(%esp)
 1183946:	80 
 1183947:	e8 f4 82 6a 00       	call   182bc40 <Variable_GetValue_Direct(YYObjectBase*, int, int, RValue*, bool, bool)@plt>
 118394c:	f7 84 24 8c 09 00 00 	testl  $0xffffff,0x98c(%esp)
 1183953:	ff ff ff 00 
 1183957:	74 1a                	je     1183973 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x9323>
 1183959:	89 3c 24             	mov    %edi,(%esp)
 118395c:	e8 7f 7e 6a 00       	call   182b7e0 <REAL_RValue_Ex(RValue const*)@plt>
 1183961:	dd 9c 24 98 04 00 00 	fstpl  0x498(%esp)
 1183968:	f2 0f 10 84 24 98 04 	movsd  0x498(%esp),%xmm0
 118396f:	00 00 
 1183971:	eb 09                	jmp    118397c <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x932c>
 1183973:	f2 0f 10 84 24 80 09 	movsd  0x980(%esp),%xmm0
 118397a:	00 00 
 118397c:	66 0f 57 83 90 62 bc 	xorpd  -0x1439d70(%ebx),%xmm0
 1183983:	fe 
 1183984:	c7 84 24 0c 06 00 00 	movl   $0x0,0x60c(%esp)
 118398b:	00 00 00 00 
 118398f:	66 0f 13 84 24 00 06 	movlpd %xmm0,0x600(%esp)
 1183996:	00 00 
 1183998:	8d 84 24 00 06 00 00 	lea    0x600(%esp),%eax
 118399f:	89 44 24 04          	mov    %eax,0x4(%esp)
 11839a3:	8d bc 24 20 0a 00 00 	lea    0xa20(%esp),%edi
 11839aa:	89 3c 24             	mov    %edi,(%esp)
 11839ad:	c7 44 24 0c fb 21 09 	movl   $0x400921fb,0xc(%esp)
 11839b4:	40 
 11839b5:	c7 44 24 08 18 2d 44 	movl   $0x54442d18,0x8(%esp)
 11839bc:	54 
 11839bd:	e8 2e 80 6a 00       	call   182b9f0 <operator*(YYRValue const&, double)@plt>
 11839c2:	83 ec 04             	sub    $0x4,%esp
 11839c5:	8b 45 08             	mov    0x8(%ebp),%eax
 11839c8:	89 04 24             	mov    %eax,(%esp)
 11839cb:	e8 c0 7d 6a 00       	call   182b790 <PushContextStack(YYObjectBase*)@plt>
 11839d0:	89 7c 24 04          	mov    %edi,0x4(%esp)
 11839d4:	89 34 24             	mov    %esi,(%esp)
 11839d7:	e8 84 7d 6a 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 11839dc:	8b 84 24 2c 0a 00 00 	mov    0xa2c(%esp),%eax
 11839e3:	be 46 00 00 00       	mov    $0x46,%esi
 11839e8:	0f a3 c6             	bt     %eax,%esi
 11839eb:	73 0f                	jae    11839fc <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x93ac>
 11839ed:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 11839f4:	89 04 24             	mov    %eax,(%esp)
 11839f7:	e8 c4 7c 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11839fc:	8b 84 24 0c 06 00 00 	mov    0x60c(%esp),%eax
 1183a03:	0f a3 c6             	bt     %eax,%esi
 1183a06:	73 0f                	jae    1183a17 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x93c7>
 1183a08:	8d 84 24 00 06 00 00 	lea    0x600(%esp),%eax
 1183a0f:	89 04 24             	mov    %eax,(%esp)
 1183a12:	e8 a9 7c 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 1183a17:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 1183a1e:	e8 7d 7d 6a 00       	call   182b7a0 <PopContextStack(int)@plt>
 1183a23:	c7 84 24 18 0a 00 00 	movl   $0x1a2,0xa18(%esp)
 1183a2a:	a2 01 00 00 
 1183a2e:	8b 4d 08             	mov    0x8(%ebp),%ecx
 1183a31:	8b 01                	mov    (%ecx),%eax
 1184970:	8b 06                	mov    (%esi),%eax
 1184972:	8b 40 0c             	mov    0xc(%eax),%eax
 1184975:	89 34 24             	mov    %esi,(%esp)
 1184978:	c7 44 24 04 d5 95 01 	movl   $0x195d5,0x4(%esp) # verified field ID: xspeed
 118497f:	00 
 1184980:	ff d0                	call   *%eax
 1184982:	89 44 24 38          	mov    %eax,0x38(%esp)
 1184986:	8b 06                	mov    (%esi),%eax
 1184988:	8b 40 08             	mov    0x8(%eax),%eax
 118498b:	89 34 24             	mov    %esi,(%esp)
 118498e:	c7 44 24 04 da 8e 01 	movl   $0x18eda,0x4(%esp) # verified field ID: max_xspeed
 1184995:	00 
 1184996:	ff d0                	call   *%eax
 1184998:	89 c7                	mov    %eax,%edi
 118499a:	8b 06                	mov    (%esi),%eax
 118499c:	8b 40 08             	mov    0x8(%eax),%eax
 118499f:	89 34 24             	mov    %esi,(%esp)
 11849a2:	c7 44 24 04 1a 8c 01 	movl   $0x18c1a,0x4(%esp)
 11849a9:	00 
 11849aa:	ff d0                	call   *%eax
 11849ac:	89 44 24 68          	mov    %eax,0x68(%esp)
 11849b0:	8b 06                	mov    (%esi),%eax
 11849b2:	8b 40 0c             	mov    0xc(%eax),%eax
 11849b5:	89 34 24             	mov    %esi,(%esp)
 11849b8:	c7 44 24 04 ca 95 01 	movl   $0x195ca,0x4(%esp) # verified field ID: wind_friction
 11849bf:	00 
 11849c0:	ff d0                	call   *%eax
 11849c2:	89 84 24 34 01 00 00 	mov    %eax,0x134(%esp)
 11849c9:	c7 84 24 ec 05 00 00 	movl   $0x0,0x5ec(%esp)
 11849d0:	00 00 00 00 
 11849d4:	c7 84 24 e4 05 00 00 	movl   $0x3ff00000,0x5e4(%esp)
 11849db:	00 00 f0 3f 
 11849df:	c7 84 24 e0 05 00 00 	movl   $0x0,0x5e0(%esp)
 11849e6:	00 00 00 00 
 11849ea:	89 7c 24 04          	mov    %edi,0x4(%esp)
 11849ee:	8d bc 24 e0 05 00 00 	lea    0x5e0(%esp),%edi
 11849f5:	89 3c 24             	mov    %edi,(%esp)
 11849f8:	e8 73 70 6a 00       	call   182ba70 <YYRValue::operator/=(YYRValue const&)@plt>
 11849fd:	89 7c 24 08          	mov    %edi,0x8(%esp)
 1184a01:	8b 44 24 38          	mov    0x38(%esp),%eax
 1184a05:	89 44 24 04          	mov    %eax,0x4(%esp)
 1184a09:	8d bc 24 f0 05 00 00 	lea    0x5f0(%esp),%edi
 1184a10:	89 3c 24             	mov    %edi,(%esp)
 1184a13:	e8 08 71 6a 00       	call   182bb20 <operator*(YYRValue const&, YYRValue const&)@plt>
 1184a18:	83 ec 04             	sub    $0x4,%esp
 1184a1b:	c7 84 24 0c 06 00 00 	movl   $0x0,0x60c(%esp)
 1184a22:	00 00 00 00 
 1184a26:	c7 84 24 04 06 00 00 	movl   $0x3ff00000,0x604(%esp)
 1184a2d:	00 00 f0 3f 
 1184a31:	c7 84 24 00 06 00 00 	movl   $0x0,0x600(%esp)
 1184a38:	00 00 00 00 
 1184a3c:	89 7c 24 04          	mov    %edi,0x4(%esp)
 1184a40:	8d bc 24 00 06 00 00 	lea    0x600(%esp),%edi
 1184a47:	89 3c 24             	mov    %edi,(%esp)
 1184a4a:	e8 e1 6f 6a 00       	call   182ba30 <YYRValue::operator-=(YYRValue const&)@plt>
 1184a4f:	8b 44 24 68          	mov    0x68(%esp),%eax
 1184a53:	89 44 24 08          	mov    %eax,0x8(%esp)
 1184a57:	89 7c 24 04          	mov    %edi,0x4(%esp)
 1184a5b:	8d b4 24 20 0a 00 00 	lea    0xa20(%esp),%esi
 1184a62:	89 34 24             	mov    %esi,(%esp)
 1184a65:	e8 f6 6d 6a 00       	call   182b860 <operator+(YYRValue const&, YYRValue const&)@plt>
 1184a6a:	83 ec 04             	sub    $0x4,%esp
 1184a6d:	89 74 24 04          	mov    %esi,0x4(%esp)
 1184a71:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 1184a78:	89 04 24             	mov    %eax,(%esp)
 1184a7b:	e8 e0 6c 6a 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 1184a80:	8b 84 24 2c 0a 00 00 	mov    0xa2c(%esp),%eax
 1184a87:	be 46 00 00 00       	mov    $0x46,%esi
 1184a8c:	0f a3 c6             	bt     %eax,%esi
 1184a8f:	73 0f                	jae    1184aa0 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa450>
 1184a91:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 1184a98:	89 04 24             	mov    %eax,(%esp)
 1184a9b:	e8 20 6c 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 1184aa0:	8b 84 24 0c 06 00 00 	mov    0x60c(%esp),%eax
 1184aa7:	0f a3 c6             	bt     %eax,%esi
 1184aaa:	73 0f                	jae    1184abb <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa46b>
 1184aac:	8d 84 24 00 06 00 00 	lea    0x600(%esp),%eax
 1184ab3:	89 04 24             	mov    %eax,(%esp)
 1184ab6:	e8 05 6c 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 1184abb:	8b 84 24 fc 05 00 00 	mov    0x5fc(%esp),%eax
 1184ac2:	be 46 00 00 00       	mov    $0x46,%esi
 1184ac7:	0f a3 c6             	bt     %eax,%esi
 1184aca:	73 0f                	jae    1184adb <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa48b>
 1184acc:	8d 84 24 f0 05 00 00 	lea    0x5f0(%esp),%eax
 1184ad3:	89 04 24             	mov    %eax,(%esp)
 1184ad6:	e8 e5 6b 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 1184adb:	8b 84 24 ec 05 00 00 	mov    0x5ec(%esp),%eax
 1184ae2:	0f a3 c6             	bt     %eax,%esi
 1184ae5:	73 0f                	jae    1184af6 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa4a6>
 1184ae7:	8d 84 24 e0 05 00 00 	lea    0x5e0(%esp),%eax
 1184aee:	89 04 24             	mov    %eax,(%esp)
 1184af1:	e8 ca 6b 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 1184af6:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 1184afd:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 1184b04:	8b 44 24 44          	mov    0x44(%esp),%eax
 1184b08:	89 44 24 04          	mov    %eax,0x4(%esp)
 1184b0c:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 1184b13:	89 04 24             	mov    %eax,(%esp)
 1184b16:	e8 55 6c 6a 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 1184b1b:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 1184b22:	89 84 24 fc 0a 00 00 	mov    %eax,0xafc(%esp)
 1184b29:	8b 84 24 a0 00 00 00 	mov    0xa0(%esp),%eax
 1184b30:	89 44 24 04          	mov    %eax,0x4(%esp)
 1184b34:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 1184b3b:	89 04 24             	mov    %eax,(%esp)
 1184b3e:	e8 2d 6c 6a 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 1184b43:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 1184b4a:	89 84 24 00 0b 00 00 	mov    %eax,0xb00(%esp)
 1184b51:	8b 44 24 60          	mov    0x60(%esp),%eax
 1184d89:	89 44 24 08          	mov    %eax,0x8(%esp)
 1184d8d:	8b 45 0c             	mov    0xc(%ebp),%eax
 1184d90:	89 44 24 04          	mov    %eax,0x4(%esp)
 1184d94:	8b 45 08             	mov    0x8(%ebp),%eax
 1184d97:	89 04 24             	mov    %eax,(%esp)
 1184d9a:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
 1184da1:	00 
 1184da2:	e8 59 6a 6a 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 1184da7:	89 c7                	mov    %eax,%edi
 1184da9:	8b 45 08             	mov    0x8(%ebp),%eax
 1184dac:	89 04 24             	mov    %eax,(%esp)
 1184daf:	e8 dc 69 6a 00       	call   182b790 <PushContextStack(YYObjectBase*)@plt>
 1184db4:	89 7c 24 04          	mov    %edi,0x4(%esp)
 1184db8:	89 34 24             	mov    %esi,(%esp)
 1184dbb:	e8 a0 69 6a 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 1184dc0:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 1184dc7:	e8 d4 69 6a 00       	call   182b7a0 <PopContextStack(int)@plt>
 1184dcc:	e9 96 00 00 00       	jmp    1184e67 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa817>
 1184dd1:	c7 84 24 18 0a 00 00 	movl   $0x1dd,0xa18(%esp)
 1184dd8:	dd 01 00 00 
 1184ddc:	8b 4d 08             	mov    0x8(%ebp),%ecx
 1184ddf:	8b 01                	mov    (%ecx),%eax
 1184de1:	8b 40 0c             	mov    0xc(%eax),%eax
 1184de4:	89 0c 24             	mov    %ecx,(%esp)
 1184de7:	c7 44 24 04 ca 95 01 	movl   $0x195ca,0x4(%esp) # verified field ID: wind_friction
 1184dee:	00 
 1184def:	ff d0                	call   *%eax
 1184df1:	89 c6                	mov    %eax,%esi
 1184df3:	8b 40 0c             	mov    0xc(%eax),%eax
 1184df6:	b9 46 00 00 00       	mov    $0x46,%ecx
 1184dfb:	0f a3 c1             	bt     %eax,%ecx
 1184dfe:	73 08                	jae    1184e08 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa7b8>
 1184e00:	89 34 24             	mov    %esi,(%esp)
 1184e03:	e8 b8 68 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 1184e08:	c7 46 0c 00 00 00 00 	movl   $0x0,0xc(%esi)
 1184e0f:	c7 46 04 00 00 f0 3f 	movl   $0x3ff00000,0x4(%esi)
 1184e16:	c7 06 00 00 00 00    	movl   $0x0,(%esi)
 1184e1c:	c7 84 24 18 0a 00 00 	movl   $0x1de,0xa18(%esp)
 1184e23:	de 01 00 00 
 1184e27:	8b 4d 08             	mov    0x8(%ebp),%ecx
 1184e2a:	8b 01                	mov    (%ecx),%eax
 1184e2c:	8b 40 0c             	mov    0xc(%eax),%eax
 1184e2f:	89 0c 24             	mov    %ecx,(%esp)
 1184e32:	c7 44 24 04 b9 95 01 	movl   $0x195b9,0x4(%esp) # verified field ID: weight_to_power
 1184e39:	00 
 1184e3a:	ff d0                	call   *%eax
 1184e3c:	89 c6                	mov    %eax,%esi
 1184e3e:	8b 40 0c             	mov    0xc(%eax),%eax
 1184e41:	b9 46 00 00 00       	mov    $0x46,%ecx
 1184e46:	0f a3 c1             	bt     %eax,%ecx
 1184e49:	73 08                	jae    1184e53 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa803>
 1184e4b:	89 34 24             	mov    %esi,(%esp)
 1184e4e:	e8 6d 68 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 1184e53:	c7 46 0c 00 00 00 00 	movl   $0x0,0xc(%esi)
 1184e5a:	c7 46 04 00 00 f0 3f 	movl   $0x3ff00000,0x4(%esi)
 1184e61:	c7 06 00 00 00 00    	movl   $0x0,(%esi)
 1184e67:	c7 84 24 18 0a 00 00 	movl   $0x1e0,0xa18(%esp)
 1184e6e:	e0 01 00 00 
 1184e72:	8b 4d 08             	mov    0x8(%ebp),%ecx
 1184e75:	8b 01                	mov    (%ecx),%eax
 1184e77:	8b 40 08             	mov    0x8(%eax),%eax
 1184e7a:	89 0c 24             	mov    %ecx,(%esp)
 1184e7d:	c7 44 24 04 1a 8c 01 	movl   $0x18c1a,0x4(%esp)
 1184e84:	00 
 1184e85:	ff d0                	call   *%eax
 1184e87:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 1184e8e:	00 00 00 00 
 1184e92:	c7 84 24 24 0a 00 00 	movl   $0x0,0xa24(%esp)
 1184e99:	00 00 00 00 
 1184e9d:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 1184ea4:	00 00 00 00 
 1184ea8:	8b 4c 24 24          	mov    0x24(%esp),%ecx
 1184eac:	f2 0f 10 01          	movsd  (%ecx),%xmm0
 1184eb0:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 1184eb6:	8d 8c 24 20 0a 00 00 	lea    0xa20(%esp),%ecx
 1184ebd:	89 4c 24 04          	mov    %ecx,0x4(%esp)
 1184ec1:	89 04 24             	mov    %eax,(%esp)
 1184ec4:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
 1184ecb:	00 
 1184ecc:	e8 ef 68 6a 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 1184ed1:	85 c0                	test   %eax,%eax
 1184ed3:	7e 76                	jle    1184f4b <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa8fb>
 1184ed5:	c7 84 24 18 0a 00 00 	movl   $0x1e2,0xa18(%esp)
 1184edc:	e2 01 00 00 
 1184ee0:	8b 4d 08             	mov    0x8(%ebp),%ecx
 1184ee3:	8b 01                	mov    (%ecx),%eax
 1184ee5:	8b 40 0c             	mov    0xc(%eax),%eax
 1184ee8:	89 0c 24             	mov    %ecx,(%esp)
 1184eeb:	c7 44 24 04 1a 8c 01 	movl   $0x18c1a,0x4(%esp)
 1184ef2:	00 
 1184ef3:	ff d0                	call   *%eax
 1184ef5:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 1184efc:	00 00 00 00 
 1184f00:	c7 84 24 24 0a 00 00 	movl   $0x3fb99999,0xa24(%esp)
 1184f07:	99 99 b9 3f 
 1184f0b:	c7 84 24 20 0a 00 00 	movl   $0x9999999a,0xa20(%esp)
 1184f12:	9a 99 99 99 
 1184f16:	8d 8c 24 20 0a 00 00 	lea    0xa20(%esp),%ecx
 1184f1d:	89 4c 24 04          	mov    %ecx,0x4(%esp)
 1184f21:	89 04 24             	mov    %eax,(%esp)
 1184f24:	e8 07 6b 6a 00       	call   182ba30 <YYRValue::operator-=(YYRValue const&)@plt>
 1184f29:	8b 84 24 2c 0a 00 00 	mov    0xa2c(%esp),%eax
 1184f30:	b9 46 00 00 00       	mov    $0x46,%ecx
 1184f35:	0f a3 c1             	bt     %eax,%ecx
 1184f38:	73 5c                	jae    1184f96 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa946>
 1184f3a:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 1184f41:	89 04 24             	mov    %eax,(%esp)
 1184f44:	e8 77 67 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 1184f49:	eb 4b                	jmp    1184f96 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xa946>
 1185072:	89 44 24 08          	mov    %eax,0x8(%esp)
 1185076:	8b 45 0c             	mov    0xc(%ebp),%eax
 1185079:	89 44 24 04          	mov    %eax,0x4(%esp)
 118507d:	8b 45 08             	mov    0x8(%ebp),%eax
 1185080:	89 04 24             	mov    %eax,(%esp)
 1185083:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
 118508a:	00 
 118508b:	e8 70 67 6a 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 1185090:	89 c6                	mov    %eax,%esi
 1185092:	8b 45 08             	mov    0x8(%ebp),%eax
 1185095:	89 04 24             	mov    %eax,(%esp)
 1185098:	e8 f3 66 6a 00       	call   182b790 <PushContextStack(YYObjectBase*)@plt>
 118509d:	89 74 24 04          	mov    %esi,0x4(%esp)
 11850a1:	8b 44 24 38          	mov    0x38(%esp),%eax
 11850a5:	89 04 24             	mov    %eax,(%esp)
 11850a8:	e8 b3 66 6a 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 11850ad:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 11850b4:	e8 e7 66 6a 00       	call   182b7a0 <PopContextStack(int)@plt>
 11850b9:	c7 84 24 18 0a 00 00 	movl   $0x1ec,0xa18(%esp)
 11850c0:	ec 01 00 00 
 11850c4:	8b 7d 08             	mov    0x8(%ebp),%edi
 11850c7:	8b 07                	mov    (%edi),%eax
 11850c9:	8b 40 0c             	mov    0xc(%eax),%eax
 11850cc:	89 3c 24             	mov    %edi,(%esp)
 11850cf:	c7 44 24 04 ca 95 01 	movl   $0x195ca,0x4(%esp) # verified field ID: wind_friction
 11850d6:	00 
 11850d7:	ff d0                	call   *%eax
 11850d9:	89 44 24 38          	mov    %eax,0x38(%esp)
 11850dd:	8b 07                	mov    (%edi),%eax
 11850df:	8b 40 0c             	mov    0xc(%eax),%eax
 11850e2:	89 3c 24             	mov    %edi,(%esp)
 11850e5:	c7 44 24 04 b9 95 01 	movl   $0x195b9,0x4(%esp) # verified field ID: weight_to_power
 11850ec:	00 
 11850ed:	ff d0                	call   *%eax
 11850ef:	89 c6                	mov    %eax,%esi
 11850f1:	8b 07                	mov    (%edi),%eax
 11850f3:	8b 40 0c             	mov    0xc(%eax),%eax
 11850f6:	89 3c 24             	mov    %edi,(%esp)
 11850f9:	c7 44 24 04 bd 90 01 	movl   $0x190bd,0x4(%esp) # verified field ID: run_acc
 1185100:	00 
 1185101:	ff d0                	call   *%eax
 1185103:	89 44 24 68          	mov    %eax,0x68(%esp)
 1185107:	c7 84 24 fc 05 00 00 	movl   $0x0,0x5fc(%esp)
 118510e:	00 00 00 00 
 1185112:	c7 84 24 f4 05 00 00 	movl   $0x3fb99999,0x5f4(%esp)
 1185119:	99 99 b9 3f 
 118511d:	c7 84 24 f0 05 00 00 	movl   $0x9999999a,0x5f0(%esp)
 1185124:	9a 99 99 99 
 1185128:	8b 84 24 80 00 00 00 	mov    0x80(%esp),%eax
 118512f:	89 44 24 04          	mov    %eax,0x4(%esp)
 1185133:	8d bc 24 f0 05 00 00 	lea    0x5f0(%esp),%edi
 118513a:	89 3c 24             	mov    %edi,(%esp)
 118513d:	e8 de 67 6a 00       	call   182b920 <YYRValue::operator+=(YYRValue const&)@plt>
 1185142:	8b 44 24 38          	mov    0x38(%esp),%eax
 1185146:	89 44 24 08          	mov    %eax,0x8(%esp)
 118514a:	89 7c 24 04          	mov    %edi,0x4(%esp)
 118514e:	8d bc 24 00 06 00 00 	lea    0x600(%esp),%edi
 1185155:	89 3c 24             	mov    %edi,(%esp)
 1185158:	e8 c3 69 6a 00       	call   182bb20 <operator*(YYRValue const&, YYRValue const&)@plt>
 118515d:	83 ec 04             	sub    $0x4,%esp
 1185160:	89 74 24 08          	mov    %esi,0x8(%esp)
 1185164:	89 7c 24 04          	mov    %edi,0x4(%esp)
 1185168:	8d b4 24 20 0a 00 00 	lea    0xa20(%esp),%esi
 118516f:	89 34 24             	mov    %esi,(%esp)
 1185172:	e8 a9 69 6a 00       	call   182bb20 <operator*(YYRValue const&, YYRValue const&)@plt>
 1185177:	83 ec 04             	sub    $0x4,%esp
 118517a:	8b 45 08             	mov    0x8(%ebp),%eax
 118517d:	89 04 24             	mov    %eax,(%esp)
 1185180:	e8 0b 66 6a 00       	call   182b790 <PushContextStack(YYObjectBase*)@plt>
 1185185:	89 74 24 04          	mov    %esi,0x4(%esp)
 1185189:	8b 44 24 68          	mov    0x68(%esp),%eax
 118518d:	89 04 24             	mov    %eax,(%esp)
 1185190:	e8 cb 65 6a 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 1185195:	8b 84 24 2c 0a 00 00 	mov    0xa2c(%esp),%eax
 118519c:	be 46 00 00 00       	mov    $0x46,%esi
 11851a1:	0f a3 c6             	bt     %eax,%esi
 11851a4:	73 0f                	jae    11851b5 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xab65>
 11851a6:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 11851ad:	89 04 24             	mov    %eax,(%esp)
 11851b0:	e8 0b 65 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11851b5:	8b 84 24 0c 06 00 00 	mov    0x60c(%esp),%eax
 11851bc:	0f a3 c6             	bt     %eax,%esi
 11851bf:	73 0f                	jae    11851d0 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xab80>
 11851c1:	8d 84 24 00 06 00 00 	lea    0x600(%esp),%eax
 11851c8:	89 04 24             	mov    %eax,(%esp)
 11851cb:	e8 f0 64 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11851d0:	8b 84 24 fc 05 00 00 	mov    0x5fc(%esp),%eax
 11851d7:	b9 46 00 00 00       	mov    $0x46,%ecx
 11851dc:	0f a3 c1             	bt     %eax,%ecx
 11851df:	73 0f                	jae    11851f0 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xaba0>
 11851e1:	8d 84 24 f0 05 00 00 	lea    0x5f0(%esp),%eax
 11851e8:	89 04 24             	mov    %eax,(%esp)
 11851eb:	e8 d0 64 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11851f0:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 11851f7:	e8 a4 65 6a 00       	call   182b7a0 <PopContextStack(int)@plt>
 11851fc:	c7 84 24 18 0a 00 00 	movl   $0x1ee,0xa18(%esp)
 1185203:	ee 01 00 00 
 1185207:	c7 84 24 2c 0a 00 00 	movl   $0xd,0xa2c(%esp)
 118520e:	0d 00 00 00 
 1185212:	c7 84 24 24 0a 00 00 	movl   $0x3ff00000,0xa24(%esp)
 1185219:	00 00 f0 3f 
 118521d:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 1185224:	00 00 00 00 
 1185228:	8b 44 24 24          	mov    0x24(%esp),%eax
 118522c:	f2 0f 10 00          	movsd  (%eax),%xmm0
 1185230:	f2 0f 11 44 24 38    	movsd  %xmm0,0x38(%esp)
 1185236:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 118523c:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 1185243:	89 44 24 04          	mov    %eax,0x4(%esp)
 11852d5:	f2 0f 10 01          	movsd  (%ecx),%xmm0
 11852d9:	f2 0f 11 44 24 38    	movsd  %xmm0,0x38(%esp)
 11852df:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 11852e5:	8d 8c 24 20 0a 00 00 	lea    0xa20(%esp),%ecx
 11852ec:	89 4c 24 04          	mov    %ecx,0x4(%esp)
 11852f0:	89 04 24             	mov    %eax,(%esp)
 11852f3:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
 11852fa:	00 
 11852fb:	e8 c0 64 6a 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 1185300:	85 c0                	test   %eax,%eax
 1185302:	0f 88 ab 01 00 00    	js     11854b3 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xae63>
 1185308:	c7 84 24 18 0a 00 00 	movl   $0x1f2,0xa18(%esp)
 118530f:	f2 01 00 00 
 1185313:	8b 75 08             	mov    0x8(%ebp),%esi
 1185316:	8b 06                	mov    (%esi),%eax
 1185318:	8b 40 0c             	mov    0xc(%eax),%eax
 118531b:	89 34 24             	mov    %esi,(%esp)
 118531e:	c7 44 24 04 a1 8d 01 	movl   $0x18da1,0x4(%esp)
 1185325:	00 
 1185326:	ff d0                	call   *%eax
 1185328:	89 c7                	mov    %eax,%edi
 118532a:	8b 06                	mov    (%esi),%eax
 118532c:	8b 40 0c             	mov    0xc(%eax),%eax
 118532f:	89 34 24             	mov    %esi,(%esp)
 1185332:	c7 44 24 04 ca 95 01 	movl   $0x195ca,0x4(%esp) # verified field ID: wind_friction
 1185339:	00 
 118533a:	ff d0                	call   *%eax
 118533c:	89 44 24 38          	mov    %eax,0x38(%esp)
 1185340:	8b 06                	mov    (%esi),%eax
 1185342:	8b 40 0c             	mov    0xc(%eax),%eax
 1185345:	89 34 24             	mov    %esi,(%esp)
 1185348:	c7 44 24 04 b9 95 01 	movl   $0x195b9,0x4(%esp) # verified field ID: weight_to_power
 118534f:	00 
 1185350:	ff d0                	call   *%eax
 1185352:	89 44 24 68          	mov    %eax,0x68(%esp)
 1185356:	8b 06                	mov    (%esi),%eax
 1185358:	8b 40 0c             	mov    0xc(%eax),%eax
 118535b:	89 34 24             	mov    %esi,(%esp)
 118535e:	c7 44 24 04 bd 90 01 	movl   $0x190bd,0x4(%esp) # verified field ID: run_acc
 1185365:	00 
 1185366:	ff d0                	call   *%eax
 1185368:	89 84 24 80 00 00 00 	mov    %eax,0x80(%esp)
 118536f:	c7 84 24 ec 05 00 00 	movl   $0x0,0x5ec(%esp)
 1185376:	00 00 00 00 
 118537a:	c7 84 24 e4 05 00 00 	movl   $0x3fb99999,0x5e4(%esp)
 1185381:	99 99 b9 3f 
 1185385:	c7 84 24 e0 05 00 00 	movl   $0x9999999a,0x5e0(%esp)
 118538c:	9a 99 99 99 
 1185390:	89 7c 24 04          	mov    %edi,0x4(%esp)
 1185394:	8d bc 24 e0 05 00 00 	lea    0x5e0(%esp),%edi
 118539b:	89 3c 24             	mov    %edi,(%esp)
 118539e:	e8 7d 65 6a 00       	call   182b920 <YYRValue::operator+=(YYRValue const&)@plt>
 11853a3:	89 7c 24 04          	mov    %edi,0x4(%esp)
 11853a7:	8d bc 24 f0 05 00 00 	lea    0x5f0(%esp),%edi
 11853ae:	89 3c 24             	mov    %edi,(%esp)
 11853b1:	c7 44 24 0c 33 33 e3 	movl   $0x3fe33333,0xc(%esp)
 11853b8:	3f 
 11853b9:	c7 44 24 08 33 33 33 	movl   $0x33333333,0x8(%esp)
 11853c0:	33 
 11853c1:	e8 2a 66 6a 00       	call   182b9f0 <operator*(YYRValue const&, double)@plt>
 11853c6:	83 ec 04             	sub    $0x4,%esp
 11853c9:	8b 44 24 38          	mov    0x38(%esp),%eax
 11853cd:	89 44 24 08          	mov    %eax,0x8(%esp)
 11853d1:	89 7c 24 04          	mov    %edi,0x4(%esp)
 11853d5:	8d bc 24 00 06 00 00 	lea    0x600(%esp),%edi
 11853dc:	89 3c 24             	mov    %edi,(%esp)
 11853df:	e8 3c 67 6a 00       	call   182bb20 <operator*(YYRValue const&, YYRValue const&)@plt>
 11853e4:	83 ec 04             	sub    $0x4,%esp
 11853e7:	8b 44 24 68          	mov    0x68(%esp),%eax
 11853eb:	89 44 24 08          	mov    %eax,0x8(%esp)
 11853ef:	89 7c 24 04          	mov    %edi,0x4(%esp)
 11853f3:	8d b4 24 20 0a 00 00 	lea    0xa20(%esp),%esi
 11853fa:	89 34 24             	mov    %esi,(%esp)
 11853fd:	e8 1e 67 6a 00       	call   182bb20 <operator*(YYRValue const&, YYRValue const&)@plt>
 1185402:	83 ec 04             	sub    $0x4,%esp
 1185405:	8b 45 08             	mov    0x8(%ebp),%eax
 1185408:	89 04 24             	mov    %eax,(%esp)
 118540b:	e8 80 63 6a 00       	call   182b790 <PushContextStack(YYObjectBase*)@plt>
 1185410:	89 74 24 04          	mov    %esi,0x4(%esp)
 1185414:	8b 84 24 80 00 00 00 	mov    0x80(%esp),%eax
 118541b:	89 04 24             	mov    %eax,(%esp)
 118541e:	e8 3d 63 6a 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 1185423:	8b 84 24 2c 0a 00 00 	mov    0xa2c(%esp),%eax
 118542a:	be 46 00 00 00       	mov    $0x46,%esi
 118542f:	0f a3 c6             	bt     %eax,%esi
 1185432:	73 0f                	jae    1185443 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xadf3>
 1185434:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 118543b:	89 04 24             	mov    %eax,(%esp)
 118543e:	e8 7d 62 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 1185443:	8b 84 24 0c 06 00 00 	mov    0x60c(%esp),%eax
 118544a:	0f a3 c6             	bt     %eax,%esi
 118544d:	73 0f                	jae    118545e <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xae0e>
 118544f:	8d 84 24 00 06 00 00 	lea    0x600(%esp),%eax
 1185456:	89 04 24             	mov    %eax,(%esp)
 1185459:	e8 62 62 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118545e:	8b 84 24 fc 05 00 00 	mov    0x5fc(%esp),%eax
 1185465:	be 46 00 00 00       	mov    $0x46,%esi
 118546a:	0f a3 c6             	bt     %eax,%esi
 118546d:	73 0f                	jae    118547e <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xae2e>
 118546f:	8d 84 24 f0 05 00 00 	lea    0x5f0(%esp),%eax
 1185476:	89 04 24             	mov    %eax,(%esp)
 1185479:	e8 42 62 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118547e:	8b 84 24 ec 05 00 00 	mov    0x5ec(%esp),%eax
 1185485:	0f a3 c6             	bt     %eax,%esi
 1185488:	73 0f                	jae    1185499 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xae49>
 118548a:	8d 84 24 e0 05 00 00 	lea    0x5e0(%esp),%eax
 1185491:	89 04 24             	mov    %eax,(%esp)
 1185494:	e8 27 62 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 1185499:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 11857f6:	89 44 24 04          	mov    %eax,0x4(%esp)
 11857fa:	8b 45 08             	mov    0x8(%ebp),%eax
 11857fd:	89 04 24             	mov    %eax,(%esp)
 1185800:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
 1185807:	00 
 1185808:	e8 f3 5f 6a 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 118580d:	89 44 24 04          	mov    %eax,0x4(%esp)
 1185811:	8d 84 24 a0 08 00 00 	lea    0x8a0(%esp),%eax
 1185818:	89 04 24             	mov    %eax,(%esp)
 118581b:	e8 40 5f 6a 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 1185820:	c7 84 24 18 0a 00 00 	movl   $0x1fb,0xa18(%esp)
 1185827:	fb 01 00 00 
 118582b:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118582e:	8b 01                	mov    (%ecx),%eax
 1185830:	8b 40 0c             	mov    0xc(%eax),%eax
 1185833:	89 0c 24             	mov    %ecx,(%esp)
 1185836:	c7 44 24 04 a1 8d 01 	movl   $0x18da1,0x4(%esp)
 118583d:	00 
 118583e:	ff d0                	call   *%eax
 1185840:	89 c7                	mov    %eax,%edi
 1185842:	8b 4d 08             	mov    0x8(%ebp),%ecx
 1185845:	8b 01                	mov    (%ecx),%eax
 1185847:	8b 40 0c             	mov    0xc(%eax),%eax
 118584a:	89 0c 24             	mov    %ecx,(%esp)
 118584d:	c7 44 24 04 ca 95 01 	movl   $0x195ca,0x4(%esp) # verified field ID: wind_friction
 1185854:	00 
 1185855:	ff d0                	call   *%eax
 1185857:	89 44 24 38          	mov    %eax,0x38(%esp)
 118585b:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118585e:	8b 01                	mov    (%ecx),%eax
 1185860:	8b 40 0c             	mov    0xc(%eax),%eax
 1185863:	89 0c 24             	mov    %ecx,(%esp)
 1185866:	c7 44 24 04 b9 95 01 	movl   $0x195b9,0x4(%esp) # verified field ID: weight_to_power
 118586d:	00 
 118586e:	ff d0                	call   *%eax
 1185870:	89 c6                	mov    %eax,%esi
 1185872:	8b 4d 08             	mov    0x8(%ebp),%ecx
 1185875:	8b 01                	mov    (%ecx),%eax
 1185877:	8b 40 0c             	mov    0xc(%eax),%eax
 118587a:	89 0c 24             	mov    %ecx,(%esp)
 118587d:	c7 44 24 04 bd 90 01 	movl   $0x190bd,0x4(%esp) # verified field ID: run_acc
 1185884:	00 
 1185885:	ff d0                	call   *%eax
 1185887:	89 44 24 68          	mov    %eax,0x68(%esp)
 118588b:	c7 84 24 ec 05 00 00 	movl   $0x0,0x5ec(%esp)
 1185892:	00 00 00 00 
 1185896:	c7 84 24 e4 05 00 00 	movl   $0x3fb99999,0x5e4(%esp)
 118589d:	99 99 b9 3f 
 11858a1:	c7 84 24 e0 05 00 00 	movl   $0x9999999a,0x5e0(%esp)
 11858a8:	9a 99 99 99 
 11858ac:	89 7c 24 04          	mov    %edi,0x4(%esp)
 11858b0:	8d bc 24 e0 05 00 00 	lea    0x5e0(%esp),%edi
 11858b7:	89 3c 24             	mov    %edi,(%esp)
 11858ba:	e8 61 60 6a 00       	call   182b920 <YYRValue::operator+=(YYRValue const&)@plt>
 11858bf:	8d 84 24 a0 08 00 00 	lea    0x8a0(%esp),%eax
 11858c6:	89 44 24 08          	mov    %eax,0x8(%esp)
 11858ca:	89 7c 24 04          	mov    %edi,0x4(%esp)
 11858ce:	8d bc 24 f0 05 00 00 	lea    0x5f0(%esp),%edi
 11858d5:	89 3c 24             	mov    %edi,(%esp)
 11858d8:	e8 43 62 6a 00       	call   182bb20 <operator*(YYRValue const&, YYRValue const&)@plt>
 11858dd:	83 ec 04             	sub    $0x4,%esp
 11858e0:	8b 44 24 38          	mov    0x38(%esp),%eax
 11858e4:	89 44 24 08          	mov    %eax,0x8(%esp)
 11858e8:	89 7c 24 04          	mov    %edi,0x4(%esp)
 11858ec:	8d bc 24 00 06 00 00 	lea    0x600(%esp),%edi
 11858f3:	89 3c 24             	mov    %edi,(%esp)
 11858f6:	e8 25 62 6a 00       	call   182bb20 <operator*(YYRValue const&, YYRValue const&)@plt>
 11858fb:	83 ec 04             	sub    $0x4,%esp
 11858fe:	89 74 24 08          	mov    %esi,0x8(%esp)
 1185902:	89 7c 24 04          	mov    %edi,0x4(%esp)
 1185906:	8d b4 24 20 0a 00 00 	lea    0xa20(%esp),%esi
 118590d:	89 34 24             	mov    %esi,(%esp)
 1185910:	e8 0b 62 6a 00       	call   182bb20 <operator*(YYRValue const&, YYRValue const&)@plt>
 1185915:	83 ec 04             	sub    $0x4,%esp
 1185918:	8b 45 08             	mov    0x8(%ebp),%eax
 118591b:	89 04 24             	mov    %eax,(%esp)
 118591e:	e8 6d 5e 6a 00       	call   182b790 <PushContextStack(YYObjectBase*)@plt>
 1185923:	89 74 24 04          	mov    %esi,0x4(%esp)
 1185927:	8b 44 24 68          	mov    0x68(%esp),%eax
 118592b:	89 04 24             	mov    %eax,(%esp)
 118592e:	e8 2d 5e 6a 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 1185933:	8b 84 24 2c 0a 00 00 	mov    0xa2c(%esp),%eax
 118593a:	be 46 00 00 00       	mov    $0x46,%esi
 118593f:	0f a3 c6             	bt     %eax,%esi
 1185942:	73 0f                	jae    1185953 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb303>
 1185944:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 118594b:	89 04 24             	mov    %eax,(%esp)
 118594e:	e8 6d 5d 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 1185953:	8b 84 24 0c 06 00 00 	mov    0x60c(%esp),%eax
 118595a:	0f a3 c6             	bt     %eax,%esi
 118595d:	73 0f                	jae    118596e <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb31e>
 118595f:	8d 84 24 00 06 00 00 	lea    0x600(%esp),%eax
 1185966:	89 04 24             	mov    %eax,(%esp)
 1185969:	e8 52 5d 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118596e:	8b 84 24 fc 05 00 00 	mov    0x5fc(%esp),%eax
 1185975:	be 46 00 00 00       	mov    $0x46,%esi
 118597a:	0f a3 c6             	bt     %eax,%esi
 118597d:	73 0f                	jae    118598e <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb33e>
 118597f:	8d 84 24 f0 05 00 00 	lea    0x5f0(%esp),%eax
 1185986:	89 04 24             	mov    %eax,(%esp)
 1185989:	e8 32 5d 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118598e:	8b 84 24 ec 05 00 00 	mov    0x5ec(%esp),%eax
 1185995:	0f a3 c6             	bt     %eax,%esi
 1185998:	73 0f                	jae    11859a9 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xb359>
 118599a:	8d 84 24 e0 05 00 00 	lea    0x5e0(%esp),%eax
 11859a1:	89 04 24             	mov    %eax,(%esp)
 11859a4:	e8 17 5d 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11859a9:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 11859b0:	e8 eb 5d 6a 00       	call   182b7a0 <PopContextStack(int)@plt>
 1186f96:	c7 44 24 04 d5 95 01 	movl   $0x195d5,0x4(%esp) # verified field ID: xspeed
 1186f9d:	00 
 1186f9e:	ff d0                	call   *%eax
 1186fa0:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 1186fa7:	00 00 00 00 
 1186fab:	c7 84 24 24 0a 00 00 	movl   $0x3ff00000,0xa24(%esp)
 1186fb2:	00 00 f0 3f 
 1186fb6:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 1186fbd:	00 00 00 00 
 1186fc1:	8b 4c 24 24          	mov    0x24(%esp),%ecx
 1186fc5:	f2 0f 10 01          	movsd  (%ecx),%xmm0
 1186fc9:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 1186fcf:	8d 8c 24 20 0a 00 00 	lea    0xa20(%esp),%ecx
 1186fd6:	89 4c 24 04          	mov    %ecx,0x4(%esp)
 1186fda:	89 04 24             	mov    %eax,(%esp)
 1186fdd:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
 1186fe4:	00 
 1186fe5:	e8 d6 47 6a 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 1186fea:	85 c0                	test   %eax,%eax
 1186fec:	0f 8e 73 38 00 00    	jle    118a865 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x10215>
 1186ff2:	8b 4d 08             	mov    0x8(%ebp),%ecx
 1186ff5:	8b 01                	mov    (%ecx),%eax
 1186ff7:	8b 40 0c             	mov    0xc(%eax),%eax
 1186ffa:	89 0c 24             	mov    %ecx,(%esp)
 1186ffd:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 1187004:	00 
 1187005:	ff d0                	call   *%eax
 1187007:	89 44 24 7c          	mov    %eax,0x7c(%esp)
 118700b:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 1187012:	00 00 00 00 
 1187016:	c7 84 24 24 0a 00 00 	movl   $0x3ff00000,0xa24(%esp)
 118701d:	00 00 f0 3f 
 1187021:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 1187028:	00 00 00 00 
 118702c:	8b 44 24 24          	mov    0x24(%esp),%eax
 1187030:	f2 0f 10 00          	movsd  (%eax),%xmm0
 1187034:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 118703a:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 1187041:	89 44 24 04          	mov    %eax,0x4(%esp)
 1187045:	8b 44 24 7c          	mov    0x7c(%esp),%eax
 1187049:	89 04 24             	mov    %eax,(%esp)
 118704c:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
 1187053:	00 
 1187054:	e8 67 47 6a 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 1187059:	83 f8 fe             	cmp    $0xfffffffe,%eax
 118705c:	0f 84 03 38 00 00    	je     118a865 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x10215>
 1187062:	85 c0                	test   %eax,%eax
 1187064:	0f 89 fb 37 00 00    	jns    118a865 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x10215>
 118706a:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118706d:	8b 01                	mov    (%ecx),%eax
 118706f:	8b 40 0c             	mov    0xc(%eax),%eax
 1187072:	89 0c 24             	mov    %ecx,(%esp)
 1187075:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 118707c:	00 
 118707d:	ff d0                	call   *%eax
 118707f:	89 44 24 7c          	mov    %eax,0x7c(%esp)
 1187083:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 118708a:	00 00 00 00 
 118708e:	c7 84 24 24 0a 00 00 	movl   $0x0,0xa24(%esp)
 1187095:	00 00 00 00 
 1187099:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 11870a0:	00 00 00 00 
 11870a4:	8b 44 24 24          	mov    0x24(%esp),%eax
 11870a8:	f2 0f 10 00          	movsd  (%eax),%xmm0
 11870ac:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 11870b2:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 11870b9:	89 44 24 04          	mov    %eax,0x4(%esp)
 11870bd:	8b 44 24 7c          	mov    0x7c(%esp),%eax
 11870c1:	89 04 24             	mov    %eax,(%esp)
 11870c4:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
 11870cb:	00 
 11870cc:	e8 ef 46 6a 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 11870d1:	85 c0                	test   %eax,%eax
 11870d3:	0f 8e 8c 37 00 00    	jle    118a865 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x10215>
 11870d9:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11870dc:	8b 01                	mov    (%ecx),%eax
 11870de:	8b 40 0c             	mov    0xc(%eax),%eax
 11870e1:	89 0c 24             	mov    %ecx,(%esp)
 11870e4:	c7 44 24 04 19 8d 01 	movl   $0x18d19,0x4(%esp)
 11870eb:	00 
 11870ec:	ff d0                	call   *%eax
 11870ee:	89 44 24 68          	mov    %eax,0x68(%esp)
 11870f2:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 11870f9:	00 00 00 00 
 11870fd:	c7 84 24 24 0a 00 00 	movl   $0x3ff00000,0xa24(%esp)
 1187104:	00 00 f0 3f 
 1187108:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 118710f:	00 00 00 00 
 1187113:	8b 44 24 24          	mov    0x24(%esp),%eax
 1187117:	f2 0f 10 00          	movsd  (%eax),%xmm0
 118711b:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 1187121:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 1187128:	89 44 24 04          	mov    %eax,0x4(%esp)
 118712c:	8b 44 24 68          	mov    0x68(%esp),%eax
 1187130:	89 04 24             	mov    %eax,(%esp)
 1187133:	c7 44 24 10 00 00 00 	movl   $0x0,0x10(%esp)
 118713a:	00 
 118713b:	e8 80 46 6a 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 1187140:	85 c0                	test   %eax,%eax
 1187142:	0f 85 1d 37 00 00    	jne    118a865 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x10215>
 1187148:	8b 44 24 5c          	mov    0x5c(%esp),%eax
 118714c:	8b 40 04             	mov    0x4(%eax),%eax
 118714f:	8d 8c 24 90 09 00 00 	lea    0x990(%esp),%ecx
 1187156:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
 118715a:	89 44 24 04          	mov    %eax,0x4(%esp)
 118715e:	8b 45 08             	mov    0x8(%ebp),%eax
 1187161:	89 04 24             	mov    %eax,(%esp)
 1187164:	c7 44 24 08 00 00 00 	movl   $0x80000000,0x8(%esp)
 118716b:	80 
 118716c:	e8 1f 49 6a 00       	call   182ba90 <Variable_GetBuiltIn_Direct(YYObjectBase*, int, int, RValue*)@plt>
 1187171:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 1187178:	00 00 00 00 
 118717c:	c7 84 24 24 0a 00 00 	movl   $0x0,0xa24(%esp)
 1187183:	00 00 00 00 
 1187187:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 118718e:	00 00 00 00 
 1187192:	8b 44 24 24          	mov    0x24(%esp),%eax
 1187196:	f2 0f 10 00          	movsd  (%eax),%xmm0
 118719a:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 11871a0:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 11871a7:	89 44 24 04          	mov    %eax,0x4(%esp)
 11871ab:	8d 84 24 90 09 00 00 	lea    0x990(%esp),%eax
 11871b2:	89 04 24             	mov    %eax,(%esp)
 11871b5:	c7 44 24 10 00 00 00 	movl   $0x0,0x10(%esp)
 11871bc:	00 
 11871bd:	e8 fe 45 6a 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 11871c2:	85 c0                	test   %eax,%eax
 11871c4:	0f 84 9b 36 00 00    	je     118a865 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x10215>
 11871ca:	c7 84 24 18 0a 00 00 	movl   $0x2c0,0xa18(%esp)
 11871d1:	c0 02 00 00 
 11871d5:	8b 84 24 cc 06 00 00 	mov    0x6cc(%esp),%eax
 11871dc:	be 46 00 00 00       	mov    $0x46,%esi
 11871e1:	0f a3 c6             	bt     %eax,%esi
 11871e4:	73 0f                	jae    11871f5 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xcba5>
 11871e6:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 11871ed:	89 04 24             	mov    %eax,(%esp)
 11871f0:	e8 cb 44 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 1187216:	8b 84 24 bc 06 00 00 	mov    0x6bc(%esp),%eax
 118721d:	0f a3 c6             	bt     %eax,%esi
 1187220:	73 0f                	jae    1187231 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xcbe1>
 1187222:	8d 84 24 b0 06 00 00 	lea    0x6b0(%esp),%eax
 1187229:	89 04 24             	mov    %eax,(%esp)
 118722c:	e8 8f 44 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 1187231:	c7 84 24 b0 06 00 00 	movl   $0x0,0x6b0(%esp)
 1187238:	00 00 00 00 
 118723c:	c7 84 24 b8 06 00 00 	movl   $0x0,0x6b8(%esp)
 1187243:	00 00 00 00 
 1187247:	c7 84 24 bc 06 00 00 	movl   $0x5,0x6bc(%esp)
 118724e:	05 00 00 00 
 1187252:	8b 4d 08             	mov    0x8(%ebp),%ecx
 1187255:	8b 01                	mov    (%ecx),%eax
 1187257:	8b 40 0c             	mov    0xc(%eax),%eax
 118725a:	89 0c 24             	mov    %ecx,(%esp)
 118725d:	c7 44 24 04 d5 95 01 	movl   $0x195d5,0x4(%esp) # verified field ID: xspeed
 1187264:	00 
 1187265:	ff d0                	call   *%eax
 1187267:	89 c6                	mov    %eax,%esi
 1187269:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118726c:	8b 01                	mov    (%ecx),%eax
 118726e:	8b 40 0c             	mov    0xc(%eax),%eax
 1187271:	89 0c 24             	mov    %ecx,(%esp)
 1187274:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 118727b:	00 
 118727c:	ff d0                	call   *%eax
 118727e:	89 44 24 7c          	mov    %eax,0x7c(%esp)
 1187282:	8b 4d 08             	mov    0x8(%ebp),%ecx
 1187285:	8b 01                	mov    (%ecx),%eax
 1187287:	8b 40 08             	mov    0x8(%eax),%eax
 118728a:	89 0c 24             	mov    %ecx,(%esp)
 118728d:	c7 44 24 04 be 90 01 	movl   $0x190be,0x4(%esp)
 1187294:	00 
 1187295:	ff d0                	call   *%eax
 1187297:	89 44 24 38          	mov    %eax,0x38(%esp)
 118729b:	8b 44 24 7c          	mov    0x7c(%esp),%eax
 118729f:	89 44 24 04          	mov    %eax,0x4(%esp)
 11872a3:	8d bc 24 00 06 00 00 	lea    0x600(%esp),%edi
 11872aa:	89 3c 24             	mov    %edi,(%esp)
 11872ad:	c7 44 24 0c cc cc ec 	movl   $0x3feccccc,0xc(%esp)
 11872b4:	3f 
 11872b5:	c7 44 24 08 cd cc cc 	movl   $0xcccccccd,0x8(%esp)
 11872bc:	cc 
 11872bd:	e8 2e 47 6a 00       	call   182b9f0 <operator*(YYRValue const&, double)@plt>
 11872c2:	83 ec 04             	sub    $0x4,%esp
 11872c5:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 11872cc:	00 00 00 00 
 11872d0:	c7 84 24 24 0a 00 00 	movl   $0x3ff00000,0xa24(%esp)
 11872d7:	00 00 f0 3f 
 11872db:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 11872e2:	00 00 00 00 
 11872e6:	89 7c 24 04          	mov    %edi,0x4(%esp)
 11872ea:	8d bc 24 20 0a 00 00 	lea    0xa20(%esp),%edi
 11872f1:	89 3c 24             	mov    %edi,(%esp)
 11872f4:	e8 37 47 6a 00       	call   182ba30 <YYRValue::operator-=(YYRValue const&)@plt>
 11872f9:	89 7c 24 04          	mov    %edi,0x4(%esp)
 11872fd:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 1187304:	89 04 24             	mov    %eax,(%esp)
 1187307:	e8 54 44 6a 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 118730c:	8b 84 24 2c 0a 00 00 	mov    0xa2c(%esp),%eax
 1187313:	bf 46 00 00 00       	mov    $0x46,%edi
 1187318:	0f a3 c7             	bt     %eax,%edi
 118731b:	73 0f                	jae    118732c <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xccdc>
 118731d:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 1187324:	89 04 24             	mov    %eax,(%esp)
 1187327:	e8 94 43 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118732c:	8b 84 24 0c 06 00 00 	mov    0x60c(%esp),%eax
 1187333:	0f a3 c7             	bt     %eax,%edi
 1187336:	73 0f                	jae    1187347 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0xccf7>
 1187338:	8d 84 24 00 06 00 00 	lea    0x600(%esp),%eax
 118733f:	89 04 24             	mov    %eax,(%esp)
 1187342:	e8 79 43 6a 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 1187347:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 118734e:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 1187355:	8b 83 04 d2 ff ff    	mov    -0x2dfc(%ebx),%eax
 118735b:	89 44 24 04          	mov    %eax,0x4(%esp)
 118735f:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 1187366:	89 04 24             	mov    %eax,(%esp)
 1187369:	e8 02 44 6a 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 118736e:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 1187375:	89 84 24 fc 0a 00 00 	mov    %eax,0xafc(%esp)
 118737c:	8b 83 44 d2 ff ff    	mov    -0x2dbc(%ebx),%eax
 1187382:	89 44 24 04          	mov    %eax,0x4(%esp)
 1187386:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 118738d:	89 04 24             	mov    %eax,(%esp)
 1187390:	e8 db 43 6a 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 1187395:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 118739c:	89 84 24 00 0b 00 00 	mov    %eax,0xb00(%esp)
 11873a3:	8b 44 24 44          	mov    0x44(%esp),%eax
 11873a7:	89 44 24 04          	mov    %eax,0x4(%esp)
 11873ab:	8d 84 24 68 0a 00 00 	lea    0xa68(%esp),%eax
 11873b2:	89 04 24             	mov    %eax,(%esp)
 11873b5:	e8 b6 43 6a 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 11873ba:	8d 84 24 68 0a 00 00 	lea    0xa68(%esp),%eax
 11873c1:	89 84 24 04 0b 00 00 	mov    %eax,0xb04(%esp)
 11873c8:	f7 46 0c ff ff ff 00 	testl  $0xffffff,0xc(%esi)
 11873cf:	0f 84 bf 32 00 00    	je     118a694 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x10044>
 11873d5:	89 34 24             	mov    %esi,(%esp)
 11873d8:	e8 03 44 6a 00       	call   182b7e0 <REAL_RValue_Ex(RValue const*)@plt>
 11873dd:	dd 9c 24 90 03 00 00 	fstpl  0x390(%esp)
 11873e4:	f2 0f 10 84 24 90 03 	movsd  0x390(%esp),%xmm0
 11873eb:	00 00 
 11873ed:	e9 a6 32 00 00       	jmp    118a698 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x10048>
 11873f2:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11873f5:	8b 01                	mov    (%ecx),%eax
 11873f7:	8b 40 0c             	mov    0xc(%eax),%eax
 11873fa:	89 0c 24             	mov    %ecx,(%esp)
 11873fd:	c7 44 24 04 0c 8a 01 	movl   $0x18a0c,0x4(%esp)
 118b7d9:	c7 84 24 2c 0a 00 00 	movl   $0xd,0xa2c(%esp)
 118b7e0:	0d 00 00 00 
 118b7e4:	c7 84 24 24 0a 00 00 	movl   $0x3ff00000,0xa24(%esp)
 118b7eb:	00 00 f0 3f 
 118b7ef:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 118b7f6:	00 00 00 00 
 118b7fa:	8b 44 24 24          	mov    0x24(%esp),%eax
 118b7fe:	f2 0f 10 00          	movsd  (%eax),%xmm0
 118b802:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 118b808:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 118b80f:	89 44 24 04          	mov    %eax,0x4(%esp)
 118b813:	8b 84 24 8c 00 00 00 	mov    0x8c(%esp),%eax
 118b81a:	89 04 24             	mov    %eax,(%esp)
 118b81d:	c7 44 24 10 00 00 00 	movl   $0x0,0x10(%esp)
 118b824:	00 
 118b825:	e8 96 ff 69 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 118b82a:	85 c0                	test   %eax,%eax
 118b82c:	0f 84 3b 04 00 00    	je     118bc6d <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1161d>
 118b832:	c7 84 24 18 0a 00 00 	movl   $0x331,0xa18(%esp)
 118b839:	31 03 00 00 
 118b83d:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118b840:	8b 01                	mov    (%ecx),%eax
 118b842:	8b 40 0c             	mov    0xc(%eax),%eax
 118b845:	89 0c 24             	mov    %ecx,(%esp)
 118b848:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 118b84f:	00 
 118b850:	ff d0                	call   *%eax
 118b852:	89 44 24 7c          	mov    %eax,0x7c(%esp)
 118b856:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 118b85d:	00 00 00 00 
 118b861:	c7 84 24 24 0a 00 00 	movl   $0x3ff00000,0xa24(%esp)
 118b868:	00 00 f0 3f 
 118b86c:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 118b873:	00 00 00 00 
 118b877:	8b 44 24 24          	mov    0x24(%esp),%eax
 118b87b:	f2 0f 10 00          	movsd  (%eax),%xmm0
 118b87f:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 118b885:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 118b88c:	89 44 24 04          	mov    %eax,0x4(%esp)
 118b890:	8b 44 24 7c          	mov    0x7c(%esp),%eax
 118b894:	89 04 24             	mov    %eax,(%esp)
 118b897:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
 118b89e:	00 
 118b89f:	e8 1c ff 69 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 118b8a4:	83 f8 fe             	cmp    $0xfffffffe,%eax
 118b8a7:	0f 84 7b 01 00 00    	je     118ba28 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x113d8>
 118b8ad:	85 c0                	test   %eax,%eax
 118b8af:	0f 89 73 01 00 00    	jns    118ba28 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x113d8>
 118b8b5:	c7 84 24 18 0a 00 00 	movl   $0x333,0xa18(%esp)
 118b8bc:	33 03 00 00 
 118b8c0:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118b8c3:	8b 01                	mov    (%ecx),%eax
 118b8c5:	8b 40 0c             	mov    0xc(%eax),%eax
 118b8c8:	89 0c 24             	mov    %ecx,(%esp)
 118b8cb:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 118b8d2:	00 
 118b8d3:	ff d0                	call   *%eax
 118b8d5:	89 04 24             	mov    %eax,(%esp)
 118b8d8:	c7 44 24 08 e1 7a 94 	movl   $0x3f947ae1,0x8(%esp)
 118b8df:	3f 
 118b8e0:	c7 44 24 04 7b 14 ae 	movl   $0x47ae147b,0x4(%esp)
 118b8e7:	47 
 118b8e8:	e8 d3 03 6a 00       	call   182bcc0 <YYRValue::operator+=(double)@plt>
 118b8ed:	c7 84 24 18 0a 00 00 	movl   $0x334,0xa18(%esp)
 118b8f4:	34 03 00 00 
 118b8f8:	8b 84 24 cc 06 00 00 	mov    0x6cc(%esp),%eax
 118b8ff:	b9 46 00 00 00       	mov    $0x46,%ecx
 118b904:	0f a3 c1             	bt     %eax,%ecx
 118b907:	73 0f                	jae    118b918 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x112c8>
 118b909:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 118b910:	89 04 24             	mov    %eax,(%esp)
 118b913:	e8 a8 fd 69 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118b918:	c7 84 24 c0 06 00 00 	movl   $0x0,0x6c0(%esp)
 118b91f:	00 00 00 00 
 118b923:	c7 84 24 c8 06 00 00 	movl   $0x0,0x6c8(%esp)
 118b92a:	00 00 00 00 
 118b92e:	c7 84 24 cc 06 00 00 	movl   $0x5,0x6cc(%esp)
 118b935:	05 00 00 00 
 118b939:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118b93c:	8b 01                	mov    (%ecx),%eax
 118b93e:	8b 40 0c             	mov    0xc(%eax),%eax
 118b941:	89 0c 24             	mov    %ecx,(%esp)
 118b944:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 118b94b:	00 
 118b94c:	ff d0                	call   *%eax
 118b94e:	89 44 24 7c          	mov    %eax,0x7c(%esp)
 118b952:	8b 44 24 7c          	mov    0x7c(%esp),%eax
 118b956:	89 44 24 04          	mov    %eax,0x4(%esp)
 118b95a:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 118b961:	89 04 24             	mov    %eax,(%esp)
 118b964:	e8 f7 fd 69 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 118b969:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 118b970:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 118b977:	8b 44 24 44          	mov    0x44(%esp),%eax
 118b97b:	89 44 24 04          	mov    %eax,0x4(%esp)
 118b97f:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 118b986:	89 04 24             	mov    %eax,(%esp)
 118b989:	e8 e2 fd 69 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 118b98e:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 118b995:	89 84 24 fc 0a 00 00 	mov    %eax,0xafc(%esp)
 118b99c:	8b 84 24 a0 00 00 00 	mov    0xa0(%esp),%eax
 118b9a3:	89 44 24 04          	mov    %eax,0x4(%esp)
 118b9a7:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 118b9ae:	89 04 24             	mov    %eax,(%esp)
 118b9b1:	e8 ba fd 69 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 118b9b6:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 118b9bd:	89 84 24 00 0b 00 00 	mov    %eax,0xb00(%esp)
 118b9c4:	8b 44 24 60          	mov    0x60(%esp),%eax
 118b9c8:	8b 40 04             	mov    0x4(%eax),%eax
 118b9cb:	8d 8c 24 f8 0a 00 00 	lea    0xaf8(%esp),%ecx
 118b9d2:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 118b9d6:	89 44 24 10          	mov    %eax,0x10(%esp)
 118b9da:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 118b9e1:	89 44 24 08          	mov    %eax,0x8(%esp)
 118b9e5:	8b 45 0c             	mov    0xc(%ebp),%eax
 118b9e8:	89 44 24 04          	mov    %eax,0x4(%esp)
 118b9ec:	8b 45 08             	mov    0x8(%ebp),%eax
 118b9ef:	89 04 24             	mov    %eax,(%esp)
 118b9f2:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
 118b9f9:	00 
 118b9fa:	e8 01 fe 69 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 118b9ff:	89 c6                	mov    %eax,%esi
 118ba01:	8b 45 08             	mov    0x8(%ebp),%eax
 118ba04:	89 04 24             	mov    %eax,(%esp)
 118ba07:	e8 84 fd 69 00       	call   182b790 <PushContextStack(YYObjectBase*)@plt>
 118ba0c:	89 74 24 04          	mov    %esi,0x4(%esp)
 118ba10:	8b 44 24 7c          	mov    0x7c(%esp),%eax
 118ba14:	89 04 24             	mov    %eax,(%esp)
 118ba17:	e8 44 fd 69 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 118ba1c:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 118ba23:	e8 78 fd 69 00       	call   182b7a0 <PopContextStack(int)@plt>
 118ba28:	c7 84 24 18 0a 00 00 	movl   $0x336,0xa18(%esp)
 118ba2f:	36 03 00 00 
 118ba33:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118ba36:	8b 01                	mov    (%ecx),%eax
 118ba38:	8b 40 0c             	mov    0xc(%eax),%eax
 118ba3b:	89 0c 24             	mov    %ecx,(%esp)
 118ba3e:	c7 44 24 04 1a 8a 01 	movl   $0x18a1a,0x4(%esp)
 118ba45:	00 
 118ba46:	ff d0                	call   *%eax
 118ba48:	c7 84 24 2c 0a 00 00 	movl   $0xd,0xa2c(%esp)
 118ba4f:	0d 00 00 00 
 118ba53:	c7 84 24 24 0a 00 00 	movl   $0x0,0xa24(%esp)
 118ba5a:	00 00 00 00 
 118ba5e:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 118ba65:	00 00 00 00 
 118ba69:	8d 8c 24 20 0a 00 00 	lea    0xa20(%esp),%ecx
 118ba70:	89 4c 24 04          	mov    %ecx,0x4(%esp)
 118ba74:	89 04 24             	mov    %eax,(%esp)
 118ba77:	e8 e4 fc 69 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 118ba7c:	8b 84 24 2c 0a 00 00 	mov    0xa2c(%esp),%eax
 118ba83:	b9 46 00 00 00       	mov    $0x46,%ecx
 118ba88:	0f a3 c1             	bt     %eax,%ecx
 118ba8b:	73 0f                	jae    118ba9c <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1144c>
 118ba8d:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 118ba94:	89 04 24             	mov    %eax,(%esp)
 118ba97:	e8 24 fc 69 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118ba9c:	c7 84 24 18 0a 00 00 	movl   $0x337,0xa18(%esp)
 118baa3:	37 03 00 00 
 118baa7:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118baaa:	8b 01                	mov    (%ecx),%eax
 118baac:	8b 40 0c             	mov    0xc(%eax),%eax
 118baaf:	89 0c 24             	mov    %ecx,(%esp)
 118bab2:	c7 44 24 04 1c 8a 01 	movl   $0x18a1c,0x4(%esp)
 118bab9:	00 
 118baba:	ff d0                	call   *%eax
 118babc:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 118c9a6:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 118c9ac:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 118c9b3:	89 44 24 04          	mov    %eax,0x4(%esp)
 118c9b7:	8b 44 24 68          	mov    0x68(%esp),%eax
 118c9bb:	89 04 24             	mov    %eax,(%esp)
 118c9be:	c7 44 24 10 00 00 00 	movl   $0x0,0x10(%esp)
 118c9c5:	00 
 118c9c6:	e8 f5 ed 69 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 118c9cb:	85 c0                	test   %eax,%eax
 118c9cd:	0f 84 4f 03 00 00    	je     118cd22 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x126d2>
 118c9d3:	c7 84 24 18 0a 00 00 	movl   $0x2f7,0xa18(%esp)
 118c9da:	f7 02 00 00 
 118c9de:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118c9e1:	8b 01                	mov    (%ecx),%eax
 118c9e3:	8b 40 0c             	mov    0xc(%eax),%eax
 118c9e6:	89 0c 24             	mov    %ecx,(%esp)
 118c9e9:	c7 44 24 04 ba 90 01 	movl   $0x190ba,0x4(%esp) # verified field ID: RPM
 118c9f0:	00 
 118c9f1:	ff d0                	call   *%eax
 118c9f3:	89 44 24 48          	mov    %eax,0x48(%esp)
 118c9f7:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118c9fa:	8b 01                	mov    (%ecx),%eax
 118c9fc:	8b 40 0c             	mov    0xc(%eax),%eax
 118c9ff:	89 0c 24             	mov    %ecx,(%esp)
 118ca02:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 118ca09:	00 
 118ca0a:	ff d0                	call   *%eax
 118ca0c:	89 c6                	mov    %eax,%esi
 118ca0e:	8b 44 24 48          	mov    0x48(%esp),%eax
 118ca12:	89 44 24 04          	mov    %eax,0x4(%esp)
 118ca16:	8d bc 24 00 06 00 00 	lea    0x600(%esp),%edi
 118ca1d:	89 3c 24             	mov    %edi,(%esp)
 118ca20:	c7 44 24 0c 00 92 b3 	movl   $0x40b39200,0xc(%esp)
 118ca27:	40 
 118ca28:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 118ca2f:	00 
 118ca30:	e8 9b ef 69 00       	call   182b9d0 <operator/(YYRValue const&, double)@plt>
 118ca35:	83 ec 04             	sub    $0x4,%esp
 118ca38:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 118ca3f:	00 00 00 00 
 118ca43:	c7 84 24 24 0a 00 00 	movl   $0x3f747ae1,0xa24(%esp)
 118ca4a:	e1 7a 74 3f 
 118ca4e:	c7 84 24 20 0a 00 00 	movl   $0x47ae147b,0xa20(%esp)
 118ca55:	7b 14 ae 47 
 118ca59:	89 7c 24 04          	mov    %edi,0x4(%esp)
 118ca5d:	8d bc 24 20 0a 00 00 	lea    0xa20(%esp),%edi
 118ca64:	89 3c 24             	mov    %edi,(%esp)
 118ca67:	e8 f4 ef 69 00       	call   182ba60 <YYRValue::operator*=(YYRValue const&)@plt>
 118ca6c:	89 7c 24 04          	mov    %edi,0x4(%esp)
 118ca70:	89 34 24             	mov    %esi,(%esp)
 118ca73:	e8 b8 ef 69 00       	call   182ba30 <YYRValue::operator-=(YYRValue const&)@plt>
 118ca78:	8b 84 24 2c 0a 00 00 	mov    0xa2c(%esp),%eax
 118ca7f:	be 46 00 00 00       	mov    $0x46,%esi
 118ca84:	0f a3 c6             	bt     %eax,%esi
 118ca87:	73 0f                	jae    118ca98 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x12448>
 118ca89:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 118ca90:	89 04 24             	mov    %eax,(%esp)
 118ca93:	e8 28 ec 69 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118ca98:	8b 84 24 0c 06 00 00 	mov    0x60c(%esp),%eax
 118ca9f:	0f a3 c6             	bt     %eax,%esi
 118caa2:	73 0f                	jae    118cab3 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x12463>
 118caa4:	8d 84 24 00 06 00 00 	lea    0x600(%esp),%eax
 118caab:	89 04 24             	mov    %eax,(%esp)
 118caae:	e8 0d ec 69 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118cab3:	c7 84 24 18 0a 00 00 	movl   $0x2f8,0xa18(%esp)
 118caba:	f8 02 00 00 
 118cabe:	8b 84 24 cc 06 00 00 	mov    0x6cc(%esp),%eax
 118cac5:	b9 46 00 00 00       	mov    $0x46,%ecx
 118caca:	0f a3 c1             	bt     %eax,%ecx
 118cacd:	73 0f                	jae    118cade <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1248e>
 118cacf:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 118cad6:	89 04 24             	mov    %eax,(%esp)
 118cad9:	e8 e2 eb 69 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118cade:	c7 84 24 c0 06 00 00 	movl   $0x0,0x6c0(%esp)
 118cae5:	00 00 00 00 
 118cae9:	c7 84 24 c8 06 00 00 	movl   $0x0,0x6c8(%esp)
 118caf0:	00 00 00 00 
 118caf4:	c7 84 24 cc 06 00 00 	movl   $0x5,0x6cc(%esp)
 118cafb:	05 00 00 00 
 118caff:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118cb02:	8b 01                	mov    (%ecx),%eax
 118cb04:	8b 40 0c             	mov    0xc(%eax),%eax
 118cb07:	89 0c 24             	mov    %ecx,(%esp)
 118cb0a:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 118cb11:	00 
 118cb12:	ff d0                	call   *%eax
 118cb14:	89 c6                	mov    %eax,%esi
 118cb16:	89 44 24 04          	mov    %eax,0x4(%esp)
 118cb1a:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 118cb21:	89 04 24             	mov    %eax,(%esp)
 118cb24:	e8 37 ec 69 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 118cb29:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 118cb30:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 118cb37:	8b 44 24 44          	mov    0x44(%esp),%eax
 118cb3b:	89 44 24 04          	mov    %eax,0x4(%esp)
 118cb3f:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 118cb46:	89 04 24             	mov    %eax,(%esp)
 118cb49:	e8 22 ec 69 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 118cb4e:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 118cb55:	89 84 24 fc 0a 00 00 	mov    %eax,0xafc(%esp)
 118cb5c:	8b 84 24 a0 00 00 00 	mov    0xa0(%esp),%eax
 118cb63:	89 44 24 04          	mov    %eax,0x4(%esp)
 118cb67:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 118cb6e:	89 04 24             	mov    %eax,(%esp)
 118cb71:	e8 fa eb 69 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 118cb76:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 118cb7d:	89 84 24 00 0b 00 00 	mov    %eax,0xb00(%esp)
 118cb84:	8b 44 24 60          	mov    0x60(%esp),%eax
 118cb88:	8b 40 04             	mov    0x4(%eax),%eax
 118cb8b:	8d 8c 24 f8 0a 00 00 	lea    0xaf8(%esp),%ecx
 118cb92:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 118cb96:	89 44 24 10          	mov    %eax,0x10(%esp)
 118cb9a:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 118cba1:	89 44 24 08          	mov    %eax,0x8(%esp)
 118cba5:	8b 45 0c             	mov    0xc(%ebp),%eax
 118cba8:	89 44 24 04          	mov    %eax,0x4(%esp)
 118cbac:	8b 45 08             	mov    0x8(%ebp),%eax
 118cbaf:	89 04 24             	mov    %eax,(%esp)
 118cbb2:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
 118cbb9:	00 
 118cbba:	e8 41 ec 69 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 118cbbf:	89 c7                	mov    %eax,%edi
 118cbc1:	8b 45 08             	mov    0x8(%ebp),%eax
 118cbc4:	89 04 24             	mov    %eax,(%esp)
 118cbc7:	e8 c4 eb 69 00       	call   182b790 <PushContextStack(YYObjectBase*)@plt>
 118cbcc:	89 7c 24 04          	mov    %edi,0x4(%esp)
 118cbd0:	89 34 24             	mov    %esi,(%esp)
 118cbd3:	e8 88 eb 69 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 118cbd8:	e9 a2 02 00 00       	jmp    118ce7f <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x1282f>
 118cbdd:	8b 44 24 5c          	mov    0x5c(%esp),%eax
 118cbe1:	8b 40 04             	mov    0x4(%eax),%eax
 118cbe4:	8d bc 24 90 09 00 00 	lea    0x990(%esp),%edi
 118cbeb:	89 7c 24 0c          	mov    %edi,0xc(%esp)
 118cbef:	89 44 24 04          	mov    %eax,0x4(%esp)
 118cbf3:	8b 45 08             	mov    0x8(%ebp),%eax
 118cbf6:	89 04 24             	mov    %eax,(%esp)
 118cbf9:	c7 44 24 08 00 00 00 	movl   $0x80000000,0x8(%esp)
 118cc00:	80 
 118cc01:	e8 8a ee 69 00       	call   182ba90 <Variable_GetBuiltIn_Direct(YYObjectBase*, int, int, RValue*)@plt>
 118cc06:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 118cc0d:	00 00 00 00 
 118cc11:	c7 84 24 24 0a 00 00 	movl   $0x40000000,0xa24(%esp)
 118cc18:	00 00 00 40 
 118cc1c:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 118cc23:	00 00 00 00 
 118cc27:	8b 44 24 24          	mov    0x24(%esp),%eax
 118cc2b:	f2 0f 10 00          	movsd  (%eax),%xmm0
 118cc2f:	f2 0f 11 44 24 38    	movsd  %xmm0,0x38(%esp)
 118cc35:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 118cc3b:	8d b4 24 20 0a 00 00 	lea    0xa20(%esp),%esi
 118cc42:	89 74 24 04          	mov    %esi,0x4(%esp)
 118cc46:	89 3c 24             	mov    %edi,(%esp)
 118cc49:	c7 44 24 10 00 00 00 	movl   $0x0,0x10(%esp)
 118cc50:	00 
 118cc51:	e8 6a eb 69 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 118cc56:	85 c0                	test   %eax,%eax
 118cc58:	0f 85 66 03 00 00    	jne    118cfc4 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x12974>
 118cc5e:	c7 84 24 2c 0a 00 00 	movl   $0xd,0xa2c(%esp)
 118cc65:	0d 00 00 00 
 118cc69:	c7 84 24 24 0a 00 00 	movl   $0x3ff00000,0xa24(%esp)
 118cc70:	00 00 f0 3f 
 118cc74:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 118cc7b:	00 00 00 00 
 118cc7f:	f2 0f 10 44 24 38    	movsd  0x38(%esp),%xmm0
 118cc85:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 118cc8b:	89 74 24 04          	mov    %esi,0x4(%esp)
 118cc8f:	8b 84 24 e8 00 00 00 	mov    0xe8(%esp),%eax
 118cc96:	89 04 24             	mov    %eax,(%esp)
 118ccce:	00 00 00 00 
 118ccd2:	c7 84 24 24 0a 00 00 	movl   $0x0,0xa24(%esp)
 118ccd9:	00 00 00 00 
 118ccdd:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 118cce4:	00 00 00 00 
 118cce8:	8b 44 24 24          	mov    0x24(%esp),%eax
 118ccec:	f2 0f 10 00          	movsd  (%eax),%xmm0
 118ccf0:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 118ccf6:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 118ccfd:	89 44 24 04          	mov    %eax,0x4(%esp)
 118cd01:	8b 44 24 48          	mov    0x48(%esp),%eax
 118cd05:	89 04 24             	mov    %eax,(%esp)
 118cd08:	c7 44 24 10 00 00 00 	movl   $0x0,0x10(%esp)
 118cd0f:	00 
 118cd10:	e8 ab ea 69 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 118cd15:	85 c0                	test   %eax,%eax
 118cd17:	0f 85 c0 f6 ff ff    	jne    118c3dd <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x11d8d>
 118cd1d:	e9 a2 02 00 00       	jmp    118cfc4 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x12974>
 118cd22:	c7 84 24 18 0a 00 00 	movl   $0x2fc,0xa18(%esp)
 118cd29:	fc 02 00 00 
 118cd2d:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118cd30:	8b 01                	mov    (%ecx),%eax
 118cd32:	8b 40 0c             	mov    0xc(%eax),%eax
 118cd35:	89 0c 24             	mov    %ecx,(%esp)
 118cd38:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 118cd3f:	00 
 118cd40:	ff d0                	call   *%eax
 118cd42:	89 04 24             	mov    %eax,(%esp)
 118cd45:	c7 44 24 08 e1 7a 84 	movl   $0x3f847ae1,0x8(%esp)
 118cd4c:	3f 
 118cd4d:	c7 44 24 04 7b 14 ae 	movl   $0x47ae147b,0x4(%esp)
 118cd54:	47 
 118cd55:	e8 66 ef 69 00       	call   182bcc0 <YYRValue::operator+=(double)@plt>
 118cd5a:	c7 84 24 18 0a 00 00 	movl   $0x2fd,0xa18(%esp)
 118cd61:	fd 02 00 00 
 118cd65:	8b 84 24 cc 06 00 00 	mov    0x6cc(%esp),%eax
 118cd6c:	b9 46 00 00 00       	mov    $0x46,%ecx
 118cd71:	0f a3 c1             	bt     %eax,%ecx
 118cd74:	73 0f                	jae    118cd85 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x12735>
 118cd76:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 118cd7d:	89 04 24             	mov    %eax,(%esp)
 118cd80:	e8 3b e9 69 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118cd85:	c7 84 24 c0 06 00 00 	movl   $0x0,0x6c0(%esp)
 118cd8c:	00 00 00 00 
 118cd90:	c7 84 24 c8 06 00 00 	movl   $0x0,0x6c8(%esp)
 118cd97:	00 00 00 00 
 118cd9b:	c7 84 24 cc 06 00 00 	movl   $0x5,0x6cc(%esp)
 118cda2:	05 00 00 00 
 118cda6:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118cda9:	8b 01                	mov    (%ecx),%eax
 118cdab:	8b 40 0c             	mov    0xc(%eax),%eax
 118cdae:	89 0c 24             	mov    %ecx,(%esp)
 118cdb1:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 118cdb8:	00 
 118cdb9:	ff d0                	call   *%eax
 118cdbb:	89 c6                	mov    %eax,%esi
 118cdbd:	89 44 24 04          	mov    %eax,0x4(%esp)
 118cdc1:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 118cdc8:	89 04 24             	mov    %eax,(%esp)
 118cdcb:	e8 90 e9 69 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 118cdd0:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 118cdd7:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 118cdde:	8b 44 24 44          	mov    0x44(%esp),%eax
 118cde2:	89 44 24 04          	mov    %eax,0x4(%esp)
 118cde6:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 118cded:	89 04 24             	mov    %eax,(%esp)
 118cdf0:	e8 7b e9 69 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 118cdf5:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 118cdfc:	89 84 24 fc 0a 00 00 	mov    %eax,0xafc(%esp)
 118ce03:	8b 84 24 a0 00 00 00 	mov    0xa0(%esp),%eax
 118ce0a:	89 44 24 04          	mov    %eax,0x4(%esp)
 118ce0e:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 118ce15:	89 04 24             	mov    %eax,(%esp)
 118ce18:	e8 53 e9 69 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 118ce1d:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 118ce24:	89 84 24 00 0b 00 00 	mov    %eax,0xb00(%esp)
 118ce2b:	8b 44 24 60          	mov    0x60(%esp),%eax
 118ce2f:	8b 40 04             	mov    0x4(%eax),%eax
 118ce32:	8d 8c 24 f8 0a 00 00 	lea    0xaf8(%esp),%ecx
 118ce39:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 118ce3d:	89 44 24 10          	mov    %eax,0x10(%esp)
 118ce41:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 118ce48:	89 44 24 08          	mov    %eax,0x8(%esp)
 118ce4c:	8b 45 0c             	mov    0xc(%ebp),%eax
 118ce4f:	89 44 24 04          	mov    %eax,0x4(%esp)
 118ce53:	8b 45 08             	mov    0x8(%ebp),%eax
 118ce56:	89 04 24             	mov    %eax,(%esp)
 118ce59:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
 118ce60:	00 
 118ce61:	e8 9a e9 69 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 118ce66:	89 c7                	mov    %eax,%edi
 118ce68:	8b 45 08             	mov    0x8(%ebp),%eax
 118ce6b:	89 04 24             	mov    %eax,(%esp)
 118ce6e:	e8 1d e9 69 00       	call   182b790 <PushContextStack(YYObjectBase*)@plt>
 118ce73:	89 7c 24 04          	mov    %edi,0x4(%esp)
 118ce77:	89 34 24             	mov    %esi,(%esp)
 118ce7a:	e8 e1 e8 69 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 118ce7f:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 118ce86:	e8 15 e9 69 00       	call   182b7a0 <PopContextStack(int)@plt>
 118ce8b:	c7 84 24 18 0a 00 00 	movl   $0x2ff,0xa18(%esp)
 118ce92:	ff 02 00 00 
 118ce96:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118ce99:	8b 01                	mov    (%ecx),%eax
 118ce9b:	8b 40 0c             	mov    0xc(%eax),%eax
 118ce9e:	89 0c 24             	mov    %ecx,(%esp)
 118cea1:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 118cea8:	00 
 118cea9:	ff d0                	call   *%eax
 118ceab:	89 44 24 7c          	mov    %eax,0x7c(%esp)
 118ceaf:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 118ceb6:	00 00 00 00 
 118ceba:	c7 84 24 24 0a 00 00 	movl   $0x3fb99999,0xa24(%esp)
 118cec1:	99 99 b9 3f 
 118cec5:	c7 84 24 20 0a 00 00 	movl   $0x9999999a,0xa20(%esp)
 118cecc:	9a 99 99 99 
 118ced0:	8b 44 24 24          	mov    0x24(%esp),%eax
 118ced4:	f2 0f 10 00          	movsd  (%eax),%xmm0
 118ced8:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 118cede:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 118cee5:	89 44 24 04          	mov    %eax,0x4(%esp)
 118cee9:	8b 44 24 7c          	mov    0x7c(%esp),%eax
 118ceed:	89 04 24             	mov    %eax,(%esp)
 118cef0:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
 118cef7:	00 
 118cef8:	e8 c3 e8 69 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 118cefd:	83 f8 fe             	cmp    $0xfffffffe,%eax
 118cf00:	0f 84 be 00 00 00    	je     118cfc4 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x12974>
 118cf06:	85 c0                	test   %eax,%eax
 118cf08:	0f 89 b6 00 00 00    	jns    118cfc4 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x12974>
 118cf0e:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118cf11:	8b 01                	mov    (%ecx),%eax
 118cf13:	8b 40 0c             	mov    0xc(%eax),%eax
 118cf16:	89 0c 24             	mov    %ecx,(%esp)
 118cf19:	c7 44 24 04 19 8d 01 	movl   $0x18d19,0x4(%esp)
 118cf20:	00 
 118cf21:	ff d0                	call   *%eax
 118cf23:	89 44 24 68          	mov    %eax,0x68(%esp)
 118cf27:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 118cf2e:	00 00 00 00 
 118cf32:	c7 84 24 24 0a 00 00 	movl   $0x0,0xa24(%esp)
 118cf39:	00 00 00 00 
 118cf3d:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 118cf44:	00 00 00 00 
 118cf48:	8b 44 24 24          	mov    0x24(%esp),%eax
 118cf4c:	f2 0f 10 00          	movsd  (%eax),%xmm0
 118cf50:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 118cf56:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 118cf5d:	89 44 24 04          	mov    %eax,0x4(%esp)
 118cf61:	8b 44 24 68          	mov    0x68(%esp),%eax
 118cf65:	89 04 24             	mov    %eax,(%esp)
 118cf68:	c7 44 24 10 00 00 00 	movl   $0x0,0x10(%esp)
 118cf6f:	00 
 118cf70:	e8 4b e8 69 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 118cf75:	85 c0                	test   %eax,%eax
 118cf77:	74 4b                	je     118cfc4 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x12974>
 118cf79:	c7 84 24 18 0a 00 00 	movl   $0x301,0xa18(%esp)
 118cf80:	01 03 00 00 
 118cf84:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118cf87:	8b 01                	mov    (%ecx),%eax
 118cf89:	8b 40 0c             	mov    0xc(%eax),%eax
 118cf8c:	89 0c 24             	mov    %ecx,(%esp)
 118cf8f:	c7 44 24 04 be 95 01 	movl   $0x195be,0x4(%esp) # verified field ID: wheel_spin
 118cf96:	00 
 118cf97:	ff d0                	call   *%eax
 118cf99:	89 c6                	mov    %eax,%esi
 118cf9b:	8b 40 0c             	mov    0xc(%eax),%eax
 118cf9e:	b9 46 00 00 00       	mov    $0x46,%ecx
 118cfa3:	0f a3 c1             	bt     %eax,%ecx
 118cfa6:	73 08                	jae    118cfb0 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x12960>
 118cfa8:	89 34 24             	mov    %esi,(%esp)
 118cfab:	e8 10 e7 69 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118cfb0:	c7 46 0c 00 00 00 00 	movl   $0x0,0xc(%esi)
 118cfb7:	c7 46 04 00 00 e0 3f 	movl   $0x3fe00000,0x4(%esi)
 118cfbe:	c7 06 00 00 00 00    	movl   $0x0,(%esi)
 118cfc4:	c7 84 24 18 0a 00 00 	movl   $0x306,0xa18(%esp)
 118cfcb:	06 03 00 00 
 118cfcf:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118cfd2:	8b 01                	mov    (%ecx),%eax
 118cfd4:	8b 40 0c             	mov    0xc(%eax),%eax
 118cfd7:	89 0c 24             	mov    %ecx,(%esp)
 118cfda:	c7 44 24 04 d5 95 01 	movl   $0x195d5,0x4(%esp) # verified field ID: xspeed
 118cfe1:	00 
 118cfe2:	ff d0                	call   *%eax
 118cfe4:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 118cfeb:	00 00 00 00 
 118cfef:	c7 84 24 24 0a 00 00 	movl   $0x40240000,0xa24(%esp)
 118cff6:	00 00 24 40 
 118cffa:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 118d001:	00 00 00 00 
 118d005:	8b 4c 24 24          	mov    0x24(%esp),%ecx
 118d349:	b9 46 00 00 00       	mov    $0x46,%ecx
 118d34e:	0f a3 c1             	bt     %eax,%ecx
 118d351:	73 0f                	jae    118d362 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x12d12>
 118d353:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 118d35a:	89 04 24             	mov    %eax,(%esp)
 118d35d:	e8 5e e3 69 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118d362:	c7 84 24 c0 06 00 00 	movl   $0x0,0x6c0(%esp)
 118d369:	00 00 00 00 
 118d36d:	c7 84 24 c8 06 00 00 	movl   $0x0,0x6c8(%esp)
 118d374:	00 00 00 00 
 118d378:	c7 84 24 cc 06 00 00 	movl   $0x5,0x6cc(%esp)
 118d37f:	05 00 00 00 
 118d383:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118d386:	8b 01                	mov    (%ecx),%eax
 118d388:	8b 40 0c             	mov    0xc(%eax),%eax
 118d38b:	89 0c 24             	mov    %ecx,(%esp)
 118d38e:	c7 44 24 04 d5 95 01 	movl   $0x195d5,0x4(%esp) # verified field ID: xspeed
 118d395:	00 
 118d396:	ff d0                	call   *%eax
 118d398:	89 44 24 50          	mov    %eax,0x50(%esp)
 118d39c:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118d39f:	8b 01                	mov    (%ecx),%eax
 118d3a1:	8b 40 0c             	mov    0xc(%eax),%eax
 118d3a4:	89 0c 24             	mov    %ecx,(%esp)
 118d3a7:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 118d3ae:	00 
 118d3af:	ff d0                	call   *%eax
 118d3b1:	89 44 24 7c          	mov    %eax,0x7c(%esp)
 118d3b5:	8b 44 24 7c          	mov    0x7c(%esp),%eax
 118d3b9:	89 44 24 04          	mov    %eax,0x4(%esp)
 118d3bd:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 118d3c4:	89 04 24             	mov    %eax,(%esp)
 118d3c7:	e8 94 e3 69 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 118d3cc:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 118d3d3:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 118d3da:	8b 44 24 44          	mov    0x44(%esp),%eax
 118d3de:	89 44 24 04          	mov    %eax,0x4(%esp)
 118d3e2:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 118d3e9:	89 04 24             	mov    %eax,(%esp)
 118d3ec:	e8 7f e3 69 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 118d3f1:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 118d3f8:	89 84 24 fc 0a 00 00 	mov    %eax,0xafc(%esp)
 118d3ff:	8b 84 24 a0 00 00 00 	mov    0xa0(%esp),%eax
 118d406:	89 44 24 04          	mov    %eax,0x4(%esp)
 118d40a:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 118d411:	89 04 24             	mov    %eax,(%esp)
 118d414:	e8 57 e3 69 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 118d419:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 118d420:	89 84 24 00 0b 00 00 	mov    %eax,0xb00(%esp)
 118d427:	8b 44 24 60          	mov    0x60(%esp),%eax
 118d42b:	8b 40 04             	mov    0x4(%eax),%eax
 118d42e:	8d 8c 24 f8 0a 00 00 	lea    0xaf8(%esp),%ecx
 118d435:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 118d439:	89 44 24 10          	mov    %eax,0x10(%esp)
 118d43d:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 118d444:	89 44 24 08          	mov    %eax,0x8(%esp)
 118d448:	8b 45 0c             	mov    0xc(%ebp),%eax
 118d44b:	89 44 24 04          	mov    %eax,0x4(%esp)
 118d44f:	8b 45 08             	mov    0x8(%ebp),%eax
 118d452:	89 04 24             	mov    %eax,(%esp)
 118d455:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
 118d45c:	00 
 118d45d:	e8 9e e3 69 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 118d462:	8d bc 24 00 06 00 00 	lea    0x600(%esp),%edi
 118d469:	89 44 24 08          	mov    %eax,0x8(%esp)
 118d46d:	8b 44 24 50          	mov    0x50(%esp),%eax
 118d471:	89 44 24 04          	mov    %eax,0x4(%esp)
 118d475:	89 3c 24             	mov    %edi,(%esp)
 118d478:	e8 a3 e6 69 00       	call   182bb20 <operator*(YYRValue const&, YYRValue const&)@plt>
 118d47d:	83 ec 04             	sub    $0x4,%esp
 118d480:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 118d487:	00 00 00 00 
 118d48b:	c7 84 24 24 0a 00 00 	movl   $0x40240000,0xa24(%esp)
 118d492:	00 00 24 40 
 118d496:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 118d49d:	00 00 00 00 
 118d4a1:	8b 44 24 24          	mov    0x24(%esp),%eax
 118d4a5:	f2 0f 10 00          	movsd  (%eax),%xmm0
 118d4a9:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 118d4af:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 118d4b6:	89 44 24 04          	mov    %eax,0x4(%esp)
 118d4ba:	89 3c 24             	mov    %edi,(%esp)
 118d4bd:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
 118d4c4:	00 
 118d4c5:	e8 f6 e2 69 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 118d4ca:	89 c6                	mov    %eax,%esi
 118d4cc:	8b 84 24 0c 06 00 00 	mov    0x60c(%esp),%eax
 118d4d3:	b9 46 00 00 00       	mov    $0x46,%ecx
 118d4d8:	0f a3 c1             	bt     %eax,%ecx
 118d4db:	73 08                	jae    118d4e5 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x12e95>
 118d4dd:	89 3c 24             	mov    %edi,(%esp)
 118d4e0:	e8 db e1 69 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118d4e5:	85 f6                	test   %esi,%esi
 118d4e7:	0f 8e 9d 00 00 00    	jle    118d58a <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x12f3a>
 118d4ed:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118d4f0:	8b 01                	mov    (%ecx),%eax
 118d4f2:	8b 40 0c             	mov    0xc(%eax),%eax
 118d4f5:	89 0c 24             	mov    %ecx,(%esp)
 118d4f8:	c7 44 24 04 1d 8a 01 	movl   $0x18a1d,0x4(%esp)
 118d4ff:	00 
 118d500:	ff d0                	call   *%eax
 118d502:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 118d509:	00 00 00 00 
 118d50d:	c7 84 24 24 0a 00 00 	movl   $0x406f4000,0xa24(%esp)
 118d514:	00 40 6f 40 
 118d518:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 118d51f:	00 00 00 00 
 118d523:	8b 4c 24 24          	mov    0x24(%esp),%ecx
 118d527:	f2 0f 10 01          	movsd  (%ecx),%xmm0
 118d59c:	b9 46 00 00 00       	mov    $0x46,%ecx
 118d5a1:	0f a3 c1             	bt     %eax,%ecx
 118d5a4:	73 0f                	jae    118d5b5 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x12f65>
 118d5a6:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 118d5ad:	89 04 24             	mov    %eax,(%esp)
 118d5b0:	e8 0b e1 69 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118d5b5:	c7 84 24 c0 06 00 00 	movl   $0x0,0x6c0(%esp)
 118d5bc:	00 00 00 00 
 118d5c0:	c7 84 24 c8 06 00 00 	movl   $0x0,0x6c8(%esp)
 118d5c7:	00 00 00 00 
 118d5cb:	c7 84 24 cc 06 00 00 	movl   $0x5,0x6cc(%esp)
 118d5d2:	05 00 00 00 
 118d5d6:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118d5d9:	8b 01                	mov    (%ecx),%eax
 118d5db:	8b 40 0c             	mov    0xc(%eax),%eax
 118d5de:	89 0c 24             	mov    %ecx,(%esp)
 118d5e1:	c7 44 24 04 d5 95 01 	movl   $0x195d5,0x4(%esp) # verified field ID: xspeed
 118d5e8:	00 
 118d5e9:	ff d0                	call   *%eax
 118d5eb:	89 44 24 50          	mov    %eax,0x50(%esp)
 118d5ef:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118d5f2:	8b 01                	mov    (%ecx),%eax
 118d5f4:	8b 40 0c             	mov    0xc(%eax),%eax
 118d5f7:	89 0c 24             	mov    %ecx,(%esp)
 118d5fa:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 118d601:	00 
 118d602:	ff d0                	call   *%eax
 118d604:	89 44 24 7c          	mov    %eax,0x7c(%esp)
 118d608:	8b 44 24 7c          	mov    0x7c(%esp),%eax
 118d60c:	89 44 24 04          	mov    %eax,0x4(%esp)
 118d610:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 118d617:	89 04 24             	mov    %eax,(%esp)
 118d61a:	e8 41 e1 69 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 118d61f:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 118d626:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 118d62d:	8b 44 24 44          	mov    0x44(%esp),%eax
 118d631:	89 44 24 04          	mov    %eax,0x4(%esp)
 118d635:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 118d63c:	89 04 24             	mov    %eax,(%esp)
 118d63f:	e8 2c e1 69 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 118d644:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 118d64b:	89 84 24 fc 0a 00 00 	mov    %eax,0xafc(%esp)
 118d652:	8b 84 24 a0 00 00 00 	mov    0xa0(%esp),%eax
 118d659:	89 44 24 04          	mov    %eax,0x4(%esp)
 118d65d:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 118d664:	89 04 24             	mov    %eax,(%esp)
 118d667:	e8 04 e1 69 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 118d66c:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 118d673:	89 84 24 00 0b 00 00 	mov    %eax,0xb00(%esp)
 118d67a:	8b 44 24 60          	mov    0x60(%esp),%eax
 118d67e:	8b 40 04             	mov    0x4(%eax),%eax
 118d681:	8d 8c 24 f8 0a 00 00 	lea    0xaf8(%esp),%ecx
 118d688:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 118d68c:	89 44 24 10          	mov    %eax,0x10(%esp)
 118d690:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 118d697:	89 44 24 08          	mov    %eax,0x8(%esp)
 118d69b:	8b 45 0c             	mov    0xc(%ebp),%eax
 118d69e:	89 44 24 04          	mov    %eax,0x4(%esp)
 118d6a2:	8b 45 08             	mov    0x8(%ebp),%eax
 118d6a5:	89 04 24             	mov    %eax,(%esp)
 118d6a8:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
 118d6af:	00 
 118d6b0:	e8 4b e1 69 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 118d6b5:	8d b4 24 00 06 00 00 	lea    0x600(%esp),%esi
 118d6bc:	89 44 24 08          	mov    %eax,0x8(%esp)
 118d6c0:	8b 44 24 50          	mov    0x50(%esp),%eax
 118d6c4:	89 44 24 04          	mov    %eax,0x4(%esp)
 118d6c8:	89 34 24             	mov    %esi,(%esp)
 118d6cb:	e8 50 e4 69 00       	call   182bb20 <operator*(YYRValue const&, YYRValue const&)@plt>
 118d6d0:	83 ec 04             	sub    $0x4,%esp
 118d6d3:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 118d6da:	00 00 00 00 
 118d6de:	c7 84 24 24 0a 00 00 	movl   $0x40240000,0xa24(%esp)
 118d6e5:	00 00 24 40 
 118d6e9:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 118d6f0:	00 00 00 00 
 118d6f4:	8b 44 24 24          	mov    0x24(%esp),%eax
 118d6f8:	f2 0f 10 00          	movsd  (%eax),%xmm0
 118d6fc:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 118d702:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 118d709:	89 44 24 04          	mov    %eax,0x4(%esp)
 118d70d:	89 34 24             	mov    %esi,(%esp)
 118d710:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
 118d717:	00 
 118d718:	e8 a3 e0 69 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 118d71d:	83 f8 fe             	cmp    $0xfffffffe,%eax
 118d720:	0f 95 44 24 38       	setne  0x38(%esp)
 118d725:	85 c0                	test   %eax,%eax
 118d727:	0f 98 84 24 8c 00 00 	sets   0x8c(%esp)
 118d72e:	00 
 118d72f:	8b 84 24 0c 06 00 00 	mov    0x60c(%esp),%eax
 118d736:	b9 46 00 00 00       	mov    $0x46,%ecx
 118d73b:	0f a3 c1             	bt     %eax,%ecx
 118d73e:	73 08                	jae    118d748 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x130f8>
 118d740:	89 34 24             	mov    %esi,(%esp)
 118d743:	e8 78 df 69 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118d748:	8a 84 24 8c 00 00 00 	mov    0x8c(%esp),%al
 118d74f:	20 44 24 38          	and    %al,0x38(%esp)
 118d753:	0f 84 1b 05 00 00    	je     118dc74 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x13624>
 118d759:	c7 84 24 18 0a 00 00 	movl   $0x32a,0xa18(%esp)
 118d760:	2a 03 00 00 
 118d764:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118d767:	8b 01                	mov    (%ecx),%eax
 118d769:	8b 40 0c             	mov    0xc(%eax),%eax
 118d76c:	89 0c 24             	mov    %ecx,(%esp)
 118d76f:	c7 44 24 04 1d 8a 01 	movl   $0x18a1d,0x4(%esp)
 118d776:	00 
 118d777:	ff d0                	call   *%eax
 118d779:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 118e01c:	c7 84 24 c8 06 00 00 	movl   $0x0,0x6c8(%esp)
 118e023:	00 00 00 00 
 118e027:	c7 84 24 cc 06 00 00 	movl   $0x5,0x6cc(%esp)
 118e02e:	05 00 00 00 
 118e032:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118e035:	8b 01                	mov    (%ecx),%eax
 118e037:	8b 40 0c             	mov    0xc(%eax),%eax
 118e03a:	89 0c 24             	mov    %ecx,(%esp)
 118e03d:	c7 44 24 04 d5 95 01 	movl   $0x195d5,0x4(%esp) # verified field ID: xspeed
 118e044:	00 
 118e045:	ff d0                	call   *%eax
 118e047:	89 44 24 50          	mov    %eax,0x50(%esp)
 118e04b:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118e04e:	8b 01                	mov    (%ecx),%eax
 118e050:	8b 40 0c             	mov    0xc(%eax),%eax
 118e053:	89 0c 24             	mov    %ecx,(%esp)
 118e056:	c7 44 24 04 49 8b 01 	movl   $0x18b49,0x4(%esp)
 118e05d:	00 
 118e05e:	ff d0                	call   *%eax
 118e060:	89 84 24 a8 00 00 00 	mov    %eax,0xa8(%esp)
 118e067:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118e06a:	8b 01                	mov    (%ecx),%eax
 118e06c:	8b 40 0c             	mov    0xc(%eax),%eax
 118e06f:	89 0c 24             	mov    %ecx,(%esp)
 118e072:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 118e079:	00 
 118e07a:	ff d0                	call   *%eax
 118e07c:	89 44 24 7c          	mov    %eax,0x7c(%esp)
 118e080:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118e083:	8b 01                	mov    (%ecx),%eax
 118e085:	8b 40 0c             	mov    0xc(%eax),%eax
 118e088:	89 0c 24             	mov    %ecx,(%esp)
 118e08b:	c7 44 24 04 d4 95 01 	movl   $0x195d4,0x4(%esp)
 118e092:	00 
 118e093:	ff d0                	call   *%eax
 118e095:	89 c6                	mov    %eax,%esi
 118e097:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118e09a:	8b 01                	mov    (%ecx),%eax
 118e09c:	8b 40 0c             	mov    0xc(%eax),%eax
 118e09f:	89 0c 24             	mov    %ecx,(%esp)
 118e0a2:	c7 44 24 04 f7 89 01 	movl   $0x189f7,0x4(%esp)
 118e0a9:	00 
 118e0aa:	ff d0                	call   *%eax
 118e0ac:	89 74 24 04          	mov    %esi,0x4(%esp)
 118e0b0:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 118e0b7:	89 04 24             	mov    %eax,(%esp)
 118e0ba:	e8 a1 d6 69 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 118e0bf:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 118e0c6:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 118e0cd:	8b 83 b0 03 ff ff    	mov    -0xfc50(%ebx),%eax
 118e0d3:	8b 40 04             	mov    0x4(%eax),%eax
 118e0d6:	8d 8c 24 f8 0a 00 00 	lea    0xaf8(%esp),%ecx
 118e0dd:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 118e0e1:	89 44 24 10          	mov    %eax,0x10(%esp)
 118e0e5:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 118e0ec:	89 44 24 08          	mov    %eax,0x8(%esp)
 118e0f0:	8b 45 0c             	mov    0xc(%ebp),%eax
 118e0f3:	89 44 24 04          	mov    %eax,0x4(%esp)
 118e0f7:	8b 45 08             	mov    0x8(%ebp),%eax
 118e0fa:	89 04 24             	mov    %eax,(%esp)
 118e0fd:	c7 44 24 0c 01 00 00 	movl   $0x1,0xc(%esp)
 118e104:	00 
 118e105:	e8 f6 d6 69 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 118e10a:	89 44 24 04          	mov    %eax,0x4(%esp)
 118e10e:	8d b4 24 80 09 00 00 	lea    0x980(%esp),%esi
 118e115:	89 34 24             	mov    %esi,(%esp)
 118e118:	e8 43 d6 69 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 118e11d:	8b 83 b0 fc fe ff    	mov    -0x10350(%ebx),%eax
 118e123:	8b 40 04             	mov    0x4(%eax),%eax
 118e126:	89 74 24 0c          	mov    %esi,0xc(%esp)
 118e12a:	89 44 24 04          	mov    %eax,0x4(%esp)
 118e12e:	8b 45 08             	mov    0x8(%ebp),%eax
 118e131:	89 04 24             	mov    %eax,(%esp)
 118e134:	c7 44 24 08 00 00 00 	movl   $0x80000000,0x8(%esp)
 118e13b:	80 
 118e13c:	e8 ef da 69 00       	call   182bc30 <Variable_SetValue_Direct(YYObjectBase*, int, int, RValue*)@plt>
 118e141:	c7 84 24 18 0a 00 00 	movl   $0x34d,0xa18(%esp)
 118e148:	4d 03 00 00 
 118e14c:	8b 44 24 5c          	mov    0x5c(%esp),%eax
 118e150:	8b 40 04             	mov    0x4(%eax),%eax
 118e153:	8d 8c 24 90 09 00 00 	lea    0x990(%esp),%ecx
 118e15a:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
 118e15e:	89 44 24 04          	mov    %eax,0x4(%esp)
 118e162:	8b 45 08             	mov    0x8(%ebp),%eax
 118e165:	89 04 24             	mov    %eax,(%esp)
 118e168:	c7 44 24 08 00 00 00 	movl   $0x80000000,0x8(%esp)
 118e16f:	80 
 118e170:	e8 1b d9 69 00       	call   182ba90 <Variable_GetBuiltIn_Direct(YYObjectBase*, int, int, RValue*)@plt>
 118e175:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 118e17c:	00 00 00 00 
 118e180:	c7 84 24 24 0a 00 00 	movl   $0x40100000,0xa24(%esp)
 118e187:	00 00 10 40 
 118e18b:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 118e192:	00 00 00 00 
 118e196:	8b 44 24 24          	mov    0x24(%esp),%eax
 118e19a:	f2 0f 10 00          	movsd  (%eax),%xmm0
 118e19e:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 118e1a4:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 118e1ab:	89 44 24 04          	mov    %eax,0x4(%esp)
 118e1af:	8d 84 24 90 09 00 00 	lea    0x990(%esp),%eax
 118e1b6:	89 04 24             	mov    %eax,(%esp)
 118e1b9:	c7 44 24 10 00 00 00 	movl   $0x0,0x10(%esp)
 118e1c0:	00 
 118e1c1:	e8 fa d5 69 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 118e1c6:	85 c0                	test   %eax,%eax
 118e1c8:	0f 85 7a 01 00 00    	jne    118e348 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x13cf8>
 118e1ce:	c7 84 24 18 0a 00 00 	movl   $0x34f,0xa18(%esp)
 118e1d5:	4f 03 00 00 
 118e1d9:	8b 84 24 cc 06 00 00 	mov    0x6cc(%esp),%eax
 118f129:	89 04 24             	mov    %eax,(%esp)
 118f12c:	e8 8f c5 69 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118f131:	c7 84 24 c0 06 00 00 	movl   $0x0,0x6c0(%esp)
 118f138:	00 00 00 00 
 118f13c:	c7 84 24 c8 06 00 00 	movl   $0x0,0x6c8(%esp)
 118f143:	00 00 00 00 
 118f147:	c7 84 24 cc 06 00 00 	movl   $0x5,0x6cc(%esp)
 118f14e:	05 00 00 00 
 118f152:	8b 84 24 bc 06 00 00 	mov    0x6bc(%esp),%eax
 118f159:	0f a3 c6             	bt     %eax,%esi
 118f15c:	73 0f                	jae    118f16d <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x14b1d>
 118f15e:	8d 84 24 b0 06 00 00 	lea    0x6b0(%esp),%eax
 118f165:	89 04 24             	mov    %eax,(%esp)
 118f168:	e8 53 c5 69 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118f16d:	c7 84 24 b0 06 00 00 	movl   $0x0,0x6b0(%esp)
 118f174:	00 00 00 00 
 118f178:	c7 84 24 b8 06 00 00 	movl   $0x0,0x6b8(%esp)
 118f17f:	00 00 00 00 
 118f183:	c7 84 24 bc 06 00 00 	movl   $0x5,0x6bc(%esp)
 118f18a:	05 00 00 00 
 118f18e:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118f191:	8b 01                	mov    (%ecx),%eax
 118f193:	8b 40 0c             	mov    0xc(%eax),%eax
 118f196:	89 0c 24             	mov    %ecx,(%esp)
 118f199:	c7 44 24 04 b4 92 01 	movl   $0x192b4,0x4(%esp) # verified field ID: tire_heat
 118f1a0:	00 
 118f1a1:	ff d0                	call   *%eax
 118f1a3:	89 c7                	mov    %eax,%edi
 118f1a5:	89 44 24 04          	mov    %eax,0x4(%esp)
 118f1a9:	8d b4 24 20 0a 00 00 	lea    0xa20(%esp),%esi
 118f1b0:	89 34 24             	mov    %esi,(%esp)
 118f1b3:	c7 44 24 0c 00 80 66 	movl   $0x40668000,0xc(%esp)
 118f1ba:	40 
 118f1bb:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 118f1c2:	00 
 118f1c3:	e8 08 c8 69 00       	call   182b9d0 <operator/(YYRValue const&, double)@plt>
 118f1c8:	83 ec 04             	sub    $0x4,%esp
 118f1cb:	89 74 24 04          	mov    %esi,0x4(%esp)
 118f1cf:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 118f1d6:	89 04 24             	mov    %eax,(%esp)
 118f1d9:	e8 82 c5 69 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 118f1de:	8b 84 24 2c 0a 00 00 	mov    0xa2c(%esp),%eax
 118f1e5:	b9 46 00 00 00       	mov    $0x46,%ecx
 118f1ea:	0f a3 c1             	bt     %eax,%ecx
 118f1ed:	73 0f                	jae    118f1fe <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x14bae>
 118f1ef:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 118f1f6:	89 04 24             	mov    %eax,(%esp)
 118f1f9:	e8 c2 c4 69 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118f1fe:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 118f205:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 118f20c:	8b 83 94 ab ff ff    	mov    -0x546c(%ebx),%eax
 118f212:	89 44 24 68          	mov    %eax,0x68(%esp)
 118f216:	8b 40 04             	mov    0x4(%eax),%eax
 118f219:	8d 8c 24 f8 0a 00 00 	lea    0xaf8(%esp),%ecx
 118f220:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 118f224:	89 44 24 10          	mov    %eax,0x10(%esp)
 118f228:	8d 84 24 b0 06 00 00 	lea    0x6b0(%esp),%eax
 118f22f:	89 44 24 08          	mov    %eax,0x8(%esp)
 118f233:	8b 45 0c             	mov    0xc(%ebp),%eax
 118f236:	89 44 24 04          	mov    %eax,0x4(%esp)
 118f23a:	8b 45 08             	mov    0x8(%ebp),%eax
 118f23d:	89 04 24             	mov    %eax,(%esp)
 118f240:	c7 44 24 0c 01 00 00 	movl   $0x1,0xc(%esp)
 118f247:	00 
 118f248:	e8 b3 c5 69 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 118f24d:	89 44 24 04          	mov    %eax,0x4(%esp)
 118f251:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 118f258:	89 04 24             	mov    %eax,(%esp)
 118f25b:	e8 00 c5 69 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 118f260:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 118f267:	89 84 24 fc 0a 00 00 	mov    %eax,0xafc(%esp)
 118f26e:	8b 44 24 44          	mov    0x44(%esp),%eax
 118f272:	89 44 24 04          	mov    %eax,0x4(%esp)
 118f276:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 118f27d:	89 04 24             	mov    %eax,(%esp)
 118f280:	e8 eb c4 69 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 118f285:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 118f28c:	89 84 24 00 0b 00 00 	mov    %eax,0xb00(%esp)
 118f293:	8b 83 44 d2 ff ff    	mov    -0x2dbc(%ebx),%eax
 118f299:	89 84 24 e8 00 00 00 	mov    %eax,0xe8(%esp)
 118f2a0:	89 44 24 04          	mov    %eax,0x4(%esp)
 118f2a4:	8d 84 24 68 0a 00 00 	lea    0xa68(%esp),%eax
 118f2ab:	89 04 24             	mov    %eax,(%esp)
 118f2ae:	e8 bd c4 69 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 118f2b3:	8d 84 24 68 0a 00 00 	lea    0xa68(%esp),%eax
 118f2ba:	89 84 24 04 0b 00 00 	mov    %eax,0xb04(%esp)
 118f2c1:	8b 44 24 60          	mov    0x60(%esp),%eax
 118f2c5:	8b 40 04             	mov    0x4(%eax),%eax
 118f2c8:	8d 8c 24 fc 0a 00 00 	lea    0xafc(%esp),%ecx
 118f2cf:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 118f2d3:	89 44 24 10          	mov    %eax,0x10(%esp)
 118f2d7:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 118f2de:	89 44 24 08          	mov    %eax,0x8(%esp)
 118f2e2:	8b 45 0c             	mov    0xc(%ebp),%eax
 118f2e5:	89 44 24 04          	mov    %eax,0x4(%esp)
 118f2e9:	8b 45 08             	mov    0x8(%ebp),%eax
 118f2ec:	89 04 24             	mov    %eax,(%esp)
 118f2ef:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
 118f2f6:	00 
 118f2f7:	e8 04 c5 69 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 118f2fc:	89 44 24 04          	mov    %eax,0x4(%esp)
 118f300:	8d 84 24 80 08 00 00 	lea    0x880(%esp),%eax
 118f307:	89 04 24             	mov    %eax,(%esp)
 118f30a:	e8 51 c4 69 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 118f30f:	c7 84 24 18 0a 00 00 	movl   $0x38e,0xa18(%esp)
 118f316:	8e 03 00 00 
 118f31a:	89 7c 24 04          	mov    %edi,0x4(%esp)
 118f31e:	8d b4 24 00 06 00 00 	lea    0x600(%esp),%esi
 118f325:	89 34 24             	mov    %esi,(%esp)
 118f3d0:	89 04 24             	mov    %eax,(%esp)
 118f3d3:	e8 e8 c2 69 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118f3d8:	c7 84 24 c0 06 00 00 	movl   $0x0,0x6c0(%esp)
 118f3df:	00 00 00 00 
 118f3e3:	c7 84 24 c8 06 00 00 	movl   $0x0,0x6c8(%esp)
 118f3ea:	00 00 00 00 
 118f3ee:	c7 84 24 cc 06 00 00 	movl   $0x5,0x6cc(%esp)
 118f3f5:	05 00 00 00 
 118f3f9:	8b 84 24 bc 06 00 00 	mov    0x6bc(%esp),%eax
 118f400:	0f a3 c7             	bt     %eax,%edi
 118f403:	73 0f                	jae    118f414 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x14dc4>
 118f405:	8d 84 24 b0 06 00 00 	lea    0x6b0(%esp),%eax
 118f40c:	89 04 24             	mov    %eax,(%esp)
 118f40f:	e8 ac c2 69 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118f414:	c7 84 24 b0 06 00 00 	movl   $0x0,0x6b0(%esp)
 118f41b:	00 00 00 00 
 118f41f:	c7 84 24 b8 06 00 00 	movl   $0x0,0x6b8(%esp)
 118f426:	00 00 00 00 
 118f42a:	c7 84 24 bc 06 00 00 	movl   $0x5,0x6bc(%esp)
 118f431:	05 00 00 00 
 118f435:	8b 4d 08             	mov    0x8(%ebp),%ecx
 118f438:	8b 01                	mov    (%ecx),%eax
 118f43a:	8b 40 0c             	mov    0xc(%eax),%eax
 118f43d:	89 0c 24             	mov    %ecx,(%esp)
 118f440:	c7 44 24 04 b4 92 01 	movl   $0x192b4,0x4(%esp) # verified field ID: tire_heat
 118f447:	00 
 118f448:	ff d0                	call   *%eax
 118f44a:	89 44 24 04          	mov    %eax,0x4(%esp)
 118f44e:	8d b4 24 20 0a 00 00 	lea    0xa20(%esp),%esi
 118f455:	89 34 24             	mov    %esi,(%esp)
 118f458:	c7 44 24 0c 00 80 66 	movl   $0x40668000,0xc(%esp)
 118f45f:	40 
 118f460:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 118f467:	00 
 118f468:	e8 63 c5 69 00       	call   182b9d0 <operator/(YYRValue const&, double)@plt>
 118f46d:	83 ec 04             	sub    $0x4,%esp
 118f470:	89 74 24 04          	mov    %esi,0x4(%esp)
 118f474:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 118f47b:	89 04 24             	mov    %eax,(%esp)
 118f47e:	e8 dd c2 69 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 118f483:	8b 84 24 2c 0a 00 00 	mov    0xa2c(%esp),%eax
 118f48a:	b9 46 00 00 00       	mov    $0x46,%ecx
 118f48f:	0f a3 c1             	bt     %eax,%ecx
 118f492:	73 0f                	jae    118f4a3 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x14e53>
 118f494:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 118f49b:	89 04 24             	mov    %eax,(%esp)
 118f49e:	e8 1d c2 69 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 118f4a3:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 118f4aa:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 118f4b1:	8b 44 24 68          	mov    0x68(%esp),%eax
 118f4b5:	8b 40 04             	mov    0x4(%eax),%eax
 118f4b8:	8d 8c 24 f8 0a 00 00 	lea    0xaf8(%esp),%ecx
 118f4bf:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 118f4c3:	89 44 24 10          	mov    %eax,0x10(%esp)
 118f4c7:	8d 84 24 b0 06 00 00 	lea    0x6b0(%esp),%eax
 118f4ce:	89 44 24 08          	mov    %eax,0x8(%esp)
 118f4d2:	8b 45 0c             	mov    0xc(%ebp),%eax
 118f4d5:	89 44 24 04          	mov    %eax,0x4(%esp)
 118f4d9:	8b 45 08             	mov    0x8(%ebp),%eax
 118f4dc:	89 04 24             	mov    %eax,(%esp)
 118f4df:	c7 44 24 0c 01 00 00 	movl   $0x1,0xc(%esp)
 118f4e6:	00 
 118f4e7:	e8 14 c3 69 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 118f4ec:	89 44 24 04          	mov    %eax,0x4(%esp)
 118f4f0:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 118f4f7:	89 04 24             	mov    %eax,(%esp)
 118f4fa:	e8 61 c2 69 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 118f4ff:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 118f506:	89 84 24 fc 0a 00 00 	mov    %eax,0xafc(%esp)
 118f50d:	8b 44 24 44          	mov    0x44(%esp),%eax
 118f511:	89 44 24 04          	mov    %eax,0x4(%esp)
 118f515:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 118f51c:	89 04 24             	mov    %eax,(%esp)
 118f51f:	e8 4c c2 69 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 118f524:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 118f52b:	89 84 24 00 0b 00 00 	mov    %eax,0xb00(%esp)
 118f532:	8b 84 24 e8 00 00 00 	mov    0xe8(%esp),%eax
 118f539:	89 44 24 04          	mov    %eax,0x4(%esp)
 118f53d:	8d 84 24 68 0a 00 00 	lea    0xa68(%esp),%eax
 118f544:	89 04 24             	mov    %eax,(%esp)
 118f547:	e8 24 c2 69 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 118f54c:	8d 84 24 68 0a 00 00 	lea    0xa68(%esp),%eax
 118f553:	89 84 24 04 0b 00 00 	mov    %eax,0xb04(%esp)
 118f55a:	8b 44 24 60          	mov    0x60(%esp),%eax
 118f55e:	8b 40 04             	mov    0x4(%eax),%eax
 118f561:	8d 8c 24 fc 0a 00 00 	lea    0xafc(%esp),%ecx
 118f568:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 118f56c:	89 44 24 10          	mov    %eax,0x10(%esp)
 118f570:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 118f577:	89 44 24 08          	mov    %eax,0x8(%esp)
 118f57b:	8b 45 0c             	mov    0xc(%ebp),%eax
 118f57e:	89 44 24 04          	mov    %eax,0x4(%esp)
 118f582:	8b 45 08             	mov    0x8(%ebp),%eax
 118f585:	89 04 24             	mov    %eax,(%esp)
 118f588:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
 118f58f:	00 
 118f590:	e8 6b c2 69 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 118f595:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 118f59c:	00 00 00 00 
 118f5a0:	c7 84 24 24 0a 00 00 	movl   $0x3ff00000,0xa24(%esp)
 118f5a7:	00 00 f0 3f 
 118f5ab:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 118f5b2:	00 00 00 00 
 118f5b6:	89 44 24 04          	mov    %eax,0x4(%esp)
 118f5ba:	8d b4 24 20 0a 00 00 	lea    0xa20(%esp),%esi
 118f5c1:	89 34 24             	mov    %esi,(%esp)
 118f5c4:	e8 67 c4 69 00       	call   182ba30 <YYRValue::operator-=(YYRValue const&)@plt>
 118f5c9:	89 74 24 04          	mov    %esi,0x4(%esp)
 118f5cd:	8d 84 24 80 08 00 00 	lea    0x880(%esp),%eax
 11a6506:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 11a650d:	89 44 24 08          	mov    %eax,0x8(%esp)
 11a6511:	8b 45 0c             	mov    0xc(%ebp),%eax
 11a6514:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a6518:	8b 45 08             	mov    0x8(%ebp),%eax
 11a651b:	89 04 24             	mov    %eax,(%esp)
 11a651e:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
 11a6525:	00 
 11a6526:	e8 d5 52 68 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 11a652b:	89 c7                	mov    %eax,%edi
 11a652d:	8b 45 08             	mov    0x8(%ebp),%eax
 11a6530:	89 04 24             	mov    %eax,(%esp)
 11a6533:	e8 58 52 68 00       	call   182b790 <PushContextStack(YYObjectBase*)@plt>
 11a6538:	89 7c 24 04          	mov    %edi,0x4(%esp)
 11a653c:	89 34 24             	mov    %esi,(%esp)
 11a653f:	e8 1c 52 68 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 11a6544:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 11a654b:	e8 50 52 68 00       	call   182b7a0 <PopContextStack(int)@plt>
 11a6550:	c7 84 24 18 0a 00 00 	movl   $0x28a,0xa18(%esp)
 11a6557:	8a 02 00 00 
 11a655b:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11a655e:	8b 01                	mov    (%ecx),%eax
 11a6560:	8b 40 08             	mov    0x8(%eax),%eax
 11a6563:	89 0c 24             	mov    %ecx,(%esp)
 11a6566:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 11a656d:	00 
 11a656e:	ff d0                	call   *%eax
 11a6570:	89 44 24 7c          	mov    %eax,0x7c(%esp)
 11a6574:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 11a657b:	00 00 00 00 
 11a657f:	c7 84 24 24 0a 00 00 	movl   $0x3ff00000,0xa24(%esp)
 11a6586:	00 00 f0 3f 
 11a658a:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 11a6591:	00 00 00 00 
 11a6595:	8b 44 24 24          	mov    0x24(%esp),%eax
 11a6599:	f2 0f 10 00          	movsd  (%eax),%xmm0
 11a659d:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 11a65a3:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 11a65aa:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a65ae:	8b 44 24 7c          	mov    0x7c(%esp),%eax
 11a65b2:	89 04 24             	mov    %eax,(%esp)
 11a65b5:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
 11a65bc:	00 
 11a65bd:	e8 fe 51 68 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 11a65c2:	83 f8 fe             	cmp    $0xfffffffe,%eax
 11a65c5:	74 59                	je     11a6620 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x2bfd0>
 11a65c7:	85 c0                	test   %eax,%eax
 11a65c9:	79 55                	jns    11a6620 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x2bfd0>
 11a65cb:	c7 84 24 18 0a 00 00 	movl   $0x28c,0xa18(%esp)
 11a65d2:	8c 02 00 00 
 11a65d6:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11a65d9:	8b 01                	mov    (%ecx),%eax
 11a65db:	8b 40 0c             	mov    0xc(%eax),%eax
 11a65de:	89 0c 24             	mov    %ecx,(%esp)
 11a65e1:	c7 44 24 04 be 95 01 	movl   $0x195be,0x4(%esp) # verified field ID: wheel_spin
 11a65e8:	00 
 11a65e9:	ff d0                	call   *%eax
 11a65eb:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11a65ee:	8b 01                	mov    (%ecx),%eax
 11a65f0:	8b 40 0c             	mov    0xc(%eax),%eax
 11a65f3:	89 0c 24             	mov    %ecx,(%esp)
 11a65f6:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 11a65fd:	00 
 11a65fe:	ff d0                	call   *%eax
 11a6600:	89 44 24 7c          	mov    %eax,0x7c(%esp)
 11a6604:	8b 44 24 7c          	mov    0x7c(%esp),%eax
 11a6608:	89 04 24             	mov    %eax,(%esp)
 11a660b:	c7 44 24 08 99 99 a9 	movl   $0x3fa99999,0x8(%esp)
 11a6612:	3f 
 11a6613:	c7 44 24 04 9a 99 99 	movl   $0x9999999a,0x4(%esp)
 11a661a:	99 
 11a661b:	e8 a0 56 68 00       	call   182bcc0 <YYRValue::operator+=(double)@plt>
 11a6620:	c7 84 24 18 0a 00 00 	movl   $0x28e,0xa18(%esp)
 11a6627:	8e 02 00 00 
 11a662b:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11a662e:	8b 01                	mov    (%ecx),%eax
 11a6630:	8b 40 0c             	mov    0xc(%eax),%eax
 11a6633:	89 0c 24             	mov    %ecx,(%esp)
 11a6636:	c7 44 24 04 49 8b 01 	movl   $0x18b49,0x4(%esp)
 11a663d:	00 
 11a663e:	ff d0                	call   *%eax
 11a6640:	89 c1                	mov    %eax,%ecx
 11a6642:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 11a6649:	00 00 00 00 
 11a664d:	c7 84 24 24 0a 00 00 	movl   $0x3ff00000,0xa24(%esp)
 11a6654:	00 00 f0 3f 
 11a6658:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 11a665f:	00 00 00 00 
 11a6663:	8b 44 24 24          	mov    0x24(%esp),%eax
 11a6667:	f2 0f 10 00          	movsd  (%eax),%xmm0
 11a666b:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 11a6671:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 11a6678:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a667c:	89 8c 24 a8 00 00 00 	mov    %ecx,0xa8(%esp)
 11a6683:	89 0c 24             	mov    %ecx,(%esp)
 11a6686:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
 11a668d:	00 
 11a668e:	e8 2d 51 68 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 11a6693:	83 f8 fe             	cmp    $0xfffffffe,%eax
 11a6696:	0f 84 a8 02 00 00    	je     11a6944 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x2c2f4>
 11a669c:	85 c0                	test   %eax,%eax
 11a669e:	0f 89 a0 02 00 00    	jns    11a6944 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x2c2f4>
 11a66a4:	c7 84 24 18 0a 00 00 	movl   $0x290,0xa18(%esp)
 11a66ab:	90 02 00 00 
 11a66af:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11a66b2:	8b 01                	mov    (%ecx),%eax
 11a66b4:	8b 40 0c             	mov    0xc(%eax),%eax
 11a66b7:	89 0c 24             	mov    %ecx,(%esp)
 11a66ba:	c7 44 24 04 49 8b 01 	movl   $0x18b49,0x4(%esp)
 11a66c1:	00 
 11a66c2:	ff d0                	call   *%eax
 11a66c4:	89 c6                	mov    %eax,%esi
 11a66c6:	89 04 24             	mov    %eax,(%esp)
 11a66c9:	c7 44 24 08 e1 7a 74 	movl   $0x3f747ae1,0x8(%esp)
 11a66d0:	3f 
 11a66d1:	c7 44 24 04 7b 14 ae 	movl   $0x47ae147b,0x4(%esp)
 11a66d8:	47 
 11a66d9:	e8 e2 55 68 00       	call   182bcc0 <YYRValue::operator+=(double)@plt>
 11a66de:	89 b4 24 a8 00 00 00 	mov    %esi,0xa8(%esp)
 11a66e5:	c7 84 24 18 0a 00 00 	movl   $0x291,0xa18(%esp)
 11a66ec:	91 02 00 00 
 11a66f0:	8b 84 24 cc 06 00 00 	mov    0x6cc(%esp),%eax
 11a66f7:	b9 46 00 00 00       	mov    $0x46,%ecx
 11a66fc:	0f a3 c1             	bt     %eax,%ecx
 11a66ff:	73 0f                	jae    11a6710 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x2c0c0>
 11a6701:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 11a6708:	89 04 24             	mov    %eax,(%esp)
 11a670b:	e8 b0 4f 68 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11a6710:	c7 84 24 c0 06 00 00 	movl   $0x0,0x6c0(%esp)
 11a6717:	00 00 00 00 
 11a671b:	c7 84 24 c8 06 00 00 	movl   $0x0,0x6c8(%esp)
 11a6722:	00 00 00 00 
 11a6726:	c7 84 24 cc 06 00 00 	movl   $0x5,0x6cc(%esp)
 11a672d:	05 00 00 00 
 11a6731:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11a6734:	8b 01                	mov    (%ecx),%eax
 11a6736:	8b 40 0c             	mov    0xc(%eax),%eax
 11a6739:	89 0c 24             	mov    %ecx,(%esp)
 11a673c:	c7 44 24 04 d5 95 01 	movl   $0x195d5,0x4(%esp) # verified field ID: xspeed
 11a6743:	00 
 11a6744:	ff d0                	call   *%eax
 11a6746:	89 c6                	mov    %eax,%esi
 11a6748:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11a674b:	8b 01                	mov    (%ecx),%eax
 11a674d:	8b 40 08             	mov    0x8(%eax),%eax
 11a6750:	89 0c 24             	mov    %ecx,(%esp)
 11a6eb6:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 11a6ebd:	89 44 24 08          	mov    %eax,0x8(%esp)
 11a6ec1:	8b 45 0c             	mov    0xc(%ebp),%eax
 11a6ec4:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a6ec8:	8b 45 08             	mov    0x8(%ebp),%eax
 11a6ecb:	89 04 24             	mov    %eax,(%esp)
 11a6ece:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
 11a6ed5:	00 
 11a6ed6:	e8 25 49 68 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 11a6edb:	89 c7                	mov    %eax,%edi
 11a6edd:	8b 45 08             	mov    0x8(%ebp),%eax
 11a6ee0:	89 04 24             	mov    %eax,(%esp)
 11a6ee3:	e8 a8 48 68 00       	call   182b790 <PushContextStack(YYObjectBase*)@plt>
 11a6ee8:	89 7c 24 04          	mov    %edi,0x4(%esp)
 11a6eec:	89 34 24             	mov    %esi,(%esp)
 11a6eef:	e8 6c 48 68 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 11a6ef4:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 11a6efb:	e8 a0 48 68 00       	call   182b7a0 <PopContextStack(int)@plt>
 11a6f00:	c7 84 24 18 0a 00 00 	movl   $0x29a,0xa18(%esp)
 11a6f07:	9a 02 00 00 
 11a6f0b:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11a6f0e:	8b 01                	mov    (%ecx),%eax
 11a6f10:	8b 40 0c             	mov    0xc(%eax),%eax
 11a6f13:	89 0c 24             	mov    %ecx,(%esp)
 11a6f16:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 11a6f1d:	00 
 11a6f1e:	ff d0                	call   *%eax
 11a6f20:	89 44 24 7c          	mov    %eax,0x7c(%esp)
 11a6f24:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 11a6f2b:	00 00 00 00 
 11a6f2f:	c7 84 24 24 0a 00 00 	movl   $0x3fc99999,0xa24(%esp)
 11a6f36:	99 99 c9 3f 
 11a6f3a:	c7 84 24 20 0a 00 00 	movl   $0x9999999a,0xa20(%esp)
 11a6f41:	9a 99 99 99 
 11a6f45:	8b 44 24 24          	mov    0x24(%esp),%eax
 11a6f49:	f2 0f 10 00          	movsd  (%eax),%xmm0
 11a6f4d:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 11a6f53:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 11a6f5a:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a6f5e:	8b 44 24 7c          	mov    0x7c(%esp),%eax
 11a6f62:	89 04 24             	mov    %eax,(%esp)
 11a6f65:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
 11a6f6c:	00 
 11a6f6d:	e8 4e 48 68 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 11a6f72:	83 f8 fe             	cmp    $0xfffffffe,%eax
 11a6f75:	0f 84 ae fa ff ff    	je     11a6a29 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x2c3d9>
 11a6f7b:	85 c0                	test   %eax,%eax
 11a6f7d:	0f 89 a6 fa ff ff    	jns    11a6a29 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x2c3d9>
 11a6f83:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11a6f86:	8b 01                	mov    (%ecx),%eax
 11a6f88:	8b 40 0c             	mov    0xc(%eax),%eax
 11a6f8b:	89 0c 24             	mov    %ecx,(%esp)
 11a6f8e:	c7 44 24 04 be 95 01 	movl   $0x195be,0x4(%esp) # verified field ID: wheel_spin
 11a6f95:	00 
 11a6f96:	ff d0                	call   *%eax
 11a6f98:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11a6f9b:	8b 01                	mov    (%ecx),%eax
 11a6f9d:	8b 40 0c             	mov    0xc(%eax),%eax
 11a6fa0:	89 0c 24             	mov    %ecx,(%esp)
 11a6fa3:	c7 44 24 04 49 8b 01 	movl   $0x18b49,0x4(%esp)
 11a6faa:	00 
 11a6fab:	ff d0                	call   *%eax
 11a6fad:	89 84 24 a8 00 00 00 	mov    %eax,0xa8(%esp)
 11a6fb4:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 11a6fbb:	00 00 00 00 
 11a6fbf:	c7 84 24 24 0a 00 00 	movl   $0x3fe00000,0xa24(%esp)
 11a6fc6:	00 00 e0 3f 
 11a6fca:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 11a6fd1:	00 00 00 00 
 11a6fd5:	8b 44 24 24          	mov    0x24(%esp),%eax
 11a6fd9:	f2 0f 10 00          	movsd  (%eax),%xmm0
 11a6fdd:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 11a6fe3:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 11a6fea:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a6fee:	8b 84 24 a8 00 00 00 	mov    0xa8(%esp),%eax
 11a6ff5:	89 04 24             	mov    %eax,(%esp)
 11a6ff8:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
 11a6fff:	00 
 11a7000:	e8 bb 47 68 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 11a7005:	85 c0                	test   %eax,%eax
 11a7007:	0f 8e 1c fa ff ff    	jle    11a6a29 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x2c3d9>
 11a700d:	c7 84 24 18 0a 00 00 	movl   $0x29c,0xa18(%esp)
 11a7014:	9c 02 00 00 
 11a7018:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11a701b:	8b 01                	mov    (%ecx),%eax
 11a701d:	8b 40 0c             	mov    0xc(%eax),%eax
 11a7020:	89 0c 24             	mov    %ecx,(%esp)
 11a7023:	c7 44 24 04 49 8b 01 	movl   $0x18b49,0x4(%esp)
 11a702a:	00 
 11a702b:	ff d0                	call   *%eax
 11a702d:	89 84 24 a8 00 00 00 	mov    %eax,0xa8(%esp)
 11a7034:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 11a703b:	00 00 00 00 
 11a703f:	c7 84 24 24 0a 00 00 	movl   $0x3f747ae1,0xa24(%esp)
 11a7046:	e1 7a 74 3f 
 11a704a:	c7 84 24 20 0a 00 00 	movl   $0x47ae147b,0xa20(%esp)
 11a7051:	7b 14 ae 47 
 11a7055:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 11a705c:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a7060:	8b 84 24 a8 00 00 00 	mov    0xa8(%esp),%eax
 11a7067:	89 04 24             	mov    %eax,(%esp)
 11a706a:	e8 c1 49 68 00       	call   182ba30 <YYRValue::operator-=(YYRValue const&)@plt>
 11a706f:	8b 84 24 2c 0a 00 00 	mov    0xa2c(%esp),%eax
 11a7076:	b9 46 00 00 00       	mov    $0x46,%ecx
 11a707b:	0f a3 c1             	bt     %eax,%ecx
 11a707e:	0f 83 a5 f9 ff ff    	jae    11a6a29 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x2c3d9>
 11a7084:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 11a708b:	89 04 24             	mov    %eax,(%esp)
 11a708e:	e8 2d 46 68 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11a7f5a:	c7 44 24 04 ba 90 01 	movl   $0x190ba,0x4(%esp) # verified field ID: RPM
 11a7f61:	00 
 11a7f62:	ff d0                	call   *%eax
 11a7f64:	89 44 24 48          	mov    %eax,0x48(%esp)
 11a7f68:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11a7f6b:	8b 01                	mov    (%ecx),%eax
 11a7f6d:	8b 40 0c             	mov    0xc(%eax),%eax
 11a7f70:	89 0c 24             	mov    %ecx,(%esp)
 11a7f73:	c7 44 24 04 a2 8d 01 	movl   $0x18da2,0x4(%esp)
 11a7f7a:	00 
 11a7f7b:	ff d0                	call   *%eax
 11a7f7d:	89 44 24 50          	mov    %eax,0x50(%esp)
 11a7f81:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11a7f84:	8b 01                	mov    (%ecx),%eax
 11a7f86:	8b 40 0c             	mov    0xc(%eax),%eax
 11a7f89:	89 0c 24             	mov    %ecx,(%esp)
 11a7f8c:	c7 44 24 04 e7 92 01 	movl   $0x192e7,0x4(%esp)
 11a7f93:	00 
 11a7f94:	ff d0                	call   *%eax
 11a7f96:	89 c7                	mov    %eax,%edi
 11a7f98:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11a7f9b:	8b 01                	mov    (%ecx),%eax
 11a7f9d:	8b 40 0c             	mov    0xc(%eax),%eax
 11a7fa0:	89 0c 24             	mov    %ecx,(%esp)
 11a7fa3:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 11a7faa:	00 
 11a7fab:	ff d0                	call   *%eax
 11a7fad:	89 84 24 e0 00 00 00 	mov    %eax,0xe0(%esp)
 11a7fb4:	8b 44 24 2c          	mov    0x2c(%esp),%eax
 11a7fb8:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a7fbc:	8d b4 24 00 06 00 00 	lea    0x600(%esp),%esi
 11a7fc3:	89 34 24             	mov    %esi,(%esp)
 11a7fc6:	c7 44 24 0c 00 70 97 	movl   $0x40977000,0xc(%esp)
 11a7fcd:	40 
 11a7fce:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 11a7fd5:	00 
 11a7fd6:	e8 f5 39 68 00       	call   182b9d0 <operator/(YYRValue const&, double)@plt>
 11a7fdb:	83 ec 04             	sub    $0x4,%esp
 11a7fde:	89 74 24 04          	mov    %esi,0x4(%esp)
 11a7fe2:	8d b4 24 20 0a 00 00 	lea    0xa20(%esp),%esi
 11a7fe9:	89 34 24             	mov    %esi,(%esp)
 11a7fec:	c7 44 24 0c 00 00 e0 	movl   $0x3fe00000,0xc(%esp)
 11a7ff3:	3f 
 11a7ff4:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 11a7ffb:	00 
 11a7ffc:	e8 ef 39 68 00       	call   182b9f0 <operator*(YYRValue const&, double)@plt>
 11a8001:	83 ec 04             	sub    $0x4,%esp
 11a8004:	89 74 24 04          	mov    %esi,0x4(%esp)
 11a8008:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 11a800f:	89 04 24             	mov    %eax,(%esp)
 11a8012:	e8 49 37 68 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 11a8017:	8b 84 24 2c 0a 00 00 	mov    0xa2c(%esp),%eax
 11a801e:	be 46 00 00 00       	mov    $0x46,%esi
 11a8023:	0f a3 c6             	bt     %eax,%esi
 11a8026:	73 0f                	jae    11a8037 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x2d9e7>
 11a8028:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 11a802f:	89 04 24             	mov    %eax,(%esp)
 11a8032:	e8 89 36 68 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11a8037:	8b 84 24 0c 06 00 00 	mov    0x60c(%esp),%eax
 11a803e:	0f a3 c6             	bt     %eax,%esi
 11a8041:	73 0f                	jae    11a8052 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x2da02>
 11a8043:	8d 84 24 00 06 00 00 	lea    0x600(%esp),%eax
 11a804a:	89 04 24             	mov    %eax,(%esp)
 11a804d:	e8 6e 36 68 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11a8052:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 11a8059:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 11a8060:	8b 44 24 44          	mov    0x44(%esp),%eax
 11a8064:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a8068:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 11a806f:	89 04 24             	mov    %eax,(%esp)
 11a8072:	e8 f9 36 68 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 11a8077:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 11a807e:	89 84 24 fc 0a 00 00 	mov    %eax,0xafc(%esp)
 11a8085:	8b 84 24 e8 00 00 00 	mov    0xe8(%esp),%eax
 11a808c:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a8090:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 11a8097:	89 04 24             	mov    %eax,(%esp)
 11a809a:	e8 d1 36 68 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 11a809f:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 11a80a6:	89 84 24 00 0b 00 00 	mov    %eax,0xb00(%esp)
 11a80ad:	89 7c 24 08          	mov    %edi,0x8(%esp)
 11a80b1:	8b 44 24 50          	mov    0x50(%esp),%eax
 11a80b5:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a80b9:	8d b4 24 d0 05 00 00 	lea    0x5d0(%esp),%esi
 11a80c0:	89 34 24             	mov    %esi,(%esp)
 11a80c3:	e8 98 37 68 00       	call   182b860 <operator+(YYRValue const&, YYRValue const&)@plt>
 11a80c8:	83 ec 04             	sub    $0x4,%esp
 11a80cb:	89 74 24 04          	mov    %esi,0x4(%esp)
 11a80cf:	8d b4 24 e0 05 00 00 	lea    0x5e0(%esp),%esi
 11a80d6:	89 34 24             	mov    %esi,(%esp)
 11a80d9:	c7 44 24 0c 00 00 e0 	movl   $0x3fe00000,0xc(%esp)
 11a80e0:	3f 
 11a80e1:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 11a80e8:	00 
 11a80e9:	e8 02 39 68 00       	call   182b9f0 <operator*(YYRValue const&, double)@plt>
 11a80ee:	83 ec 04             	sub    $0x4,%esp
 11a80f1:	89 74 24 04          	mov    %esi,0x4(%esp)
 11a80f5:	8d b4 24 f0 05 00 00 	lea    0x5f0(%esp),%esi
 11a80fc:	89 34 24             	mov    %esi,(%esp)
 11a80ff:	c7 44 24 08 50 00 00 	movl   $0x50,0x8(%esp)
 11a8106:	00 
 11a8107:	e8 04 39 68 00       	call   182ba10 <operator-(YYRValue const&, int)@plt>
 11a810c:	83 ec 04             	sub    $0x4,%esp
 11a810f:	89 74 24 04          	mov    %esi,0x4(%esp)
 11a8113:	8d b4 24 00 06 00 00 	lea    0x600(%esp),%esi
 11a811a:	89 34 24             	mov    %esi,(%esp)
 11a811d:	c7 44 24 0c 06 f0 46 	movl   $0x3f46f006,0xc(%esp)
 11a8124:	3f 
 11a8125:	c7 44 24 08 c7 ba b8 	movl   $0x8db8bac7,0x8(%esp)
 11a86eb:	8d 84 24 d0 05 00 00 	lea    0x5d0(%esp),%eax
 11a86f2:	89 04 24             	mov    %eax,(%esp)
 11a86f5:	e8 c6 2f 68 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11a86fa:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 11a8701:	e8 9a 30 68 00       	call   182b7a0 <PopContextStack(int)@plt>
 11a8706:	c7 84 24 18 0a 00 00 	movl   $0x39e,0xa18(%esp)
 11a870d:	9e 03 00 00 
 11a8711:	8b 84 24 cc 06 00 00 	mov    0x6cc(%esp),%eax
 11a8718:	b9 46 00 00 00       	mov    $0x46,%ecx
 11a871d:	0f a3 c1             	bt     %eax,%ecx
 11a8720:	73 0f                	jae    11a8731 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x2e0e1>
 11a8722:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 11a8729:	89 04 24             	mov    %eax,(%esp)
 11a872c:	e8 8f 2f 68 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11a8731:	c7 84 24 c0 06 00 00 	movl   $0x0,0x6c0(%esp)
 11a8738:	00 00 00 00 
 11a873c:	c7 84 24 c8 06 00 00 	movl   $0x0,0x6c8(%esp)
 11a8743:	00 00 00 00 
 11a8747:	c7 84 24 cc 06 00 00 	movl   $0x5,0x6cc(%esp)
 11a874e:	05 00 00 00 
 11a8752:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11a8755:	8b 01                	mov    (%ecx),%eax
 11a8757:	8b 40 0c             	mov    0xc(%eax),%eax
 11a875a:	89 0c 24             	mov    %ecx,(%esp)
 11a875d:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 11a8764:	00 
 11a8765:	ff d0                	call   *%eax
 11a8767:	89 44 24 7c          	mov    %eax,0x7c(%esp)
 11a876b:	8b 44 24 7c          	mov    0x7c(%esp),%eax
 11a876f:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a8773:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 11a877a:	89 04 24             	mov    %eax,(%esp)
 11a877d:	e8 de 2f 68 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 11a8782:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 11a8789:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 11a8790:	8b 44 24 44          	mov    0x44(%esp),%eax
 11a8794:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a8798:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 11a879f:	89 04 24             	mov    %eax,(%esp)
 11a87a2:	e8 c9 2f 68 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 11a87a7:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 11a87ae:	89 84 24 fc 0a 00 00 	mov    %eax,0xafc(%esp)
 11a87b5:	8b 84 24 a0 00 00 00 	mov    0xa0(%esp),%eax
 11a87bc:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a87c0:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 11a87c7:	89 04 24             	mov    %eax,(%esp)
 11a87ca:	e8 a1 2f 68 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 11a87cf:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 11a87d6:	89 84 24 00 0b 00 00 	mov    %eax,0xb00(%esp)
 11a87dd:	8b 44 24 60          	mov    0x60(%esp),%eax
 11a87e1:	8b 40 04             	mov    0x4(%eax),%eax
 11a87e4:	8d 8c 24 f8 0a 00 00 	lea    0xaf8(%esp),%ecx
 11a87eb:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 11a87ef:	89 44 24 10          	mov    %eax,0x10(%esp)
 11a87f3:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 11a87fa:	89 44 24 08          	mov    %eax,0x8(%esp)
 11a87fe:	8b 45 0c             	mov    0xc(%ebp),%eax
 11a8801:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a8805:	8b 45 08             	mov    0x8(%ebp),%eax
 11a8808:	89 04 24             	mov    %eax,(%esp)
 11a880b:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
 11a8812:	00 
 11a8813:	e8 e8 2f 68 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 11a8818:	89 c6                	mov    %eax,%esi
 11a881a:	8b 45 08             	mov    0x8(%ebp),%eax
 11a881d:	89 04 24             	mov    %eax,(%esp)
 11a8820:	e8 6b 2f 68 00       	call   182b790 <PushContextStack(YYObjectBase*)@plt>
 11a8825:	89 74 24 04          	mov    %esi,0x4(%esp)
 11a8829:	8b 44 24 7c          	mov    0x7c(%esp),%eax
 11a882d:	89 04 24             	mov    %eax,(%esp)
 11a8830:	e8 2b 2f 68 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 11a8835:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 11a883c:	e8 5f 2f 68 00       	call   182b7a0 <PopContextStack(int)@plt>
 11a8841:	c7 84 24 18 0a 00 00 	movl   $0x39f,0xa18(%esp)
 11a8848:	9f 03 00 00 
 11a884c:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11a884f:	8b 01                	mov    (%ecx),%eax
 11a8851:	8b 40 0c             	mov    0xc(%eax),%eax
 11a8854:	89 0c 24             	mov    %ecx,(%esp)
 11a8857:	c7 44 24 04 d5 95 01 	movl   $0x195d5,0x4(%esp) # verified field ID: xspeed
 11a885e:	00 
 11a885f:	ff d0                	call   *%eax
 11a8861:	89 44 24 50          	mov    %eax,0x50(%esp)
 11a8865:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 11a886c:	00 00 00 00 
 11a8870:	c7 84 24 24 0a 00 00 	movl   $0x40280000,0xa24(%esp)
 11a8877:	00 00 28 40 
 11a887b:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 11a8882:	00 00 00 00 
 11a8886:	8b 44 24 24          	mov    0x24(%esp),%eax
 11a888a:	f2 0f 10 00          	movsd  (%eax),%xmm0
 11a888e:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 11a8894:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 11a889b:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a889f:	8b 44 24 50          	mov    0x50(%esp),%eax
 11a88a3:	89 04 24             	mov    %eax,(%esp)
 11a88a6:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
 11a88ad:	00 
 11a88ae:	e8 0d 2f 68 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 11a88b3:	83 f8 fe             	cmp    $0xfffffffe,%eax
 11a88b6:	0f 84 c9 6e fe ff    	je     118f785 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x15135>
 11a88bc:	85 c0                	test   %eax,%eax
 11a88be:	0f 89 c1 6e fe ff    	jns    118f785 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x15135>
 11a88c4:	c7 84 24 18 0a 00 00 	movl   $0x3a1,0xa18(%esp)
 11a88cb:	a1 03 00 00 
 11a88cf:	8b 84 24 cc 06 00 00 	mov    0x6cc(%esp),%eax
 11a88d6:	be 46 00 00 00       	mov    $0x46,%esi
 11a88db:	0f a3 c6             	bt     %eax,%esi
 11a88de:	73 0f                	jae    11a88ef <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x2e29f>
 11a9711:	c7 44 24 04 ba 90 01 	movl   $0x190ba,0x4(%esp) # verified field ID: RPM
 11a9718:	00 
 11a9719:	ff d0                	call   *%eax
 11a971b:	89 44 24 50          	mov    %eax,0x50(%esp)
 11a971f:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11a9722:	8b 01                	mov    (%ecx),%eax
 11a9724:	8b 40 0c             	mov    0xc(%eax),%eax
 11a9727:	89 0c 24             	mov    %ecx,(%esp)
 11a972a:	c7 44 24 04 a2 8d 01 	movl   $0x18da2,0x4(%esp)
 11a9731:	00 
 11a9732:	ff d0                	call   *%eax
 11a9734:	89 44 24 48          	mov    %eax,0x48(%esp)
 11a9738:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11a973b:	8b 01                	mov    (%ecx),%eax
 11a973d:	8b 40 0c             	mov    0xc(%eax),%eax
 11a9740:	89 0c 24             	mov    %ecx,(%esp)
 11a9743:	c7 44 24 04 e7 92 01 	movl   $0x192e7,0x4(%esp)
 11a974a:	00 
 11a974b:	ff d0                	call   *%eax
 11a974d:	89 c7                	mov    %eax,%edi
 11a974f:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11a9752:	8b 01                	mov    (%ecx),%eax
 11a9754:	8b 40 0c             	mov    0xc(%eax),%eax
 11a9757:	89 0c 24             	mov    %ecx,(%esp)
 11a975a:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 11a9761:	00 
 11a9762:	ff d0                	call   *%eax
 11a9764:	89 44 24 7c          	mov    %eax,0x7c(%esp)
 11a9768:	8b 44 24 2c          	mov    0x2c(%esp),%eax
 11a976c:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a9770:	8d b4 24 00 06 00 00 	lea    0x600(%esp),%esi
 11a9777:	89 34 24             	mov    %esi,(%esp)
 11a977a:	c7 44 24 0c 00 70 97 	movl   $0x40977000,0xc(%esp)
 11a9781:	40 
 11a9782:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 11a9789:	00 
 11a978a:	e8 41 22 68 00       	call   182b9d0 <operator/(YYRValue const&, double)@plt>
 11a978f:	83 ec 04             	sub    $0x4,%esp
 11a9792:	89 74 24 04          	mov    %esi,0x4(%esp)
 11a9796:	8d b4 24 20 0a 00 00 	lea    0xa20(%esp),%esi
 11a979d:	89 34 24             	mov    %esi,(%esp)
 11a97a0:	c7 44 24 0c 00 00 e0 	movl   $0x3fe00000,0xc(%esp)
 11a97a7:	3f 
 11a97a8:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 11a97af:	00 
 11a97b0:	e8 3b 22 68 00       	call   182b9f0 <operator*(YYRValue const&, double)@plt>
 11a97b5:	83 ec 04             	sub    $0x4,%esp
 11a97b8:	89 74 24 04          	mov    %esi,0x4(%esp)
 11a97bc:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 11a97c3:	89 04 24             	mov    %eax,(%esp)
 11a97c6:	e8 95 1f 68 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 11a97cb:	8b 84 24 2c 0a 00 00 	mov    0xa2c(%esp),%eax
 11a97d2:	be 46 00 00 00       	mov    $0x46,%esi
 11a97d7:	0f a3 c6             	bt     %eax,%esi
 11a97da:	73 0f                	jae    11a97eb <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x2f19b>
 11a97dc:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 11a97e3:	89 04 24             	mov    %eax,(%esp)
 11a97e6:	e8 d5 1e 68 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11a97eb:	8b 84 24 0c 06 00 00 	mov    0x60c(%esp),%eax
 11a97f2:	0f a3 c6             	bt     %eax,%esi
 11a97f5:	73 0f                	jae    11a9806 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x2f1b6>
 11a97f7:	8d 84 24 00 06 00 00 	lea    0x600(%esp),%eax
 11a97fe:	89 04 24             	mov    %eax,(%esp)
 11a9801:	e8 ba 1e 68 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11a9806:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 11a980d:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 11a9814:	8b 44 24 44          	mov    0x44(%esp),%eax
 11a9818:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a981c:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 11a9823:	89 04 24             	mov    %eax,(%esp)
 11a9826:	e8 45 1f 68 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 11a982b:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 11a9832:	89 84 24 fc 0a 00 00 	mov    %eax,0xafc(%esp)
 11a9839:	8b 84 24 e8 00 00 00 	mov    0xe8(%esp),%eax
 11a9840:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a9844:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 11a984b:	89 04 24             	mov    %eax,(%esp)
 11a984e:	e8 1d 1f 68 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 11a9853:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 11a985a:	89 84 24 00 0b 00 00 	mov    %eax,0xb00(%esp)
 11a9861:	89 7c 24 08          	mov    %edi,0x8(%esp)
 11a9865:	8b 44 24 48          	mov    0x48(%esp),%eax
 11a9869:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a986d:	8d b4 24 d0 05 00 00 	lea    0x5d0(%esp),%esi
 11a9874:	89 34 24             	mov    %esi,(%esp)
 11a9877:	e8 e4 1f 68 00       	call   182b860 <operator+(YYRValue const&, YYRValue const&)@plt>
 11a987c:	83 ec 04             	sub    $0x4,%esp
 11a987f:	89 74 24 04          	mov    %esi,0x4(%esp)
 11a9883:	8d b4 24 e0 05 00 00 	lea    0x5e0(%esp),%esi
 11a988a:	89 34 24             	mov    %esi,(%esp)
 11a988d:	c7 44 24 08 02 00 00 	movl   $0x2,0x8(%esp)
 11a9894:	00 
 11a9895:	e8 46 23 68 00       	call   182bbe0 <operator*(YYRValue const&, int)@plt>
 11a989a:	83 ec 04             	sub    $0x4,%esp
 11a989d:	89 74 24 04          	mov    %esi,0x4(%esp)
 11a98a1:	8d b4 24 f0 05 00 00 	lea    0x5f0(%esp),%esi
 11a98a8:	89 34 24             	mov    %esi,(%esp)
 11a98ab:	c7 44 24 08 50 00 00 	movl   $0x50,0x8(%esp)
 11a98b2:	00 
 11a98b3:	e8 58 21 68 00       	call   182ba10 <operator-(YYRValue const&, int)@plt>
 11a98b8:	83 ec 04             	sub    $0x4,%esp
 11a98bb:	89 74 24 04          	mov    %esi,0x4(%esp)
 11a98bf:	8d b4 24 00 06 00 00 	lea    0x600(%esp),%esi
 11a98c6:	89 34 24             	mov    %esi,(%esp)
 11a98c9:	c7 44 24 0c 06 f0 46 	movl   $0x3f46f006,0xc(%esp)
 11a98d0:	3f 
 11a98d1:	c7 44 24 08 c7 ba b8 	movl   $0x8db8bac7,0x8(%esp)
 11a98d8:	8d 
 11a98d9:	e8 12 21 68 00       	call   182b9f0 <operator*(YYRValue const&, double)@plt>
 11a9d71:	8d 84 24 d0 05 00 00 	lea    0x5d0(%esp),%eax
 11a9d78:	89 04 24             	mov    %eax,(%esp)
 11a9d7b:	e8 40 19 68 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11a9d80:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 11a9d87:	e8 14 1a 68 00       	call   182b7a0 <PopContextStack(int)@plt>
 11a9d8c:	c7 84 24 18 0a 00 00 	movl   $0x3a9,0xa18(%esp)
 11a9d93:	a9 03 00 00 
 11a9d97:	8b 84 24 cc 06 00 00 	mov    0x6cc(%esp),%eax
 11a9d9e:	b9 46 00 00 00       	mov    $0x46,%ecx
 11a9da3:	0f a3 c1             	bt     %eax,%ecx
 11a9da6:	73 0f                	jae    11a9db7 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x2f767>
 11a9da8:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 11a9daf:	89 04 24             	mov    %eax,(%esp)
 11a9db2:	e8 09 19 68 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11a9db7:	c7 84 24 c0 06 00 00 	movl   $0x0,0x6c0(%esp)
 11a9dbe:	00 00 00 00 
 11a9dc2:	c7 84 24 c8 06 00 00 	movl   $0x0,0x6c8(%esp)
 11a9dc9:	00 00 00 00 
 11a9dcd:	c7 84 24 cc 06 00 00 	movl   $0x5,0x6cc(%esp)
 11a9dd4:	05 00 00 00 
 11a9dd8:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11a9ddb:	8b 01                	mov    (%ecx),%eax
 11a9ddd:	8b 40 0c             	mov    0xc(%eax),%eax
 11a9de0:	89 0c 24             	mov    %ecx,(%esp)
 11a9de3:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 11a9dea:	00 
 11a9deb:	ff d0                	call   *%eax
 11a9ded:	89 44 24 7c          	mov    %eax,0x7c(%esp)
 11a9df1:	8b 44 24 7c          	mov    0x7c(%esp),%eax
 11a9df5:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a9df9:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 11a9e00:	89 04 24             	mov    %eax,(%esp)
 11a9e03:	e8 58 19 68 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 11a9e08:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 11a9e0f:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 11a9e16:	8b 44 24 44          	mov    0x44(%esp),%eax
 11a9e1a:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a9e1e:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 11a9e25:	89 04 24             	mov    %eax,(%esp)
 11a9e28:	e8 43 19 68 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 11a9e2d:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 11a9e34:	89 84 24 fc 0a 00 00 	mov    %eax,0xafc(%esp)
 11a9e3b:	8b 84 24 a0 00 00 00 	mov    0xa0(%esp),%eax
 11a9e42:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a9e46:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 11a9e4d:	89 04 24             	mov    %eax,(%esp)
 11a9e50:	e8 1b 19 68 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 11a9e55:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 11a9e5c:	89 84 24 00 0b 00 00 	mov    %eax,0xb00(%esp)
 11a9e63:	8b 44 24 60          	mov    0x60(%esp),%eax
 11a9e67:	8b 40 04             	mov    0x4(%eax),%eax
 11a9e6a:	8d 8c 24 f8 0a 00 00 	lea    0xaf8(%esp),%ecx
 11a9e71:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 11a9e75:	89 44 24 10          	mov    %eax,0x10(%esp)
 11a9e79:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 11a9e80:	89 44 24 08          	mov    %eax,0x8(%esp)
 11a9e84:	8b 45 0c             	mov    0xc(%ebp),%eax
 11a9e87:	89 44 24 04          	mov    %eax,0x4(%esp)
 11a9e8b:	8b 45 08             	mov    0x8(%ebp),%eax
 11a9e8e:	89 04 24             	mov    %eax,(%esp)
 11a9e91:	c7 44 24 0c 03 00 00 	movl   $0x3,0xc(%esp)
 11a9e98:	00 
 11a9e99:	e8 62 19 68 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 11a9e9e:	89 c6                	mov    %eax,%esi
 11a9ea0:	8b 45 08             	mov    0x8(%ebp),%eax
 11a9ea3:	89 04 24             	mov    %eax,(%esp)
 11a9ea6:	e8 e5 18 68 00       	call   182b790 <PushContextStack(YYObjectBase*)@plt>
 11a9eab:	89 74 24 04          	mov    %esi,0x4(%esp)
 11a9eaf:	8b 44 24 7c          	mov    0x7c(%esp),%eax
 11a9eb3:	89 04 24             	mov    %eax,(%esp)
 11a9eb6:	e8 a5 18 68 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 11a9ebb:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 11a9ec2:	e8 d9 18 68 00       	call   182b7a0 <PopContextStack(int)@plt>
 11a9ec7:	c7 84 24 18 0a 00 00 	movl   $0x3aa,0xa18(%esp)
 11a9ece:	aa 03 00 00 
 11a9ed2:	8b 84 24 cc 06 00 00 	mov    0x6cc(%esp),%eax
 11a9ed9:	be 46 00 00 00       	mov    $0x46,%esi
 11a9ede:	0f a3 c6             	bt     %eax,%esi
 11a9ee1:	73 0f                	jae    11a9ef2 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x2f8a2>
 11a9ee3:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 11a9eea:	89 04 24             	mov    %eax,(%esp)
 11a9eed:	e8 ce 17 68 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11a9ef2:	c7 84 24 c0 06 00 00 	movl   $0x0,0x6c0(%esp)
 11a9ef9:	00 00 00 00 
 11a9efd:	c7 84 24 c8 06 00 00 	movl   $0x0,0x6c8(%esp)
 11a9f04:	00 00 00 00 
 11a9f08:	c7 84 24 cc 06 00 00 	movl   $0x5,0x6cc(%esp)
 11a9f0f:	05 00 00 00 
 11a9f13:	8b 84 24 bc 06 00 00 	mov    0x6bc(%esp),%eax
 11a9f1a:	0f a3 c6             	bt     %eax,%esi
 11a9f1d:	73 0f                	jae    11a9f2e <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x2f8de>
 11a9f1f:	8d 84 24 b0 06 00 00 	lea    0x6b0(%esp),%eax
 11a9f26:	89 04 24             	mov    %eax,(%esp)
 11a9f29:	e8 92 17 68 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11a9f2e:	c7 84 24 b0 06 00 00 	movl   $0x0,0x6b0(%esp)
 11a9f35:	00 00 00 00 
 11a9f39:	c7 84 24 b8 06 00 00 	movl   $0x0,0x6b8(%esp)
 11a9f40:	00 00 00 00 
 11a9f44:	c7 84 24 bc 06 00 00 	movl   $0x5,0x6bc(%esp)
 11a9f4b:	05 00 00 00 
 11a9f4f:	8b 84 24 ac 06 00 00 	mov    0x6ac(%esp),%eax
 11a9f56:	b9 46 00 00 00       	mov    $0x46,%ecx
 11a9f5b:	0f a3 c1             	bt     %eax,%ecx
 11a9f5e:	73 0f                	jae    11a9f6f <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x2f91f>
 11a9f60:	8d 84 24 a0 06 00 00 	lea    0x6a0(%esp),%eax
 11a9f67:	89 04 24             	mov    %eax,(%esp)
 11a9f6a:	e8 51 17 68 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11a9f6f:	c7 84 24 a0 06 00 00 	movl   $0x0,0x6a0(%esp)
 11a9f76:	00 00 00 00 
 11d01e1:	c7 84 24 c8 06 00 00 	movl   $0x0,0x6c8(%esp)
 11d01e8:	00 00 00 00 
 11d01ec:	c7 84 24 cc 06 00 00 	movl   $0x5,0x6cc(%esp)
 11d01f3:	05 00 00 00 
 11d01f7:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11d01fa:	8b 01                	mov    (%ecx),%eax
 11d01fc:	8b 40 0c             	mov    0xc(%eax),%eax
 11d01ff:	89 0c 24             	mov    %ecx,(%esp)
 11d0202:	c7 44 24 04 d5 95 01 	movl   $0x195d5,0x4(%esp) # verified field ID: xspeed
 11d0209:	00 
 11d020a:	ff d0                	call   *%eax
 11d020c:	89 44 24 50          	mov    %eax,0x50(%esp)
 11d0210:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11d0213:	8b 01                	mov    (%ecx),%eax
 11d0215:	8b 40 0c             	mov    0xc(%eax),%eax
 11d0218:	89 0c 24             	mov    %ecx,(%esp)
 11d021b:	c7 44 24 04 49 8b 01 	movl   $0x18b49,0x4(%esp)
 11d0222:	00 
 11d0223:	ff d0                	call   *%eax
 11d0225:	89 84 24 a8 00 00 00 	mov    %eax,0xa8(%esp)
 11d022c:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11d022f:	8b 01                	mov    (%ecx),%eax
 11d0231:	8b 40 0c             	mov    0xc(%eax),%eax
 11d0234:	89 0c 24             	mov    %ecx,(%esp)
 11d0237:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 11d023e:	00 
 11d023f:	ff d0                	call   *%eax
 11d0241:	89 44 24 7c          	mov    %eax,0x7c(%esp)
 11d0245:	8b 84 24 24 01 00 00 	mov    0x124(%esp),%eax
 11d024c:	89 44 24 04          	mov    %eax,0x4(%esp)
 11d0250:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 11d0257:	89 04 24             	mov    %eax,(%esp)
 11d025a:	e8 01 b5 65 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 11d025f:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 11d0266:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 11d026d:	8b 83 34 d3 ff ff    	mov    -0x2ccc(%ebx),%eax
 11d0273:	89 44 24 04          	mov    %eax,0x4(%esp)
 11d0277:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 11d027e:	89 04 24             	mov    %eax,(%esp)
 11d0281:	e8 ea b4 65 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 11d0286:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 11d028d:	89 84 24 fc 0a 00 00 	mov    %eax,0xafc(%esp)
 11d0294:	8b 83 38 d3 ff ff    	mov    -0x2cc8(%ebx),%eax
 11d029a:	89 44 24 04          	mov    %eax,0x4(%esp)
 11d029e:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 11d02a5:	89 04 24             	mov    %eax,(%esp)
 11d02a8:	e8 c3 b4 65 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 11d02ad:	8d 84 24 58 0a 00 00 	lea    0xa58(%esp),%eax
 11d02b4:	89 84 24 00 0b 00 00 	mov    %eax,0xb00(%esp)
 11d02bb:	8b 44 24 44          	mov    0x44(%esp),%eax
 11d02bf:	89 44 24 04          	mov    %eax,0x4(%esp)
 11d02c3:	8d 84 24 68 0a 00 00 	lea    0xa68(%esp),%eax
 11d02ca:	89 04 24             	mov    %eax,(%esp)
 11d02cd:	e8 9e b4 65 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 11d02d2:	8d 84 24 68 0a 00 00 	lea    0xa68(%esp),%eax
 11d02d9:	89 84 24 04 0b 00 00 	mov    %eax,0xb04(%esp)
 11d02e0:	8b 84 24 a0 00 00 00 	mov    0xa0(%esp),%eax
 11d02e7:	89 44 24 04          	mov    %eax,0x4(%esp)
 11d02eb:	8d 84 24 78 0a 00 00 	lea    0xa78(%esp),%eax
 11d02f2:	89 04 24             	mov    %eax,(%esp)
 11d02f5:	e8 76 b4 65 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 11d02fa:	8d 84 24 78 0a 00 00 	lea    0xa78(%esp),%eax
 11d0301:	89 84 24 08 0b 00 00 	mov    %eax,0xb08(%esp)
 11d0308:	8b 83 a4 d1 ff ff    	mov    -0x2e5c(%ebx),%eax
 11d030e:	8b 40 04             	mov    0x4(%eax),%eax
 11d0311:	8d 8c 24 f8 0a 00 00 	lea    0xaf8(%esp),%ecx
 11d0318:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 11d031c:	89 44 24 10          	mov    %eax,0x10(%esp)
 11d0320:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 11d0327:	89 44 24 08          	mov    %eax,0x8(%esp)
 11d032b:	8b 45 0c             	mov    0xc(%ebp),%eax
 11d032e:	89 44 24 04          	mov    %eax,0x4(%esp)
 11d0332:	8b 45 08             	mov    0x8(%ebp),%eax
 11d0335:	89 04 24             	mov    %eax,(%esp)
 11d0338:	c7 44 24 0c 05 00 00 	movl   $0x5,0xc(%esp)
 11d033f:	00 
 11d0340:	e8 bb b4 65 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 11d0345:	e9 4a 01 00 00       	jmp    11d0494 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x55e44>
 11d034a:	c7 84 24 18 0a 00 00 	movl   $0x1769,0xa18(%esp)
 11d0351:	69 17 00 00 
 11d0355:	8b 84 24 cc 06 00 00 	mov    0x6cc(%esp),%eax
 11d035c:	b9 46 00 00 00       	mov    $0x46,%ecx
 11d0361:	0f a3 c1             	bt     %eax,%ecx
 11d0364:	73 0f                	jae    11d0375 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x55d25>
 11d0366:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 11d036d:	89 04 24             	mov    %eax,(%esp)
 11d0370:	e8 4b b3 65 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11d0375:	c7 84 24 c0 06 00 00 	movl   $0x0,0x6c0(%esp)
 11d037c:	00 00 00 00 
 11d0380:	c7 84 24 c8 06 00 00 	movl   $0x0,0x6c8(%esp)
 11d0387:	00 00 00 00 
 11d038b:	c7 84 24 cc 06 00 00 	movl   $0x5,0x6cc(%esp)
 11d0392:	05 00 00 00 
 11d0396:	8b 84 24 24 01 00 00 	mov    0x124(%esp),%eax
 11d039d:	89 44 24 04          	mov    %eax,0x4(%esp)
 11d03a1:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 11d03a8:	89 04 24             	mov    %eax,(%esp)
 11d03ab:	e8 b0 b3 65 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 11d03b0:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 11d03b7:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 11d03be:	8b 44 24 44          	mov    0x44(%esp),%eax
 11d03c2:	89 44 24 04          	mov    %eax,0x4(%esp)
 11d03c6:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 11d03cd:	89 04 24             	mov    %eax,(%esp)
 11d03d0:	e8 9b b3 65 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 11d03d5:	8d 84 24 48 0a 00 00 	lea    0xa48(%esp),%eax
 11d03dc:	89 84 24 fc 0a 00 00 	mov    %eax,0xafc(%esp)
 11d03e3:	8b 83 3c d3 ff ff    	mov    -0x2cc4(%ebx),%eax
 11d03e9:	89 44 24 04          	mov    %eax,0x4(%esp)
 11d0aac:	73 0f                	jae    11d0abd <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x5646d>
 11d0aae:	8d 84 24 c0 05 00 00 	lea    0x5c0(%esp),%eax
 11d0ab5:	89 04 24             	mov    %eax,(%esp)
 11d0ab8:	e8 03 ac 65 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11d0abd:	85 f6                	test   %esi,%esi
 11d0abf:	0f 8e 8b 02 00 00    	jle    11d0d50 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x56700>
 11d0ac5:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11d0ac8:	8b 01                	mov    (%ecx),%eax
 11d0aca:	8b 40 0c             	mov    0xc(%eax),%eax
 11d0acd:	89 0c 24             	mov    %ecx,(%esp)
 11d0ad0:	c7 44 24 04 d5 95 01 	movl   $0x195d5,0x4(%esp) # verified field ID: xspeed
 11d0ad7:	00 
 11d0ad8:	ff d0                	call   *%eax
 11d0ada:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11d0add:	8b 01                	mov    (%ecx),%eax
 11d0adf:	8b 40 0c             	mov    0xc(%eax),%eax
 11d0ae2:	89 0c 24             	mov    %ecx,(%esp)
 11d0ae5:	c7 44 24 04 49 8b 01 	movl   $0x18b49,0x4(%esp)
 11d0aec:	00 
 11d0aed:	ff d0                	call   *%eax
 11d0aef:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11d0af2:	8b 01                	mov    (%ecx),%eax
 11d0af4:	8b 40 0c             	mov    0xc(%eax),%eax
 11d0af7:	89 0c 24             	mov    %ecx,(%esp)
 11d0afa:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 11d0b01:	00 
 11d0b02:	ff d0                	call   *%eax
 11d0b04:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11d0b07:	8b 01                	mov    (%ecx),%eax
 11d0b09:	8b 40 0c             	mov    0xc(%eax),%eax
 11d0b0c:	89 0c 24             	mov    %ecx,(%esp)
 11d0b0f:	c7 44 24 04 9d 8a 01 	movl   $0x18a9d,0x4(%esp)
 11d0b16:	00 
 11d0b17:	ff d0                	call   *%eax
 11d0b19:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 11d0b20:	00 00 00 00 
 11d0b24:	c7 84 24 24 0a 00 00 	movl   $0x40140000,0xa24(%esp)
 11d0b2b:	00 00 14 40 
 11d0b2f:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 11d0b36:	00 00 00 00 
 11d0b3a:	8b 4c 24 24          	mov    0x24(%esp),%ecx
 11d0b3e:	f2 0f 10 01          	movsd  (%ecx),%xmm0
 11d0b42:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 11d0b48:	8d 8c 24 20 0a 00 00 	lea    0xa20(%esp),%ecx
 11d0b4f:	89 4c 24 04          	mov    %ecx,0x4(%esp)
 11d0b53:	89 04 24             	mov    %eax,(%esp)
 11d0b56:	c7 44 24 10 01 00 00 	movl   $0x1,0x10(%esp)
 11d0b5d:	00 
 11d0b5e:	e8 5d ac 65 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 11d0b63:	85 c0                	test   %eax,%eax
 11d0b65:	0f 88 e5 01 00 00    	js     11d0d50 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x56700>
 11d0b6b:	8b 44 24 5c          	mov    0x5c(%esp),%eax
 11d0b6f:	8b 40 04             	mov    0x4(%eax),%eax
 11d0b72:	8d 8c 24 90 09 00 00 	lea    0x990(%esp),%ecx
 11d0b79:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
 11d0b7d:	89 44 24 04          	mov    %eax,0x4(%esp)
 11d0b81:	8b 45 08             	mov    0x8(%ebp),%eax
 11d0b84:	89 04 24             	mov    %eax,(%esp)
 11d0b87:	c7 44 24 08 00 00 00 	movl   $0x80000000,0x8(%esp)
 11d0b8e:	80 
 11d0b8f:	e8 fc ae 65 00       	call   182ba90 <Variable_GetBuiltIn_Direct(YYObjectBase*, int, int, RValue*)@plt>
 11d0b94:	c7 84 24 2c 0a 00 00 	movl   $0x0,0xa2c(%esp)
 11d0b9b:	00 00 00 00 
 11d0b9f:	c7 84 24 24 0a 00 00 	movl   $0x40200000,0xa24(%esp)
 11d0ba6:	00 00 20 40 
 11d0baa:	c7 84 24 20 0a 00 00 	movl   $0x0,0xa20(%esp)
 11d0bb1:	00 00 00 00 
 11d0bb5:	8b 44 24 24          	mov    0x24(%esp),%eax
 11d0bb9:	f2 0f 10 00          	movsd  (%eax),%xmm0
 11d0bbd:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%esp)
 11d0bc3:	8d 84 24 20 0a 00 00 	lea    0xa20(%esp),%eax
 11d0bca:	89 44 24 04          	mov    %eax,0x4(%esp)
 11d0bce:	8d 84 24 90 09 00 00 	lea    0x990(%esp),%eax
 11d0bd5:	89 04 24             	mov    %eax,(%esp)
 11d0bd8:	c7 44 24 10 00 00 00 	movl   $0x0,0x10(%esp)
 11d0bdf:	00 
 11d0be0:	e8 db ab 65 00       	call   182b7c0 <YYCompareVal(RValue const&, RValue const&, double, bool)@plt>
 11d0be5:	85 c0                	test   %eax,%eax
 11d0be7:	0f 84 63 01 00 00    	je     11d0d50 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x56700>
 11d0bed:	c7 84 24 18 0a 00 00 	movl   $0x1773,0xa18(%esp)
 11d0bf4:	73 17 00 00 
 11d0bf8:	8b 84 24 bc 06 00 00 	mov    0x6bc(%esp),%eax
 11d0bff:	be 46 00 00 00       	mov    $0x46,%esi
 11d0c04:	0f a3 c6             	bt     %eax,%esi
 11d0c07:	73 0f                	jae    11d0c18 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x565c8>
 11d0c09:	8d 84 24 b0 06 00 00 	lea    0x6b0(%esp),%eax
 11d0c10:	89 04 24             	mov    %eax,(%esp)
 11d0c13:	e8 a8 aa 65 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11d0c18:	c7 84 24 b0 06 00 00 	movl   $0x0,0x6b0(%esp)
 11d0c1f:	00 00 00 00 
 11d0c23:	c7 84 24 b8 06 00 00 	movl   $0x0,0x6b8(%esp)
 11d0c2a:	00 00 00 00 
 11d0c2e:	c7 84 24 bc 06 00 00 	movl   $0x5,0x6bc(%esp)
 11d0c35:	05 00 00 00 
 11d0c39:	8b 84 24 ac 06 00 00 	mov    0x6ac(%esp),%eax
 11d0c40:	0f a3 c6             	bt     %eax,%esi
 11d0c43:	73 0f                	jae    11d0c54 <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x56604>
 11d0c45:	8d 84 24 a0 06 00 00 	lea    0x6a0(%esp),%eax
 11d0c4c:	89 04 24             	mov    %eax,(%esp)
 11d0c4f:	e8 6c aa 65 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11d0c54:	c7 84 24 a0 06 00 00 	movl   $0x0,0x6a0(%esp)
 11d0c5b:	00 00 00 00 
 11d0c5f:	c7 84 24 a8 06 00 00 	movl   $0x0,0x6a8(%esp)
 11d0c66:	00 00 00 00 
 11d0c6a:	c7 84 24 ac 06 00 00 	movl   $0x5,0x6ac(%esp)
 11d0c71:	05 00 00 00 
 11d0c75:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11d0c78:	8b 01                	mov    (%ecx),%eax
 11d0c7a:	8b 40 0c             	mov    0xc(%eax),%eax
 11d0c7d:	89 0c 24             	mov    %ecx,(%esp)
 11d0c80:	c7 44 24 04 d5 95 01 	movl   $0x195d5,0x4(%esp) # verified field ID: xspeed
 11d0c87:	00 
 11d0c88:	ff d0                	call   *%eax
 11d0c8a:	89 c7                	mov    %eax,%edi
 11d0c8c:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11d0c8f:	8b 01                	mov    (%ecx),%eax
 11d0c91:	8b 40 0c             	mov    0xc(%eax),%eax
 11d0c94:	89 0c 24             	mov    %ecx,(%esp)
 11d0c97:	c7 44 24 04 49 8b 01 	movl   $0x18b49,0x4(%esp)
 11d0c9e:	00 
 11d0c9f:	ff d0                	call   *%eax
 11d0ca1:	89 c6                	mov    %eax,%esi
 11d0ca3:	8b 4d 08             	mov    0x8(%ebp),%ecx
 11d0ca6:	8b 01                	mov    (%ecx),%eax
 11d0ca8:	8b 40 0c             	mov    0xc(%eax),%eax
 11d0cab:	89 0c 24             	mov    %ecx,(%esp)
 11d0cae:	c7 44 24 04 38 8f 01 	movl   $0x18f38,0x4(%esp) # verified field ID: no_traction
 11d0cb5:	00 
 11d0cb6:	ff d0                	call   *%eax
 11d0cb8:	89 44 24 04          	mov    %eax,0x4(%esp)
 11d0cbc:	8d 84 24 68 0a 00 00 	lea    0xa68(%esp),%eax
 11d0cc3:	89 04 24             	mov    %eax,(%esp)
 11d0cc6:	e8 95 aa 65 00       	call   182b760 <YYRValue::operator=(YYRValue const&)@plt>
 11d0ccb:	8d 84 24 68 0a 00 00 	lea    0xa68(%esp),%eax
 11d0cd2:	89 84 24 04 0b 00 00 	mov    %eax,0xb04(%esp)
 11d0cd9:	8b 44 24 44          	mov    0x44(%esp),%eax
 11d0cdd:	89 44 24 04          	mov    %eax,0x4(%esp)
 11d0ce1:	8d 84 24 78 0a 00 00 	lea    0xa78(%esp),%eax
 11d0ce8:	89 04 24             	mov    %eax,(%esp)
 11d0ceb:	e8 80 aa 65 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 11d0cf0:	8d 84 24 78 0a 00 00 	lea    0xa78(%esp),%eax
 11d0cf7:	89 84 24 08 0b 00 00 	mov    %eax,0xb08(%esp)
 11d0cfe:	8b 84 24 a0 00 00 00 	mov    0xa0(%esp),%eax
 11d0d05:	89 44 24 04          	mov    %eax,0x4(%esp)
 11d0d09:	8d 84 24 88 0a 00 00 	lea    0xa88(%esp),%eax
 11d0d10:	89 04 24             	mov    %eax,(%esp)
 11d0d13:	e8 58 aa 65 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 11d0d18:	8d 84 24 88 0a 00 00 	lea    0xa88(%esp),%eax
 11d0d1f:	89 84 24 0c 0b 00 00 	mov    %eax,0xb0c(%esp)
 11d0d26:	f7 47 0c ff ff ff 00 	testl  $0xffffff,0xc(%edi)
 11d0d2d:	0f 84 f8 0b 00 00    	je     11d192b <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x572db>
 11d0d33:	89 3c 24             	mov    %edi,(%esp)
 11d0d36:	e8 a5 aa 65 00       	call   182b7e0 <REAL_RValue_Ex(RValue const*)@plt>
 11d0d3b:	dd 9c 24 b8 01 00 00 	fstpl  0x1b8(%esp)
 11d0d42:	f2 0f 10 84 24 b8 01 	movsd  0x1b8(%esp),%xmm0
 11d0d49:	00 00 
 11d0d4b:	e9 df 0b 00 00       	jmp    11d192f <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x572df>
 11d0d50:	c7 84 24 18 0a 00 00 	movl   $0x1789,0xa18(%esp)
 11d0d57:	89 17 00 00 
 11d0d5b:	8b 84 24 cc 06 00 00 	mov    0x6cc(%esp),%eax
 11d0d62:	b9 46 00 00 00       	mov    $0x46,%ecx
 11d0d67:	0f a3 c1             	bt     %eax,%ecx
 11d0d6a:	73 0f                	jae    11d0d7b <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x5672b>
 11d0d6c:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 11d0d73:	89 04 24             	mov    %eax,(%esp)
 11d0d76:	e8 45 a9 65 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11d0d7b:	c7 84 24 c0 06 00 00 	movl   $0x0,0x6c0(%esp)
 11d0d82:	00 00 00 00 
 11d0d86:	c7 84 24 c8 06 00 00 	movl   $0x0,0x6c8(%esp)
 11d0d8d:	00 00 00 00 
 11d0d91:	c7 84 24 cc 06 00 00 	movl   $0x5,0x6cc(%esp)
 11d0d98:	05 00 00 00 
 11d0d9c:	8b b3 48 d3 ff ff    	mov    -0x2cb8(%ebx),%esi
 11d0da2:	89 74 24 04          	mov    %esi,0x4(%esp)
 11d0da6:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 11d0dad:	89 04 24             	mov    %eax,(%esp)
 11d0db0:	e8 bb a9 65 00       	call   182b770 <YYRValue::operator=(YYRValue const*)@plt>
 11d0db5:	8d 84 24 38 0a 00 00 	lea    0xa38(%esp),%eax
 11d0dbc:	89 84 24 f8 0a 00 00 	mov    %eax,0xaf8(%esp)
 11d0dc3:	8b 83 d4 00 ff ff    	mov    -0xff2c(%ebx),%eax
 11d0dc9:	8b 40 04             	mov    0x4(%eax),%eax
 11d0dcc:	8d 8c 24 f8 0a 00 00 	lea    0xaf8(%esp),%ecx
 11d0dd3:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 11d0dd7:	89 44 24 10          	mov    %eax,0x10(%esp)
 11d0ddb:	8d 84 24 c0 06 00 00 	lea    0x6c0(%esp),%eax
 11d0de2:	89 44 24 08          	mov    %eax,0x8(%esp)
 11d0de6:	8b 45 0c             	mov    0xc(%ebp),%eax
 11d0de9:	89 44 24 04          	mov    %eax,0x4(%esp)
 11d0ded:	8b 45 08             	mov    0x8(%ebp),%eax
 11d0df0:	89 04 24             	mov    %eax,(%esp)
 11d0df3:	c7 44 24 0c 01 00 00 	movl   $0x1,0xc(%esp)
 11d0dfa:	00 
 11d0dfb:	e8 00 aa 65 00       	call   182b800 <YYGML_CallLegacyFunction(CInstance*, CInstance*, YYRValue&, int, int, YYRValue**)@plt>
 11d0e00:	89 04 24             	mov    %eax,(%esp)
 11d0e03:	e8 28 aa 65 00       	call   182b830 <BOOL_RValue(RValue const*)@plt>
 11d0e08:	84 c0                	test   %al,%al
 11d0e0a:	0f 84 aa 00 00 00    	je     11d0eba <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x5686a>
 11d0e10:	c7 84 24 18 0a 00 00 	movl   $0x178b,0xa18(%esp)
 11d0e17:	8b 17 00 00 
 11d0e1b:	8b 84 24 bc 06 00 00 	mov    0x6bc(%esp),%eax
 11d0e22:	b9 46 00 00 00       	mov    $0x46,%ecx
 11d0e27:	0f a3 c1             	bt     %eax,%ecx
 11d0e2a:	73 0f                	jae    11d0e3b <gml_Object_ob_car_Step_0(CInstance*, CInstance*)@@Base+0x567eb>
 11d0e2c:	8d 84 24 b0 06 00 00 	lea    0x6b0(%esp),%eax
 11d0e33:	89 04 24             	mov    %eax,(%esp)
 11d0e36:	e8 85 a8 65 00       	call   182b6c0 <FREE_RValue__Pre(RValue*)@plt>
 11d0e3b:	c7 84 24 b0 06 00 00 	movl   $0x0,0x6b0(%esp)
 11d0e42:	00 00 00 00 
 11d0e46:	c7 84 24 b8 06 00 00 	movl   $0x0,0x6b8(%esp)
 11d0e4d:	00 00 00 00 
 11d0e51:	c7 84 24 bc 06 00 00 	movl   $0x5,0x6bc(%esp)
