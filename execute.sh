echo '================================================================='
echo '==                        Alunos                               =='
echo '================================================================='
cat ./alunos.txt
echo ''
echo ''
echo '================================================================='
echo '==     Em caso de duvidas/problemas leia o arquivo Readme.md   =='
echo '================================================================='
echo ''

make
echo "./bin/main < ./test/input/01.in > result.txt"
./bin/main < ./test/input/01.in > result.txt

echo ''
echo ''
echo '================================================================='
echo '==              Programa compilado e executado                 =='
echo '================================================================='