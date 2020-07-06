./ft_ls  /bin/ -la > test/a
ls /bin -la > test/b
#./ft_ls  -l > test/a1
#ls  -l > test/b1
#./ft_ls  -la > test/a2
#ls  -la > test/b2
#./ft_ls  -lat > test/a3
#ls  -lat > test/b3
#./ft_ls  -latu > test/a4
#ls  -latu > test/b4
#./ft_ls  -latuS > test/a5
#ls  -latuS > test/b5
#./ft_ls zzzz -1lu > test/a6
#ls  zzzz -1lu > test/b6
#./ft_ls -1ltc /usr/share > test/a7
#ls -1ltc /usr/share > test/b7
##./ft_ls -lRa ft_printf > test/a8
##ls -lRa ft_printf > test/b8
#./ft_ls -lR > test/a9
#ls -lR > test/b9
diff  test/a test/b
#diff  test/a1 test/b1
#diff  test/a2 test/b2
#diff  test/a3 test/b3
#diff  test/a4 test/b4
#diff  test/a5 test/b5
#diff  test/a6 test/b6
#diff  test/a7 test/b7
#diff  test/a8 test/b8
#diff  test/a9 test/b9

