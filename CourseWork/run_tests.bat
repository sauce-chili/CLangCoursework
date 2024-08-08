echo Protocol: > results.txt
echo. >> results.txt
chcp 1251 >NUL

set current_test=tests\test1\
type %current_test%description.txt >> results.txt
echo. >> results.txt
echo Input data: >> results.txt
echo. >> results.txt
type %current_test%test.txt >> results.txt
echo. >> results.txt
echo Expected result:>> results.txt
type %current_test%exp_test.txt >> results.txt
echo. >> results.txt
echo Result:>> results.txt
CourseWork_Smirnov.exe < %current_test%test.txt >> results.txt
echo. >> results.txt
echo ------------------------- >> results.txt


set current_test=tests\test2\
type %current_test%description.txt >> results.txt
echo. >> results.txt
echo Input data: >> results.txt
echo. >> results.txt
type %current_test%test.txt >> results.txt
echo. >> results.txt
echo Expected result:>> results.txt
type %current_test%exp_test.txt >> results.txt
echo. >> results.txt
echo Result:>> results.txt
CourseWork_Smirnov.exe < %current_test%test.txt >> results.txt
echo. >> results.txt
echo ------------------------- >> results.txt


set current_test=tests\test3\
type %current_test%description.txt >> results.txt
echo. >> results.txt
echo Input data: >> results.txt
echo. >> results.txt
type %current_test%test.txt >> results.txt
echo. >> results.txt
echo Expected result:>> results.txt
type %current_test%exp_test.txt >> results.txt
echo. >> results.txt
echo Result:>> results.txt
CourseWork_Smirnov.exe < %current_test%test.txt >> results.txt
echo. >> results.txt
echo ------------------------- >> results.txt

set current_test=tests\test4\
type %current_test%description.txt >> results.txt
echo. >> results.txt
echo Input data: >> results.txt
echo. >> results.txt
type %current_test%test.txt >> results.txt
echo. >> results.txt
echo Expected result:>> results.txt
type %current_test%exp_test.txt >> results.txt
echo. >> results.txt
echo Result:>> results.txt
CourseWork_Smirnov.exe < %current_test%test.txt >> results.txt
echo. >> results.txt
echo ------------------------- >> results.txt

set current_test=tests\test5\
type %current_test%description.txt >> results.txt
echo. >> results.txt
echo Input data: >> results.txt
echo. >> results.txt
type %current_test%test.txt >> results.txt
echo. >> results.txt
echo Expected result:>> results.txt
type %current_test%exp_test.txt >> results.txt
echo. >> results.txt
echo Result:>> results.txt
CourseWork_Smirnov.exe < %current_test%test.txt >> results.txt
echo. >> results.txt
echo ------------------------- >> results.txt
