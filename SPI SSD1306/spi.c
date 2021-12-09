Real-Time Linux with PREEMPT_RT

Check our new training course
with Creative Commons CC-BY-SA
lecture and lab materials

Elixir Cross Referencer
HOME ENGINEERING TRAINING DOCS COMMUNITY COMPANY
twitter mastodon linkedin github
/drivers/spi/spi.c

All symbols
Search Identifier
Go get it
   1
   2
   3
   4
   5
   6
   7
   8
   9
  10
  11
  12
  13
  14
  15
  16
  17
  18
  19
  20
  21
  22
  23
  24
  25
  26
  27
  28
  29
  30
  31
  32
  33
  34
  35
  36
  37
  38
  39
  40
  41
  42
  43
  44
  45
  46
  47
  48
  49
  50
  51
  52
  53
  54
  55
  56
  57
  58
  59
  60
  61
  62
  63
  64
  65
  66
  67
  68
  69
  70
  71
  72
  73
  74
  75
  76
  77
  78
  79
  80
  81
  82
  83
  84
  85
  86
  87
  88
  89
  90
  91
  92
  93
  94
  95
  96
  97
  98
  99
 100
 101
 102
 103
 104
 105
 106
 107
 108
 109
 110
 111
 112
 113
 114
 115
 116
 117
 118
 119
 120
 121
 122
 123
 124
 125
 126
 127
 128
 129
 130
 131
 132
 133
 134
 135
 136
 137
 138
 139
 140
 141
 142
 143
 144
 145
 146
 147
 148
 149
 150
 151
 152
 153
 154
 155
 156
 157
 158
 159
 160
 161
 162
 163
 164
 165
 166
 167
 168
 169
 170
 171
 172
 173
 174
 175
 176
 177
 178
 179
 180
 181
 182
 183
 184
 185
 186
 187
 188
 189
 190
 191
 192
 193
 194
 195
 196
 197
 198
 199
 200
 201
 202
 203
 204
 205
 206
 207
 208
 209
 210
 211
 212
 213
 214
 215
 216
 217
 218
 219
 220
 221
 222
 223
 224
 225
 226
 227
 228
 229
 230
 231
 232
 233
 234
 235
 236
 237
 238
 239
 240
 241
 242
 243
 244
 245
 246
 247
 248
 249
 250
 251
 252
 253
 254
 255
 256
 257
 258
 259
 260
 261
 262
 263
 264
 265
 266
 267
 268
 269
 270
 271
 272
 273
 274
 275
 276
 277
 278
 279
 280
 281
 282
 283
 284
 285
 286
 287
 288
 289
 290
 291
 292
 293
 294
 295
 296
 297
 298
 299
 300
 301
 302
 303
 304
 305
 306
 307
 308
 309
 310
 311
 312
 313
 314
 315
 316
 317
 318
 319
 320
 321
 322
 323
 324
 325
 326
 327
 328
 329
 330
 331
 332
 333
 334
 335
 336
 337
 338
 339
 340
 341
 342
 343
 344
 345
 346
 347
 348
 349
 350
 351
 352
 353
 354
 355
 356
 357
 358
 359
 360
 361
 362
 363
 364
 365
 366
 367
 368
 369
 370
 371
 372
 373
 374
 375
 376
 377
 378
 379
 380
 381
 382
 383
 384
 385
 386
 387
 388
 389
 390
 391
 392
 393
 394
 395
 396
 397
 398
 399
 400
 401
 402
 403
 404
 405
 406
 407
 408
 409
 410
 411
 412
 413
 414
 415
 416
 417
 418
 419
 420
 421
 422
 423
 424
 425
 426
 427
 428
 429
 430
 431
 432
 433
 434
 435
 436
 437
 438
 439
 440
 441
 442
 443
 444
 445
 446
 447
 448
 449
 450
 451
 452
 453
 454
 455
 456
 457
 458
 459
 460
 461
 462
 463
 464
 465
 466
 467
 468
 469
 470
 471
 472
 473
 474
 475
 476
 477
 478
 479
 480
 481
 482
 483
 484
 485
 486
 487
 488
 489
 490
 491
 492
 493
 494
 495
 496
 497
 498
 499
 500
 501
 502
 503
 504
 505
 506
 507
 508
 509
 510
 511
 512
 513
 514
 515
 516
 517
 518
 519
 520
 521
 522
 523
 524
 525
 526
 527
 528
 529
 530
 531
 532
 533
 534
 535
 536
 537
 538
 539
 540
 541
 542
 543
 544
 545
 546
 547
 548
 549
 550
 551
 552
 553
 554
 555
 556
 557
 558
 559
 560
 561
 562
 563
 564
 565
 566
 567
 568
 569
 570
 571
 572
 573
 574
 575
 576
 577
 578
 579
 580
 581
 582
 583
 584
 585
 586
 587
 588
 589
 590
 591
 592
 593
 594
 595
 596
 597
 598
 599
 600
 601
 602
 603
 604
 605
 606
 607
 608
 609
 610
 611
 612
 613
 614
 615
 616
 617
 618
 619
 620
 621
 622
 623
 624
 625
 626
 627
 628
 629
 630
 631
 632
 633
 634
 635
 636
 637
 638
 639
 640
 641
 642
 643
 644
 645
 646
 647
 648
 649
 650
 651
 652
 653
 654
 655
 656
 657
 658
 659
 660
 661
 662
 663
 664
 665
 666
 667
 668
 669
 670
 671
 672
 673
 674
 675
 676
 677
 678
 679
 680
 681
 682
 683
 684
 685
 686
 687
 688
 689
 690
 691
 692
 693
 694
 695
 696
 697
 698
 699
 700
 701
 702
 703
 704
 705
 706
 707
 708
 709
 710
 711
 712
 713
 714
 715
 716
 717
 718
 719
 720
 721
 722
 723
 724
 725
 726
 727
 728
 729
 730
 731
 732
 733
 734
 735
 736
 737
 738
 739
 740
 741
 742
 743
 744
 745
 746
 747
 748
 749
 750
 751
 752
 753
 754
 755
 756
 757
 758
 759
 760
 761
 762
 763
 764
 765
 766
 767
 768
 769
 770
 771
 772
 773
 774
 775
 776
 777
 778
 779
 780
 781
 782
 783
 784
 785
 786
 787
 788
 789
 790
 791
 792
 793
 794
 795
 796
 797
 798
 799
 800
 801
 802
 803
 804
 805
 806
 807
 808
 809
 810
 811
 812
 813
 814
 815
 816
 817
 818
 819
 820
 821
 822
 823
 824
 825
 826
 827
 828
 829
 830
 831
 832
 833
 834
 835
 836
 837
 838
 839
 840
 841
 842
 843
 844
 845
 846
 847
 848
 849
 850
 851
 852
 853
 854
 855
 856
 857
 858
 859
 860
 861
 862
 863
 864
 865
 866
 867
 868
 869
 870
 871
 872
 873
 874
 875
 876
 877
 878
 879
 880
 881
 882
 883
 884
 885
 886
 887
 888
 889
 890
 891
 892
 893
 894
 895
 896
 897
 898
 899
 900
 901
 902
 903
 904
 905
 906
 907
 908
 909
 910
 911
 912
 913
 914
 915
 916
 917
 918
 919
 920
 921
 922
 923
 924
 925
 926
 927
 928
 929
 930
 931
 932
 933
 934
 935
 936
 937
 938
 939
 940
 941
 942
 943
 944
 945
 946
 947
 948
 949
 950
 951
 952
 953
 954
 955
 956
 957
 958
 959
 960
 961
 962
 963
 964
 965
 966
 967
 968
 969
 970
 971
 972
 973
 974
 975
 976
 977
 978
 979
 980
 981
 982
 983
 984
 985
 986
 987
 988
 989
 990
 991
 992
 993
 994
 995
 996
 997
 998
 999
1000
1001
1002
1003
1004
1005
1006
1007
1008
1009
1010
1011
1012
1013
1014
1015
1016
1017
1018
1019
1020
1021
1022
1023
1024
1025
1026
1027
1028
1029
1030
1031
1032
1033
1034
1035
1036
1037
1038
1039
1040
1041
1042
1043
1044
1045
1046
1047
1048
1049
1050
1051
1052
1053
1054
1055
1056
1057
1058
1059
1060
1061
1062
1063
1064
1065
1066
1067
1068
1069
1070
1071
1072
1073
1074
1075
1076
1077
1078
1079
1080
1081
1082
1083
1084
1085
1086
1087
1088
1089
1090
1091
1092
1093
1094
1095
1096
1097
1098
1099
1100
1101
1102
1103
1104
1105
1106
1107
1108
1109
1110
1111
1112
1113
1114
1115
1116
1117
1118
1119
1120
1121
1122
1123
1124
1125
1126
1127
1128
1129
1130
1131
1132
1133
1134
1135
1136
1137
1138
1139
1140
1141
1142
1143
1144
1145
1146
1147
1148
1149
1150
1151
1152
1153
1154
1155
1156
1157
1158
1159
1160
1161
1162
1163
1164
1165
1166
1167
1168
1169
1170
1171
1172
1173
1174
1175
1176
1177
1178
1179
1180
1181
1182
1183
1184
1185
1186
1187
1188
1189
1190
1191
1192
1193
1194
1195
1196
1197
1198
1199
1200
1201
1202
1203
1204
1205
1206
1207
1208
1209
1210
1211
1212
1213
1214
1215
1216
1217
1218
1219
1220
1221
1222
1223
1224
1225
1226
1227
1228
1229
1230
1231
1232
1233
1234
1235
1236
1237
1238
1239
1240
1241
1242
1243
1244
1245
1246
1247
1248
1249
1250
1251
1252
1253
1254
1255
1256
1257
1258
1259
1260
1261
1262
1263
1264
1265
1266
1267
1268
1269
1270
1271
1272
1273
1274
1275
1276
1277
1278
1279
1280
1281
1282
1283
1284
1285
1286
1287
1288
1289
1290
1291
1292
1293
1294
1295
1296
1297
1298
1299
1300
1301
1302
1303
1304
1305
1306
1307
1308
1309
1310
1311
1312
1313
1314
1315
1316
1317
1318
1319
1320
1321
1322
1323
1324
1325
1326
1327
1328
1329
1330
1331
1332
1333
1334
1335
1336
1337
1338
1339
1340
1341
1342
1343
1344
1345
1346
1347
1348
1349
1350
1351
1352
1353
1354
1355
1356
1357
1358
1359
1360
1361
1362
1363
1364
1365
1366
1367
1368
1369
1370
1371
1372
1373
1374
1375
1376
1377
1378
1379
1380
1381
1382
1383
1384
1385
1386
1387
1388
1389
1390
1391
1392
1393
1394
1395
1396
1397
1398
1399
1400
1401
1402
1403
1404
1405
1406
1407
1408
1409
1410
1411
1412
1413
1414
1415
1416
1417
1418
1419
1420
1421
1422
1423
1424
1425
1426
1427
1428
1429
1430
1431
1432
1433
1434
1435
1436
1437
1438
1439
1440
1441
1442
1443
1444
1445
1446
1447
1448
1449
1450
1451
1452
1453
1454
1455
1456
1457
1458
1459
1460
1461
1462
1463
1464
1465
1466
1467
1468
1469
1470
1471
1472
1473
1474
1475
1476
1477
1478
1479
1480
1481
1482
1483
1484
1485
1486
1487
1488
1489
1490
1491
1492
1493
1494
1495
1496
1497
1498
1499
1500
1501
1502
1503
1504
1505
1506
1507
1508
1509
1510
1511
1512
1513
1514
1515
1516
1517
1518
1519
1520
1521
1522
1523
1524
1525
1526
1527
1528
1529
1530
1531
1532
1533
1534
1535
1536
1537
1538
1539
1540
1541
1542
1543
1544
1545
1546
1547
1548
1549
1550
1551
1552
1553
1554
1555
1556
1557
1558
1559
1560
1561
1562
1563
1564
1565
1566
1567
1568
1569
1570
1571
1572
1573
1574
1575
1576
1577
1578
1579
1580
1581
1582
1583
1584
1585
1586
1587
1588
1589
1590
1591
1592
1593
1594
1595
1596
1597
1598
1599
1600
1601
1602
1603
1604
1605
1606
1607
1608
1609
1610
1611
1612
1613
1614
1615
1616
1617
1618
1619
1620
1621
1622
1623
1624
1625
1626
1627
1628
1629
1630
1631
1632
1633
1634
1635
1636
1637
1638
1639
1640
1641
1642
1643
1644
1645
1646
1647
1648
1649
1650
1651
1652
1653
1654
1655
1656
1657
1658
1659
1660
1661
1662
1663
1664
1665
1666
1667
1668
1669
1670
1671
1672
1673
1674
1675
1676
1677
1678
1679
1680
1681
1682
1683
1684
1685
1686
1687
1688
1689
1690
1691
1692
1693
1694
1695
1696
1697
1698
1699
1700
1701
1702
1703
1704
1705
1706
1707
1708
1709
1710
1711
1712
1713
1714
1715
1716
1717
1718
1719
1720
1721
1722
1723
1724
1725
1726
1727
1728
1729
1730
1731
1732
1733
1734
1735
1736
1737
1738
1739
1740
1741
1742
1743
1744
1745
1746
1747
1748
1749
1750
1751
1752
1753
1754
1755
1756
1757
1758
1759
1760
1761
1762
1763
1764
1765
1766
1767
1768
1769
1770
1771
1772
1773
1774
1775
1776
1777
1778
1779
1780
1781
1782
1783
1784
1785
1786
1787
1788
1789
1790
1791
1792
1793
1794
1795
1796
1797
1798
1799
1800
1801
1802
1803
1804
1805
1806
1807
1808
1809
1810
1811
1812
1813
1814
1815
1816
1817
1818
1819
1820
1821
1822
1823
1824
1825
1826
1827
1828
1829
1830
1831
1832
1833
1834
1835
1836
1837
1838
1839
1840
1841
1842
1843
1844
1845
1846
1847
1848
1849
1850
1851
1852
1853
1854
1855
1856
1857
1858
1859
1860
1861
1862
1863
1864
1865
1866
1867
1868
1869
1870
1871
1872
1873
1874
1875
1876
1877
1878
1879
1880
1881
1882
1883
1884
1885
1886
1887
1888
1889
1890
1891
1892
1893
1894
1895
1896
1897
1898
1899
1900
1901
1902
1903
1904
1905
1906
1907
1908
1909
1910
1911
1912
1913
1914
1915
1916
1917
1918
1919
1920
1921
1922
1923
1924
1925
1926
1927
1928
1929
1930
1931
1932
1933
1934
1935
1936
1937
1938
1939
1940
1941
1942
1943
1944
1945
1946
1947
1948
1949
1950
1951
1952
1953
1954
1955
1956
1957
1958
1959
1960
1961
1962
1963
1964
1965
1966
1967
1968
1969
1970
1971
1972
1973
1974
1975
1976
1977
1978
1979
1980
1981
1982
1983
1984
1985
1986
1987
1988
1989
1990
1991
1992
1993
1994
1995
1996
1997
1998
1999
2000
2001
2002
2003
2004
2005
2006
2007
2008
2009
2010
2011
2012
2013
2014
2015
2016
2017
2018
2019
2020
2021
2022
2023
2024
2025
2026
2027
2028
2029
2030
2031
2032
2033
2034
2035
2036
2037
2038
2039
2040
2041
2042
2043
2044
2045
2046
2047
2048
2049
2050
2051
2052
2053
2054
2055
2056
2057
2058
2059
2060
2061
2062
2063
2064
2065
2066
2067
2068
2069
2070
2071
2072
2073
2074
2075
2076
2077
2078
2079
2080
2081
2082
2083
2084
2085
2086
2087
2088
2089
2090
2091
2092
2093
2094
2095
2096
2097
2098
2099
2100
2101
2102
2103
2104
2105
2106
2107
2108
2109
2110
2111
2112
2113
2114
2115
2116
2117
2118
2119
2120
2121
2122
2123
2124
2125
2126
2127
2128
2129
2130
2131
2132
2133
2134
2135
2136
2137
2138
2139
2140
2141
2142
2143
2144
2145
2146
2147
2148
2149
2150
2151
2152
2153
2154
2155
2156
2157
2158
2159
2160
2161
2162
2163
2164
2165
2166
2167
2168
2169
2170
2171
2172
2173
2174
2175
2176
2177
2178
2179
2180
2181
2182
2183
2184
2185
2186
2187
2188
2189
2190
2191
2192
2193
2194
2195
2196
2197
2198
2199
2200
2201
2202
2203
2204
2205
2206
2207
2208
2209
2210
2211
2212
2213
2214
2215
2216
2217
2218
2219
2220
2221
2222
2223
2224
2225
2226
2227
2228
2229
2230
2231
2232
2233
2234
2235
2236
2237
2238
2239
2240
2241
2242
2243
2244
2245
2246
2247
2248
2249
2250
2251
2252
2253
2254
2255
2256
2257
2258
2259
2260
2261
2262
2263
2264
2265
2266
2267
2268
2269
2270
2271
2272
2273
2274
2275
2276
2277
2278
2279
2280
2281
2282
2283
2284
2285
2286
2287
2288
2289
2290
2291
2292
2293
2294
2295
2296
2297
2298
2299
2300
2301
2302
2303
2304
2305
2306
2307
2308
2309
2310
2311
2312
2313
2314
2315
2316
2317
2318
2319
2320
2321
2322
2323
2324
2325
2326
2327
2328
2329
2330
2331
2332
2333
2334
2335
2336
2337
2338
2339
2340
2341
2342
2343
2344
2345
2346
2347
2348
2349
2350
2351
2352
2353
2354
2355
2356
2357
2358
2359
2360
2361
2362
2363
2364
2365
2366
2367
2368
2369
2370
2371
2372
2373
2374
2375
2376
2377
2378
2379
2380
2381
2382
2383
2384
2385
2386
2387
2388
2389
2390
2391
2392
2393
2394
2395
2396
2397
2398
2399
2400
2401
2402
2403
2404
2405
2406
2407
2408
2409
2410
2411
2412
2413
2414
2415
2416
2417
2418
2419
2420
2421
2422
2423
2424
2425
2426
2427
2428
2429
2430
2431
2432
2433
2434
2435
2436
2437
2438
2439
2440
2441
2442
2443
2444
2445
2446
2447
2448
2449
2450
2451
2452
2453
2454
2455
2456
2457
2458
2459
2460
2461
2462
2463
2464
2465
2466
2467
2468
2469
2470
2471
2472
2473
2474
2475
2476
2477
2478
2479
2480
2481
2482
2483
2484
2485
2486
2487
2488
2489
2490
2491
2492
2493
2494
2495
2496
2497
2498
2499
2500
2501
2502
2503
2504
2505
2506
2507
2508
2509
2510
2511
2512
2513
2514
2515
2516
2517
2518
2519
2520
2521
2522
2523
2524
2525
2526
2527
2528
2529
2530
2531
2532
2533
2534
2535
2536
2537
2538
2539
2540
2541
2542
2543
2544
2545
2546
2547
2548
2549
2550
2551
2552
2553
2554
2555
2556
2557
2558
2559
2560
2561
2562
2563
2564
2565
2566
2567
2568
2569
2570
2571
2572
2573
2574
2575
2576
2577
2578
2579
2580
2581
2582
2583
2584
2585
2586
2587
2588
2589
2590
2591
2592
2593
2594
2595
2596
2597
2598
2599
2600
2601
2602
2603
2604
2605
2606
2607
2608
2609
2610
2611
2612
2613
2614
2615
2616
2617
2618
2619
2620
2621
2622
2623
2624
2625
2626
2627
2628
2629
2630
2631
2632
2633
2634
2635
2636
2637
2638
2639
2640
2641
2642
2643
2644
2645
2646
2647
2648
2649
2650
2651
2652
2653
2654
2655
2656
2657
2658
2659
2660
2661
2662
2663
2664
2665
2666
2667
2668
2669
2670
2671
2672
2673
2674
2675
2676
2677
2678
2679
2680
2681
2682
2683
2684
2685
2686
2687
2688
2689
2690
2691
2692
2693
2694
2695
2696
2697
2698
2699
2700
2701
2702
2703
2704
2705
2706
2707
2708
2709
2710
2711
2712
2713
2714
2715
2716
2717
2718
2719
2720
2721
2722
2723
2724
2725
2726
2727
2728
2729
2730
2731
2732
2733
2734
2735
2736
2737
2738
2739
2740
2741
2742
2743
2744
2745
2746
2747
2748
2749
2750
2751
2752
2753
2754
2755
2756
2757
2758
2759
2760
2761
2762
2763
2764
2765
2766
2767
2768
2769
2770
2771
2772
2773
2774
2775
2776
2777
2778
2779
2780
2781
2782
2783
2784
2785
2786
2787
2788
2789
2790
2791
2792
2793
2794
2795
2796
2797
2798
2799
2800
2801
2802
2803
2804
2805
2806
2807
2808
2809
2810
2811
2812
2813
2814
2815
2816
2817
2818
2819
2820
2821
2822
2823
2824
2825
2826
2827
2828
2829
2830
2831
2832
2833
2834
2835
2836
2837
2838
2839
2840
2841
2842
2843
2844
2845
2846
2847
2848
2849
2850
2851
2852
2853
2854
2855
2856
2857
2858
2859
2860
2861
2862
2863
2864
2865
2866
2867
2868
2869
2870
2871
2872
2873
2874
2875
2876
2877
2878
2879
2880
2881
2882
2883
2884
2885
2886
2887
2888
2889
2890
2891
2892
2893
2894
2895
2896
2897
2898
2899
2900
2901
2902
2903
2904
2905
2906
2907
2908
2909
2910
2911
2912
2913
2914
2915
2916
2917
2918
2919
2920
2921
2922
2923
2924
2925
2926
2927
2928
2929
2930
2931
2932
2933
2934
2935
2936
2937
2938
2939
2940
2941
2942
2943
2944
2945
2946
2947
2948
2949
2950
2951
2952
2953
2954
2955
2956
2957
2958
2959
2960
2961
2962
2963
2964
2965
2966
2967
2968
2969
2970
2971
2972
2973
2974
2975
2976
2977
2978
2979
2980
2981
2982
2983
2984
2985
2986
2987
2988
2989
2990
2991
2992
2993
2994
2995
2996
2997
2998
2999
3000
3001
3002
3003
3004
3005
3006
3007
3008
3009
3010
3011
3012
3013
3014
3015
3016
3017
3018
3019
3020
3021
3022
3023
3024
3025
3026
3027
3028
3029
3030
3031
3032
3033
3034
3035
3036
3037
3038
3039
3040
3041
3042
3043
3044
3045
3046
3047
3048
3049
3050
3051
3052
3053
3054
3055
3056
3057
3058
3059
3060
3061
3062
3063
3064
3065
3066
3067
3068
3069
3070
3071
3072
3073
3074
3075
3076
3077
3078
3079
3080
3081
3082
3083
3084
3085
3086
3087
3088
3089
3090
3091
3092
3093
3094
3095
3096
3097
3098
3099
3100
3101
3102
3103
3104
3105
3106
3107
3108
3109
3110
3111
3112
3113
3114
3115
3116
3117
3118
3119
3120
3121
3122
3123
3124
3125
3126
3127
3128
3129
3130
3131
3132
3133
3134
3135
3136
3137
3138
3139
3140
3141
3142
3143
3144
3145
3146
3147
3148
3149
3150
3151
3152
3153
3154
3155
3156
3157
3158
3159
3160
3161
3162
3163
3164
3165
3166
3167
3168
3169
3170
3171
3172
3173
3174
3175
3176
3177
3178
3179
3180
3181
3182
3183
3184
3185
3186
3187
3188
3189
3190
3191
3192
3193
3194
3195
3196
3197
3198
3199
3200
3201
3202
3203
3204
3205
3206
3207
3208
3209
3210
3211
3212
3213
3214
3215
3216
3217
3218
3219
3220
3221
3222
3223
3224
3225
3226
3227
3228
3229
3230
3231
3232
3233
3234
3235
3236
3237
3238
3239
3240
3241
3242
3243
3244
3245
3246
3247
3248
3249
3250
3251
3252
3253
3254
3255
3256
3257
3258
3259
3260
3261
3262
3263
3264
3265
3266
3267
3268
3269
3270
3271
3272
3273
3274
3275
3276
3277
3278
3279
3280
3281
3282
3283
3284
3285
3286
3287
3288
3289
3290
3291
3292
3293
3294
3295
3296
3297
3298
3299
3300
3301
3302
3303
3304
3305
3306
3307
3308
3309
3310
3311
3312
3313
3314
3315
3316
3317
3318
3319
3320
3321
3322
3323
3324
3325
3326
3327
3328
3329
3330
3331
3332
3333
3334
3335
3336
3337
3338
3339
3340
3341
3342
3343
3344
3345
3346
3347
3348
3349
3350
3351
3352
3353
3354
3355
3356
3357
3358
3359
3360
3361
3362
3363
3364
3365
3366
3367
3368
3369
3370
3371
3372
3373
3374
3375
3376
3377
3378
3379
3380
3381
3382
3383
3384
3385
3386
3387
3388
3389
3390
3391
3392
3393
3394
3395
3396
3397
3398
3399
3400
3401
3402
3403
3404
3405
3406
3407
3408
3409
3410
3411
3412
3413
3414
3415
3416
3417
3418
3419
3420
3421
3422
3423
3424
3425
3426
3427
3428
3429
3430
3431
3432
3433
3434
3435
3436
3437
3438
3439
3440
3441
3442
3443
3444
3445
3446
3447
3448
3449
3450
3451
3452
3453
3454
3455
3456
3457
3458
3459
3460
3461
3462
3463
3464
3465
3466
3467
3468
3469
3470
3471
3472
3473
3474
3475
3476
3477
3478
3479
3480
3481
3482
3483
3484
3485
3486
3487
3488
3489
3490
3491
3492
3493
3494
3495
3496
3497
3498
3499
3500
3501
3502
3503
3504
3505
3506
3507
3508
3509
3510
3511
3512
3513
3514
3515
3516
3517
3518
3519
3520
3521
3522
3523
3524
3525
3526
3527
3528
3529
3530
3531
3532
3533
3534
3535
3536
3537
3538
3539
3540
3541
3542
3543
3544
3545
3546
3547
3548
3549
3550
3551
3552
3553
3554
3555
3556
3557
3558
3559
3560
3561
3562
3563
3564
3565
3566
3567
3568
3569
3570
3571
3572
3573
3574
3575
3576
3577
3578
3579
3580
3581
3582
3583
3584
3585
3586
3587
3588
3589
3590
3591
3592
3593
3594
3595
3596
3597
3598
3599
3600
3601
3602
3603
3604
3605
3606
3607
3608
3609
3610
3611
3612
3613
3614
3615
3616
3617
3618
3619
3620
3621
3622
3623
3624
3625
3626
3627
3628
3629
3630
3631
3632
3633
3634
3635
3636
3637
3638
3639
3640
3641
3642
3643
3644
3645
3646
3647
3648
3649
3650
3651
3652
3653
3654
3655
3656
3657
3658
3659
3660
3661
3662
3663
3664
3665
3666
3667
3668
3669
3670
3671
3672
3673
3674
3675
3676
3677
3678
3679
3680
3681
3682
3683
3684
3685
3686
3687
3688
3689
3690
3691
3692
3693
3694
3695
3696
3697
3698
3699
3700
3701
3702
3703
3704
3705
3706
3707
3708
3709
3710
3711
3712
3713
3714
3715
3716
3717
3718
3719
3720
3721
3722
3723
3724
3725
3726
3727
3728
3729
3730
3731
3732
3733
3734
3735
3736
3737
3738
3739
3740
3741
3742
3743
3744
3745
3746
3747
3748
3749
3750
3751
3752
3753
3754
3755
3756
3757
3758
3759
3760
3761
3762
3763
3764
3765
3766
3767
3768
3769
3770
3771
3772
3773
3774
3775
3776
3777
3778
3779
3780
3781
3782
3783
3784
3785
3786
3787
3788
3789
3790
3791
3792
3793
3794
3795
3796
3797
3798
3799
3800
3801
3802
3803
3804
3805
3806
3807
3808
3809
3810
3811
3812
3813
3814
3815
3816
3817
3818
3819
3820
3821
3822
3823
3824
3825
3826
3827
3828
3829
3830
3831
3832
3833
3834
3835
3836
3837
3838
3839
3840
3841
3842
3843
3844
3845
3846
3847
3848
3849
3850
3851
3852
3853
3854
3855
3856
3857
3858
3859
3860
3861
3862
3863
3864
3865
3866
3867
3868
3869
3870
3871
3872
3873
3874
3875
3876
3877
3878
3879
3880
3881
3882
3883
3884
3885
3886
3887
3888
3889
3890
3891
3892
3893
3894
3895
3896
3897
3898
3899
3900
3901
3902
3903
3904
3905
3906
3907
3908
3909
3910
3911
3912
3913
3914
3915
3916
3917
3918
3919
3920
3921
3922
3923
3924
3925
3926
3927
3928
3929
3930
3931
3932
3933
3934
3935
3936
3937
3938
3939
3940
3941
3942
3943
3944
3945
3946
3947
3948
3949
3950
3951
3952
3953
3954
3955
3956
3957
3958
3959
3960
3961
3962
3963
3964
3965
3966
3967
3968
3969
3970
3971
3972
3973
3974
3975
3976
3977
3978
3979
3980
3981
3982
3983
3984
3985
3986
3987
3988
3989
3990
3991
3992
3993
3994
3995
3996
3997
3998
3999
4000
4001
4002
4003
4004
4005
4006
4007
4008
4009
4010
4011
4012
4013
4014
4015
4016
4017
4018
4019
4020
4021
4022
4023
4024
4025
4026
4027
4028
4029
4030
4031
4032
4033
4034
4035
4036
4037
4038
4039
4040
4041
4042
4043
4044
4045
4046
4047
4048
4049
4050
4051
4052
4053
4054
4055
4056
4057
4058
4059
4060
4061
4062
4063
4064
4065
4066
4067
4068
4069
4070
4071
4072
4073
4074
4075
4076
4077
4078
4079
4080
4081
4082
4083
4084
4085
4086
4087
4088
4089
4090
4091
4092
4093
4094
4095
4096
4097
4098
4099
4100
4101
4102
4103
4104
4105
4106
4107
4108
4109
4110
4111
4112
4113
4114
4115
4116
4117
4118
4119
4120
4121
4122
4123
4124
4125
4126
4127
4128
4129
4130
4131
4132
4133
4134
4135
4136
4137
4138
4139
4140
4141
4142
4143
4144
4145
4146
4147
4148
4149
4150
4151
4152
4153
4154
4155
4156
4157
4158
4159
4160
4161
4162
4163
4164
4165
4166
4167
4168
4169
4170
4171
4172
4173
4174
4175
4176
4177
4178
4179
4180
4181
4182
4183
4184
4185
4186
4187
4188
4189
4190
4191
4192
4193
4194
4195
4196
4197
4198
4199
4200
4201
4202
4203
4204
4205
4206
4207
4208
4209
4210
4211
4212
4213
4214
4215
4216
4217
4218
4219
4220
4221
4222
4223
4224
4225
4226
4227
4228
4229
4230
4231
4232
4233
4234
4235
4236
4237
4238
4239
4240
4241
4242
4243
4244
4245
4246
4247
4248
4249
4250
// SPDX-License-Identifier: GPL-2.0-or-later
// SPI init/core code
//
// Copyright (C) 2005 David Brownell
// Copyright (C) 2008 Secret Lab Technologies Ltd.

#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/cache.h>
#include <linux/dma-mapping.h>
#include <linux/dmaengine.h>
#include <linux/mutex.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/clk/clk-conf.h>
#include <linux/slab.h>
#include <linux/mod_devicetable.h>
#include <linux/spi/spi.h>
#include <linux/spi/spi-mem.h>
#include <linux/of_gpio.h>
#include <linux/gpio/consumer.h>
#include <linux/pm_runtime.h>
#include <linux/pm_domain.h>
#include <linux/property.h>
#include <linux/export.h>
#include <linux/sched/rt.h>
#include <uapi/linux/sched/types.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/ioport.h>
#include <linux/acpi.h>
#include <linux/highmem.h>
#include <linux/idr.h>
#include <linux/platform_data/x86/apple.h>

#define CREATE_TRACE_POINTS
#include <trace/events/spi.h>
EXPORT_TRACEPOINT_SYMBOL(spi_transfer_start);
EXPORT_TRACEPOINT_SYMBOL(spi_transfer_stop);

#include "internals.h"

static DEFINE_IDR(spi_master_idr);

static void spidev_release(struct device *dev)
{
	struct spi_device	*spi = to_spi_device(dev);

	spi_controller_put(spi->controller);
	kfree(spi->driver_override);
	kfree(spi);
}

static ssize_t
modalias_show(struct device *dev, struct device_attribute *a, char *buf)
{
	const struct spi_device	*spi = to_spi_device(dev);
	int len;

	len = acpi_device_modalias(dev, buf, PAGE_SIZE - 1);
	if (len != -ENODEV)
		return len;

	return sprintf(buf, "%s%s\n", SPI_MODULE_PREFIX, spi->modalias);
}
static DEVICE_ATTR_RO(modalias);

static ssize_t driver_override_store(struct device *dev,
				     struct device_attribute *a,
				     const char *buf, size_t count)
{
	struct spi_device *spi = to_spi_device(dev);
	const char *end = memchr(buf, '\n', count);
	const size_t len = end ? end - buf : count;
	const char *driver_override, *old;

	/* We need to keep extra room for a newline when displaying value */
	if (len >= (PAGE_SIZE - 1))
		return -EINVAL;

	driver_override = kstrndup(buf, len, GFP_KERNEL);
	if (!driver_override)
		return -ENOMEM;

	device_lock(dev);
	old = spi->driver_override;
	if (len) {
		spi->driver_override = driver_override;
	} else {
		/* Empty string, disable driver override */
		spi->driver_override = NULL;
		kfree(driver_override);
	}
	device_unlock(dev);
	kfree(old);

	return count;
}

static ssize_t driver_override_show(struct device *dev,
				    struct device_attribute *a, char *buf)
{
	const struct spi_device *spi = to_spi_device(dev);
	ssize_t len;

	device_lock(dev);
	len = snprintf(buf, PAGE_SIZE, "%s\n", spi->driver_override ? : "");
	device_unlock(dev);
	return len;
}
static DEVICE_ATTR_RW(driver_override);

#define SPI_STATISTICS_ATTRS(field, file)				\
static ssize_t spi_controller_##field##_show(struct device *dev,	\
					     struct device_attribute *attr, \
					     char *buf)			\
{									\
	struct spi_controller *ctlr = container_of(dev,			\
					 struct spi_controller, dev);	\
	return spi_statistics_##field##_show(&ctlr->statistics, buf);	\
}									\
static struct device_attribute dev_attr_spi_controller_##field = {	\
	.attr = { .name = file, .mode = 0444 },				\
	.show = spi_controller_##field##_show,				\
};									\
static ssize_t spi_device_##field##_show(struct device *dev,		\
					 struct device_attribute *attr,	\
					char *buf)			\
{									\
	struct spi_device *spi = to_spi_device(dev);			\
	return spi_statistics_##field##_show(&spi->statistics, buf);	\
}									\
static struct device_attribute dev_attr_spi_device_##field = {		\
	.attr = { .name = file, .mode = 0444 },				\
	.show = spi_device_##field##_show,				\
}

#define SPI_STATISTICS_SHOW_NAME(name, file, field, format_string)	\
static ssize_t spi_statistics_##name##_show(struct spi_statistics *stat, \
					    char *buf)			\
{									\
	unsigned long flags;						\
	ssize_t len;							\
	spin_lock_irqsave(&stat->lock, flags);				\
	len = sprintf(buf, format_string, stat->field);			\
	spin_unlock_irqrestore(&stat->lock, flags);			\
	return len;							\
}									\
SPI_STATISTICS_ATTRS(name, file)

#define SPI_STATISTICS_SHOW(field, format_string)			\
	SPI_STATISTICS_SHOW_NAME(field, __stringify(field),		\
				 field, format_string)

SPI_STATISTICS_SHOW(messages, "%lu");
SPI_STATISTICS_SHOW(transfers, "%lu");
SPI_STATISTICS_SHOW(errors, "%lu");
SPI_STATISTICS_SHOW(timedout, "%lu");

SPI_STATISTICS_SHOW(spi_sync, "%lu");
SPI_STATISTICS_SHOW(spi_sync_immediate, "%lu");
SPI_STATISTICS_SHOW(spi_async, "%lu");

SPI_STATISTICS_SHOW(bytes, "%llu");
SPI_STATISTICS_SHOW(bytes_rx, "%llu");
SPI_STATISTICS_SHOW(bytes_tx, "%llu");

#define SPI_STATISTICS_TRANSFER_BYTES_HISTO(index, number)		\
	SPI_STATISTICS_SHOW_NAME(transfer_bytes_histo##index,		\
				 "transfer_bytes_histo_" number,	\
				 transfer_bytes_histo[index],  "%lu")
SPI_STATISTICS_TRANSFER_BYTES_HISTO(0,  "0-1");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(1,  "2-3");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(2,  "4-7");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(3,  "8-15");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(4,  "16-31");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(5,  "32-63");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(6,  "64-127");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(7,  "128-255");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(8,  "256-511");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(9,  "512-1023");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(10, "1024-2047");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(11, "2048-4095");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(12, "4096-8191");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(13, "8192-16383");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(14, "16384-32767");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(15, "32768-65535");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(16, "65536+");

SPI_STATISTICS_SHOW(transfers_split_maxsize, "%lu");

static struct attribute *spi_dev_attrs[] = {
	&dev_attr_modalias.attr,
	&dev_attr_driver_override.attr,
	NULL,
};

static const struct attribute_group spi_dev_group = {
	.attrs  = spi_dev_attrs,
};

static struct attribute *spi_device_statistics_attrs[] = {
	&dev_attr_spi_device_messages.attr,
	&dev_attr_spi_device_transfers.attr,
	&dev_attr_spi_device_errors.attr,
	&dev_attr_spi_device_timedout.attr,
	&dev_attr_spi_device_spi_sync.attr,
	&dev_attr_spi_device_spi_sync_immediate.attr,
	&dev_attr_spi_device_spi_async.attr,
	&dev_attr_spi_device_bytes.attr,
	&dev_attr_spi_device_bytes_rx.attr,
	&dev_attr_spi_device_bytes_tx.attr,
	&dev_attr_spi_device_transfer_bytes_histo0.attr,
	&dev_attr_spi_device_transfer_bytes_histo1.attr,
	&dev_attr_spi_device_transfer_bytes_histo2.attr,
	&dev_attr_spi_device_transfer_bytes_histo3.attr,
	&dev_attr_spi_device_transfer_bytes_histo4.attr,
	&dev_attr_spi_device_transfer_bytes_histo5.attr,
	&dev_attr_spi_device_transfer_bytes_histo6.attr,
	&dev_attr_spi_device_transfer_bytes_histo7.attr,
	&dev_attr_spi_device_transfer_bytes_histo8.attr,
	&dev_attr_spi_device_transfer_bytes_histo9.attr,
	&dev_attr_spi_device_transfer_bytes_histo10.attr,
	&dev_attr_spi_device_transfer_bytes_histo11.attr,
	&dev_attr_spi_device_transfer_bytes_histo12.attr,
	&dev_attr_spi_device_transfer_bytes_histo13.attr,
	&dev_attr_spi_device_transfer_bytes_histo14.attr,
	&dev_attr_spi_device_transfer_bytes_histo15.attr,
	&dev_attr_spi_device_transfer_bytes_histo16.attr,
	&dev_attr_spi_device_transfers_split_maxsize.attr,
	NULL,
};

static const struct attribute_group spi_device_statistics_group = {
	.name  = "statistics",
	.attrs  = spi_device_statistics_attrs,
};

static const struct attribute_group *spi_dev_groups[] = {
	&spi_dev_group,
	&spi_device_statistics_group,
	NULL,
};

static struct attribute *spi_controller_statistics_attrs[] = {
	&dev_attr_spi_controller_messages.attr,
	&dev_attr_spi_controller_transfers.attr,
	&dev_attr_spi_controller_errors.attr,
	&dev_attr_spi_controller_timedout.attr,
	&dev_attr_spi_controller_spi_sync.attr,
	&dev_attr_spi_controller_spi_sync_immediate.attr,
	&dev_attr_spi_controller_spi_async.attr,
	&dev_attr_spi_controller_bytes.attr,
	&dev_attr_spi_controller_bytes_rx.attr,
	&dev_attr_spi_controller_bytes_tx.attr,
	&dev_attr_spi_controller_transfer_bytes_histo0.attr,
	&dev_attr_spi_controller_transfer_bytes_histo1.attr,
	&dev_attr_spi_controller_transfer_bytes_histo2.attr,
	&dev_attr_spi_controller_transfer_bytes_histo3.attr,
	&dev_attr_spi_controller_transfer_bytes_histo4.attr,
	&dev_attr_spi_controller_transfer_bytes_histo5.attr,
	&dev_attr_spi_controller_transfer_bytes_histo6.attr,
	&dev_attr_spi_controller_transfer_bytes_histo7.attr,
	&dev_attr_spi_controller_transfer_bytes_histo8.attr,
	&dev_attr_spi_controller_transfer_bytes_histo9.attr,
	&dev_attr_spi_controller_transfer_bytes_histo10.attr,
	&dev_attr_spi_controller_transfer_bytes_histo11.attr,
	&dev_attr_spi_controller_transfer_bytes_histo12.attr,
	&dev_attr_spi_controller_transfer_bytes_histo13.attr,
	&dev_attr_spi_controller_transfer_bytes_histo14.attr,
	&dev_attr_spi_controller_transfer_bytes_histo15.attr,
	&dev_attr_spi_controller_transfer_bytes_histo16.attr,
	&dev_attr_spi_controller_transfers_split_maxsize.attr,
	NULL,
};

static const struct attribute_group spi_controller_statistics_group = {
	.name  = "statistics",
	.attrs  = spi_controller_statistics_attrs,
};

static const struct attribute_group *spi_master_groups[] = {
	&spi_controller_statistics_group,
	NULL,
};

void spi_statistics_add_transfer_stats(struct spi_statistics *stats,
				       struct spi_transfer *xfer,
				       struct spi_controller *ctlr)
{
	unsigned long flags;
	int l2len = min(fls(xfer->len), SPI_STATISTICS_HISTO_SIZE) - 1;

	if (l2len < 0)
		l2len = 0;

	spin_lock_irqsave(&stats->lock, flags);

	stats->transfers++;
	stats->transfer_bytes_histo[l2len]++;

	stats->bytes += xfer->len;
	if ((xfer->tx_buf) &&
	    (xfer->tx_buf != ctlr->dummy_tx))
		stats->bytes_tx += xfer->len;
	if ((xfer->rx_buf) &&
	    (xfer->rx_buf != ctlr->dummy_rx))
		stats->bytes_rx += xfer->len;

	spin_unlock_irqrestore(&stats->lock, flags);
}
EXPORT_SYMBOL_GPL(spi_statistics_add_transfer_stats);

/* modalias support makes "modprobe $MODALIAS" new-style hotplug work,
 * and the sysfs version makes coldplug work too.
 */

static const struct spi_device_id *spi_match_id(const struct spi_device_id *id,
						const struct spi_device *sdev)
{
	while (id->name[0]) {
		if (!strcmp(sdev->modalias, id->name))
			return id;
		id++;
	}
	return NULL;
}

const struct spi_device_id *spi_get_device_id(const struct spi_device *sdev)
{
	const struct spi_driver *sdrv = to_spi_driver(sdev->dev.driver);

	return spi_match_id(sdrv->id_table, sdev);
}
EXPORT_SYMBOL_GPL(spi_get_device_id);

static int spi_match_device(struct device *dev, struct device_driver *drv)
{
	const struct spi_device	*spi = to_spi_device(dev);
	const struct spi_driver	*sdrv = to_spi_driver(drv);

	/* Check override first, and if set, only use the named driver */
	if (spi->driver_override)
		return strcmp(spi->driver_override, drv->name) == 0;

	/* Attempt an OF style match */
	if (of_driver_match_device(dev, drv))
		return 1;

	/* Then try ACPI */
	if (acpi_driver_match_device(dev, drv))
		return 1;

	if (sdrv->id_table)
		return !!spi_match_id(sdrv->id_table, spi);

	return strcmp(spi->modalias, drv->name) == 0;
}

static int spi_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	const struct spi_device		*spi = to_spi_device(dev);
	int rc;

	rc = acpi_device_uevent_modalias(dev, env);
	if (rc != -ENODEV)
		return rc;

	return add_uevent_var(env, "MODALIAS=%s%s", SPI_MODULE_PREFIX, spi->modalias);
}

struct bus_type spi_bus_type = {
	.name		= "spi",
	.dev_groups	= spi_dev_groups,
	.match		= spi_match_device,
	.uevent		= spi_uevent,
};
EXPORT_SYMBOL_GPL(spi_bus_type);


static int spi_drv_probe(struct device *dev)
{
	const struct spi_driver		*sdrv = to_spi_driver(dev->driver);
	struct spi_device		*spi = to_spi_device(dev);
	int ret;

	ret = of_clk_set_defaults(dev->of_node, false);
	if (ret)
		return ret;

	if (dev->of_node) {
		spi->irq = of_irq_get(dev->of_node, 0);
		if (spi->irq == -EPROBE_DEFER)
			return -EPROBE_DEFER;
		if (spi->irq < 0)
			spi->irq = 0;
	}

	ret = dev_pm_domain_attach(dev, true);
	if (ret)
		return ret;

	if (sdrv->probe) {
		ret = sdrv->probe(spi);
		if (ret)
			dev_pm_domain_detach(dev, true);
	}

	return ret;
}

static int spi_drv_remove(struct device *dev)
{
	const struct spi_driver		*sdrv = to_spi_driver(dev->driver);
	int ret = 0;

	if (sdrv->remove)
		ret = sdrv->remove(to_spi_device(dev));
	dev_pm_domain_detach(dev, true);

	return ret;
}

static void spi_drv_shutdown(struct device *dev)
{
	const struct spi_driver		*sdrv = to_spi_driver(dev->driver);

	sdrv->shutdown(to_spi_device(dev));
}

/**
 * __spi_register_driver - register a SPI driver
 * @owner: owner module of the driver to register
 * @sdrv: the driver to register
 * Context: can sleep
 *
 * Return: zero on success, else a negative error code.
 */
int __spi_register_driver(struct module *owner, struct spi_driver *sdrv)
{
	sdrv->driver.owner = owner;
	sdrv->driver.bus = &spi_bus_type;
	sdrv->driver.probe = spi_drv_probe;
	sdrv->driver.remove = spi_drv_remove;
	if (sdrv->shutdown)
		sdrv->driver.shutdown = spi_drv_shutdown;
	return driver_register(&sdrv->driver);
}
EXPORT_SYMBOL_GPL(__spi_register_driver);

/*-------------------------------------------------------------------------*/

/* SPI devices should normally not be created by SPI device drivers; that
 * would make them board-specific.  Similarly with SPI controller drivers.
 * Device registration normally goes into like arch/.../mach.../board-YYY.c
 * with other readonly (flashable) information about mainboard devices.
 */

struct boardinfo {
	struct list_head	list;
	struct spi_board_info	board_info;
};

static LIST_HEAD(board_list);
static LIST_HEAD(spi_controller_list);

/*
 * Used to protect add/del operation for board_info list and
 * spi_controller list, and their matching process
 * also used to protect object of type struct idr
 */
static DEFINE_MUTEX(board_lock);

/*
 * Prevents addition of devices with same chip select and
 * addition of devices below an unregistering controller.
 */
static DEFINE_MUTEX(spi_add_lock);

/**
 * spi_alloc_device - Allocate a new SPI device
 * @ctlr: Controller to which device is connected
 * Context: can sleep
 *
 * Allows a driver to allocate and initialize a spi_device without
 * registering it immediately.  This allows a driver to directly
 * fill the spi_device with device parameters before calling
 * spi_add_device() on it.
 *
 * Caller is responsible to call spi_add_device() on the returned
 * spi_device structure to add it to the SPI controller.  If the caller
 * needs to discard the spi_device without adding it, then it should
 * call spi_dev_put() on it.
 *
 * Return: a pointer to the new device, or NULL.
 */
struct spi_device *spi_alloc_device(struct spi_controller *ctlr)
{
	struct spi_device	*spi;

	if (!spi_controller_get(ctlr))
		return NULL;

	spi = kzalloc(sizeof(*spi), GFP_KERNEL);
	if (!spi) {
		spi_controller_put(ctlr);
		return NULL;
	}

	spi->master = spi->controller = ctlr;
	spi->dev.parent = &ctlr->dev;
	spi->dev.bus = &spi_bus_type;
	spi->dev.release = spidev_release;
	spi->cs_gpio = -ENOENT;
	spi->mode = ctlr->buswidth_override_bits;

	spin_lock_init(&spi->statistics.lock);

	device_initialize(&spi->dev);
	return spi;
}
EXPORT_SYMBOL_GPL(spi_alloc_device);

static void spi_dev_set_name(struct spi_device *spi)
{
	struct acpi_device *adev = ACPI_COMPANION(&spi->dev);

	if (adev) {
		dev_set_name(&spi->dev, "spi-%s", acpi_dev_name(adev));
		return;
	}

	dev_set_name(&spi->dev, "%s.%u", dev_name(&spi->controller->dev),
		     spi->chip_select);
}

static int spi_dev_check(struct device *dev, void *data)
{
	struct spi_device *spi = to_spi_device(dev);
	struct spi_device *new_spi = data;

	if (spi->controller == new_spi->controller &&
	    spi->chip_select == new_spi->chip_select)
		return -EBUSY;
	return 0;
}

static void spi_cleanup(struct spi_device *spi)
{
	if (spi->controller->cleanup)
		spi->controller->cleanup(spi);
}

/**
 * spi_add_device - Add spi_device allocated with spi_alloc_device
 * @spi: spi_device to register
 *
 * Companion function to spi_alloc_device.  Devices allocated with
 * spi_alloc_device can be added onto the spi bus with this function.
 *
 * Return: 0 on success; negative errno on failure
 */
int spi_add_device(struct spi_device *spi)
{
	struct spi_controller *ctlr = spi->controller;
	struct device *dev = ctlr->dev.parent;
	int status;

	/* Chipselects are numbered 0..max; validate. */
	if (spi->chip_select >= ctlr->num_chipselect) {
		dev_err(dev, "cs%d >= max %d\n", spi->chip_select,
			ctlr->num_chipselect);
		return -EINVAL;
	}

	/* Set the bus ID string */
	spi_dev_set_name(spi);

	/* We need to make sure there's no other device with this
	 * chipselect **BEFORE** we call setup(), else we'll trash
	 * its configuration.  Lock against concurrent add() calls.
	 */
	mutex_lock(&spi_add_lock);

	status = bus_for_each_dev(&spi_bus_type, NULL, spi, spi_dev_check);
	if (status) {
		dev_err(dev, "chipselect %d already in use\n",
				spi->chip_select);
		goto done;
	}

	/* Controller may unregister concurrently */
	if (IS_ENABLED(CONFIG_SPI_DYNAMIC) &&
	    !device_is_registered(&ctlr->dev)) {
		status = -ENODEV;
		goto done;
	}

	/* Descriptors take precedence */
	if (ctlr->cs_gpiods)
		spi->cs_gpiod = ctlr->cs_gpiods[spi->chip_select];
	else if (ctlr->cs_gpios)
		spi->cs_gpio = ctlr->cs_gpios[spi->chip_select];

	/* Drivers may modify this initial i/o setup, but will
	 * normally rely on the device being setup.  Devices
	 * using SPI_CS_HIGH can't coexist well otherwise...
	 */
	status = spi_setup(spi);
	if (status < 0) {
		dev_err(dev, "can't setup %s, status %d\n",
				dev_name(&spi->dev), status);
		goto done;
	}

	/* Device may be bound to an active driver when this returns */
	status = device_add(&spi->dev);
	if (status < 0) {
		dev_err(dev, "can't add %s, status %d\n",
				dev_name(&spi->dev), status);
		spi_cleanup(spi);
	} else {
		dev_dbg(dev, "registered child %s\n", dev_name(&spi->dev));
	}

done:
	mutex_unlock(&spi_add_lock);
	return status;
}
EXPORT_SYMBOL_GPL(spi_add_device);

/**
 * spi_new_device - instantiate one new SPI device
 * @ctlr: Controller to which device is connected
 * @chip: Describes the SPI device
 * Context: can sleep
 *
 * On typical mainboards, this is purely internal; and it's not needed
 * after board init creates the hard-wired devices.  Some development
 * platforms may not be able to use spi_register_board_info though, and
 * this is exported so that for example a USB or parport based adapter
 * driver could add devices (which it would learn about out-of-band).
 *
 * Return: the new device, or NULL.
 */
struct spi_device *spi_new_device(struct spi_controller *ctlr,
				  struct spi_board_info *chip)
{
	struct spi_device	*proxy;
	int			status;

	/* NOTE:  caller did any chip->bus_num checks necessary.
	 *
	 * Also, unless we change the return value convention to use
	 * error-or-pointer (not NULL-or-pointer), troubleshootability
	 * suggests syslogged diagnostics are best here (ugh).
	 */

	proxy = spi_alloc_device(ctlr);
	if (!proxy)
		return NULL;

	WARN_ON(strlen(chip->modalias) >= sizeof(proxy->modalias));

	proxy->chip_select = chip->chip_select;
	proxy->max_speed_hz = chip->max_speed_hz;
	proxy->mode = chip->mode;
	proxy->irq = chip->irq;
	strlcpy(proxy->modalias, chip->modalias, sizeof(proxy->modalias));
	proxy->dev.platform_data = (void *) chip->platform_data;
	proxy->controller_data = chip->controller_data;
	proxy->controller_state = NULL;

	if (chip->properties) {
		status = device_add_properties(&proxy->dev, chip->properties);
		if (status) {
			dev_err(&ctlr->dev,
				"failed to add properties to '%s': %d\n",
				chip->modalias, status);
			goto err_dev_put;
		}
	}

	status = spi_add_device(proxy);
	if (status < 0)
		goto err_remove_props;

	return proxy;

err_remove_props:
	if (chip->properties)
		device_remove_properties(&proxy->dev);
err_dev_put:
	spi_dev_put(proxy);
	return NULL;
}
EXPORT_SYMBOL_GPL(spi_new_device);

/**
 * spi_unregister_device - unregister a single SPI device
 * @spi: spi_device to unregister
 *
 * Start making the passed SPI device vanish. Normally this would be handled
 * by spi_unregister_controller().
 */
void spi_unregister_device(struct spi_device *spi)
{
	if (!spi)
		return;

	if (spi->dev.of_node) {
		of_node_clear_flag(spi->dev.of_node, OF_POPULATED);
		of_node_put(spi->dev.of_node);
	}
	if (ACPI_COMPANION(&spi->dev))
		acpi_device_clear_enumerated(ACPI_COMPANION(&spi->dev));
	device_del(&spi->dev);
	spi_cleanup(spi);
	put_device(&spi->dev);
}
EXPORT_SYMBOL_GPL(spi_unregister_device);

static void spi_match_controller_to_boardinfo(struct spi_controller *ctlr,
					      struct spi_board_info *bi)
{
	struct spi_device *dev;

	if (ctlr->bus_num != bi->bus_num)
		return;

	dev = spi_new_device(ctlr, bi);
	if (!dev)
		dev_err(ctlr->dev.parent, "can't create new device for %s\n",
			bi->modalias);
}

/**
 * spi_register_board_info - register SPI devices for a given board
 * @info: array of chip descriptors
 * @n: how many descriptors are provided
 * Context: can sleep
 *
 * Board-specific early init code calls this (probably during arch_initcall)
 * with segments of the SPI device table.  Any device nodes are created later,
 * after the relevant parent SPI controller (bus_num) is defined.  We keep
 * this table of devices forever, so that reloading a controller driver will
 * not make Linux forget about these hard-wired devices.
 *
 * Other code can also call this, e.g. a particular add-on board might provide
 * SPI devices through its expansion connector, so code initializing that board
 * would naturally declare its SPI devices.
 *
 * The board info passed can safely be __initdata ... but be careful of
 * any embedded pointers (platform_data, etc), they're copied as-is.
 * Device properties are deep-copied though.
 *
 * Return: zero on success, else a negative error code.
 */
int spi_register_board_info(struct spi_board_info const *info, unsigned n)
{
	struct boardinfo *bi;
	int i;

	if (!n)
		return 0;

	bi = kcalloc(n, sizeof(*bi), GFP_KERNEL);
	if (!bi)
		return -ENOMEM;

	for (i = 0; i < n; i++, bi++, info++) {
		struct spi_controller *ctlr;

		memcpy(&bi->board_info, info, sizeof(*info));
		if (info->properties) {
			bi->board_info.properties =
					property_entries_dup(info->properties);
			if (IS_ERR(bi->board_info.properties))
				return PTR_ERR(bi->board_info.properties);
		}

		mutex_lock(&board_lock);
		list_add_tail(&bi->list, &board_list);
		list_for_each_entry(ctlr, &spi_controller_list, list)
			spi_match_controller_to_boardinfo(ctlr,
							  &bi->board_info);
		mutex_unlock(&board_lock);
	}

	return 0;
}

/*-------------------------------------------------------------------------*/

static void spi_set_cs(struct spi_device *spi, bool enable, bool force)
{
	bool enable1 = enable;

	/*
	 * Avoid calling into the driver (or doing delays) if the chip select
	 * isn't actually changing from the last time this was called.
	 */
	if (!force && (spi->controller->last_cs_enable == enable) &&
	    (spi->controller->last_cs_mode_high == (spi->mode & SPI_CS_HIGH)))
		return;

	spi->controller->last_cs_enable = enable;
	spi->controller->last_cs_mode_high = spi->mode & SPI_CS_HIGH;

	if (!spi->controller->set_cs_timing) {
		if (enable1)
			spi_delay_exec(&spi->controller->cs_setup, NULL);
		else
			spi_delay_exec(&spi->controller->cs_hold, NULL);
	}

	if (spi->mode & SPI_CS_HIGH)
		enable = !enable;

	if (spi->cs_gpiod || gpio_is_valid(spi->cs_gpio)) {
		if (!(spi->mode & SPI_NO_CS)) {
			if (spi->cs_gpiod) {
				/*
				 * Historically ACPI has no means of the GPIO polarity and
				 * thus the SPISerialBus() resource defines it on the per-chip
				 * basis. In order to avoid a chain of negations, the GPIO
				 * polarity is considered being Active High. Even for the cases
				 * when _DSD() is involved (in the updated versions of ACPI)
				 * the GPIO CS polarity must be defined Active High to avoid
				 * ambiguity. That's why we use enable, that takes SPI_CS_HIGH
				 * into account.
				 */
				if (has_acpi_companion(&spi->dev))
					gpiod_set_value_cansleep(spi->cs_gpiod, !enable);
				else
					/* Polarity handled by GPIO library */
					gpiod_set_value_cansleep(spi->cs_gpiod, enable1);
			} else {
				/*
				 * invert the enable line, as active low is
				 * default for SPI.
				 */
				gpio_set_value_cansleep(spi->cs_gpio, !enable);
			}
		}
		/* Some SPI masters need both GPIO CS & slave_select */
		if ((spi->controller->flags & SPI_MASTER_GPIO_SS) &&
		    spi->controller->set_cs)
			spi->controller->set_cs(spi, !enable);
	} else if (spi->controller->set_cs) {
		spi->controller->set_cs(spi, !enable);
	}

	if (!spi->controller->set_cs_timing) {
		if (!enable1)
			spi_delay_exec(&spi->controller->cs_inactive, NULL);
	}
}

#ifdef CONFIG_HAS_DMA
int spi_map_buf(struct spi_controller *ctlr, struct device *dev,
		struct sg_table *sgt, void *buf, size_t len,
		enum dma_data_direction dir)
{
	const bool vmalloced_buf = is_vmalloc_addr(buf);
	unsigned int max_seg_size = dma_get_max_seg_size(dev);
#ifdef CONFIG_HIGHMEM
	const bool kmap_buf = ((unsigned long)buf >= PKMAP_BASE &&
				(unsigned long)buf < (PKMAP_BASE +
					(LAST_PKMAP * PAGE_SIZE)));
#else
	const bool kmap_buf = false;
#endif
	int desc_len;
	int sgs;
	struct page *vm_page;
	struct scatterlist *sg;
	void *sg_buf;
	size_t min;
	int i, ret;

	if (vmalloced_buf || kmap_buf) {
		desc_len = min_t(int, max_seg_size, PAGE_SIZE);
		sgs = DIV_ROUND_UP(len + offset_in_page(buf), desc_len);
	} else if (virt_addr_valid(buf)) {
		desc_len = min_t(int, max_seg_size, ctlr->max_dma_len);
		sgs = DIV_ROUND_UP(len, desc_len);
	} else {
		return -EINVAL;
	}

	ret = sg_alloc_table(sgt, sgs, GFP_KERNEL);
	if (ret != 0)
		return ret;

	sg = &sgt->sgl[0];
	for (i = 0; i < sgs; i++) {

		if (vmalloced_buf || kmap_buf) {
			/*
			 * Next scatterlist entry size is the minimum between
			 * the desc_len and the remaining buffer length that
			 * fits in a page.
			 */
			min = min_t(size_t, desc_len,
				    min_t(size_t, len,
					  PAGE_SIZE - offset_in_page(buf)));
			if (vmalloced_buf)
				vm_page = vmalloc_to_page(buf);
			else
				vm_page = kmap_to_page(buf);
			if (!vm_page) {
				sg_free_table(sgt);
				return -ENOMEM;
			}
			sg_set_page(sg, vm_page,
				    min, offset_in_page(buf));
		} else {
			min = min_t(size_t, len, desc_len);
			sg_buf = buf;
			sg_set_buf(sg, sg_buf, min);
		}

		buf += min;
		len -= min;
		sg = sg_next(sg);
	}

	ret = dma_map_sg(dev, sgt->sgl, sgt->nents, dir);
	if (!ret)
		ret = -ENOMEM;
	if (ret < 0) {
		sg_free_table(sgt);
		return ret;
	}

	sgt->nents = ret;

	return 0;
}

void spi_unmap_buf(struct spi_controller *ctlr, struct device *dev,
		   struct sg_table *sgt, enum dma_data_direction dir)
{
	if (sgt->orig_nents) {
		dma_unmap_sg(dev, sgt->sgl, sgt->orig_nents, dir);
		sg_free_table(sgt);
	}
}

static int __spi_map_msg(struct spi_controller *ctlr, struct spi_message *msg)
{
	struct device *tx_dev, *rx_dev;
	struct spi_transfer *xfer;
	int ret;

	if (!ctlr->can_dma)
		return 0;

	if (ctlr->dma_tx)
		tx_dev = ctlr->dma_tx->device->dev;
	else
		tx_dev = ctlr->dev.parent;

	if (ctlr->dma_rx)
		rx_dev = ctlr->dma_rx->device->dev;
	else
		rx_dev = ctlr->dev.parent;

	list_for_each_entry(xfer, &msg->transfers, transfer_list) {
		if (!ctlr->can_dma(ctlr, msg->spi, xfer))
			continue;

		if (xfer->tx_buf != NULL) {
			ret = spi_map_buf(ctlr, tx_dev, &xfer->tx_sg,
					  (void *)xfer->tx_buf, xfer->len,
					  DMA_TO_DEVICE);
			if (ret != 0)
				return ret;
		}

		if (xfer->rx_buf != NULL) {
			ret = spi_map_buf(ctlr, rx_dev, &xfer->rx_sg,
					  xfer->rx_buf, xfer->len,
					  DMA_FROM_DEVICE);
			if (ret != 0) {
				spi_unmap_buf(ctlr, tx_dev, &xfer->tx_sg,
					      DMA_TO_DEVICE);
				return ret;
			}
		}
	}

	ctlr->cur_msg_mapped = true;

	return 0;
}

static int __spi_unmap_msg(struct spi_controller *ctlr, struct spi_message *msg)
{
	struct spi_transfer *xfer;
	struct device *tx_dev, *rx_dev;

	if (!ctlr->cur_msg_mapped || !ctlr->can_dma)
		return 0;

	if (ctlr->dma_tx)
		tx_dev = ctlr->dma_tx->device->dev;
	else
		tx_dev = ctlr->dev.parent;

	if (ctlr->dma_rx)
		rx_dev = ctlr->dma_rx->device->dev;
	else
		rx_dev = ctlr->dev.parent;

	list_for_each_entry(xfer, &msg->transfers, transfer_list) {
		if (!ctlr->can_dma(ctlr, msg->spi, xfer))
			continue;

		spi_unmap_buf(ctlr, rx_dev, &xfer->rx_sg, DMA_FROM_DEVICE);
		spi_unmap_buf(ctlr, tx_dev, &xfer->tx_sg, DMA_TO_DEVICE);
	}

	ctlr->cur_msg_mapped = false;

	return 0;
}
#else /* !CONFIG_HAS_DMA */
static inline int __spi_map_msg(struct spi_controller *ctlr,
				struct spi_message *msg)
{
	return 0;
}

static inline int __spi_unmap_msg(struct spi_controller *ctlr,
				  struct spi_message *msg)
{
	return 0;
}
#endif /* !CONFIG_HAS_DMA */

static inline int spi_unmap_msg(struct spi_controller *ctlr,
				struct spi_message *msg)
{
	struct spi_transfer *xfer;

	list_for_each_entry(xfer, &msg->transfers, transfer_list) {
		/*
		 * Restore the original value of tx_buf or rx_buf if they are
		 * NULL.
		 */
		if (xfer->tx_buf == ctlr->dummy_tx)
			xfer->tx_buf = NULL;
		if (xfer->rx_buf == ctlr->dummy_rx)
			xfer->rx_buf = NULL;
	}

	return __spi_unmap_msg(ctlr, msg);
}

static int spi_map_msg(struct spi_controller *ctlr, struct spi_message *msg)
{
	struct spi_transfer *xfer;
	void *tmp;
	unsigned int max_tx, max_rx;

	if ((ctlr->flags & (SPI_CONTROLLER_MUST_RX | SPI_CONTROLLER_MUST_TX))
		&& !(msg->spi->mode & SPI_3WIRE)) {
		max_tx = 0;
		max_rx = 0;

		list_for_each_entry(xfer, &msg->transfers, transfer_list) {
			if ((ctlr->flags & SPI_CONTROLLER_MUST_TX) &&
			    !xfer->tx_buf)
				max_tx = max(xfer->len, max_tx);
			if ((ctlr->flags & SPI_CONTROLLER_MUST_RX) &&
			    !xfer->rx_buf)
				max_rx = max(xfer->len, max_rx);
		}

		if (max_tx) {
			tmp = krealloc(ctlr->dummy_tx, max_tx,
				       GFP_KERNEL | GFP_DMA);
			if (!tmp)
				return -ENOMEM;
			ctlr->dummy_tx = tmp;
			memset(tmp, 0, max_tx);
		}

		if (max_rx) {
			tmp = krealloc(ctlr->dummy_rx, max_rx,
				       GFP_KERNEL | GFP_DMA);
			if (!tmp)
				return -ENOMEM;
			ctlr->dummy_rx = tmp;
		}

		if (max_tx || max_rx) {
			list_for_each_entry(xfer, &msg->transfers,
					    transfer_list) {
				if (!xfer->len)
					continue;
				if (!xfer->tx_buf)
					xfer->tx_buf = ctlr->dummy_tx;
				if (!xfer->rx_buf)
					xfer->rx_buf = ctlr->dummy_rx;
			}
		}
	}

	return __spi_map_msg(ctlr, msg);
}

static int spi_transfer_wait(struct spi_controller *ctlr,
			     struct spi_message *msg,
			     struct spi_transfer *xfer)
{
	struct spi_statistics *statm = &ctlr->statistics;
	struct spi_statistics *stats = &msg->spi->statistics;
	u32 speed_hz = xfer->speed_hz;
	unsigned long long ms;

	if (spi_controller_is_slave(ctlr)) {
		if (wait_for_completion_interruptible(&ctlr->xfer_completion)) {
			dev_dbg(&msg->spi->dev, "SPI transfer interrupted\n");
			return -EINTR;
		}
	} else {
		if (!speed_hz)
			speed_hz = 100000;

		ms = 8LL * 1000LL * xfer->len;
		do_div(ms, speed_hz);
		ms += ms + 200; /* some tolerance */

		if (ms > UINT_MAX)
			ms = UINT_MAX;

		ms = wait_for_completion_timeout(&ctlr->xfer_completion,
						 msecs_to_jiffies(ms));

		if (ms == 0) {
			SPI_STATISTICS_INCREMENT_FIELD(statm, timedout);
			SPI_STATISTICS_INCREMENT_FIELD(stats, timedout);
			dev_err(&msg->spi->dev,
				"SPI transfer timed out\n");
			return -ETIMEDOUT;
		}
	}

	return 0;
}

static void _spi_transfer_delay_ns(u32 ns)
{
	if (!ns)
		return;
	if (ns <= 1000) {
		ndelay(ns);
	} else {
		u32 us = DIV_ROUND_UP(ns, 1000);

		if (us <= 10)
			udelay(us);
		else
			usleep_range(us, us + DIV_ROUND_UP(us, 10));
	}
}

int spi_delay_to_ns(struct spi_delay *_delay, struct spi_transfer *xfer)
{
	u32 delay = _delay->value;
	u32 unit = _delay->unit;
	u32 hz;

	if (!delay)
		return 0;

	switch (unit) {
	case SPI_DELAY_UNIT_USECS:
		delay *= 1000;
		break;
	case SPI_DELAY_UNIT_NSECS: /* nothing to do here */
		break;
	case SPI_DELAY_UNIT_SCK:
		/* clock cycles need to be obtained from spi_transfer */
		if (!xfer)
			return -EINVAL;
		/* if there is no effective speed know, then approximate
		 * by underestimating with half the requested hz
		 */
		hz = xfer->effective_speed_hz ?: xfer->speed_hz / 2;
		if (!hz)
			return -EINVAL;
		delay *= DIV_ROUND_UP(1000000000, hz);
		break;
	default:
		return -EINVAL;
	}

	return delay;
}
EXPORT_SYMBOL_GPL(spi_delay_to_ns);

int spi_delay_exec(struct spi_delay *_delay, struct spi_transfer *xfer)
{
	int delay;

	might_sleep();

	if (!_delay)
		return -EINVAL;

	delay = spi_delay_to_ns(_delay, xfer);
	if (delay < 0)
		return delay;

	_spi_transfer_delay_ns(delay);

	return 0;
}
EXPORT_SYMBOL_GPL(spi_delay_exec);

static void _spi_transfer_cs_change_delay(struct spi_message *msg,
					  struct spi_transfer *xfer)
{
	u32 delay = xfer->cs_change_delay.value;
	u32 unit = xfer->cs_change_delay.unit;
	int ret;

	/* return early on "fast" mode - for everything but USECS */
	if (!delay) {
		if (unit == SPI_DELAY_UNIT_USECS)
			_spi_transfer_delay_ns(10000);
		return;
	}

	ret = spi_delay_exec(&xfer->cs_change_delay, xfer);
	if (ret) {
		dev_err_once(&msg->spi->dev,
			     "Use of unsupported delay unit %i, using default of 10us\n",
			     unit);
		_spi_transfer_delay_ns(10000);
	}
}

/*
 * spi_transfer_one_message - Default implementation of transfer_one_message()
 *
 * This is a standard implementation of transfer_one_message() for
 * drivers which implement a transfer_one() operation.  It provides
 * standard handling of delays and chip select management.
 */
static int spi_transfer_one_message(struct spi_controller *ctlr,
				    struct spi_message *msg)
{
	struct spi_transfer *xfer;
	bool keep_cs = false;
	int ret = 0;
	struct spi_statistics *statm = &ctlr->statistics;
	struct spi_statistics *stats = &msg->spi->statistics;

	spi_set_cs(msg->spi, true, false);

	SPI_STATISTICS_INCREMENT_FIELD(statm, messages);
	SPI_STATISTICS_INCREMENT_FIELD(stats, messages);

	list_for_each_entry(xfer, &msg->transfers, transfer_list) {
		trace_spi_transfer_start(msg, xfer);

		spi_statistics_add_transfer_stats(statm, xfer, ctlr);
		spi_statistics_add_transfer_stats(stats, xfer, ctlr);

		if (!ctlr->ptp_sts_supported) {
			xfer->ptp_sts_word_pre = 0;
			ptp_read_system_prets(xfer->ptp_sts);
		}

		if ((xfer->tx_buf || xfer->rx_buf) && xfer->len) {
			reinit_completion(&ctlr->xfer_completion);

fallback_pio:
			ret = ctlr->transfer_one(ctlr, msg->spi, xfer);
			if (ret < 0) {
				if (ctlr->cur_msg_mapped &&
				   (xfer->error & SPI_TRANS_FAIL_NO_START)) {
					__spi_unmap_msg(ctlr, msg);
					ctlr->fallback = true;
					xfer->error &= ~SPI_TRANS_FAIL_NO_START;
					goto fallback_pio;
				}

				SPI_STATISTICS_INCREMENT_FIELD(statm,
							       errors);
				SPI_STATISTICS_INCREMENT_FIELD(stats,
							       errors);
				dev_err(&msg->spi->dev,
					"SPI transfer failed: %d\n", ret);
				goto out;
			}

			if (ret > 0) {
				ret = spi_transfer_wait(ctlr, msg, xfer);
				if (ret < 0)
					msg->status = ret;
			}
		} else {
			if (xfer->len)
				dev_err(&msg->spi->dev,
					"Bufferless transfer has length %u\n",
					xfer->len);
		}

		if (!ctlr->ptp_sts_supported) {
			ptp_read_system_postts(xfer->ptp_sts);
			xfer->ptp_sts_word_post = xfer->len;
		}

		trace_spi_transfer_stop(msg, xfer);

		if (msg->status != -EINPROGRESS)
			goto out;

		spi_transfer_delay_exec(xfer);

		if (xfer->cs_change) {
			if (list_is_last(&xfer->transfer_list,
					 &msg->transfers)) {
				keep_cs = true;
			} else {
				spi_set_cs(msg->spi, false, false);
				_spi_transfer_cs_change_delay(msg, xfer);
				spi_set_cs(msg->spi, true, false);
			}
		}

		msg->actual_length += xfer->len;
	}

out:
	if (ret != 0 || !keep_cs)
		spi_set_cs(msg->spi, false, false);

	if (msg->status == -EINPROGRESS)
		msg->status = ret;

	if (msg->status && ctlr->handle_err)
		ctlr->handle_err(ctlr, msg);

	spi_finalize_current_message(ctlr);

	return ret;
}

/**
 * spi_finalize_current_transfer - report completion of a transfer
 * @ctlr: the controller reporting completion
 *
 * Called by SPI drivers using the core transfer_one_message()
 * implementation to notify it that the current interrupt driven
 * transfer has finished and the next one may be scheduled.
 */
void spi_finalize_current_transfer(struct spi_controller *ctlr)
{
	complete(&ctlr->xfer_completion);
}
EXPORT_SYMBOL_GPL(spi_finalize_current_transfer);

static void spi_idle_runtime_pm(struct spi_controller *ctlr)
{
	if (ctlr->auto_runtime_pm) {
		pm_runtime_mark_last_busy(ctlr->dev.parent);
		pm_runtime_put_autosuspend(ctlr->dev.parent);
	}
}

/**
 * __spi_pump_messages - function which processes spi message queue
 * @ctlr: controller to process queue for
 * @in_kthread: true if we are in the context of the message pump thread
 *
 * This function checks if there is any spi message in the queue that
 * needs processing and if so call out to the driver to initialize hardware
 * and transfer each message.
 *
 * Note that it is called both from the kthread itself and also from
 * inside spi_sync(); the queue extraction handling at the top of the
 * function should deal with this safely.
 */
static void __spi_pump_messages(struct spi_controller *ctlr, bool in_kthread)
{
	struct spi_transfer *xfer;
	struct spi_message *msg;
	bool was_busy = false;
	unsigned long flags;
	int ret;

	/* Lock queue */
	spin_lock_irqsave(&ctlr->queue_lock, flags);

	/* Make sure we are not already running a message */
	if (ctlr->cur_msg) {
		spin_unlock_irqrestore(&ctlr->queue_lock, flags);
		return;
	}

	/* If another context is idling the device then defer */
	if (ctlr->idling) {
		kthread_queue_work(ctlr->kworker, &ctlr->pump_messages);
		spin_unlock_irqrestore(&ctlr->queue_lock, flags);
		return;
	}

	/* Check if the queue is idle */
	if (list_empty(&ctlr->queue) || !ctlr->running) {
		if (!ctlr->busy) {
			spin_unlock_irqrestore(&ctlr->queue_lock, flags);
			return;
		}

		/* Defer any non-atomic teardown to the thread */
		if (!in_kthread) {
			if (!ctlr->dummy_rx && !ctlr->dummy_tx &&
			    !ctlr->unprepare_transfer_hardware) {
				spi_idle_runtime_pm(ctlr);
				ctlr->busy = false;
				trace_spi_controller_idle(ctlr);
			} else {
				kthread_queue_work(ctlr->kworker,
						   &ctlr->pump_messages);
			}
			spin_unlock_irqrestore(&ctlr->queue_lock, flags);
			return;
		}

		ctlr->busy = false;
		ctlr->idling = true;
		spin_unlock_irqrestore(&ctlr->queue_lock, flags);

		kfree(ctlr->dummy_rx);
		ctlr->dummy_rx = NULL;
		kfree(ctlr->dummy_tx);
		ctlr->dummy_tx = NULL;
		if (ctlr->unprepare_transfer_hardware &&
		    ctlr->unprepare_transfer_hardware(ctlr))
			dev_err(&ctlr->dev,
				"failed to unprepare transfer hardware\n");
		spi_idle_runtime_pm(ctlr);
		trace_spi_controller_idle(ctlr);

		spin_lock_irqsave(&ctlr->queue_lock, flags);
		ctlr->idling = false;
		spin_unlock_irqrestore(&ctlr->queue_lock, flags);
		return;
	}

	/* Extract head of queue */
	msg = list_first_entry(&ctlr->queue, struct spi_message, queue);
	ctlr->cur_msg = msg;

	list_del_init(&msg->queue);
	if (ctlr->busy)
		was_busy = true;
	else
		ctlr->busy = true;
	spin_unlock_irqrestore(&ctlr->queue_lock, flags);

	mutex_lock(&ctlr->io_mutex);

	if (!was_busy && ctlr->auto_runtime_pm) {
		ret = pm_runtime_get_sync(ctlr->dev.parent);
		if (ret < 0) {
			pm_runtime_put_noidle(ctlr->dev.parent);
			dev_err(&ctlr->dev, "Failed to power device: %d\n",
				ret);
			mutex_unlock(&ctlr->io_mutex);
			return;
		}
	}

	if (!was_busy)
		trace_spi_controller_busy(ctlr);

	if (!was_busy && ctlr->prepare_transfer_hardware) {
		ret = ctlr->prepare_transfer_hardware(ctlr);
		if (ret) {
			dev_err(&ctlr->dev,
				"failed to prepare transfer hardware: %d\n",
				ret);

			if (ctlr->auto_runtime_pm)
				pm_runtime_put(ctlr->dev.parent);

			msg->status = ret;
			spi_finalize_current_message(ctlr);

			mutex_unlock(&ctlr->io_mutex);
			return;
		}
	}

	trace_spi_message_start(msg);

	if (ctlr->prepare_message) {
		ret = ctlr->prepare_message(ctlr, msg);
		if (ret) {
			dev_err(&ctlr->dev, "failed to prepare message: %d\n",
				ret);
			msg->status = ret;
			spi_finalize_current_message(ctlr);
			goto out;
		}
		ctlr->cur_msg_prepared = true;
	}

	ret = spi_map_msg(ctlr, msg);
	if (ret) {
		msg->status = ret;
		spi_finalize_current_message(ctlr);
		goto out;
	}

	if (!ctlr->ptp_sts_supported && !ctlr->transfer_one) {
		list_for_each_entry(xfer, &msg->transfers, transfer_list) {
			xfer->ptp_sts_word_pre = 0;
			ptp_read_system_prets(xfer->ptp_sts);
		}
	}

	ret = ctlr->transfer_one_message(ctlr, msg);
	if (ret) {
		dev_err(&ctlr->dev,
			"failed to transfer one message from queue\n");
		goto out;
	}

out:
	mutex_unlock(&ctlr->io_mutex);

	/* Prod the scheduler in case transfer_one() was busy waiting */
	if (!ret)
		cond_resched();
}

/**
 * spi_pump_messages - kthread work function which processes spi message queue
 * @work: pointer to kthread work struct contained in the controller struct
 */
static void spi_pump_messages(struct kthread_work *work)
{
	struct spi_controller *ctlr =
		container_of(work, struct spi_controller, pump_messages);

	__spi_pump_messages(ctlr, true);
}

/**
 * spi_take_timestamp_pre - helper for drivers to collect the beginning of the
 *			    TX timestamp for the requested byte from the SPI
 *			    transfer. The frequency with which this function
 *			    must be called (once per word, once for the whole
 *			    transfer, once per batch of words etc) is arbitrary
 *			    as long as the @tx buffer offset is greater than or
 *			    equal to the requested byte at the time of the
 *			    call. The timestamp is only taken once, at the
 *			    first such call. It is assumed that the driver
 *			    advances its @tx buffer pointer monotonically.
 * @ctlr: Pointer to the spi_controller structure of the driver
 * @xfer: Pointer to the transfer being timestamped
 * @progress: How many words (not bytes) have been transferred so far
 * @irqs_off: If true, will disable IRQs and preemption for the duration of the
 *	      transfer, for less jitter in time measurement. Only compatible
 *	      with PIO drivers. If true, must follow up with
 *	      spi_take_timestamp_post or otherwise system will crash.
 *	      WARNING: for fully predictable results, the CPU frequency must
 *	      also be under control (governor).
 */
void spi_take_timestamp_pre(struct spi_controller *ctlr,
			    struct spi_transfer *xfer,
			    size_t progress, bool irqs_off)
{
	if (!xfer->ptp_sts)
		return;

	if (xfer->timestamped)
		return;

	if (progress > xfer->ptp_sts_word_pre)
		return;

	/* Capture the resolution of the timestamp */
	xfer->ptp_sts_word_pre = progress;

	if (irqs_off) {
		local_irq_save(ctlr->irq_flags);
		preempt_disable();
	}

	ptp_read_system_prets(xfer->ptp_sts);
}
EXPORT_SYMBOL_GPL(spi_take_timestamp_pre);

/**
 * spi_take_timestamp_post - helper for drivers to collect the end of the
 *			     TX timestamp for the requested byte from the SPI
 *			     transfer. Can be called with an arbitrary
 *			     frequency: only the first call where @tx exceeds
 *			     or is equal to the requested word will be
 *			     timestamped.
 * @ctlr: Pointer to the spi_controller structure of the driver
 * @xfer: Pointer to the transfer being timestamped
 * @progress: How many words (not bytes) have been transferred so far
 * @irqs_off: If true, will re-enable IRQs and preemption for the local CPU.
 */
void spi_take_timestamp_post(struct spi_controller *ctlr,
			     struct spi_transfer *xfer,
			     size_t progress, bool irqs_off)
{
	if (!xfer->ptp_sts)
		return;

	if (xfer->timestamped)
		return;

	if (progress < xfer->ptp_sts_word_post)
		return;

	ptp_read_system_postts(xfer->ptp_sts);

	if (irqs_off) {
		local_irq_restore(ctlr->irq_flags);
		preempt_enable();
	}

	/* Capture the resolution of the timestamp */
	xfer->ptp_sts_word_post = progress;

	xfer->timestamped = true;
}
EXPORT_SYMBOL_GPL(spi_take_timestamp_post);

/**
 * spi_set_thread_rt - set the controller to pump at realtime priority
 * @ctlr: controller to boost priority of
 *
 * This can be called because the controller requested realtime priority
 * (by setting the ->rt value before calling spi_register_controller()) or
 * because a device on the bus said that its transfers needed realtime
 * priority.
 *
 * NOTE: at the moment if any device on a bus says it needs realtime then
 * the thread will be at realtime priority for all transfers on that
 * controller.  If this eventually becomes a problem we may see if we can
 * find a way to boost the priority only temporarily during relevant
 * transfers.
 */
static void spi_set_thread_rt(struct spi_controller *ctlr)
{
	dev_info(&ctlr->dev,
		"will run message pump with realtime priority\n");
	sched_set_fifo(ctlr->kworker->task);
}

static int spi_init_queue(struct spi_controller *ctlr)
{
	ctlr->running = false;
	ctlr->busy = false;

	ctlr->kworker = kthread_create_worker(0, dev_name(&ctlr->dev));
	if (IS_ERR(ctlr->kworker)) {
		dev_err(&ctlr->dev, "failed to create message pump kworker\n");
		return PTR_ERR(ctlr->kworker);
	}

	kthread_init_work(&ctlr->pump_messages, spi_pump_messages);

	/*
	 * Controller config will indicate if this controller should run the
	 * message pump with high (realtime) priority to reduce the transfer
	 * latency on the bus by minimising the delay between a transfer
	 * request and the scheduling of the message pump thread. Without this
	 * setting the message pump thread will remain at default priority.
	 */
	if (ctlr->rt)
		spi_set_thread_rt(ctlr);

	return 0;
}

/**
 * spi_get_next_queued_message() - called by driver to check for queued
 * messages
 * @ctlr: the controller to check for queued messages
 *
 * If there are more messages in the queue, the next message is returned from
 * this call.
 *
 * Return: the next message in the queue, else NULL if the queue is empty.
 */
struct spi_message *spi_get_next_queued_message(struct spi_controller *ctlr)
{
	struct spi_message *next;
	unsigned long flags;

	/* get a pointer to the next message, if any */
	spin_lock_irqsave(&ctlr->queue_lock, flags);
	next = list_first_entry_or_null(&ctlr->queue, struct spi_message,
					queue);
	spin_unlock_irqrestore(&ctlr->queue_lock, flags);

	return next;
}
EXPORT_SYMBOL_GPL(spi_get_next_queued_message);

/**
 * spi_finalize_current_message() - the current message is complete
 * @ctlr: the controller to return the message to
 *
 * Called by the driver to notify the core that the message in the front of the
 * queue is complete and can be removed from the queue.
 */
void spi_finalize_current_message(struct spi_controller *ctlr)
{
	struct spi_transfer *xfer;
	struct spi_message *mesg;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&ctlr->queue_lock, flags);
	mesg = ctlr->cur_msg;
	spin_unlock_irqrestore(&ctlr->queue_lock, flags);

	if (!ctlr->ptp_sts_supported && !ctlr->transfer_one) {
		list_for_each_entry(xfer, &mesg->transfers, transfer_list) {
			ptp_read_system_postts(xfer->ptp_sts);
			xfer->ptp_sts_word_post = xfer->len;
		}
	}

	if (unlikely(ctlr->ptp_sts_supported))
		list_for_each_entry(xfer, &mesg->transfers, transfer_list)
			WARN_ON_ONCE(xfer->ptp_sts && !xfer->timestamped);

	spi_unmap_msg(ctlr, mesg);

	/* In the prepare_messages callback the spi bus has the opportunity to
	 * split a transfer to smaller chunks.
	 * Release splited transfers here since spi_map_msg is done on the
	 * splited transfers.
	 */
	spi_res_release(ctlr, mesg);

	if (ctlr->cur_msg_prepared && ctlr->unprepare_message) {
		ret = ctlr->unprepare_message(ctlr, mesg);
		if (ret) {
			dev_err(&ctlr->dev, "failed to unprepare message: %d\n",
				ret);
		}
	}

	spin_lock_irqsave(&ctlr->queue_lock, flags);
	ctlr->cur_msg = NULL;
	ctlr->cur_msg_prepared = false;
	ctlr->fallback = false;
	kthread_queue_work(ctlr->kworker, &ctlr->pump_messages);
	spin_unlock_irqrestore(&ctlr->queue_lock, flags);

	trace_spi_message_done(mesg);

	mesg->state = NULL;
	if (mesg->complete)
		mesg->complete(mesg->context);
}
EXPORT_SYMBOL_GPL(spi_finalize_current_message);

static int spi_start_queue(struct spi_controller *ctlr)
{
	unsigned long flags;

	spin_lock_irqsave(&ctlr->queue_lock, flags);

	if (ctlr->running || ctlr->busy) {
		spin_unlock_irqrestore(&ctlr->queue_lock, flags);
		return -EBUSY;
	}

	ctlr->running = true;
	ctlr->cur_msg = NULL;
	spin_unlock_irqrestore(&ctlr->queue_lock, flags);

	kthread_queue_work(ctlr->kworker, &ctlr->pump_messages);

	return 0;
}

static int spi_stop_queue(struct spi_controller *ctlr)
{
	unsigned long flags;
	unsigned limit = 500;
	int ret = 0;

	spin_lock_irqsave(&ctlr->queue_lock, flags);

	/*
	 * This is a bit lame, but is optimized for the common execution path.
	 * A wait_queue on the ctlr->busy could be used, but then the common
	 * execution path (pump_messages) would be required to call wake_up or
	 * friends on every SPI message. Do this instead.
	 */
	while ((!list_empty(&ctlr->queue) || ctlr->busy) && limit--) {
		spin_unlock_irqrestore(&ctlr->queue_lock, flags);
		usleep_range(10000, 11000);
		spin_lock_irqsave(&ctlr->queue_lock, flags);
	}

	if (!list_empty(&ctlr->queue) || ctlr->busy)
		ret = -EBUSY;
	else
		ctlr->running = false;

	spin_unlock_irqrestore(&ctlr->queue_lock, flags);

	if (ret) {
		dev_warn(&ctlr->dev, "could not stop message queue\n");
		return ret;
	}
	return ret;
}

static int spi_destroy_queue(struct spi_controller *ctlr)
{
	int ret;

	ret = spi_stop_queue(ctlr);

	/*
	 * kthread_flush_worker will block until all work is done.
	 * If the reason that stop_queue timed out is that the work will never
	 * finish, then it does no good to call flush/stop thread, so
	 * return anyway.
	 */
	if (ret) {
		dev_err(&ctlr->dev, "problem destroying queue\n");
		return ret;
	}

	kthread_destroy_worker(ctlr->kworker);

	return 0;
}

static int __spi_queued_transfer(struct spi_device *spi,
				 struct spi_message *msg,
				 bool need_pump)
{
	struct spi_controller *ctlr = spi->controller;
	unsigned long flags;

	spin_lock_irqsave(&ctlr->queue_lock, flags);

	if (!ctlr->running) {
		spin_unlock_irqrestore(&ctlr->queue_lock, flags);
		return -ESHUTDOWN;
	}
	msg->actual_length = 0;
	msg->status = -EINPROGRESS;

	list_add_tail(&msg->queue, &ctlr->queue);
	if (!ctlr->busy && need_pump)
		kthread_queue_work(ctlr->kworker, &ctlr->pump_messages);

	spin_unlock_irqrestore(&ctlr->queue_lock, flags);
	return 0;
}

/**
 * spi_queued_transfer - transfer function for queued transfers
 * @spi: spi device which is requesting transfer
 * @msg: spi message which is to handled is queued to driver queue
 *
 * Return: zero on success, else a negative error code.
 */
static int spi_queued_transfer(struct spi_device *spi, struct spi_message *msg)
{
	return __spi_queued_transfer(spi, msg, true);
}

static int spi_controller_initialize_queue(struct spi_controller *ctlr)
{
	int ret;

	ctlr->transfer = spi_queued_transfer;
	if (!ctlr->transfer_one_message)
		ctlr->transfer_one_message = spi_transfer_one_message;

	/* Initialize and start queue */
	ret = spi_init_queue(ctlr);
	if (ret) {
		dev_err(&ctlr->dev, "problem initializing queue\n");
		goto err_init_queue;
	}
	ctlr->queued = true;
	ret = spi_start_queue(ctlr);
	if (ret) {
		dev_err(&ctlr->dev, "problem starting queue\n");
		goto err_start_queue;
	}

	return 0;

err_start_queue:
	spi_destroy_queue(ctlr);
err_init_queue:
	return ret;
}

/**
 * spi_flush_queue - Send all pending messages in the queue from the callers'
 *		     context
 * @ctlr: controller to process queue for
 *
 * This should be used when one wants to ensure all pending messages have been
 * sent before doing something. Is used by the spi-mem code to make sure SPI
 * memory operations do not preempt regular SPI transfers that have been queued
 * before the spi-mem operation.
 */
void spi_flush_queue(struct spi_controller *ctlr)
{
	if (ctlr->transfer == spi_queued_transfer)
		__spi_pump_messages(ctlr, false);
}

/*-------------------------------------------------------------------------*/

#if defined(CONFIG_OF)
static int of_spi_parse_dt(struct spi_controller *ctlr, struct spi_device *spi,
			   struct device_node *nc)
{
	u32 value;
	int rc;

	/* Mode (clock phase/polarity/etc.) */
	if (of_property_read_bool(nc, "spi-cpha"))
		spi->mode |= SPI_CPHA;
	if (of_property_read_bool(nc, "spi-cpol"))
		spi->mode |= SPI_CPOL;
	if (of_property_read_bool(nc, "spi-3wire"))
		spi->mode |= SPI_3WIRE;
	if (of_property_read_bool(nc, "spi-lsb-first"))
		spi->mode |= SPI_LSB_FIRST;
	if (of_property_read_bool(nc, "spi-cs-high"))
		spi->mode |= SPI_CS_HIGH;

	/* Device DUAL/QUAD mode */
	if (!of_property_read_u32(nc, "spi-tx-bus-width", &value)) {
		switch (value) {
		case 1:
			break;
		case 2:
			spi->mode |= SPI_TX_DUAL;
			break;
		case 4:
			spi->mode |= SPI_TX_QUAD;
			break;
		case 8:
			spi->mode |= SPI_TX_OCTAL;
			break;
		default:
			dev_warn(&ctlr->dev,
				"spi-tx-bus-width %d not supported\n",
				value);
			break;
		}
	}

	if (!of_property_read_u32(nc, "spi-rx-bus-width", &value)) {
		switch (value) {
		case 1:
			break;
		case 2:
			spi->mode |= SPI_RX_DUAL;
			break;
		case 4:
			spi->mode |= SPI_RX_QUAD;
			break;
		case 8:
			spi->mode |= SPI_RX_OCTAL;
			break;
		default:
			dev_warn(&ctlr->dev,
				"spi-rx-bus-width %d not supported\n",
				value);
			break;
		}
	}

	if (spi_controller_is_slave(ctlr)) {
		if (!of_node_name_eq(nc, "slave")) {
			dev_err(&ctlr->dev, "%pOF is not called 'slave'\n",
				nc);
			return -EINVAL;
		}
		return 0;
	}

	/* Device address */
	rc = of_property_read_u32(nc, "reg", &value);
	if (rc) {
		dev_err(&ctlr->dev, "%pOF has no valid 'reg' property (%d)\n",
			nc, rc);
		return rc;
	}
	spi->chip_select = value;

	/* Device speed */
	if (!of_property_read_u32(nc, "spi-max-frequency", &value))
		spi->max_speed_hz = value;

	return 0;
}

static struct spi_device *
of_register_spi_device(struct spi_controller *ctlr, struct device_node *nc)
{
	struct spi_device *spi;
	int rc;

	/* Alloc an spi_device */
	spi = spi_alloc_device(ctlr);
	if (!spi) {
		dev_err(&ctlr->dev, "spi_device alloc error for %pOF\n", nc);
		rc = -ENOMEM;
		goto err_out;
	}

	/* Select device driver */
	rc = of_modalias_node(nc, spi->modalias,
				sizeof(spi->modalias));
	if (rc < 0) {
		dev_err(&ctlr->dev, "cannot find modalias for %pOF\n", nc);
		goto err_out;
	}

	rc = of_spi_parse_dt(ctlr, spi, nc);
	if (rc)
		goto err_out;

	/* Store a pointer to the node in the device structure */
	of_node_get(nc);
	spi->dev.of_node = nc;
	spi->dev.fwnode = of_fwnode_handle(nc);

	/* Register the new device */
	rc = spi_add_device(spi);
	if (rc) {
		dev_err(&ctlr->dev, "spi_device register error %pOF\n", nc);
		goto err_of_node_put;
	}

	return spi;

err_of_node_put:
	of_node_put(nc);
err_out:
	spi_dev_put(spi);
	return ERR_PTR(rc);
}

/**
 * of_register_spi_devices() - Register child devices onto the SPI bus
 * @ctlr:	Pointer to spi_controller device
 *
 * Registers an spi_device for each child node of controller node which
 * represents a valid SPI slave.
 */
static void of_register_spi_devices(struct spi_controller *ctlr)
{
	struct spi_device *spi;
	struct device_node *nc;

	if (!ctlr->dev.of_node)
		return;

	for_each_available_child_of_node(ctlr->dev.of_node, nc) {
		if (of_node_test_and_set_flag(nc, OF_POPULATED))
			continue;
		spi = of_register_spi_device(ctlr, nc);
		if (IS_ERR(spi)) {
			dev_warn(&ctlr->dev,
				 "Failed to create SPI device for %pOF\n", nc);
			of_node_clear_flag(nc, OF_POPULATED);
		}
	}
}
#else
static void of_register_spi_devices(struct spi_controller *ctlr) { }
#endif

#ifdef CONFIG_ACPI
struct acpi_spi_lookup {
	struct spi_controller 	*ctlr;
	u32			max_speed_hz;
	u32			mode;
	int			irq;
	u8			bits_per_word;
	u8			chip_select;
};

static void acpi_spi_parse_apple_properties(struct acpi_device *dev,
					    struct acpi_spi_lookup *lookup)
{
	const union acpi_object *obj;

	if (!x86_apple_machine)
		return;

	if (!acpi_dev_get_property(dev, "spiSclkPeriod", ACPI_TYPE_BUFFER, &obj)
	    && obj->buffer.length >= 4)
		lookup->max_speed_hz  = NSEC_PER_SEC / *(u32 *)obj->buffer.pointer;

	if (!acpi_dev_get_property(dev, "spiWordSize", ACPI_TYPE_BUFFER, &obj)
	    && obj->buffer.length == 8)
		lookup->bits_per_word = *(u64 *)obj->buffer.pointer;

	if (!acpi_dev_get_property(dev, "spiBitOrder", ACPI_TYPE_BUFFER, &obj)
	    && obj->buffer.length == 8 && !*(u64 *)obj->buffer.pointer)
		lookup->mode |= SPI_LSB_FIRST;

	if (!acpi_dev_get_property(dev, "spiSPO", ACPI_TYPE_BUFFER, &obj)
	    && obj->buffer.length == 8 &&  *(u64 *)obj->buffer.pointer)
		lookup->mode |= SPI_CPOL;

	if (!acpi_dev_get_property(dev, "spiSPH", ACPI_TYPE_BUFFER, &obj)
	    && obj->buffer.length == 8 &&  *(u64 *)obj->buffer.pointer)
		lookup->mode |= SPI_CPHA;
}

static int acpi_spi_add_resource(struct acpi_resource *ares, void *data)
{
	struct acpi_spi_lookup *lookup = data;
	struct spi_controller *ctlr = lookup->ctlr;

	if (ares->type == ACPI_RESOURCE_TYPE_SERIAL_BUS) {
		struct acpi_resource_spi_serialbus *sb;
		acpi_handle parent_handle;
		acpi_status status;

		sb = &ares->data.spi_serial_bus;
		if (sb->type == ACPI_RESOURCE_SERIAL_TYPE_SPI) {

			status = acpi_get_handle(NULL,
						 sb->resource_source.string_ptr,
						 &parent_handle);

			if (ACPI_FAILURE(status) ||
			    ACPI_HANDLE(ctlr->dev.parent) != parent_handle)
				return -ENODEV;

			/*
			 * ACPI DeviceSelection numbering is handled by the
			 * host controller driver in Windows and can vary
			 * from driver to driver. In Linux we always expect
			 * 0 .. max - 1 so we need to ask the driver to
			 * translate between the two schemes.
			 */
			if (ctlr->fw_translate_cs) {
				int cs = ctlr->fw_translate_cs(ctlr,
						sb->device_selection);
				if (cs < 0)
					return cs;
				lookup->chip_select = cs;
			} else {
				lookup->chip_select = sb->device_selection;
			}

			lookup->max_speed_hz = sb->connection_speed;
			lookup->bits_per_word = sb->data_bit_length;

			if (sb->clock_phase == ACPI_SPI_SECOND_PHASE)
				lookup->mode |= SPI_CPHA;
			if (sb->clock_polarity == ACPI_SPI_START_HIGH)
				lookup->mode |= SPI_CPOL;
			if (sb->device_polarity == ACPI_SPI_ACTIVE_HIGH)
				lookup->mode |= SPI_CS_HIGH;
		}
	} else if (lookup->irq < 0) {
		struct resource r;

		if (acpi_dev_resource_interrupt(ares, 0, &r))
			lookup->irq = r.start;
	}

	/* Always tell the ACPI core to skip this resource */
	return 1;
}

static acpi_status acpi_register_spi_device(struct spi_controller *ctlr,
					    struct acpi_device *adev)
{
	acpi_handle parent_handle = NULL;
	struct list_head resource_list;
	struct acpi_spi_lookup lookup = {};
	struct spi_device *spi;
	int ret;

	if (acpi_bus_get_status(adev) || !adev->status.present ||
	    acpi_device_enumerated(adev))
		return AE_OK;

	lookup.ctlr		= ctlr;
	lookup.irq		= -1;

	INIT_LIST_HEAD(&resource_list);
	ret = acpi_dev_get_resources(adev, &resource_list,
				     acpi_spi_add_resource, &lookup);
	acpi_dev_free_resource_list(&resource_list);

	if (ret < 0)
		/* found SPI in _CRS but it points to another controller */
		return AE_OK;

	if (!lookup.max_speed_hz &&
	    !ACPI_FAILURE(acpi_get_parent(adev->handle, &parent_handle)) &&
	    ACPI_HANDLE(ctlr->dev.parent) == parent_handle) {
		/* Apple does not use _CRS but nested devices for SPI slaves */
		acpi_spi_parse_apple_properties(adev, &lookup);
	}

	if (!lookup.max_speed_hz)
		return AE_OK;

	spi = spi_alloc_device(ctlr);
	if (!spi) {
		dev_err(&ctlr->dev, "failed to allocate SPI device for %s\n",
			dev_name(&adev->dev));
		return AE_NO_MEMORY;
	}


	ACPI_COMPANION_SET(&spi->dev, adev);
	spi->max_speed_hz	= lookup.max_speed_hz;
	spi->mode		|= lookup.mode;
	spi->irq		= lookup.irq;
	spi->bits_per_word	= lookup.bits_per_word;
	spi->chip_select	= lookup.chip_select;

	acpi_set_modalias(adev, acpi_device_hid(adev), spi->modalias,
			  sizeof(spi->modalias));

	if (spi->irq < 0)
		spi->irq = acpi_dev_gpio_irq_get(adev, 0);

	acpi_device_set_enumerated(adev);

	adev->power.flags.ignore_parent = true;
	if (spi_add_device(spi)) {
		adev->power.flags.ignore_parent = false;
		dev_err(&ctlr->dev, "failed to add SPI device %s from ACPI\n",
			dev_name(&adev->dev));
		spi_dev_put(spi);
	}

	return AE_OK;
}

static acpi_status acpi_spi_add_device(acpi_handle handle, u32 level,
				       void *data, void **return_value)
{
	struct spi_controller *ctlr = data;
	struct acpi_device *adev;

	if (acpi_bus_get_device(handle, &adev))
		return AE_OK;

	return acpi_register_spi_device(ctlr, adev);
}

#define SPI_ACPI_ENUMERATE_MAX_DEPTH		32

static void acpi_register_spi_devices(struct spi_controller *ctlr)
{
	acpi_status status;
	acpi_handle handle;

	handle = ACPI_HANDLE(ctlr->dev.parent);
	if (!handle)
		return;

	status = acpi_walk_namespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT,
				     SPI_ACPI_ENUMERATE_MAX_DEPTH,
				     acpi_spi_add_device, NULL, ctlr, NULL);
	if (ACPI_FAILURE(status))
		dev_warn(&ctlr->dev, "failed to enumerate SPI slaves\n");
}
#else
static inline void acpi_register_spi_devices(struct spi_controller *ctlr) {}
#endif /* CONFIG_ACPI */

static void spi_controller_release(struct device *dev)
{
	struct spi_controller *ctlr;

	ctlr = container_of(dev, struct spi_controller, dev);
	kfree(ctlr);
}

static struct class spi_master_class = {
	.name		= "spi_master",
	.owner		= THIS_MODULE,
	.dev_release	= spi_controller_release,
	.dev_groups	= spi_master_groups,
};

#ifdef CONFIG_SPI_SLAVE
/**
 * spi_slave_abort - abort the ongoing transfer request on an SPI slave
 *		     controller
 * @spi: device used for the current transfer
 */
int spi_slave_abort(struct spi_device *spi)
{
	struct spi_controller *ctlr = spi->controller;

	if (spi_controller_is_slave(ctlr) && ctlr->slave_abort)
		return ctlr->slave_abort(ctlr);

	return -ENOTSUPP;
}
EXPORT_SYMBOL_GPL(spi_slave_abort);

static int match_true(struct device *dev, void *data)
{
	return 1;
}

static ssize_t slave_show(struct device *dev, struct device_attribute *attr,
			  char *buf)
{
	struct spi_controller *ctlr = container_of(dev, struct spi_controller,
						   dev);
	struct device *child;

	child = device_find_child(&ctlr->dev, NULL, match_true);
	return sprintf(buf, "%s\n",
		       child ? to_spi_device(child)->modalias : NULL);
}

static ssize_t slave_store(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct spi_controller *ctlr = container_of(dev, struct spi_controller,
						   dev);
	struct spi_device *spi;
	struct device *child;
	char name[32];
	int rc;

	rc = sscanf(buf, "%31s", name);
	if (rc != 1 || !name[0])
		return -EINVAL;

	child = device_find_child(&ctlr->dev, NULL, match_true);
	if (child) {
		/* Remove registered slave */
		device_unregister(child);
		put_device(child);
	}

	if (strcmp(name, "(null)")) {
		/* Register new slave */
		spi = spi_alloc_device(ctlr);
		if (!spi)
			return -ENOMEM;

		strlcpy(spi->modalias, name, sizeof(spi->modalias));

		rc = spi_add_device(spi);
		if (rc) {
			spi_dev_put(spi);
			return rc;
		}
	}

	return count;
}

static DEVICE_ATTR_RW(slave);

static struct attribute *spi_slave_attrs[] = {
	&dev_attr_slave.attr,
	NULL,
};

static const struct attribute_group spi_slave_group = {
	.attrs = spi_slave_attrs,
};

static const struct attribute_group *spi_slave_groups[] = {
	&spi_controller_statistics_group,
	&spi_slave_group,
	NULL,
};

static struct class spi_slave_class = {
	.name		= "spi_slave",
	.owner		= THIS_MODULE,
	.dev_release	= spi_controller_release,
	.dev_groups	= spi_slave_groups,
};
#else
extern struct class spi_slave_class;	/* dummy */
#endif

/**
 * __spi_alloc_controller - allocate an SPI master or slave controller
 * @dev: the controller, possibly using the platform_bus
 * @size: how much zeroed driver-private data to allocate; the pointer to this
 *	memory is in the driver_data field of the returned device, accessible
 *	with spi_controller_get_devdata(); the memory is cacheline aligned;
 *	drivers granting DMA access to portions of their private data need to
 *	round up @size using ALIGN(size, dma_get_cache_alignment()).
 * @slave: flag indicating whether to allocate an SPI master (false) or SPI
 *	slave (true) controller
 * Context: can sleep
 *
 * This call is used only by SPI controller drivers, which are the
 * only ones directly touching chip registers.  It's how they allocate
 * an spi_controller structure, prior to calling spi_register_controller().
 *
 * This must be called from context that can sleep.
 *
 * The caller is responsible for assigning the bus number and initializing the
 * controller's methods before calling spi_register_controller(); and (after
 * errors adding the device) calling spi_controller_put() to prevent a memory
 * leak.
 *
 * Return: the SPI controller structure on success, else NULL.
 */
struct spi_controller *__spi_alloc_controller(struct device *dev,
					      unsigned int size, bool slave)
{
	struct spi_controller	*ctlr;
	size_t ctlr_size = ALIGN(sizeof(*ctlr), dma_get_cache_alignment());

	if (!dev)
		return NULL;

	ctlr = kzalloc(size + ctlr_size, GFP_KERNEL);
	if (!ctlr)
		return NULL;

	device_initialize(&ctlr->dev);
	ctlr->bus_num = -1;
	ctlr->num_chipselect = 1;
	ctlr->slave = slave;
	if (IS_ENABLED(CONFIG_SPI_SLAVE) && slave)
		ctlr->dev.class = &spi_slave_class;
	else
		ctlr->dev.class = &spi_master_class;
	ctlr->dev.parent = dev;
	pm_suspend_ignore_children(&ctlr->dev, true);
	spi_controller_set_devdata(ctlr, (void *)ctlr + ctlr_size);

	return ctlr;
}
EXPORT_SYMBOL_GPL(__spi_alloc_controller);

static void devm_spi_release_controller(struct device *dev, void *ctlr)
{
	spi_controller_put(*(struct spi_controller **)ctlr);
}

/**
 * __devm_spi_alloc_controller - resource-managed __spi_alloc_controller()
 * @dev: physical device of SPI controller
 * @size: how much zeroed driver-private data to allocate
 * @slave: whether to allocate an SPI master (false) or SPI slave (true)
 * Context: can sleep
 *
 * Allocate an SPI controller and automatically release a reference on it
 * when @dev is unbound from its driver.  Drivers are thus relieved from
 * having to call spi_controller_put().
 *
 * The arguments to this function are identical to __spi_alloc_controller().
 *
 * Return: the SPI controller structure on success, else NULL.
 */
struct spi_controller *__devm_spi_alloc_controller(struct device *dev,
						   unsigned int size,
						   bool slave)
{
	struct spi_controller **ptr, *ctlr;

	ptr = devres_alloc(devm_spi_release_controller, sizeof(*ptr),
			   GFP_KERNEL);
	if (!ptr)
		return NULL;

	ctlr = __spi_alloc_controller(dev, size, slave);
	if (ctlr) {
		ctlr->devm_allocated = true;
		*ptr = ctlr;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return ctlr;
}
EXPORT_SYMBOL_GPL(__devm_spi_alloc_controller);

#ifdef CONFIG_OF
static int of_spi_get_gpio_numbers(struct spi_controller *ctlr)
{
	int nb, i, *cs;
	struct device_node *np = ctlr->dev.of_node;

	if (!np)
		return 0;

	nb = of_gpio_named_count(np, "cs-gpios");
	ctlr->num_chipselect = max_t(int, nb, ctlr->num_chipselect);

	/* Return error only for an incorrectly formed cs-gpios property */
	if (nb == 0 || nb == -ENOENT)
		return 0;
	else if (nb < 0)
		return nb;

	cs = devm_kcalloc(&ctlr->dev, ctlr->num_chipselect, sizeof(int),
			  GFP_KERNEL);
	ctlr->cs_gpios = cs;

	if (!ctlr->cs_gpios)
		return -ENOMEM;

	for (i = 0; i < ctlr->num_chipselect; i++)
		cs[i] = -ENOENT;

	for (i = 0; i < nb; i++)
		cs[i] = of_get_named_gpio(np, "cs-gpios", i);

	return 0;
}
#else
static int of_spi_get_gpio_numbers(struct spi_controller *ctlr)
{
	return 0;
}
#endif

/**
 * spi_get_gpio_descs() - grab chip select GPIOs for the master
 * @ctlr: The SPI master to grab GPIO descriptors for
 */
static int spi_get_gpio_descs(struct spi_controller *ctlr)
{
	int nb, i;
	struct gpio_desc **cs;
	struct device *dev = &ctlr->dev;
	unsigned long native_cs_mask = 0;
	unsigned int num_cs_gpios = 0;

	nb = gpiod_count(dev, "cs");
	ctlr->num_chipselect = max_t(int, nb, ctlr->num_chipselect);

	/* No GPIOs at all is fine, else return the error */
	if (nb == 0 || nb == -ENOENT)
		return 0;
	else if (nb < 0)
		return nb;

	cs = devm_kcalloc(dev, ctlr->num_chipselect, sizeof(*cs),
			  GFP_KERNEL);
	if (!cs)
		return -ENOMEM;
	ctlr->cs_gpiods = cs;

	for (i = 0; i < nb; i++) {
		/*
		 * Most chipselects are active low, the inverted
		 * semantics are handled by special quirks in gpiolib,
		 * so initializing them GPIOD_OUT_LOW here means
		 * "unasserted", in most cases this will drive the physical
		 * line high.
		 */
		cs[i] = devm_gpiod_get_index_optional(dev, "cs", i,
						      GPIOD_OUT_LOW);
		if (IS_ERR(cs[i]))
			return PTR_ERR(cs[i]);

		if (cs[i]) {
			/*
			 * If we find a CS GPIO, name it after the device and
			 * chip select line.
			 */
			char *gpioname;

			gpioname = devm_kasprintf(dev, GFP_KERNEL, "%s CS%d",
						  dev_name(dev), i);
			if (!gpioname)
				return -ENOMEM;
			gpiod_set_consumer_name(cs[i], gpioname);
			num_cs_gpios++;
			continue;
		}

		if (ctlr->max_native_cs && i >= ctlr->max_native_cs) {
			dev_err(dev, "Invalid native chip select %d\n", i);
			return -EINVAL;
		}
		native_cs_mask |= BIT(i);
	}

	ctlr->unused_native_cs = ffs(~native_cs_mask) - 1;

	if ((ctlr->flags & SPI_MASTER_GPIO_SS) && num_cs_gpios &&
	    ctlr->max_native_cs && ctlr->unused_native_cs >= ctlr->max_native_cs) {
		dev_err(dev, "No unused native chip select available\n");
		return -EINVAL;
	}

	return 0;
}

static int spi_controller_check_ops(struct spi_controller *ctlr)
{
	/*
	 * The controller may implement only the high-level SPI-memory like
	 * operations if it does not support regular SPI transfers, and this is
	 * valid use case.
	 * If ->mem_ops is NULL, we request that at least one of the
	 * ->transfer_xxx() method be implemented.
	 */
	if (ctlr->mem_ops) {
		if (!ctlr->mem_ops->exec_op)
			return -EINVAL;
	} else if (!ctlr->transfer && !ctlr->transfer_one &&
		   !ctlr->transfer_one_message) {
		return -EINVAL;
	}

	return 0;
}

/**
 * spi_register_controller - register SPI master or slave controller
 * @ctlr: initialized master, originally from spi_alloc_master() or
 *	spi_alloc_slave()
 * Context: can sleep
 *
 * SPI controllers connect to their drivers using some non-SPI bus,
 * such as the platform bus.  The final stage of probe() in that code
 * includes calling spi_register_controller() to hook up to this SPI bus glue.
 *
 * SPI controllers use board specific (often SOC specific) bus numbers,
 * and board-specific addressing for SPI devices combines those numbers
 * with chip select numbers.  Since SPI does not directly support dynamic
 * device identification, boards need configuration tables telling which
 * chip is at which address.
 *
 * This must be called from context that can sleep.  It returns zero on
 * success, else a negative error code (dropping the controller's refcount).
 * After a successful return, the caller is responsible for calling
 * spi_unregister_controller().
 *
 * Return: zero on success, else a negative error code.
 */
int spi_register_controller(struct spi_controller *ctlr)
{
	struct device		*dev = ctlr->dev.parent;
	struct boardinfo	*bi;
	int			status;
	int			id, first_dynamic;

	if (!dev)
		return -ENODEV;

	/*
	 * Make sure all necessary hooks are implemented before registering
	 * the SPI controller.
	 */
	status = spi_controller_check_ops(ctlr);
	if (status)
		return status;

	if (ctlr->bus_num >= 0) {
		/* devices with a fixed bus num must check-in with the num */
		mutex_lock(&board_lock);
		id = idr_alloc(&spi_master_idr, ctlr, ctlr->bus_num,
			ctlr->bus_num + 1, GFP_KERNEL);
		mutex_unlock(&board_lock);
		if (WARN(id < 0, "couldn't get idr"))
			return id == -ENOSPC ? -EBUSY : id;
		ctlr->bus_num = id;
	} else if (ctlr->dev.of_node) {
		/* allocate dynamic bus number using Linux idr */
		id = of_alias_get_id(ctlr->dev.of_node, "spi");
		if (id >= 0) {
			ctlr->bus_num = id;
			mutex_lock(&board_lock);
			id = idr_alloc(&spi_master_idr, ctlr, ctlr->bus_num,
				       ctlr->bus_num + 1, GFP_KERNEL);
			mutex_unlock(&board_lock);
			if (WARN(id < 0, "couldn't get idr"))
				return id == -ENOSPC ? -EBUSY : id;
		}
	}
	if (ctlr->bus_num < 0) {
		first_dynamic = of_alias_get_highest_id("spi");
		if (first_dynamic < 0)
			first_dynamic = 0;
		else
			first_dynamic++;

		mutex_lock(&board_lock);
		id = idr_alloc(&spi_master_idr, ctlr, first_dynamic,
			       0, GFP_KERNEL);
		mutex_unlock(&board_lock);
		if (WARN(id < 0, "couldn't get idr"))
			return id;
		ctlr->bus_num = id;
	}
	INIT_LIST_HEAD(&ctlr->queue);
	spin_lock_init(&ctlr->queue_lock);
	spin_lock_init(&ctlr->bus_lock_spinlock);
	mutex_init(&ctlr->bus_lock_mutex);
	mutex_init(&ctlr->io_mutex);
	ctlr->bus_lock_flag = 0;
	init_completion(&ctlr->xfer_completion);
	if (!ctlr->max_dma_len)
		ctlr->max_dma_len = INT_MAX;

	/* register the device, then userspace will see it.
	 * registration fails if the bus ID is in use.
	 */
	dev_set_name(&ctlr->dev, "spi%u", ctlr->bus_num);

	if (!spi_controller_is_slave(ctlr)) {
		if (ctlr->use_gpio_descriptors) {
			status = spi_get_gpio_descs(ctlr);
			if (status)
				goto free_bus_id;
			/*
			 * A controller using GPIO descriptors always
			 * supports SPI_CS_HIGH if need be.
			 */
			ctlr->mode_bits |= SPI_CS_HIGH;
		} else {
			/* Legacy code path for GPIOs from DT */
			status = of_spi_get_gpio_numbers(ctlr);
			if (status)
				goto free_bus_id;
		}
	}

	/*
	 * Even if it's just one always-selected device, there must
	 * be at least one chipselect.
	 */
	if (!ctlr->num_chipselect) {
		status = -EINVAL;
		goto free_bus_id;
	}

	status = device_add(&ctlr->dev);
	if (status < 0)
		goto free_bus_id;
	dev_dbg(dev, "registered %s %s\n",
			spi_controller_is_slave(ctlr) ? "slave" : "master",
			dev_name(&ctlr->dev));

	/*
	 * If we're using a queued driver, start the queue. Note that we don't
	 * need the queueing logic if the driver is only supporting high-level
	 * memory operations.
	 */
	if (ctlr->transfer) {
		dev_info(dev, "controller is unqueued, this is deprecated\n");
	} else if (ctlr->transfer_one || ctlr->transfer_one_message) {
		status = spi_controller_initialize_queue(ctlr);
		if (status) {
			device_del(&ctlr->dev);
			goto free_bus_id;
		}
	}
	/* add statistics */
	spin_lock_init(&ctlr->statistics.lock);

	mutex_lock(&board_lock);
	list_add_tail(&ctlr->list, &spi_controller_list);
	list_for_each_entry(bi, &board_list, list)
		spi_match_controller_to_boardinfo(ctlr, &bi->board_info);
	mutex_unlock(&board_lock);

	/* Register devices from the device tree and ACPI */
	of_register_spi_devices(ctlr);
	acpi_register_spi_devices(ctlr);
	return status;

free_bus_id:
	mutex_lock(&board_lock);
	idr_remove(&spi_master_idr, ctlr->bus_num);
	mutex_unlock(&board_lock);
	return status;
}
EXPORT_SYMBOL_GPL(spi_register_controller);

static void devm_spi_unregister(struct device *dev, void *res)
{
	spi_unregister_controller(*(struct spi_controller **)res);
}

/**
 * devm_spi_register_controller - register managed SPI master or slave
 *	controller
 * @dev:    device managing SPI controller
 * @ctlr: initialized controller, originally from spi_alloc_master() or
 *	spi_alloc_slave()
 * Context: can sleep
 *
 * Register a SPI device as with spi_register_controller() which will
 * automatically be unregistered and freed.
 *
 * Return: zero on success, else a negative error code.
 */
int devm_spi_register_controller(struct device *dev,
				 struct spi_controller *ctlr)
{
	struct spi_controller **ptr;
	int ret;

	ptr = devres_alloc(devm_spi_unregister, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return -ENOMEM;

	ret = spi_register_controller(ctlr);
	if (!ret) {
		*ptr = ctlr;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return ret;
}
EXPORT_SYMBOL_GPL(devm_spi_register_controller);

static int __unregister(struct device *dev, void *null)
{
	spi_unregister_device(to_spi_device(dev));
	return 0;
}

/**
 * spi_unregister_controller - unregister SPI master or slave controller
 * @ctlr: the controller being unregistered
 * Context: can sleep
 *
 * This call is used only by SPI controller drivers, which are the
 * only ones directly touching chip registers.
 *
 * This must be called from context that can sleep.
 *
 * Note that this function also drops a reference to the controller.
 */
void spi_unregister_controller(struct spi_controller *ctlr)
{
	struct spi_controller *found;
	int id = ctlr->bus_num;

	/* Prevent addition of new devices, unregister existing ones */
	if (IS_ENABLED(CONFIG_SPI_DYNAMIC))
		mutex_lock(&spi_add_lock);

	device_for_each_child(&ctlr->dev, NULL, __unregister);

	/* First make sure that this controller was ever added */
	mutex_lock(&board_lock);
	found = idr_find(&spi_master_idr, id);
	mutex_unlock(&board_lock);
	if (ctlr->queued) {
		if (spi_destroy_queue(ctlr))
			dev_err(&ctlr->dev, "queue remove failed\n");
	}
	mutex_lock(&board_lock);
	list_del(&ctlr->list);
	mutex_unlock(&board_lock);

	device_del(&ctlr->dev);

	/* Release the last reference on the controller if its driver
	 * has not yet been converted to devm_spi_alloc_master/slave().
	 */
	if (!ctlr->devm_allocated)
		put_device(&ctlr->dev);

	/* free bus id */
	mutex_lock(&board_lock);
	if (found == ctlr)
		idr_remove(&spi_master_idr, id);
	mutex_unlock(&board_lock);

	if (IS_ENABLED(CONFIG_SPI_DYNAMIC))
		mutex_unlock(&spi_add_lock);
}
EXPORT_SYMBOL_GPL(spi_unregister_controller);

int spi_controller_suspend(struct spi_controller *ctlr)
{
	int ret;

	/* Basically no-ops for non-queued controllers */
	if (!ctlr->queued)
		return 0;

	ret = spi_stop_queue(ctlr);
	if (ret)
		dev_err(&ctlr->dev, "queue stop failed\n");

	return ret;
}
EXPORT_SYMBOL_GPL(spi_controller_suspend);

int spi_controller_resume(struct spi_controller *ctlr)
{
	int ret;

	if (!ctlr->queued)
		return 0;

	ret = spi_start_queue(ctlr);
	if (ret)
		dev_err(&ctlr->dev, "queue restart failed\n");

	return ret;
}
EXPORT_SYMBOL_GPL(spi_controller_resume);

static int __spi_controller_match(struct device *dev, const void *data)
{
	struct spi_controller *ctlr;
	const u16 *bus_num = data;

	ctlr = container_of(dev, struct spi_controller, dev);
	return ctlr->bus_num == *bus_num;
}

/**
 * spi_busnum_to_master - look up master associated with bus_num
 * @bus_num: the master's bus number
 * Context: can sleep
 *
 * This call may be used with devices that are registered after
 * arch init time.  It returns a refcounted pointer to the relevant
 * spi_controller (which the caller must release), or NULL if there is
 * no such master registered.
 *
 * Return: the SPI master structure on success, else NULL.
 */
struct spi_controller *spi_busnum_to_master(u16 bus_num)
{
	struct device		*dev;
	struct spi_controller	*ctlr = NULL;

	dev = class_find_device(&spi_master_class, NULL, &bus_num,
				__spi_controller_match);
	if (dev)
		ctlr = container_of(dev, struct spi_controller, dev);
	/* reference got in class_find_device */
	return ctlr;
}
EXPORT_SYMBOL_GPL(spi_busnum_to_master);

/*-------------------------------------------------------------------------*/

/* Core methods for SPI resource management */

/**
 * spi_res_alloc - allocate a spi resource that is life-cycle managed
 *                 during the processing of a spi_message while using
 *                 spi_transfer_one
 * @spi:     the spi device for which we allocate memory
 * @release: the release code to execute for this resource
 * @size:    size to alloc and return
 * @gfp:     GFP allocation flags
 *
 * Return: the pointer to the allocated data
 *
 * This may get enhanced in the future to allocate from a memory pool
 * of the @spi_device or @spi_controller to avoid repeated allocations.
 */
void *spi_res_alloc(struct spi_device *spi,
		    spi_res_release_t release,
		    size_t size, gfp_t gfp)
{
	struct spi_res *sres;

	sres = kzalloc(sizeof(*sres) + size, gfp);
	if (!sres)
		return NULL;

	INIT_LIST_HEAD(&sres->entry);
	sres->release = release;

	return sres->data;
}
EXPORT_SYMBOL_GPL(spi_res_alloc);

/**
 * spi_res_free - free an spi resource
 * @res: pointer to the custom data of a resource
 *
 */
void spi_res_free(void *res)
{
	struct spi_res *sres = container_of(res, struct spi_res, data);

	if (!res)
		return;

	WARN_ON(!list_empty(&sres->entry));
	kfree(sres);
}
EXPORT_SYMBOL_GPL(spi_res_free);

/**
 * spi_res_add - add a spi_res to the spi_message
 * @message: the spi message
 * @res:     the spi_resource
 */
void spi_res_add(struct spi_message *message, void *res)
{
	struct spi_res *sres = container_of(res, struct spi_res, data);

	WARN_ON(!list_empty(&sres->entry));
	list_add_tail(&sres->entry, &message->resources);
}
EXPORT_SYMBOL_GPL(spi_res_add);

/**
 * spi_res_release - release all spi resources for this message
 * @ctlr:  the @spi_controller
 * @message: the @spi_message
 */
void spi_res_release(struct spi_controller *ctlr, struct spi_message *message)
{
	struct spi_res *res, *tmp;

	list_for_each_entry_safe_reverse(res, tmp, &message->resources, entry) {
		if (res->release)
			res->release(ctlr, message, res->data);

		list_del(&res->entry);

		kfree(res);
	}
}
EXPORT_SYMBOL_GPL(spi_res_release);

/*-------------------------------------------------------------------------*/

/* Core methods for spi_message alterations */

static void __spi_replace_transfers_release(struct spi_controller *ctlr,
					    struct spi_message *msg,
					    void *res)
{
	struct spi_replaced_transfers *rxfer = res;
	size_t i;

	/* call extra callback if requested */
	if (rxfer->release)
		rxfer->release(ctlr, msg, res);

	/* insert replaced transfers back into the message */
	list_splice(&rxfer->replaced_transfers, rxfer->replaced_after);

	/* remove the formerly inserted entries */
	for (i = 0; i < rxfer->inserted; i++)
		list_del(&rxfer->inserted_transfers[i].transfer_list);
}

/**
 * spi_replace_transfers - replace transfers with several transfers
 *                         and register change with spi_message.resources
 * @msg:           the spi_message we work upon
 * @xfer_first:    the first spi_transfer we want to replace
 * @remove:        number of transfers to remove
 * @insert:        the number of transfers we want to insert instead
 * @release:       extra release code necessary in some circumstances
 * @extradatasize: extra data to allocate (with alignment guarantees
 *                 of struct @spi_transfer)
 * @gfp:           gfp flags
 *
 * Returns: pointer to @spi_replaced_transfers,
 *          PTR_ERR(...) in case of errors.
 */
struct spi_replaced_transfers *spi_replace_transfers(
	struct spi_message *msg,
	struct spi_transfer *xfer_first,
	size_t remove,
	size_t insert,
	spi_replaced_release_t release,
	size_t extradatasize,
	gfp_t gfp)
{
	struct spi_replaced_transfers *rxfer;
	struct spi_transfer *xfer;
	size_t i;

	/* allocate the structure using spi_res */
	rxfer = spi_res_alloc(msg->spi, __spi_replace_transfers_release,
			      struct_size(rxfer, inserted_transfers, insert)
			      + extradatasize,
			      gfp);
	if (!rxfer)
		return ERR_PTR(-ENOMEM);

	/* the release code to invoke before running the generic release */
	rxfer->release = release;

	/* assign extradata */
	if (extradatasize)
		rxfer->extradata =
			&rxfer->inserted_transfers[insert];

	/* init the replaced_transfers list */
	INIT_LIST_HEAD(&rxfer->replaced_transfers);

	/* assign the list_entry after which we should reinsert
	 * the @replaced_transfers - it may be spi_message.messages!
	 */
	rxfer->replaced_after = xfer_first->transfer_list.prev;

	/* remove the requested number of transfers */
	for (i = 0; i < remove; i++) {
		/* if the entry after replaced_after it is msg->transfers
		 * then we have been requested to remove more transfers
		 * than are in the list
		 */
		if (rxfer->replaced_after->next == &msg->transfers) {
			dev_err(&msg->spi->dev,
				"requested to remove more spi_transfers than are available\n");
			/* insert replaced transfers back into the message */
			list_splice(&rxfer->replaced_transfers,
				    rxfer->replaced_after);

			/* free the spi_replace_transfer structure */
			spi_res_free(rxfer);

			/* and return with an error */
			return ERR_PTR(-EINVAL);
		}

		/* remove the entry after replaced_after from list of
		 * transfers and add it to list of replaced_transfers
		 */
		list_move_tail(rxfer->replaced_after->next,
			       &rxfer->replaced_transfers);
	}

	/* create copy of the given xfer with identical settings
	 * based on the first transfer to get removed
	 */
	for (i = 0; i < insert; i++) {
		/* we need to run in reverse order */
		xfer = &rxfer->inserted_transfers[insert - 1 - i];

		/* copy all spi_transfer data */
		memcpy(xfer, xfer_first, sizeof(*xfer));

		/* add to list */
		list_add(&xfer->transfer_list, rxfer->replaced_after);

		/* clear cs_change and delay for all but the last */
		if (i) {
			xfer->cs_change = false;
			xfer->delay_usecs = 0;
			xfer->delay.value = 0;
		}
	}

	/* set up inserted */
	rxfer->inserted = insert;

	/* and register it with spi_res/spi_message */
	spi_res_add(msg, rxfer);

	return rxfer;
}
EXPORT_SYMBOL_GPL(spi_replace_transfers);

static int __spi_split_transfer_maxsize(struct spi_controller *ctlr,
					struct spi_message *msg,
					struct spi_transfer **xferp,
					size_t maxsize,
					gfp_t gfp)
{
	struct spi_transfer *xfer = *xferp, *xfers;
	struct spi_replaced_transfers *srt;
	size_t offset;
	size_t count, i;

	/* calculate how many we have to replace */
	count = DIV_ROUND_UP(xfer->len, maxsize);

	/* create replacement */
	srt = spi_replace_transfers(msg, xfer, 1, count, NULL, 0, gfp);
	if (IS_ERR(srt))
		return PTR_ERR(srt);
	xfers = srt->inserted_transfers;

	/* now handle each of those newly inserted spi_transfers
	 * note that the replacements spi_transfers all are preset
	 * to the same values as *xferp, so tx_buf, rx_buf and len
	 * are all identical (as well as most others)
	 * so we just have to fix up len and the pointers.
	 *
	 * this also includes support for the depreciated
	 * spi_message.is_dma_mapped interface
	 */

	/* the first transfer just needs the length modified, so we
	 * run it outside the loop
	 */
	xfers[0].len = min_t(size_t, maxsize, xfer[0].len);

	/* all the others need rx_buf/tx_buf also set */
	for (i = 1, offset = maxsize; i < count; offset += maxsize, i++) {
		/* update rx_buf, tx_buf and dma */
		if (xfers[i].rx_buf)
			xfers[i].rx_buf += offset;
		if (xfers[i].rx_dma)
			xfers[i].rx_dma += offset;
		if (xfers[i].tx_buf)
			xfers[i].tx_buf += offset;
		if (xfers[i].tx_dma)
			xfers[i].tx_dma += offset;

		/* update length */
		xfers[i].len = min(maxsize, xfers[i].len - offset);
	}

	/* we set up xferp to the last entry we have inserted,
	 * so that we skip those already split transfers
	 */
	*xferp = &xfers[count - 1];

	/* increment statistics counters */
	SPI_STATISTICS_INCREMENT_FIELD(&ctlr->statistics,
				       transfers_split_maxsize);
	SPI_STATISTICS_INCREMENT_FIELD(&msg->spi->statistics,
				       transfers_split_maxsize);

	return 0;
}

/**
 * spi_split_tranfers_maxsize - split spi transfers into multiple transfers
 *                              when an individual transfer exceeds a
 *                              certain size
 * @ctlr:    the @spi_controller for this transfer
 * @msg:   the @spi_message to transform
 * @maxsize:  the maximum when to apply this
 * @gfp: GFP allocation flags
 *
 * Return: status of transformation
 */
int spi_split_transfers_maxsize(struct spi_controller *ctlr,
				struct spi_message *msg,
				size_t maxsize,
				gfp_t gfp)
{
	struct spi_transfer *xfer;
	int ret;

	/* iterate over the transfer_list,
	 * but note that xfer is advanced to the last transfer inserted
	 * to avoid checking sizes again unnecessarily (also xfer does
	 * potentiall belong to a different list by the time the
	 * replacement has happened
	 */
	list_for_each_entry(xfer, &msg->transfers, transfer_list) {
		if (xfer->len > maxsize) {
			ret = __spi_split_transfer_maxsize(ctlr, msg, &xfer,
							   maxsize, gfp);
			if (ret)
				return ret;
		}
	}

	return 0;
}
EXPORT_SYMBOL_GPL(spi_split_transfers_maxsize);

/*-------------------------------------------------------------------------*/

/* Core methods for SPI controller protocol drivers.  Some of the
 * other core methods are currently defined as inline functions.
 */

static int __spi_validate_bits_per_word(struct spi_controller *ctlr,
					u8 bits_per_word)
{
	if (ctlr->bits_per_word_mask) {
		/* Only 32 bits fit in the mask */
		if (bits_per_word > 32)
			return -EINVAL;
		if (!(ctlr->bits_per_word_mask & SPI_BPW_MASK(bits_per_word)))
			return -EINVAL;
	}

	return 0;
}

/**
 * spi_setup - setup SPI mode and clock rate
 * @spi: the device whose settings are being modified
 * Context: can sleep, and no requests are queued to the device
 *
 * SPI protocol drivers may need to update the transfer mode if the
 * device doesn't work with its default.  They may likewise need
 * to update clock rates or word sizes from initial values.  This function
 * changes those settings, and must be called from a context that can sleep.
 * Except for SPI_CS_HIGH, which takes effect immediately, the changes take
 * effect the next time the device is selected and data is transferred to
 * or from it.  When this function returns, the spi device is deselected.
 *
 * Note that this call will fail if the protocol driver specifies an option
 * that the underlying controller or its driver does not support.  For
 * example, not all hardware supports wire transfers using nine bit words,
 * LSB-first wire encoding, or active-high chipselects.
 *
 * Return: zero on success, else a negative error code.
 */
int spi_setup(struct spi_device *spi)
{
	unsigned	bad_bits, ugly_bits;
	int		status;

	/* check mode to prevent that DUAL and QUAD set at the same time
	 */
	if (((spi->mode & SPI_TX_DUAL) && (spi->mode & SPI_TX_QUAD)) ||
		((spi->mode & SPI_RX_DUAL) && (spi->mode & SPI_RX_QUAD))) {
		dev_err(&spi->dev,
		"setup: can not select dual and quad at the same time\n");
		return -EINVAL;
	}
	/* if it is SPI_3WIRE mode, DUAL and QUAD should be forbidden
	 */
	if ((spi->mode & SPI_3WIRE) && (spi->mode &
		(SPI_TX_DUAL | SPI_TX_QUAD | SPI_TX_OCTAL |
		 SPI_RX_DUAL | SPI_RX_QUAD | SPI_RX_OCTAL)))
		return -EINVAL;
	/* help drivers fail *cleanly* when they need options
	 * that aren't supported with their current controller
	 * SPI_CS_WORD has a fallback software implementation,
	 * so it is ignored here.
	 */
	bad_bits = spi->mode & ~(spi->controller->mode_bits | SPI_CS_WORD);
	/* nothing prevents from working with active-high CS in case if it
	 * is driven by GPIO.
	 */
	if (gpio_is_valid(spi->cs_gpio))
		bad_bits &= ~SPI_CS_HIGH;
	ugly_bits = bad_bits &
		    (SPI_TX_DUAL | SPI_TX_QUAD | SPI_TX_OCTAL |
		     SPI_RX_DUAL | SPI_RX_QUAD | SPI_RX_OCTAL);
	if (ugly_bits) {
		dev_warn(&spi->dev,
			 "setup: ignoring unsupported mode bits %x\n",
			 ugly_bits);
		spi->mode &= ~ugly_bits;
		bad_bits &= ~ugly_bits;
	}
	if (bad_bits) {
		dev_err(&spi->dev, "setup: unsupported mode bits %x\n",
			bad_bits);
		return -EINVAL;
	}

	if (!spi->bits_per_word)
		spi->bits_per_word = 8;

	status = __spi_validate_bits_per_word(spi->controller,
					      spi->bits_per_word);
	if (status)
		return status;

	if (!spi->max_speed_hz)
		spi->max_speed_hz = spi->controller->max_speed_hz;

	mutex_lock(&spi->controller->io_mutex);

	if (spi->controller->setup)
		status = spi->controller->setup(spi);

	if (spi->controller->auto_runtime_pm && spi->controller->set_cs) {
		status = pm_runtime_get_sync(spi->controller->dev.parent);
		if (status < 0) {
			mutex_unlock(&spi->controller->io_mutex);
			pm_runtime_put_noidle(spi->controller->dev.parent);
			dev_err(&spi->controller->dev, "Failed to power device: %d\n",
				status);
			return status;
		}

		/*
		 * We do not want to return positive value from pm_runtime_get,
		 * there are many instances of devices calling spi_setup() and
		 * checking for a non-zero return value instead of a negative
		 * return value.
		 */
		status = 0;

		spi_set_cs(spi, false, true);
		pm_runtime_mark_last_busy(spi->controller->dev.parent);
		pm_runtime_put_autosuspend(spi->controller->dev.parent);
	} else {
		spi_set_cs(spi, false, true);
	}

	mutex_unlock(&spi->controller->io_mutex);

	if (spi->rt && !spi->controller->rt) {
		spi->controller->rt = true;
		spi_set_thread_rt(spi->controller);
	}

	dev_dbg(&spi->dev, "setup mode %d, %s%s%s%s%u bits/w, %u Hz max --> %d\n",
			(int) (spi->mode & (SPI_CPOL | SPI_CPHA)),
			(spi->mode & SPI_CS_HIGH) ? "cs_high, " : "",
			(spi->mode & SPI_LSB_FIRST) ? "lsb, " : "",
			(spi->mode & SPI_3WIRE) ? "3wire, " : "",
			(spi->mode & SPI_LOOP) ? "loopback, " : "",
			spi->bits_per_word, spi->max_speed_hz,
			status);

	return status;
}
EXPORT_SYMBOL_GPL(spi_setup);

/**
 * spi_set_cs_timing - configure CS setup, hold, and inactive delays
 * @spi: the device that requires specific CS timing configuration
 * @setup: CS setup time specified via @spi_delay
 * @hold: CS hold time specified via @spi_delay
 * @inactive: CS inactive delay between transfers specified via @spi_delay
 *
 * Return: zero on success, else a negative error code.
 */
int spi_set_cs_timing(struct spi_device *spi, struct spi_delay *setup,
		      struct spi_delay *hold, struct spi_delay *inactive)
{
	size_t len;

	if (spi->controller->set_cs_timing)
		return spi->controller->set_cs_timing(spi, setup, hold,
						      inactive);

	if ((setup && setup->unit == SPI_DELAY_UNIT_SCK) ||
	    (hold && hold->unit == SPI_DELAY_UNIT_SCK) ||
	    (inactive && inactive->unit == SPI_DELAY_UNIT_SCK)) {
		dev_err(&spi->dev,
			"Clock-cycle delays for CS not supported in SW mode\n");
		return -ENOTSUPP;
	}

	len = sizeof(struct spi_delay);

	/* copy delays to controller */
	if (setup)
		memcpy(&spi->controller->cs_setup, setup, len);
	else
		memset(&spi->controller->cs_setup, 0, len);

	if (hold)
		memcpy(&spi->controller->cs_hold, hold, len);
	else
		memset(&spi->controller->cs_hold, 0, len);

	if (inactive)
		memcpy(&spi->controller->cs_inactive, inactive, len);
	else
		memset(&spi->controller->cs_inactive, 0, len);

	return 0;
}
EXPORT_SYMBOL_GPL(spi_set_cs_timing);

static int _spi_xfer_word_delay_update(struct spi_transfer *xfer,
				       struct spi_device *spi)
{
	int delay1, delay2;

	delay1 = spi_delay_to_ns(&xfer->word_delay, xfer);
	if (delay1 < 0)
		return delay1;

	delay2 = spi_delay_to_ns(&spi->word_delay, xfer);
	if (delay2 < 0)
		return delay2;

	if (delay1 < delay2)
		memcpy(&xfer->word_delay, &spi->word_delay,
		       sizeof(xfer->word_delay));

	return 0;
}

static int __spi_validate(struct spi_device *spi, struct spi_message *message)
{
	struct spi_controller *ctlr = spi->controller;
	struct spi_transfer *xfer;
	int w_size;

	if (list_empty(&message->transfers))
		return -EINVAL;

	/* If an SPI controller does not support toggling the CS line on each
	 * transfer (indicated by the SPI_CS_WORD flag) or we are using a GPIO
	 * for the CS line, we can emulate the CS-per-word hardware function by
	 * splitting transfers into one-word transfers and ensuring that
	 * cs_change is set for each transfer.
	 */
	if ((spi->mode & SPI_CS_WORD) && (!(ctlr->mode_bits & SPI_CS_WORD) ||
					  spi->cs_gpiod ||
					  gpio_is_valid(spi->cs_gpio))) {
		size_t maxsize;
		int ret;

		maxsize = (spi->bits_per_word + 7) / 8;

		/* spi_split_transfers_maxsize() requires message->spi */
		message->spi = spi;

		ret = spi_split_transfers_maxsize(ctlr, message, maxsize,
						  GFP_KERNEL);
		if (ret)
			return ret;

		list_for_each_entry(xfer, &message->transfers, transfer_list) {
			/* don't change cs_change on the last entry in the list */
			if (list_is_last(&xfer->transfer_list, &message->transfers))
				break;
			xfer->cs_change = 1;
		}
	}

	/* Half-duplex links include original MicroWire, and ones with
	 * only one data pin like SPI_3WIRE (switches direction) or where
	 * either MOSI or MISO is missing.  They can also be caused by
	 * software limitations.
	 */
	if ((ctlr->flags & SPI_CONTROLLER_HALF_DUPLEX) ||
	    (spi->mode & SPI_3WIRE)) {
		unsigned flags = ctlr->flags;

		list_for_each_entry(xfer, &message->transfers, transfer_list) {
			if (xfer->rx_buf && xfer->tx_buf)
				return -EINVAL;
			if ((flags & SPI_CONTROLLER_NO_TX) && xfer->tx_buf)
				return -EINVAL;
			if ((flags & SPI_CONTROLLER_NO_RX) && xfer->rx_buf)
				return -EINVAL;
		}
	}

	/**
	 * Set transfer bits_per_word and max speed as spi device default if
	 * it is not set for this transfer.
	 * Set transfer tx_nbits and rx_nbits as single transfer default
	 * (SPI_NBITS_SINGLE) if it is not set for this transfer.
	 * Ensure transfer word_delay is at least as long as that required by
	 * device itself.
	 */
	message->frame_length = 0;
	list_for_each_entry(xfer, &message->transfers, transfer_list) {
		xfer->effective_speed_hz = 0;
		message->frame_length += xfer->len;
		if (!xfer->bits_per_word)
			xfer->bits_per_word = spi->bits_per_word;

		if (!xfer->speed_hz)
			xfer->speed_hz = spi->max_speed_hz;

		if (ctlr->max_speed_hz && xfer->speed_hz > ctlr->max_speed_hz)
			xfer->speed_hz = ctlr->max_speed_hz;

		if (__spi_validate_bits_per_word(ctlr, xfer->bits_per_word))
			return -EINVAL;

		/*
		 * SPI transfer length should be multiple of SPI word size
		 * where SPI word size should be power-of-two multiple
		 */
		if (xfer->bits_per_word <= 8)
			w_size = 1;
		else if (xfer->bits_per_word <= 16)
			w_size = 2;
		else
			w_size = 4;

		/* No partial transfers accepted */
		if (xfer->len % w_size)
			return -EINVAL;

		if (xfer->speed_hz && ctlr->min_speed_hz &&
		    xfer->speed_hz < ctlr->min_speed_hz)
			return -EINVAL;

		if (xfer->tx_buf && !xfer->tx_nbits)
			xfer->tx_nbits = SPI_NBITS_SINGLE;
		if (xfer->rx_buf && !xfer->rx_nbits)
			xfer->rx_nbits = SPI_NBITS_SINGLE;
		/* check transfer tx/rx_nbits:
		 * 1. check the value matches one of single, dual and quad
		 * 2. check tx/rx_nbits match the mode in spi_device
		 */
		if (xfer->tx_buf) {
			if (xfer->tx_nbits != SPI_NBITS_SINGLE &&
				xfer->tx_nbits != SPI_NBITS_DUAL &&
				xfer->tx_nbits != SPI_NBITS_QUAD)
				return -EINVAL;
			if ((xfer->tx_nbits == SPI_NBITS_DUAL) &&
				!(spi->mode & (SPI_TX_DUAL | SPI_TX_QUAD)))
				return -EINVAL;
			if ((xfer->tx_nbits == SPI_NBITS_QUAD) &&
				!(spi->mode & SPI_TX_QUAD))
				return -EINVAL;
		}
		/* check transfer rx_nbits */
		if (xfer->rx_buf) {
			if (xfer->rx_nbits != SPI_NBITS_SINGLE &&
				xfer->rx_nbits != SPI_NBITS_DUAL &&
				xfer->rx_nbits != SPI_NBITS_QUAD)
				return -EINVAL;
			if ((xfer->rx_nbits == SPI_NBITS_DUAL) &&
				!(spi->mode & (SPI_RX_DUAL | SPI_RX_QUAD)))
				return -EINVAL;
			if ((xfer->rx_nbits == SPI_NBITS_QUAD) &&
				!(spi->mode & SPI_RX_QUAD))
				return -EINVAL;
		}

		if (_spi_xfer_word_delay_update(xfer, spi))
			return -EINVAL;
	}

	message->status = -EINPROGRESS;

	return 0;
}

static int __spi_async(struct spi_device *spi, struct spi_message *message)
{
	struct spi_controller *ctlr = spi->controller;
	struct spi_transfer *xfer;

	/*
	 * Some controllers do not support doing regular SPI transfers. Return
	 * ENOTSUPP when this is the case.
	 */
	if (!ctlr->transfer)
		return -ENOTSUPP;

	message->spi = spi;

	SPI_STATISTICS_INCREMENT_FIELD(&ctlr->statistics, spi_async);
	SPI_STATISTICS_INCREMENT_FIELD(&spi->statistics, spi_async);

	trace_spi_message_submit(message);

	if (!ctlr->ptp_sts_supported) {
		list_for_each_entry(xfer, &message->transfers, transfer_list) {
			xfer->ptp_sts_word_pre = 0;
			ptp_read_system_prets(xfer->ptp_sts);
		}
	}

	return ctlr->transfer(spi, message);
}

/**
 * spi_async - asynchronous SPI transfer
 * @spi: device with which data will be exchanged
 * @message: describes the data transfers, including completion callback
 * Context: any (irqs may be blocked, etc)
 *
 * This call may be used in_irq and other contexts which can't sleep,
 * as well as from task contexts which can sleep.
 *
 * The completion callback is invoked in a context which can't sleep.
 * Before that invocation, the value of message->status is undefined.
 * When the callback is issued, message->status holds either zero (to
 * indicate complete success) or a negative error code.  After that
 * callback returns, the driver which issued the transfer request may
 * deallocate the associated memory; it's no longer in use by any SPI
 * core or controller driver code.
 *
 * Note that although all messages to a spi_device are handled in
 * FIFO order, messages may go to different devices in other orders.
 * Some device might be higher priority, or have various "hard" access
 * time requirements, for example.
 *
 * On detection of any fault during the transfer, processing of
 * the entire message is aborted, and the device is deselected.
 * Until returning from the associated message completion callback,
 * no other spi_message queued to that device will be processed.
 * (This rule applies equally to all the synchronous transfer calls,
 * which are wrappers around this core asynchronous primitive.)
 *
 * Return: zero on success, else a negative error code.
 */
int spi_async(struct spi_device *spi, struct spi_message *message)
{
	struct spi_controller *ctlr = spi->controller;
	int ret;
	unsigned long flags;

	ret = __spi_validate(spi, message);
	if (ret != 0)
		return ret;

	spin_lock_irqsave(&ctlr->bus_lock_spinlock, flags);

	if (ctlr->bus_lock_flag)
		ret = -EBUSY;
	else
		ret = __spi_async(spi, message);

	spin_unlock_irqrestore(&ctlr->bus_lock_spinlock, flags);

	return ret;
}
EXPORT_SYMBOL_GPL(spi_async);

/**
 * spi_async_locked - version of spi_async with exclusive bus usage
 * @spi: device with which data will be exchanged
 * @message: describes the data transfers, including completion callback
 * Context: any (irqs may be blocked, etc)
 *
 * This call may be used in_irq and other contexts which can't sleep,
 * as well as from task contexts which can sleep.
 *
 * The completion callback is invoked in a context which can't sleep.
 * Before that invocation, the value of message->status is undefined.
 * When the callback is issued, message->status holds either zero (to
 * indicate complete success) or a negative error code.  After that
 * callback returns, the driver which issued the transfer request may
 * deallocate the associated memory; it's no longer in use by any SPI
 * core or controller driver code.
 *
 * Note that although all messages to a spi_device are handled in
 * FIFO order, messages may go to different devices in other orders.
 * Some device might be higher priority, or have various "hard" access
 * time requirements, for example.
 *
 * On detection of any fault during the transfer, processing of
 * the entire message is aborted, and the device is deselected.
 * Until returning from the associated message completion callback,
 * no other spi_message queued to that device will be processed.
 * (This rule applies equally to all the synchronous transfer calls,
 * which are wrappers around this core asynchronous primitive.)
 *
 * Return: zero on success, else a negative error code.
 */
int spi_async_locked(struct spi_device *spi, struct spi_message *message)
{
	struct spi_controller *ctlr = spi->controller;
	int ret;
	unsigned long flags;

	ret = __spi_validate(spi, message);
	if (ret != 0)
		return ret;

	spin_lock_irqsave(&ctlr->bus_lock_spinlock, flags);

	ret = __spi_async(spi, message);

	spin_unlock_irqrestore(&ctlr->bus_lock_spinlock, flags);

	return ret;

}
EXPORT_SYMBOL_GPL(spi_async_locked);

/*-------------------------------------------------------------------------*/

/* Utility methods for SPI protocol drivers, layered on
 * top of the core.  Some other utility methods are defined as
 * inline functions.
 */

static void spi_complete(void *arg)
{
	complete(arg);
}

static int __spi_sync(struct spi_device *spi, struct spi_message *message)
{
	DECLARE_COMPLETION_ONSTACK(done);
	int status;
	struct spi_controller *ctlr = spi->controller;
	unsigned long flags;

	status = __spi_validate(spi, message);
	if (status != 0)
		return status;

	message->complete = spi_complete;
	message->context = &done;
	message->spi = spi;

	SPI_STATISTICS_INCREMENT_FIELD(&ctlr->statistics, spi_sync);
	SPI_STATISTICS_INCREMENT_FIELD(&spi->statistics, spi_sync);

	/* If we're not using the legacy transfer method then we will
	 * try to transfer in the calling context so special case.
	 * This code would be less tricky if we could remove the
	 * support for driver implemented message queues.
	 */
	if (ctlr->transfer == spi_queued_transfer) {
		spin_lock_irqsave(&ctlr->bus_lock_spinlock, flags);

		trace_spi_message_submit(message);

		status = __spi_queued_transfer(spi, message, false);

		spin_unlock_irqrestore(&ctlr->bus_lock_spinlock, flags);
	} else {
		status = spi_async_locked(spi, message);
	}

	if (status == 0) {
		/* Push out the messages in the calling context if we
		 * can.
		 */
		if (ctlr->transfer == spi_queued_transfer) {
			SPI_STATISTICS_INCREMENT_FIELD(&ctlr->statistics,
						       spi_sync_immediate);
			SPI_STATISTICS_INCREMENT_FIELD(&spi->statistics,
						       spi_sync_immediate);
			__spi_pump_messages(ctlr, false);
		}

		wait_for_completion(&done);
		status = message->status;
	}
	message->context = NULL;
	return status;
}

/**
 * spi_sync - blocking/synchronous SPI data transfers
 * @spi: device with which data will be exchanged
 * @message: describes the data transfers
 * Context: can sleep
 *
 * This call may only be used from a context that may sleep.  The sleep
 * is non-interruptible, and has no timeout.  Low-overhead controller
 * drivers may DMA directly into and out of the message buffers.
 *
 * Note that the SPI device's chip select is active during the message,
 * and then is normally disabled between messages.  Drivers for some
 * frequently-used devices may want to minimize costs of selecting a chip,
 * by leaving it selected in anticipation that the next message will go
 * to the same chip.  (That may increase power usage.)
 *
 * Also, the caller is guaranteeing that the memory associated with the
 * message will not be freed before this call returns.
 *
 * Return: zero on success, else a negative error code.
 */
int spi_sync(struct spi_device *spi, struct spi_message *message)
{
	int ret;

	mutex_lock(&spi->controller->bus_lock_mutex);
	ret = __spi_sync(spi, message);
	mutex_unlock(&spi->controller->bus_lock_mutex);

	return ret;
}
EXPORT_SYMBOL_GPL(spi_sync);

/**
 * spi_sync_locked - version of spi_sync with exclusive bus usage
 * @spi: device with which data will be exchanged
 * @message: describes the data transfers
 * Context: can sleep
 *
 * This call may only be used from a context that may sleep.  The sleep
 * is non-interruptible, and has no timeout.  Low-overhead controller
 * drivers may DMA directly into and out of the message buffers.
 *
 * This call should be used by drivers that require exclusive access to the
 * SPI bus. It has to be preceded by a spi_bus_lock call. The SPI bus must
 * be released by a spi_bus_unlock call when the exclusive access is over.
 *
 * Return: zero on success, else a negative error code.
 */
int spi_sync_locked(struct spi_device *spi, struct spi_message *message)
{
	return __spi_sync(spi, message);
}
EXPORT_SYMBOL_GPL(spi_sync_locked);

/**
 * spi_bus_lock - obtain a lock for exclusive SPI bus usage
 * @ctlr: SPI bus master that should be locked for exclusive bus access
 * Context: can sleep
 *
 * This call may only be used from a context that may sleep.  The sleep
 * is non-interruptible, and has no timeout.
 *
 * This call should be used by drivers that require exclusive access to the
 * SPI bus. The SPI bus must be released by a spi_bus_unlock call when the
 * exclusive access is over. Data transfer must be done by spi_sync_locked
 * and spi_async_locked calls when the SPI bus lock is held.
 *
 * Return: always zero.
 */
int spi_bus_lock(struct spi_controller *ctlr)
{
	unsigned long flags;

	mutex_lock(&ctlr->bus_lock_mutex);

	spin_lock_irqsave(&ctlr->bus_lock_spinlock, flags);
	ctlr->bus_lock_flag = 1;
	spin_unlock_irqrestore(&ctlr->bus_lock_spinlock, flags);

	/* mutex remains locked until spi_bus_unlock is called */

	return 0;
}
EXPORT_SYMBOL_GPL(spi_bus_lock);

/**
 * spi_bus_unlock - release the lock for exclusive SPI bus usage
 * @ctlr: SPI bus master that was locked for exclusive bus access
 * Context: can sleep
 *
 * This call may only be used from a context that may sleep.  The sleep
 * is non-interruptible, and has no timeout.
 *
 * This call releases an SPI bus lock previously obtained by an spi_bus_lock
 * call.
 *
 * Return: always zero.
 */
int spi_bus_unlock(struct spi_controller *ctlr)
{
	ctlr->bus_lock_flag = 0;

	mutex_unlock(&ctlr->bus_lock_mutex);

	return 0;
}
EXPORT_SYMBOL_GPL(spi_bus_unlock);

/* portable code must never pass more than 32 bytes */
#define	SPI_BUFSIZ	max(32, SMP_CACHE_BYTES)

static u8	*buf;

/**
 * spi_write_then_read - SPI synchronous write followed by read
 * @spi: device with which data will be exchanged
 * @txbuf: data to be written (need not be dma-safe)
 * @n_tx: size of txbuf, in bytes
 * @rxbuf: buffer into which data will be read (need not be dma-safe)
 * @n_rx: size of rxbuf, in bytes
 * Context: can sleep
 *
 * This performs a half duplex MicroWire style transaction with the
 * device, sending txbuf and then reading rxbuf.  The return value
 * is zero for success, else a negative errno status code.
 * This call may only be used from a context that may sleep.
 *
 * Parameters to this routine are always copied using a small buffer.
 * Performance-sensitive or bulk transfer code should instead use
 * spi_{async,sync}() calls with dma-safe buffers.
 *
 * Return: zero on success, else a negative error code.
 */
int spi_write_then_read(struct spi_device *spi,
		const void *txbuf, unsigned n_tx,
		void *rxbuf, unsigned n_rx)
{
	static DEFINE_MUTEX(lock);

	int			status;
	struct spi_message	message;
	struct spi_transfer	x[2];
	u8			*local_buf;

	/* Use preallocated DMA-safe buffer if we can.  We can't avoid
	 * copying here, (as a pure convenience thing), but we can
	 * keep heap costs out of the hot path unless someone else is
	 * using the pre-allocated buffer or the transfer is too large.
	 */
	if ((n_tx + n_rx) > SPI_BUFSIZ || !mutex_trylock(&lock)) {
		local_buf = kmalloc(max((unsigned)SPI_BUFSIZ, n_tx + n_rx),
				    GFP_KERNEL | GFP_DMA);
		if (!local_buf)
			return -ENOMEM;
	} else {
		local_buf = buf;
	}

	spi_message_init(&message);
	memset(x, 0, sizeof(x));
	if (n_tx) {
		x[0].len = n_tx;
		spi_message_add_tail(&x[0], &message);
	}
	if (n_rx) {
		x[1].len = n_rx;
		spi_message_add_tail(&x[1], &message);
	}

	memcpy(local_buf, txbuf, n_tx);
	x[0].tx_buf = local_buf;
	x[1].rx_buf = local_buf + n_tx;

	/* do the i/o */
	status = spi_sync(spi, &message);
	if (status == 0)
		memcpy(rxbuf, x[1].rx_buf, n_rx);

	if (x[0].tx_buf == buf)
		mutex_unlock(&lock);
	else
		kfree(local_buf);

	return status;
}
EXPORT_SYMBOL_GPL(spi_write_then_read);

/*-------------------------------------------------------------------------*/

#if IS_ENABLED(CONFIG_OF)
/* must call put_device() when done with returned spi_device device */
struct spi_device *of_find_spi_device_by_node(struct device_node *node)
{
	struct device *dev = bus_find_device_by_of_node(&spi_bus_type, node);

	return dev ? to_spi_device(dev) : NULL;
}
EXPORT_SYMBOL_GPL(of_find_spi_device_by_node);
#endif /* IS_ENABLED(CONFIG_OF) */

#if IS_ENABLED(CONFIG_OF_DYNAMIC)
/* the spi controllers are not using spi_bus, so we find it with another way */
static struct spi_controller *of_find_spi_controller_by_node(struct device_node *node)
{
	struct device *dev;

	dev = class_find_device_by_of_node(&spi_master_class, node);
	if (!dev && IS_ENABLED(CONFIG_SPI_SLAVE))
		dev = class_find_device_by_of_node(&spi_slave_class, node);
	if (!dev)
		return NULL;

	/* reference got in class_find_device */
	return container_of(dev, struct spi_controller, dev);
}

static int of_spi_notify(struct notifier_block *nb, unsigned long action,
			 void *arg)
{
	struct of_reconfig_data *rd = arg;
	struct spi_controller *ctlr;
	struct spi_device *spi;

	switch (of_reconfig_get_state_change(action, arg)) {
	case OF_RECONFIG_CHANGE_ADD:
		ctlr = of_find_spi_controller_by_node(rd->dn->parent);
		if (ctlr == NULL)
			return NOTIFY_OK;	/* not for us */

		if (of_node_test_and_set_flag(rd->dn, OF_POPULATED)) {
			put_device(&ctlr->dev);
			return NOTIFY_OK;
		}

		spi = of_register_spi_device(ctlr, rd->dn);
		put_device(&ctlr->dev);

		if (IS_ERR(spi)) {
			pr_err("%s: failed to create for '%pOF'\n",
					__func__, rd->dn);
			of_node_clear_flag(rd->dn, OF_POPULATED);
			return notifier_from_errno(PTR_ERR(spi));
		}
		break;

	case OF_RECONFIG_CHANGE_REMOVE:
		/* already depopulated? */
		if (!of_node_check_flag(rd->dn, OF_POPULATED))
			return NOTIFY_OK;

		/* find our device by node */
		spi = of_find_spi_device_by_node(rd->dn);
		if (spi == NULL)
			return NOTIFY_OK;	/* no? not meant for us */

		/* unregister takes one ref away */
		spi_unregister_device(spi);

		/* and put the reference of the find */
		put_device(&spi->dev);
		break;
	}

	return NOTIFY_OK;
}

static struct notifier_block spi_of_notifier = {
	.notifier_call = of_spi_notify,
};
#else /* IS_ENABLED(CONFIG_OF_DYNAMIC) */
extern struct notifier_block spi_of_notifier;
#endif /* IS_ENABLED(CONFIG_OF_DYNAMIC) */

#if IS_ENABLED(CONFIG_ACPI)
static int spi_acpi_controller_match(struct device *dev, const void *data)
{
	return ACPI_COMPANION(dev->parent) == data;
}

static struct spi_controller *acpi_spi_find_controller_by_adev(struct acpi_device *adev)
{
	struct device *dev;

	dev = class_find_device(&spi_master_class, NULL, adev,
				spi_acpi_controller_match);
	if (!dev && IS_ENABLED(CONFIG_SPI_SLAVE))
		dev = class_find_device(&spi_slave_class, NULL, adev,
					spi_acpi_controller_match);
	if (!dev)
		return NULL;

	return container_of(dev, struct spi_controller, dev);
}

static struct spi_device *acpi_spi_find_device_by_adev(struct acpi_device *adev)
{
	struct device *dev;

	dev = bus_find_device_by_acpi_dev(&spi_bus_type, adev);
	return to_spi_device(dev);
}

static int acpi_spi_notify(struct notifier_block *nb, unsigned long value,
			   void *arg)
{
	struct acpi_device *adev = arg;
	struct spi_controller *ctlr;
	struct spi_device *spi;

	switch (value) {
	case ACPI_RECONFIG_DEVICE_ADD:
		ctlr = acpi_spi_find_controller_by_adev(adev->parent);
		if (!ctlr)
			break;

		acpi_register_spi_device(ctlr, adev);
		put_device(&ctlr->dev);
		break;
	case ACPI_RECONFIG_DEVICE_REMOVE:
		if (!acpi_device_enumerated(adev))
			break;

		spi = acpi_spi_find_device_by_adev(adev);
		if (!spi)
			break;

		spi_unregister_device(spi);
		put_device(&spi->dev);
		break;
	}

	return NOTIFY_OK;
}

static struct notifier_block spi_acpi_notifier = {
	.notifier_call = acpi_spi_notify,
};
#else
extern struct notifier_block spi_acpi_notifier;
#endif

static int __init spi_init(void)
{
	int	status;

	buf = kmalloc(SPI_BUFSIZ, GFP_KERNEL);
	if (!buf) {
		status = -ENOMEM;
		goto err0;
	}

	status = bus_register(&spi_bus_type);
	if (status < 0)
		goto err1;

	status = class_register(&spi_master_class);
	if (status < 0)
		goto err2;

	if (IS_ENABLED(CONFIG_SPI_SLAVE)) {
		status = class_register(&spi_slave_class);
		if (status < 0)
			goto err3;
	}

	if (IS_ENABLED(CONFIG_OF_DYNAMIC))
		WARN_ON(of_reconfig_notifier_register(&spi_of_notifier));
	if (IS_ENABLED(CONFIG_ACPI))
		WARN_ON(acpi_reconfig_notifier_register(&spi_acpi_notifier));

	return 0;

err3:
	class_unregister(&spi_master_class);
err2:
	bus_unregister(&spi_bus_type);
err1:
	kfree(buf);
	buf = NULL;
err0:
	return status;
}

